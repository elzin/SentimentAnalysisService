#include "StdAfx.h"
#include ".\index_storage.h"
#include ".\index_cash.h"
#include ".\text_binary_storage_ex.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Storages
{

using namespace SS::Interface::Core::NdxSE::NdxDataStorage;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Core::NdxSE::NdxProcessor::MemoryManagement;
using namespace SS::Interface::Core::CommonContainers;

//--------------------------------------------------------------------//

CIndexStorage::CIndexStorage(INdxStorage* pNdxStorage)
:m_pNdxStorage(pNdxStorage),
m_pIndexEntryPointTable(NULL),
m_pTextsBinaryStorage(NULL),
m_pCoordinateStorage(NULL),
m_pIndexCash(NULL), m_pContainersFactory(NULL),
m_uiSentencesControlLevelNumber(EMPTY_VALUE), m_uiWordsControlLevelNumber(EMPTY_VALUE),
m_pLogIndexCoordinatesFileStream(NULL), m_bLogIndexCoordinates(false)
{
	if(ISNULL(m_pNdxStorage)) return;

	m_pIndexEntryPointTable=new CIndexEntryPointTable(m_pNdxStorage->GetEntryPointsStorage());
	m_pCoordinateStorage=m_pNdxStorage->GetCoordinateStorage();
	//m_pTextsBinaryStorage=new CTextsBinaryStorageSimple(m_pNdxStorage->GetTextImagesStorage());

	INdxFile* pNdxTextsOffsets=NULL;
	INdxFile* pNdxTextBlocksOffsets=NULL;
	INdxVectorStorage* pNdxTextBlocksContent=NULL;
	m_pNdxStorage->GetTextImagesStorages(&pNdxTextsOffsets, &pNdxTextBlocksOffsets, &pNdxTextBlocksContent);
	m_pTextsBinaryStorage=new CTextsBinaryStorageEx(pNdxTextsOffsets, pNdxTextBlocksOffsets, pNdxTextBlocksContent);

	unsigned int uiLevelIndex=0;
	SNdxLevelInfo const* pNdxLevelInfo=NULL;
	do{
		//�������� ���������� � ��������� ������
		pNdxLevelInfo=m_pNdxStorage->GetLevelInfo(uiLevelIndex);
		if(ISNULL(pNdxLevelInfo)) break;
		
		if(pNdxLevelInfo->m_eControlType==SNdxLevelInfo::lctSentences){
			//���� ������� ������������ ���������� ����������� ���������� ��� �����
			m_uiSentencesControlLevelNumber=uiLevelIndex;
		}else if(pNdxLevelInfo->m_eControlType==SNdxLevelInfo::lctWords){
			//���� ������� ������������ ���������� ���� ���������� ��� �����
			m_uiWordsControlLevelNumber=uiLevelIndex;
		}

		
		//������ ������� � ���������
		m_CoordinateLevelInfo.push_back(pNdxLevelInfo);
	}while(++uiLevelIndex!=m_pNdxStorage->GetLevelsNumber());
	
	m_pContainersFactory=new CContainersFactory(this);

	//���������� ��������� ����
	m_uiCashMaxSize=100000/*100000*/;
	m_uiCashIndexMinFreq=2;
}

CIndexStorage::~CIndexStorage(void)
{
	if(m_pIndexEntryPointTable) delete m_pIndexEntryPointTable;
	if(m_pTextsBinaryStorage) delete m_pTextsBinaryStorage;
	m_pCoordinateStorage=NULL;
	
	if(m_pIndexCash) delete m_pIndexCash;
	if(m_pContainersFactory) delete m_pContainersFactory;
}

void CIndexStorage::CreateIndexCash(void)
{
	if(m_pIndexCash){
		TO_CONSOLE(L"IndexCash already created");
		return;
	}

	//������� ��� ��������
	m_pIndexCash=new CIndexCash(m_pContainersFactory, m_uiCashMaxSize, m_uiCashIndexMinFreq);
}

CIndexCash*  CIndexStorage::GetIndexCash(void)
{
	if(!m_pIndexCash){
		CreateIndexCash();
	}

	return m_pIndexCash;
}

unsigned int CIndexStorage::GetBitMapSizeByLevel(unsigned char ucLevel)
{
	if(ucLevel<GetLevelStoragesNumber()){
		unsigned char ucBitPerLevel=m_CoordinateLevelInfo[ucLevel]->m_ucBitPerLevel;
		if(ucBitPerLevel<32){
			return SS::Core::NdxSE::NdxProcessor::Containers::carrBmSizes[ucBitPerLevel];
		}else{
			TO_CONSOLE(L"Too much BitPerLevel!");
			return 0;
		}
	}else{
		if(ucLevel==GetWordsControlLevelNumber()+1){
			//��� ������ ��� ������� ����, ���������� 256
			return SS::Core::NdxSE::NdxProcessor::Containers::carrBmSizes[8];
		}else{
			TO_CONSOLE(L"No such level!");
			return 0;
		}
	}
}

void CIndexStorage::AddIndexes(SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut)
{
	if(ISNULL(pTextBlockCut)) return;

	IIndexAndPosition* pIndexAndPosition=NULL;

	pIndexAndPosition=pTextBlockCut->GetFirstIndexAndPosition();
	while(pIndexAndPosition){

		//������� ������� � ���������
		AddIndex(pIndexAndPosition);

		pIndexAndPosition=pTextBlockCut->GetNextIndexAndPosition();
	}
}

void	CIndexStorage::AddIndex(IIndexAndPosition* pIndexAndPosition)
{
	if(ISNULL(pIndexAndPosition)) return;

	if(ISNULL(GetIndexCash())) return;
	if(ISNULL(m_pTextsBinaryStorage)) return;
	
	//��������� ����������
	int iPosDiffer=pIndexAndPosition->GetPosition()-
		m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictWordInTextNumber);
	
	//ToConsole(L"iPosDiffer", (unsigned int)iPosDiffer);
	//ToConsole(L"Indexed Position", (unsigned int)pIndexAndPosition->GetPosition());
	
	if(iPosDiffer<=0){
		wchar_t buf[100];
		wsprintf(buf, L"For index storage %s pIndexAndPosition not increasing!!!", GetIndexStorageName());
		TO_CONSOLE(buf);
		return;
	}

	//����������� �������
	m_CoordinateCounter.Increment(SNdxLevelInfo::ictWordInTextNumber, iPosDiffer);

	//--------------------------
	//��������� ��������� �����
	//�� ������� ������� ������ ������ ��������� �������
	for(int i=0; i<iPosDiffer-1; i++)	m_pTextsBinaryStorage->AddIndex(NULL, EMPTY_VALUE);
	m_pTextsBinaryStorage->AddIndex(pIndexAndPosition->GetServiceIndex(), pIndexAndPosition->GetFirstCharPosition());
	//--------------------------

	//ToConsole(pIndexAndPosition->GetWord());

	//--------------------------
	//��������� ��������� �����
	AddIndexationIndex(pIndexAndPosition->GetIndexationIndex());
	//--------------------------
}

void CIndexStorage::AddIndexationIndex(IIndexationIndex* pIndexationIndex)
{
	//--------------------------
	//��������� ��������� �����
	if(pIndexationIndex!=NULL){
		//������ ���������� � �����
		unsigned int CoordBuffer[5];
		CoordBuffer[1]=m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber);
		CoordBuffer[4]=m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictWordInTextNumber);

		unsigned int uiIndex=pIndexationIndex->GetFirstIndex();
		if(ISNULL(uiIndex)) return;
		while(uiIndex){
			//ToConsole(L"uiIndex", uiIndex);
			//ToConsole(L"CoordBuffer[1]", CoordBuffer[1]);
			//ToConsole(L"CoordBuffer[4]", CoordBuffer[4]);

			if(!m_pLogIndexCoordinatesFileStream && m_bLogIndexCoordinates){
				//���� ��������� ���� ��������� ���-���� ��� ��������
				wstring wsLogFileName(L"./log_icoord_");
				wsLogFileName.append(GetIndexStorageName());
				wsLogFileName.append(L".txt");
				m_pLogIndexCoordinatesFileStream=_wfopen(wsLogFileName.c_str(), L"wt");
				if(ISNULL(m_pLogIndexCoordinatesFileStream)){
					TO_CONSOLE(L"Cann't open log file");
				}
			}

			//����� � ���: ������; ����� ������; ������� � ������
			if(m_pLogIndexCoordinatesFileStream)
				fwprintf(m_pLogIndexCoordinatesFileStream, L"%u; %u; %u;\n", uiIndex, CoordBuffer[1], CoordBuffer[4]);

			//���� ������ ���� ��������� ��� � ���
			GetIndexCash()->Add(uiIndex, CoordBuffer, 5);
			//�������� ��������� ������ �� ������ �������
			uiIndex=pIndexationIndex->GetNextIndex();
		}
	}else{
		ISNULL(pIndexationIndex);
	}
	//--------------------------
}

void CIndexStorage::UpdateIndexedData(void)
{
	if(!m_pIndexCash) return;

	if(ISNULL(m_pTextsBinaryStorage)) return;
	if(ISNULL(m_pNdxStorage)) return;

	//GetIndexCash()->View();

	//������������� �� ��������� ����� ������
	m_pTextsBinaryStorage->SetTextBlockComplete();

	//��������� ��� ������������������ ������� ������� �� ����
	START_TICK(L"Cash_Update");
	bool bWasUpdate=GetIndexCash()->Update();
	STOP_TICK(L"Cash_Update");
	//VIEW_TICK(L"Cash_Update");

	if(bWasUpdate){
		//ToConsole(L"WasUpdate");
		START_TICK(L"Index_Flush");
		//���� ������ ��� ��� ��� ���������� � ��������� ���������� �� ����
		m_pNdxStorage->Flush();
		STOP_TICK(L"Index_Flush");
		//VIEW_TICK(L"Index_Flush");
	}

	//GetIndexCash()->View();
}

void CIndexStorage::CompleteDocumentIndexing(void)
{
	if(ISNULL(m_pTextsBinaryStorage)) return;
	//������������� �� ��������� ����� ������
	m_pTextsBinaryStorage->SetTextComplete();
	
	//����������� �������
	m_CoordinateCounter.Increment(SNdxLevelInfo::ictTextAbsNumber);
}

void CIndexStorage::CompleteIndexing(void)
{
	if(!m_pIndexCash) return;
	if(ISNULL(m_pNdxStorage)) return;
	
	//��� ������� ���� ������� � ���������
	GetIndexCash()->Flush();
	//��� ��� ���������� � ��������� ���������� �� ����
	m_pNdxStorage->Flush();

	//���������� ������� ���������
	m_CoordinateCounter.Reset();
	
	//���� ����� ��� �� ���������� ���������� ��������� ���
	if(m_pLogIndexCoordinatesFileStream){
		fclose(m_pLogIndexCoordinatesFileStream);
		m_pLogIndexCoordinatesFileStream=NULL;
	}
}

void CIndexStorage::PrepareIndexing(void)
{
	if(ISNULL(m_pTextsBinaryStorage)) return;

	//���������� ������� ���������
	m_CoordinateCounter.Reset();
	//������� ������� ���������
	m_CoordinateCounter.Update(SNdxLevelInfo::ictTextAbsNumber, m_pTextsBinaryStorage->GetTextsNumber());
}

//--------------------------------------------------------------------//

}
}
}
}
}