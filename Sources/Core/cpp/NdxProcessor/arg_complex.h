#pragma once

#include ".\arg.h"
#include ".\logic.h"

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

class CComplexArgument;
class CResultArgument;

//--------------------------------------------------------------------//

///������� ��������, �������� ��������� �������� �� �������
class CComplexValue : public SS::Core::NdxSE::NdxProcessor::Containers::CValue
{
public:
	typedef vector< pair<SS::Core::NdxSE::NdxProcessor::Extracting::Logics::CLogic*, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue*> > TLogicValuesCollection;
	
	CComplexValue(void);
	virtual ~CComplexValue(void);

	///��������� ��������� ������ � ��������
	void AddLogic(SS::Core::NdxSE::NdxProcessor::Extracting::Logics::CLogic* pLogic);
	///��������� ������� �������� �� ��������
	void FillComplexValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, 
		CComplexArgument* pComplexArgument);
	///��������� ��������-���������
	void FillResultArgument(CResultArgument* pResultArgument);
	///���������� �������� �� ������
	void Reset(void);
	///���������� �������� �� �������������� ������
	Containers::CValue* GetValueByLogic(Logics::CLogic::ELogicID LogicID);

	///��������� �������� � ����������� � ����������
	static void Calculate(CComplexValue* pChangedValue, CComplexValue* pValue, 
		SS::Core::NdxSE::NdxProcessor::Extracting::Logics::CLogic::EOperator Operator);

	///���������� ���������� ������� ������
	void View(void);
	
protected:
	///��������� �������� �����, ������ � ��������� �� �������������� ������
	TLogicValuesCollection m_LogicValuesCollection;
};

//--------------------------------------------------------------------//

///�������� - ������ ������� ��������, ������������ � CCalcArgument
class CComplexArgument : public CArgument
{
public:
	CComplexArgument(unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, float fKoeff = 1.0, SS::Interface::Core::CommonContainers::SQueryIndexAttributes ArgumentAttributes = SS::Interface::Core::CommonContainers::SQueryIndexAttributes());
	virtual ~CComplexArgument(void);

	///������������� �������� ���������
	void SetComplexValue(CComplexValue* pValue);
	///������������� �������� ���������, �� ����� ������� ��������
	/**�� ���� ��������� �������, ��� ������� ������������ Subster'��,
	����� �� ����������� �������� ���������� �������*/
	void SetValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue);
	///���������� �������� ���������
	CComplexValue* GetValue(void){return (CComplexValue*)m_pCurrentValue;};
	///��������� ��������-���������
	void FillResultArgument(CResultArgument* pResultArgument);

	///���������� ��������� ��������
	Containers::CValue* GetStartValue(void){return m_pStartValue;};
	///���������� ��������� � ����� ��������-��������
	Containers::CValue* GetBackSourceValue(void){return m_SourceValuesStack.empty()?NULL:m_SourceValuesStack.back();};
	///����������� �� ����� ������� ��������
	void PopBackSourceValue(void);
	///������ � ���� ��������-��������
	void PushBackSourceValue(Containers::CValue* pValue);
	///��������� ���� ��������-���������� �� ������� 
	bool IsEmptySourceValuesStack(void){return m_SourceValuesStack.empty();};
	///������ ���� ��������-����������, ������������� ��������� ��������
	void InitSourceValuesStack(Containers::CValue* pValue);

	///���������� ������������� �����
	unsigned int GetBlockID(void){return m_uiBlockID;};
	///������������� ������������� �����
	void SetBlockID(unsigned int uiValue){m_uiBlockID=uiValue;};

protected:
	typedef list<Containers::CValue*> TValuesStack;

	///���� ��������-����������, ������� �������� ����� �������� ���������� �����������
	TValuesStack m_SourceValuesStack;
	///��������� ��������, �������� � �������� ���������� ����������
	Containers::CValue* m_pStartValue;
	///������������� �����
	unsigned int m_uiBlockID;
};

//--------------------------------------------------------------------//

}
}
}
}
}