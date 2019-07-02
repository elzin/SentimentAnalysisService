#pragma once

#include "..\ASDInterface\INdxBaseManager.h"
#include "..\ASDInterface\INdxDataStorage.h"
#include ".\base_factory.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxBaseManager
{

//--------------------------------------------------------------------//

///�������� ����������� ������� ��������� ����
class CNdxBaseManager : public  SS::Interface::Core::NdxSE::INdxBaseManager
{
public:
	typedef map<wstring, SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit*> TNdxDataUnitCollection;
	typedef vector< pair<wstring, SS::Interface::Core::NdxSE::ENdxStorageConfig> > TNdxBaseStructCollection;

	CNdxBaseManager(void);
	virtual ~CNdxBaseManager(void);

	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������
	ULONG Release(void);
	//-----------Eof-IBase

	//------------------IBaseManager
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
	void GetDatabaseFilePathes(std::vector< std::pair<std::wstring, std::wstring> >* vPathes, std::wstring& sBaseName);

	//------------------Eof-IBaseManager

	//------------------INdxBaseManager
	///���������� ��������� ��������� ����
	void ResetNdxBaseStructure(void){m_BaseStructCollection.clear();};
	///���������� ���� ��������� ���� �� �������� ����
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* 
		GetNdxBaseUnit(const wchar_t* wszStorageName);
	///��������� ���� ��������� ���� � ���������
	void AddNdxBaseUnit(const wchar_t* wszStorageName, 
		SS::Interface::Core::NdxSE::ENdxStorageConfig StorageConfig);
	///���������� ������������� ������� ������ ��������� ����,
	///���� � ������� �� ��������� ������������� ������, ���������� ��������
	///���� ���������, ��� ��� ��� ��������� ��� ���� ������� ������
	unsigned int GetCurrentSessionID(void){return m_uiCurrentSessionID;};
	///���������� ������ � ��������� ��������� ��������� ����
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* GetFirstNdxBaseUnit(void);
	///���������� ��������� �� ������� � ��������� ��������� ��������� ����, 
	//��� ���������� ����� ��� ��� ������ GetFirstNdxBaseUnit ������ NULL
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* GetNextNdxBaseUnit(void);
	//------------------Eof-INdxBaseManager


	///������� ���� ��������� ���� �� ��������� � �� ����� �� �����
	void DeleteNdxBaseUnit(const wchar_t* wszStorageName);
	///���������� ��������� ��������� ����
	TNdxBaseStructCollection* GetBaseStructure(void){return &m_BaseStructCollection;};
	///��������� ���� ��������� ���� � ���������
	void AddNdxBaseUnit(const wchar_t* wszStorageName, SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* pNdxDataUnit);
	///������� ��� ���� ����� �� ���������
	void TotalRemoveAll(void);
	
protected:
	///������������� ��������� ����
	HRESULT ReOpenBase(void);

	///��������� �� ��������� �����
	bool IsFolder(WIN32_FIND_DATA* pFD);
	///������� �����
	bool ClearFolder(const wchar_t* wszPathFrom);
	
	///������� ����
	wstring m_wsCurrentBase;
	///���� � ��������� ����� �� ����
	wstring m_wsBasePath;
	///���� �������� ����
	bool m_bIsBaseOpen;
	///������������� ������� ������ ��������� ����,
	unsigned int m_uiCurrentSessionID;

	///��������� ��������� ��������� ����, ���������� ����� ����� ������ ���� � ��������� ����, � ����� ������������
	TNdxBaseStructCollection m_BaseStructCollection;
	///��������� ������ ��������� ����
	TNdxDataUnitCollection m_DataUnitCollection;
	///�������� ��� ����������� ������ ������ ��������� ���� ����� 
	TNdxDataUnitCollection::iterator m_itCurrentDataUnit;
	///��������� ��� ������������� ����������
	TNdxDataUnitCollection m_NullCollection;
	///������� ��������� ����
	CNdxBaseFactory m_NdxBaseFactory;
};

//--------------------------------------------------------------------//

}
}
}
}