#pragma once

#include "..\ASCInterface\ICommonServices.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{

class CFileFinder : public SS::Interface::Core::CommonServices::IFileFinder
{
public:
	CFileFinder(void);
	~CFileFinder(void);
	/// ���� ����� � �����
	/** 
		\param sRootPath - �������� �����
		\param sSubPath - ��������� �����
		\param vIgnoreExt - ������������ ���������� (������ - ".ext")
		\param vRelPaths - ������������� ���� � ������ � ����� sRootPath
		\return bool - true, ���� ��� �������
	*/
	bool GetFiles(std::wstring& sRootPath, std::wstring& sSubPath, std::vector<std::wstring>* vIgnoreExt, std::vector<std::wstring>* vRelPaths);

	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������
	ULONG Release();

};

}
}
}