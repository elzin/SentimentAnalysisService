#include "StdAfx.h"
#include ".\arg_calc.h"
#include ".\eq_calc.h"
#include ".\index_container_nodes_s.h"

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
 
using namespace SS::Core::NdxSE::NdxProcessor;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Core::NdxSE::NdxProcessor::Extracting::Logics;

//--------------------------------------------------------------------//

CCalcArgument::CCalcArgument(CCalcEquation* pOwnerEquation, unsigned int uiArgumentID, CLogic::EOperator Operator, float fKoeff, SS::Interface::Core::CommonContainers::SQueryIndexAttributes ArgumentAttributes)
:CBinTreeNode<CComplexArgument*>(new CComplexArgument(uiArgumentID, fKoeff, ArgumentAttributes)), 
m_Operator(Operator), m_pOwnerEquation(pOwnerEquation)
{
	if(ISNULL(m_pOwnerEquation)) return;
	
}

CCalcArgument::~CCalcArgument(void)
{
}

void CCalcArgument::Calculate(CResultArgument* pResult)
{
	//if(ISNULL(pResult)) return;
	if(ISNULL(m_pMyself)) return;
	
	//�������� ����� ��������
	if(GetLeftChild()){
		GetLeftChild()->Calculate(pResult);	
		if(m_pMyself && IsArgumentIntermediate() && GetLeftChild()->GetMyself()){
			//���� �������� ������������� �� ����� ���������� �� ������������
			m_pMyself->SetComplexValue(GetLeftChild()->GetMyself()->GetValue());

			if(GetLeftChild()->IsArgumentIntermediate()){
				GetLeftChild()->GetMyself()->SetComplexValue(NULL);
			}
		}else{
			TO_CONSOLE(L"Equation filling error!!!");
		}
	}else{
		//m_pMyself->GetValue()->View();
	}

	//����������� � ������ ��������
	if(GetRightChild()){
		GetRightChild()->Calculate(pResult);	
		if(GetRightChild()->GetMyself()){
			//�������� ���������� � ������������ � ����������
			CComplexValue::Calculate(
				m_pMyself->GetValue(), 
				GetRightChild()->GetMyself()->GetValue(), 
				m_Operator);

			if(GetRightChild()->IsArgumentIntermediate()){
				//���� �������� ������������� �� ����� ���������� �� ������������
				GetRightChild()->GetMyself()->SetComplexValue(NULL);
			}else{
				//��� ���������������� ��������� ���������� ���������� ��������
				if(GetRightChild()->GetMyself()->GetValue())
					GetRightChild()->GetMyself()->GetValue()->Reset();
				//GetRightChild()->GetMyself()->GetValue()->View();
			}
		}
	}
	
	//������ � m_pMyself ����� ��������� ����������
	//if(m_pMyself->GetValue())
	//	m_pMyself->GetValue()->View();

	if(IsRoot() && m_pMyself){
		//���� �������� ������� ��������� ���������
		m_pMyself->FillResultArgument(pResult);
		//���������� ����������� ��������
		m_pMyself->GetValue()->Reset();
		m_pMyself->SetComplexValue(NULL);
		//pResult->GetValue()->View();
	}
}

CCalcArgument* CCalcArgument::AddChild(CCalcArgument* pChildArgument)
{
	if(ISNULL(pChildArgument)) return NULL;
	
	if(!m_pLeftChild && !m_pRightChild){
		//���� ����� � ������ ���� ����� ������ ����� ��������
		return (CCalcArgument*)CBinTreeNode<CComplexArgument*>::AddChild(pChildArgument, true);
	}

	if(m_pLeftChild && !m_pRightChild){
		//���� ����� ����� � ������ ���� ���� ������ ������ ��������
		return (CCalcArgument*)CBinTreeNode<CComplexArgument*>::AddChild(pChildArgument, false);
	}

	//� ��������� ������� ���� �� ������
	return NULL;
}

CLogic::EOperator CCalcArgument::GetOperator(wstring& szValue)
{
	if(szValue.empty()) return CLogic::eoUndefined;

	switch(szValue[0]){
	case '&':
		return CLogic::eoAND;
		break;
	case '|':
		return CLogic::eoOR;
		break;
	case '~':
		return CLogic::eoNOT;
		break;
	case '(':
		return CLogic::eoLeftBracket;
		break;
	case ')':
		return CLogic::eoRightBracket;
		break;
	default:
		return CLogic::eoUndefined;
		break;
	}
}

bool CCalcArgument::IsOperatorPriorityNotHigher(wstring& szValue)
{
	return IsOperatorPriorityNotHigher(GetOperator(szValue));
}

bool CCalcArgument::IsOperatorPriorityNotHigher(CLogic::EOperator Operator)
{
	//� �������� ���� ��������� ������ ����
	if(IsRoot()) return false;

	switch(m_Operator){
	case CLogic::EOperator::eoLeftBracket:
		return false;
		break;
	case CLogic::eoNOT:
		return (Operator!=CLogic::eoLeftBracket);
		break;
	case CLogic::eoAND:
		return (Operator!=CLogic::eoLeftBracket && Operator!=CLogic::eoNOT);
		break;
	case CLogic::eoOR:
		return (Operator!=CLogic::eoLeftBracket && Operator!=CLogic::eoNOT && Operator!=CLogic::eoAND);
		break;
	case CLogic::EOperator::eoRightBracket:
		return true;
		break;
	default:
		return (Operator!=CLogic::eoUndefined);
		break;
	}

}

CCalcArgument* CCalcArgument::InsertCalcArgument(unsigned int uiArgumentID, CLogic::EOperator Operator, float fWeight, SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attributes, CCalcArgument** ppInsertedArgument)
{
	if(ISNULL(m_pOwnerEquation)) return NULL;

	CCalcArgument* pInsertedArgument=NULL;
	CCalcArgument* pRetArgument=NULL;

	if(Operator==CLogic::eoUndefined){
		//���� ������� �������� �� ���������
		if(!ChildsOccupied()){
			//������� ���������� ������� � ���������,
			//���� ���� ����� � ����� ������� ������� 
			pInsertedArgument=AddChild(new CCalcArgument(m_pOwnerEquation, uiArgumentID, CLogic::eoUndefined, fWeight, Attributes));
			//������� ������ ������� ��������
			pInsertedArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());
			pRetArgument=this;
		}else{
			//���� ����� ��� ��������� �������� ��� ��������� ����� ������
			pInsertedArgument=NULL;
			pRetArgument=NULL;
		}
	}else{
		//���� ������� �������� ���������
		if(m_Operator==CLogic::eoUndefined){
			//���� �������� ��������� �� ��������� (�� ���� � ���� ��� ��������� �����)
			//������ ��������� ����� ���� � ���������� ��������� ��� �������� 
			SetOperator(Operator);
			pInsertedArgument=AddChild(new CCalcArgument(m_pOwnerEquation, uiArgumentID, CLogic::eoUndefined, fWeight, Attributes));
			
			if(uiArgumentID==SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE){
				pRetArgument=pInsertedArgument;
			}else{
				//������� ������ ������� ��������
				pInsertedArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());
				pRetArgument=this;
			}
		}else{
			//���� �������� ��������� ��������� 
			//�������� �������������� ������

			//������� ������������� ��������
			CCalcArgument* pTempArgument=new CCalcArgument(m_pOwnerEquation);

			//���� � ��������� ��� ���� ��������
			//�������� ��������� ��������� ��������� � ������ ���������
			if(IsOperatorPriorityNotHigher(Operator)){
				//���� ��������� ��������� ��������� ���� ��� ��� �� ��� � ������ ���������
				
				//������ ��� ����� �������� ��������� ������ � ����������
				pTempArgument->AddChild(GetLeftChild());

				//������ ������ �������� ������� ����� ���������, ���� �� �� ������
				if(uiArgumentID!=EMPTY_VALUE){
					pInsertedArgument=pTempArgument->AddChild(new CCalcArgument(m_pOwnerEquation, uiArgumentID, CLogic::eoUndefined, fWeight, Attributes));
					//������� ������ ������� ��������
					pInsertedArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());
				}else{
					pTempArgument->AddChild(GetRightChild());
					pInsertedArgument=NULL;
				}

				pTempArgument->SetOperator(GetOperator());
				RemoveChilds();

				//������ ������������� �������� �������� ��������
				AddChild(pTempArgument);
				//�������� ��������� ���������� �������� ������ ���������
				SetOperator(Operator);
				//������� �������� ��� � �������� �������								
				pRetArgument=this;
			}else{
				//���� ��������� ��������� ��������� ���� ��� ����� �� ��� � ������ ���������
				//������ ����� �������� ������� ����� ���������, ���� �� �� ������
				if(uiArgumentID!=EMPTY_VALUE){
					pInsertedArgument=pTempArgument->AddChild(new CCalcArgument(m_pOwnerEquation, uiArgumentID, CLogic::eoUndefined, fWeight, Attributes));
					//������� ������ ������� ��������
					pInsertedArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());
				}else{
					pTempArgument->AddChild(GetRightChild());
					pInsertedArgument=NULL;
				}

				//�������������� ��������� ���������� �������� ������ ���������
				pTempArgument->SetOperator(Operator);
				//������ ������������� �������� ������ �������� ��������
				RemoveRightChild();
				AddChild(pTempArgument);
				//������������� �������� ���������� �������
				pRetArgument=pTempArgument;
			}
		}
	}
	
	if(ppInsertedArgument)
		(*ppInsertedArgument)=pInsertedArgument;

	return pRetArgument;
}

CCalcArgument* CCalcArgument::InsertCalcArgument(wstring* pszArgument, float fWeight, SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attributes)
{
	/*
	������� ������������ ����������� �������:
	1. ������� ������� �� ���������� (�����, ���������������) � ������������� ���������� 
	(������������� ��������� ���������� ���� ���������� 
	� ������������ � ������ ��������� - �������� ������ ���� ��������)
	2. ��������� ������ � ������������ � ������������� CLogic::EOperator
	3. ������������ ����� ����� ���� ������ �� ������������� ���������
	4. �������� ������ ����������� � �������� �������������� ��������
	5. ������������� �������� � �������� �������������� ����������� � ����������� � ����������� ������ ���������
	6. ��� ���� ��������� �������� �������������� ���������, ��� ���� �� ������ ��������� � ������ �������
	(���������� ���� ����� �����, �.�. �� ����� �������� ������)
	7. ����� ������ ������� ������ ������������� ��������, ����� ��������� ��������� �� ����������
	8. ������ ������ ���������� ����� ������ �� ��������� �������� �������������� ��������� � ����� ������� 
	(� ��� �� ��������� ������, ���� ����������� ������ ������)
	*/

	if(ISNULL(pszArgument)) return this;
	if(pszArgument->empty()) return this;

	unsigned int uiArgumentID=EMPTY_VALUE;
	CLogic::EOperator Operator;

	//���������� ��� ������
	Operator=GetOperator(*pszArgument);
	if(Operator==CLogic::EOperator::eoUndefined){
		//���� ��� �� �������� ������� ��� �� ����� ��������
		//�������� ��� � �����
		uiArgumentID=_wtoi(pszArgument->c_str());
		//��������� ��� � �������� ����
		if(!ChildsOccupied()){
			//������� ���������� ������� � ���������,
			//���� ���� ����� � ����� ������� ������� 
			CCalcArgument* pChildArgument=AddChild(new CCalcArgument(m_pOwnerEquation, uiArgumentID, CLogic::eoUndefined, fWeight, Attributes));
			//������� ������ ������� ��������
			pChildArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());
		}else{
			//���� ����� ��� ��� ������
			TO_CONSOLE(L"CCalcArgument ChildsOccupied Error!!!");
		}
		return this;
	}else if(Operator==CLogic::EOperator::eoRightBracket){
		//���� ������ ������, ������ ������� ����� ������ �� ����� ������
		CCalcArgument* pTempArgument=this;
		while(pTempArgument->GetOperator()!=CLogic::EOperator::eoLeftBracket){
			pTempArgument=pTempArgument->GetParent();
			if(!pTempArgument){
				TO_CONSOLE(L"Expression error RightBracket without LeftBracket");
				pTempArgument=this;
				break;
			}
		}

		pTempArgument->SetOperator(CLogic::EOperator::eoRightBracket);
		return pTempArgument->GetParent();

	}else if(Operator==CLogic::EOperator::eoLeftBracket){
		//���� ����� ������, ������ ��������� �� � �������� ��������� � ��������� �����
		//������� ������������� ��������
		CCalcArgument* pTempArgument=new CCalcArgument(m_pOwnerEquation, uiArgumentID, Operator, fWeight, Attributes);
		////������� ������ ������� ��������
		//pTempArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());

		AddChild(pTempArgument);

		return pTempArgument;
	}else{
		//���� ��� �������� ��������� ��� � ������� � ������������ � ��� �����������
		
		//������� ������������� ��������
		CCalcArgument* pTempArgument=new CCalcArgument(m_pOwnerEquation, uiArgumentID, Operator, fWeight, Attributes);
		////������� ������ ������� ��������
		//pTempArgument->GetMyself()->SetComplexValue(m_pOwnerEquation->GetEquationLogic()->CreateComplexValue());

		//���������� ��������� ��������� �� �������
		if(IsOperatorPriorityNotHigher(Operator)){
			//��������� �������� ��������� �� ����
			//�� ���������� ��������� �������� ���������, ����� ��� ����� ����� ��������


			CCalcArgument* pParentArgument=GetParent();
			CCalcArgument* pLeftChildArgument=pParentArgument->GetLeftChild();
			CCalcArgument* pRightChildArgument=pParentArgument->GetRightChild();
			if(pRightChildArgument==this){ 
				pParentArgument->RemoveChilds();
				pParentArgument->AddChild(pLeftChildArgument);
				pParentArgument->AddChild(pTempArgument);
				pTempArgument->AddChild(pRightChildArgument);	
			}else if(pLeftChildArgument==this && !pRightChildArgument){
				pParentArgument->RemoveChilds();
				pParentArgument->AddChild(pTempArgument);
				pTempArgument->AddChild(pLeftChildArgument);	
			}else{
				TO_CONSOLE(L"Impossible case");
				delete pTempArgument;
				return this;
			}


		}else{
			//��������� �������� ��������� ����
			//�� ���������� ������ �������� �������� ���������, ����� ����� ����� ��������, ��� ������� �������
			
			CCalcArgument* pLeftChildArgument=GetLeftChild();
			CCalcArgument* pRightChildArgument=GetRightChild();
			RemoveChilds();
			if(pRightChildArgument){ 
				AddChild(pLeftChildArgument);
				pTempArgument->AddChild(pRightChildArgument);	
			}else if(pLeftChildArgument){
				pTempArgument->AddChild(pLeftChildArgument);	
			}

			AddChild(pTempArgument);
		}
		
		return pTempArgument;
	}

	return this;
}

bool CCalcArgument::IsSpare(void)
{
	if(IsArgumentIntermediate() && (GetOperator()==CLogic::eoUndefined || GetOperator()==CLogic::eoRightBracket)){
		//���� �������� ������������� � � ������������� ����������
		if(!(GetLeftChild() && GetRightChild())){
			//���� � ��������� ������ ���� �����
			//�� ������!!!
			return true;
		}
	}

	return false;
}

void CCalcArgument::OptimizeCalcEquation(void)
{
	//��������� ����������� ����� �����
	if(GetLeftChild()){
		GetLeftChild()->OptimizeCalcEquation();	
	}

	//��������� ����������� ������ �����
	if(GetRightChild()){
		GetRightChild()->OptimizeCalcEquation();	
	}
	
	if(IsSpare() && !IsRoot()){
		//���� ������ �������� ������, �� ������� ����
		CCalcArgument* pChild=NULL;
		CCalcArgument* pParent=GetParent();
		
		if(GetLeftChild())
			pChild=GetLeftChild();
		else if(GetRightChild())
			pChild=GetRightChild();

		//������ �������� ������ �������
		if(pParent->GetLeftChild()==this){
			pParent->m_pLeftChild=pChild;
		}else if(pParent->GetRightChild()==this){
			pParent->m_pRightChild=pChild;
		}
		
		//������� ����
		RemoveChilds();
		delete this;
	}
}

void CCalcArgument::ToString(wstring& szValue, wstring szOffset)
{
	szOffset.append(L" ");	
	szValue.append(L"\n");
	szValue.append(szOffset);
	szValue.append(L"|-->");

	if(!m_pParent)
		szValue.append(L"root ");
	else
		m_pMyself->ToString(szValue);

	switch(m_Operator){
	case CLogic::eoAND:
		szValue.append(L"Op-AND");
		break;
	case CLogic::eoOR:
		szValue.append(L"Op-OR");
		break;
	case CLogic::eoNOT:
		szValue.append(L"Op-NOT");
		break;
	case CLogic::eoLeftBracket:case CLogic::eoRightBracket:
		szValue.append(L"Op-BR");
		break;
	default:
		szValue.append(L"Op-UDF");
		break;
	}

	if(m_pLeftChild)
		((CCalcArgument*)(m_pLeftChild))->ToString(szValue, szOffset);
	if(m_pRightChild)
		((CCalcArgument*)(m_pRightChild))->ToString(szValue, szOffset);
}

//--------------------------------------------------------------------//

CArgumentsGroup::~CArgumentsGroup(void)
{
	for(unsigned int i=0; i<m_ArgumentCollection.size(); i++){
		delete m_ArgumentCollection[i];
	}
	m_ArgumentCollection.clear();
}

float CArgumentsGroup::GetWeight(void)
{
	if(!m_ArgumentCollection.empty()){
		return m_fTotalArgWeight/m_ArgumentCollection.size();
	}
	return 0;
}

CComplexArgument* CArgumentsGroup::AddArgument(unsigned int uiArgumentID, float fWeight, SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attributes)
{
	if(ISNULL(m_pEquationLogic)) return NULL;
	
	//ToConsole(L"BlockID", GetBlockID());
	//ToConsole(L"ArgumentID", uiArgumentID);

	CComplexArgument* pComplexArgument=new CComplexArgument(uiArgumentID, fWeight, Attributes);
	pComplexArgument->SetBlockID(GetID());
	pComplexArgument->SetComplexValue(m_pEquationLogic->CreateComplexValue());
	m_ArgumentCollection.push_back(pComplexArgument);
	m_fTotalArgWeight+=fWeight;

	return pComplexArgument;
}


void CArgumentsGroup::Calculate(unsigned int uiEvalID, CComplexValue* pResultValue)
{
	if(ISNULL(pResultValue)) return;
	
	CComplexArgument* pComplexArgument=NULL;
	Containers::CCoordinateNode_4s* pCoordinateNode=NULL;
	Containers::CValue* pChildNode=NULL;

	//��������� � �������� �������� ��� �� ���
	for(unsigned int i=0; i<m_ArgumentCollection.size(); i++){
		pComplexArgument=m_ArgumentCollection[i];
		pChildNode=NULL;

		//�������� ����������� ��������
		if(pComplexArgument->IsEmptySourceValuesStack()){
			//���� ���� �������� ������ ����� ������ �������� 
			//������� ������� ������������ ��� ����������
			pChildNode=pComplexArgument->GetStartValue();
		}else{
			//���� ���� �������� �� ������, �������� ������� �������� �����
			pCoordinateNode=dynamic_cast<CCoordinateNode_4s*>(pComplexArgument->GetBackSourceValue());
			//�������� �������� ��������
			pChildNode=dynamic_cast<CValue*>(pCoordinateNode->MoveUpChildNode(uiEvalID));
		}

		if(pChildNode){
			//���� ��������� ���� ���� ���������

			//������������� ��������� �������� ��������
			pComplexArgument->SetValue(pChildNode);
			//ToConsole(L"ArgumentID", pComplexArgument->GetArgumentID());
			//pComplexArgument->GetValue()->GetValueByLogic(Logics::CLogic::ELogicID::elBoolean)->View();
			//���������
			CComplexValue::Calculate(pResultValue, pComplexArgument->GetValue(), Logics::CLogic::eoOR);
		}

		//�������� ������� ���������� � ���������� ������ � ����, ��� ������ ��������� �����������
		pComplexArgument->PushBackSourceValue(pChildNode);
	}
}

void CArgumentsGroup::SynhronizeArguments(void)
{
	//���������� ��������� ������ � ���� ������ ��������
	for(unsigned int i=0; i<m_ArgumentCollection.size(); i++){
		m_ArgumentCollection[i]->PushBackSourceValue(NULL);
	}
}

void CArgumentsGroup::ToString(wstring& szValue)
{
	szValue.clear();
	wchar_t buf[100];

	swprintf(buf, L"Block: \n\tID:%u \n\tWeight: %.3f \n\tObl: %u \n\t", GetID(), GetWeight(), (unsigned int)GetObligatory());
	szValue.append(buf);

	for(unsigned int i=0; i<m_ArgumentCollection.size(); i++){
		wsprintf(buf, L"%u ", m_ArgumentCollection[i]->GetArgumentID());
		szValue.append(buf);
	}

	szValue.append(L"\n");
}

//--------------------------------------------------------------------//

CCalcBlock::~CCalcBlock(void)
{
	TArgGroupCollection::iterator itGroup=m_ArgGroupCollection.begin();
	while(itGroup!=m_ArgGroupCollection.end()){
		delete itGroup->second;
		++itGroup;
	}

	TArgGroupList::iterator itNotOblGroup=m_NotOblArgGroupCollection.begin();
	while(itNotOblGroup!=m_NotOblArgGroupCollection.end()){
		delete (*itNotOblGroup);
		++itNotOblGroup;
	}
}

void CCalcBlock::AddGroup(CArgumentsGroup* pArgumentsGroup)
{
	if(ISNULL(pArgumentsGroup)) return;

	if(!pArgumentsGroup->GetObligatory()){
		m_NotOblArgGroupCollection.push_back(pArgumentsGroup);
		return;
	}

	float fWeight=pArgumentsGroup->GetWeight();
	if(fWeight==0.0) return;
	
	unsigned int uiWeight=(unsigned int)(fWeight*1000);

	TArgGroupCollection::iterator itGroup=m_ArgGroupCollection.find(uiWeight);
	while(!(itGroup==m_ArgGroupCollection.end())){
		itGroup=m_ArgGroupCollection.find(++uiWeight);
	}
	
	//wchar_t buf[100];
	//swprintf(buf, L"\nIDW: %u\n", uiWeight);
	//ToConsole(buf);

	//��������� ���� � ���������
	if(!m_ArgGroupCollection.insert(TArgGroupCollection::value_type(uiWeight, pArgumentsGroup)).second){
		TO_CONSOLE(L"Cann't insert block");
	};
}

void CCalcBlock::Calculate(unsigned int uiEvalID, CComplexValue* pResultValue)
{
	if(ISNULL(pResultValue)) return;
	if(ISNULL(m_pEquationLogic)) return;

	//ToConsole(L"uiEvalID", uiEvalID);
	
	CComplexValue* pValue=m_pEquationLogic->CreateComplexValue();
	TArgGroupCollection::iterator itGroup=m_ArgGroupCollection.begin();
	Containers::CValue* pTempValue=NULL;
	bool bCalculationBreaked=false;
	while(itGroup!=m_ArgGroupCollection.end()){
		if(!bCalculationBreaked){
			//���� ����������� �� �������� ��������� �������� �����
			itGroup->second->Calculate(uiEvalID, pValue);

			//itGroup->second->View();
			//pValue->GetValueByLogic(Logics::CLogic::ELogicID::elBoolean)->View();

			//������� ���������� � ����� ���������
			if(itGroup==m_ArgGroupCollection.begin())		
				CComplexValue::Calculate(pResultValue, pValue, Logics::CLogic::eoOR);
			else
				CComplexValue::Calculate(pResultValue, pValue, Logics::CLogic::eoAND);

			//��������� ������� ���������, ���� �� ������ ������ ��������� �� ����� ������
			pTempValue=pResultValue->GetValueByLogic(Logics::CLogic::ELogicID::elBoolean);
			if(!pTempValue || pTempValue->IsEmpty()){
				//��������� ����������
				bCalculationBreaked=true;
			}

			pValue->Reset();
		}else{
			//���� ���������� ��������, ��������� ����� ���������� ����� ������� ��������
			//��� �������������
			itGroup->second->SynhronizeArguments();
		}
		
		++itGroup;
	}

	TArgGroupList::iterator itNotOblGroup=m_NotOblArgGroupCollection.begin();
	while(itNotOblGroup!=m_NotOblArgGroupCollection.end()){
		if(!bCalculationBreaked){
			//���� ����������� �� �������� ��������� �������� �����
			pValue->Reset();
			(*itNotOblGroup)->Calculate(uiEvalID, pValue);
			
			if(m_ArgGroupCollection.size()==0){
				//���� � ����� ��� ������������ ����������, ��������� ��������� �� ��������������
				//������� ���������� � ����� ���������
				CComplexValue::Calculate(pResultValue, pValue, Logics::CLogic::eoOR);
			}
		}else{
			//���� ���������� ��������, ��������� ����� ���������� ����� ������� ��������
			//��� �������������
			(*itNotOblGroup)->SynhronizeArguments();
		}
		++itNotOblGroup;
	}

	//ToConsole(L"Result:");
	//pResultValue->GetValueByLogic(Logics::CLogic::ELogicID::elBoolean)->View();
}

void CCalcBlock::SynhronizeArguments(void)
{
	TArgGroupCollection::iterator itGroup=m_ArgGroupCollection.begin();
	while(itGroup!=m_ArgGroupCollection.end()){
		//���� ���������� ��������, ��������� ����� ���������� ����� ������� ��������
		//��� �������������
		itGroup->second->SynhronizeArguments();
		++itGroup;
	}

	TArgGroupList::iterator itNotOblGroup=m_NotOblArgGroupCollection.begin();
	while(itNotOblGroup!=m_NotOblArgGroupCollection.end()){
		(*itNotOblGroup)->SynhronizeArguments();
		++itNotOblGroup;
	}

}

void CCalcBlock::ToString(wstring& wszValue)
{
	wstring wsBlockValue;
	wszValue.clear();
	wszValue.append(L"//------Bof-CCalcBlock\n");

	TArgGroupCollection::iterator itGroup=m_ArgGroupCollection.begin();
	while(itGroup!=m_ArgGroupCollection.end()){
		wchar_t buf[100];
		swprintf(buf, L"\nIDW: %u\n", itGroup->first);
		wszValue.append(buf);
		itGroup->second->ToString(wsBlockValue);
		wszValue.append(wsBlockValue);

		++itGroup;
	}

	wszValue.append(L"\nNot Obligatory Blocks:\n");
	TArgGroupList::iterator itNotOblGroup=m_NotOblArgGroupCollection.begin();
	while(itNotOblGroup!=m_NotOblArgGroupCollection.end()){
		(*itNotOblGroup)->ToString(wsBlockValue);
		wszValue.append(wsBlockValue);
		++itNotOblGroup;
	}

	wszValue.append(L"//------Eof-CCalcBlock\n");
}

//--------------------------------------------------------------------//

}
}
}
}
}