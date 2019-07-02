#pragma once
#include ".\basis_containers.h"
#include ".\consoleclient.h"
#include ".\const.h"
#include "..\ASCInterface\ICommonContainers.h"

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

///����� ������� ���������� ���������� �� �������� �� ����������
typedef vector<SS::Core::NdxSE::NdxProcessor::Containers::TValuePtrsBuffer*> TArgumentsValuesBuffer;

//--------------------------------------------------------------------//

///�������� - ������ �������� � ���� ���
class CArgument : public CConsoleClient
{
public:
	CArgument(unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, float fKoeff = 1.0, SS::Interface::Core::CommonContainers::SQueryIndexAttributes ArgumentAttributes = SS::Interface::Core::CommonContainers::SQueryIndexAttributes());
	virtual ~CArgument(void);
	
	///������������� �������� ���������
	virtual void SetValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue){m_pCurrentValue=pValue;};
	///���������� �������� ���������
	virtual SS::Core::NdxSE::NdxProcessor::Containers::CValue* GetValue(void){return m_pCurrentValue;};
	///���������� ������������� ���������
	unsigned int GetArgumentID(void){return m_uiArgumentID;};
	///���������� ����������� ��� ���������
	float GetKoeff(void){return m_fKoeff;}
	///������������� ����������� ��� ���������
	void SetKoeff(float fKoeff){m_fKoeff=fKoeff;}
	///���������� ���������
	SS::Interface::Core::CommonContainers::SQueryIndexAttributes GetAttributes(void){return m_Attributes;};
	///������������� ���������
	void SetAttributes(SS::Interface::Core::CommonContainers::SQueryIndexAttributes Value){m_Attributes=Value;};

	///������������ � ������
	void ToString(wstring& szValue);

protected:
	///������������� ���������
	const unsigned int m_uiArgumentID;
	///����������� ��� ���������
	float m_fKoeff;
	///������� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* m_pCurrentValue;
	///��������� ��������
	SS::Interface::Core::CommonContainers::SQueryIndexAttributes m_Attributes;
};

//--------------------------------------------------------------------//

///�������� - ������ ������� �������� � ���� ��� ���
class CArgumentEx : public CArgument
{
public:
	typedef vector<float> TValueOrtsWeightsCollection;

	CArgumentEx(unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, float fKoeff = 1.0, SS::Interface::Core::CommonContainers::SQueryIndexAttributes ArgumentAttributes = SS::Interface::Core::CommonContainers::SQueryIndexAttributes());
	virtual ~CArgumentEx(void);

	///������������� �������� ���������
	void SetValue(SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* pValue);
	///���������� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* GetValue(void){return (SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue*)m_pCurrentValue;};
	///���������� ��������� ����� ����� ����������� �������� ���������
	TValueOrtsWeightsCollection* GetValueOrtsWeights(void);

	///������������ � ������
	void ToString(wstring& szValue);

protected:
	///������������� �������� ���������
	void SetValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue){m_pCurrentValue=pValue;};

	///��������� ����� ����� �������� ���������, ������ � ���� �� ������ ����
	TValueOrtsWeightsCollection* m_pValueOrtsWeights;	
};

//--------------------------------------------------------------------//

class CComplexArgument;

///���� ��������-��������
class CArgValuesPair
{
public:
	CArgValuesPair(CComplexArgument* pArgument, SS::Core::NdxSE::NdxProcessor::Containers::CValuesContainer* pValuesContainer)
		:m_pArgument(pArgument), m_pValuesContainer(pValuesContainer), m_pLastUsedValue(NULL){};
	virtual ~CArgValuesPair(void)
	{
		//������� ��������� �������� 
		//��� ��� ��� ������ ������ �������,
		//�� �� ������ ��� ����������� �� ��������
		if(m_pValuesContainer){
			delete m_pValuesContainer;
			m_pValuesContainer=NULL;
		}
		m_pLastUsedValue=NULL;
	};
	
	///���������� ��������
	SS::Core::NdxSE::NdxProcessor::Containers::CValuesContainer* GetValuesContainer(void){return m_pValuesContainer;};
	///���������� ��������
	CComplexArgument* GetArgument(void){return m_pArgument;};
	///������������� ��������� ������������ �������� ����������
	void SetLastUsedValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue){m_pLastUsedValue=pValue;};
	///������������� ��������� ������������ �������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* GetLastUsedValue(void){return m_pLastUsedValue;};
	///���������� �������� ��������� ���������� �� ���������� �������������� ��������
	void SetFreshValues(SS::Core::NdxSE::NdxProcessor::Containers::TValuePtrsBuffer* pValuePtrsBuffer)
	{
		if(ISNULL(m_pValuesContainer)) return; 
		if(ISNULL(pValuePtrsBuffer)) return; 

		//START_TICK(L"SetFreshValues");
		m_pValuesContainer->SetFreshValues(m_pLastUsedValue, pValuePtrsBuffer);
		//STOP_TICK(L"SetFreshValues");
	};

protected:
	///��������
	CComplexArgument* m_pArgument;
	///��������� ��������
	SS::Core::NdxSE::NdxProcessor::Containers::CValuesContainer* m_pValuesContainer;
	///��������� ������������ �������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* m_pLastUsedValue;
};

typedef list<CArgValuesPair*> TArgValCollection;

//--------------------------------------------------------------------//

}
}
}
}
}
