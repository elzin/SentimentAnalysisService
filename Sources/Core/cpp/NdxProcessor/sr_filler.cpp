#include "StdAfx.h"
#include ".\sr_filler.h"
#include ".\coordinate_convertor.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{

using namespace SS::Core::NdxSE::NdxProcessor::Storages; 
using namespace SS::Interface::Core::CommonContainers; 
using namespace SS::Interface::Core::NdxSE::NdxDataStorage; 
using namespace SS::Interface::Core::NdxSE; 
using namespace SS::Core::NdxSE::NdxProcessor;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;

//--------------------------------------------------------------------//

CSearchResultFiller::CSearchResultFiller(
		Containers::CFindResultCollection* pSearchResultCollection, 
		CIndexStorage* pIndexStorage, 
		TResultsTextsNumbers* pResultsTextsNumbers, unsigned int uiResultsIntervalRange,
		CNdxSearchSettings::SSearchSettings::EStorageUsingMode StorageUsingMode) :
	m_pCurrSearchResultCollection(pSearchResultCollection),
	m_pIndexStorage(pIndexStorage), 
	m_pResultsTextsNumbers(pResultsTextsNumbers), 
	m_uiResultsIntervalRange(uiResultsIntervalRange), 
	m_uiCurrTextBlockCutNumber(0), 
	m_StorageUsingMode(StorageUsingMode),
	m_uiCurrTextNumber(0)
{
}

CSearchResultFiller::~CSearchResultFiller(void)
{
}

void CSearchResultFiller::AddCoordinate(unsigned int* puiBuffer, unsigned int uiBufferSize, float fRelevance)
{
	if(ISNULL(puiBuffer)) return;
	if(ISNULL(uiBufferSize)) return;
	if(ISNULL(m_pIndexStorage)) return;
	if(fRelevance==0) return;

	CIndexStorage::TCoordinateLevelInfo* pLevelCollection=m_pIndexStorage->GetCoordinateLevelCollection();

	if(uiBufferSize!=pLevelCollection->size()){ 
		TO_CONSOLE(L"Buffer size and Levels number not equal");	
		ToConsole(L"Buffer size", uiBufferSize);	
		ToConsole(L"Levels number", (unsigned int)pLevelCollection->size());	
		return;
	}
	
	m_uiCurrTextNumber=0;
	unsigned int* CoordBuffer[5]={NULL, &m_uiCurrTextNumber, NULL, NULL, NULL};

	//���� ���������� ���������� �� �������
	unsigned int uiBufferCurrPos=0;
	CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=pLevelCollection->begin();
	SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);
	do{
		pLevelInfo=(*itLevelStorage);

		if(ISNULL(pLevelInfo)) break;

		CCoordinateConvertor::InsertToCoordinate(
			//����������
			CoordBuffer[pLevelInfo->m_IndexCoordinateType], 
			//�������� �� ������	
			*(puiBuffer+uiBufferCurrPos),
			//��������� ��� ������ ������ ����������
			pLevelInfo->m_ucStartBit,
			//���������� ��� �� �������
			pLevelInfo->m_ucBitPerLevel);
	}while(++uiBufferCurrPos<uiBufferSize && ++itLevelStorage!=pLevelCollection->end());

	//������� ��������� ������
	m_pCurrSearchResultCollection->AddFindResult(m_uiCurrTextNumber, (unsigned int)fRelevance);
}

void CSearchResultFiller::StartAddCoordinate(unsigned int* puiBuffer, unsigned int uiBufferSize)
{
	if(ISNULL(puiBuffer)) return;
	if(ISNULL(uiBufferSize)) return;
	if(ISNULL(m_pIndexStorage)) return;

	CIndexStorage::TCoordinateLevelInfo* pLevelCollection=m_pIndexStorage->GetCoordinateLevelCollection();

	if(uiBufferSize!=pLevelCollection->size()){ 
		TO_CONSOLE(L"Buffer size and Levels number not equal");	
		ToConsole(L"Buffer size", uiBufferSize);	
		ToConsole(L"Levels number", (unsigned int)pLevelCollection->size());	
		return;
	}
	
	m_uiCurrTextNumber=0;
	unsigned int* CoordBuffer[5]={NULL, &m_uiCurrTextNumber, NULL, NULL, NULL};

	//���� ���������� ���������� �� �������
	unsigned int uiBufferCurrPos=0;
	CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=pLevelCollection->begin();
	SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);
	do{
		pLevelInfo=(*itLevelStorage);

		if(ISNULL(pLevelInfo)) break;

		CCoordinateConvertor::InsertToCoordinate(
			//����������
			CoordBuffer[pLevelInfo->m_IndexCoordinateType], 
			//�������� �� ������	
			*(puiBuffer+uiBufferCurrPos),
			//��������� ��� ������ ������ ����������
			pLevelInfo->m_ucStartBit,
			//���������� ��� �� �������
			pLevelInfo->m_ucBitPerLevel);
	}while(++uiBufferCurrPos<uiBufferSize && ++itLevelStorage!=pLevelCollection->end());
}

void CSearchResultFiller::AddCoordinate(unsigned int uiLastValue, float fRelevance)
{
	if(fRelevance==0) return;
	
	CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=(--(m_pIndexStorage->GetCoordinateLevelCollection()->end()));
	SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);
	
	CCoordinateConvertor::InsertToCoordinate(
		//����������
		&m_uiCurrTextNumber, 
		//�������� �� ������	
		uiLastValue,
		//��������� ��� ������ ������ ����������
		pLevelInfo->m_ucStartBit,
		//���������� ��� �� �������
		pLevelInfo->m_ucBitPerLevel);
	

	//ToConsole(L"TextNumber", m_uiCurrTextNumber);

	//������� ��������� ������
	m_pCurrSearchResultCollection->AddFindResult(m_uiCurrTextNumber, (unsigned int)fRelevance);
	//����� �� �����������, �.�. ��� ���������
}

bool CSearchResultFiller::AddCoordinate(unsigned int uiLastValue, float fRelevance, TIntervalCollection* pIntervalCollection)
{
	if(fRelevance==0) return true;
	
	CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=(--(m_pIndexStorage->GetCoordinateLevelCollection()->end()));
	SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);
	
	CCoordinateConvertor::InsertToCoordinate(
		//����������
		&m_uiCurrTextNumber, 
		//�������� �� ������	
		uiLastValue,
		//��������� ��� ������ ������ ����������
		pLevelInfo->m_ucStartBit,
		//���������� ��� �� �������
		pLevelInfo->m_ucBitPerLevel);
	
	//ToConsole(L"TextNumber", m_uiCurrTextNumber);
	
	//������� ��������� ������
	Containers::CFindResult* pFindResult=
		m_pCurrSearchResultCollection->AddFindResult(m_uiCurrTextNumber, (unsigned int)fRelevance);

	if(!pFindResult) return true;
	if(!pIntervalCollection) return true;
	if(pIntervalCollection->empty()) return true;


	//int a=0;
	//if(m_uiCurrTextNumber==17383){
	//	a=17383;
	//}

	wstring wszStorageName;
	if(m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumSingleStorage){
		
		if(!wcscmp(m_pIndexStorage->GetIndexStorageName(), L"TEXT")){
			for(unsigned int i=0; i<pIntervalCollection->size(); i++){
				//�������� ������������� ��������� �� ��������� ��������
				//(*pIntervalCollection)[i]->View();
				(*pIntervalCollection)[i]->Expand(m_uiResultsIntervalRange);
			}
		}

		//��������� ������� ����� � ����� ���������		
		wszStorageName.assign(m_pIndexStorage->GetIndexStorageName());
	}else if(m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage){

		for(unsigned int i=0; i<pIntervalCollection->size(); i++){
			//�������� ������������� ��������� �� ��������� ��������
			//(*pIntervalCollection)[i]->View();
			(*pIntervalCollection)[i]->Expand(m_uiResultsIntervalRange);
		}

		//��������� ������� ����� � ������� � ����������
		wszStorageName.assign(L"HEADERS|TEXT");
	}else if(m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage){
		//��������� ������� ����� � ������� � ����������
		wszStorageName.assign(L"HEADERS|TABLES");
	}

	//��������� � ��������� ��������, � ������������ � ������� ��������� ����������
	pFindResult->MoveIntervalCollection(wszStorageName.c_str(), pIntervalCollection);
	
	m_uiCurrTextBlockCutNumber+=(unsigned int)pIntervalCollection->size();

	//��������� ����� ������
	if(m_pResultsTextsNumbers){
		if(m_pResultsTextsNumbers->empty()){
			m_pResultsTextsNumbers->push_back(m_uiCurrTextNumber);
		}else{
			if(m_pResultsTextsNumbers->back()<m_uiCurrTextNumber){
				m_pResultsTextsNumbers->push_back(m_uiCurrTextNumber);
			}
		}
	}
	
	return /*(m_uiCurrTextBlockCutNumber>50000)?false:*/true; 
}

bool CSearchResultFiller::AddCoordinate(unsigned int uiLastValue, float fRelevance, CFindResult::TBlockHIDCollection* pBlockHIDCollection)
{
	if(fRelevance==0) return true;
	
	CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=(--(m_pIndexStorage->GetCoordinateLevelCollection()->end()));
	SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);
	
	CCoordinateConvertor::InsertToCoordinate(
		//����������
		&m_uiCurrTextNumber, 
		//�������� �� ������	
		uiLastValue,
		//��������� ��� ������ ������ ����������
		pLevelInfo->m_ucStartBit,
		//���������� ��� �� �������
		pLevelInfo->m_ucBitPerLevel);
	
	//ToConsole(L"TextNumber", m_uiCurrTextNumber);
	
	//������� ��������� ������
	Containers::CFindResult* pFindResult=
		m_pCurrSearchResultCollection->AddFindResult(m_uiCurrTextNumber, (unsigned int)fRelevance);

	if(!pFindResult) return true;
	if(!pBlockHIDCollection) return true;
	if(pBlockHIDCollection->empty()) return true;

	//��������� � ��������� ������� �������������� ����������
	pFindResult->MoveBlockHIDCollection(pBlockHIDCollection);
	
	//��������� ����� ������
	if(m_pResultsTextsNumbers){
		if(m_pResultsTextsNumbers->empty()){
			m_pResultsTextsNumbers->push_back(m_uiCurrTextNumber);
		}else{
			if(m_pResultsTextsNumbers->back()<m_uiCurrTextNumber){
				m_pResultsTextsNumbers->push_back(m_uiCurrTextNumber);
			}
		}
	}
	
	return true; 
}

void CSearchResultFiller::ViewSearchResult(ISearchResult* pSearchResult, set<unsigned int>* pQueryIndexes)
{
	if(ISNULL(pSearchResult)) return;
	
	ITextBlock* pTextBlock=NULL;
	ITextBlockCut* pTextBlockCut=NULL;
	IIndexAndPosition* pIndexAndPosition=NULL;

	wstring szValue;
	wchar_t buf[100];

	ToConsole(L"//-----------------SearchResult");
	pTextBlock=pSearchResult->GetFirstTextBlock();
	while(pTextBlock){
		szValue.clear();
		szValue.append(L"//----------TextBlock\n");
		wsprintf(buf, L"Text Number:%u\n", pTextBlock->GetTextFeature()->GetTextNumber());
		szValue.append(buf);
		wsprintf(buf, L"Text Relevance:%u\n", pTextBlock->GetRelevance());
		szValue.append(buf);
		ToConsole(szValue.c_str());
		szValue.clear();

		pTextBlockCut=pTextBlock->GetFirstBlockCut();
		while(pTextBlockCut){
			szValue.append(L"  //----------TextBlockCut: ");
			if(pTextBlockCut->GetIndexTypeName())
				szValue.append(pTextBlockCut->GetIndexTypeName());
			if(pTextBlockCut->GetType()==SS::Core::Types::IndexationSearch::tctHeader){
				wsprintf(buf, L" GroupID: %u HeaderLevel: %u\n", pTextBlockCut->GetNumber(), pTextBlockCut->GetLevel());
				szValue.append(buf);
			}else{
				wsprintf(buf, L" GroupID: %u\n", pTextBlockCut->GetNumber());
				szValue.append(buf);
			}
			szValue.append(L"    ");
			//wsprintf(buf, L" TextBlockCut Relevance:%u\n", pTextBlockCut->GetRelevance());
			//szValue.append(buf);

			pIndexAndPosition=pTextBlockCut->GetFirstIndexAndPosition();
			int i=0;
			while(pIndexAndPosition){
				
				unsigned int uiDictionaryIndex=pIndexAndPosition->GetServiceIndex()->GetViewIndex()->m_DictionaryIndex;
				if(pQueryIndexes && pQueryIndexes->find(uiDictionaryIndex)!=pQueryIndexes->end()){
					wsprintf(buf, L"*_%u_*", uiDictionaryIndex);
				}else{
					wsprintf(buf, L" %u ", uiDictionaryIndex);
				}

				szValue.append(buf);
				
				if(i==10){
					szValue.append(L"\n    ");
					i=0;
				}

				pIndexAndPosition=pTextBlockCut->GetNextIndexAndPosition();
				i++;
			}
			szValue.append(L"\n  //----------Eof-TextBlockCut\n");
			pTextBlockCut=pTextBlock->GetNextBlockCut();
			ToConsole(szValue.c_str());
			szValue.clear();
		}
		szValue.append(L"//----------Eof-TextBlock\n");
		ToConsole(szValue.c_str());
		pTextBlock=pSearchResult->GetNextTextBlock();
	}
	ToConsole(L"//-----------------Eof-SearchResult");
}

void CSearchResultFiller::ViewTextBlockCut(ITextBlockCut* pTextBlockCut, bool bViewWords, bool bViewIndexes)
{
	if(ISNULL(pTextBlockCut)) return;
	
	IIndexAndPosition* pIndexAndPosition=NULL;
	wstring szValue;
	wchar_t buf[100];

	szValue.append(L"//----------Bof-TextBlockCut: ");

	if(pTextBlockCut->GetIndexTypeName())
		szValue.append(pTextBlockCut->GetIndexTypeName());
	if(pTextBlockCut->GetType()==SS::Core::Types::IndexationSearch::tctHeader){
		wsprintf(buf, L" GroupID: %u HeaderLevel: %u\n", pTextBlockCut->GetNumber(), pTextBlockCut->GetLevel());
		szValue.append(buf);
	}else{
		wsprintf(buf, L" GroupID: %u\n", pTextBlockCut->GetNumber());
		szValue.append(buf);
	}

	//wsprintf(buf, L" TextBlockCut Relevance:%u\n", pTextBlockCut->GetRelevance());
	//szValue.append(buf);

	pIndexAndPosition=pTextBlockCut->GetFirstIndexAndPosition();
	while(pIndexAndPosition){
		szValue.append(L"//----------Bof-IndPos:\n");
		//���������� �������
		wsprintf(buf, L"\tPos: %u\n", pIndexAndPosition->GetPosition());
		szValue.append(buf);

		if(bViewWords && pIndexAndPosition->GetWord()){
			//���������� �����
			wsprintf(buf, L"\tWord: \"%s\"\n", pIndexAndPosition->GetWord());
			szValue.append(buf);
		}

		if(bViewIndexes){
			//���������� �������
			unsigned int uiDictionaryIndex=pIndexAndPosition->GetServiceIndex()->GetViewIndex()->m_DictionaryIndex;
			wsprintf(buf, L"\tService: %u\n", uiDictionaryIndex);
			szValue.append(buf);

			szValue.append(L"\tIndex: \n");
			unsigned int uiIndex=pIndexAndPosition->GetIndexationIndex()->GetFirstIndex();
			if(ISNULL(uiIndex)) return;
			while(uiIndex){
				wsprintf(buf, L"\t\t%u\n", uiIndex);
				//�������� ��������� ������ �� ������ �������
				uiIndex=pIndexAndPosition->GetIndexationIndex()->GetNextIndex();
				szValue.append(buf);
			}
		}		

		szValue.append(L"//----------Eof-IndPos\n");
		pIndexAndPosition=pTextBlockCut->GetNextIndexAndPosition();
	}
	szValue.append(L"//----------Eof-TextBlockCut\n");
	ToConsole(szValue.c_str());

}

//--------------------------------------------------------------------//

}
}
}
}
}