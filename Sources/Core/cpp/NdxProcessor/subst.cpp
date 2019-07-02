#include "StdAfx.h"
#include ".\subst.h"
#include ".\console.h"

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

//--------------------------------------------------------------------//

CSubster::CSubster(void)
{
}

CSubster::~CSubster(void)
{
	Reset();

	//������� ��������� ���������� � ��������������� �� �������� ��������
	TArgValCollection::iterator itArgValues=m_ArgValCollection.begin();
	while(itArgValues!=m_ArgValCollection.end()){
		
		if((*itArgValues)){
			delete (*itArgValues);
		}
		++itArgValues;
	}
}

void CSubster::Reset(void)
{
	//������� ����
	m_ResultsStack.Clear();
}

void CSubster::IdleSubst(void)
{
	//� ����� �������� �� �����������, ���������� �������� � ���������� ����������
	TArgValCollection::iterator itArgValues=m_ArgValCollection.begin();
	while(itArgValues!=m_ArgValCollection.end()){
		if(ISNULL((*itArgValues))) break;
	
		//������� ��������� ���������� ������ ��������, ���� ��������� ����������		
		(*itArgValues)->GetArgument()->SetValue(NULL);

		++itArgValues;
	}
}

void CSubster::StartSubsting(void)
{
	//� ����� �������� �� �����������, ���������� �������� � ���������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::TValuePtrsBuffer ValuePtrsBuffer(1);
	TArgValCollection::iterator itArgValues=m_ArgValCollection.begin();
	while(itArgValues!=m_ArgValCollection.end()){
		
		if(ISNULL((*itArgValues))) break;
		
		//������� ��������� ���������� ������ ��������, ���� ��������� ����������		
		(*itArgValues)->SetFreshValues(&ValuePtrsBuffer);
		//(*itArgValues)->GetArgument()->SetValue(ValuePtrsBuffer.front());
		(*itArgValues)->GetArgument()->InitSourceValuesStack(ValuePtrsBuffer.front());
		(*itArgValues)->SetLastUsedValue(ValuePtrsBuffer.front());
		ValuePtrsBuffer[0]=NULL;	
		
		++itArgValues;
	}
}

bool CSubster::SubstValues()
{

	//���� ���� ������ � ����������� ������ �������
	if(m_ResultsStack.IsEmpty()) return false;
	
	if(ISNULL(m_ResultsStack.GetBackResult())) return false;
	
	//������� �� ����� ������������ ����������
	while(!m_ResultsStack.IsEmpty() && m_ResultsStack.GetBackResult()->GetCurrentEvalID()==EMPTY_VALUE){
		m_ResultsStack.PopBackResult();
		//������ � ��������� ������������ ����� ����������
		for(TArgValCollection::iterator itArgVal=m_ArgValCollection.begin(); itArgVal!=m_ArgValCollection.end(); itArgVal++){
			(*itArgVal)->GetArgument()->PopBackSourceValue();
		}
	}

	//m_ResultsStack.View();

	//���� ���� ������� ���... ����������� ������ �������
	if(m_ResultsStack.IsEmpty()) return false;
	
	////�������� ��� ������� ��������� ���������� �� ���������� �����������
	//m_ResultsStack.GetBackResult()->GetCurrentArgValueCollection()->TriggerArguments();

	return true;
}

void CSubster::EvaluateResult(CArgument* pResult)
{
	//�������� ������� �������� ���������� � ������������ �� �� �������� ����������
	if(!m_ResultsStack.IsEmpty()){
		if(ISNULL(m_ResultsStack.GetBackResult())) return;
		if(m_ResultsStack.GetBackResult()->GetCurrentEvalID()==EMPTY_VALUE) return;
		
		m_ResultsStack.GetBackResult()->MoveNextEvalID();
	}

	if(pResult){
		//���� ������� ��������� ��������
		//������� ����� ��������� ����� � ��������� ��������� � ����	
		m_ResultsStack.PushBackResult(new CResult(pResult));
	}else{
		//���� ������� ��������� �� ��������, ����� �������� ��������� �������� �� ������ ����������
		for(TArgValCollection::iterator itArgVal=m_ArgValCollection.begin(); itArgVal!=m_ArgValCollection.end(); itArgVal++){
			(*itArgVal)->GetArgument()->PopBackSourceValue();
		}
	}
}

void CSubster::View(void)
{
	ToConsole(L"//-----------------Subster:");

	ViewArgValCollection();
	m_ResultsStack.View();

	ToConsole(L"//-------------End-of-Subster");
}

void CSubster::ViewArgValCollection(void)
{
	wstring szValue(L"");
	wstring szOffset(L"");
	szValue.reserve(1000);
	szValue.reserve(100);

	szValue.append(L"//-ArgValCollection:");
	
	for(TArgValCollection::iterator itArgVal=m_ArgValCollection.begin(); itArgVal!=m_ArgValCollection.end(); itArgVal++){
		szValue.append(L"\n\t");
		(*itArgVal)->GetArgument()->ToString(szValue);
		szValue.append(L"\n\t");
		(*itArgVal)->GetValuesContainer()->ToString(szValue);
	}
	szValue.append(L"//-End-of-ArgValCollection:");
	ToConsole(szValue.c_str());
}

//--------------------------------------------------------------------//

}
}
}
}
}