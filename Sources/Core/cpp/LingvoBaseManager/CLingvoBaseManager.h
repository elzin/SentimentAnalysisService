#pragma once


#include "..\ASSInterface\ILingvoBaseManager.h"
#include "..\ASCInterface\IBaseManager.h"

#include ".\BaseManager.h"



namespace SS
{
namespace Core
{
namespace ResourceManagers
{

class CLingvoBaseManager 
	: public CBaseManager /*public SS::Interface::Core::ResourceManagers::IBaseManager*/
	, public SS::Interface::Core::ResourceManagers::ILingvoBaseManager
{

public:
	CLingvoBaseManager();
public:
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** ppBase); 

	///������������
	ULONG Release();

public:
	/// ������������� ��������� �� ���� ��������
	void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

	/// ��������� ���� ������������� ���� �� ������������ ������ 
	/** 
		\param BaseType - ��� ����, (���������������,  � �.�.) \see SS::MANAGER::Constants
		\param BaseGroup - ������, � ������� ��������� ���� (���������� �� DBMS � SQL-����) \see SS::MANAGER::Constants
	*/
	void Close(const wchar_t* BaseType, const wchar_t* BaseGroup);

	/// ��������� ���� ������������� ���� �� ������������ ������  
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param BaseGroup - ������, � ������� ��������� ���� (���������� �� DBMS � SQL-����) \see SS::MANAGER::Constants
		\return bool - ���� true, �� ���� �������
	*/
	bool Open(const wchar_t* BaseType, const wchar_t* BaseGroup);

	/// ��������� ������������ ��� ��� �� ���� �����
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
	*/
	void Close(const wchar_t* BaseType);

	/// ��������� ������������ ��� ���
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\return bool - ���� true, �� ���� �������
	*/
	bool Open(const wchar_t* BaseType);

	/// ��������� ������������ �������� ���������� � �������������
	void Close();

	/// ��������� ������������, �� �������� ���������� � �������������
	/** 
		\return bool - ���� true, �� �������� ������ �������
	*/
	bool Open();

	/// ���������� ��� ��������� ���������
	/** 
		\return const wchar_t* ������ �� ��� ��������� ���������
	*/
	const wchar_t* GetNameActiveStorage();

	/// ������ ��� ��������� ���������
	/** 
		\param StorageName ��� ��������� ��������� (����� ���� Ind70ZMDF045DF...)
		\return bool - true, ���� �������� ��������� ������� ������
	*/
	bool OpenStorage(const wchar_t* StorageName);

	/// ���������� SubConnection 
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param pSubConnection - �������������, \see ISubConnection
		
	��������� � ���������� ������������� � ����� ������������������ 
	(��� �������������) �������� ������� ������
	*/
	void Register(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::ISubConnection* pSubConnection);

	/// �������� SubConnection
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param pSubConnection - �������������, \see ISubConnection
		
	������� ����� ������������������ ������������� 
	*/
	void UnRegister(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::ISubConnection* pSubConnection);

	/// ������������� ������ �� ���� DBMS-������ \see SS::MANAGER::Constants
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ��������� �� ������ � ����� DBMS
		
	���� ����� ������ ����� ����, ���� ����������� � ������������ ��������, ���������� � ��� 
	*/
	void UnRegisterDeleteAndClose(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection);

	/// �������� ��������, �������������� ����� ���������� ������������� ���� � ������� ������� ���������� � ������������
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ��������� ��� ������ � ����������� � SQL-�����
		
	������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
	��������������� ����� ���������� ������������� ���� SQL-������ � ���������� ��������� �� ���� � ���������� ��������� 
	*/
	void CreateOpenAndRegister(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection);

	/// �������� ��������, �������������� ����� ���� ������������� ���� � ������� ������� ���������� � ������������
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ��������� �� ������ � ����� DBMS
		
	������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
	��������������� ����� ���� ������������� ���� DBMS-������ � ���������� ��������� �� ���� � ���������� ��������� 
	*/
	void CreateOpenAndRegister(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection);

	/// ������������� ������ �� ���������� SQL-������ \see SS::MANAGER::Constants
	/** 
		\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		\param ptssConnection - ��������� �� ������ � ����� SQL
		
	���� ����� ������ ����� ����, ���������� ����������� � ������������ ��������, ���������� � ��� 
	*/
	void UnRegisterDeleteAndClose(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection);

};

}
}
}

