#include "StdAfx.h"

#include ".\prx_eval.h"
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

//--------------------------------------------------------------------//

CProximityEvaluator_Text::CProximityEvaluator_Text(unsigned int uiEvalID, bool bCheckSequence, CContainersFactory* pContainersFactory)
:CRelevanceEvaluator(uiEvalID, bCheckSequence, pContainersFactory)
{
}

CProximityEvaluator_Text::~CProximityEvaluator_Text(void)
{
}

CWordInSequence* CProximityEvaluator_Text::AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord)
{
	CWordInSequence* pWordInSequence=NULL;
	if(!pWord){
		pWordInSequence=new CWordUnion(ucPositionID, GetFactory(), ucSequenceID, ucPosInSequence);
		pWordInSequence->SetObligatory(true);
		m_WordUnionCollection.push_back(static_cast<CWordUnion*>(pWordInSequence));
	}else{
		pWordInSequence=new CWordInSequence(ucPositionID, GetFactory(), pWord->GetAsString(), pWord->GetLinguisticWeight(), ucSequenceID, ucPosInSequence);
		pWordInSequence->SetObligatory(pWord->GetObligatoryFlag()==0?false:true);
	}

	//��������� ������� � ���������
	pWordInSequence=AddChildElement(pWordInSequence->GetID(), pWordInSequence); 
	if(ISNULL(pWordInSequence)) return NULL;

	if(m_bCheckSequence){
		m_SequenceCollection.AddPosition(pWordInSequence->GetSequenceID(), pWordInSequence->GetPosInSequence());
	}

	return pWordInSequence;
}

CInterval* CProximityEvaluator_Text::CreateInterval(unsigned int uiHeadPos, unsigned int uiTailPos)
{
	return new CInterval(uiHeadPos, uiTailPos);
}

unsigned int CProximityEvaluator_Text::GetIntervalWeight(Containers::CInterval* pInterval)
{
	if(ISNULL(pInterval)) return 0;
	unsigned int uiIntervalLength=pInterval->GetLength();

	//��� ��������� ������� �� ������� ���������� ����� � ��������� �����
	//����� ��� ���������� ������������� (����������) ������� ���������
	int iDirtyPositionsCount=(int)(uiIntervalLength-GetEvaluatedChildsNumber());

	if(iDirtyPositionsCount<0) return 0;

	//	������������ ���
	int	weight = 0;
	
	//������ 128 ������� �������
	if(iDirtyPositionsCount==0)
		weight = 100;
	else
	if(iDirtyPositionsCount<=2)
		weight = 98;
	else
	if(iDirtyPositionsCount<=5)
		weight = 90;
	else
	if(iDirtyPositionsCount<=7)
		weight = 85;
	else
	if(iDirtyPositionsCount<=10)
		weight = 70;
	else
	if(iDirtyPositionsCount<=12)
		weight = 65;
	else
	if(iDirtyPositionsCount<=20)
		weight = 55;
	else
	if(iDirtyPositionsCount<=40)
		weight = 30;
	else
	if(iDirtyPositionsCount<=60)
		weight = 20;
	else
	if(iDirtyPositionsCount<=80)
		weight = 10;
	else
	if(iDirtyPositionsCount<=100)
		weight = 5;
	else
	if(iDirtyPositionsCount<=m_uiMaxIntervalLength)
		weight = 2;
	else
		weight = 0;

	//��������� ��� �� ������� ��������� ������ �� ����������� ����
	double fUnionWeight=0.0;
	if(weight!=0 && !m_WordUnionCollection.empty()){
		unsigned int uiHeadPos=EMPTY_VALUE, uiTailPos=EMPTY_VALUE;

		for(unsigned int i=0; i<m_WordUnionCollection.size(); ++i)
		{
			fUnionWeight+=m_WordUnionCollection[i]->GetUnionWeight(&uiHeadPos, &uiTailPos);
			//���������� �������� ���� �����
			if(uiHeadPos!=EMPTY_VALUE && pInterval->m_uiHeadPos>uiHeadPos) pInterval->m_uiHeadPos=uiHeadPos;
			if(uiTailPos!=EMPTY_VALUE && pInterval->m_uiTailPos<uiTailPos) pInterval->m_uiTailPos=uiTailPos;
		}
	}
	
	if(m_SortedChildCollection.size()==1)
		return (unsigned int)((double)weight+floor(fUnionWeight));
	else
		return (unsigned int)(((double)weight+floor(fUnionWeight))*(double)m_IntervalPositions.size());
}

bool CProximityEvaluator_Text::PrepareEvaluation(unsigned int uiEvalID)
{
	m_SortedChildCollection.clear();
	m_EvaledIntervalCollection.clear();
	m_IntervalPositions.clear();
	m_SequenceCollection.Init();

	if(m_ChildCollection.empty()){
		TO_CONSOLE(L"Common positions not exist");
		return false;
	}

	//ToConsole(L"uiEvalID", uiEvalID);

	TChildCollection::iterator itSP=m_ChildCollection.begin();
	unsigned int uiRangeID;
	do{
		if((*itSP) && (*itSP)->IsEvaluated()){
			//������� ������� ������ ��� ���� ������ ��������� � �����������
			(*itSP)->ClearPositions();

			//	������������ ��� �������� ����� � list<CPosCnt*> ��������� ������� ��������
			uiRangeID=(*itSP)->PrepareMakeCommonPositions(uiEvalID);
			if(uiRangeID==0){
				//��������� ������ ��� ������������� �����	
				if((*itSP)->GetObligatory())return false;
				else continue;
			}else{
				if(!(*itSP)->GetObligatory()) uiRangeID*=10000;
			}
				
			//����� �� �������� ��� ����������� � ����� �� ������ �������, ������ ������ ����
			while(m_SortedChildCollection.find(uiRangeID)!=m_SortedChildCollection.end()){
				++uiRangeID;
			}

			//ToConsole(L"RangeID", uiRangeID);
			//(*itSP)->View();

			//��������� � ��������� ���� � ��������� �� �����
			m_SortedChildCollection.insert(TSortedChildCollection::value_type(uiRangeID, (*itSP)));
		}
	}while(++itSP!=m_ChildCollection.end());

	if(m_SortedChildCollection.empty()) return false;
	
	//�� ������� ���������� ����� ����������� ��������� ���������,
	//��������������� ����������
	TSortedChildCollection::iterator itSSP=m_SortedChildCollection.begin();
	unsigned int uiLeftBound=EMPTY_VALUE;
	unsigned int uiRightBound=EMPTY_VALUE;
	unsigned int uiMaxBound=m_uiMaxIntervalLength+m_uiValidChildsNumber;
	if(itSSP->second){	
		START_TICK(L"MakeCommonPositions");
		//	���������� m_CurrentPositions � ����� (set<unsigned int>)
		itSSP->second->MakeCommonPositions(uiEvalID, uiLeftBound, uiRightBound);
		STOP_TICK(L"MakeCommonPositions");

		//itSSP->second->View();

		CWord::TCommonPositions* pCommonPositions=itSSP->second->GetCurrentPositions();
		CWord::TCommonPositions::iterator itPos=pCommonPositions->begin();
		while(itPos!=pCommonPositions->end()){
			//������������ �������
			unsigned int uiTempLeftBound=*(itPos);
			uiTempLeftBound=uiTempLeftBound<uiMaxBound?0:uiTempLeftBound-uiMaxBound;
			unsigned int uiTempRightBound=*(itPos)+uiMaxBound;
			
			if(!m_EvaledIntervalCollection.empty() && m_EvaledIntervalCollection.back().second>=uiTempLeftBound){
				m_EvaledIntervalCollection.back().second=uiTempRightBound;
			}else{
				m_EvaledIntervalCollection.push_back(pair<unsigned int, unsigned int>(uiTempLeftBound, uiTempRightBound));
			}

			itPos++;
		}
	}
	
	return true;
}

bool CProximityEvaluator_Text::PreparePositions(unsigned int uiEvalID, unsigned int uiIntervalIndex)
{
	m_IntervalPositions.clear();
	m_SequenceCollection.Init();

	if(m_ChildCollection.empty()){
		TO_CONSOLE(L"Common positions not exist");
		return false;
	}

	if(uiIntervalIndex>=m_EvaledIntervalCollection.size()){
		TO_CONSOLE(L"Too big uiIntervalIndex");
		ToConsole(L"uiIntervalIndex", uiIntervalIndex);
		ToConsole(L"m_EvaledIntervalCollection.size()", (unsigned int)m_EvaledIntervalCollection.size());
		return false;
	}

	//���� ����� ������ ���� �����, ������� �������� �� �����, ��� ��� ������
	if(m_SortedChildCollection.size()==1) return true;

	//������� �������� ���� ���������� � �������, �� ���� ������� ���� ��� ���������� ��������
	//�������� �� ����� ���������� ������� �����
	unsigned int uiMaxBound=m_uiMaxIntervalLength+m_uiValidChildsNumber;
	unsigned int uiLeftBound=m_EvaledIntervalCollection[uiIntervalIndex].first;
	unsigned int uiRightBound=m_EvaledIntervalCollection[uiIntervalIndex].second;
	//ToConsole(L"uiLeftBound", uiLeftBound);
	//ToConsole(L"uiRightBound", uiRightBound);
	
	//��������� ����� ������ �������, �������� �� ������� �����
	TSortedChildCollection::iterator itSSP=++m_SortedChildCollection.begin();
	do{
		if(itSSP->second){
			//������ ������� ����� �����������
			itSSP->second->ClearPositions();

			//���������� m_CurrentPositions � ����� (set<unsigned int>)
			START_TICK(L"MakeCommonPositions");
			itSSP->second->MakeCommonPositions(uiEvalID, uiLeftBound, uiRightBound);
			STOP_TICK(L"MakeCommonPositions");
			
			//itSSP->second->View();
			
			if(itSSP->second->GetCurrentPositions()->empty()){
				//����� ����� ���������� ������ �����, �� ������������ ������ ����
				if(itSSP->second->GetObligatory()) break;
				else continue;
			}
			//������������ �������
			unsigned int uiTempLeftBound=*(itSSP->second->GetCurrentPositions()->begin());
			uiTempLeftBound=uiTempLeftBound<uiMaxBound?0:uiTempLeftBound-uiMaxBound;
			unsigned int uiTempRightBound=*(--(itSSP->second)->GetCurrentPositions()->end());
			uiTempRightBound+=uiMaxBound;

			if(uiLeftBound<uiTempLeftBound) uiLeftBound=uiTempLeftBound;
			if(uiLeftBound==EMPTY_VALUE) uiLeftBound=uiTempLeftBound;
			if(uiRightBound>uiTempRightBound) uiRightBound=uiTempRightBound;

		}
	}while(++itSSP!=m_SortedChildCollection.end());
	
	//������� ����� � ��������� �������, ������ ���� ������� ��� ����������
	//	������ �� ���� ������, ���������� � ����� m_IntervalPositions <�������, "�������,�����">
	TChildCollection::iterator itSP=m_ChildCollection.begin();
	do{
		if((*itSP) && (*itSP)->IsEvaluated()){
			//���� ����� ���� � ��������� � �����������
			if((*itSP)->GetCurrentPositions()->empty()){
				//���� � ����� ��� ������� ���������� �� �������
				if((*itSP)->GetObligatory())return false;
				else continue;
			}

			if(!ReplaceIntervalPosition((*itSP), NULL, EMPTY_VALUE)){
				return false;
			}
		}
	}while(++itSP!=m_ChildCollection.end());
	
	return true;
}

bool CProximityEvaluator_Text::ReplaceIntervalPosition(CWordInSequence* pCommonPosition, 
												  TIntervalPositions::iterator* pOldPosition, unsigned int uiPopedPosition)
{
	if(ISNULL(pCommonPosition))	return false;
	
	if(pOldPosition){
		//���������� �������� � �������������������
		m_SequenceCollection.UpdateSequences(&(*pOldPosition)->second, m_SequenceCollection.GetNullCollection().end());
		//������� �� ��������� �������
		m_IntervalPositions.erase(*pOldPosition);
	}

	//� ����� �������� �������� ������� � ��������, ���� �� ����������
	//��� �� ����������� �������
	while(true){
		if(uiPopedPosition==EMPTY_VALUE)
			uiPopedPosition=pCommonPosition->CurrentPositionsPopFront();
		
		pCommonPosition->SetCurrentEvalPosition(uiPopedPosition);

		//��������� ����������� �� �������
		if(uiPopedPosition==EMPTY_VALUE){ 
			//��� ������������� ����� ���������� �������
			//����������� ����������� ���������� ����� ����������, 
			//��� ��������������� ����� ���� ��������� ��� ����������� �� ����������
			return pCommonPosition->GetObligatory()?false:true;
		}
		

		//�������� ��������
		pair<TIntervalPositions::iterator, bool> Result=
			m_IntervalPositions.insert(TIntervalPositions::value_type(uiPopedPosition, SIntervalPos()));

		if(Result.second){
			//���� �������� ������
			Result.first->second.m_uiIndexPosition=uiPopedPosition;
			Result.first->second.m_pCommonPositions=pCommonPosition;

			//��������� � �������������������
			m_SequenceCollection.UpdateSequences(&Result.first->second, Result.first);
			return true;
		}

		//���� �� ������ ����������
		uiPopedPosition=EMPTY_VALUE;
	}
}

bool CProximityEvaluator_Text::SingleChildEvaluation(void)
{
	if(m_SortedChildCollection.size()==1){
		
		if(!m_IntervalPositions.empty()){
			unsigned int uiPos=m_IntervalPositions.begin()->first;
			AddInterval(uiPos, uiPos);
		}

		//����� ����� ������ ���� �������, ������ ������ ��� ������� ��� ������
		TSortedChildCollection::iterator itSP=m_SortedChildCollection.begin();
		CWord::TCommonPositions::iterator itPos=itSP->second->GetCurrentPositions()->begin();
		while(itPos!=itSP->second->GetCurrentPositions()->end()){
			//������ �������� � ���������
			AddInterval(*itPos, (*itPos));
			++itPos;
		}

		itSP->second->ClearPositions();
		return true;
	}else
		return false;
}

void CProximityEvaluator_Text::EvaluateIntervals(void)
{
	TIntervalPositions::iterator itIntervalPos=m_SequenceCollection.GetNullCollection().end();
	SIntervalPos IntervalPos;
	SIntervalPos RightIntervalPos;
	SIntervalPos LeftIntervalPos;

	if(SingleChildEvaluation()) return;

	unsigned int uiStep=0;
	try{

	while(true){
		//ViewIntervalPositions();

		//��������� ��������� ������� ��������� �� �������������� �������������������
		if(!m_SequenceCollection.CheckOnSequences(&itIntervalPos))
		{
			//���� ������������������ ����������, ��������� ������� ����������� ��������
			if(!ReplaceIntervalPosition(itIntervalPos->second.m_pCommonPositions, &itIntervalPos, EMPTY_VALUE)) break;
		}else{
			//���� � �������������������� ��� ������, �������� �������������� ��������

			//�������� ����� ����� �� ���������
			itIntervalPos=m_IntervalPositions.begin();
			//����������� ������� ��� ������ ����� ���������
			IntervalPos=m_IntervalPositions.begin()->second;
			
			//�������� � ������ ����� ����� �������-�������� ��� ���������� ���������
			IntervalPos.m_uiIndexPosition=IntervalPos.m_pCommonPositions->CurrentPositionsPopFront();
			
			//�������� ������� ���������
			LeftIntervalPos=m_IntervalPositions.begin()->second;
			RightIntervalPos=(--m_IntervalPositions.end())->second;
			
			//���������...
			if(IntervalPos.m_uiIndexPosition>RightIntervalPos.m_uiIndexPosition)
			{
				//���� ��������� ������� ������� �������� ��������� 
				//������ ������� ���������� �������� ��������, �� ������� �������� - �����������
				//������ �������� � ����������
				AddInterval(LeftIntervalPos.m_uiIndexPosition, RightIntervalPos.m_uiIndexPosition);
			}else{
				//���� ��������� ������� ������� �������� ��������� 
				//�� ������ ������� ���������� �������� ��������, �� ������� �������� �� ����������� 
				//������ ����� �������� � ������� �������-���������

				//��������� �������� �� ������ �������-�������� ������������������ ���� � ���������
				if(m_SequenceCollection.IsSequencesBreaked(&IntervalPos))
				{
					//���� �������� ������� ����������� ������� ��������
					//������ �������� � ����������
					AddInterval(LeftIntervalPos.m_uiIndexPosition, RightIntervalPos.m_uiIndexPosition);
				}
				//���� �� �������� ��������� �������� ������ �������-���������
			}
		
			//��������� �������� ������ ������� ��������� �� �������-�������� 
			if(!ReplaceIntervalPosition(itIntervalPos->second.m_pCommonPositions, 
				&itIntervalPos, IntervalPos.m_uiIndexPosition)) break;
		}
		//�������� ������
	}

	}catch(...){
		TO_CONSOLE(L"Evaluation error!!!");
		ToConsole(L"uiStep", uiStep);
		throw;
	}
}

void CProximityEvaluator_Text::Evaluate(unsigned int uiEvalID)
{
	//	���������� ������ ��� ����
	//CalcSequencesSizes();

	unsigned char ucStep=0;
	try{
		bool bResult=false;
		ucStep=0;
		
		unsigned int uiDocumentIndex=m_uiDocumentBasisIndex+uiEvalID;
		//ToConsole(L"EvalID", uiEvalID);
		//ToConsole(L"Evaluator", GetCollectionID());
		//ToConsole(L"DocumentIndex", uiDocumentIndex);
		
		//���������������� � �����������, 
		//��������� ������������� �� ������ �������� ���� � ���������
		//�� ������� ����� ��������� ��������� ��������� ����������, � ��������� ������� ����� ���������� ��������
		START_TICK(L"CProximityEvaluator_Text::PrepareEvaluation");		
		bResult=PrepareEvaluation(uiEvalID);
		STOP_TICK(L"CProximityEvaluator_Text::PrepareEvaluation");		
		if(!bResult) return;
		
		m_uiGoodIntervalsNumber=0;
		//���������� ��������� ��������� ���������� ��������� ��������
		for(unsigned int uiIntervalIndex=0; uiIntervalIndex<m_EvaledIntervalCollection.size(); uiIntervalIndex++){		
			//���������� ���������� ����
			//���������������� � ����������� 
			START_TICK(L"CProximityEvaluator_Text::PreparePositions");		
			bResult=PreparePositions(uiEvalID, uiIntervalIndex);
			STOP_TICK(L"CProximityEvaluator_Text::PreparePositions");		

			if(bResult){
				ucStep=1;
				//��������� ���������
				START_TICK(L"CProximityEvaluator_Text::Evaluate");		
				EvaluateIntervals();
				STOP_TICK(L"CProximityEvaluator_Text::Evaluate");		
			}			
			
			//���� ���������� ������� ���������� ��������� ����� ��������� ����������
			if(m_uiGoodIntervalsNumber>=m_uiGoodIntervalsLimitNumber) return;
		}

		//ucStep=2;
		////���������� ���������
		//ViewIntervalCollection();
		
	}catch(...){
		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"InitEvaluation");
			break;
		case 1:
			wcscpy(buf, L"Evaluate");
			break;
		case 2:
			wcscpy(buf, L"ViewIntervalCollection");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		}

		ERR_TO_CONSOLE(erTryCatch, buf);
		throw;
	}
}

void CProximityEvaluator_Text::ViewIntervalPositions(void)
{
	ToConsole(L"//----------------CProximityEvaluator_Text");

	if(m_IntervalPositions.empty()){
		ToConsole(L"IntervalPositions is empty!!!");
	}else{
		wstring wszValue;
		wchar_t buf[50]=L"";
		TIntervalPositions::iterator itIntPos=m_IntervalPositions.begin();
		do{
			//wsprintf(buf, L"P:%u-ID:%u ", itIntPos->m_uiIndexPosition, itIntPos->m_pCommonPositions->GetID());
			wsprintf(buf, L"%u ", itIntPos->second.m_uiIndexPosition);
			wszValue.append(buf);
		}while(++itIntPos!=m_IntervalPositions.end());
		ToConsole(wszValue.c_str());
	}

	ToConsole(L"//----------------Eof-CProximityEvaluator_Text");
}

//--------------------------------------------------------------------//

}
}
}
}
}
}
