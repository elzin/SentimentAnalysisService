#pragma once

#include "types.h"
#include "baseconnectionsmanager.h"
#include "..\ASCInterface\idbms.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

/// ��������� ���������������� ������ � DBMS - ������
class CDBMSManager 
	: public CBaseConnectionsManager<SS::Interface::Core::DBMS::IDataBase>
	, public SS::Core::CommonServices::CBaseCoreClass
{
protected:

	///�������� � DBMS-���� (��������� ��� + ��� �������)
	SS::Core::ResourceManagers::Types::THMDBMSConnections m_hmdbmsConnections;

	///�������� DBMS-��� (����������)
	SS::Interface::Core::DBMS::IDBManager * m_pConstDBManager;

	///�������� DBMS-��� (NDX)
	SS::Interface::Core::DBMS::IDBManager * m_pNDXDBManager;

	/// ���� � �����
	std::wstring m_wsDataBasePath;
	/// ���� � ��������� �����
	std::wstring m_wsITDataBasePath;

protected:
	/// �������������� ���������� ������
	void Init(void);

	/// ��������� ���� ���������� ���� � ������� ��������� 
	/** 
		\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ���������� � DBMS - �����
		\return bool - ���� ���������� ���������, true
	*/
	bool Open(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection);

	/// ��������� ����������, �� ������� ��������� �������� 
	/** 
		\param it_Connection - ��������, ����������� �� ����������
	*/
	void Close(SS::Core::ResourceManagers::Types::THMDBMSConnections::iterator it_Connection);

	/// ������� ����, �� ������� ��������� �������� 
	/** 
		\param it_Connection - ��������, ����������� �� ����������
	*/
	void Clear(SS::Core::ResourceManagers::Types::THMDBMSConnections::iterator it_Connection);

	/// ��������� ����������, �� ������� ��������� �������� 
	/** 
		\param it_Connection - ��������, ����������� �� ����������
	*/
	bool Open(SS::Core::ResourceManagers::Types::THMDBMSConnections::iterator it_Connection);

	/// ���������������� DBMS - ���� 
	/** 
		\param sDataBaseInit - ���� � ���-�����, � ������� ������� ��������� ����
		\param sDataBaseRoot - ���� � �����, � ������� ��������� ����
		\param ppDBManager - �������� ���, � ������� �������� ���������� �������������
	*/
	void CreateAndInit(std::wstring sDataBaseInit, std::wstring sDataBaseRoot, SS::Interface::Core::DBMS::IDBManager** ppDBManager);

	void GetFileNamesFromDirectory(/*in*/std::pair<std::wstring, std::wstring>& DirectoryPaths, /*out*/std::vector< std::pair<std::wstring, std::wstring> >* vPathes);

public:
	/// �����������
	CDBMSManager();
	/// �������� ���� ����������, ����������� ���������� ���
	~CDBMSManager();

public:
	/// ������������� ��������� �� ���� ��������
	void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

public:
	/// ������� ������������ ��� ��� �� DBMS - ������
	/** 
		\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
	*/
	bool Clear(const wchar_t* BaseType);
	/// ������������� ���� � ��������� ����� ������
	void SetITDataBasePath(const wchar_t * wszITDataBasePath);

	/// ����������� ��� ���������� 
	void Close();

	/// ��������� ������������ ��� ��� �� DBMS - ������
	/** 
		\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
	*/
	void Close(const wchar_t* BaseType);

	/// ��������� ������������, �� �������� ����������
	/** 
		\return bool - ���� true, �� �������� ������ �������
	*/
	bool Open();

	/// ��������� ������������ ��� ���
	/** 
		\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
		\return bool - ���� true, �� ���� �������
	*/
	bool Open(const wchar_t* BaseType);

	/// ������ ��� ��������� ���������
	/** 
		\param StorageName ��� ��������� ��������� (����� ���� Ind70ZMDF045DF...)
		\return bool - true, ���� �������� ��������� ������� ������
	*/
	bool OpenStorage(const wchar_t* StorageName);

	/// �������� ��������, �������������� ����� ���� ������������� ���� � ������� ������� ���������� � ������������
	/** 
		\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ��������� �� ������ � ����� DBMS
		
	������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
	��������������� ����� ���� ������������� ���� DBMS-������ � ���������� ��������� �� ���� � ���������� ��������� 
	*/
	void CreateOpenAndRegister(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection);

	/// ������������� ������ �� ���� DBMS-������ \see SS::MANAGER::Constants
	/** 
		\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ��������� �� ������ � ����� DBMS
		
	���� ����� ������ ����� ����, ���� ����������� � ������������ ��������, ���������� � ��� 
	*/
	void UnRegisterDeleteAndClose(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection);

	/// �������� ������ ������ � ������ ���� (���������� ��� ������)
	void GetDatabaseFilePathes(std::vector< std::pair<std::wstring, std::wstring> >* vPathes, std::wstring& sBaseName);

};

}
}
}
