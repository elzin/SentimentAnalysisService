#include "StdAfx.h"
#include ".\search_factory.h"

#include ".\eval.h"
#include ".\res_check_cnv.h"
#include ".\arg_res_int.h"
#include ".\b_logic.h"
#include ".\f_logic.h"
#include ".\r_logic.h"
#include ".\hdr_logic.h"

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
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Core::Types::IndexationSearch;
using namespace SS::Core::NdxSE::NdxProcessor::Extracting::Logics;
using namespace SS::Interface::Core::NdxSE;

//--------------------------------------------------------------------//

CSearchFactory::CSearchFactory(
		const wchar_t* wszIndexStorageName,
		Storages::CStorageManager* pStorageManager, 
		SS::Core::NdxSE::NdxProcessor::Containers::CFindResultCollection* pSearchResult,
		CSearchResultFiller::TResultsTextsNumbers* pResultsTextsNumbers,
		IParametrizedQuery*	pPrmQueryResult,
		TSearchParams* pSearchParameter, 
		CNdxSearchSettings* pSearchSettings)
:CEvalFactory(pStorageManager->GetIndexStorage(wszIndexStorageName)->GetContainersFactory()), 
m_pConvertorToLinearResults(NULL), m_pESFillerFromQuery(NULL), m_pStorageManager(pStorageManager)
{
	//������������� ��������� ������
	GetFactory()->SetSearchSettings(pSearchSettings);

	m_SearchSettings.m_CommonSettings=(*pSearchParameter);
	m_SearchSettings.m_EngineSettings=(*pSearchSettings);

	//������� ��������� ����������� � ��������
	m_pConvertorToLinearResults=new 
		CSearchResultFiller(pSearchResult, GetFactory()->GetIndexStorage(), 
		pResultsTextsNumbers, 
		m_SearchSettings.m_EngineSettings.m_ResultsSettings.m_uiIntervalExpandRange,
		m_SearchSettings.m_EngineSettings.m_SearchSettings.m_StorageUsingMode);

	//������� ������ �������
	if(pSearchSettings->m_SearchSettings.m_EvalRelevanceMode==
			CNdxSearchSettings::SSearchSettings::erWordProximityWithStatistic)
		m_pESFillerFromQuery=new CESFillerFromQuery_Statistic(GetFactory(), pPrmQueryResult);
	else
		m_pESFillerFromQuery=new CESFillerFromQuery(GetFactory(), pPrmQueryResult);
}

CSearchFactory::~CSearchFactory(void)
{
	if(m_pConvertorToLinearResults) delete m_pConvertorToLinearResults;
	if(m_pESFillerFromQuery) delete m_pESFillerFromQuery;
}

CCompositeLogic* CSearchFactory::CreateEquationLogic(void)
{
	CCompositeLogic* pCompositeLogic=new CCompositeLogic();
	
	//������������� �������� ������ ������ ��� fuzzy
	if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_SearchMode==CNdxSearchSettings::SSearchSettings::esmFuzzySearch){
		//��������� Fuzzy ������
		CFuzzyLogic* pFuzzyLogic=new CFuzzyLogic();
		pFuzzyLogic->SetActivationLevels(0, GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber());
		pCompositeLogic->AddLogic(pFuzzyLogic);
	}else if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_SearchMode==CNdxSearchSettings::SSearchSettings::esmBooleanSearch){
		//��������� ������ ������ � �������� �������
		CBooleanLogic* pBooleanLogic=new CBooleanLogic();
		pBooleanLogic->SetActivationLevels(0, GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber());
		pCompositeLogic->AddLogic(pBooleanLogic);
	}
	
	//������� �������������� ������
	if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_StorageUsingMode==CNdxSearchSettings::SSearchSettings::esumSingleStorage){
		//����� ������ � ����� ���������
		//������������� ������ ������� �������������
		if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode!=CNdxSearchSettings::SSearchSettings::erUndefined){
			CRelevanceLogic* pRelevanceLogic=new CRelevanceLogic();
			pRelevanceLogic->SetActivationLevel(GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber());
			pCompositeLogic->AddLogic(pRelevanceLogic);

			if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erTextsStatistic ||
				m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erAll){
				//������������� ���� ���������� �� �������
				pRelevanceLogic->UseStatistic((CIndexStatisticStorage*)GetFactory()->GetIndexStorage(), 
					GetFactory()->GetIndexStorage()->GetTextsBinaryStorage()->GetTextsNumber());
			}

			if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erWordProximity ||
				m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erAll){

				if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"TABLES")){
					//������������� ���� �������� ������������ ����
					pRelevanceLogic->UseTableProximity(GetFactory(), 
						m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_uiIndexProximityLimitWeight, 
						m_SearchSettings.m_EngineSettings.m_ResultsSettings.m_uiIntervalInTextMaxCount);
				}else{
					//������������� ���� �������� ������������ ����
					pRelevanceLogic->UseTextProximity(GetFactory(), 
						m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_bCheckIndexSequence, 
						m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_uiIndexProximityLimitWeight, 
						m_SearchSettings.m_EngineSettings.m_ResultsSettings.m_uiIntervalInTextMaxCount);
				}
				}else if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erWordProximityWithStatistic){
					if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"TEXT")){
						//������������� ���� �������� ������������ ����
						pRelevanceLogic->UseStatisticProximity(GetFactory());
					}
				}
			
			//������������� ������ ������
			pRelevanceLogic->SetQuery(m_pESFillerFromQuery->GetFillingSource());
		}

	}else if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_StorageUsingMode==
			CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage ||
			m_SearchSettings.m_EngineSettings.m_SearchSettings.m_StorageUsingMode==
					CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage){
		//����� ������ � ������� � ���������� ���������
		if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"HEADERS")){
			//���� ����� ���� ������ � ���������� ��� ����������� �� ���������� ������� ���������� ������
			CHeaderLogic* pHeaderLogic=new CHeaderLogic();
			pHeaderLogic->SetActivationLevel(GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber());
			pCompositeLogic->AddLogic(pHeaderLogic);
			//������������� ������ ������	
			pHeaderLogic->SetQuery(m_pESFillerFromQuery->GetFillingSource());

		}else if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"TEXT")){
			//��� ��������� ���������
			//������� ������ ������� ��������, � ������ ��������� ������� � ����������
		
			CRelevanceLogic* pRelevanceLogic=new CRelevanceLogic();
			pRelevanceLogic->SetActivationLevel(GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber());
			pCompositeLogic->AddLogic(pRelevanceLogic);

			if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erWordProximity ||
				m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erAll){
				//������������� ���� �������� ������������ ����
				pRelevanceLogic->UseTextAndHeadersProximity(GetFactory(), 
					m_pConvertorToLinearResults->GetCurrSearchResultCollection(),
					static_cast<Storages::CIndexStorageHeaders*>(m_pStorageManager->GetIndexStorage(L"HEADERS")),
					m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_bCheckIndexSequence, 
					m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_uiIndexProximityLimitWeight, 
					m_SearchSettings.m_EngineSettings.m_ResultsSettings.m_uiIntervalInTextMaxCount);
			}
			
			//������������� ������ ������
			pRelevanceLogic->SetQuery(m_pESFillerFromQuery->GetFillingSource());
		}else if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"TABLES")){
			//��� ��������� ���������
			//������� ������ ������� ��������, � ������ ��������� ������� � ����������
		
			CRelevanceLogic* pRelevanceLogic=new CRelevanceLogic();
			pRelevanceLogic->SetActivationLevel(GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber());
			pCompositeLogic->AddLogic(pRelevanceLogic);

			if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erWordProximity ||
				m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==CNdxSearchSettings::SSearchSettings::erAll){
				//������������� ���� �������� ������������ ����
					pRelevanceLogic->UseTableAndHeadersProximity(GetFactory(), 
					m_pConvertorToLinearResults->GetCurrSearchResultCollection(),
					static_cast<Storages::CIndexStorageHeaders*>(m_pStorageManager->GetIndexStorage(L"HEADERS")),
					static_cast<Storages::CIndexStorageTables*>(m_pStorageManager->GetIndexStorage(L"TABLES")),
					m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_bCheckIndexSequence, 
					m_SearchSettings.m_EngineSettings.m_PatternSearchSettings.m_uiIndexProximityLimitWeight, 
					m_SearchSettings.m_EngineSettings.m_ResultsSettings.m_uiIntervalInTextMaxCount);
			}
			
			//������������� ������ ������
			pRelevanceLogic->SetQuery(m_pESFillerFromQuery->GetFillingSource());
		}
	}

	return pCompositeLogic;
}

CResultsContainer* CSearchFactory::CreateResultsContainer(void)
{
	if(ISNULL(GetFactory()->GetIndexStorage())) return NULL;
	
	unsigned int uiSearchLimitDepth=0;
	//������������� ������� ������ - ��������� �������
	uiSearchLimitDepth=GetFactory()->GetIndexStorage()->GetLevelStoragesNumber()-1;

	if(m_SearchSettings.m_CommonSettings.m_SearchInObtainedMode==TSearchParams::esiomText){
		//���� ����� � ���������
		unsigned int uiCorrectionLimitDepth=EMPTY_VALUE;
		//������� ������ �������
		uiCorrectionLimitDepth=GetFactory()->GetIndexStorage()->GetWordsControlLevelNumber();

		//������� ��������� � ������������ ���������
		CResultsContainerWithCorrection* pResultsContainer=
			new CResultsContainerWithCorrection(
				this, 
				GetFactory()->GetIndexStorage(),
				uiSearchLimitDepth, 
				uiCorrectionLimitDepth);
		
		//��������� ������� ��������������� ����������
		unsigned int CoordBuffer[5] = { 0 };
		CSearchResultFiller::TResultsTextsNumbers* pResultsTextsNumbers=m_pConvertorToLinearResults->GetResultsTextsNumbers();
		if(pResultsTextsNumbers && !pResultsTextsNumbers->empty()){
			for(CSearchResultFiller::TResultsTextsNumbers::iterator itTextNumber=pResultsTextsNumbers->begin(); itTextNumber!=pResultsTextsNumbers->end(); itTextNumber++){
				//ToConsole(L"TextNumber", (*itTextNumber));
				//������ � ����� ����� ������
				CoordBuffer[1]=(unsigned int)(*itTextNumber);
				//��������� � ��������� ����� ������
				pResultsContainer->AddCorrectionResult(CoordBuffer, 2);
			}

			//��������� ��������, ������� ��������� ������ ������ ����� ��������� �� ������
			pResultsTextsNumbers->clear();

			//pResultsContainer->View();
		}else{

			TO_CONSOLE(L"pResultsTextsNumbers not valid or empty! Perfom simple searching");		
			
			//������� ��������� ���������
			if(pResultsContainer) delete pResultsContainer;

			//���� ��� ������ � ��������� ������� ������� ��������� 
			//� ������������ �� ���������� �����������
			return new CResultsContainer(
				this, 
				uiSearchLimitDepth);

		}
		
		return pResultsContainer;
	}else{
		
		//������� ��������� ������ ������ ����� ��������� �� ������
		if(m_pConvertorToLinearResults->GetResultsTextsNumbers())
			m_pConvertorToLinearResults->GetResultsTextsNumbers()->clear();

		//���� ��� ������ � ��������� ������� ������� ��������� 
		//� ������������ �� ���������� �����������
		return new CResultsContainer(
			this, 
			uiSearchLimitDepth);
	}

}

CResultsChecker* CSearchFactory::CreateResultsChecker(unsigned int uiValidResultsDepth)
{
	if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"HEADERS")){	
		
		//���� ����� � ������ ���������� �� ������ ������ � ����������
		return new CResultsCheckerWithHIDConvertion(uiValidResultsDepth, 
			m_SearchSettings.m_CommonSettings.m_uiMaxSearchResultsCount,
			m_pConvertorToLinearResults);
	
	}else if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==
		CNdxSearchSettings::SSearchSettings::erWordProximity ||
		m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==
		CNdxSearchSettings::SSearchSettings::erAll ||
			m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==
			CNdxSearchSettings::SSearchSettings::erWordProximityWithStatistic){
		
		//��� ������ � ��������� �������� �������
		return new CResultsCheckerWithIntervalConvertion(uiValidResultsDepth, 
			m_SearchSettings.m_CommonSettings.m_uiMaxSearchResultsCount,
			m_pConvertorToLinearResults);
	}else{
		
		//��� ������� ������
		return new CResultsCheckerWithConvertion(uiValidResultsDepth, 
			m_SearchSettings.m_CommonSettings.m_uiMaxSearchResultsCount,
			m_pConvertorToLinearResults);
	}
}

CResultArgument* CSearchFactory::CreateResultArgument(unsigned int uiArgumentID, float fArgumentWeight, unsigned int uiArgumentDepth)
{

	if(!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"HEADERS")){	
		if((GetFactory()->GetIndexStorage()->GetLevelStoragesNumber()-1)==uiArgumentDepth){
			//���� ����� � ������ ���������� �� ������ ������ � ����������
			//��� ���������� ������ �� ������� �������� 
			//� ��������� ��������������� ����������
			return new CResultArgument_HID(uiArgumentID, fArgumentWeight);
		}
	}else{
		if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==
			CNdxSearchSettings::SSearchSettings::erWordProximity ||
			m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==
			CNdxSearchSettings::SSearchSettings::erAll ||
			m_SearchSettings.m_EngineSettings.m_SearchSettings.m_EvalRelevanceMode==
			CNdxSearchSettings::SSearchSettings::erWordProximityWithStatistic){

			if((GetFactory()->GetIndexStorage()->GetLevelStoragesNumber()-1)==uiArgumentDepth){
				//���� ����� ��������� ��������, � �� ������� �������� ���������� ������,
				//�� ���������� �������� � ��������� ����������� ����������
				return new CResultArgumentWithIntervals(uiArgumentID, fArgumentWeight);
			}
		}
	}	

	//� ��������� ������� ������� ������� ��������
	return new CResultArgument(uiArgumentID, fArgumentWeight);
}

CEvaluator* CSearchFactory::CreateEvaluator(void)
{
	//������� �����������
	CEvaluator* pEvaluator=new CEvaluator(this);
	//������ �����������
	pEvaluator->Init(m_pESFillerFromQuery);

	return pEvaluator;
}

CBlockEquation* CSearchFactory::CreateCalcEquation(void)
{
	if(m_SearchSettings.m_EngineSettings.m_SearchSettings.m_StorageUsingMode==
		CNdxSearchSettings::SSearchSettings::esumHeadersAndTextStorage ||
		m_SearchSettings.m_EngineSettings.m_SearchSettings.m_StorageUsingMode==
		CNdxSearchSettings::SSearchSettings::esumHeadersAndTablesStorage){
		//��� ������ � ������� � ���������� ������� ������ �������������� ������� 
		return new CBlockOREquation(this);
	}else{
		//��� ��� ��������� ������� ������� �������������� ������� 
		return CEvalFactory::CreateCalcEquation();
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}