#include "StdAfx.h"
#include ".\b_logic.h"
#include ".\console.h"
#include ".\arg_res.h"
#include ".\arg_complex.h"
#include ".\box_containers_s.h"

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

using namespace SS::Core::NdxSE::NdxProcessor::Containers;

//--------------------------------------------------------------------//

CBooleanLogic::CBooleanLogic(void)
:CLogic(CLogic::elBoolean), m_fResultMaxWeight(0.0)
{
}

CBooleanLogic::CBooleanLogic(ELogicID LogicID)
:CLogic(LogicID), m_fResultMaxWeight(0.0)
{
}

CBooleanLogic::~CBooleanLogic(void)
{
}

CValue* CBooleanLogic::CreateLogicValue(CValue* pValue, CComplexArgument* pComplexArgument)
{
	if(ISNULL(pComplexArgument)) return NULL;
	CValue* pNewValue=NULL;

	if(IsIdleCalculation()){
		if(pValue){
			//������� �������� ����������� ������ ���� �� ��������
			TO_CONSOLE(L"pValue is valid in IdleCalculation");
			return NULL;
		}
		
		//������� ������� ��������
		pNewValue=new CValue();	
		//������������� ��� ��������
		pNewValue->SetValueWeight(pComplexArgument->GetKoeff());

	}else{
		if(pValue==NULL) return NULL;
		//������ ��������� �� ����������
		if(!IsActive()) return NULL;
		
		pNewValue=new CBitMap_4s(((CCompositeValue*)pValue)->GetOrtsMaxNumber());

		if(pNewValue){
			//������� ����� �� ��������
			pNewValue->MakeOr(pValue);
			//������������� ��� ��������
			pNewValue->SetValueWeight(pComplexArgument->GetKoeff());
		}
	}

	//���������� ������ ���� ���� ����� �������
	AddToValuesCollection(pNewValue);

	return pNewValue;
}

void CBooleanLogic::ToResultValue(CValue* pValue, CResultArgument* pResultArgument)
{
	if(IsIdleCalculation()){
		if(ISNULL(pValue)) return;

		//���� ��� �������� ������, �� � �������������� �������� ������������ ��� ��������� ���
		m_fResultMaxWeight=pValue->GetValueWeight();
		m_fResultMaxWeight=(m_fResultMaxWeight*GetActivationLevelsNumber());
		//char buf[50];
		//sprintf(buf, "ResultMaxWeight: %f", m_fResultMaxWeight);
		//ToConsole(buf);

	}else{

		//������ ��������� �� ����������
		if(!IsActive()) return;

		if(ISNULL(pResultArgument)) return;
		if(ISNULL(pResultArgument->GetMyself())) return;
		if(ISNULL(pResultArgument->GetMyself()->GetValue())) return;

		if(pValue){
			//�������� �������� ����������
			CCompositeValue* pCompositeValue=pResultArgument->GetMyself()->GetValue();

			//pValue->View();

			//��������� �������� � ����������
			if(pCompositeValue->IsEmpty())
				pCompositeValue->MakeOr(pValue);
			else
				pCompositeValue->MakeAnd(pValue);

			//��������� ���������� ��� ��������
			pResultArgument->GetMyself()->SetKoeff(
				pResultArgument->GetMyself()->GetKoeff()+pValue->GetValueWeight());

			if(pResultArgument->GetDepth()==GetLastActivationLevel()){
				///���� ��������� �������� ������� ��������� ��� � ���������� �� �������������
				pResultArgument->GetMyself()->SetKoeff(EvalResultWeight(pResultArgument->GetMyself()->GetKoeff()));
			}

			//char buf[50];
			//sprintf(buf, "ResultArgument: %f", pResultArgument->GetMyself()->GetKoeff());
			//ToConsole(buf);

			//pCompositeValue->View();
		}else{
			pResultArgument->GetMyself()->GetValue()->Reset();
		}
	}
	
	//������� ��������� ��������
	ClearValuesCollection();
}

void CBooleanLogic::MakeAnd(CValue** ppChangedValue, CValue** ppValue)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	if(ISNULL(ppChangedValue)) return;
	if(ISNULL(ppValue)) return;

	//���� ��� �� ������� �� �� �� ������
	if(!(*ppChangedValue) && !(*ppValue)) return;

	//START_TICK(L"CBooleanLogic::MakeAnd");

	if((*ppChangedValue) && (*ppValue)){
		//���� ��� �������� ������� ��������� ��������
		(*ppChangedValue)->MakeAnd((*ppValue));
	}else if(!(*ppValue)){
		//���� ������ ���������� �������� �������, ���������� ���� ��������
		(*ppChangedValue)->Reset();
	}else if(!(*ppChangedValue)){
		//���� ������ ���������� �������� �� �������, 
		//������ ������������ �������� � ���������� ���
		(*ppChangedValue)=(*ppValue);
		(*ppChangedValue)->Reset();
		(*ppValue)=NULL;
	}
	//STOP_TICK(L"CBooleanLogic::MakeAnd");
}

void CBooleanLogic::MakeOr(CValue** ppChangedValue, CValue** ppValue)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	if(ISNULL(ppChangedValue)) return;
	if(ISNULL(ppValue)) return;

	//���� ������������ �������� �� ������� �� �� �� ������ 
	if(!(*ppValue)) return;

	//START_TICK(L"CBooleanLogic::MakeOr");
	if((*ppChangedValue) && (*ppValue)){
		
		//ToConsole("Before");
		//(*ppChangedValue)->View();
		//(*ppValue)->View();
		//ToConsole("eof-Before");

		//���� ��� �������� ������� ��������� ��������
		(*ppChangedValue)->MakeOr((*ppValue));

		//ToConsole("After");
		//(*ppChangedValue)->View();
		//ToConsole("eof-After");

	}else if(!(*ppChangedValue)){
		//���� ������ ���������� �������� �� �������, 
		//������ ������������ ��������
		(*ppChangedValue)=(*ppValue);
		(*ppValue)=NULL;
	}

	//STOP_TICK(L"CBooleanLogic::MakeOr");
}

//--------------------------------------------------------------------//

CBooleanLogicWithSentencesAdjacent::CBooleanLogicWithSentencesAdjacent(int iSizeAdjacent/*, SSearchParameter::EAdjacentSearchIntervalType IntervalType*/)
:m_iSizeAdjacent(iSizeAdjacent)/*, 
m_IntervalType(IntervalType)*/
{
}

CBooleanLogicWithSentencesAdjacent::~CBooleanLogicWithSentencesAdjacent(void)
{
}

void CBooleanLogicWithSentencesAdjacent::MakeAnd(CValue** ppChangedValue, CValue** ppValue)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	//���� ��� �� ������� �� �� �� ������
	if(!(*ppChangedValue) && !(*ppValue)) return;

	if((*ppChangedValue) && (*ppValue)){
		//���� ��� �������� ������� ��������� ��������, �������� � ������ ���������
		(*ppChangedValue)->MakeSmoothAnd((*ppValue), (unsigned int)m_iSizeAdjacent);
	}else if(!(*ppValue)){
		//���� ������ ���������� �������� �������, ���������� ���� ��������
		(*ppChangedValue)->Reset();
	}else if(!(*ppChangedValue)){
		//���� ������ ���������� �������� �� �������, 
		//������ ������������ �������� � ���������� ���
		(*ppChangedValue)=(*ppValue);
		(*ppChangedValue)->Reset();
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}
}