#include "StdAfx.h"
#include ".\box_containers_s.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

using namespace SS::Interface::Core::NdxSE::NdxDataStorage;

//--------------------------------------------------------------------//

CBitMap_4s::CBitMap_4s(unsigned int uiBitMapSizeInBits, EBitMapState eBitMapState)
:m_uiBitMapSizeInBits(uiBitMapSizeInBits), m_ucCurrBitNumber(UC_EMPTY), 
m_eBitMapState(eBitMapState), m_uiCurrBitValue(EMPTY_VALUE),
m_uiCurrBoxPos(EMPTY_VALUE), m_uiLastBitValue(EMPTY_VALUE)
{
	m_itCurrBox = m_NullCollection.end();
	if(m_eBitMapState==esEmpty){
		Reset();
	}else if(m_eBitMapState==esFull){
		Fill();	
	}
}

unsigned int CBitMap_4s::GetBitMapBoxSize(void)
{
	div_t div_result=div(m_uiBitMapSizeInBits, cucBitBoxValueSize);
	return div_result.rem==0?div_result.quot:div_result.quot+1;
}

void CBitMap_4s::Fill(void)
{
	SBitBox BitBox;
	memset((void*)&BitBox, cucFullBitBox, 1);
	m_BitMapBoxes.assign(GetBitMapBoxSize(), BitBox);	
	SetState(esFull);
	m_uiLastBitValue=GetOrtsMaxNumber()-1;
}

void CBitMap_4s::Reset(void)
{
	m_BitMapBoxes.clear();
	SetState(esEmpty);
	m_uiLastBitValue=EMPTY_VALUE;
}

bool CBitMap_4s::AddBit(unsigned int uiBitValue)
{
 	if(m_uiLastBitValue!=EMPTY_VALUE && uiBitValue<=m_uiLastBitValue) return false;

	//�������� ��������� ��������� �� ���������� ���� � ������� �����
	//�������� �������� ���������� ���� � ������� �����
	unsigned int uiBitDistance;
	unsigned int uiLastBitInBox;
	if(m_uiLastBitValue==EMPTY_VALUE){
		uiBitDistance=uiBitValue+1;
		uiLastBitInBox=EMPTY_VALUE;
	}else{
		if(uiBitValue<m_uiLastBitValue){
			TO_CONSOLE(L"BitValue not increase, cann't add bit");
			ToConsole(L"BitValue", uiBitValue);
			ToConsole(L"LastBitValue", m_uiLastBitValue);
			return false;
		}
		uiBitDistance=uiBitValue-m_uiLastBitValue;
		uiLastBitInBox=m_BitMapBoxes.back().GetLastBitValue();
	}

	//��������� ��� � �����
	if(uiLastBitInBox+uiBitDistance<=cucBitMaxBitValue){
		//���� ����� �������� � ��������� ����, ���������
		if(m_BitMapBoxes.empty()){
			SBitBox BitBox;
			BitBox.Type=cucBitBoxType;
			BitBox.Value=0;
			m_BitMapBoxes.push_back(BitBox);
		}
		m_BitMapBoxes.back().SetBit(uiLastBitInBox+uiBitDistance);
	}else{
		//���� ��������� ������� �������
		//���������� ��������� ���������� � ��������� ���
		if(m_uiLastBitValue!=EMPTY_VALUE) uiBitDistance-=cucBitMaxBitValue-uiLastBitInBox;
		
		//���������� ������� ����� ������� ������ (������� ���������� 7-�� �����)
		//� �������� ���� � ��������� �����
		div_t div_result=div(uiBitDistance, cucBitBoxValueSize);
		unsigned int uiNeededBitBoxNumber=div_result.quot;
		unsigned char ucBitValue=(unsigned char)div_result.rem;
		
		//���� �������� ������� ������, ��� ����� ��������� � ����� ���������� �����
		if(!ucBitValue){
			uiNeededBitBoxNumber--;
			ucBitValue=cucBitMaxBitValue;
		}else{
			ucBitValue--;
		}

		//���������� ���������� NullBox-�� ��� �������� ����� ������ 7-�� �����
		div_result=div(uiNeededBitBoxNumber, cucBitMaxNumberValue);
		//���������� ������ NullBox-��
		unsigned int uiNullBoxNumber=div_result.quot;
		//���������� ��������� � ��������� NullBox-�
		unsigned int uiLastNullBoxValue=div_result.rem;
		
		//����� ���������� ��������� � ������ ���������� ���������
		if(uiLastNullBoxValue) uiNullBoxNumber++;
		//��������� ��� ��� � ������� �����
		unsigned int uiValue=cucBitMaxNumberValue;
		while(uiNullBoxNumber){
			//��� ���������� �������� �������� ������
			if(uiNullBoxNumber==1)	uiValue=uiLastNullBoxValue;
			
			//�������� � ���� �������
			SBitBox NullBox;
			NullBox.Type=cucNullBoxType;
			NullBox.Value=uiValue;
			m_BitMapBoxes.push_back(NullBox);
			
			//��������� �������
			uiNullBoxNumber--;
		}
		
		//��������� �������
		//���������� � ��� ������ ���
		SBitBox BitBox;
		BitBox.Type=cucBitBoxType;
		BitBox.Value=0;
		m_BitMapBoxes.push_back(BitBox);
		m_BitMapBoxes.back().SetBit(ucBitValue);
	}

	//������������� �������� ���������� ���� �����
	m_uiLastBitValue=uiBitValue;
	
	return true;
}

bool CBitMap_4s::SetOrt(unsigned int uiBitPos)
{
	//��� ������ ����� �� �����
	if(IsFull()) return false;
	
	SetNotEmpty();
	
	//���� �������� ���������� ���������� ����
 	if(m_uiLastBitValue==EMPTY_VALUE || uiBitPos>m_uiLastBitValue) 
		return AddBit(uiBitPos);

	unsigned int uiBoxPos=0;
	unsigned char ucBitValue=0;
	//���������� ����� ������� ��������� � ����� ���� � ���
	div_t div_result=div(uiBitPos, cucBitBoxValueSize);
	uiBoxPos=div_result.quot;
	ucBitValue=(unsigned char)div_result.rem;

	unsigned int uiCurrPos=0;
	TBitBoxCollection::iterator itBox=m_BitMapBoxes.begin(); 
	while(itBox!=m_BitMapBoxes.end()){
		//���������� ��� ���������
		if(itBox->IsBitBox()){
			if(uiCurrPos==uiBoxPos){
				//���� ����� ������ ��������� ������ ���������� � ��� ��� � �������
				itBox->SetBit(ucBitValue);
				return true;
			}
			uiCurrPos++;
		}else{
			//���� ��� ��������� �����
			if(uiCurrPos+itBox->Value<=uiBoxPos){
				//���� ������� ����� ������ ����������
				uiCurrPos+=itBox->Value;
			}else{
				//���� ������� ����� ��� �����
				//������ ���������� ���������
				unsigned char ucTemp=itBox->Value-(uiBoxPos-uiCurrPos)-1;
				//����� ������� ����� ����� ���������
				if(uiBoxPos-uiCurrPos){
					itBox->Value=(uiBoxPos-uiCurrPos);
					//���� ������� �� ��������, ��������� ������ ������� ��� �����
					SBitBox NewBox;
					NewBox.SetNumber(0);
					itBox=m_BitMapBoxes.insert(++itBox, NewBox);
				}else{
					itBox->SetNumber(0);
				}

				//���������� ���
				itBox->Type=cucBitBoxType;
				itBox->SetBit(ucBitValue);
				
				if(ucTemp){
					SBitBox NewBox;
					NewBox.Type=cucNullBoxType;
					NewBox.Value=ucTemp;
					itBox=m_BitMapBoxes.insert(++itBox, NewBox);
				}
				return true;
			}
		}
		itBox++;
	}

	return false;
}

bool CBitMap_4s::HasOrt(unsigned int uiBitPos)
{
	//��� ������ ����� �� �����
	if(IsFull()) return true;
	//��� ������ ����� �� �����
	if(IsEmpty()) return false;

	//���������� ����� ������� ��������� � ����� ���� � ���
	div_t div_result=div(uiBitPos, cucBitBoxValueSize);
	//������� ������� ���������
	unsigned int uiBoxPos=div_result.quot;
	
	TBitBoxCollection::iterator itBox=m_BitMapBoxes.begin(); 
	unsigned int uiCurrPos=0;
	do{
		//���������� ��� ���������
		if(itBox->IsBitBox()){
			if(uiCurrPos==uiBoxPos){
				//���� ����� ������ ��������� ������ ���������� � ��� ��� � �������
				return itBox->IsSetBit(div_result.rem);
			}
			uiCurrPos++;
		}else{
			//���� ��� ��������� �����, �������� ������� �� ���������� �����
			uiCurrPos+=itBox->Value;
		}
		if(uiBoxPos<uiCurrPos){
			//���� ������ ������ ������� ��������� ���, �������			
			return false;
		}
	}while(++itBox!=m_BitMapBoxes.end());
	
	return false;
}

bool CBitMap_4s::MoveFirstOrt(void)
{
	//��� ������ ����� �� ���������
	m_ucCurrBitNumber=UC_EMPTY;
	m_uiCurrBoxPos=EMPTY_VALUE;
	m_uiCurrBitValue=EMPTY_VALUE;
	if(IsEmpty()) return false;

	//START_TICK(L"MoveFirstOrt");
	//������� �� ������ ������������ ���
	TBitBoxCollection::iterator itBox=m_BitMapBoxes.begin(); 
	unsigned int uiCurrPos=0;
	while(itBox!=m_BitMapBoxes.end()){
		if(itBox->IsBitBox()){
			m_ucCurrBitNumber=itBox->GetFirstBitValue();
			//���������� ����� ������� ������������� ����
			if(m_ucCurrBitNumber==UC_EMPTY){
				TO_CONSOLE(L"GetFirstBitValue error!");
				m_uiCurrBoxPos=EMPTY_VALUE;
				m_itCurrBox=m_NullCollection.end();
				return false;
			}else{
				m_itCurrBox=itBox;
				m_uiCurrBoxPos=uiCurrPos;
				m_uiCurrBitValue=m_ucCurrBitNumber+(m_uiCurrBoxPos*cucBitBoxValueSize);
				return true;
			}
		}else{
			uiCurrPos+=itBox->Value;
		}
		itBox++;
	}
	//STOP_TICK(L"MoveFirstOrt");

	return false;
}

bool CBitMap_4s::MoveNextOrt(void)
{
	if(m_itCurrBox == m_NullCollection.end()) return false;
	//��� ������ ����� �� ���������
	if(IsEmpty()) return false;
	
	//START_TICK(L"MoveNextOrt");
	//������� �� ��������� ������������ ���
	//�������� � �������� ���������
	TBitBoxCollection::iterator itBox=m_itCurrBox; 
	unsigned int uiCurrPos=m_uiCurrBoxPos;
	while(itBox!=m_BitMapBoxes.end()){
		if(itBox->IsBitBox()){
			//�������� ����� ���������� ���� � ������� ���������
			m_ucCurrBitNumber=itBox->GetNextBitValue(m_ucCurrBitNumber+1);
			if(m_ucCurrBitNumber!=UC_EMPTY){
				//���� � ������ ��������� ���� ��� ���
				m_itCurrBox=itBox;
				m_uiCurrBoxPos=uiCurrPos;
				m_uiCurrBitValue=m_ucCurrBitNumber+(m_uiCurrBoxPos*cucBitBoxValueSize);
				return true;
			}else{
				//���� � ������ ��������� ��� ���������� ����, ��������� ������
				uiCurrPos++;
			}
		}else{
			//������� ��������� ������ �������� ���������� �������
			uiCurrPos+=itBox->Value;
		}
		itBox++;
	}

	//STOP_TICK(L"MoveNextOrt");
	
	//���� ���������� ���� ��� �������
	m_ucCurrBitNumber=UC_EMPTY;
	m_uiCurrBoxPos=EMPTY_VALUE;
	m_uiCurrBitValue=EMPTY_VALUE;
	m_itCurrBox=m_NullCollection.end();
	return false;
}

bool CBitMap_4s::MoveLastOrt(void)
{
	m_ucCurrBitNumber=UC_EMPTY;
	m_uiCurrBoxPos=EMPTY_VALUE;
	m_uiCurrBitValue=EMPTY_VALUE;

	//��� ������ ����� �� ���������
	if(IsEmpty()) return false;

	m_uiCurrBitValue=GetLastBitValue();
	return true;

	////������� �� ��������� ������������ ���
	//TBitBoxCollection::iterator itBox=m_BitMapBoxes.end(); 
	//unsigned int uiCurrPos=GetBitMapBoxSize()-1;
	//while(itBox--!=m_BitMapBoxes.begin()){
	//	if(itBox->IsBitBox()){
	//		m_ucCurrBitNumber=itBox->GetLastBitValue();
	//		if(m_ucCurrBitNumber==UC_EMPTY){
	//			TO_CONSOLE(L"GetLastBitValue error!");
	//			m_uiCurrBoxPos=EMPTY_VALUE;
	//			m_itCurrBox=NULL;
	//			return false;
	//		}else{
	//			m_itCurrBox=itBox;
	//			m_uiCurrBoxPos=uiCurrPos;
	//			m_uiCurrBitValue=m_ucCurrBitNumber+(m_uiCurrBoxPos*cucBitBoxValueSize);
	//			return true;
	//		}
	//	}else{
	//		uiCurrPos-=itBox->Value;
	//	}
	//}

	//return false;
}

void CBitMap_4s::MakeAnd(CValue* pValue)
{
	//������� ������� �����
	Merge(static_cast<CBitMap_4s*>(pValue), mmAND);
	//�������� ������� ��������	
	CValue::MakeAnd(pValue);
}

void CBitMap_4s::MakeSmoothAnd(CValue* pValue, unsigned int uiAdjacentSize)
{
	//������� ������� �����
	MergeAdjacent(static_cast<CBitMap_4s*>(pValue), uiAdjacentSize);
	//�������� ������� ��������	
	CValue::MakeSmoothAnd(pValue, uiAdjacentSize);
}

void CBitMap_4s::MakeOr(CValue* pValue)
{
	//������� ������� �����
	Merge(static_cast<CBitMap_4s*>(pValue), mmOR);
	//�������� ������� ��������	
	CValue::MakeOr(pValue);
}

void CBitMap_4s::Assign(CBitMap_4s* pBitMap)
{
	SetState(pBitMap->GetState());
	m_BitMapBoxes.assign(pBitMap->m_BitMapBoxes.begin(), pBitMap->m_BitMapBoxes.end());
	SetLastBitValue(pBitMap->GetLastBitValue());
}

bool CBitMap_4s::PreMerge(CBitMap_4s* pBitMap, EMergeMode MergeMode)
{
	if(ISNULL(pBitMap)) return true;

	//����� ������ ���� ���������� ��������
	if(GetBitMapSize()!=pBitMap->GetBitMapSize()){
		ERR_TO_CONSOLE(erNotEqual, L"GetBitMapSize");
		ToConsole(L"MergeMode", (unsigned int)MergeMode);
		ToConsole(L"This Box Size", GetBitMapSize());
		ToConsole(L"Input Box Size", pBitMap->GetBitMapSize());
		return true;
	}
	
	//��� ������ �������...
	switch(MergeMode)
	{
	//������� �������� �� �
	case mmAND:
		if(IsEmpty() || pBitMap->IsEmpty()){
			//���� ���� ���� ������ - ��������� ������
			Reset();
			return true;
		}

		if(IsFull() && pBitMap->IsFull()){
			//���� ��� ����� ������ ����� ������� ������� �� �����
			return true;
		}

		if(IsFull()){
			//���� ������ this �����, ������������ �� �������� ������
			Assign(pBitMap);
			return true;
		}

		if(pBitMap->IsFull()){
			//���� ������ ������� ����� ������� ������� �� �����
			return true;
		}
		break;
	//������� �������� �� ���
	case mmOR:
		if(IsFull()){
			//���� ������ - ��������� ������
			return true;
		}

		if(pBitMap->IsFull()){
			//���� ���� ���� ������ - ��������� ������
			Fill();
			return true;
		}

		if(IsEmpty() && pBitMap->IsEmpty()){
			//���� ��� ������ - ��������� ������
			return true;
		}

		if(IsEmpty()){
			//���� this ����� ������, ������������ �� �������� ������
			Assign(pBitMap);
			return true;
		}

		if(pBitMap->IsEmpty()){
			//���� ������� ����� ������ ������� ������� �� �����
			return true;
		}
		break;
	default:
		TO_CONSOLE(L"MergeMode undefined");
		return true;
		break;
	}
	
	return false;
}

void CBitMap_4s::Merge(CBitMap_4s* pBitMap, EMergeMode MergeMode)
{
	//��������� �������������� ���� ��� ������ ������ ������� �� �����
	if(PreMerge(pBitMap, MergeMode)) return;
	
	//if((unsigned int)MergeMode==1){
	//	ToConsole(L"Input:");
	//	View();
	//	pBitMap->View();
	//	ToConsole(L"MergeMode", (unsigned int)MergeMode);
	//}
	//����� ����������
	TBitBoxCollection ResultBitMapBoxes;

	SMoveInBitMap ThisMoveInBitMap;
	SMoveInBitMap ThatMoveInBitMap;
	SBitBox ResultBox;

	TBitBoxCollection::iterator  itThisBox=m_NullCollection.end();
	TBitBoxCollection::iterator  itThatBox=m_NullCollection.end();
	ThisMoveInBitMap.m_uiSteps=1;
	ThisMoveInBitMap.m_uiNotDoneSteps=0;
	ThatMoveInBitMap.m_uiSteps=1;
	ThatMoveInBitMap.m_uiNotDoneSteps=0;
	unsigned int uiTotalBoxesCount=0;

	GetNextBox(&m_BitMapBoxes, &itThisBox, &ThisMoveInBitMap);
	GetNextBox(&pBitMap->m_BitMapBoxes, &itThatBox, &ThatMoveInBitMap);
	while(itThisBox!=m_BitMapBoxes.end() && itThatBox!=pBitMap->m_BitMapBoxes.end()){

		//��������� �������� � �������, ���������� �� ������� ����� ���������� �������
		switch(MergeMode){
		case mmAND:
			ResultBox=MakeBoxAnd(&ThisMoveInBitMap, &ThatMoveInBitMap);
			break;
		case mmOR:
			ResultBox=MakeBoxOr(&ThisMoveInBitMap, &ThatMoveInBitMap);
			break;
		default:
			return;
		}

		//��������� ���� � ���������, ������� ����� ���������� ������
		uiTotalBoxesCount+=ResultBox.IsNullBox()?ResultBox.Value:1;
		AddResultBox(&ResultBitMapBoxes, ResultBox);
		
		//�������� ��������� ����� ��� ����������
		GetNextBox(&m_BitMapBoxes, &itThisBox, &ThisMoveInBitMap);
		GetNextBox(&pBitMap->m_BitMapBoxes, &itThatBox, &ThatMoveInBitMap);
	}

	//�������������
	switch(MergeMode){
	case mmAND:
		//������� ��������
		while(!ResultBitMapBoxes.empty() && ResultBitMapBoxes.back().IsNullBox()){ 
			uiTotalBoxesCount-=ResultBitMapBoxes.back().Value;
			ResultBitMapBoxes.pop_back();
		}
		if(ResultBitMapBoxes.empty())
			Reset();
		else
			//������������� �������� ���������� ����
			SetLastBitValue((cucBitBoxValueSize*(uiTotalBoxesCount-1))+ResultBitMapBoxes.back().GetLastBitValue());
		break;
	case mmOR:
		{
			TBitBoxCollection::iterator  itBox=m_NullCollection.end();
			TBitBoxCollection* pBitMapBoxes=NULL;
			SMoveInBitMap* MoveInBitMap=NULL;
			if(itThisBox!=m_BitMapBoxes.end()){
				itBox=itThisBox;
				pBitMapBoxes=&m_BitMapBoxes;
				MoveInBitMap=&ThisMoveInBitMap;
			}else if(itThatBox!=pBitMap->m_BitMapBoxes.end()){
				itBox=itThatBox;
				pBitMapBoxes=&pBitMap->m_BitMapBoxes;
				MoveInBitMap=&ThatMoveInBitMap;
				//������������� �������� ���������� ����
				SetLastBitValue(pBitMap->GetLastBitValue());
			}else if(itThisBox==m_BitMapBoxes.end() && itThatBox==pBitMap->m_BitMapBoxes.end()){
				//���� ������� ����� ����� ���������� ���������� ������
				//��������� ����� ������� ���
				if(pBitMap->GetLastBitValue()>GetLastBitValue())
					SetLastBitValue(pBitMap->GetLastBitValue());
			}
			
			if(itBox!=m_NullCollection.end()){
				//��������� ���������� ����� � �����
				if(itBox->IsNullBox())
					itBox->Value=MoveInBitMap->m_uiNotDoneSteps+1;
				ResultBitMapBoxes.push_back(*itBox);
				while(++itBox!=pBitMapBoxes->end()){
					ResultBitMapBoxes.push_back(*itBox);
				}
			}
		}
		break;
	default:
		return;
	}

	if(!ResultBitMapBoxes.empty() && ResultBitMapBoxes.back().IsNullBox()){
		TO_CONSOLE(L"Warning not correct result of merging");
		ToConsole(L"MergeMode", (unsigned int)MergeMode);
	}


	//��������� ���������
	m_BitMapBoxes.swap(ResultBitMapBoxes);
	
	//if((unsigned int)MergeMode==1){
	//	ToConsole(L"Result:");
	//	View();
	//}
}

void CBitMap_4s::AddResultBox(TBitBoxCollection* pBitBoxCollection, SBitBox ResultBox)
{
	if(!pBitBoxCollection->empty() && pBitBoxCollection->back().IsNullBox() && ResultBox.IsNullBox()){
		//������� ���� �������� ���������
		TBitBoxCollection::iterator  itLastBox=--pBitBoxCollection->end();
		unsigned char ucTemp=cucBitMaxNumberValue-itLastBox->Value;
		if(ucTemp!=0)
		{
			if(ResultBox.Value>ucTemp){
				itLastBox->Value+=ucTemp;
				ResultBox.Value-=ucTemp;
				pBitBoxCollection->push_back(ResultBox);
			}else{
				itLastBox->Value+=ResultBox.Value;
			}
		}else{
			//������ ��������� ����
			pBitBoxCollection->push_back(ResultBox);
		}
	}else{
		//������ ��������� ����
		pBitBoxCollection->push_back(ResultBox);
	}
}

void CBitMap_4s::GetNextBox(TBitBoxCollection* pBitBoxCollection, 
							   TBitBoxCollection::iterator*  pitCurrBox, 
							   SMoveInBitMap* pMoveInBitMap)
{
	if(pMoveInBitMap->m_uiSteps==0 && pMoveInBitMap->m_uiNotDoneSteps!=0)
		pMoveInBitMap->m_uiNotDoneSteps--;

	//��������� � ��������� �� �������� ����� ������ ���������� ��������� ����
	while(pMoveInBitMap->m_uiSteps){
		//������� ��������		
		if((*pitCurrBox)==m_NullCollection.end())
			(*pitCurrBox)=pBitBoxCollection->begin();
		else
			++(*pitCurrBox);
		
		if((*pitCurrBox)==pBitBoxCollection->end()){
			pMoveInBitMap->m_BitBox.Type=0;
			pMoveInBitMap->m_BitBox.SetNumber(cucBitMaxNumberValue);
			return;
		}

		if((*pitCurrBox)->IsNullBox()){
			if(pMoveInBitMap->m_uiSteps<(*pitCurrBox)->Value){
				pMoveInBitMap->m_uiNotDoneSteps=(*pitCurrBox)->Value-pMoveInBitMap->m_uiSteps;
				pMoveInBitMap->m_uiSteps=0;
				break;
			}else{
				pMoveInBitMap->m_uiSteps-=(*pitCurrBox)->Value;
			}
		}else{
			pMoveInBitMap->m_uiSteps--;
		}
	}

	pMoveInBitMap->m_BitBox=(**pitCurrBox);
}

SBitBox CBitMap_4s::MakeBoxAnd(SMoveInBitMap* pThisMoveInBitMap, SMoveInBitMap* pThatMoveInBitMap)
{
	pThisMoveInBitMap->m_uiSteps=1;
	pThatMoveInBitMap->m_uiSteps=1;

	SBitBox ResultBitBox;
	
	//���� ��� ��������, �������
	if(pThisMoveInBitMap->m_BitBox.IsBitBox() && pThatMoveInBitMap->m_BitBox.IsBitBox()){
		ResultBitBox.Type=cucBitBoxType;
		ResultBitBox.Value=pThisMoveInBitMap->m_BitBox.Value&pThatMoveInBitMap->m_BitBox.Value;
		//���� ��������� ������� ������ ���������
		if(!ResultBitBox.Value){
			ResultBitBox.Type=cucNullBoxType;
			ResultBitBox.Value=1;
		}
	}else{
		//� ��������� ������� ������� ������ ����������
		if(pThisMoveInBitMap->m_BitBox.IsBitBox()){
			pThisMoveInBitMap->m_BitBox.Type=cucNullBoxType;
			pThisMoveInBitMap->m_BitBox.SetNumber(1);
		}
		if(pThatMoveInBitMap->m_BitBox.IsBitBox()){
			pThatMoveInBitMap->m_BitBox.Type=cucNullBoxType;
			pThatMoveInBitMap->m_BitBox.SetNumber(1);
		}

		//���� ��� ��������, �������� ����������
		if(pThisMoveInBitMap->m_BitBox.IsNullBox() && pThatMoveInBitMap->m_BitBox.IsNullBox()){
			unsigned char ucMax=max(pThisMoveInBitMap->m_uiNotDoneSteps, pThatMoveInBitMap->m_uiNotDoneSteps);
			pThisMoveInBitMap->m_uiSteps+=ucMax-pThisMoveInBitMap->m_uiNotDoneSteps;
			pThatMoveInBitMap->m_uiSteps+=ucMax-pThatMoveInBitMap->m_uiNotDoneSteps;
			ResultBitBox.Type=cucNullBoxType;
			ResultBitBox.SetNumber(ucMax+1);
		}
	}

	pThisMoveInBitMap->m_uiNotDoneSteps=0;
	pThatMoveInBitMap->m_uiNotDoneSteps=0;
	return ResultBitBox;
}

SBitBox CBitMap_4s::MakeBoxOr(SMoveInBitMap* pThisMoveInBitMap, SMoveInBitMap* pThatMoveInBitMap)
{
	pThisMoveInBitMap->m_uiSteps=1;
	pThatMoveInBitMap->m_uiSteps=1;
	SBitBox ResultBitBox;
	
	//���� ��� ��������, �������
	if(pThisMoveInBitMap->m_BitBox.IsBitBox() && pThatMoveInBitMap->m_BitBox.IsBitBox()){
		ResultBitBox.Type=cucBitBoxType;
		ResultBitBox.Value=pThisMoveInBitMap->m_BitBox.Value|pThatMoveInBitMap->m_BitBox.Value;
		//���� ��������� ������� ������ ���������
		if(!ResultBitBox.Value){
			ResultBitBox.Type=cucNullBoxType;
			ResultBitBox.Value=1;
		}
		return ResultBitBox;
	}


	//� ��������� ������� ������� ������ ����������
	if(pThisMoveInBitMap->m_BitBox.IsNullBox() && pThatMoveInBitMap->m_BitBox.IsBitBox()){
		ResultBitBox=pThatMoveInBitMap->m_BitBox;
		pThisMoveInBitMap->m_uiSteps=pThisMoveInBitMap->m_uiNotDoneSteps==0?1:0;
	}

	if(pThatMoveInBitMap->m_BitBox.IsNullBox() && pThisMoveInBitMap->m_BitBox.IsBitBox()){
		ResultBitBox=pThisMoveInBitMap->m_BitBox;
		pThatMoveInBitMap->m_uiSteps=pThatMoveInBitMap->m_uiNotDoneSteps==0?1:0;
	}

	//���� ��� ��������, �������� ����������
	if(pThisMoveInBitMap->m_BitBox.IsNullBox() && pThatMoveInBitMap->m_BitBox.IsNullBox()){
		unsigned char ucMin=min(pThisMoveInBitMap->m_uiNotDoneSteps, pThatMoveInBitMap->m_uiNotDoneSteps);
		pThisMoveInBitMap->m_uiNotDoneSteps-=ucMin;
		pThatMoveInBitMap->m_uiNotDoneSteps-=ucMin;

		pThisMoveInBitMap->m_uiSteps=pThisMoveInBitMap->m_uiNotDoneSteps==0?1:0;
		pThatMoveInBitMap->m_uiSteps=pThatMoveInBitMap->m_uiNotDoneSteps==0?1:0;

		ResultBitBox.Type=cucNullBoxType;
		ResultBitBox.SetNumber(ucMin+1);
	}

	return ResultBitBox;
}

void CBitMap_4s::MergeAdjacent(CBitMap_4s* pBitMap, int iSizeAdjacent)
{
	if (IsEmpty() || pBitMap->IsFull()) return;

	if(pBitMap->IsEmpty() ) {
		Reset();
		return;
	}

	if(IsFull()) 
	{
		Merge(pBitMap, mmAND);
		return;
	}

	CBitMap_4s temp(m_uiBitMapSizeInBits);
	int bit1, bit2, i, n;
	if ( MoveFirstOrt() ) 
	{
		do{
			bit1=this->GetCurrentOrt();
			bit2=(bit1-iSizeAdjacent) >=0 ? (bit1-iSizeAdjacent):0;
			n=((int)(m_uiBitMapSizeInBits-1)>(bit1+iSizeAdjacent))?(bit1+iSizeAdjacent):m_uiBitMapSizeInBits-1;
			for ( i=bit2 ; i <= n; i++ ) 
				if ( pBitMap->HasOrt( i ) ) 
				{
					temp.SetOrt(bit1);
					break;
				}
		}while ( MoveNextOrt()) ;
	}
	m_BitMapBoxes.assign(temp.m_BitMapBoxes.begin(), temp.m_BitMapBoxes.end());
	SetState(temp.GetState());
	m_itCurrBox=temp.m_itCurrBox;
	m_uiCurrBoxPos=temp.m_uiCurrBoxPos;
}

void CBitMap_4s::Read(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return;
	
	START_TICK(L"CBitMap_4s::Read");
	//������ �������� ���������� ����
	unsigned int uiLastBitValue=ReadCompressed(pNdxStorage);
	SetLastBitValue(uiLastBitValue);

	//������ ���������� ������ � �������
	unsigned short usBitChunkNumber;
	pNdxStorage->Read((unsigned char*)&usBitChunkNumber, sizeof(unsigned short));

	//������ ���������� ������ � ������� �����
	unsigned char ucChunkSize; 
	pNdxStorage->Read((unsigned char*)&ucChunkSize, sizeof(unsigned char));
	
	//���������� ����� ���������� ������
	unsigned int uiTotalBoxNumber=(usBitChunkNumber-1)*cucBoxInBitChunk+ucChunkSize;
	
	//ToConsole(L"uiTotalBoxNumber", uiTotalBoxNumber);

	//����������� ������ ���������
	SBitBox BitBox;
	BitBox.Type=0;
	BitBox.SetNumber(0);
	m_BitMapBoxes.assign(uiTotalBoxNumber, BitBox);

	//������ ����� � �������, ��������� ������ ������
	CBitChunk* pTempBitChunk=NULL;
	unsigned char* pCurrentBox=((unsigned char*)(&m_BitMapBoxes.front()))+m_BitMapBoxes.size();
	while(usBitChunkNumber){
		pCurrentBox-=ucChunkSize;
		//������ ���������� �����
		pNdxStorage->Read(pCurrentBox, ucChunkSize);
		ucChunkSize=cucBoxInBitChunk;
		usBitChunkNumber--;
	}
	STOP_TICK(L"CBitMap_4s::Read");
	
	//View();
}

void CBitMap_4s::ToString(wstring& szValue)
{
	wchar_t buf[500];
	if(MoveFirstOrt()){
		do{
			wsprintf(buf, L" %u ", GetCurrentOrt());
			szValue.append(buf);
		}while(MoveNextOrt());
	}else{
		szValue.append(L"--empty--");
	}
}

void CBitMap_4s::View(void)
{
	wstring szValue=L"";
	if(IsFull()){
		szValue=L"BitMap Filled";
	}else{
		ToString(szValue);
	}

	ToConsole(L"//------BoxedBitMap:");
	ToConsole(szValue.c_str());
	ToConsole(L"//--End-of-BoxedBitMap");
}

//--------------------------------------------------------------------//

}
}
}
}
}