#include "StdAfx.h"
#include ".\f_logic.h"
#include ".\arg_res.h"
#include ".\acc_containers.h"
#include ".\arg_complex.h"

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

CFuzzyLogic::CFuzzyLogic(void)
:CLogic(CLogic::elFuzzy), m_fBeta((float)0.7), m_fThreshold((float)0.7)
{
}

CFuzzyLogic::CFuzzyLogic(ELogicID LogicID)
:CLogic(LogicID), m_fBeta((float)0.7), m_fThreshold((float)0.7)
{
}

CFuzzyLogic::~CFuzzyLogic(void)
{
}

CValue* CFuzzyLogic::CreateLogicValue(CValue* pValue, CComplexArgument* pComplexArgument)
{
	//������ ��������� �� ����������
	if(!IsActive()) return NULL;

	if(ISNULL(pValue)) return NULL;

	CCompositeValue* pCompositeValue=(CCompositeValue*)pValue;
	if(ISNULL(pCompositeValue)) return NULL;

	CAccumulator* pAccumulator=new CAccumulator(pCompositeValue->GetOrtsMaxNumber());
	pAccumulator->m_uinMean++;
	
	//��� �������� ���������
	float fArgumentWeight=pComplexArgument->GetKoeff();

	if(pCompositeValue->MoveFirstOrt()) 
	{
		//������� ��� ��������
		unsigned int uiCurrentOrt=0;
		do{ 
			uiCurrentOrt=pCompositeValue->GetCurrentOrt();
			
			//��������� �����������
			pAccumulator->m_vfMean[uiCurrentOrt]=
				pAccumulator->m_vfMean[uiCurrentOrt]+fArgumentWeight;
			if(pAccumulator->m_vfMax[uiCurrentOrt]<fArgumentWeight) 
				pAccumulator->m_vfMax[uiCurrentOrt]=fArgumentWeight;
		}while(pCompositeValue->MoveNextOrt());
	}

	return pAccumulator;
}

void CFuzzyLogic::ToResultValue(CValue* pValue, CResultArgument* pResultArgument)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	if(ISNULL(pValue)) return;
	if(ISNULL(pResultArgument)) return;
	if(ISNULL(pResultArgument->GetMyself())) return;
	if(ISNULL(pResultArgument->GetMyself()->GetValue())) return;

	//�������� �������� ����������
	CCompositeValue* pCompositeValue=pResultArgument->GetMyself()->GetValue();
	//�������� ������������ � ������������ ������
	CAccumulator* pAccumulator=static_cast<CAccumulator*>(pValue);
	
	//��������� �� ���������� ��������
	if(pAccumulator->m_vfMean.size()!=pCompositeValue->GetOrtsMaxNumber()){
		TO_CONSOLE(L"Accumulator and CompositeValue size not equal");
		return;
	}

	//� ����� �������� �� ������ ������������
	for(unsigned int uiCurrentOrt=0; uiCurrentOrt<pAccumulator->m_vfMean.size(); uiCurrentOrt++){
		if(pAccumulator->m_vfMean[uiCurrentOrt]>m_fThreshold){
			//���� ��� ������ ������ ���������� ���	
			pCompositeValue->SetOrt(uiCurrentOrt);
		}
	}
}

void CFuzzyLogic::MakeAnd(CValue** ppChangedValue, CValue** ppValue)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	if(ISNULL(ppChangedValue)) return;
	if(ISNULL(ppValue)) return;

	//���� ��� �� ������� �� �� �� ������
	if(!(*ppChangedValue) && !(*ppValue)) return;

	if((*ppChangedValue) && (*ppValue)){
		//���� ��� �������� ������� ��������� ��������
		((CAccumulator*)(*ppValue))->EvalA4ANDFromAccumulator(m_fBeta);
		((CAccumulator*)(*ppChangedValue))->MergeAccumulators(*((CAccumulator*)(*ppValue)));
	}else if(!(*ppValue)){
		//���� ������ ���������� �������� �������, ���������� ���� ��������

	}else if(!(*ppChangedValue)){
		//���� ������ ���������� �������� �� �������, 
		//������ ������������ �������� � ���������� ���
		(*ppChangedValue)=(*ppValue);
		(*ppValue)=NULL;
	}
}

void CFuzzyLogic::MakeOr(CValue** ppChangedValue, CValue** ppValue)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	//���� ������������ �������� �� ������� �� �� �� ������ 
	if(ISNULL(ppChangedValue)) return;
	if(ISNULL(ppValue)) return;

	//���� ��� �� ������� �� �� �� ������
	if(!(*ppValue)) return;

	if((*ppChangedValue) && (*ppValue)){
		//���� ��� �������� ������� ��������� ��������
		((CAccumulator*)(*ppValue))->EvalA4ORFromAccumulator(m_fBeta);
		((CAccumulator*)(*ppChangedValue))->MergeAccumulators(*((CAccumulator*)(*ppValue)));
	}else if(!(*ppChangedValue)){
		//���� ������ ���������� �������� �� �������, 
		//������ ������������ �������� � ���������� ���
		(*ppChangedValue)=(*ppValue);
		(*ppValue)=NULL;
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}
}