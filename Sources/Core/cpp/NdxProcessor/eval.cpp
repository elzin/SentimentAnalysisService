#include "StdAfx.h"
#include ".\eval.h"
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


CEvaluator::CEvaluator(CEvalFactory* pEvalFactory)
:CFactoryClient<CEvalFactory>(pEvalFactory), 
m_pEquation(NULL), m_pSubster(NULL), 
m_pResultsContainer(NULL), m_pCurrResultArgument(NULL)
{
	m_pEquation=GetFactory()->CreateCalcEquation();
	m_pSubster=GetFactory()->CreateSubster();
	m_pResultsContainer=GetFactory()->CreateResultsContainer();
}


CEvaluator::~CEvaluator(void)
{
	if(m_pEquation) 
		delete m_pEquation;

	if(m_pSubster) 
		delete m_pSubster;

	if(m_pResultsContainer) 
		delete m_pResultsContainer;
}

CResultsContainer* CEvaluator::ExtractResultsContainer(void)
{
	CResultsContainer* pResultsContainer=m_pResultsContainer;
	m_pResultsContainer=NULL;
	return pResultsContainer;
}

void CEvaluator::Init(CESFiller* pESFiller)
{
	if(ISNULL(m_pEquation)) return;
	if(ISNULL(m_pSubster)) return;
	if(ISNULL(m_pResultsContainer)) return;
	if(ISNULL(pESFiller)) return;
	
	if(pESFiller->IsInited()){
		//��������� ������� � ������������ �����������
		pESFiller->Fill(m_pEquation, m_pSubster);
		m_pEquation->View();
		
		//�������������� �������, ������� � ��������� ������� 
		m_pEquation->IdlePreCalculate();
		//����������� ������ �������� ����������
		m_pSubster->IdleSubst();
		//�������� �������� ������
		m_pEquation->IdleCalculate();

	}else{
		TO_CONSOLE(L"ESFiller not inited!!!");
		
	}
}


bool CEvaluator::Calculate(void)
{
	if(ISNULL(m_pEquation)) return false;
	if(ISNULL(m_pSubster)) return false;
	if(ISNULL(m_pResultsContainer)) return false;

	bool bOk=false;
	CArgument* pTempArgument=NULL;
	unsigned char ucStep=0;
	
	try{

	//�������� ��������� ��������� ��� ����������
	//START_TICK(L"E_GenerateResult");
	ucStep=0;
	m_pCurrResultArgument=m_pResultsContainer->GenerateResult();
	//STOP_TICK(L"E_GenerateResult");

	//��������� ��������������
	//START_TICK(L"E_PreCalculate");
	ucStep=1;
	m_pEquation->PreCalculate(m_pCurrResultArgument);
	//STOP_TICK(L"E_PreCalculate");
	
	//��������� �����������
	//START_TICK(L"E_StartSubsting");
	ucStep=2;
	m_pSubster->StartSubsting();
	//STOP_TICK(L"E_StartSubsting");
	
	//� ����� ����������� �������� ��������� �������
	//� ���������� ����������, ���� ������������� ���� ��� �����������
	do{
		//m_pSubster->ViewResultsStack();
		//��������� ��������� ��������
		START_TICK(L"E_Calculate");
		ucStep=3;
		m_pEquation->Calculate(m_pCurrResultArgument);
		STOP_TICK(L"E_Calculate");
		
		//��������� ��������� 
		START_TICK(L"E_CheckResult");
		ucStep=4;
		if(!m_pResultsContainer->CheckResult(m_pCurrResultArgument, &pTempArgument)){
			//�� ����� ���������� ������������, ����� ���� ������������ ���������� ����������
			//m_pSubster->Reset();
			TO_CONSOLE(L"Calculation breaked!!!");
			break;
		}
		STOP_TICK(L"E_CheckResult");

		//���� ������������� ���������� ���������
		START_TICK(L"E_EvaluateResult");
		ucStep=5;
		m_pSubster->EvaluateResult(pTempArgument);
		STOP_TICK(L"E_EvaluateResult");
		
		//�������� ��������� ��������� ��� ����������
		START_TICK(L"E_GenerateResult");
		ucStep=6;
		m_pCurrResultArgument=m_pResultsContainer->GenerateResult();
		STOP_TICK(L"E_GenerateResult");

		//��������� ��������������
		START_TICK(L"E_PreCalculate");
		ucStep=7;
		if(m_pCurrResultArgument)
			m_pEquation->PreCalculate(m_pCurrResultArgument);
		STOP_TICK(L"E_PreCalculate");

		//����������� �������� � �������
		START_TICK(L"E_SubstValues");
		ucStep=8;
		bOk=m_pSubster->SubstValues();
		STOP_TICK(L"E_SubstValues");
	}while(bOk);

	return m_pCurrResultArgument?true:false;

	}catch(...){
		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"First GenerateResult");
			break;
		case 1:
			wcscpy(buf, L"First PreCalculate");
			break;
		case 2:
			wcscpy(buf, L"StartSubsting");
			break;
		case 3:
			wcscpy(buf, L"Calculate");
			break;
		case 4:
			wcscpy(buf, L"CheckResult");
			break;
		case 5:
			wcscpy(buf, L"EvaluateResult");
			break;
		case 6:
			wcscpy(buf, L"GenerateResult");
			break;
		case 7:
			wcscpy(buf, L"PreCalculate");
			break;
		case 8:
			wcscpy(buf, L"SubstValues");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		};
		ERR_TO_CONSOLE(erTryCatch, buf);
		
		throw;
	}
}

bool CEvaluator::CalculateNext(void)
{
	if(ISNULL(m_pEquation)) return false;
	if(ISNULL(m_pSubster)) return false;
	if(ISNULL(m_pResultsContainer)) return false;
	if(ISNULL(m_pCurrResultArgument)) return false;

	bool bOk=false;
	CArgument* pTempArgument=NULL;
	unsigned char ucStep=0;
	
	try{
	
	//������ ��������� ���������� �����������, 
	//��� ����� �������� ������� �����������, ��� �������� ������
	m_pResultsContainer->GetResultsChecker()->Init();
	
	//���������� ������ �����������, ������� � ���� �� ������� ������������ � ���������� ������
	//� ����� ����������� �������� ��������� �������
	//� ���������� ����������, ���� ������������� ���� ��� �����������
	do{
		//��������� ��������� 
		START_TICK(L"E_CheckResult");
		ucStep=0;
		if(!m_pResultsContainer->CheckResult(m_pCurrResultArgument, &pTempArgument)){
			TO_CONSOLE(L"Calculation breaked!!!");
			break;
		}
		STOP_TICK(L"E_CheckResult");

		//���� ������������� ���������� ���������
		START_TICK(L"E_EvaluateResult");
		ucStep=1;
		m_pSubster->EvaluateResult(pTempArgument);
		STOP_TICK(L"E_EvaluateResult");
		
		//�������� ��������� ��������� ��� ����������
		START_TICK(L"E_GenerateResult");
		ucStep=2;
		m_pCurrResultArgument=m_pResultsContainer->GenerateResult();
		STOP_TICK(L"E_GenerateResult");

		//��������� ��������������
		START_TICK(L"E_PreCalculate");
		ucStep=3;
		//if(m_pCurrResultArgument)
		//	m_pEquation->PreCalculate(m_pCurrResultArgument);
		STOP_TICK(L"E_PreCalculate");

		//����������� �������� � �������
		START_TICK(L"E_SubstValues");
		ucStep=4;
		bOk=m_pSubster->SubstValues();
		STOP_TICK(L"E_SubstValues");

		if(bOk){
			//��������� ��������� ��������
			START_TICK(L"E_Calculate");
			ucStep=5;
			m_pEquation->Calculate(m_pCurrResultArgument);
			STOP_TICK(L"E_Calculate");
		}
	}while(bOk);
	
	return m_pCurrResultArgument?true:false;

	}catch(...){
		wchar_t buf[256]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"CheckResult");
			break;
		case 1:
			wcscpy(buf, L"EvaluateResult");
			break;
		case 2:
			wcscpy(buf, L"GenerateResult");
			break;
		case 3:
			wcscpy(buf, L"PreCalculate");
			break;
		case 4:
			wcscpy(buf, L"SubstValues");
			break;
		case 5:
			wcscpy(buf, L"Calculate");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		};
		ERR_TO_CONSOLE(erTryCatch, buf);
		
		throw;
	}
}


void CEvaluator::View(void)
{
	if(ISNULL(m_pEquation)) return;
	if(ISNULL(m_pSubster)) return;
	if(ISNULL(m_pResultsContainer)) return;

	ToConsole(L"//-----------------Evaluator:");
	m_pEquation->View();
	m_pSubster->View();
	m_pResultsContainer->View();
	ToConsole(L"//-------------End-of-Evaluator");
}

void CEvaluator::ViewResultsContainer(void)
{
	if(ISNULL(m_pResultsContainer)) return;
	m_pResultsContainer->View();
}

//--------------------------------------------------------------------//

}
}
}
}
}