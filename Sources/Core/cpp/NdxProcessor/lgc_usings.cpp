#include "StdAfx.h"
#include ".\lgc_usings.h"
#include ".\arg_res.h"

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

using namespace SS::Core::NdxSE::NdxProcessor::Extracting;

//--------------------------------------------------------------------//

CCompositeLogic::CCompositeLogic(void)
{
}

CCompositeLogic::~CCompositeLogic(void)
{
	//������� ������
	while(!m_LogicCollection.empty()){
		if(m_LogicCollection.back())
			delete m_LogicCollection.back();
		m_LogicCollection.pop_back();
	}
}

void CCompositeLogic::Init(CResultArgument* pResultArgument)
{
	if(ISNULL(pResultArgument)) return;
	
	//������ ������
	TLogicCollection::iterator itLogic=m_LogicCollection.begin();
	while(itLogic!=m_LogicCollection.end()){
		if((*itLogic)){
			//���� �� ����� ���������� ��������� �����������, ������� ������ ��� ����������
			(*itLogic)->Init(pResultArgument);
		}		
		itLogic++;
	}
}

void CCompositeLogic::SetIdleCalculation(void)
{
	TLogicCollection::iterator itLogic=m_LogicCollection.begin();
	while(itLogic!=m_LogicCollection.end()){
		if((*itLogic)){
			//������� ������ ��� ��������� �������
			(*itLogic)->SetIdleCalculation();
		}
		itLogic++;
	}
}

void CCompositeLogic::UnsetIdleCalculation(void)
{
	TLogicCollection::iterator itLogic=m_LogicCollection.begin();
	while(itLogic!=m_LogicCollection.end()){
		if((*itLogic)){
			//���������� ����� ��������� �������
			(*itLogic)->UnsetIdleCalculation();
		}
		itLogic++;
	}
}

void CCompositeLogic::AddLogic(CLogic* pLogic)
{
	if(ISNULL(pLogic)) return;

	//��������� ������
	m_LogicCollection.push_back(pLogic);
}

CComplexValue* CCompositeLogic::CreateComplexValue(void)
{
	//������� ������� ��������
	CComplexValue* pComplexValue=new CComplexValue();
	
	if(ISNULL(pComplexValue)) return NULL;

	TLogicCollection::iterator itLogic=m_LogicCollection.begin();
	while(itLogic!=m_LogicCollection.end()){
		if(ISNULL((*itLogic))) break;
		
		//��������� �������� ������
		pComplexValue->AddLogic(*itLogic);

		itLogic++;
	}
	
	AddToValuesCollection(pComplexValue);

	return pComplexValue;
}

//--------------------------------------------------------------------//

}
}
}
}
}
}