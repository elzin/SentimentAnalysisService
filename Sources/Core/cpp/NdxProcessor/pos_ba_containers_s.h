#pragma once

#include ".\pos_containers.h"

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


///��������� ������� � ������������� ���������� �������� 
///� ����������� ������� ������������ ��� ������
class CPosBaCntSearch : public CPosCnt
{
public:
	CPosBaCntSearch(void);
	virtual ~CPosBaCntSearch(void);
	
	///������ ���������� ���������� �� �����
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize);
	//���������� �������� �����
	CByteAlignCompress::TBytesBuffer* GetBuffer(void){return m_pBuffer;};

	///���������� �������� �� ������
	virtual void Reset(void);

	//����� ������������ ������������
	///��������������� �� ������ ������������
	bool MoveFirstOrt(void);
	///��������������� �� �������� ������������
	bool MoveNextOrt(void);

	///���������� ������� ������������
	unsigned int GetCurrentOrt(void){return m_uiCurrentPosition;};
	///���������� ���������� ������������ ��������
	unsigned int GetOrtsNumber(void);
	///��������� �� �������
	bool IsEmpty(void){return (unsigned int)m_pBuffer->size()==0?true:false;};

	///���������� ������ �������
	unsigned int GetFirstPosition(void);
	///���������� ��������� �������
	unsigned int GetLastPosition(void){return m_uiLastPosition;};
	///���������� ������ ��������� �������, ������� ����������� ���������
	virtual unsigned int GetPositionRangeLength(void){return GetLastPosition()-GetFirstPosition();};
	
	///��������� ��������� �� ���������������
	bool IsEqual(CPosBaCntSearch* pPosBaCntSearch);

	///���������� ���������� ������� ������
	void View(void);
	///������������ � ������
	void ToString(wstring& szValue);
	
protected:
	///������� ���� � ������ ����������
	unsigned int m_uiCurrByte;
	///������� ������� � ����������
	unsigned int m_uiCurrentPosition;
	///���������� ������� � ����������
	unsigned int m_uiPositionsNumber;
	///���� ������� ���������� �������
	bool m_bPositionsNumberFixed;
	///����� � �������� ����������
	CByteAlignCompress::TBytesBuffer* m_pBuffer;
};

//--------------------------------------------------------------------//

///��������� ������� � ������������� ���������� �������� 
///� ����������� ������� ������������ ��� ������
///������� �������� ������, ���� ����������� �������� � ������������ ������� ��� ������� ��������
class CPosBaCntSearch_Blocked : public CPosBaCntSearch
{
public:
	///���������� �� �����
	struct SBlockInfo
	{
		//�������� �����
		unsigned int m_uiBlockOffset;
		//����� �����
		unsigned int m_uiBlockNumber;
	};

	typedef map<unsigned int, SBlockInfo> TBlockOffsets;

	CPosBaCntSearch_Blocked(void)
		:m_uiCurrentPositionIndex(EMPTY_VALUE), m_InLastBlockValuesNumber(0){};

	///���������� �������� �� ������
	void Reset(void);

	///������ ���������� ���������� �� �����
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize);

	//����� ������������ ������������
	///��������������� �� ������ ������������
	bool MoveFirstOrt(void);
	///��������������� �� ������������, ������� ������ ��� ����� ��������
	bool MoveLowerBoundOrt(unsigned int uiValue);
	///��������������� �� �������� ������������
	bool MoveNextOrt(void);

	///���������� ���������� ������������ ��������
	unsigned int GetOrtsNumber(void){return m_uiPositionsNumber;};
	/////���������� ������ ��������� �������, ������� ����������� ���������
	//unsigned int GetPositionRangeLength(void){return GetOrtsNumber();};

protected:
	///��������� ��������� �������� ������ ������������ �� ������ ��������
	void FillBlockOffsets(unsigned char* pBuffer, unsigned int uiBufferSize);

	///��������� �������� ������ ������������ �� ������ ��������
	TBlockOffsets m_BlockOffsets;
	///���������� ����� ������� ������� � ����������
	unsigned int m_uiCurrentPositionIndex;
	///���������� ������� � �����
	unsigned char m_InLastBlockValuesNumber;
};

//--------------------------------------------------------------------//

}
}
}
}
}