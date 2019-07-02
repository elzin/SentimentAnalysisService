#pragma once

struct HKEY__;
#include "..\ASCInterface\services.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{

	
///������ ��������� ���������� �������
class CWorkRegister
{
public:
	CWorkRegister();
	~CWorkRegister();

	///���������� �������� ��������� �� ��� ����� (������ ������)
	std::wstring GetParameter(std::wstring wParametrName, const wchar_t* wszPath);

	///��������� ������� ����������
	void SetWorkDir(std::wstring wPathToDir);

protected:

	///HANDLE ��� ������������� �������
	CManagerLifeTimeForCriticalSection m_CriticalSection;

	///�������� ���� ��� ��������� ���������� �� �������
	const std::wstring csPath;

	bool m_blParametersHadBeenLoaded;

	///���� � ����� � ������ ������
	std::wstring	m_sPathDataBase;
	///���� � ����� � ��������
	std::wstring	m_sPathWordsystem;
	///���� � ����� � ���������� �������
	std::wstring	m_sPathTemporaryFiles;
	///������ ��� �������� ���������� � ����� ������
	std::wstring m_sPassword;
	///���� � ������� ����
	std::wstring m_sPathCore;
	///������� ����������
	std::wstring m_sWorkPath;
	///��� ������� (��� ������ ������)
	std::wstring m_sServer;
	///���� � ���������� ��������
	std::wstring m_sDocPluginsPath;
	///��� ���������
	std::wstring m_sDataSource;

	///�������� ��������� �� ������� �� ��� �����
	std::wstring	LoadParameter(std::wstring sNameParameter);
	///�������� ��������� �� INI ����� �� ��� �����
	std::wstring	LoadParameterFromINIFile(std::wstring sNameParameter, const wchar_t* wszPath);
	///���������� ���������
	void	SaveParameter(std::wstring sNameParameter,std::wstring sValue);
	///��������� ��������� �� �������
	std::wstring	QueryValue(HKEY hPredefinedKey, std::wstring sKeyName,std::wstring sValueName);
	///�������� ��������� � �������
	void	CreateNewKey(HKEY hPredefinedKey, std::wstring sNewKeyName);
	///������������ �������� ��������� � �������
	void	SetKeyValue(HKEY hPredefinedKey, std::wstring sKeyName, std::wstring sValueName, std::wstring sValueSetting, long lValueType);

	///����������� ��� ������������� �� �������������� ���� � ����������
	void UpdateForRelativePath(std::wstring* pString, const wchar_t* wszPath);


	/// ��������� � ����������� ��������� �� ss.ini ���� �� �����������
	void CheckAndLoadParameters(const wchar_t* wszPath);


};

}
}
}
