#pragma once
#include ".\eq.h"
#include ".\arg_calc.h"

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
 
///������� �������, �������� ��� ��������� ������ ���������
///��������� � ����� �����������, � ����� ����� ����� ����������� �� �
class CBlockEquation : public CFactoryClient<CEvalFactory>, public CConsoleClient
{
public:
	CBlockEquation(CEvalFactory* pEvalFactory);
	virtual ~CBlockEquation(void);
	
	//--------������������ �������
	///��������� � ������� ��������� �-����
	virtual void AddAndBlock(void);
	///��������� � ������� ��������� ���-����
	virtual void AddOrBlock(void);
	///��������� � ������� ����������� ���� ������ ����������
	virtual void AddGroup(CArgumentsGroup* pArgumentsGroup);
	//----------------------------

	///��������� �������� �� ����������
	virtual void Calculate(CResultArgument* pResult);
	///���������� ������ ������������ � �����������
	Logics::CCompositeLogic* GetEquationLogic(void){return m_pEquationLogic;};

	///������� ������� � ������
	void IdlePreCalculate(void)
	{
		if(ISNULL(m_pEquationLogic)) return;
		//������� ������ � ��������� �������
		m_pEquationLogic->SetIdleCalculation();
	};

	///��������� ������ ��� ���������� ��������
	void IdleCalculate(void)
	{
		if(ISNULL(m_pEquationLogic)) return;
		//���������� �������� ������ � �����
		m_pEquationLogic->UnsetIdleCalculation();
	};

	///������������� ������ ������ ������� ��� ������ � ������ ����������� �����������
	void PreCalculate(CResultArgument* pResult)
	{
		if(ISNULL(pResult)) return;
		//������ ������
		m_pEquationLogic->Init(pResult);
	};


	///������������ � ������
	void ToString(wstring& wszValue);

protected:
	typedef vector<CCalcBlock*> TCalcBlockCollection;
	
	///�-���� �������
	CCalcBlock* m_pANDBlock;
	///��������� ���-������ �������
	TCalcBlockCollection m_ORBlockCollection;
	///������� ���� ������������ ��� ����������
	CCalcBlock* m_pCurrentBlock; 
	///������ ������������ � �����������
	Logics::CCompositeLogic* m_pEquationLogic;
};

//--------------------------------------------------------------------//

///������� �������, � ������� ��� ������ ���������� ����������� �� ���
///��� ����� ������ ������ �������� � ��������� ���-����
class CBlockOREquation : public CBlockEquation
{
public:
	CBlockOREquation(CEvalFactory* pEvalFactory):CBlockEquation(pEvalFactory){};
	virtual ~CBlockOREquation(void){};

	//--------������������ �������
	///��������� � ������� ��������� �-����
	void AddAndBlock(void){};
	///��������� � ������� ��������� ���-����
	void AddOrBlock(void){};
	///��������� � ������� ����������� ���� ������ ����������
	void AddGroup(CArgumentsGroup* pArgumentsGroup);
	//----------------------------
};

//--------------------------------------------------------------------//

///������� �������, � ������� ��� ������ ���������� ����������� �� �
///��� ����� ��� ������ �������� � ���� �-����, � ���-������ ��� ������
class CBlockANDEquation : public CBlockEquation
{
public:
	CBlockANDEquation(CEvalFactory* pEvalFactory):CBlockEquation(pEvalFactory){};
	virtual ~CBlockANDEquation(void){};

	//--------������������ �������
	///��������� � ������� ��������� �-����
	void AddAndBlock(void){};
	///��������� � ������� ��������� ���-����
	void AddOrBlock(void){};
	///��������� � ������� ����������� ���� ������ ����������
	void AddGroup(CArgumentsGroup* pArgumentsGroup);
	//----------------------------
};

//--------------------------------------------------------------------//

}
}
}
}
}