#pragma once

#include "..\ASDInterface\INdxDataStorage.h"
#include "./basisfile.h"
#include "./cashed_files.h"
#include "./vector_storage.h"
#include "./index_storage.h"
#include "./index_stat_storage.h"
#include "./table_storage.h"


namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

//--------------------------------------------------------------------//

class CDataUnitFactory
{
friend class CDataUnit;

public:
	CDataUnitFactory(void);
	virtual ~CDataUnitFactory(void);

	///������� ������� ��������� ����
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* CreateBasisFile(void);
	///������� ��������� ���� �������������� ����������� ������-������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* CreateCashedFile(void); 
	///������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* CreateTableStorage(void);
	///������� ��������� ������ ������
	CFilesCollectionEx* CreateFilesCollectionEx(void);
	///������� ��������� ����������� ������
	CUpdateFile* CreateUpdateFile(void);
	///������� ���� � ������������ ����������� ������
	CACashedFile* CreateAppendingCashedFile(void);
	///������� ���������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* CreateLevelStorage(void);
	///������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* CreateVectorStorage(void);

protected:
	///������������� ���� ����� � �������
	virtual void Register(SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* pNdxDataUnit){};
	///���������������� ���� ����� � �������
	virtual void UnRegister(SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* pNdxDataUnit){};

	///�������� ��� DBMS
	SS::Interface::Core::DBMS::IDBManager* m_pDBMSManager;
	///������� ����������� ����,� ��� ����� ����������� �������
	SS::Interface::Core::DBMS::IDataBase* m_pDBMSBase;
	
	///���� ����������� ����������� ��������
	bool m_bRegister;
};

//--------------------------------------------------------------------//

class CDataStorageFactory : public CDataUnitFactory,
	public SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataStorageFactory
{
friend class CDataUnit;

protected:
	typedef set<SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit*> TDataUnitCollection;

public:
	CDataStorageFactory(void);
	virtual ~CDataStorageFactory(void);

	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������� ��������� �� ���� ��������
	void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
	///������������
	ULONG Release(void);
	//-----------Eof-IBase

	//-----------INdxDataStorageFactory
	///������� ������� ��������� ����
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* CreateNdxFile(void);
	///������� ��������� ���� �������������� ����������� ������-������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* CreateNdxCashedFile(void); 
	///������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* CreateNdxTableStorage(void);
	///������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* CreateNdxVectorStorage(void);
	///������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* CreateNdxStorage(void);
	///������� ��������� ��������� ������ � ���������� ����������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorageWithStatistic* CreateNdxStorageWithStatistic(void);
	//-----------Eof-INdxDataStorageFactory

protected:
	///������������� ���� ����� � �������
	void Register(SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* pNdxDataUnit);
	///���������������� ���� ����� � �������
	void UnRegister(SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* pNdxDataUnit);
	///���������������� ��� ����� � �������
	void UnRegisterAll(void);

	///��������� ������ ����������� ��������
	TDataUnitCollection m_DataUnitCollection;
};

//--------------------------------------------------------------------//

}
}
}
}