#pragma once

#include ".\consoleclient.h"
#include ".\lgc_usings.h"
#include ".\ev_factory.h"

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

///������� - ��������� ����������, ��������� � ������
template <class TArgument, class TResult>
class CEquation : public CFactoryClient<CEvalFactory>, public CConsoleClient
{
public:
	CEquation(CEvalFactory* pEvalFactory, TArgument* pRootArgument)
		:CFactoryClient<CEvalFactory>(pEvalFactory), m_pRootArgument(pRootArgument), m_pEquationLogic(NULL)
	{
	};

	virtual ~CEquation(void)
	{
		if(m_pRootArgument)
			delete m_pRootArgument;

		if(m_pEquationLogic)
			delete m_pEquationLogic;
	};
	
	///������� ������� � ������
	void IdlePreCalculate(void)
	{
		if(ISNULL(m_pRootArgument)) return;
		if(ISNULL(m_pEquationLogic)) return;
		
		//������� ������ � ��������� �������
		m_pEquationLogic->SetIdleCalculation();
	};

	///��������� ������ ��� ���������� ��������
	void IdleCalculate(void)
	{
		if(ISNULL(m_pRootArgument)) return;
		if(ISNULL(m_pEquationLogic)) return;
		
		//��������� �������� ����������
		m_pRootArgument->Calculate(NULL);

		//���������� �������� ������ � �����
		m_pEquationLogic->UnsetIdleCalculation();
	};

	///������������� ������ ������ ������� ��� ������ � ������ ����������� �����������
	void PreCalculate(TResult* pResult)
	{
		if(ISNULL(pResult)) return;
		if(ISNULL(m_pRootArgument)) return;
		if(ISNULL(m_pEquationLogic)) return;
		
		//������ ������
		m_pEquationLogic->Init(pResult);
	};

	///��������� �������� �� ����������
	void Calculate(TResult* pResult)
	{
		if(ISNULL(pResult)) return;
		if(ISNULL(m_pRootArgument)) return;
		if(ISNULL(m_pEquationLogic)) return;
		
		//��������� ����������
		m_pRootArgument->Calculate(pResult);
	};

	///���������� �������� �������� �������
	TArgument* GetRootArgument(void){return m_pRootArgument;};
	///���������� ������ ������ �������
	Logics::CCompositeLogic* GetEquationLogic(void){return m_pEquationLogic;};

	///���������� ���������� ������� ������
	void View(void)
	{
		wstring szValue;
		wstring szOffset;
		
		//������� ������
		ToConsole(L"//----------Equation:");
		szValue.reserve(1000);
		szOffset.reserve(100);
		if(m_pRootArgument)
			m_pRootArgument->ToString(szValue, szOffset);

		ToConsole(szValue.c_str());
		ToConsole(L"//------End-of-Equation");
	}

protected:
	///�������� �������� �������
	TArgument* m_pRootArgument;
	///������ ������������ �������� � �����������
	Logics::CCompositeLogic* m_pEquationLogic;
};

//--------------------------------------------------------------------//

}
}
}
}
}