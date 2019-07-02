// ControlDynamicLibrary.h: interface for the CControlDynamicLibrary class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\ASCInterface\IInterface.h"
#include "..\ASCInterface\types.h"
#include "PathMap.h"

///��� ��� �������� � ��������� ����������� �������, ������ �������� ��� ������ wstring
typedef std::map<std::wstring, HMODULE> MNameLibrary_HModule;


///����� ��� �������� ������� � �������� �������
class  CControlDynamicLibrary  
{
private:
	///���������� ������ ������� � ����������������� id
	void Init();
	///������ ��� ����������� �������
	MNameLibrary_HModule m_mNameLibrary_HModule;
	///��������� ���������� � �������� ������ sNameLibrary
	HMODULE GetLibrary(std::wstring sNameLibrary, const wchar_t* wszPath);
	///�������� ���������� � �������� ������ sNameLibrary
	BOOL FreeLibrary(std::wstring sNameLibrary);
	///�������� � ������ hModule ��������� �� ILog
	void SetLog(HMODULE hModule, const wchar_t* wszPath);
	BOOL FileExists(const wchar_t* wszLibraryPath);

private:
	CPathMap m_oPathMap;

public:
	CControlDynamicLibrary();
	virtual ~CControlDynamicLibrary();

	///������� ��������� ���������� ������ � ���������� ��������� �� ��� ������� ���������
	void CreateInstance(const GUID* pGuid, void** ppBase, TCoreLibrary CoreLibrary, const wchar_t* wszPath);
	///������� ��������� ���������� ������(�� ����� dll) � ���������� ��������� �� ��� ������� ��������� 
	void CreateInstance(const GUID* pGuid, void** ppBase, const wchar_t* wszDllName, const wchar_t* wszPath);

	TCoreLibrary AddLibraryByPath(const wchar_t* wszPath);
};
