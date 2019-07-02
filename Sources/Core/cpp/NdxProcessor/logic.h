#pragma once
#include ".\node_containers.h"
#include ".\consoleclient.h"
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
	class CComplexArgument;
}
}
}
}
}

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

//--------------------------------------------------------------------//

///���������� ������ �������� �� ����������
class CLogic : public CConsoleClient
{
public:
	///��������� ������������ �������
	enum EOperator
	{
		///�����������
		eoUndefined,		
		///"�"
		eoAND,		
		///"���"
		eoOR,		
		///���������
		eoNOT,
		///����� ������
		eoLeftBracket,
		///������ ������
		eoRightBracket,
		///���������
		eoReset,
		///�������� �� �������
		eoIsEmpty
	};

	///��������� �������������� �����
	enum ELogicID
	{
		///�������������
		elUndefined,
		///������ ������
		elBoolean,
		///������ ������� �������������
		elRelevance,
		///������ ����������
		elHeader,
		///fuzzy ������
		elFuzzy,
		///������ ���������� ���� ���������� �� �������
		elTextStatistic,
		///������ �������� �������� �� ������ �����������
		elSentenceAdjust,
	};

	CLogic(ELogicID LogicID = elUndefined)
		:m_LogicID(LogicID), m_bLogicActive(true), 
		m_uiActivationLevels(0), m_bIdleCalculation(false),
		m_ucLastActivationLevel(0), m_ucActivationLevelsNumber(0){};
	virtual ~CLogic(void){ClearValuesCollection();};

	///��������� �������� � ����������� � ����������
	void Calculate(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue, CLogic::EOperator Operator);
	///���������� ������������� ������
	ELogicID GetLogicID(void){return m_LogicID;};
	
	///������������� ������ ����� ������������
	virtual void Init(CResultArgument* pResultArgument);
	///�������� �������� ������ �� �������� ���������
	virtual SS::Core::NdxSE::NdxProcessor::Containers::CValue* 
		CreateLogicValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, 
		SS::Core::NdxSE::NdxProcessor::Extracting::CComplexArgument* pComplexArgument){TO_CONSOLE(L"Not ovveriden"); return NULL;};
	///�������� �������� ��������� �� �������� ������
	virtual void ToResultValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CResultArgument* pResultArgument){TO_CONSOLE(L"Not ovveriden");};

	///��������� ���������� ������
	virtual bool IsActive(void){return m_bLogicActive;};
	///������������� ������� ���������� ������
	void SetActivationLevel(unsigned char ucActivationLevel);
	///������������� ������� ���������� ������
	void SetActivationLevels(unsigned char ucActivationLevelFirst, unsigned char ucActivationLevelLast);
	///��������� �� ������� ���������� ������
	bool IsActivationLevel(unsigned char ucLevel);
	///���������� ���������� ������� ���������� ������
	unsigned char GetActivationLevelsNumber(void){return m_ucActivationLevelsNumber;};
	///���������� ����� ���������� ������ ���������� ������
	unsigned char GetLastActivationLevel(void){return m_ucLastActivationLevel;};

	///���������� ���� ��������� �������
	virtual void SetIdleCalculation(void){m_bIdleCalculation=true;};
	///���������� ���� ��������� �������
	virtual void UnsetIdleCalculation(void){m_bIdleCalculation=false;};
	///���������� ���� ��������� �������
	bool IsIdleCalculation(void){return m_bIdleCalculation;};

	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);

protected:
	typedef vector<SS::Core::NdxSE::NdxProcessor::Containers::CValue*> TCreatedValuesCollection;

	///��������� �������� AND
	virtual void MakeAnd(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue){TO_CONSOLE(L"Not ovveriden");};
	///��������� �������� OR
	virtual void MakeOr(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue){TO_CONSOLE(L"Not ovveriden");};
	///������� ��������� �������� ��������� �������
	void ClearValuesCollection(void);
	///������� ��������� �������� ��������� �������
	void AddToValuesCollection(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue);

	///������������� ������
	ELogicID m_LogicID;
	///���� ���������� ������
	bool m_bLogicActive;
	///������� ����� ������� ���������� ������ (�� ������ 32 �������)
	unsigned int m_uiActivationLevels;
	///����� ���������� ������ ���������� ������ 
	unsigned char m_ucLastActivationLevel;
	///���������� ������� ���������� ������ 
	unsigned char m_ucActivationLevelsNumber;
	///���� ��������� �������
	bool m_bIdleCalculation;
	///��������� �������� ��������� �������
	TCreatedValuesCollection m_CreatedValuesCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}