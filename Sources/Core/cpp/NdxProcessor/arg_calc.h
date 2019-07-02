#pragma once

#include ".\arg.h"
#include ".\logic.h"
#include ".\node_containers.h"
#include ".\arg_complex.h"
#include ".\lgc_usings.h"

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

class CCalcEquation;
 
//--------------------------------------------------------------------//

///�������� �������������� ��� ���������� ���������� ���������
class CCalcArgument : public SS::Core::NdxSE::NdxProcessor::Containers::CBinTreeNode<CComplexArgument*>
{
public:
	CCalcArgument(CCalcEquation* pOwnerEquation, 
		unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, 
		Logics::CLogic::EOperator Operator = Logics::CLogic::eoUndefined, 
		float fKoeff = 1.0, 
		SS::Interface::Core::CommonContainers::SQueryIndexAttributes ArgumentAttributes = SS::Interface::Core::CommonContainers::SQueryIndexAttributes());
	virtual ~CCalcArgument(void);

	///��������� �������� ����� 
	void Calculate(CResultArgument* pResult);
	///��������� ������� ������� ����
	CCalcArgument* AddChild(CCalcArgument* pChildArgument);
	///���������� ������������ ����
	CCalcArgument* GetParent(void){return ((CCalcArgument*)(SS::Core::NdxSE::NdxProcessor::Containers::CBinTreeNode<CComplexArgument*>::GetParent()));};
	///���������� ������ �������
	CCalcArgument* GetLeftChild(void){return ((CCalcArgument*)(SS::Core::NdxSE::NdxProcessor::Containers::CBinTreeNode<CComplexArgument*>::GetLeftChild()));};
	///���������� ������� �������
	CCalcArgument* GetRightChild(void){return ((CCalcArgument*)(SS::Core::NdxSE::NdxProcessor::Containers::CBinTreeNode<CComplexArgument*>::GetRightChild()));};

	///������������� �������� ���������
	void SetOperator(Logics::CLogic::EOperator Operator){m_Operator=Operator;};
	///������������� �������� ��������� �� ������
	void SetOperator(wstring& szValue){SetOperator(GetOperator(szValue));};
	///���������� �������� ���������
	Logics::CLogic::EOperator GetOperator(void){return m_Operator;};
	///���������� �������� �� ������
	Logics::CLogic::EOperator GetOperator(wstring& szValue);
	///��������� ���������� ��������� ��������� �� �������
	bool IsOperatorPriorityNotHigher(Logics::CLogic::EOperator Operator);
	///��������� ���������� ��������� ��������� �� �������
	bool IsOperatorPriorityNotHigher(wstring& szValue);
	///��������� �������� � ������
	CCalcArgument* InsertCalcArgument(unsigned int uiArgumentID, Logics::CLogic::EOperator Operator, float fWeight, SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attributes, CCalcArgument** ppInsertedArgument);
	///��������� �������� � ������
	CCalcArgument* InsertCalcArgument(wstring* pszArgument, float fWeight = 1.0, SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attributes = SS::Interface::Core::CommonContainers::SQueryIndexAttributes());
	///��������� �������� �� �������������
	bool IsArgumentIntermediate(void){return (m_pMyself->GetArgumentID()==SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE)?true:false;};
	///��������� �������� �� �������� ������
	bool IsSpare(void);
	///������������ ����� �����-����������
	void OptimizeCalcEquation(void);

	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);

protected:
	///�������� �� �������� ��������� ����
	Logics::CLogic::EOperator m_Operator;
	//������� �������� ���������
	CCalcEquation* m_pOwnerEquation;
};

//--------------------------------------------------------------------//

///������ ����������, �������� ��������� ���������
///��� ���������� �������� ���������� ������������ �� ���
class  CArgumentsGroup : public CConsoleClient
{
public:
	CArgumentsGroup(unsigned int uiID, Logics::CCompositeLogic* pEquationLogic, bool bObligatory)
		:m_pEquationLogic(pEquationLogic), m_fTotalArgWeight(0.0), m_uiID(uiID), m_bObligatory(bObligatory){};
	~CArgumentsGroup(void);

	///���������� ��� ������
	float GetWeight(void); 
	///��������� �������� � ������
	CComplexArgument* AddArgument(unsigned int uiArgumentID, float fWeight, SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attributes);
	///��������� �������� ������ ����������
	void Calculate(unsigned int uiEvalID, CComplexValue* pResultValue);
	///��������� ������ �� ������������ ���������� ������, ������������ � �������
	void SynhronizeArguments(void);
	///��������� �� �������
	bool IsEmpty(void){return m_ArgumentCollection.empty();};
	///���������� ������������� ������
	unsigned int GetID(void){return m_uiID;};
	///���������� ���� �������������� ������
	bool GetObligatory(void){return m_bObligatory;};

	///������������ � ������
	void ToString(wstring& szValue);

protected:
	typedef vector<CComplexArgument*> TArgumentCollection;

	///������ ������������ � �����������
	Logics::CCompositeLogic* m_pEquationLogic;
	///��������� ���������� ������
	TArgumentCollection m_ArgumentCollection;
	///����� ��� �����������
	float m_fTotalArgWeight;
	///������������� ������
	const unsigned int m_uiID;
	///���� �������������� ������
	const bool m_bObligatory;
};

//--------------------------------------------------------------------//

///�������������� ����, �������� ������ ���������� ������� �� �� �
///������ �������� ����� ������� ���������� ��� ��������� ����� ������ �����,
///� ������� ����������� ��� ���������� 
class CCalcBlock : public CConsoleClient
{
public:
	CCalcBlock(Logics::CCompositeLogic* pEquationLogic)
		:m_pEquationLogic(pEquationLogic){};
	virtual ~CCalcBlock(void);
	
	///��������� ������ ���������� � ����
	void AddGroup(CArgumentsGroup* pArgumentsGroup);
	///���������� ������ ������������ � �����������
	Logics::CCompositeLogic* GetEquationLogic(void){return m_pEquationLogic;};

	///��������� �������� ������ ����������
	void Calculate(unsigned int uiEvalID, CComplexValue* pResultValue);
	///��������� ������ �� ������������ ����������
	void SynhronizeArguments(void);

	///������������ � ������
	void ToString(wstring& wszValue);

protected:
	typedef map<unsigned int, CArgumentsGroup*> TArgGroupCollection;
	typedef list<CArgumentsGroup*> TArgGroupList;
	
	///������ ������������ � �����������
	Logics::CCompositeLogic* m_pEquationLogic;
	///��������� ����� �������
	TArgGroupCollection m_ArgGroupCollection;
	///��������� �� ������������� ����� �������
	TArgGroupList m_NotOblArgGroupCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}