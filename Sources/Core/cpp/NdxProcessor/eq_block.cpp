#include "StdAfx.h"
#include ".\eq_block.h"

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
 
CBlockEquation::CBlockEquation(CEvalFactory* pEvalFactory)
	:CFactoryClient<CEvalFactory>(pEvalFactory), m_pANDBlock(NULL), m_pEquationLogic(NULL)
{
	m_pEquationLogic=GetFactory()->CreateEquationLogic();
}

CBlockEquation::~CBlockEquation(void)
{
	TCalcBlockCollection::iterator itBlock=m_ORBlockCollection.begin();
	while(itBlock!=m_ORBlockCollection.end()){
		delete (*itBlock);
		++itBlock;
	}
	m_ORBlockCollection.clear();

	if(m_pANDBlock){
		delete m_pANDBlock;
		m_pANDBlock=NULL;
	}

	delete m_pEquationLogic;
}

void CBlockEquation::AddAndBlock(void)
{
	if(!m_pANDBlock) m_pANDBlock=new CCalcBlock(GetEquationLogic());
	m_pCurrentBlock=m_pANDBlock;
}

void CBlockEquation::AddOrBlock(void)
{
	m_pCurrentBlock=new CCalcBlock(GetEquationLogic());
	m_ORBlockCollection.push_back(m_pCurrentBlock);
}

void CBlockEquation::AddGroup(CArgumentsGroup* pArgumentsGroup)
{
	if(ISNULL(pArgumentsGroup)) return;
	if(ISNULL(m_pCurrentBlock)) return;
	
	m_pCurrentBlock->AddGroup(pArgumentsGroup);
}

void CBlockEquation::Calculate(CResultArgument* pResult)
{
	if(ISNULL(pResult)) return;
	if(ISNULL(m_pEquationLogic)) return;
	
	CComplexValue* pResultValue=m_pEquationLogic->CreateComplexValue();
	Containers::CValue* pTempValue=NULL;
	bool bCalculationBreaked=false;
	
	//������� ��������� ��������� ��� ����� �, ���� �� ������ ��������� ����������
	if(m_pANDBlock){
		m_pANDBlock->Calculate(pResult->GetMyself()->GetArgumentID(), pResultValue);
		pTempValue=pResultValue->GetValueByLogic(Logics::CLogic::ELogicID::elBoolean);
		if(!pTempValue || pTempValue->IsEmpty()){
			//��������� ����������
			bCalculationBreaked=true;
		}
	}

	CComplexValue* pResultORValue=NULL;
	if(!m_ORBlockCollection.empty()){
		//����� ��������� ��������� ��� ��������� ������ ���
		pResultORValue=m_pEquationLogic->CreateComplexValue();
		CComplexValue* pValue=m_pEquationLogic->CreateComplexValue();
		TCalcBlockCollection::iterator itBlock=m_ORBlockCollection.begin();
		while(itBlock!=m_ORBlockCollection.end()){
			if(!bCalculationBreaked){
				//���� ����������� �� �������� ��������� �������� �����
				//ToConsole(L"BlockID", itBlock->second->GetBlockID());
				(*itBlock)->Calculate(pResult->GetMyself()->GetArgumentID(), pValue);
				//������� ���������� � ����� ���������
				CComplexValue::Calculate(pResultORValue, pValue, Logics::CLogic::eoOR);
				
				pValue->Reset();
			}else{
				//���� ���������� ��������, ��������� ����� ���������� ����� ������� ��������
				//��� �������������
				(*itBlock)->SynhronizeArguments();
			}
			
			++itBlock;
		}
	}
	if(!bCalculationBreaked){
		//���� ���������� �� ��������
		if(pResultORValue){
			if(m_pANDBlock){
				//������� �������� �� � ����� �� ��������� �� ��� ������
				CComplexValue::Calculate(pResultValue, pResultORValue, Logics::CLogic::eoAND);
			}else{
				pResultValue=pResultORValue;
			}
		}

		pTempValue=pResultValue->GetValueByLogic(Logics::CLogic::ELogicID::elBoolean);
		if(pTempValue && !pTempValue->IsEmpty()){
			//��������� ���������
			pResultValue->FillResultArgument(pResult);
		}
	}
}

void CBlockEquation::ToString(wstring& wszValue)
{
	wstring wsTemp;
	wszValue.clear();

	wszValue.append(L"//--------------Bof-CBlockEquation\n");

	if(m_pANDBlock){
		wszValue.append(L"//---------Bof-AND-Block\n");
		m_pANDBlock->ToString(wsTemp);
		wszValue.append(wsTemp);
		wszValue.append(L"//---------Eof-AND-Block\n");
	}

	if(!m_ORBlockCollection.empty()){
		wszValue.append(L"//---------Bof-OR-Block\n");
		TCalcBlockCollection::iterator itBlock=m_ORBlockCollection.begin();
		while(itBlock!=m_ORBlockCollection.end()){
			(*itBlock)->ToString(wsTemp);
			wszValue.append(wsTemp);
			++itBlock;
		}
		wszValue.append(L"//---------Eof-OR-Block\n");
	}

	wszValue.append(L"//--------------Eof-CBlockEquation\n");
}

//--------------------------------------------------------------------//

void CBlockOREquation::AddGroup(CArgumentsGroup* pArgumentsGroup)
{
	if(ISNULL(pArgumentsGroup)) return;

	m_pCurrentBlock=new CCalcBlock(GetEquationLogic());
	m_ORBlockCollection.push_back(m_pCurrentBlock);
	m_pCurrentBlock->AddGroup(pArgumentsGroup);
}

//--------------------------------------------------------------------//

void CBlockANDEquation::AddGroup(CArgumentsGroup* pArgumentsGroup)
{
	if(ISNULL(pArgumentsGroup)) return;

	if(!m_pANDBlock) m_pANDBlock=new CCalcBlock(GetEquationLogic());
	m_pANDBlock->AddGroup(pArgumentsGroup);
}

//--------------------------------------------------------------------//

}
}
}
}
}