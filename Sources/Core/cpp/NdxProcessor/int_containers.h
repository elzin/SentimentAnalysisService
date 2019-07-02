#pragma once

#include ".\const.h"
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

///��������� ���������
class CInterval : public CConsoleClient
{
public:
	CInterval(void):m_uiHeadPos(EMPTY_VALUE), m_uiTailPos(EMPTY_VALUE), m_uiWeight(0){};
	CInterval(unsigned int uiHeadPos, unsigned int uiTailPos, unsigned int uiWeight = 0)
		:m_uiHeadPos(uiHeadPos), m_uiTailPos(uiTailPos), m_uiWeight(uiWeight){};

	///���������� ������ ���������
	unsigned int GetLength(void){return (m_uiTailPos-m_uiHeadPos+1);};
	///���������� ��������� ���������
	void Reset(void){m_uiTailPos=EMPTY_VALUE;m_uiHeadPos=EMPTY_VALUE;m_uiWeight=0;};
	///�������� �� �������
	bool IsEmpty(void){return (m_uiTailPos==EMPTY_VALUE && m_uiHeadPos==EMPTY_VALUE)?true:false;};
	///��������� ��������, �������� ��� �����
	void Expand(unsigned int uiExpandedValue)
	{
		//��������� �������� �� ������ � ������ �� ������ ����������
		int iTemp=((int)m_uiHeadPos-uiExpandedValue);
		m_uiHeadPos=iTemp<0?0:iTemp;
		m_uiTailPos+=uiExpandedValue;
	};

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wchar_t buf[50]=L"";
		wsprintf(buf, L"L:%u-R:%u D:%u W:%u\n", m_uiHeadPos, m_uiTailPos, GetLength(), (unsigned int)m_uiWeight);
		wszValue.append(buf);
	};
	///���������� ���������� ������� ������
	void View(void)
	{
		wstring wszValue;
		wszValue.append(L"//-------CInterval\n");
		ToString(wszValue);
		wszValue.append(L"//-----Eof-CInterval\n");
		ToConsole(wszValue.c_str());
	};
	
	///������� ����� ������� ������
	virtual CInterval* Clone(void)
	{
		return new CInterval(m_uiHeadPos, m_uiTailPos, m_uiWeight);
	}

	///��������� ������� ���������
	unsigned int m_uiHeadPos;
	///�������� ������� ���������
	unsigned int m_uiTailPos;
	///��� ���������
	unsigned int m_uiWeight;
};


///��������� ����������
typedef vector<CInterval*> TIntervalCollection; 

//--------------------------------------------------------------------//

class CWordInSequence;

///������� ���������
struct SIntervalPos
{
	SIntervalPos(void):m_uiIndexPosition(EMPTY_VALUE), m_pCommonPositions(NULL){};

	///������� ������� � ���������
	unsigned int m_uiIndexPosition;
	///�������� ���� ������� �������
	CWordInSequence* m_pCommonPositions;

	///�������� ��������� ��� ����������
	bool operator <(const SIntervalPos& IntervalPos) const
	{
		return (m_uiIndexPosition<IntervalPos.m_uiIndexPosition)?true:false;
	};
};

///��������� ������� ����������
//typedef list<SIntervalPos> TIntervalPositions; 
typedef map<unsigned int, SIntervalPos> TIntervalPositions; 

//--------------------------------------------------------------------//

}
}
}
}
}
