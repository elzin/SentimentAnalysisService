#include "StdAfx.h"
#include ".\r_logic.h"
#include ".\arg_res_int.h"
#include ".\arg_complex.h"
#include ".\prx_union.h"
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
using namespace SS::Interface::Core::NdxSE;

//--------------------------------------------------------------------//

CRelevanceLogic::CRelevanceLogic(void)
:CLogic(CLogic::elRelevance), 
m_pRelevanceEvaluators(NULL), m_pStatisticEvaluator(NULL)
{
}

CRelevanceLogic::~CRelevanceLogic(void)
{
	if(m_pRelevanceEvaluators) delete m_pRelevanceEvaluators;
	if(m_pStatisticEvaluator) delete m_pStatisticEvaluator;
}

void CRelevanceLogic::UseStatistic(CIndexStatisticStorage* pIndexStorage, unsigned int uiTotalTextsNumber)
{
	if(ISNULL(pIndexStorage)) return;

	if(m_pStatisticEvaluator) delete m_pStatisticEvaluator;
	m_pStatisticEvaluator=new CStatisticEvaluator(pIndexStorage, uiTotalTextsNumber);
}

void CRelevanceLogic::UseStatisticProximity(CContainersFactory* pContainersFactory)
{
	if(ISNULL(pContainersFactory)) return;

	if(m_pRelevanceEvaluators) delete m_pRelevanceEvaluators;
	m_pRelevanceEvaluators=new CRelevanceEvaluators(pContainersFactory);
}

void CRelevanceLogic::UseTextProximity(CContainersFactory* pContainersFactory, bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber)
{
	if(ISNULL(pContainersFactory)) return;

	if(m_pRelevanceEvaluators) delete m_pRelevanceEvaluators;
	m_pRelevanceEvaluators=new CRelevanceEvaluators(pContainersFactory, bCheckSequence, uiIntervalLimitWeight, uiIntervalLimitNumber);
}

void CRelevanceLogic::UseTableProximity(CContainersFactory* pContainersFactory, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber)
{
	if(ISNULL(pContainersFactory)) return;

	if(m_pRelevanceEvaluators) delete m_pRelevanceEvaluators;
	m_pRelevanceEvaluators=new CRelevanceEvaluators(pContainersFactory, uiIntervalLimitWeight, uiIntervalLimitNumber);
}

void CRelevanceLogic::UseTextAndHeadersProximity(CContainersFactory* pContainersFactory, 
	CFindResultCollection* pFindResultCollection, Storages::CIndexStorageHeaders* pIndexStorageHeaders, 
	bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber)
{
	if(ISNULL(pContainersFactory)) return;

	if(m_pRelevanceEvaluators) delete m_pRelevanceEvaluators;

	m_pRelevanceEvaluators=
		new CRelevanceEvaluators(pContainersFactory, bCheckSequence, uiIntervalLimitWeight, 
			uiIntervalLimitNumber, pFindResultCollection, pIndexStorageHeaders);
}

void CRelevanceLogic::UseTableAndHeadersProximity(CContainersFactory* pContainersFactory, 
	CFindResultCollection* pFindResultCollection, Storages::CIndexStorageHeaders* pIndexStorageHeaders, Storages::CIndexStorageTables* pIndexStorageTables, 
	bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber)
{
	if(ISNULL(pContainersFactory)) return;

	if(m_pRelevanceEvaluators) delete m_pRelevanceEvaluators;

	m_pRelevanceEvaluators=
		new CRelevanceEvaluators(pContainersFactory, bCheckSequence, uiIntervalLimitWeight, 
			uiIntervalLimitNumber, pFindResultCollection, pIndexStorageHeaders, pIndexStorageTables);
}

void CRelevanceLogic::SetQuery(IParametrizedQuery* pPrmQueryResult)
{
	//ToConsole(L"CRelevanceLogic::SetQuery");
	if(ISNULL(pPrmQueryResult))  return;
	if(ISNULL(m_pRelevanceEvaluators))	return;

	//������� �����������
	CRelevanceEvaluator* pEvaluator = NULL;
	//������� ����������� ����� �������
	CWordInSequence* pEvalWord = NULL;
	CWordUnion* pUnion=NULL;
	//����� ����� � �������
	unsigned char ucWordPosInVariant = 0;

	//��� ������ � IParametrizedQuery
	IVariant* pVariant = NULL;
	ISequence* pSequence = NULL;
	IWord* pWord = NULL;

	pPrmQueryResult->DebugView();

	//�������� �� ���������
	for (unsigned int v = 0, uiVarCount = pPrmQueryResult->GetVariantCount(); v<uiVarCount; ++v)
	{
		pVariant = pPrmQueryResult->GetVariant(v);
		if (ISNULL(pVariant)) return;

		//���������� ������� ���� � ��������
		ucWordPosInVariant = 0;

		//�������� �����������
		pEvaluator = m_pRelevanceEvaluators->AddEvaluator(v);
		if (ISNULL(pEvaluator)) return;

		//	������ �� �������������������
		for (unsigned int s = 0, uiSeqCount = pVariant->GetSequenceCount(); s<uiSeqCount; ++s)
		{
			// ��������� ������������������, ��������
			pSequence = pVariant->GetSequence(s);
			if (ISNULL(pSequence)) return;
			SUnionWordsBlockInSequence sUnion(EMPTY_VALUE, EMPTY_VALUE);
			pUnion=NULL;

			//������ �� ������ � ������������������
			for (unsigned int w = 0, uiWordCount= pSequence->GetWordCount(), uiWordPosInSeq = 0; w<uiWordCount; ++w)
			{
				//�������� �����
				pWord=pSequence->GetWord(w);
				if (ISNULL(pWord)) return;

				//��������� ���� ����� ��� �������������� � ������������
				SUnionWordsBlockInSequence sTempUnion(EMPTY_VALUE, EMPTY_VALUE);
				if(pSequence->IsWordInUnion(w, &sTempUnion)){
					if(memcmp(&sTempUnion, &sUnion, sizeof(SUnionWordsBlockInSequence))!=0){
						//���� ����������� ����������...
						//���� ����� ����������� ����������, ��������� ����������� � �����������
						pUnion=static_cast<CWordUnion*>(
							pEvaluator->AddPosition(ucWordPosInVariant, s, uiWordPosInSeq, NULL));
						if(pUnion) ++uiWordPosInSeq; ++ucWordPosInVariant;
						sUnion=sTempUnion;
					}
					if(!pUnion){
						sUnion.uiFirstWordNumber=EMPTY_VALUE;
						sUnion.uiLastWordNumber=EMPTY_VALUE;
						pEvalWord = pEvaluator->AddPosition(ucWordPosInVariant, s, uiWordPosInSeq, pWord);
						++uiWordPosInSeq; ++ucWordPosInVariant;
						//�������� ����������� �������
						if(ISNULL(pEvalWord)) continue;
					}else{
						//� ��� � ��������� ����� ����� ����������� ������ � ����
						pEvalWord=new CWordInSequence(ucWordPosInVariant, pEvaluator->GetFactory(), pWord->GetAsString(), pWord->GetLinguisticWeight(), s, 0);
						pUnion->AddWord(pEvalWord);
					}
				}else{
					//����� �� ����� "��������� �����������"
					sUnion.uiFirstWordNumber=EMPTY_VALUE;
					sUnion.uiLastWordNumber=EMPTY_VALUE;

					//������ ��� � �����������
					pEvalWord = pEvaluator->AddPosition(ucWordPosInVariant, s, uiWordPosInSeq, pWord);
					++uiWordPosInSeq; ++ucWordPosInVariant;
					//�������� ����������� �������
					if(ISNULL(pEvalWord)) continue;
				}

				//�������� �� �������� � ������
				for (unsigned int i = 0, uiIndexCount=pWord->GetMorphoIndexCount(); i<uiIndexCount; ++i)
				{
					//��������� ������ �����
					pEvalWord->AddIndex(pWord->GetMorphoIndex(i));
					if(m_pStatisticEvaluator) m_pStatisticEvaluator->AddIndex(pWord->GetMorphoIndex(i));
				}
				//pEvalWord->View();
			}
		}
	}
}

void CRelevanceLogic::Init(CResultArgument* pResultArgument)
{
	CLogic::Init(pResultArgument);
	
	if(IsActive()){
		if(m_pRelevanceEvaluators) m_pRelevanceEvaluators->Clear();

		unsigned int uiCurrBasisTextsNumber=
			m_pRelevanceEvaluators!=NULL?
			pResultArgument->CalculateBaseIDFromResultHistory(m_pRelevanceEvaluators->
			GetFactory()->GetIndexStorage()):EMPTY_VALUE;
		
		if(m_pStatisticEvaluator){
			m_pStatisticEvaluator->Clear();
			m_pStatisticEvaluator->SetDocumentBasisIndex(uiCurrBasisTextsNumber);
		}
		
		if(m_pRelevanceEvaluators)
			m_pRelevanceEvaluators->SetDocumentBasisIndex(uiCurrBasisTextsNumber);
		
		//����������� ��� ���������� ���������������� ������������ ��������
		if(CWord::m_pLoggedIndexContainer){
			CWord::m_pLoggedIndexContainer->SetCurrBasisTextsNumber(uiCurrBasisTextsNumber);
		}
	}
}


CValue* CRelevanceLogic::CreateLogicValue(CValue* pValue, CComplexArgument* pComplexArgument)
{
	try{

		if(IsIdleCalculation()) return NULL;

		//������ ��������� �� ����������
		if(!IsActive()) return NULL;

		if(ISNULL(pComplexArgument)) return NULL;

		//���� �������� �� ��������� 
		//if(!(pComplexArgument->GetAttributes().m_EvalProximity)) return NULL;
		
		//START_TICK(L"SL_CreateLogicValue");
		if(m_pRelevanceEvaluators){
			//ToConsole(L"m_pRelevanceEvaluators->AddArgumentPosition");
			m_pRelevanceEvaluators->AddArgumentPosition(pComplexArgument, dynamic_cast<CCoordinateNode_4s*>(pValue));
		}

		if(m_pStatisticEvaluator){ 
			//ToConsole(L"m_pStatisticEvaluator->AddArgumentPosition");
			m_pStatisticEvaluator->AddArgumentPosition(pComplexArgument, dynamic_cast<CCoordinateNode_4s*>(pValue));
		}
		//STOP_TICK(L"SL_CreateLogicValue");

		return NULL;
	
	}
	catch(...)
	{
		ERR_TO_CONSOLE(erTryCatch, L"CRelevanceLogic::CreateLogicValue failed!!!");
		throw;
	}
}

void CRelevanceLogic::ToResultValue(CValue* pValue, CResultArgument* pResultArgument)
{
	try{
		if(IsIdleCalculation()){ 
			return;
		}

		//������ ��������� �� ����������
		if(!IsActive()) return ;

		//ToConsole(L"CRelevanceLogic::ToResultValue");
		
		if(ISNULL(pResultArgument)) return;
		if(ISNULL(pResultArgument->GetMyself())) return;
		if(ISNULL(pResultArgument->GetMyself()->GetValue())) return;
		
		START_TICK(L"CRelevanceLogic::ToResultValue");
		
		//�������� �������� ����������
		CCompositeValue* pCompositeValue=pResultArgument->GetMyself()->GetValue();
		//pCompositeValue->View();
		
		CResultArgumentWithIntervals* pResultArgumentWithIntervals=static_cast<CResultArgumentWithIntervals*>(pResultArgument);
		//�������� ���� ����� ��������
		CArgumentEx::TValueOrtsWeightsCollection* 
			pValueOrtsWeightsCollection=pResultArgument->GetMyself()->GetValueOrtsWeights();

		//���������� ���� ����� ��������
		unsigned int uiEvalID=0;
		float fRelevance=0.0;
		if(pCompositeValue->MoveFirstOrt()){
			do{
				fRelevance=0;

				//�������� ������������� ��� ����������
				uiEvalID=pCompositeValue->GetCurrentOrt();
				//ToConsole(L"EvalID", uiEvalID);	

				//��������� ������������� �� ��������
				if(m_pRelevanceEvaluators){
					//������������� �� �������� ����������� � ������� �������
					//START_TICK(L"ProximityEvaluators");
					fRelevance+=floor(m_pRelevanceEvaluators->Evaluate(uiEvalID))/**1000*/;
					//STOP_TICK(L"ProximityEvaluators");
					//�������� ����������� ��������� ����������
					m_pRelevanceEvaluators->FillIntervals(pResultArgumentWithIntervals);
					//�� ��������� �������
					m_pRelevanceEvaluators->ClearRangedIntervals();
				}

				//��������� ������������� �� ����������
				if(m_pStatisticEvaluator){
					//���������� ������� ������ ���� ���������� ��������, ��� �������� ������� �� ����
					if ( !m_pRelevanceEvaluators || (fRelevance != 0)) {
						//START_TICK(L"StatisticEvaluator");
						fRelevance+=floor(m_pStatisticEvaluator->Evaluate(uiEvalID));
						//STOP_TICK(L"StatisticEvaluator");
					}
				}

				//ToConsole(L"//-------------------------------------------Relevance", (unsigned int)fRelevance);	

				(*pValueOrtsWeightsCollection)[uiEvalID]=fRelevance;

			}while(pCompositeValue->MoveNextOrt());
		}

		STOP_TICK(L"CRelevanceLogic::ToResultValue");
	}
	catch(...)
	{
		if(m_pRelevanceEvaluators)
			m_pRelevanceEvaluators->ClearRangedIntervals();

		ERR_TO_CONSOLE(erTryCatch, L"CRelevanceLogic::ToResultValue failed!!!");
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
