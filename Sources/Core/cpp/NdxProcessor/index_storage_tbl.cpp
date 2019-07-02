#include "StdAfx.h"
#include ".\index_storage_tbl.h"
#include ".\sr_filler.h"
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

using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Interface::Core::NdxSE::NdxDataStorage;

//--------------------------------------------------------------------//

CIndexStorageTables::CIndexStorageTables(INdxStorageWithStatistic* pNdxStorage)
	:CIndexStatisticStorage(pNdxStorage), m_uiLastFilledDocumentIndex(EMPTY_VALUE), 
	m_uiLastFilledTableIndex(EMPTY_VALUE), m_uiLastFilledRowIndex(EMPTY_VALUE)
{
	m_pTablesInfoStorage=pNdxStorage->GetTextImagesStorage();

	//���������� ��������� ����
	m_uiCashMaxSize=10000;
	m_uiCashIndexMinFreq=2;
}

void CIndexStorageTables::AddTableIndexes(IIndexationResult* pIndexationResult)
{
	if(ISNULL(pIndexationResult)) return;

	ITextBlock* pTextBlock=NULL;
	ITextBlockCut* pTextBlockCut=NULL;
	IIndexAndPosition* pIndexAndPosition=NULL;
	unsigned int uiCellsCount=EMPTY_VALUE;
	
	//������ ������� ������������� � ����
	if(m_CurrentTrcID.IsEmpty()) m_CurrentTrcID.SetIDByType(Containers::CTrcID::etrcTable, 0);
	
	//��������� �������� �� ������ �������
	m_TablesOffsets.push_back(Containers::STableInfo());
	m_TablesOffsets.back().m_uiCellsOffset=(unsigned int)m_CellPositions.size();
	
	pTextBlock=pIndexationResult->GetFirstTextBlock();
	while(pTextBlock){
		
		//�������� ���������� �����
		unsigned int uiTBCCount=GetTextBlockCutCount(pTextBlock);
		if(uiTBCCount==EMPTY_VALUE){
			//���� ������ ������ ��������� � ���������� �����
			pTextBlock=pIndexationResult->GetNextTextBlock();
			continue;
		}

		if(uiCellsCount==EMPTY_VALUE){
			//!!!������������� �� ��, ��� ������� ������������� ����������
			//����� � ������ ������ ���� ����������, ������ ������ � ���� �� ���������

			//��� ������ ������, ������������� ��������
			uiCellsCount=uiTBCCount;
			//���������� ���������� ����� ������ �������
			m_TablesOffsets.back().m_uiColumnCount=uiCellsCount;
		}else{
			//���� �� ������ ������, ���������� �� ��������� �����
			//���� ��� �� ��������� �� ����������� ��� ������
			if(uiCellsCount!=uiTBCCount){
				//�������� � ���
				wchar_t buf[200];
				swprintf(buf, L"Cell count in table not equal. \n\tDocID: %u \n\tTableID: %u \n\tRowID: %u \n\tCellCount: %u \n\tNeeded CellCount: %u", 
					m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber), 
					m_CurrentTrcID.GetIDByType(Containers::CTrcID::etrcTable),
					m_CurrentTrcID.GetIDByType(Containers::CTrcID::etrcRow), 
					uiTBCCount, uiCellsCount);
				SAVE_LOG(SS_WARNING AND buf);
				//��������� � ���������� �����
				pTextBlock=pIndexationResult->GetNextTextBlock();
				continue;
			}
		}
		
		//���� ������ ������������� �������� ����������� ��
		pTextBlockCut=pTextBlock->GetFirstBlockCut();
		while(pTextBlockCut){
			//������ ��������� ������� ������
			m_CellPositions.push_back(EMPTY_VALUE);

			//���������� �������
			//Extracting::CSearchResultFiller::ViewTextBlockCut(pTextBlockCut, true, true);
				
			AddIndexes(pTextBlockCut);
			
			//���� TextBlockCut, ��� ���� ������ ����������� �������
			m_CurrentTrcID.IncIDByType(Containers::CTrcID::etrcCell);
			//��������� � ���������� �����
			pTextBlockCut=pTextBlock->GetNextBlockCut();
		}
		
		//� ����� ������ ��������� ������� ����� ���������� �����
		m_CellPositions.push_back(m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictWordInTextNumber)+1);

		//���� TextBlock, ��� ���� ������ ����������� �������
		m_CurrentTrcID.IncIDByType(Containers::CTrcID::etrcRow);
		//��������� � ���������� �����
		pTextBlock=pIndexationResult->GetNextTextBlock();
	}
	
	if(m_TablesOffsets.back().m_uiColumnCount==EMPTY_VALUE){
		//���� � ������� ���������� ���������� �������, �� ������� ��� �������	
		//��� ������
		m_TablesOffsets.pop_back();

		wchar_t buf[200];
		swprintf(buf, L"Empty table!!!. \n\tDocID: %u \n\tTableID: %u", 
			m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber), 
			m_CurrentTrcID.GetIDByType(Containers::CTrcID::etrcTable));
		SAVE_LOG(SS_WARNING AND buf);
	}else{
		//���� IndexationResult ��� �������, ����������� �������
		m_CurrentTrcID.IncIDByType(Containers::CTrcID::etrcTable);
	}
}

unsigned int CIndexStorageTables::GetTextBlockCutCount(ITextBlock* pTextBlock)
{
	if(ISNULL(pTextBlock)) return 0;
	ITextBlockCut* pTextBlockCut=pTextBlock->GetFirstBlockCut();
	unsigned int uiInc=0;
	bool bEmptyRow=true;
	while(pTextBlockCut){
		uiInc++;
		if(pTextBlockCut->GetFirstIndexAndPosition()!=NULL) bEmptyRow=false;
		pTextBlockCut=pTextBlock->GetNextBlockCut();
	}

	//��� ������ ������ ������������ ������ ����������.
	if(bEmptyRow) uiInc=EMPTY_VALUE;
	return uiInc;		
}

void CIndexStorageTables::AddIndexationIndex(IIndexationIndex* pIndexationIndex)
{
	if(m_CellPositions.back()==EMPTY_VALUE){
		m_CellPositions.back()=m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictWordInTextNumber);
	}

	//ToConsole(L"m_CellPositions.back()", m_CellPositions.back());

	//--------------------------
	//��������� ��������� �����
	if(pIndexationIndex!=NULL){
		//������ ���������� � �����
		unsigned int CoordBuffer[5];
		CoordBuffer[1]=m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber);
		CoordBuffer[4]=m_CurrentTrcID.GetTrcID();

		//ToConsole(L"CoordBuffer[1]", CoordBuffer[1]);
		//m_CurrentTrcID.View();
		
		unsigned int uiIndex=pIndexationIndex->GetFirstIndex();
		if(ISNULL(uiIndex)) return;
		while(uiIndex){

			//ToConsole(L"uiIndex", uiIndex);

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

void CIndexStorageTables::CompleteDocumentIndexing(void)
{
	//������ � ��������� ������� ������

	//��������� �������� �� ������������� ������� 
	//�� ����� ����� ���� ��������� ������ ������ �������
	m_TablesOffsets.push_back(Containers::STableInfo());
	m_TablesOffsets.back().m_uiCellsOffset=(unsigned int)m_CellPositions.size();

	//����� �������� �� �������
	unsigned int uiTablesOffsetsSize=(unsigned int)m_TablesOffsets.size()*sizeof(Containers::STableInfo);
	m_pTablesInfoStorage->AppendDataChunk((unsigned char*)&uiTablesOffsetsSize, sizeof(unsigned int));
	m_pTablesInfoStorage->AppendDataChunk((unsigned char*)&m_TablesOffsets.front(), uiTablesOffsetsSize);
	
	//����� ������� ����� ������
	m_pTablesInfoStorage->AppendDataChunk((unsigned char*)&m_CellPositions.front(), (unsigned int)m_CellPositions.size()*sizeof(unsigned int));

	//��������� ����������
	unsigned int uiTextIndex=EMPTY_VALUE;
	m_pTablesInfoStorage->AppendDataChunkComplete(&uiTextIndex);
	m_TablesOffsets.clear();
	m_CellPositions.clear();

	//���������� �������
	m_CurrentTrcID.Reset();
	//������ ����������
	CIndexStatisticStorage::CompleteDocumentIndexing();
}

void CIndexStorageTables::FillTablePositions(unsigned int uiDocumentIndex, unsigned int uiTableIndex, unsigned int uiRowIndex)
{
	if(ISNULL(m_pTablesInfoStorage)) return;
	
	unsigned int uiTablesOffsetsSize=0;

	if(m_uiLastFilledDocumentIndex!=uiDocumentIndex){ 
		//���� ������ ��������� ���������, ������ ������� ������

		//��������� � ������ ������ ��������� ������ ������
		unsigned int uiBufferSize;
		m_pTablesInfoStorage->MoveToAndGetDataSize(uiDocumentIndex, &uiBufferSize);
		
		//����������� ����� ������ �������� �� �������
		m_pTablesInfoStorage->ReadDataChunk((unsigned char*)&uiTablesOffsetsSize, sizeof(unsigned int));
		m_TablesOffsets.resize(uiTablesOffsetsSize/sizeof(Containers::STableInfo));
		m_pTablesInfoStorage->ReadDataChunk((unsigned char*)&m_TablesOffsets.front(), uiTablesOffsetsSize);
		
		//��������� ������ ���������
		m_uiLastFilledDocumentIndex=uiDocumentIndex;
		m_uiLastFilledTableIndex=EMPTY_VALUE;
		m_uiLastFilledRowIndex=EMPTY_VALUE;
	}

	if(m_uiLastFilledTableIndex!=uiTableIndex){
		//���� ������ ������� ���������, ������ 
		//����������� ����� �������� ����� ������� �������

		if(uiTableIndex>=m_TablesOffsets.size()-1){
			TO_CONSOLE(L"Invalid table index!!!");
			ToConsole(L"uiTableIndex", uiTableIndex);
			ToConsole(L"DocumentIndex", m_uiLastFilledDocumentIndex);
			return;
		}

		//���������� ����� ��� ������ + 1, ����� ���������� �����
		m_CellPositions.resize(m_TablesOffsets[uiTableIndex].m_uiColumnCount+1);
		
		//��������� ������ �������
		m_uiLastFilledTableIndex=uiTableIndex;
		m_uiLastFilledRowIndex=EMPTY_VALUE;
	}

	if(m_uiLastFilledRowIndex!=uiRowIndex){
		//���� ������ ������ ���������, ������ ������� ����� ������
		//m_TablesOffsets[uiTableIndex].View();
		
		unsigned int uiRowsCount=m_TablesOffsets[uiTableIndex].GetRowsCount(m_TablesOffsets[uiTableIndex+1].m_uiCellsOffset);

		if(uiRowIndex>=uiRowsCount){
			TO_CONSOLE(L"Invalid uiRowIndex index!!!");
			ToConsole(L"uiTableIndex", uiTableIndex);
			ToConsole(L"DocumentIndex", m_uiLastFilledDocumentIndex);
			ToConsole(L"uiRowIndex", uiRowIndex);
			ToConsole(L"uiRowsCount", uiRowsCount);
			return;
		}

		//������� � �������� ��������� ������
		m_pTablesInfoStorage->SeekInData(sizeof(unsigned int)+
			((unsigned int)m_TablesOffsets.size()*sizeof(Containers::STableInfo))+
			(m_TablesOffsets[uiTableIndex].m_uiCellsOffset*sizeof(unsigned int))+
			(uiRowIndex*(m_TablesOffsets[uiTableIndex].m_uiColumnCount+1)*sizeof(unsigned int)));

		//������ ������� ����� �������
		m_pTablesInfoStorage->ReadDataChunk((unsigned char*)&m_CellPositions.front(), (unsigned int)m_CellPositions.size()*sizeof(unsigned int));
		
		//��������� ������ ������
		m_uiLastFilledRowIndex=uiRowIndex;
	}
}

unsigned int CIndexStorageTables::GetCellTailPosition(unsigned int uiCellIndex)
{
	unsigned int uiCellPosition=EMPTY_VALUE;
	if(uiCellIndex<m_CellPositions.size()-1 || uiCellIndex==EMPTY_VALUE){
		//��������� � ��������� ������ � ���� �������� �������
		uiCellIndex++;
		do{
			if(m_CellPositions[uiCellIndex]!=EMPTY_VALUE){
				uiCellPosition=m_CellPositions[uiCellIndex]-1;
				break;
			}
		}while(++uiCellIndex<m_CellPositions.size());
	}
	return uiCellPosition;
}

void CIndexStorageTables::FillTablePositions(unsigned int uiDocumentIndex, 
	unsigned int uiTableIndex, Containers::STablePositions* pOutTablePositions, unsigned int uiHeadRowIndex, unsigned int uiTailRowIndex)
{
	if(ISNULL(m_pTablesInfoStorage)) return;
	if(ISNULL(pOutTablePositions)) return;
	
	//��������� �� ������ ���������� �������
	if(uiTableIndex==EMPTY_VALUE || uiHeadRowIndex==EMPTY_VALUE){
		pOutTablePositions->m_uiHeadPosition=EMPTY_VALUE;
		pOutTablePositions->m_uiTailPosition=EMPTY_VALUE;
		return;
	}

	if(uiTailRowIndex==EMPTY_VALUE) uiTailRowIndex=(unsigned int)m_CellPositions.size()-1;
	
	if(uiHeadRowIndex>uiTailRowIndex){
		TO_CONSOLE(L"Invalid rows indexes!!!");
		ToConsole(L"uiHeadRowIndex", uiHeadRowIndex);
		ToConsole(L"uiTailRowIndex", uiTailRowIndex);
		return;
	}

	//��������� ������� �������� ������
	FillTablePositions(uiDocumentIndex, uiTableIndex, uiHeadRowIndex);
	//���������� ������� ������� ����� ������ ������ ������
	pOutTablePositions->m_uiHeadPosition=GetCellTailPosition(EMPTY_VALUE);
	
	//��������� ��������� �������
	if(uiHeadRowIndex!=uiTailRowIndex){
		//���� ������ ������ ��������� ������ ������
		FillTablePositions(uiDocumentIndex, uiTableIndex, uiTailRowIndex);
	}

	//���������� ������� ���������� ����� ��������� ������ ������
	pOutTablePositions->m_uiTailPosition=GetCellTailPosition(m_TablesOffsets[m_uiLastFilledTableIndex].m_uiColumnCount-1);
}

void CIndexStorageTables::FillTablesToTextBlock(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
		Containers::CInterval* pInterval, unsigned int uiGroupID)
{
	if(ISNULL(pTextBlock)) return;
	if(ISNULL(pInterval)) return;
	if(ISNULL(m_pTablesInfoStorage)) return;

	//!!!����������� ������ �� ������� �������� ������ ������� � ������ ������������� � ���������� ���������

	try{

	ITextBlockCut* pTextBlockCut=NULL;
	
	//�������� ������ ���������
	unsigned int uiDocumentIndex=pTextBlock->GetTextFeature()->GetTextNumber();

	//��������� �� ������ ���������� �������
	if(pInterval->m_uiHeadPos==EMPTY_VALUE){
		return;
	}

	//ToConsole(L"uiDocumentIndex", uiDocumentIndex);
	//ToConsole(L"TableIndex", pInterval->m_uiHeadPos);
	//ToConsole(L"ColumnCount", (unsigned int)m_CellPositions.size()-1);

	//int a=0;
	//if(uiDocumentIndex==30921){
	//	a=30921;
	//}

	//� ������ ������� ����� �������
	//����� ������� ������ ��� ����������� 2-�� ������
	unsigned int uiHeadRowIndex=0;
	FillTablePositions(uiDocumentIndex, pInterval->m_uiHeadPos, uiHeadRowIndex);
	wstring wsIndexStorageName(L"HEADERS");
	for(unsigned int i=0; i<m_TablesOffsets[m_uiLastFilledTableIndex].m_uiColumnCount; i++){
		
		Containers::CInterval Interval(EMPTY_VALUE, EMPTY_VALUE, pInterval->m_uiWeight);
		Interval.m_uiHeadPos=m_CellPositions[i];
		if(Interval.m_uiHeadPos!=EMPTY_VALUE){
			//���� ������ �� ������ ���������� ������� ���������� �����
			Interval.m_uiTailPos=GetCellTailPosition(i+1);
			//��������� ������
			pTextBlockCut=GetTextsBinaryStorage()->FillTextBlock(pTextBlock, &Interval, &wsIndexStorageName);	
		}else{
			//��� ������ ����� ���������� �� ����������
			pTextBlockCut=pTextBlock->AddBlockCut();
		}

		//������������� ��� �����
		pTextBlockCut->SetRelevance(pInterval->m_uiWeight);
		//������������� ��� ���������� ��������� � ������� ������ ����
		pTextBlockCut->SetIndexTypeName(wsIndexStorageName.c_str());
		pTextBlockCut->SetNumber(uiGroupID);
		pTextBlockCut->SetType(SS::Core::Types::IndexationSearch::tctHeader);
		pTextBlockCut->SetLevel(2);
	}
	
	if(pInterval->m_uiTailPos!=0){
		//���� ������ ���������� �� �������� ������
		//�������� ������� ������
		FillTablePositions(uiDocumentIndex, pInterval->m_uiHeadPos, pInterval->m_uiTailPos);
		wsIndexStorageName.assign(GetIndexStorageName());
		for(unsigned int i=0; i<m_TablesOffsets[m_uiLastFilledTableIndex].m_uiColumnCount; i++){
			
			Containers::CInterval Interval(EMPTY_VALUE, EMPTY_VALUE, pInterval->m_uiWeight);
			Interval.m_uiHeadPos=m_CellPositions[i];
			if(Interval.m_uiHeadPos!=EMPTY_VALUE){
				//���� ������ �� ������ ���������� ������� ���������� �����
				Interval.m_uiTailPos=GetCellTailPosition(i+1);
				//��������� ������
				pTextBlockCut=GetTextsBinaryStorage()->FillTextBlock(pTextBlock, &Interval, &wsIndexStorageName);	
			}else{
				//��� ������ ����� ���������� �� ����������
				pTextBlockCut=pTextBlock->AddBlockCut();
			}

			//������������� ��� �����
			pTextBlockCut->SetRelevance(pInterval->m_uiWeight);
			//������������� ��� ���������� ��������� � ������� ������ ����
			pTextBlockCut->SetIndexTypeName(wsIndexStorageName.c_str());
			pTextBlockCut->SetNumber(uiGroupID);
			pTextBlockCut->SetType(SS::Core::Types::IndexationSearch::tctTable);
		}
	}

	}
	catch(...)
	{
		ERR_TO_CONSOLE(erTryCatch, L"CIndexStorageTables::FillTablesToTextBlock failed!!!");
		throw;
	}

}

void CIndexStorageTables::FillTablesStructure(unsigned int uiTextIndex, std::wstring* pwsTablesStructure)
{
	if(ISNULL(m_pTablesInfoStorage)) return;
	if(ISNULL(pwsTablesStructure)) return;

	pwsTablesStructure->append(L"//---------Bof-Tables-Structure\n");
	wchar_t buf[1000];
	swprintf(buf, L"Document: %u\n", uiTextIndex);
	pwsTablesStructure->append(buf);
	
	//��������� � ������ ������ ��������� ������ ������
	unsigned int uiBufferSize;
	m_pTablesInfoStorage->MoveToAndGetDataSize(uiTextIndex, &uiBufferSize);
	
	//����������� ����� ������ �������� �� �������
	unsigned int uiTablesOffsetsSize=0;
	m_pTablesInfoStorage->ReadDataChunk((unsigned char*)&uiTablesOffsetsSize, sizeof(unsigned int));
	m_TablesOffsets.resize(uiTablesOffsetsSize/sizeof(Containers::STableInfo));
	m_pTablesInfoStorage->ReadDataChunk((unsigned char*)&m_TablesOffsets.front(), uiTablesOffsetsSize);

	pwsTablesStructure->append(L"//------Bof-Tables-Offsets\n");
	wstring wsValue;

	for(unsigned int i=0; i<m_TablesOffsets.size()-1; i++){
		m_TablesOffsets[i].ToString(wsValue);
		pwsTablesStructure->append(L"\t");
		pwsTablesStructure->append(wsValue.c_str());
		swprintf(buf, L" RowsCount:%u", m_TablesOffsets[i].GetRowsCount(m_TablesOffsets[i+1].m_uiCellsOffset));
		pwsTablesStructure->append(buf);
		pwsTablesStructure->append(L"\n");
	}	
	pwsTablesStructure->append(L"//------Eof-Tables-Offsets\n");


	//������ ������� �����
	uiBufferSize-=sizeof(unsigned int)+uiTablesOffsetsSize;
	m_CellPositions.resize(uiBufferSize/sizeof(unsigned int));

	//ToConsole(L"uiBufferSize", uiBufferSize);

	//������ ������� ����� �������
	m_pTablesInfoStorage->ReadDataChunk((unsigned char*)&m_CellPositions.front(), uiBufferSize);
	
	//������� �������� �� ������ ������
	unsigned int uiCurentRow=0;
	for(unsigned int i=0; i<m_TablesOffsets.size()-1; i++){
		swprintf(buf, L"//-------Table: %u\n", i);
		pwsTablesStructure->append(buf);
		//���������� ���������� ����� �������
		unsigned int uiRowsCount=m_TablesOffsets[i].GetRowsCount(m_TablesOffsets[i+1].m_uiCellsOffset);
		//ToConsole(L"uiRowsCount", uiRowsCount);
		for(unsigned int r=0; r<uiRowsCount; r++){
			//��������� ������
			FillTablePositions(uiTextIndex, i, r);
			swprintf(buf, L"R_%u:---------\n\t", r);
			pwsTablesStructure->append(buf);
			int a=0;
			for(unsigned int c=0; c<m_TablesOffsets[i].m_uiColumnCount; c++){
				//��������� ���������� ������

				//���������� ������� ������ � ����� ������
				if(m_CellPositions[c]!=EMPTY_VALUE){
					swprintf(buf, L"<%u-%u> ", m_CellPositions[c], GetCellTailPosition(c));
					pwsTablesStructure->append(buf);
				}else{
					pwsTablesStructure->append(L"<empty> ");
				}

				if(a==5){
					a=0; pwsTablesStructure->append(L"\n\t");
				}else a++;

			}
			pwsTablesStructure->append(L"\n");
		}
		pwsTablesStructure->append(L"//-------\n");
	}
	pwsTablesStructure->append(L"//---------Eof-Tables-Structure\n");
}

//--------------------------------------------------------------------//

}
}
}
}
}