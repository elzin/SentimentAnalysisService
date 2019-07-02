#pragma once

#include "..\ASDInterface\INdxDataStorage.h"
#include ".\box_containers.h"
#include ".\block_container.h"

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

///��������� - ������� ������������ ����, � ����������� ��������
///�������� �������� �� ����������� ����
class CCoordinateNode_4i : public CBinaryContainer
{
public:
	///��������� �������� � ���������, ���������� true ���� �������� ���������
	virtual bool AddCoordinate(unsigned int uiValue) = 0;	
	///��������� �������� �� ����������� ����
	virtual void AddChildOffset(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset){};	
	///���������� � ����������� �� ����� ��������� �������� �� ������� ����������� ����
	virtual void PopLastChildOffset(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset){};	
	///��������� ����������� ����
	virtual void AddChild(CCoordinateNode_4i* pCoordinateNode){};	
	///��������� � ����������� �� ����� ��������� ������� ����������� ����
	virtual void PopLastChild(CCoordinateNode_4i* pCoordinateNode){};	
	///���������� ����
	virtual void ResetNode(void) = 0;	
	///���������� ���� ������� ����
	virtual bool IsEmptyNode(void) = 0;	

protected:
	///������� 4 ����� � ����� � ����
	unsigned int WriteCompressed(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage, unsigned int uiValue)
	{
		return CBinaryContainer::WriteCompressed(pNdxStorage, uiValue);
	}
	///������ � ��������� � 4 ����� �� ����
	unsigned int ReadCompressed(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage)
	{
		return CBinaryContainer::ReadCompressed(pNdxStorage);
	}
};

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ � ������� �����
///�������� �������� �� ����������� ����
///�������� ������������ ������ ������ � ���������
#pragma pack(push,1)  // Fix packing size 
class CBmCoordinateNode_4i : 
	public CBitMap,
	public CBlockBufferPusher<cucBmCoordinateNode_BlockBufferSize>,
	public CCoordinateNode_4i
	,
	public SS::Core::NdxSE::NdxProcessor::MemoryManagement::CPoolClient
{
public:
	CBmCoordinateNode_4i(void):m_pucChildData(NULL), m_uiChildDataSize(0){};
	~CBmCoordinateNode_4i(void){ResetNode();};

	///��������� �������� � ���������, ���������� true ���� �������� ���������
	bool AddCoordinate(unsigned int uiValue);	
	///��������� �������� �� ����������� ����
	void AddChildOffset(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset);	
	///���������� � ����������� �� ����� ��������� �������� �� ������� ����������� ����
	void PopLastChildOffset(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset);	
	///���������� ����
	void ResetNode(void);	
	///���������� ���� ������� ����
	bool IsEmptyNode(void);	

	///����� ���������� ���������� � ���������
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);

protected:
	///����� � ������� �� �����	
	unsigned char* m_pucChildData;
	///������ ������ � ������� �� �����	
	unsigned int m_uiChildDataSize;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ � ������� �����
///�������� ����������� ����
///�������� ������������ ������ ������ � ���������
#pragma pack(push,1)  // Fix packing size 
class CBmCoordinateNode_4i_Heavy : 
	public CBmCoordinateNode_4i
{
public:
	CBmCoordinateNode_4i_Heavy(void):m_uiLastChildSize(0){};

	///��������� �������� �� ����������� ����
	void AddChildOffset(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset){};	
	///���������� � ����������� �� ����� ��������� �������� �� ������� ����������� ����
	void PopLastChildOffset(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset){};	
	///��������� ����������� ����
	void AddChild(CCoordinateNode_4i* pCoordinateNode);	
	///��������� � ����������� �� ����� ��������� ������� ����������� ����
	void PopLastChild(CCoordinateNode_4i* pCoordinateNode);	

	///����� ���������� ���������� � ���������
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

protected:
	unsigned int m_uiLastChildSize;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ ������� ByteAlign
///�������� ������������ ������ ������ � ���������
#pragma pack(push,1)  // Fix packing size 
class CBaCoordinateNode_4i : 
	public CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>,
	public CCoordinateNode_4i
	,
	public SS::Core::NdxSE::NdxProcessor::MemoryManagement::CPoolClient
{
public:
	CBaCoordinateNode_4i(void):m_uiLastValue(EMPTY_VALUE){};

	///��������� �������� � ���������, ���������� true ���� �������� ���������
	bool AddCoordinate(unsigned int uiValue);	
	///���������� ����
	void ResetNode(void);	
	///���������� ���� ������� ����
	bool IsEmptyNode(void);	

	///����� ���������� ���������� � ���������
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize);
	///������� � �����
	void ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBuffer);

	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);
	///���������� ���������� ������� ������
	void View(void);
	///������������ � ������
	void ToString(wstring& szValue);

protected:
	///��������� ����������� ��������
	unsigned int m_uiLastValue;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ ������� ByteAlign
///�������� ������������ ������ ������ � ���������
///�������� ������ ������, ������������� �������� ������ ������ �� �����
#pragma pack(push,1)  // Fix packing size 
class CBaCoordinateNode_4i_Blocked : 
	public CBaCoordinateNode_4i
{
public:
	CBaCoordinateNode_4i_Blocked(void):m_InBlockValuesNumber(cuiPositionBlockSize){};

	///��������� �������� � ���������, ���������� true ���� �������� ���������
	bool AddCoordinate(unsigned int uiValue);	
	///���������� ����
	void ResetNode(void);	

	///����� ���������� ���������� � ���������
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize);
	///������� � �����
	void ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBuffer);

	///���������� ���������� ������� ������
	void View(void);
	///������������ � ������
	void ToString(wstring& szValue);

protected:
	///������� ����� ��� �������� �������� �� �������
	CBlockBuffer<cucBaCoordinateNode_BlockBufferSize> m_OffsetsBuffer;
	///���������� ������� � �����
	unsigned char m_InBlockValuesNumber;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

}
}
}
}
}