#pragma once

#include "..\ASDInterface\INdxDataStorage.h"
#include ".\ndx_configurator.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxBaseManager
{

//--------------------------------------------------------------------//
class CNdxBaseManager;

///������� ������� ��������� ����
class CNdxBaseFactory
{
public:
	CNdxBaseFactory(void);
	virtual ~CNdxBaseFactory(void);

	///������� ��������� ����
	virtual void CreateBase(CNdxBaseManager* pNdxBaseManager);

protected:
	///������� ��������� ���������� � ����������������� �������
	void CreateTextInfo(CNdxBaseManager* pNdxBaseManager);
	///������� ��������� ����� � ������� � ���� ������ �����
	void CreateTextPathStorage(CNdxBaseManager* pNdxBaseManager);
	///������� ��������� ����� ������� � ���� ������� DBMS
	void CreateTextFieldsStorage(CNdxBaseManager* pNdxBaseManager);
	///������� ��������� ���������
	void CreateIndexStorage(CNdxBaseManager* pNdxBaseManager, const wchar_t* wszIndexStorageName, 
		SS::Interface::Core::NdxSE::ENdxStorageConfig StorageConfig, bool bStorageWithStatistic);
	///������� ��������� ��������� �������� �� ��������� ����������
	void CreateIndexStoragesBySettings(CNdxBaseManager* pNdxBaseManager);
	
	///��������� � ���������� �������� ��������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataStorageFactory* m_pNdxDataStorageFactory;
	///������������ ��������� ��������
	CNdxConfigurator m_NdxConfigurator;
};

//--------------------------------------------------------------------//

}
}
}
}