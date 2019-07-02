#include "StdAfx.h"
#include ".\index_storage_hdr.h"
#include "..\ASCInterface\defines.h"

USES_LOAD_MANAGER;

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
using namespace SS::Interface::Core::CommonContainers;

//--------------------------------------------------------------------//

CIndexStorageHeaders::CIndexStorageHeaders(INdxStorageWithStatistic* pNdxStorage)
:CIndexStatisticStorage(pNdxStorage), m_pHeadersInfoStorage(NULL), m_uiLastFilledDocumentIndex(EMPTY_VALUE)
{
	m_pHeadersInfoStorage=pNdxStorage->GetTextImagesStorage();

	//���������� ��������� ����
	m_uiCashMaxSize=10000;
	m_uiCashIndexMinFreq=2;
}

CIndexStorageHeaders::~CIndexStorageHeaders(void)
{
}

void CIndexStorageHeaders::AddIndexes(ITextBlockCut* pTextBlockCut)
{
	if(ISNULL(pTextBlockCut)) return;
	
	//��������� ������� ������������ ���������
	if(!m_DocumentHeadersInfo.IncCurrentHeaderID(pTextBlockCut->GetLevel()))
	{
		//���� �� ����� ��������� ������������� ��������� ������ ��������� 
		//�������� � ���
		wchar_t buf[200];
		swprintf(buf, L"Max Headers count exceeded, next header will be lost!!! DocID: %u", 
			m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber));
		SAVE_LOG(SS_WARNING AND buf);
		return;
	}

	//������ ����������
	CIndexStatisticStorage::AddIndexes(pTextBlockCut);
}

void CIndexStorageHeaders::AddIndexationIndex(IIndexationIndex* pIndexationIndex)
{
	
	///��������� ������� ���������
	m_DocumentHeadersInfo.UpdateHeaderPosition(m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictWordInTextNumber));

	//--------------------------
	//��������� ��������� �����
	if(pIndexationIndex!=NULL){
		//������ ���������� � �����
		unsigned int CoordBuffer[5];
		CoordBuffer[1]=m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber);
		CoordBuffer[4]=m_DocumentHeadersInfo.GetCurrentHeaderID()->GetID();

		//ToConsole(L"CoordBuffer[1]", CoordBuffer[1]);
		//ToConsole(L"HeaderID", CoordBuffer[4]);
		
		unsigned int uiIndex=pIndexationIndex->GetFirstIndex();
		if(ISNULL(uiIndex)) return;
		while(uiIndex){

			//ToConsole(L"uiIndex", uiIndex);

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

void CIndexStorageHeaders::CompleteDocumentIndexing(void)
{
	m_DocumentHeadersInfo.View();

	//��������� ���������� �� ����������
	unsigned int uiTextIndex=EMPTY_VALUE;
	CDocumentHeadersInfo::THeaderInfoCollection* pHeaderInfoCollection=m_DocumentHeadersInfo.GetHeaderInfoCollection();
	m_pHeadersInfoStorage->AppendWholeData((unsigned char*)&pHeaderInfoCollection->front(), 
		(unsigned int)pHeaderInfoCollection->size()*sizeof(SHeaderInfo), &uiTextIndex);
	m_DocumentHeadersInfo.Reset();

	//������ ����������
	CIndexStatisticStorage::CompleteDocumentIndexing();
}

void CIndexStorageHeaders::FillHeaderPositions(unsigned int uiDocumentIndex, 
	CLevelHeaderID* pLevelHeaderID, SHeaderPositions* pOutHeaderPositions)
{
	if(ISNULL(m_pHeadersInfoStorage)) return;
	if(ISNULL(pLevelHeaderID)) return;
	if(ISNULL(pOutHeaderPositions)) return;
	
	CDocumentHeadersInfo::THeaderInfoCollection* pHeaderInfoCollection=NULL;

	if(m_uiLastFilledDocumentIndex!=uiDocumentIndex){
		//��������� � ������ ������ ��������� ������ ������
		unsigned int uiHeadersBufferSize;
		m_pHeadersInfoStorage->MoveToAndGetDataSize(uiDocumentIndex, &uiHeadersBufferSize);
		
		//����������� ����� ������ ������
		pHeaderInfoCollection=m_DocumentHeadersInfo.GetHeaderInfoCollection();
		pHeaderInfoCollection->resize(uiHeadersBufferSize/sizeof(SHeaderInfo));
		m_pHeadersInfoStorage->ReadWholeData((unsigned char*)&pHeaderInfoCollection->front(), uiHeadersBufferSize);	
		//��������� ������ ���������
		m_uiLastFilledDocumentIndex=uiDocumentIndex;
	}else{
		//������ ��� � ������ �������� �� �� �����
		pHeaderInfoCollection=m_DocumentHeadersInfo.GetHeaderInfoCollection();
	}

	//������� ��������� ���� ������ ���������
	for(unsigned int i=0; i<pHeaderInfoCollection->size(); i++){
		if(pHeaderInfoCollection->at(i).m_HeaderID==(*pLevelHeaderID)){
			memcpy(pOutHeaderPositions, &pHeaderInfoCollection->at(i).m_HeaderPositions, sizeof(SHeaderPositions));
			return;
		}
	}

}

CDocumentHeadersInfo* CIndexStorageHeaders::FillHeadersInfo(unsigned int uiDocumentIndex)
{
	if(ISNULL(m_pHeadersInfoStorage)) return NULL;
	
	//��������� � ������ ������ ��������� ������ ������
	unsigned int uiHeadersBufferSize;
	m_pHeadersInfoStorage->MoveToAndGetDataSize(uiDocumentIndex, &uiHeadersBufferSize);
	
	//����������� ����� ������ ������
	CDocumentHeadersInfo::THeaderInfoCollection* pHeaderInfoCollection=m_DocumentHeadersInfo.GetHeaderInfoCollection();
	pHeaderInfoCollection->resize(uiHeadersBufferSize/sizeof(SHeaderInfo));
	m_pHeadersInfoStorage->ReadWholeData((unsigned char*)&pHeaderInfoCollection->front(), uiHeadersBufferSize);	
	
	return &m_DocumentHeadersInfo;
}

void CIndexStorageHeaders::FillHeadersToTextBlock(ITextBlock* pTextBlock, 
		Containers::CIntervalAndHeader* pInterval, unsigned int uiGroupID)
{
	if(ISNULL(pTextBlock)) return;
	if(ISNULL(pInterval)) return;
	if(ISNULL(m_pHeadersInfoStorage)) return;
	
	unsigned int uiDocumentIndex=pTextBlock->GetTextFeature()->GetTextNumber();
	
	//int a=0;
	//if(uiDocumentIndex==17383){
	//	a=17383;
	//}

	CLevelHeaderID HeaderID(pInterval->m_HeaderID.GetID());
	list<CLevelHeaderID> HeaderIDList;
	while(!HeaderID.IsEmpty()){
		HeaderIDList.push_front(HeaderID);
		//�������� ������������ ���������
		HeaderID=HeaderID.MakeParentHeader();
	}

	list<CLevelHeaderID>::iterator itHeaderID=HeaderIDList.begin();
	while(itHeaderID!=HeaderIDList.end()){
		//�������� ������� ���������
		SHeaderPositions HeaderPositions;
		FillHeaderPositions(uiDocumentIndex, &(*itHeaderID), &HeaderPositions);
		
		//��������� ��� ����������
		CInterval Interval(HeaderPositions.m_uiHeadPosition, HeaderPositions.m_uiTailPosition, pInterval->m_uiWeight);
		wstring wsIndexStorageName(GetIndexStorageName());
		ITextBlockCut* pTextBlockCut=GetTextsBinaryStorage()->FillTextBlock(pTextBlock, &Interval, &wsIndexStorageName);	
		pTextBlockCut->SetNumber(uiGroupID);
		pTextBlockCut->SetType(SS::Core::Types::IndexationSearch::tctHeader);
		pTextBlockCut->SetLevel(itHeaderID->GetHeaderLevel());

		itHeaderID++;
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}