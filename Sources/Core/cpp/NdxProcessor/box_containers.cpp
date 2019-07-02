#include "StdAfx.h"
#include ".\box_containers.h"
#include ".\pool_client.h"

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

using namespace SS::Core::NdxSE::NdxProcessor::MemoryManagement;
using namespace SS::Interface::Core::NdxSE::NdxDataStorage;

//--------------------------------------------------------------------//

unsigned int CBitChunk::ToArray(vector<unsigned int>* pBitArray, unsigned int uiStartValue)
{
	if(!pBitArray) return uiStartValue;
	if(IsEmpty()) return uiStartValue;

	unsigned int uiValue=uiStartValue;
	unsigned char ucLastBox=0;
	do{
		if(m_BitBoxes[ucLastBox].Type==cucBitBoxType){
			//��� ����� � ������ ��������� ���������� ����
			for(unsigned char i=0; i<=cucBitMaxBitValue; i++){
				if(m_BitBoxes[ucLastBox].IsSetBit(i))
				{
					pBitArray->push_back(uiValue);
				}
				uiValue++;
			}
		}else{
			//��� �������� ����������� ��������
			uiValue+=m_BitBoxes[ucLastBox].Value*cucBitBoxValueSize;
		}

	}while(++ucLastBox<=m_ucLastBox);
	
	return uiValue;
}

//--------------------------------------------------------------------//

CBitMap::CBitMap(void)
:m_pTailBitChunk(NULL), m_usBitChunkNumber(0), m_uiLastBitValue(EMPTY_VALUE)
{
}

CBitMap::~CBitMap(void)
{
	Reset();
}

void CBitMap::Reset(void)
{
	CBitChunk* pTempBitChunk=NULL;
	while(m_pTailBitChunk){
		pTempBitChunk=m_pTailBitChunk->GetNextItem();
		delete m_pTailBitChunk;
		m_pTailBitChunk=pTempBitChunk;
	}

	m_pTailBitChunk=NULL;
	m_usBitChunkNumber=0;
	m_uiLastBitValue=EMPTY_VALUE;
}

bool CBitMap::AddBit(unsigned int uiBitValue)
{

 	if(uiBitValue==m_uiLastBitValue) return false;

	if(!m_pTailBitChunk)
		AddBitChunk();

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
		uiLastBitInBox=(unsigned int)m_pTailBitChunk->GetLastBitBox()->GetLastBitValue();
	}

	//��������� ��� � �����
	if(uiLastBitInBox+uiBitDistance<=cucBitMaxBitValue){
		//���� ����� �������� � ��������� ����, ���������
		if(m_pTailBitChunk->IsEmpty()) m_pTailBitChunk->AddBitBox();
		m_pTailBitChunk->GetLastBitBox()->SetBit(uiLastBitInBox+uiBitDistance);
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
			
			//��������� ���� �� �������
			if(m_pTailBitChunk->IsFull()){
				//���� ���� ����� ������ ��������� ��������� ���� 
				AddBitChunk();
			}

			//�������� � ���� �������
			m_pTailBitChunk->AddNullBox(uiValue);
			
			//��������� �������
			uiNullBoxNumber--;
		}
		
		//��������� ���� �� �������
		if(m_pTailBitChunk->IsFull()){
			//���� ���� ����� ������ ��������� ��������� ���� 
			AddBitChunk();
		}
		
		//��������� �������
		m_pTailBitChunk->AddBitBox();
		//���������� � ��� ������ ���
		m_pTailBitChunk->GetLastBitBox()->SetBit(ucBitValue);	
	}

	//������������� �������� ���������� ���� �����
	m_uiLastBitValue=uiBitValue;
	
	return true;
}

void CBitMap::AddBitChunk(void)
{
	CBitChunk* pTempBitChunk=new CBitChunk();
	pTempBitChunk->SetNextItem(m_pTailBitChunk);
	m_pTailBitChunk=pTempBitChunk;
	m_usBitChunkNumber++;
}

unsigned int CBitMap::Write(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return 0;

	unsigned int uiWritedBytes=0;
	//����� �������� ���������� ����
	unsigned int uiLastBitValue=GetLastBitValue();
	uiWritedBytes+=WriteCompressed(pNdxStorage, uiLastBitValue);
	//m_pNdxStorage->Append((unsigned char*)&uiLastBitValue, sizeof(unsigned int));
	
	//����� ���������� ������ � �������
	unsigned short usBitChunkNumber=GetBitChunkNumber();
	pNdxStorage->Append((unsigned char*)&usBitChunkNumber, sizeof(unsigned short));
	uiWritedBytes+=sizeof(unsigned short);

	//����� ���������� ������ � ������� �����
	CBitChunk* pTempBitChunk=GetTailBitChunk();
	unsigned char ucChunkSize=pTempBitChunk->GetBitBoxesNumber(); 
	pNdxStorage->Append((unsigned char*)&ucChunkSize, sizeof(unsigned char));
	while(pTempBitChunk){
		//����� ��������� ���� � �������
		unsigned char* pBuffer=pTempBitChunk->GetBitBoxBuffer();
		pNdxStorage->Append(pBuffer, ucChunkSize);
		uiWritedBytes+=ucChunkSize;
		ucChunkSize=cucBoxInBitChunk;
		pTempBitChunk=pTempBitChunk->GetNextItem();
	}

	//View();

	return uiWritedBytes;
}

void CBitMap::Read(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return;
	
	//������ �������� ���������� ����
	//unsigned int uiLastBitValue;
	//m_pNdxStorage->Read((unsigned char*)&uiLastBitValue, sizeof(unsigned int));
	//pBitMap->SetLastBitValue(uiLastBitValue);
	SetLastBitValue(ReadCompressed(pNdxStorage));

	//������ ���������� ������ � �������
	unsigned short usBitChunkNumber;
	pNdxStorage->Read((unsigned char*)&usBitChunkNumber, sizeof(unsigned short));
	SetBitChunkNumber(usBitChunkNumber);

	//������ ���������� ������ � ������� �����
	unsigned char ucChunkSize; 
	pNdxStorage->Read((unsigned char*)&ucChunkSize, sizeof(unsigned char));
	
	//������ ����� � �������, ��������� ������ ������
	CBitChunk* pTempBitChunk=NULL;
	while(usBitChunkNumber){

		if(pTempBitChunk){ 
			//���� ���� �� ������ ��������� � �������� � ������
			pTempBitChunk->SetNextItem(new CBitChunk());
			pTempBitChunk=pTempBitChunk->GetNextItem();
		}else{
			m_pTailBitChunk=new CBitChunk();
			pTempBitChunk=GetTailBitChunk();
		}
		
		//������ ���������� �����
		pNdxStorage->Read(pTempBitChunk->GetBitBoxBuffer(), ucChunkSize);
		pTempBitChunk->SetBitBoxesNumber(ucChunkSize);

		ucChunkSize=cucBoxInBitChunk;
		usBitChunkNumber--;
	}
	
	//View();
}

void CBitMap::ToString(wstring& szValue)
{
	//��������� ������ �������� ��������� ������
	list<CBitChunk*> BitChunkCollection;
	CBitChunk* pTempBitChunk=m_pTailBitChunk;
	while(pTempBitChunk){
		BitChunkCollection.push_front(pTempBitChunk);
		pTempBitChunk=pTempBitChunk->GetNextItem();
	}
	
	//��������� ������ �������� ������������ �����
	vector<unsigned int> BitArray;
	unsigned int uiBitValue=0;
	for(list<CBitChunk*>::iterator itBitChunk=BitChunkCollection.begin(); itBitChunk!=BitChunkCollection.end(); itBitChunk++){
		uiBitValue=(*itBitChunk)->ToArray(&BitArray, uiBitValue);
	}

	//��������� � ������
	if(BitArray.empty()){
		szValue.append(L"-empty-");
	}else{
		wchar_t buf[30];
		for(unsigned int i=0; i<BitArray.size(); i++){
			wsprintf(buf, L"%u ", BitArray[i]);
			szValue.append(buf);
		}
	}
}

void CBitMap::View(void)
{
	ToConsole(L"//-------Bof-CBitMap");
	wstring szValue;
	ToString(szValue);
	ToConsole(szValue.c_str());
	ToConsole(L"//-------Eof-CBitMap");
}

//--------------------------------------------------------------------//

}
}
}
}
}