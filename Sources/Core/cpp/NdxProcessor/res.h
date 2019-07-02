#pragma once
#include ".\eq_res.h"
#include ".\ev_factory.h"
#include ".\consoleclient.h"
#include ".\res_check.h"
#include ".\index_storage.h"

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
class CResultsContainerWithCorrection;
class CResultsChecker;

///��������� ����������� - ������ ����������� �������
class CResultsContainer : public CFactoryClient<CEvalFactory>, public CConsoleClient
{
public:
	friend CResultsContainerWithCorrection;

	CResultsContainer(CEvalFactory* pEvalFactory, unsigned int uiGenerationLimitDepth = 0);
	virtual ~CResultsContainer(void);
	
	///���������� ��������� ������ ��������� ��� ����������
	virtual CResultArgument* GenerateResult(void);
	///��������� ��������� �� ������������
	virtual bool CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument);

	///���������� ��������� �����������
	CResultsChecker* GetResultsChecker(void){return m_pResultsChecker;};

	///���������� ���������� ������� ������
	void View(void);

protected:
	///������� �������� ��������� ��� �������� �� ����
	CResultArgument* CreateChildResult(CResultArgument* pParentResult, unsigned int uiOrt);

	///��������� �������
	CResultEquation* m_pDeriveEquation;
	///��������� �����������
	CResultsChecker* m_pResultsChecker;
	///��������� ������� ���������
	CResultArgument* m_pLastResult;
	///������� �������������� ���������� �����������
	const unsigned int m_uiGenerationLimitDepth;
};

//--------------------------------------------------------------------//

///��������� ����������� - � ������������� ��������� ������ �������������� �������
class CResultsContainerWithCorrection : public CResultsContainer
{
public:
	CResultsContainerWithCorrection(CEvalFactory* pEvalFactory, 
		SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* pIndexStorage,
		unsigned int uiGenerationLimitDepth = 0, 
		unsigned int uiCorrectionLimitDepth = 0);
	virtual ~CResultsContainerWithCorrection (void);
	
	///��������� �������������� ��������� (��������� ��������� � ������ � ��������� �������� ��������� ��������� ����)
	void AddCorrectionResult(unsigned int* pBuffer, unsigned int uiBufferSize);
	///����������� �� ������� ����������
	void CreateCorrectionTemplate(CResultsContainer* pResultsContainer);
	///���������� ��������� ������ ��������� ��� ����������
	CResultArgument* GenerateResult(void);
	///��������� ��������� �� ������������
	bool CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument);

protected:
	///���������� �� �������������� ���������
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* m_pIndexStorage;
	///������� �� ������� ��������� ���������
	const unsigned int m_uiCorrectionLimitDepth;
};

//--------------------------------------------------------------------//

///��������� ���������� � ����� �����������
class CResult : public CConsoleClient
{
public:
	typedef vector<unsigned int> TResultCollection;

	CResult(CArgument* pResultArgument);
	virtual ~CResult(void);

	///���������� ������� ��������� ��������-�������� 
	unsigned int GetCurrentEvalID(void);
	///��������� �� ��������� ���� ��������-��������
	bool MoveNextEvalID(void);

	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);

protected:
	///��� ����������� ���������
	CArgument* const m_pResultArgument;
	///��������� ��������� ��������-�������� �� ���������������
	TResultCollection m_ResultCollection;
	///������� ��������� ��������-��������
	TResultCollection::iterator m_itCurrResultValuesCollection;
	///��������� ��� ������������� ����������
	TResultCollection m_NullCollection;
};

//--------------------------------------------------------------------//

///���� �����������
class CResultsStack
{
public:
	typedef list<CResult*> TResultsStack;
	
	CResultsStack(void);
	virtual ~CResultsStack(void);
	
	///��������� ����� ��������� � �����
	void PushBackResult(CResult* pResult);
	///����������� ��������� �� ����� �����
	void PopBackResult(void);
	///���������� ��������� ���������
	CResult* GetBackResult(void);
	///��������� �� �������
	bool IsEmpty(void){return m_ResultsStack.empty();};
	///������� ����
	void Clear(void);

	///���������� ���������� ������� ������
	void View(void);

protected:
	///������ �����������
	TResultsStack m_ResultsStack;
};

//--------------------------------------------------------------------//

}
}
}
}
}