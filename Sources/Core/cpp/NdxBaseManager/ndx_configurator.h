#pragma once

#include "..\ASDInterface\INdxDataStorage.h"
#include "..\ASDInterface\INdxBaseManager.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxBaseManager
{

//--------------------------------------------------------------------//

///������� ������� ��������� ����
class CNdxConfigurator
{
public:
	CNdxConfigurator(void);
	virtual ~CNdxConfigurator(void);
	
	///������������� ��������� ���������
	void Cofigure(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage, 
		SS::Interface::Core::NdxSE::ENdxStorageConfig NdxStorageConfig);

protected:
	///������� ��������� ������������ �������
	void ConfigLevels_0(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	///������� ��������� ������������ �������
	void ConfigLevels_1(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	///������� ��������� ������������ �������
	void ConfigLevels_2(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	///������� ��������� ������������ �������
	void ConfigLevels_3(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	///������� ��������� ������������ �������
	void ConfigLevels_4(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	///������� ��������� ������������ �������
	void ConfigLevels_5(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	///������� ��������� ������������ �������
	void ConfigLevels_6(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);

};

//--------------------------------------------------------------------//

}
}
}
}