#pragma once

#include "..\ASDInterface\INdxBaseManager.h"
#include ".\index_storage.h"
#include ".\index_storage_hdr.h"
#include ".\index_storage_tbl.h"
#include ".\index_stat_storage.h"
#include ".\texts_info_storage.h"
#include ".\texts_binary_storage.h"
#include ".\texts_path_storage.h"
#include ".\texts_field_storage.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Storages
{

//--------------------------------------------------------------------//

///���������� ����������� ����������� ������� ��������� ����
class CStorageManager
{
public:
	typedef map<wstring, CBasisStorage*> TStorages;

	CStorageManager(void);
	virtual ~CStorageManager(void);
	
	///�������������� �������� ��������
	void Init(SS::Interface::Core::NdxSE::INdxBaseManager* pNdxBaseManager);
	///����������� ��������� � ����� ����������
	void SetIndexingMode(void);
	///��������� �� ����� ����������
	bool IsIndexingMode(void);
	///����������� ��������� � ����� ����������-������
	void SetExtractingMode(void);
	///��������� �� ����� ����������
	bool IsExtractingMode(void);
	
	///������������ ���������� ��������� ����������
	void PrepareIndexing(void);
	///��������� �������� ��������� �� ��������� ����������
	void CompleteIndexing(void);
	///��������� �������� ��������� �� ��������� ���������� ���������
	void CompleteDocumentIndexing(void);

	///���������� ��������� ��������� �������� �������
	CIndexStorage* GetIndexStorage(const wchar_t* wszIndexStorageName){return static_cast<CIndexStorage*>(GetStorage(wszIndexStorageName));};
	///���������� ��������� ���������� � ����������������� �������
	CTextsInfoStorage* GetTextsInfoStorage(void){return static_cast<CTextsInfoStorage*>(GetStorage(SS::Interface::Core::NdxSE::ObligatoryStorageNames::TextsInfoStorage));};
	///���������� ��������� ����� � ������� � ���� ������ �����
	CTextsPathsTreeStorage* GetTextsPathsTreeStorage(void){return static_cast<CTextsPathsTreeStorage*>(GetStorage(SS::Interface::Core::NdxSE::ObligatoryStorageNames::TextsPathTreeStorage));};
	///���������� ��������� ����� ������� � ���� ������� DBMS
	CTextsFieldsStorage* GetTextsFieldsStorage(void){return static_cast<CTextsFieldsStorage*>(GetStorage(SS::Interface::Core::NdxSE::ObligatoryStorageNames::TextsFieldsStorage));};

	///��������� ��������� �� ��������� ����
	bool Update(void);

protected:
	///��������� ��������� ���������
	void AddStorage(const wchar_t* wszStorageName, CBasisStorage* pStorage);
	///���������� ��������� ���������
	CBasisStorage* GetStorage(const wchar_t* wszStorageName);
	///������� ��������� ���������
	void DeleteStorages(void);

	///��������� �������� ���������
	TStorages m_Storages;

	///��������� �� �������� ��������� ����
	SS::Interface::Core::NdxSE::INdxBaseManager* m_pNdxBaseManager;
	///������������� ������� ������ ��������� ����
	unsigned int m_uiCurrentNdxBaseSessionID;

};

//--------------------------------------------------------------------//

}
}
}
}
}