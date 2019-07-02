#include "StdAfx.h"

#include ".\index_container_nodes.h"
#include ".\pos_ba_containers_s.h"

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

bool CBmCoordinateNode_4i::AddCoordinate(unsigned int uiValue)	
{
	//��������� ��� �� �������� � ����� ��
	//START_TICK(L"AddBit");
	return AddBit(uiValue);
	//STOP_TICK(L"AddBit");
}

void CBmCoordinateNode_4i::AddChildOffset(SCompositeOffset* pCompositeOffset)
{
	if(ISNULL(pCompositeOffset)) return;
	PushBack((unsigned char*)pCompositeOffset, sizeof(SCompositeOffset));
}

void CBmCoordinateNode_4i::PopLastChildOffset(SCompositeOffset* pCompositeOffset)
{
	if(ISNULL(pCompositeOffset)) return;
	//PopBack((unsigned char*)pCompositeOffset, sizeof(SCompositeOffset));

	if(ISNULL(m_pucChildData)) return;
	if(ISNULL(m_uiChildDataSize)) return;
	
	m_uiChildDataSize-=sizeof(SCompositeOffset);
	memcpy((unsigned char*)pCompositeOffset, m_pucChildData+m_uiChildDataSize, sizeof(SCompositeOffset));
}

void CBmCoordinateNode_4i::ResetNode(void)
{
	CBitMap::Reset();
	CBlockBufferPusher<cucBmCoordinateNode_BlockBufferSize>::Reset();
	if(m_pucChildData) free(m_pucChildData);
	m_pucChildData=NULL;
	m_uiChildDataSize=0;
}

bool CBmCoordinateNode_4i::IsEmptyNode(void)
{
	return CBitMap::IsEmpty();
}

unsigned int CBmCoordinateNode_4i::Write(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return 0;

	unsigned int uiWritedBytes=0;

	//����� ������� �����
	uiWritedBytes+=CBitMap::Write(pNdxStorage);
	
	//���������� ����� ������
	unsigned int uiTotalSize=m_uiChildDataSize+CBlockBufferPusher<cucBmCoordinateNode_BlockBufferSize>::GetBinaryBufferSize();

	//����� ����� ������
	uiWritedBytes+=CCoordinateNode_4i::WriteCompressed(pNdxStorage, uiTotalSize);

	//����� ����� ��������� � ���������� ������
	if(m_pucChildData && m_uiChildDataSize){
		pNdxStorage->Append(m_pucChildData, m_uiChildDataSize);
		uiWritedBytes+=m_uiChildDataSize;
	}

	//����� ��������� �������� �� ����������� ����
	uiWritedBytes+=CBlockBufferPusher<cucBmCoordinateNode_BlockBufferSize>::Write(pNdxStorage);

	return uiWritedBytes;
}

void CBmCoordinateNode_4i::Read(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return;

	//������ ������� �����
	CBitMap::Read(pNdxStorage);
	////������ ��������� �������� �� ����������� ����
	//CBlockBuffer<cucBmCoordinateNode_BlockBufferSize>::Read(pNdxStorage);

	//������ ������ ������
	m_uiChildDataSize=CCoordinateNode_4i::ReadCompressed(pNdxStorage);
	
	//�������� ����� � ������ � ���� ������
	if(m_pucChildData) free(m_pucChildData);
	m_pucChildData=(unsigned char*)malloc(m_uiChildDataSize);
	pNdxStorage->Read(m_pucChildData, m_uiChildDataSize);
}

void CBmCoordinateNode_4i::ToString(wstring& szValue, wstring szOffset)
{
	szOffset.append(L" ");	
	szValue.append(L"\n");
	szValue.append(szOffset);
	szValue.append(L"|");
	//wchar_t buf[30];
	//wsprintf(buf, L"%u", m_cuiValue);
	//szValue.append(buf);
	szValue.append(L"-->");
	CBitMap::ToString(szValue);
}

//--------------------------------------------------------------------//

void CBmCoordinateNode_4i_Heavy::AddChild(CCoordinateNode_4i* pCoordinateNode)
{
	if(ISNULL(pCoordinateNode)) return;
	
	//�������� ����� ��� ����������� ����
	CByteAlignCompress::TBytesBuffer ChildBuffer;

	//����������� �������� ���������� ������������ ����
	pCoordinateNode->ToBinaryBuffer(&ChildBuffer);
	m_uiLastChildSize=(unsigned int)ChildBuffer.size();

	//��������� ����� ����
	PushBack(&ChildBuffer.front(), m_uiLastChildSize);
}

void CBmCoordinateNode_4i_Heavy::PopLastChild(CCoordinateNode_4i* pCoordinateNode)
{
	if(ISNULL(pCoordinateNode)) return;
	if(ISNULL(m_uiLastChildSize)) return;
	
	//�������� ����� ��� ����������� ����
	unsigned char* pChildBuffer=(unsigned char*)malloc(m_uiLastChildSize);

	//����������� �������� ���������� ������������ ����
	//PopBack(pChildBuffer, m_uiLastChildSize);
	if(ISNULL(m_pucChildData)) return;
	if(ISNULL(m_uiChildDataSize)) return;
	m_uiChildDataSize-=m_uiLastChildSize;
	memcpy(pChildBuffer, m_pucChildData+m_uiChildDataSize, m_uiLastChildSize);

	//��������� ����� ����
	pCoordinateNode->FromBinaryBuffer(pChildBuffer, m_uiLastChildSize);

	//����������� �����
	free(pChildBuffer);
	m_uiLastChildSize=0;
}

unsigned int CBmCoordinateNode_4i_Heavy::Write(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return 0;

	unsigned int uiWritedBytes=0;

	//�����
	uiWritedBytes+=CBmCoordinateNode_4i::Write(pNdxStorage);
	uiWritedBytes+=CCoordinateNode_4i::WriteCompressed(pNdxStorage, m_uiLastChildSize);

	return uiWritedBytes;
}

void CBmCoordinateNode_4i_Heavy::Read(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return;

	//������
	CBmCoordinateNode_4i::Read(pNdxStorage);
	m_uiLastChildSize=CCoordinateNode_4i::ReadCompressed(pNdxStorage);
}

//--------------------------------------------------------------------//

bool CBaCoordinateNode_4i::AddCoordinate(unsigned int uiValue)
{
	if(ISNULL(m_pByteAlignCompress)) return false;

	//������� ��� ���������� ������ ���������� ���������������
	if(m_uiLastValue!=EMPTY_VALUE && uiValue<=m_uiLastValue){
		ERR_TO_CONSOLE(erNotFind, L"Value not correct");
		ToConsole(L"uiValue", uiValue);
		ToConsole(L"m_uiLastValue", m_uiLastValue);
		return false;
	}
	
	if(m_uiLastValue==EMPTY_VALUE){
		//��� ������ ������� ���������� ���������� �������� ������� � ������ ��� � �����
		PushBackEncoded(uiValue);
	}else{
		//��� ����������� ������� ���������� ������������� �������� ������� � ������ ��� � �����
		PushBackEncoded(uiValue-m_uiLastValue);
	}
	
	//��������� ������� ���������� �������
	m_uiLastValue=uiValue;
	
	return true;
}

void CBaCoordinateNode_4i::ResetNode(void)
{
	CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::Reset();
	m_uiLastValue=EMPTY_VALUE;
}

bool CBaCoordinateNode_4i::IsEmptyNode(void)
{
	return CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::GetBinaryBufferSize()==0?true:false;
}

unsigned int CBaCoordinateNode_4i::Write(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return 0;

	unsigned int uiWritedBytes=0;

	//����� ��������� ��������
	uiWritedBytes+=CCoordinateNode_4i::WriteCompressed(pNdxStorage, m_uiLastValue);
	//����� ��������� ���������
	uiWritedBytes+=CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::Write(pNdxStorage);

	return uiWritedBytes;
}

void CBaCoordinateNode_4i::Read(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return;

	//������ ��������� ��������
	m_uiLastValue=CCoordinateNode_4i::ReadCompressed(pNdxStorage);
	//������ ��������� ���������
	CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::Read(pNdxStorage);
}

unsigned int CBaCoordinateNode_4i::FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize)
{
	if(ISNULL(pBuffer)) return 0;
	if(ISNULL(uiBufferSize)) return 0;
	
	unsigned int uiReadedBytesNumber=0;

	//������ ��������� �������
	unsigned int uiWorkedBytesNumber;
	m_uiLastValue=m_pByteAlignCompress->Decode(pBuffer, uiBufferSize, 0, &uiWorkedBytesNumber);
	uiReadedBytesNumber+=uiWorkedBytesNumber;

	//������ ��������� ���������
	uiReadedBytesNumber+=CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::FromBinaryBuffer(pBuffer+uiWorkedBytesNumber, uiBufferSize-uiWorkedBytesNumber);

	////������ ��������� �����������
	//unsigned char ucTemp=0;
	//memcpy(&ucTemp, pBuffer, sizeof(unsigned char));
	//SetFreqIncreaseKoef(ucTemp);
	//pBuffer+=sizeof(unsigned char);
	
	return uiReadedBytesNumber;
}

void CBaCoordinateNode_4i::ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBytesBuffer)
{
	if(ISNULL(pBytesBuffer)) return;
	
	//����� �������� ��������� �������
	m_pByteAlignCompress->EncodeToBuffer(m_uiLastValue, pBytesBuffer);
	//����� ��������� ���������
	CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::ToBinaryBuffer(pBytesBuffer);

	////����� ��������� �����������
	//pBytesBuffer->push_back(GetFreqIncreaseKoef());
}

void CBaCoordinateNode_4i::ToString(wstring& szValue, wstring szOffset)
{
	szOffset.append(L" ");	
	szValue.append(L"\n");
	szValue.append(szOffset);
	ToString(szValue);
}

void CBaCoordinateNode_4i::View(void)
{
	ToConsole(L"//------CBaCoordinateNode_4i");

	wstring szValue;
	ToString(szValue);
	ToConsole(szValue.c_str());

	ToConsole(L"//------Eof-CBaCoordinateNode_4i");
}

void CBaCoordinateNode_4i::ToString(wstring& szValue)
{
	//����� ���������� ����� ������� �����������
	CPosBaCntSearch PosBaCntSearch;
	CByteAlignCompress::TBytesBuffer Buffer;

	ToBinaryBuffer(&Buffer);

	PosBaCntSearch.FromBinaryBuffer(&Buffer.front(), (unsigned int)Buffer.size());
	PosBaCntSearch.ToString(szValue);	
}

//--------------------------------------------------------------------//

bool CBaCoordinateNode_4i_Blocked::AddCoordinate(unsigned int uiValue)
{
	if(ISNULL(m_pByteAlignCompress)) return false;

	//������� ��� ���������� ������ ���������� ���������������
	if(m_uiLastValue!=EMPTY_VALUE && uiValue<=m_uiLastValue){
		TO_CONSOLE(L"Value not correct");
		ToConsole(L"uiValue", uiValue);
		ToConsole(L"m_uiLastValue", m_uiLastValue);
		return false;
	}
	
	if(m_InBlockValuesNumber==cuiPositionBlockSize){
		//���� ���� ��� ������, ���������� �������� �� ����
		m_InBlockValuesNumber=0;
		m_OffsetsBuffer.PushBackEncoded(CBlockBuffer<cucBaCoordinateNode_BlockBufferSize>::GetBinaryBufferSize());
		//��������� ��������� �������� ����� �������� ����������
		m_uiLastValue=0;
	}

	//��� ����������� ������� ���������� ������������� �������� ������� � ������ ��� � �����
	PushBackEncoded(uiValue-m_uiLastValue);
	
	//��������� ������� ���������� �������
	m_uiLastValue=uiValue;
	++m_InBlockValuesNumber;

	return true;
}

void CBaCoordinateNode_4i_Blocked::ResetNode(void)
{
	CBaCoordinateNode_4i::ResetNode();
	m_OffsetsBuffer.Reset();
	m_InBlockValuesNumber=UC_EMPTY;
}

unsigned int CBaCoordinateNode_4i_Blocked::Write(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return 0;

	unsigned int uiWritedBytes=0;

	//����� ������� ���������
	uiWritedBytes+=CBaCoordinateNode_4i::Write(pNdxStorage);
	//����� ����� ��������
	uiWritedBytes+=m_OffsetsBuffer.Write(pNdxStorage);
	//����� ���������� ������� � ��������� ������������ �����
	pNdxStorage->Append(&m_InBlockValuesNumber, sizeof(m_InBlockValuesNumber));
	uiWritedBytes+=sizeof(m_InBlockValuesNumber);

	return uiWritedBytes;
}

void CBaCoordinateNode_4i_Blocked::Read(INdxLevelStorage* pNdxStorage)
{
	if(ISNULL(pNdxStorage)) return;

	//������ ������� ���������
	CBaCoordinateNode_4i::Read(pNdxStorage);
	//������ ����� ��������
	m_OffsetsBuffer.Read(pNdxStorage);
	//������ ���������� ������� � ��������� ������������ �����
	pNdxStorage->Read(&m_InBlockValuesNumber, sizeof(m_InBlockValuesNumber));
}

unsigned int CBaCoordinateNode_4i_Blocked::FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize)
{
	if(ISNULL(pBuffer)) return 0;
	if(ISNULL(uiBufferSize)) return 0;
	
	unsigned int uiReadedBytesNumber=0;

	//������ ������� ���������
	uiReadedBytesNumber+=CBaCoordinateNode_4i::FromBinaryBuffer(pBuffer, uiBufferSize);
	//������ ����� ��������
	uiReadedBytesNumber+=m_OffsetsBuffer.FromBinaryBuffer(pBuffer+uiReadedBytesNumber, uiBufferSize-uiReadedBytesNumber);
	//������ ���������� ������� � ��������� ������������ �����
	memcpy(&m_InBlockValuesNumber, pBuffer+uiReadedBytesNumber, sizeof(m_InBlockValuesNumber));
	uiReadedBytesNumber+=sizeof(m_InBlockValuesNumber);

	return uiReadedBytesNumber;
}

void CBaCoordinateNode_4i_Blocked::ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBytesBuffer)
{
	if(ISNULL(pBytesBuffer)) return;
	
	//����� ������� ���������
	CBaCoordinateNode_4i::ToBinaryBuffer(pBytesBuffer);
	//����� ����� ��������
	m_OffsetsBuffer.ToBinaryBuffer(pBytesBuffer);
	//����� ���������� ������� � ��������� ������������ �����
	pBytesBuffer->push_back(m_InBlockValuesNumber);
}

void CBaCoordinateNode_4i_Blocked::View(void)
{
	ToConsole(L"//------CBaCoordinateNode_4i_Blocked");

	wstring szValue;
	ToString(szValue);
	ToConsole(szValue.c_str());

	ToConsole(L"//------Eof-CBaCoordinateNode_4i_Blocked");
}

void CBaCoordinateNode_4i_Blocked::ToString(wstring& szValue)
{
	//����� ���������� ����� ������� �����������
	CPosBaCntSearch_Blocked PosBaCntSearch;
	CByteAlignCompress::TBytesBuffer Buffer;

	ToBinaryBuffer(&Buffer);

	PosBaCntSearch.FromBinaryBuffer(&Buffer.front(), (unsigned int)Buffer.size());
	PosBaCntSearch.ToString(szValue);	
}

//--------------------------------------------------------------------//

}
}
}
}
}