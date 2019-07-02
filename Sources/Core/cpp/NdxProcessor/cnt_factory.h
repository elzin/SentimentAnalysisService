#pragma once

#include ".\factory_client.h"
#include ".\index_storage.h"
#include ".\byte_align.h"
#include "..\ASDInterface\TNdxSearchEngineTypes.h"

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

class CBinaryContainer;
class CPosCnt;
class CValuesContainer;
class CCompositeValue;
class CIndexAttributes;
class CCoordinateNode_4i;
class CCoordinateNode_4s;

//--------------------------------------------------------------------//

///������� ��������� ���������� ��� �������� ��������� ��������
///��������� � ��������������� ���������� ���������, ��� �������� ��������� ����������
class CContainersFactory
{
public:
	CContainersFactory(SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* pIndexStorage);
	virtual ~CContainersFactory(void);
	
	///���������� ��������� ���������
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* GetIndexStorage(void){return m_pIndexStorage;};

	///������� ��������� ��������
	CValuesContainer* CreateValuesContainer(unsigned int uiEntryPoint);
	///������� ��������� ��������
	CCompositeValue* CreateCompositeValue(unsigned int uiValue, unsigned char ucLevel);
	///������� ������������ ����
	CCoordinateNode_4i* CreateCoordinateNode_4i(unsigned char ucLevel);
	///������� ������������ ����
	CCoordinateNode_4s* CreateCoordinateNode_4s(unsigned char ucLevel);

	///���������� ������� ��������� ������
	SS::Interface::Core::NdxSE::CNdxSearchSettings* GetSearchSettings(void){return m_pSearchSettings;};
	///������������� ������� ��������� ������
	void SetSearchSettings(SS::Interface::Core::NdxSE::CNdxSearchSettings* pValue){m_pSearchSettings=pValue;};

protected:
	///������ ������� �����
	void InitPoolsManager(void);

	///��������� ���������
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* m_pIndexStorage;
	///���� ������ ������� ����
	bool m_bCompressWordPositions;
	///��������� ������� � �����
	CByteAlignCompress m_ByteAlignCompress;
	///������� ��������� ������
	SS::Interface::Core::NdxSE::CNdxSearchSettings* m_pSearchSettings;
};

//--------------------------------------------------------------------//

}
}
}
}
}