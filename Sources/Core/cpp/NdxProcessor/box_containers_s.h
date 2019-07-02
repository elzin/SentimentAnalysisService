#pragma once

#include ".\box_containers.h"

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

///������� ����� �������� ��������� SBitBox (������������ ��� ������)
class CBitMap_4s : public CCompositeValue, public CBinaryContainer
{
public:
	typedef vector<SBitBox> TBitBoxCollection;

	///���������� ��������� ������� �����
	enum EBitMapState{
		//�������������
		esIntermediate,
		//����� ������ (��� ���� ����������)
		esFull,
		//����� ������ (�� ���� ��� �� ���������)
		esEmpty
	};

	CBitMap_4s(unsigned int uiBitMapSize, EBitMapState eBitMapState = esEmpty);
	
	///���������� �������� �����
	unsigned char* GetBinaryBuffer(void){return (unsigned char*)&(m_BitMapBoxes.front());};	
	///���������� ������ ��������� ������
	unsigned int GetBinaryBufferSize(void){return (unsigned int)m_BitMapBoxes.size();};	
	///������������� ����� ������ ��������� ������, ����� �������
	void InitBinaryBuffer(unsigned int uiNewSize)
	{
		SBitBox BitBox;
		memset((void*)&BitBox, 0, 1);
		m_BitMapBoxes.assign(uiNewSize, BitBox);
		if(!m_BitMapBoxes.empty()) SetNotEmpty();
	};
	
	///��������� �������� �����, �� ��������� ������
	void FillBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize)
	{
		if(ISNULL(pBuffer)) return;
		if(ISNULL(uiBufferSize)) return;

		InitBinaryBuffer(uiBufferSize);
		memcpy(GetBinaryBuffer(), pBuffer, GetBinaryBufferSize());
	};

	///���������� ������ ������� ����� � �����
	unsigned int GetBitMapSize(void){return m_uiBitMapSizeInBits;};	
	///���������� ��������� �� ����� ������
	TBitBoxCollection* GetBoxBuffer(void){return &m_BitMapBoxes;};	
	///���������� ������������ ������ ������� ����� � ������
	unsigned int GetBitMapBoxSize(void);
	
	///������ ����� ������
	void Fill(void);
	///��������� ����� �� �������������
	bool IsFull(void){return GetState()==esFull?true:false;};
	///���������� ������� ���������
	EBitMapState GetState(void){return m_eBitMapState;};	
	///������������� �������� ���������� ���� �����
	void SetLastBitValue(unsigned int uiValue){m_uiLastBitValue=uiValue; if(m_uiLastBitValue!=EMPTY_VALUE) SetNotEmpty();};
	///���������� �������� ���������� ���� �����
	unsigned int GetLastBitValue(void){return m_uiLastBitValue;};


	//-----------CValue
	///��������� �������� AND 
	void MakeAnd(CValue* pValue);
	///��������� �������� AND �� ������������
	void MakeSmoothAnd(CValue* pValue, unsigned int uiAdjacentSize);
	///��������� �������� OR
	void MakeOr(CValue* pValue);
	///��������� �� �������
	bool IsEmpty(void){return GetState()==esEmpty?true:false;};
	///���������� �������� �� ������
	void Reset(void);
	//-----------Eof-CValue

	//-----------CCompositeValue
	///���������� ������ ��� � �����
	bool SetOrt(unsigned int uiBitPos);	
	///��������� ��������� �� ������ ��� � �����
	bool HasOrt(unsigned int uiBitPos);
	///��������������� �� ������ ������������
	bool MoveFirstOrt(void);
	///��������������� �� �������� ������������
	bool MoveNextOrt(void);
	///��������������� �� ��������� ������������
	bool MoveLastOrt(void);
	///���������� ������� ������������
	unsigned int GetCurrentOrt(void){return m_uiCurrBitValue;};
	///���������� ���������� ������������
	unsigned int GetOrtsMaxNumber(void){return GetBitMapSize();};
	//-----------Eof-CCompositeValue

	///������ ���������� ���������� �� �����
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	//-----------CConsoleClient
	///������������ � ������
	void ToString(wstring& szValue);
	///���������� ���������� ������� ������
	void View(void);
	//-----------Eof-CConsoleClient

protected:
	///����� ��������
	enum EMergeMode{
		///�������� �� �
		mmAND,
		///�������� �� ���
		mmOR
	};
	
	///���������� ��� ������������ �� �����
	struct SMoveInBitMap
	{
		///������� ����
		SBitBox m_BitBox; 
		///���������� ����� �� ������� ���� ����������
		unsigned int m_uiSteps;
		///���������� ����� �� ������� �� ����������
		unsigned int m_uiNotDoneSteps;
	};
	
	///������������ ������ ����� �������
	void Assign(CBitMap_4s* pBitMap);
	///���� (������� ������ � ������) ������� ������ ������ ����� �� ������� � ������������ � �������
	bool PreMerge(CBitMap_4s* pBitMap, EMergeMode MergeMode);
	///������� ������ ������ ����� �� ������� � ������������ � �������
	void Merge(CBitMap_4s* pBitMap, EMergeMode MergeMode);
	///��������� ���� ��������� � ��������
	void AddResultBox(TBitBoxCollection* pBitBoxCollection, SBitBox ResultBox);
	///������� ����� �� � ���������� ���������, ��������� ��������
	SBitBox MakeBoxAnd(SMoveInBitMap* pThisMoveInBitMap, SMoveInBitMap* pThatMoveInBitMap);
	///������� ����� �� ��� ���������� ���������, ��������� ��������
	SBitBox MakeBoxOr(SMoveInBitMap* pThisMoveInBitMap, SMoveInBitMap* pThatMoveInBitMap);
	///��������� � ���������� ����� � ��������� �������� SMoveInBitMap
	void GetNextBox(TBitBoxCollection* pBitBoxCollection, 
		TBitBoxCollection::iterator*  pitCurrBox, SMoveInBitMap* pMoveInBitMap);


	///������� ������ ����� � ������ ���������
	void MergeAdjacent(CBitMap_4s* pBitMap, int m_iSizeAdjacent);

	///������������� ������� ���������
	void SetState(EBitMapState eBitMapState){m_eBitMapState=eBitMapState;};	
	///���������� ���� ������ �����
	void SetNotEmpty(void){m_eBitMapState=esIntermediate;};
	///��������� ��� � ����� �����
	bool AddBit(unsigned int uiBitValue);
	
	///������ �������� �����
	TBitBoxCollection m_BitMapBoxes;
	///������� ��������� ��� ������
	TBitBoxCollection::iterator m_itCurrBox;
	///��������� ��� ������������� ����������
	TBitBoxCollection m_NullCollection;
	///������ ������� ����� � �����
	unsigned int m_uiBitMapSizeInBits;
	///���������� ������� �������� ��������� ��� ������
	unsigned int m_uiCurrBoxPos;
	///����� �������� ��c���������� ���� � ��������� ��� ������
	unsigned char m_ucCurrBitNumber;
	///�������� �������� ��c���������� ���� � ��������� ��� ������
	unsigned int m_uiCurrBitValue;
	///���������� �������� ���������� ���� � �����
	unsigned int m_uiLastBitValue;
	///���������  �����
	EBitMapState m_eBitMapState;	
};

//--------------------------------------------------------------------//

}
}
}
}
}