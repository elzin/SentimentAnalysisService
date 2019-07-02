#pragma once

#include ".\byte_align.h"
#include ".\basis_containers.h"
#include ".\list_containers.h"
#include ".\const.h"

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

///������� ��������� ������� 
class CPosCnt : public CCompositeValue, public CBinaryContainer, public CUnidirListItem<CPosCnt>
{
public:
	CPosCnt(void):m_ucFreqIncreaseKoef(0), m_uiLastPosition(EMPTY_VALUE){};

	///���������� ����������� ��������� �����������
	unsigned char GetFreqIncreaseKoef(void){return m_ucFreqIncreaseKoef;};
	///������������� ����������� ��������� �����������
	void SetFreqIncreaseKoef(unsigned char ucValue){m_ucFreqIncreaseKoef=ucValue;};

protected:
	///����������� ��������� �����������, ��� ������� ��������� 
	///���������� �������� ���������� ������� � ����������
	unsigned char m_ucFreqIncreaseKoef;
	///������� ���������� �������
	unsigned int m_uiLastPosition;
};

//--------------------------------------------------------------------//

///������ �������� ����������� ������� � �������� ����
class CPosBinaryContainer
{
public:
	///��������� ��������� ������ �������
	CBinaryBufferContainer* GetPosBinaryContainer(void){return &m_PosBinaryContainer;};

protected:
	///��������� ��������� ������ ������������ 
	///��� �������� ��������� ����������� ����������� �������
	CBinaryBufferContainer m_PosBinaryContainer;
};

//--------------------------------------------------------------------//

}
}
}
}
}