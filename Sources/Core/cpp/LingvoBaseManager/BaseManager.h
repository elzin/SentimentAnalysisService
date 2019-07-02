#pragma once

#include "..\ASCInterface\IBaseManager.h"

#include ".\DBMSManager.h"
#include ".\SQLManager.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

class CBaseManager 
	: public SS::Interface::Core::ResourceManagers::IBaseManager
{
	std::wstring m_wszBaseName;
	std::wstring m_wszPath;
protected:
	CDBMSManager m_oDBMSManager;
	CSQLManager m_oSQLManager;
public:
	CBaseManager(void);
	~CBaseManager(void);
public:
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** ppBase); 
	///������������
	ULONG Release();

public:
	///������������� ���� � ��������� �����
	void SetBasePath(const wchar_t* wszPath);
	///��������� ��������� ����
	HRESULT OpenBase(const wchar_t* wszBaseName);
	///������� ��������� ����
	HRESULT ClearBase(void);
	///�a������� ��������� ����
	void CloseBase(void);
	///������������ ��������� ����������� ��������� ����
	HRESULT BackUpBase(const wchar_t* wszPath);
	/// �������� ������ ������ � ������ ���� (���������� ��� ������)
	void GetDatabaseFilePathes(std::vector< std::pair<std::wstring, std::wstring> >* pvPathes, std::wstring& sBaseName);
};

}
}
}