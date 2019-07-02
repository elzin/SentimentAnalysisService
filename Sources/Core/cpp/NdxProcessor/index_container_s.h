#pragma once

#include ".\index_container_nodes_s.h"
#include ".\cnt_factory.h"

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

///��������� ���������, �������� ���������� �������, ������������ ��� ������
///����� ��������� ���������� �������� ����� ����� ��� ��������� �������� ����, 
///��������� �������������� ��������� ��� �������� ���������
///���������� ��������� � ���� ������, � ����������� �� �������� ���������,
///����� ��������� �������� � �����, ��� ��������� �������� ������ ����� �����
class CCoordinateContainer_4s : public CValuesContainer, public CFactoryClient<CContainersFactory>
{
public:
	CCoordinateContainer_4s(CContainersFactory* pContainersFactory, unsigned int uiEntryPoint = EMPTY_VALUE);
	~CCoordinateContainer_4s(void);

	///���������� �������� ��������� ���������� �� ���������� �������������� ��������
	void SetFreshValues(CValue* pPrevValue, TValuePtrsBuffer* pValuePtrsBuffer);
	///����������� �������� �� ���������� ����������� ��������
	void FreeValues(CValue* pGenerativeValue);

protected:
	///�������� ���� ���������
	CCoordinateNode_4s* m_pRootNode;
};

//--------------------------------------------------------------------//

}
}
}
}
}