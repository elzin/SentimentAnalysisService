#include "StdAfx.h"
#include ".\prx_eval_ans.h"
#include ".\index_stat_storage.h"
#include ".\r_evals.h"
#include <math.h>

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
namespace Logics
{

using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Core::NdxSE::NdxProcessor::Extracting;
using namespace SS::Core::NdxSE::NdxProcessor::Storages;

//--------------------------------------------------------------------//

CProximityEvaluator_Answer::CProximityEvaluator_Answer(unsigned int uiEvaluatorID, 
			Containers::CContainersFactory* pContainersFactory)
:CRelevanceEvaluator(uiEvaluatorID, false, pContainersFactory), 
m_uiRarityWordsCount(EMPTY_VALUE), m_uiCurrDocumentRarityWordsCount(0)
{
}

CProximityEvaluator_Answer::~CProximityEvaluator_Answer(void)
{
	TWordsCollection::iterator itAW=m_AnswerWords.begin();
	while(itAW!=m_AnswerWords.end()){
		delete (*itAW);
		itAW++;
	}
}

CWordInSequence* CProximityEvaluator_Answer::AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord)
{
	if(!pWord) return NULL;

	//��������� ��������� ������� � �����������
	CWordWithStatistic* pCommonPosition=
		new CWordWithStatistic(ucPositionID, GetFactory(), pWord->GetAsString(), pWord->GetLinguisticWeight(), pWord->GetAnswerFlag()==FALSE?false:true);

	if(pCommonPosition->IsAnswerWord()){
		//���� ����� ���� ��������� ���� ����� � ��������� ���� �������
		m_AnswerWords.push_back(pCommonPosition);
	}else{
		//��������� ������� � ���������
		AddChildElement(pCommonPosition->GetID(), pCommonPosition); 
	}

	return pCommonPosition;
}

unsigned int CProximityEvaluator_Answer::GetRarityWordsCount(void)
{
	if(m_uiRarityWordsCount==EMPTY_VALUE){
		TWordsCollection::iterator itAW=m_AnswerWords.begin();
		while(itAW!=m_AnswerWords.end()){
			if((*itAW)) 
				if((*itAW)->GetAbsFrequencyWeight()<GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordLimit)
						m_uiRarityWordsCount++;
			itAW++;
		}

		TChildCollection::iterator itWord=m_ChildCollection.begin();
		while(itWord!=m_ChildCollection.end()){
			if((*itWord)){
				if(((Containers::CWordWithStatistic*)(*itWord))->GetAbsFrequencyWeight()<GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordLimit)
						m_uiRarityWordsCount++;
			}
			itWord++;
		}
		if(m_uiRarityWordsCount==EMPTY_VALUE) m_uiRarityWordsCount=0;
	}

	return m_uiRarityWordsCount;
}

void CProximityEvaluator_Answer::ResetWordsWeights(void)
{
	TWordsCollection::iterator itAW=m_AnswerWords.begin();
	while(itAW!=m_AnswerWords.end()){
		if((*itAW)) (*itAW)->ResetWeight();
		itAW++;
	}

	TChildCollection::iterator itWord=m_ChildCollection.begin();
	while(itWord!=m_ChildCollection.end()){
		if((*itWord)){
			((Containers::CWordWithStatistic*)(*itWord))->ResetWeight();
		}
		itWord++;
	}
}

void CProximityEvaluator_Answer::AddArgumentPosition(CComplexArgument* pComplexArgument, CCoordinateNode_4s* pCoordinateNode)
{
	if(ISNULL(pComplexArgument)) return;
	
	if(pComplexArgument->GetAttributes().m_bAnswerIndex){
		//���� ����� ���� ������ ��������� ���� � ��������� �������
		TWordsCollection::iterator itAW=m_AnswerWords.begin();
		while(itAW!=m_AnswerWords.end()){
			(*itAW)->AddArgumentPosition(pComplexArgument, pCoordinateNode);
			itAW++;
		}
	}else{
		for(unsigned int uiChildID=0; uiChildID<m_ChildCollection.size(); uiChildID++){
			if(m_ChildCollection[uiChildID]){
				AddArgumentPositionByID(uiChildID, pComplexArgument, pCoordinateNode);
			}
		}
	}
}

bool CProximityEvaluator_Answer::PrepareAnswersWords(unsigned int uiEvalID)
{
	m_WordsByRangeID.clear();

	//��������� ��������������� ��������� ���� ������
	unsigned int uiRangeID;
	TWordsCollection::iterator itAW=m_AnswerWords.begin();
	while(itAW!=m_AnswerWords.end()){
		if((*itAW)){
			//������� ������� ������ ��� ���� ������ ��������� � �����������
			(*itAW)->ClearPositions();

			uiRangeID=(*itAW)->PrepareMakeCommonPositions(uiEvalID);
			if(uiRangeID==0){
				m_WordsByRangeID.clear();
				break;
			}
				
			//����� �� �������� ��� ����������� � ����� �� ������ �������, ������ ������ ����
			while(m_WordsByRangeID.find(uiRangeID)!=m_WordsByRangeID.end()){
				++uiRangeID;
			}
			//��������� � ���������
			m_WordsByRangeID.insert(TSortedWordsCollection::value_type(uiRangeID, (*itAW)));
		}
		itAW++;
	}
	
	if(m_WordsByRangeID.empty()) return false;
	
	//������� ������� ������� ����� ������
	m_WordsByRangeID.begin()->second->MakeCommonPositions(uiEvalID, 0, EMPTY_VALUE);
	
	return true;
}

bool CProximityEvaluator_Answer::PrepareCommonWords(unsigned int uiEvalID)
{
	m_WordsByRangeID.clear();

	m_uiCurrDocumentRarityWordsCount=0;

	//��������� ��������������� ��������� ���� ������
	unsigned int uiRangeID;
	TChildCollection::iterator itWord=m_ChildCollection.begin();
	while(itWord!=m_ChildCollection.end()){
		if((*itWord)){
			//������� ������� ������ ��� ���� ������ ��������� � �����������
			(*itWord)->ClearPositions();

			uiRangeID=(*itWord)->PrepareMakeCommonPositions(uiEvalID);
			if(uiRangeID==0){
				itWord++;
				continue;
			}
			
			float fWordWeight=((CWordWithStatistic*)(*itWord))->GetAbsFrequencyWeight();
			
			//wchar_t buf[256];
			//swprintf(buf, L"Word: %u, Weight: %f", (*itWord)->GetID(), fWordWeight);
			//ToConsole(buf);

			if(fWordWeight<GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordLimit)
				m_uiCurrDocumentRarityWordsCount++;

			//����� �� �������� ��� ����������� � ����� �� ������ �������, ������ ������ ����
			while(m_WordsByRangeID.find(uiRangeID)!=m_WordsByRangeID.end()){
				++uiRangeID;
			}
			//��������� � ���������
			m_WordsByRangeID.insert(TSortedWordsCollection::value_type(uiRangeID, (CWordWithStatistic*)(*itWord)));
		}
		itWord++;
	}
	
	//ToConsole(L"m_uiCurrDocumentRarityWordsCount", m_uiCurrDocumentRarityWordsCount);
	//ToConsole(L"GetRarityWordsCount()", GetRarityWordsCount());

	//��������� ������ ������ ����
	if(GetRarityWordsCount()!=0 && ((float)m_uiCurrDocumentRarityWordsCount/(float)GetRarityWordsCount())<
		GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordsQuorum){
		return false;
	}else{
		return true;
	}
}

bool CProximityEvaluator_Answer::EvaluateNextPositions(unsigned int uiEvalID, unsigned int uiLimitBound)
{
	if(m_WordsByRangeID.empty()) return false;

	m_CurrentResultWords.clear();

	TSortedWordsCollection::iterator itWord=m_WordsByRangeID.begin();

	//���� � ������� ����� ������ ������� ����������� ��������� ����������
	if(itWord->second->GetCurrentPositions()->empty()) return false;

	//�������� ��������� ������� ��������� �� � ���������, ��������� �������
	unsigned int uiStartPos=itWord->second->CurrentPositionsPopFront();
	m_CurrentResultWords.insert(TSortedWordsCollection::value_type(uiStartPos, itWord->second));

	unsigned int uiDocumentIndex=m_uiDocumentBasisIndex+CWordWithStatistic::m_uiCurrentEvalID;
	//if(uiDocumentIndex==1265){
		//ToConsole(L"Bof-CProximityEvaluator_Answer::EvaluateNextPositions Limit", uiLimitBound);
		//itWord->second->View();
		//ToConsole(L"uiStartPos", uiStartPos);
	//}		

	unsigned int uiLeftBound=uiStartPos>=uiLimitBound?uiStartPos-uiLimitBound:0;
	unsigned int uiRightBound=uiStartPos+uiLimitBound;

	if(m_WordsByRangeID.size()==1) return true;
	//��������� ����� ������ �������, �������� �� ������� �����
	unsigned int uiPosSum=uiStartPos;
	itWord++;
	while(itWord!=m_WordsByRangeID.end()){
		if(itWord->second){
			itWord->second->ClearPositions();
			START_TICK(L"MakeCommonPositions");
			itWord->second->MakeCommonPositions(uiEvalID, uiLeftBound, uiRightBound);
			STOP_TICK(L"MakeCommonPositions");
			//itWord->second->View();
			
			//���� ���� � ������ ����� ������ ������� ���, ��������� ����������
			if(itWord->second->GetCurrentPositions()->empty()){
				if(!m_AnswerWords.empty()){
					m_CurrentResultWords.clear();
					return true;
				}
			}else{
				unsigned int uiTemp=itWord->second->GetNearPosition(uiPosSum/m_CurrentResultWords.size());

				//if(uiDocumentIndex==1265){
				//itWord->second->View();
				//ToConsole(L"NearPosition", uiTemp);
				//ToConsole(L"uiStartPos", uiStartPos);
				//}		

				if(uiTemp!=EMPTY_VALUE){
					//������ � ��������� ������ ������� �����
					m_CurrentResultWords.insert(TSortedWordsCollection::value_type(uiTemp, itWord->second));
					uiPosSum+=uiTemp;
				}
			}
			

		}
		itWord++;
	}

	//��������� ��� ���� ������ ����������� �������
	return true;
}

unsigned int CProximityEvaluator_Answer::GetResultCenterPosition(void)
{
	if(m_CurrentResultWords.empty()) return EMPTY_VALUE;
	if(m_CurrentResultWords.size()==1) return m_CurrentResultWords.begin()->first;
	return m_CurrentResultWords.begin()->first+
		(((--m_CurrentResultWords.end())->first-m_CurrentResultWords.begin()->first)/2);
}

Containers::CInterval* CProximityEvaluator_Answer::CreateInterval(unsigned int uiHeadPos, unsigned int uiTailPos)
{
	//������� ��������
	CInterval* pInterval=new CInterval(uiHeadPos, uiTailPos);
	//pInterval->View();
	return pInterval;
}

unsigned int CProximityEvaluator_Answer::GetIntervalWeight(Containers::CInterval* pInterval)
{
	if(ISNULL(pInterval)) return 0;
	unsigned int uiIntervalLength=pInterval->GetLength();
	//pInterval->View();

	//ToConsole(L"Bof-CProximityEvaluator_Answer::GetIntervalWeight");

	//��������� ��� ��������
	//��� ������� ��: 
	//1. ���������� ���� � ����������
	//2. �������������� ���� ����
	//3. ����� ��������� ����������

	wchar_t buf[256];

	//���������� �������� ����������, �������������� ���� ����/���������� ���� 
	float fResult=0.0;
	float fRarity=0.0;
	float fWordWeight=0.0;
	float fDistributionWeight=1;
	unsigned int uiRarityWordsCount=0;
	TSortedWordsCollection::iterator itWord=m_CurrentResultWords.begin();
	while(itWord!=m_CurrentResultWords.end()){
		fWordWeight=itWord->second->GetWeight();

		//if(itWord!=--m_CurrentResultWords.end()){
		//	TSortedWordsCollection::iterator itTemp=itWord;
		//	itTemp++;
		//	fDistributionWeight*=(itTemp->first-itWord->first);
		//}

		if(itWord->second->GetAbsFrequencyWeight()<GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordLimit)
			uiRarityWordsCount++;

		//swprintf(buf, L"Word: %u, Position: %u, WordWeight: %f", itWord->second->GetID(), itWord->first, fWordWeight);
		//ToConsole(buf);

		fRarity+=fWordWeight;
		itWord++;
	}

	//��������� ������ ������ ����
	if(GetRarityWordsCount()!=0 && ((float)uiRarityWordsCount/(float)GetRarityWordsCount())<
		GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordsQuorum){
		return 0;
	}

	if(fRarity==0.0) return 0;
	fResult+=fRarity;
	
	//���������� ���������� ������ ����
	unsigned int uiDirtyWordsCount=(uiIntervalLength+1-m_CurrentResultWords.size());

	//���������� ��� �� ������������� ���� � ���������
	//if(m_CurrentResultWords.size()>2){
	//	fDistributionWeight=((float)uiDirtyWordsCount)/fDistributionWeight;
	//	//fResult+=fDistributionWeight*0;
	//}else{
	//	fDistributionWeight=0.0;
	//}

	//���������� ��� �� ������� ��������� �� �������
	float fIntWeight=exp((float)m_CurrentResultWords.size())/(float)uiDirtyWordsCount;
	fIntWeight=logf(fIntWeight+1);
	fResult+=fIntWeight;

	unsigned int uiDocumentIndex=m_uiDocumentBasisIndex+CWordWithStatistic::m_uiCurrentEvalID;
	//if(uiDocumentIndex==369){
	//swprintf(buf, L"Result: %f, Rarity: %f, Weight: %f, DistributionWeight: %f, uiIntervalLength: %u, WordsCount: %u", 
	//	fResult, fRarity, fIntWeight, fDistributionWeight,
	//	uiIntervalLength, (unsigned int)m_CurrentResultWords.size());
	//ToConsole(buf);
	//}
	return (unsigned int)(fResult*10000);
}

bool CProximityEvaluator_Answer::EvaluateWithAnswers(unsigned int uiEvalID)
{
	//������� ����� ������� ��� ���������� �������
	if(!PrepareAnswersWords(uiEvalID)) 
		return m_AnswerWords.empty()?false:true;


	unsigned int uiResultIntervalCenter;
	unsigned int uiCommonLimitBound=GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_uiCommonIntervalLimitLength/2;

	//� ����� ��������� �������� �� ������� ������
	while(EvaluateNextPositions(uiEvalID, GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_uiAnswerIntervalLimitLength)){
		//�������� ������ �������� ���������
		uiResultIntervalCenter=GetResultCenterPosition();
		//�������� �������� ������� � ��������� ������ � �������� ��������
		TChildCollection::iterator itCommonWord=m_ChildCollection.begin();
		while(itCommonWord!=m_ChildCollection.end()){
			if((*itCommonWord)){
				//������� ������� �����
				(*itCommonWord)->ClearPositions();
				(*itCommonWord)->PrepareMakeCommonPositions(uiEvalID);
				(*itCommonWord)->MakeCommonPositions(
					uiEvalID, 
					uiResultIntervalCenter>=uiCommonLimitBound?uiResultIntervalCenter-uiCommonLimitBound:0, 
					uiResultIntervalCenter+uiCommonLimitBound);
				
				if((*itCommonWord)->GetCurrentPositions()->empty()){
					itCommonWord++;
					continue;
				}

				unsigned int uiTemp=(*itCommonWord)->GetNearPosition(uiResultIntervalCenter);
				//ToConsole(L"uiTemp", uiTemp);
				//ToConsole(L"uiResultIntervalCenter", uiResultIntervalCenter);

				//�������� ��������� � ������ ������� ��������� � ���������
				m_CurrentResultWords.insert(TSortedWordsCollection::value_type(
					uiTemp, 
					(Containers::CWordWithStatistic*)(*itCommonWord)));
			}
			itCommonWord++;
		}
		
		//���� � ���������� ������ ����� ������, ����� �� ��������
		if(m_CurrentResultWords.size()==m_AnswerWords.size()) continue;

		//��������� ���������
		AddInterval(m_CurrentResultWords.begin()->first, (--m_CurrentResultWords.end())->first); 		
	}

	return true;
}

void CProximityEvaluator_Answer::Evaluate(unsigned int uiEvalID)
{
	unsigned char ucStep=0;
	try{

		ResetWordsWeights();

		unsigned int uiDocumentIndex=m_uiDocumentBasisIndex+uiEvalID;
		if(uiDocumentIndex==1265){
			int a=0;
		}
		//ToConsole(L"DocumentIndex", uiDocumentIndex);
		
		//�������� ����������� ����������� ��� ������� ���������
		CWordWithStatistic::m_uiCurrentDocumentNormKoef=((CIndexStatisticStorage*)GetFactory()->GetIndexStorage())->GetDocNormStorage()->GetDocNorm(uiDocumentIndex);
		CWordWithStatistic::m_uiTotalDocumentsNumber=GetFactory()->GetIndexStorage()->GetTextsBinaryStorage()->GetTextsNumber();
		CWordWithStatistic::m_uiCurrentEvalID=uiEvalID;

		//���� ���������� � ������ ���� ������ ������ ������� ������ ������� �� �����
		if(EvaluateWithAnswers(uiEvalID)) return;

		//���� ���������� � ������ ���� ������ �� ������,
		//�������� ������������� ������ ��� ������� ����
		
		//������� ����� � �����������
		if(!PrepareCommonWords(uiEvalID)){ 
			//ToConsole(L"PrepareCommonWords");
			return;
		}

		unsigned int uiCommonLimitBound=GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_uiCommonIntervalLimitLength/2;

		//� ����� ��������� �������� �� ������� ������
		while(!m_WordsByRangeID.empty()){
			//������� ������� ������� �����
			m_WordsByRangeID.begin()->second->ClearPositions();
			m_WordsByRangeID.begin()->second->MakeCommonPositions(uiEvalID, 0, EMPTY_VALUE);
			
			while(EvaluateNextPositions(uiEvalID, uiCommonLimitBound)){
				//��������� ���������
				AddInterval(m_CurrentResultWords.begin()->first, (--m_CurrentResultWords.end())->first); 		
				
				//���� ����������� ����������� ������ �����������
				if(m_pRelevanceEvaluatorsOwner->GetAddedIntervalsCount()>=m_uiGoodIntervalsLimitNumber) return;
			}
			
			//���� � ������� ����� ����������� �������, ������� ��� �� ��������� 
			//� ���������� ���������� � ��������� ������ ������
			if(m_WordsByRangeID.begin()->second->GetCurrentPositions()->empty()){
				//���� ����� ���� ������ ��������� ������� ������ ����
				if(m_WordsByRangeID.begin()->second->GetAbsFrequencyWeight()<
					GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordLimit)
					m_uiCurrDocumentRarityWordsCount--;
				
				//���� ������ ���� ����� ������ �������, ��������� ����������
				if(GetRarityWordsCount()!=0 && ((float)m_uiCurrDocumentRarityWordsCount/(float)GetRarityWordsCount())<
					GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordsQuorum){
					return;
				}
				
				m_WordsByRangeID.erase(m_WordsByRangeID.begin());
			}
		}
		
	}catch(...){
		wchar_t buf[256]=L"";
		//switch(ucStep){
		//default:
		//	wcscpy(buf, L"Unknown place");
		//	break;
		//}

		ERR_TO_CONSOLE(erTryCatch, buf);
		throw;
	}

}

//--------------------------------------------------------------------//

}
}
}
}
}
}
