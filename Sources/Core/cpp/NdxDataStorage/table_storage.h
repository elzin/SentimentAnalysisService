#pragma once

#include ".\data_unit.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

//�������� ������� � ������������
#pragma warning( disable : 4250 )

//--------------------------------------------------------------------//

///������ � ��������� ���� DBMS
class CTableStorage : public CDataUnit, 
	public SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage
{
friend class CDataUnitFactory;
friend class CDataStorageFactory;

protected:
   CTableStorage(CDataUnitFactory* pDataStorageFactory, SS::Interface::Core::DBMS::IDataBase* pDBMSBase);
   virtual ~CTableStorage(void);

public:
   	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///��������� ���� ������ � ������� ������
	bool Open(const wchar_t* pszPath);
	///��������� ���� ������ 
	bool Close(void);
	///�������  ���� ������ 
	void Clear(void);
	///���������� ���� ������ 
	bool Flush(void);
	///���������� ������ ����� ������ 
	unsigned int GetDataUnitSize(void);
	//-----------Eof-INdxDataUnit

	//-----------INdxTableStorage
	///��������� ���� � �������
	HRESULT AddField(SS::Interface::Core::DBMS::TDataTableFieldDescription* pDataTableFieldDescription);
	///���������� ��������� ����� �������
	TTableFieldCollection* GetFieldsCollection(void){return &m_TTableFieldCollection;};

	///�������������� ������� ������ � ����
	HRESULT InitFind(wchar_t* pKeyName, void* pKeyValue, void* ArrayOfPointersToData[], unsigned short* pusFindId = 0);
	///���� � ������� ��������� ��� �� ������������ ��������� ���� ����� �� ���������� ��������
	HRESULT Find(unsigned int uiFindId = 0);
	///���� � ������� ���� ��� �� ����������� �������
	HRESULT FindOne(unsigned int uiFindId = 0);

	///�������������� ������� ������������� ������ � ����
	HRESULT SpanFindInit(wchar_t* pKeyName, void* pLowerKeyValue, void* pUpperKeyValue, 
		std::set<unsigned int>* pSetOfRecordsIndexes, unsigned short* pusFindId = 0);
	///���� � ������� ������ ��������������� SpanFindInit
	HRESULT SpanFind(unsigned int uiFindId = 0) ;

	///���������� ������ ������ ������� �������� ����� ������� ������� ������
	unsigned int GetFoundRecordIndex(unsigned int uiFindId = 0);
	///������� ������ ������� �� �������
	void DeleteRecord(unsigned int uiRecordIndex);

	///�������������� ������� ������������ �������
	HRESULT InitScan(long nStartRecordIdx, void* ArrayOfPointersToData[]);
	///���������� ��������� ������ �������
	HRESULT Scan(void);
	///���������� ������ ������� �� �������
	HRESULT ScanOne(unsigned int uiRecordIndex);

	///�������������� �������� ���������� ������ � �������.
	HRESULT InitAdd(void* ArrayOfPointersToData[]);
	///��������� ������ � �������
	HRESULT Add(void);

	///�������������� �������� ��������� ���� ����� �������.
	HRESULT InitModify(void* ArrayOfPointersToData[]);
	///������� � �������� ������ � �������
	HRESULT FindOneAndChange(void);
	//-----------Eof-INdxTableStorage
  
protected:

	///��������� �� ������� DBMS
	SS::Interface::Core::DBMS::IDataTable* m_pDBMSTable;
	///��������� �� ���� DBMS, � �� ������� ��������� ����������� � ����������� �������
	SS::Interface::Core::DBMS::IDataBase* m_pDBMSBase;
	///��������� ����� �������
	TTableFieldCollection m_TTableFieldCollection;
	///��������� �������� ����� �������
	vector<wchar_t*> m_TableFieldNamesCollection;

	///��������� ������������� ������ ������� �������� DBMS::Scan .
	unsigned long m_LastAccessIndex;
};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}

