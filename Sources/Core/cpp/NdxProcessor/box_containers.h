#pragma once
#include ".\list_containers.h"
#include ".\pool_client.h"
#include ".\consoleclient.h"
#include ".\basis_containers.h"

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

//--------------------------------------------------------------------//

///������ ����� ��� ��������� ����� � �����
const unsigned char carrBitBoxMasks[]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};
///������������ �������� ���� � �����
const unsigned char cucBitMaxBitValue=0x06;
///������������ ����� �������� � �����
const unsigned char cucBitMaxNumberValue=0x7f;
///������������ ���������� ����� � �����
const unsigned char cucBitBoxValueSize=0x07;
///��� NullBox
const unsigned char cucNullBoxType=0x00;
///��� BitBox
const unsigned char cucBitBoxType=0x01;
///����� ������� ��������
const unsigned char cucFullBitBox=0xff;

/// ��������� �����.
/// ������ ��������: 
///	8-���: 
///	1. ������ ���-���� ���������� ��� : ValBox ��� NullBox
/// 2. ��������� 7 ��� ��������
/// ValBox: �������� 7 �������� ����� - 7-������� ������� ������ ������� �����
/// ���-���� ����� 1
/// NullBox: �������� 7 �������� �����, ��� ���������� �� 0-128 ���������� 7-����� � ������� ��� ����������� �����
/// ���-���� ����� 0
/// ���� Value � Type ����� ���� SBitBox �����������
#pragma pack(push,1)  // Fix packing size 
struct SBitBox
{
	///���������� �����
	unsigned char
	///������� ���� ���������� ����������
	Value:7,
	///������� ��� ���������� ���
	Type:1;
	
	///���������� �������� ���������� ���� � �����
	unsigned char GetLastBitValue(void)
	{
		for(/*unsigned*/ char i = cucBitMaxBitValue; i>=0; i--)
			if(Value&carrBitBoxMasks[i]) return i;
		return 0xff;
	}

	///���������� �������� ������� ���� � �����
	unsigned char GetFirstBitValue(void)
	{
		for(unsigned char i=0; i<=cucBitMaxBitValue; i++)
			if(Value&carrBitBoxMasks[i]) return i;
		return 0xff;
	}

	///���������� �������� ���� � ����� ����� ���������
	unsigned char GetNextBitValue(unsigned char ucFrom)
	{
		for(unsigned char i=ucFrom; i<=cucBitMaxBitValue; i++)
			if(Value&carrBitBoxMasks[i]) return i;
		return 0xff;
	}

	///���������� ��� � ����� (�������� ����� ���� 0-6)
	void SetBit(unsigned char ucBitValue)
	{
		if(ucBitValue>cucBitMaxBitValue) return;
		Value|=carrBitBoxMasks[ucBitValue];
	}

	///������� ��� � ����� (�������� ����� ���� 0-6)
	void UnSetBit(unsigned char ucBitValue)
	{
		if(ucBitValue>cucBitMaxBitValue) return;
		Value&=(~carrBitBoxMasks[ucBitValue]);
	}

	///��������� ���������� �� ��� � ����� (�������� ����� ���� 0-6)
	bool IsSetBit(unsigned char ucBitValue)
	{
		if(ucBitValue>cucBitMaxBitValue) return false;
		return (Value&(carrBitBoxMasks[ucBitValue]))==0?false:true;
	}

	///���������� ����� � �����
	void SetNumber(unsigned char ucValue)
	{
		Value=ucValue&cucBitMaxNumberValue;
	}

	///��������� ����������� �� ����
	bool IsUndefined(void){return (Value==0 && Type==0)?true:false;};
	///��������� ��� �����
	bool IsBitBox(void){return Type==cucBitBoxType?true:false;};
	///��������� ��� �����
	bool IsNullBox(void){return Type==cucNullBoxType?true:false;};
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///������������ ���������� ��������� � �����
const unsigned char cucBoxInBitChunk=0x08;
///����� ������� �����
const unsigned char carrFullNullBoxChunk[]={0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f};
///����� ������� �����
const unsigned char carrFullBitBoxChunk[]={0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

///���� SBitBox-�� 
#pragma pack(push,1)  // Fix packing size 
class CBitChunk : 
	public SS::Core::NdxSE::NdxProcessor::MemoryManagement::CPoolClient
{
public:
	CBitChunk():m_ucLastBox(cucBoxInBitChunk), m_pNextItem(NULL){memset(m_BitBoxes, 0, cucBoxInBitChunk);};

	///��������� ���� ������� ����������
	void FillByNullBox(void){memcpy(m_BitBoxes, carrFullNullBoxChunk, cucBoxInBitChunk);m_ucLastBox=cucBoxInBitChunk-1;};
	///��������� ���� ������� ����������
	void FillByBitBox(void){memcpy(m_BitBoxes, carrFullBitBoxChunk, cucBoxInBitChunk);m_ucLastBox=cucBoxInBitChunk-1;};
	///��������� � ����� �������
	void AddNullBox(unsigned char ucValue)
	{
		if(IsFull()) return;
		m_ucLastBox==cucBoxInBitChunk?m_ucLastBox=0:m_ucLastBox++;

		m_BitBoxes[m_ucLastBox].Type=cucNullBoxType;
		m_BitBoxes[m_ucLastBox].SetNumber(ucValue);
	};
	///��������� � ����� �������
	void AddBitBox()
	{
		if(IsFull()) return;
		m_ucLastBox==cucBoxInBitChunk?m_ucLastBox=0:m_ucLastBox++;

		m_BitBoxes[m_ucLastBox].Type=cucBitBoxType;
	};
	///�������� �� �������
	bool IsEmpty(void){return m_ucLastBox<cucBoxInBitChunk?false:true;};
	///�������� �� �������
	bool IsFull(void){return m_ucLastBox==(cucBoxInBitChunk-1)?true:false;};
	///���������� ������� �������
	SBitBox* GetLastBitBox(void){return IsEmpty()?NULL:&(m_BitBoxes[m_ucLastBox]);};
	///������������ � ������ �����
	unsigned int ToArray(vector<unsigned int>* pBitArray, unsigned int uiStartValue);

	///���������� ��������� ���� � ������
	CBitChunk* GetNextItem(void){return m_pNextItem;};
	///������������� ��������� ���� � ������
	void SetNextItem(CBitChunk* pNextItem){m_pNextItem=pNextItem;};

	///���������� ��������� �� ����� � �������
	unsigned char* GetBitBoxBuffer(void){return (unsigned char*)m_BitBoxes;};
	///���������� ������ ������ ��������� ������ � ������
	unsigned char GetBitBoxesNumber(void){return m_ucLastBox+1;}; 
	///������������� ������ ������ ��������� ������ � ������
	void SetBitBoxesNumber(unsigned char ucValue){ucValue==0?m_ucLastBox=cucBoxInBitChunk:m_ucLastBox=ucValue-1;}; 
	///��������� �������� �����, �� ��������� ������
	void FillBitBoxBuffer(unsigned char* pBoxBuffer, unsigned char ucBoxNumber = cucBoxInBitChunk)
	{
		if(ISNULL(pBoxBuffer)) return;
		if(ISNULL(ucBoxNumber)) return;

		memcpy(m_BitBoxes, pBoxBuffer, ucBoxNumber);
	};

protected:
	///���� SBitBox
	SBitBox m_BitBoxes[cucBoxInBitChunk];
	///��������� ����
	CBitChunk* m_pNextItem;
	///������ ��������� SBitBox, 
	///���� ����� cucBoxInBitChunk-1 ���� ������, ���� ����� cucBoxInBitChunk ���� ������
	unsigned char m_ucLastBox;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///������� ����� �������� ������ CBitChunk-�� (������������ ��� ����������)
#pragma pack(push,1)  // Fix packing size 
class CBitMap : public CConsoleClient, public CBinaryContainer
{
public:
	CBitMap(void);
	virtual ~CBitMap(void);

	///���������� �������� ���������� ���� �����
	unsigned int GetLastBitValue(void){return m_uiLastBitValue;};
	///��������� ��� � ������� �����
	bool AddBit(unsigned int uiBitValue);	

	///���������� ��������� ���� CBitChunk � �����
	CBitChunk* GetTailBitChunk(void){return m_pTailBitChunk;};
	///���������� ��������� CBitChunk ������ ������� �������� �����
	unsigned short GetBitChunkNumber(void){return m_usBitChunkNumber;};
	///������������� ��������� CBitChunk ������ ������� �������� �����
	void SetBitChunkNumber(unsigned short usValue){m_usBitChunkNumber=usValue;};
	///������������� �������� ���������� ���� �����
	void SetLastBitValue(unsigned int uiValue){m_uiLastBitValue=uiValue;};
	///���������� ������� �����
	void Reset(void);	
	///���������� ���� ������ ������� �����
	bool IsEmpty(void){return m_pTailBitChunk==NULL?true:false;};	

	///����� ���������� ���������� � ����
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///������ ���������� ���������� �� �����
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	///������������ � ������
	void ToString(wstring& szValue);
	///���������� ���������� ������� ������
	void View(void);

protected:
	///��������� CBitChunk
	void AddBitChunk(void);

	///��������� ���� CBitChunk � �����
	CBitChunk* m_pTailBitChunk;
	///���������� �������� ���������� ���� � �����
	unsigned int m_uiLastBitValue;
	///��������� CBitChunk ������ ������� �������� �����
	unsigned short m_usBitChunkNumber;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

}
}
}
}
}