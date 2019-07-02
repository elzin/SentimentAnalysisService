#pragma once
#include "IInterface.h"
#include <vector>
#include <string>

//--------------------------------------------------------------------//

// {91B8739C-D168-4ee4-BECA-136D36BD66B8}
static const GUID IID_BasesManager = 
{ 0x91b8739c, 0xd168, 0x4ee4, { 0xbe, 0xca, 0x13, 0x6d, 0x36, 0xbd, 0x66, 0xb8 } };

// {84DF324C-EB6E-41aa-A535-F305261948C0}
static const GUID CLSID_BasesManager = 
{ 0x84df324c, 0xeb6e, 0x41aa, { 0xa5, 0x35, 0xf3, 0x5, 0x26, 0x19, 0x48, 0xc0 } };

//--------------------------------------------------------------------//

namespace SS
{
namespace Interface
{
namespace Core
{
namespace ResourceManagers
{

//--------------------------------------------------------------------//

///��������� ���������� ���������� ������ ������
/**
	����� ��� IID_BaseManager
	�������������� ���������� ������������ � ��������:
	- L"./core/BasesManager.dll":
		CLSID_BasesManager
*/
class IBasesManager : public virtual IBase
{
public:
	///������������� ��� ��������� ���������
	virtual void SetActiveStorage(const wchar_t* wszStorage) = 0;
	///��������� ����� ��������� ���������
	virtual const wchar_t* GetActiveStorage() = 0;
	///��������� ���������
	virtual bool OpenStorage() = 0;
	///������� ���������
	virtual bool CloseStorage() = 0;
	///������� ���������
	virtual bool ClearStorage() = 0;
	///������ ���������
	virtual bool DeleteStorage() = 0;
	///������ ��������� �����
	virtual bool DeleteTemporaryFiles() = 0;
	///��������� ��������� �� ���������� ����
	virtual bool BackupStorage(const wchar_t* wszPath) = 0;
	/// �������� ������ ������ � ������ ���� (���������� ��� ������)
	virtual void GetDatabaseFilePathes(std::vector< std::pair<std::wstring, std::wstring> >* vPathes, std::wstring& sBaseName) = 0;
	///����� ���������
	virtual bool ShrinkStorage() = 0;
};

//--------------------------------------------------------------------//

}
}
}
}