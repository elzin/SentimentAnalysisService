#pragma once

#include ".\arg_res.h"
#include ".\res_containers.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{

//--------------------------------------------------------------------//

///�������� ��������� ��� ������ � ����������, 
///�������� ��������� ������ � ���������������� ����������
class CResultArgument_HID : public CResultArgument
{
public:
	typedef vector<Containers::CFindResult::TBlockHIDCollection*> TBlocksCollection;

	CResultArgument_HID(unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, float fKoeff = 1.0);
	virtual ~CResultArgument_HID(void);
	
	///��������� ��������� ��������� ������ � ����������
	void AddResultBlocks(void);
	///��������� ������������ ��������� �� �������������� �����
	void AddIndexHID(unsigned int uiIndex, unsigned int uiHeaderID);
	///���������� ��������� ������ ����������
	TBlocksCollection* GetResultBlocksCollection(void){return &m_BlockHIDCollection;};

protected:

	///��������� ��������������� ���������� �� �� ������
	TBlocksCollection m_BlockHIDCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}