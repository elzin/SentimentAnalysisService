#pragma once

#include ".\const.h"
#include ".\console.h"
#include ".\consoleclient.h"

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

///���������� �� ������������ ���������
#pragma pack(push,1)  // Fix packing size 
struct STablePositions
{
	STablePositions(void):m_uiHeadPosition(EMPTY_VALUE), m_uiTailPosition(EMPTY_VALUE){};

	///���������� �����
	unsigned int GetTableLength(void){return m_uiTailPosition-m_uiHeadPosition;};

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wchar_t buf[100];
		wsprintf(buf, L"Head: %u, Tail: %u", m_uiHeadPosition, m_uiTailPosition);
		wszValue.assign(buf);
	};

	///�������� ������� (������)
	unsigned int m_uiHeadPosition;
	///��������� ������� (�����)
	unsigned int m_uiTailPosition;
};
#pragma pack(pop)
//--------------------------------------------------------------------//

///���������� �� ������������ ���������
#pragma pack(push,1)  // Fix packing size 
struct STableInfo
{
	STableInfo(void):m_uiCellsOffset(EMPTY_VALUE), m_uiColumnCount(EMPTY_VALUE){};
	
	///���������� ���������� ����� � �������
	unsigned int GetRowsCount(unsigned int uiNextCellsOffset)
	{
		//��� ������������ ��� ������� ����� �������� �� �������, � ���������, ������� �� ���������� ����� � ������+1
		return (uiNextCellsOffset-m_uiCellsOffset)/(m_uiColumnCount+1);
	}

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wchar_t buf[100];
		wsprintf(buf, L"CellsOffset: %u, ColumnCount: %u", m_uiCellsOffset, m_uiColumnCount);
		wszValue.assign(buf);
	};

	///���������� ���������� ������� ������
	void View(void)
	{
		wstring wszValue;
		ToString(wszValue);
		ToConsole(wszValue.c_str());
	};

	///�������� �� ������
	unsigned int m_uiCellsOffset;
	///���������� ������� � �������
	unsigned int m_uiColumnCount;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///�������� ��� ��������� �� ������ ��������������� �������, ������, ������
const unsigned int arrTrcOffsets[3]={0, 8, 24};
///����� ��� ��������� �� ������ ��������������� �������, ������, ������
const unsigned int arrTrcMasks[3]={0x000000ff, 0x00ffff00, 0xff000000};

///TRC �������������, �������� � ���� ������������
///��������������� �������, ������, ������, 
//�� ���� ����� ���������� ���������������� ������ � ���������, ������ �������
class CTrcID : public CConsoleClient
{
public:
	CTrcID(void):m_uiValues(EMPTY_VALUE){};
	CTrcID(unsigned int uiTableID):m_uiValues(uiTableID){};
	
	enum ETrcIDType
	{
		etrcCell,
		etrcRow,
		etrcTable,
	};

	///���������� �������� TRC ��������������
	unsigned int GetTrcID(void){return m_uiValues;};

	///���������� ������������� �� ����
	unsigned int GetIDByType(CTrcID::ETrcIDType Type){
		if((unsigned int)Type>(unsigned int)etrcTable){
			TO_CONSOLE(L"Too big TRC Type!!!");
			return EMPTY_VALUE;
		}	
		return (m_uiValues&arrTrcMasks[Type])>>arrTrcOffsets[Type];
	};
	
	///������������� ������������� �� ����, ���������� �������
	void SetIDByType(CTrcID::ETrcIDType Type, unsigned int uiID){
		if((unsigned int)Type>(unsigned int)etrcTable){
			TO_CONSOLE(L"Too big TRC Type!!!");
			return;
		}	

		m_uiValues&=(~arrTrcMasks[Type]);
		m_uiValues|=((uiID<<arrTrcOffsets[Type])&arrTrcMasks[Type]);

		if(Type==etrcCell) return;
		unsigned int i=(unsigned int)Type;
		do{
			--i;
			SetIDByType((CTrcID::ETrcIDType)i, 0);
		}while(i!=0);
	};

	///�������������� ������������� �� ����
	void IncIDByType(CTrcID::ETrcIDType Type){SetIDByType(Type, GetIDByType(Type)+1);};

	///��������� �������������
	void Reset(void){m_uiValues=EMPTY_VALUE;};
	///��������� �� �������
	bool IsEmpty(void){return m_uiValues==EMPTY_VALUE?true:false;};

	///������������ � ������
	void ToString(wstring& wszValue);

protected:
	///����� �������� �������������� �������, ������, ������
	unsigned int m_uiValues;
};

//--------------------------------------------------------------------//

}
}
}
}
}