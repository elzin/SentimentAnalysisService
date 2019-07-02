#pragma once

#include ".\const.h"
#include ".\console.h"
#include "..\ASDInterface\INdxDataStorage.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

class CDataUnitFactory;

//--------------------------------------------------------------------//

///����������� ���� ��������� ���� ������ � ������� �� ������ � ���
class CDataUnit : public virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit
{
public:
	CDataUnit(CDataUnitFactory* pDataStorageFactory);
	virtual ~CDataUnit(void);
	
	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������
	ULONG Release(void);
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///������� ���� ������ 
	void Create(const wchar_t* pszDataUnitName, const wchar_t* pszDataUnitExt);
	///��������� ������ �� ���� ������ 
	bool IsOpen(void);
	///���������� ��� ����� ������ 
	const wchar_t*	GetDataUnitName(void);
	///���������� ���������� ����� ������ 
	const wchar_t* GetDataUnitExt(void);
	///������������� ��������� �������������
	void SetBackupSettings(
		SS::Interface::Core::NdxSE::NdxDataStorage::SBackupSettings::ECompressMode CompressMode, 
		SS::Interface::Core::NdxSE::NdxDataStorage::SBackupSettings::EWriteMode WriteMode);
	//-----------Eof-INdxDataUnit
	
	///���������� ������� ��������
	CDataUnitFactory* GetDataStorageFactory(void){return m_pDataStorageFactory;};

protected:
	///��� ����� ������ 
	wstring	m_wszDataUnitName;
	///���������� ����� ������ 
	wstring	m_wszDataUnitExt;
	///���� �������� ����� ������
	bool m_bIsOpen;
	///������� �������� ��������
	CDataUnitFactory* m_pDataStorageFactory;
	///��������� �������������
	SS::Interface::Core::NdxSE::NdxDataStorage::SBackupSettings m_BackupSettings;
};

//--------------------------------------------------------------------//

}
}
}
}