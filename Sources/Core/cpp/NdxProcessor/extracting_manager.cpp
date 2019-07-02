#include "StdAfx.h"

#include ".\extracting_manager.h"
#include ".\console.h"
#include "..\ASCInterface\defines.h"

#include "tchar.h"


USES_LOAD_MANAGER;

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

using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Core::Types::IndexationSearch;
using namespace SS::Interface::Core::NdxSE;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;

//--------------------------------------------------------------------//

CExtractingManager::CExtractingManager(void) :
	m_pSearchFactory(NULL), m_pEvaluator(NULL), 
	m_pCurrentPrmQueryResult(NULL), m_pISContainer(NULL), 
	m_pSettingsServer(NULL), m_pTextInfoManager(NULL), m_pStorageManager(NULL)
{
}

CExtractingManager::~CExtractingManager(void)
{
	Reset();
}

void CExtractingManager::Init(SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* pStorageManager,
							  SS::Interface::Core::CommonServices::ISettingsServer* pSettingsServer,
							  Extracting::CTextInfoManager* pTextInfoManager)
{
	if(ISNULL(pStorageManager)) SS_THROW(L"pStorageManager is NULL");
	if(ISNULL(pSettingsServer)) SS_THROW(L"pSettingsServer is NULL");

	m_pStorageManager=pStorageManager;
	m_pSettingsServer=pSettingsServer;
	m_pTextInfoManager = pTextInfoManager;
}

void CExtractingManager::FillSearchResult(ITextBlock* pTextBlock, CInterval* pInterval, 
										  wstring* pwsIndexStorageName, unsigned int uiResultGroupID)
{
	if(ISNULL(m_pSearchFactory)) return;
	if(ISNULL(pTextBlock)) return;
	if(ISNULL(pInterval)) return;
	if(ISNULL(pwsIndexStorageName)) return;

	if(pwsIndexStorageName->find(L"HEADERS")!=EMPTY_VALUE){
		//��������� ���� � ���������� ����� ����������
		Storages::CIndexStorageHeaders* pIndexStorageHeaders=
			static_cast<Storages::CIndexStorageHeaders*>(m_pStorageManager->GetIndexStorage(L"HEADERS"));
		
		//��������� ��������� �� ��������� ����������
		pIndexStorageHeaders->FillHeadersToTextBlock(pTextBlock, 
			static_cast<CIntervalAndHeader*>(pInterval), uiResultGroupID);
	}

	if(pwsIndexStorageName->find(L"TEXT")!=EMPTY_VALUE){
		//��������� ���� � ���������� ����� ������	
		wstring wsIndexStorageName(L"TEXT");
		//��������� ���� ������ �� ���������
		ITextBlockCut* pTextBlockCut=m_pStorageManager->GetIndexStorage(wsIndexStorageName.c_str())->
			GetTextsBinaryStorage()->FillTextBlock(pTextBlock, pInterval, &wsIndexStorageName);
		
		if(ISNULL(pTextBlockCut)) return;
		
		//������������� ���������� ����� ������ � ���
		pTextBlockCut->SetNumber(uiResultGroupID);
		pTextBlockCut->SetType(SS::Core::Types::IndexationSearch::tctText);
	}
	
	if(pwsIndexStorageName->find(L"TABLES")!=EMPTY_VALUE){
		//��������� ���� � ���������� ����� ������
		Storages::CIndexStorageTables* pIndexStorageTables=
			static_cast<Storages::CIndexStorageTables*>(m_pStorageManager->GetIndexStorage(L"TABLES"));
		
		//��������� ������� �� ��������� ������
		pIndexStorageTables->FillTablesToTextBlock(pTextBlock, pInterval, uiResultGroupID);
	}
}

HRESULT CExtractingManager::StartFindSession(SS::Interface::Core::IISContainerUM* pISContainer)
{
	if(ISNULL(pISContainer)) SS_THROW(L"pISContainer is NULL!!!");
	
	SS_TRY
	m_pISContainer=pISContainer;

	m_pISContainer->Clear();

	//������� ���������� ����������
	m_SessionFindResults.Clear();
	m_SessionFindResults.ResetAddingSession();

	return S_OK;

	SS_CATCH(L"");
	return E_FAIL;
}

/*
	CFindResultsByRelevanceCollection - ��������� CFindResult
		typedef list<CFindResult*> TFindResultsList;
		typedef map<unsigned int,  TFindResultsList*, greater<int> > TFindResultsByRelevanceCollection;

	CFindResult
		///��������� ��������� �������� �� ����������, � ������� ��� ���� �������
		typedef map<wstring, TIntervalCollection*> TIntervalByStorageCollection;
		///��������� ��������������� ����������
		typedef vector<unsigned int> THIDCollection;
		///��������� ��������� ��������������� ���������� �� ��������
		typedef map<unsigned int, THIDCollection*> TBlockHIDCollection;

	TIntervalCollection
		///��������� ����������
		typedef vector<CInterval*> TIntervalCollection; 

	CFindResultCollection
		///��������� ����������� ���������� ������
		typedef map<unsigned int, CFindResult*> TFindResultsCollection;

	TTextBlocksStorageCollection
		typedef map<wstring, SS::Interface::Core::CommonContainers::ITextBlock*> TTextBlocksStorageCollection;

	m_TextBlocksStorageCollection - ����� (�� ��������� ��������) ��������� ��������� ������

	������ uiOutputSearchResultsCount - ����� ��������� ����������� ������
	������ uiBlockCutsInTextCount - ����� ��������� ������
*/
HRESULT CExtractingManager::EndFindSession(void)
{
	if(ISNULL(m_pISContainer)) SS_THROW(L"m_pISContainer is NULL!!!");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL");
	if(ISNULL(m_pSettingsServer)) SS_THROW(L"m_pSettingsServer is NULL");
	
	SS_TRY

		m_pISContainer->Clear();
	
		//�������� ���������� ����������� ������� ����� ������
		unsigned int uiOutputSearchResultsCount=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::MaxOutputTextBlockCount");
		unsigned int uiBlockCutsInTextCount=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::MaxBlockCutsInTextCount");
		unsigned int uiGoodIntervalLimitWeight=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::VipOutputBlockCutMinWeight");
		unsigned int uiOutputBlockCutsCount=uiOutputSearchResultsCount*uiBlockCutsInTextCount;

		ITextBlock* pTextBlock=NULL;
		CFindResult::TIntervalByStorageCollection* pIntervalCollection=NULL;
		CFindResult* pFindResult=NULL;
		CFindResultsByRelevanceCollection* pFindResultsByRelevanceCollection=m_SessionFindResults.GetFindResultsByRelevanceCollection();
		if(ISNULL(pFindResultsByRelevanceCollection)) SS_THROW(L"pFindResultsByRelevanceCollection is NULL");

		unsigned int uiInc = 0;
		//	�������� �� �����������
		if(pFindResultsByRelevanceCollection->MoveFirstFindResult())
		do
		{
			ClearTextBlocksStorageCollection();
			//�������� ���� ������
			pFindResult=pFindResultsByRelevanceCollection->GetCurrentFindResult();
			
			//ToConsole(L"TextIndex", pFindResult->GetTextIndex());
			//ToConsole(L"Relevance", pFindResult->GetRelevance());

			//������� ��������� ���������� ��������� ����������
			pIntervalCollection=pFindResult->GetIntervalCollection();
			if(!pIntervalCollection) continue;
			unsigned int uiBlockCutInc = 0;

			//�������/�������� ��������� ������
			wstring wsTemp(L"TEXT");	//	ig ������ ����������� ��������� ���� � �� ������ � ����, ���������� �� ���� ���������� ���������??
			pTextBlock=GetTextBlock(wsTemp, pFindResult);
			if(ISNULL(pTextBlock)) return E_FAIL;

			//	������ �� ����� ��������� ����������
			for(CFindResult::TIntervalByStorageCollection::iterator itInt=pIntervalCollection->begin(); itInt!=pIntervalCollection->end(); itInt++)
			{
				//	�������� ���� ���������
				wstring wsIndexStorageName=itInt->first;
				//	����: � ������� �� �� ������ �������� ��� ���
				bool is_text = (wsIndexStorageName.find(L"TEXT") != wstring::npos);
				//	������ �� ��������� �������� ����
				for(unsigned int i=0; i<itInt->second->size(); i++)
				{
					//��������� ���� ������ �� ���������
					FillSearchResult(pTextBlock, ((*itInt->second)[i]), &wsIndexStorageName, uiInc);

					//	��������� �������� ����������
					++uiInc;
					//	�������� �� ���������� �������� ����������
					if(uiInc >= uiOutputBlockCutsCount) break;
					//	��������� �������� ������ ������
					++uiBlockCutInc;
					//	���� ������������ �� �����, ���������� �������� �� ����������
					if (!is_text) continue;
					//	��������� ������, � ������� ����� ����������. ���� �������� � ������� �����, ������ ��� ���� � ��� ���� ������
					register unsigned int	limit = (((*itInt->second)[i])->m_uiWeight  >=  uiGoodIntervalLimitWeight) 
						? (uiBlockCutsInTextCount * 2) : (uiBlockCutsInTextCount);
					//	�������� �� ���������� �������
					if(uiBlockCutInc >= limit) break;
				}
			}
		}while(pFindResultsByRelevanceCollection->MoveNextFindResult() && uiInc < uiOutputBlockCutsCount);
		

		//������� ���������� ����������
		m_SessionFindResults.Clear();
		

	//CSearchResultFiller::ViewSearchResult(m_pISContainer->GetSearchResult(L"TEXT"));
	//ToConsole(L"Total Results Count", uiInc);

	return S_OK;

	SS_CATCH(L"");
	return E_FAIL;
}

HRESULT CExtractingManager::EndFindByFieldSession(void)
{
	if(ISNULL(m_pISContainer)) SS_THROW(L"m_pISContainer is NULL!!!");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL");
	
	SS_TRY

		m_pISContainer->Clear();
	
		ITextBlock* pTextBlock=NULL;
		CFindResult* pFindResult=NULL;
		CFindResultsByRelevanceCollection* pFindResultsByRelevanceCollection=m_SessionFindResults.GetFindResultsByRelevanceCollection();

		if(ISNULL(pFindResultsByRelevanceCollection)) SS_THROW(L"pFindResultsByRelevanceCollection is NULL");

		if(pFindResultsByRelevanceCollection->MoveFirstFindResult())
		do{

			ClearTextBlocksStorageCollection();
			//�������� ���� ������
			pFindResult=pFindResultsByRelevanceCollection->GetCurrentFindResult();
			
			//ToConsole(L"TextIndex", pFindResult->GetTextIndex());
			//ToConsole(L"Relevance", pFindResult->GetRelevance());

			//�������/�������� ��������� ������
			wstring wsTemp(L"TEXT");
			pTextBlock=GetTextBlock(wsTemp, pFindResult);
			if(ISNULL(pTextBlock)) return E_FAIL;

		}while(pFindResultsByRelevanceCollection->MoveNextFindResult());

		//������� ���������� ����������
		m_SessionFindResults.Clear();

	//CSearchResultFiller::ViewSearchResult(m_pISContainer->GetSearchResult(L"TEXT"));
	//ToConsole(L"Total Results Count", uiInc);

	return S_OK;

	SS_CATCH(L"");
	return E_FAIL;
}


SS::Interface::Core::CommonContainers::ITextBlock* CExtractingManager::GetTextBlock(wstring& wsIndexStorageName,
						 SS::Core::NdxSE::NdxProcessor::Containers::CFindResult* pFindResult)
{
/*
	ig 
	������ ��������� ���� �� ��������� ����� ���� ��� �� ���������� � m_TextBlocksStorageCollection
*/
	TTextBlocksStorageCollection::iterator it_current = m_TextBlocksStorageCollection.find(wsIndexStorageName);
	SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock = NULL;

	//���� ��� ����� ��������� �� �������������, �������� ��������� ����������� ������ ��� ���� � ������� TextBlock
	if(it_current == m_TextBlocksStorageCollection.end())
	{
		SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult = 
			m_pISContainer->GetSearchResult(wsIndexStorageName.c_str());

		pTextBlock = pSearchResult->AddTextBlock();
		if(!pTextBlock)
			SS_THROW(L"pSearchResult->AddTextBlock() return NULL");
		
		m_TextBlocksStorageCollection.insert(TTextBlocksStorageCollection::value_type(wsIndexStorageName, pTextBlock));

		//������������� �������������� ����� ������	

		pTextBlock->GetTextFeature()->SetTextNumber(pFindResult->GetTextIndex());
		m_pTextInfoManager->GetTextInfo(pFindResult->GetTextIndex(), pTextBlock->GetTextFeature());

		SS::Interface::Core::NdxSE::CNdxMetaField oNdxMetaField(
			L"FILENAME", SS::Interface::Core::DBMS::TYPE_WSTRING, SS::Interface::Core::DBMS::MOD_COMMON);
		m_pTextInfoManager->GetTextInfo(pFindResult->GetTextIndex(), &oNdxMetaField);
		
		std::wstring* pwsFilePath = (std::wstring*)oNdxMetaField.GetValue();
		std::wstring wsFileName = pwsFilePath->substr(pwsFilePath->find_last_of( L"\\", pwsFilePath->length())+1, pwsFilePath->length());

		pTextBlock->GetTextFeature()->SetTextName(wsFileName.c_str());
		pTextBlock->GetTextFeature()->SetTextPath(pwsFilePath->c_str());

		pTextBlock->SetRelevance(pFindResult->GetRelevance());
		pTextBlock->m_IndexProcessorMark = SS::Core::Types::IndexationSearch::ipLocal;
	}
	else
	{
		pTextBlock = it_current->second;
	};
	return pTextBlock;
}

void CExtractingManager::ClearTextBlocksStorageCollection()
{
	m_TextBlocksStorageCollection.clear();
};

HRESULT  CExtractingManager::Find(
	const wchar_t* wszIndexStorageName, 
	IParametrizedQuery* pPrmQueryResult, 
	TSearchParams* pSearchParams, 
	CNdxSearchSettings* pSearchSettings)
{
	if(ISNULL(m_pISContainer)) SS_THROW(L"m_pISContainer is NULL!!! StartFindSession was not called");
	if(ISNULL(pPrmQueryResult)) SS_THROW(L"pPrmQueryResult is NULL!!!");
	if(ISNULL(pSearchParams)) SS_THROW(L"pCommonSearchParams is NULL!!!");
	if(ISNULL(pSearchSettings)) SS_THROW(L"pSearchSettings is NULL!!!");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL!!!");
	if(ISNULL(m_pSettingsServer)) SS_THROW(L"m_pSettingsServer is NULL!!!");

	wstring wsIndexStorageName(wszIndexStorageName);

	//������������ ��������� �������� ����������� ������
	pSearchParams->m_uiMaxSearchResultsCount=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::MaxTotalIntervalsCount");
	pSearchSettings->m_ResultsSettings.m_uiIntervalExpandRange=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::IntervalExpandRange");
	pSearchSettings->m_ResultsSettings.m_uiIntervalInTextMaxCount=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::IntervalInTextMaxCount");
	pSearchSettings->m_ResultsSettings.m_uiIntervalJoinRange=m_pSettingsServer->GetUInt(L"NdxProcessor::Results::IntervalJoinRange");

	//������������ ����� ��������� ������
	pSearchSettings->m_SearchSettings.m_SearchMode=
		SS::Interface::Core::NdxSE::CNdxSearchSettings::SSearchSettings::esmBooleanSearch;
	pSearchSettings->m_SearchSettings.m_EvalRelevanceMode=
		SS::Interface::Core::NdxSE::CNdxSearchSettings::SSearchSettings::erAll;

	//��������� ��� ������ �� �������
	pSearchSettings->m_PatternSearchSettings.m_bCheckIndexSequence=m_pSettingsServer->GetBoolean(L"NdxProcessor::Pattern::CheckWordSequence")==0?false:true;
	pSearchSettings->m_PatternSearchSettings.m_uiIndexProximityLimitWeight=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::GoodProximityWeight");
	pSearchSettings->m_PatternSearchSettings.m_uiUnionLimitWordWeightPart=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::UnionLimitWordWeightPart");
	pSearchSettings->m_PatternSearchSettings.m_uiUnionSurplusWordsMaxCount=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::UnionSurplusWordsCount");
	pSearchSettings->m_PatternSearchSettings.m_uiUnionDistanceWeightKoef=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::UnionDistanceWeightKoef");
	pSearchSettings->m_PatternSearchSettings.m_uiUnionWordsWeightKoef=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::UnionWordsWeightKoef");
	pSearchSettings->m_PatternSearchSettings.m_uiUnionWeightKoef=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::UnionWeightKoef");
	pSearchSettings->m_PatternSearchSettings.m_uiGrandWordWeightLimit=m_pSettingsServer->GetUInt(L"NdxProcessor::Pattern::GrandWordWeightLimit");

	//��������� ��� ������ � ������ ����������
	pSearchSettings->m_SmartSearchSettings.m_fWordsNormKoef=(float)m_pSettingsServer->GetDouble(L"NdxProcessor::Smart::WordsNormKoef");
	pSearchSettings->m_SmartSearchSettings.m_fRarityWordLimit=(float)m_pSettingsServer->GetDouble(L"NdxProcessor::Smart::RarityWordsLimit");
	pSearchSettings->m_SmartSearchSettings.m_fRarityWordsQuorum=(float)m_pSettingsServer->GetDouble(L"NdxProcessor::Smart::RarityWordsQuorum");
	pSearchSettings->m_SmartSearchSettings.m_uiAnswerIntervalLimitLength=m_pSettingsServer->GetUInt(L"NdxProcessor::Smart::AnswerIntervalLimitLength");
	pSearchSettings->m_SmartSearchSettings.m_uiCommonIntervalLimitLength=m_pSettingsServer->GetInt(L"NdxProcessor::Smart::ResultIntervalLimitLength");
	pSearchSettings->m_SmartSearchSettings.m_fWordsLingvoWeightKoef=(float)m_pSettingsServer->GetDouble(L"NdxProcessor::Smart::WordsLingvoWeightKoef");

	///������ ���������, ���� ������������� �� ������ ����� ������, ���������� ��� ��� �� �����
	unsigned int uiForcedSearchMode=m_pSettingsServer->GetUInt(L"NdxProcessor::ForcedSearchMode");
	if(pPrmQueryResult->GetHasAnswers() || pSearchParams->m_bForceOrSearch) uiForcedSearchMode=7;
	switch(uiForcedSearchMode){
	case 1:
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumAll;
		break;
	case 2:
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage;
		break;
	case 3:
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage;
		break;
	case 4:
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
		wsIndexStorageName.assign(L"TEXT");
		break;
	case 5:
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
		wsIndexStorageName.assign(L"TABLES");
		break;
	case 6:
		//��������� ����� � ������ ���������� � �������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage;
		ComplexFind(wsIndexStorageName.c_str(), pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamIfExist); 

		//��������� ����� � �������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
		return ComplexFind(L"TEXT", pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways); 
		break;
	case 7:
		//��������� ����� � �������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
		pSearchSettings->m_SearchSettings.m_EvalRelevanceMode=
			SS::Interface::Core::NdxSE::CNdxSearchSettings::SSearchSettings::erWordProximityWithStatistic;
		return ComplexFind(L"TEXT", pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways); 
		break;
	default:
		break;
	}

	ToConsole(L"NdxProcessor::SearchMode", (unsigned int)pSearchSettings->m_SearchSettings.m_StorageUsingMode);

	if(pSearchSettings->m_SearchSettings.m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumAll){

		//��������� ����� � ������ ���������� � �������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage;
		ComplexFind(wsIndexStorageName.c_str(), pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamIfExist); 

		//��������� ����� � ������ ���������� � ��������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage;
		ComplexFind(wsIndexStorageName.c_str(), pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways); 

		//��������� ����� � �������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
		ComplexFind(L"TEXT", pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways); 

		//��������� ����� � ��������
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
		return ComplexFind(L"TABLES", pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways); 

	}else{
		return ComplexFind(wsIndexStorageName.c_str(), pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamIfExist); 
	}
}

HRESULT  CExtractingManager::ComplexFind(
	const wchar_t* wszIndexStorageName,
	IParametrizedQuery* pPrmQueryResult, 
	TSearchParams* pSearchParams,
	CNdxSearchSettings* pSearchSettings, 
	Containers::CFindResultCollection::EAddingMode ResultsAddingMode)
{
	if(ISNULL(m_pISContainer)) SS_THROW(L"m_pISContainer is NULL!!! StartFindSession was not called");
	if(ISNULL(pPrmQueryResult)) SS_THROW(L"pPrmQueryResult is NULL!!!");
	if(ISNULL(pSearchParams)) SS_THROW(L"pCommonSearchParams is NULL!!!");
	if(ISNULL(pSearchSettings)) SS_THROW(L"pSearchSettings is NULL!!!");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL!!!");

	//pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumSingleStorage;
	//pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage;
	//pSearchSettings->m_SearchSettings.m_StorageUsingMode=CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage;
	if(pSearchSettings->m_SearchSettings.m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumSingleStorage){
		ToConsole(L"CExtractingManager execute esumSingleStorage search");


		//��������� ������� ����� � ����� ���������		
		pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomNone;
		return FindByQuery(wszIndexStorageName, pPrmQueryResult, pSearchParams, pSearchSettings, ResultsAddingMode)?S_OK:S_FALSE; 

	}else if(pSearchSettings->m_SearchSettings.m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage){

		ToConsole(L"CExtractingManager execute esumHeadersAndTextStorage search");

		//��������� ����� � ��������� ���������� ����� �� ����������� � ��������� �������
		if(FindByQuery(L"HEADERS", pPrmQueryResult, pSearchParams, pSearchSettings, ResultsAddingMode)){
			if(!m_ResultsTextsNumbers.empty()){
				//���� ���� ���������� ������ �� ���������� ������������� ����� ������ � ���������
				pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomText;
				return FindByQuery(L"TEXT", pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways)?S_OK:S_FALSE; 
			}
		}
		return S_FALSE;

	}else if(pSearchSettings->m_SearchSettings.m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage){

		ToConsole(L"CExtractingManager execute esumHeadersAndTablesStorage search");

		//��������� ����� � ��������� ���������� ����� �� ����������� � ��������� �������
		if(FindByQuery(L"HEADERS", pPrmQueryResult, pSearchParams, pSearchSettings, ResultsAddingMode)){
			if(!m_ResultsTextsNumbers.empty()){
				//���� ���� ���������� ������ �� ���������� ������������� ����� ������ � ���������
				pSearchParams->m_SearchInObtainedMode=TSearchParams::esiomText;
				return FindByQuery(L"TABLES", pPrmQueryResult, pSearchParams, pSearchSettings, CFindResultCollection::eamAlways)?S_OK:S_FALSE; 
			}
		}
		return S_FALSE;
	}else{
		SS_THROW(L"Unknown StorageUsingMode!!! Fill CNdxSearchSettings");
	}
	return S_FALSE;
}

bool CExtractingManager::FindByQuery(
	const wchar_t* wszIndexStorageName,
	IParametrizedQuery* pPrmQueryResult,
	TSearchParams* pSearchParams,
	CNdxSearchSettings* pSearchSettings,
	Containers::CFindResultCollection::EAddingMode ResultsAddingMode)
{
	if(ISNULL(m_pISContainer)) SS_THROW(L"m_pISContainer is NULL!!! StartFindSession was not called");
	if(ISNULL(pPrmQueryResult)) SS_THROW(L"pPrmQueryResult is NULL!!!");
	if(ISNULL(pSearchParams)) SS_THROW(L"pCommonSearchParams is NULL!!!");
	if(ISNULL(pSearchSettings)) SS_THROW(L"pSearchSettings is NULL!!!");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL!!!");

	unsigned char ucStep=0;
	bool bCanSearchMore=false;
	
	try{
		ToConsole(L"CExtractingManager::Search");

		m_pStorageManager->Update();

		if(!m_pStorageManager->IsExtractingMode()){
			///���� ����� ���������� �� ��������� ������ �� ���������
			TO_CONSOLE(L"Extracting not set, stop indexation before!!!");
			SS_THROW(L"Extracting not set, stop indexation before!!!");
		}

		START_TICK(L"FullSearch");
		
		m_SessionFindResults.StartFindResultAdding(ResultsAddingMode);

		ucStep=0;
		m_pCurrentPrmQueryResult = pPrmQueryResult;
		
		ucStep=1;
		if(PrepareToFind(wszIndexStorageName, pSearchParams, pSearchSettings)){

			if(ISNULL(m_pEvaluator)) SS_THROW(L"m_pEvaluator empty!!!");

			//���������
			ucStep=2;
			START_TICK(L"FullCalculate");
			bCanSearchMore=m_pEvaluator->Calculate();
			STOP_TICK(L"FullCalculate");
			++ucStep;

			//ucStep=3;
			//m_pEvaluator->ViewResultsContainer();
			
		}		
		
		m_SessionFindResults.StopFindResultAdding();


		STOP_TICK(L"FullSearch");
		//VIEW_TICKS();
		ToConsole(L"Eof-CExtractingManager::Search");
		
		return !bCanSearchMore;
	}catch(...){
		
		Reset();

		STOP_TICK(L"FullSearch");
		VIEW_TICKS();

		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"m_pCurrentQueryResult");
			break;
		case 1:
			wcscpy(buf, L"Init");
			break;
		case 2:
			wcscpy(buf, L"Evaluator Calculate");
			break;
		case 3:
			wcscpy(buf, L"ViewResultsContainer");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		}

		ERR_TO_CONSOLE(erTryCatch, buf);
		SS_THROW(buf);
		return false;
	}
}

HRESULT CExtractingManager::Find(
	TNdxMetaFieldCollection* pNdxMetaFieldCollection,
	TSearchParams* pCommonSearchParams, 
	CNdxSearchSettings* pSearchSettings)
{

	if(ISNULL(m_pISContainer)) SS_THROW(L"m_pISContainer is NULL!!! StartFindSession was not called");
	if(ISNULL(pNdxMetaFieldCollection)) SS_THROW(L"pNdxMetaFieldCollection is NULL!!!");
	if(ISNULL(pCommonSearchParams)) SS_THROW(L"pCommonSearchParams is NULL!!!");
	if(ISNULL(pSearchSettings)) SS_THROW(L"pSearchSettings is NULL!!!");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL!!!");

	SS_TRY

		m_pStorageManager->Update();

		if(!m_pStorageManager->IsExtractingMode()){
			///���� ����� ���������� �� ��������� ������ �� ���������
			TO_CONSOLE(L"Extracting not set, stop indexation before!!!");
			SS_THROW(L"Extracting not set, stop indexation before!!!");
		}

		m_SessionFindResults.StartFindResultAdding(CFindResultCollection::eamIfExist);
		
		//��������� �����
		m_pStorageManager->GetTextsFieldsStorage()->
			GetTexts(pNdxMetaFieldCollection, &m_SessionFindResults, pCommonSearchParams);

		m_SessionFindResults.StopFindResultAdding();

		return S_OK;

	SS_CATCH(L"");
	return E_FAIL;
}

bool CExtractingManager::FindNext(SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult)
{
	unsigned char ucStep=0;

	if(ISNULL(pSearchResult)) SS_THROW(L"pSearchResult empty!!!");
	if(ISNULL(m_pSearchFactory)) SS_THROW(L"m_pSearchFactory empty!!!");
	if(ISNULL(m_pEvaluator)) SS_THROW(L"m_pEvaluator empty!!!");
	
	bool bCanSearchMore=false;
	try{
		ToConsole(L"CExtractingManager::SearchNext");

		m_pStorageManager->Update();

		if(!m_pStorageManager->IsExtractingMode()){
			///���� ����� ���������� �� ��������� ������ �� ���������
			TO_CONSOLE(L"Extracting not set, stop indexation before!!!");
			SS_THROW(L"Extracting not set, stop indexation before!!!");
		}
		
		ucStep=0;
		//������������� ����� ��������� ����������� ������
		m_pSearchFactory->GetConvertorToLinearResults()->SetCurrSearchResultCollection(&m_SessionFindResults);

		//������������ ������� ����������
		START_TICK(L"CalculateNext");
		ucStep=1;
		bCanSearchMore=m_pEvaluator->CalculateNext();
		STOP_TICK(L"CalculateNext");

		if(!bCanSearchMore){
			ToConsole(L"All Index base is searched. Cann't search more!!!!");
		}
		
		//VIEW_TICKS();
		ToConsole(L"Eof-CExtractingManager::Next");

		return bCanSearchMore?true:false;
	}catch(...){
		
		Reset();

		VIEW_TICKS();

		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"SetCurrSearchResultCollection");
			break;
		case 1:
			wcscpy(buf, L"CalculateNext");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		}

		ERR_TO_CONSOLE(erTryCatch, buf);
		SS_THROW(buf);
		return false;
	}
}

bool CExtractingManager::PrepareToFind(
		const wchar_t* wszIndexStorageName, 
		SS::Core::Types::IndexationSearch::TSearchParams* pCommonSearchParameter,
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings)
{
	if(ISNULL(pSearchSettings)) SS_THROW(L"pSearchSettings is NULL");
	if(ISNULL(pCommonSearchParameter)) SS_THROW(L"pCommonSearchParameter is NULL");
	if(ISNULL(m_pStorageManager)) SS_THROW(L"m_pStorageManager is NULL");
	if(ISNULL(m_pSettingsServer)) SS_THROW(L"m_pSettingsServer is NULL");

	unsigned char ucStep=0;
	
	try{
		START_TICK(L"Init");
		
		ucStep=0;

		//	�������� �������
		if (m_pCurrentPrmQueryResult == NULL)
		{
			TO_CONSOLE(L"m_pCurrentQueryResult empty!!!");
			SS_THROW(L"m_pCurrentQueryResult empty!!!");
		}
		else
		{
			if (m_pCurrentPrmQueryResult->GetSuperTemplate() == NULL)
			{
				TO_CONSOLE(L"m_pCurrentQueryResult SuperTemplate empty!!!");
				SS_THROW(L"m_pCurrentQueryResult SuperTemplate empty!!!");
			}
		}
		
		ucStep=3;
		//���������� ��� ��� ����
		Reset();

		//������� ��������� �������
		ucStep=4;
		
		wchar_t buf[100];
		swprintf(buf, L"CExtractingManager::PrepareToFind Source Storage: %s, SearchInObtained: %u", 
			wszIndexStorageName, (unsigned int)pCommonSearchParameter->m_SearchInObtainedMode);
		ToConsole(buf);

		Storages::CIndexStorage* pIndexStorage=m_pStorageManager->GetIndexStorage(wszIndexStorageName);

		if(ISNULL(pIndexStorage)){
			TO_CONSOLE(wszIndexStorageName);
			SS_THROW(L"pIndexStorage called by name: " AND wszIndexStorageName AND " is NULL");
		}

		ucStep=5;
		m_pSearchFactory=new CSearchFactory(
			wszIndexStorageName,
			m_pStorageManager, 
			&m_SessionFindResults, 
			&m_ResultsTextsNumbers,
			m_pCurrentPrmQueryResult,
			pCommonSearchParameter, 
			pSearchSettings);
		
		ucStep=6;
		m_pSearchFactory->GetESFiller()->ViewFillingSource();

		//�������� �����������
		ucStep=7;
		m_pEvaluator=m_pSearchFactory->CreateEvaluator();
		//m_pEvaluator->View();

		STOP_TICK(L"Init");

		return true;
	}catch(...){
		
		Reset();

		STOP_TICK(L"Init");

		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"m_pCurrentQueryResult empty");
			break;
		case 1:
			wcscpy(buf, L"InitQueryResult");
			break;
		case 2:
			wcscpy(buf, L"pSearchSettings correct");
			break;
		case 3:
			wcscpy(buf, L"Reset");
			break;
		case 4:
			wcscpy(buf, L"Getting IndexStorage");
			break;
		case 5:
			wcscpy(buf, L"SearchFactory creation");
			break;
		case 6:
			wcscpy(buf, L"ESFillerFromBSW View");
			break;
		case 7:
			wcscpy(buf, L"CreateEvaluator");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		}

		ERR_TO_CONSOLE(erTryCatch, buf);
		SS_THROW(buf);
	}
	return false;
}

void CExtractingManager::Reset(void)
{
	unsigned char ucStep=0;
	
	try{

	ucStep=0;
	if(m_pEvaluator){
		delete m_pEvaluator;
		m_pEvaluator=NULL;
	}

	ucStep=1;
	if(m_pSearchFactory){
		delete m_pSearchFactory;
		m_pSearchFactory=NULL;
	}

	}catch(...){

		VIEW_TICKS();

		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"Evaluator");
			break;
		case 1:
			wcscpy(buf, L"SearchFactory");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		}

		ERR_TO_CONSOLE(erTryCatch, buf);
		SS_THROW(buf);
	}
}

//--------------------------------------------------------------------//


}
}
}
}
}