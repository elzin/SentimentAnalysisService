#pragma once

#include "../ASDInterface/TNdxSearchEngineTypes.h"
#include "../ASDInterface/INdxDataStorage.h"
#include ".\basis_storage.h"
#include ".\consoleclient.h"

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

///���� ������� ������
class CTableStorageDataField : public SS::Interface::Core::NdxSE::CNdxMetaField
{
public:
	CTableStorageDataField(wchar_t* pwszFieldName, 
		SS::Interface::Core::DBMS::EFieldDataTypes FieldType,
		SS::Interface::Core::DBMS::EFieldModificatorTypes FieldModificator);
	CTableStorageDataField(const CTableStorageDataField& DataField);
	
	///������������� ������������� ��������� ������ �� ������� ����
	void SetFindProgramId(unsigned short usFindProgramId){m_usFindProgramId=usFindProgramId;};
	///���������� ������������� ��������� ������ �� ������� ����
	unsigned short GetFindProgramId(void){return m_usFindProgramId;};
	///������������� ������������� ��������� ������������� ������ �� ������� ����
	void SetSpanFindProgramId(unsigned short usSpanFindProgramId){m_usSpanFindProgramId=usSpanFindProgramId;};
	///���������� ������������� ��������� ������������� ������ �� ������� ����
	unsigned short GetSpanFindProgramId(void){return m_usSpanFindProgramId;};

	///���������� ���������� ������� ������
	void View(void) const;

	///�������� ��� ��������� � ����������
	bool operator<(const CTableStorageDataField& RightDF) const {return m_SingleValue<RightDF.m_SingleValue;};

protected:
	///������������� ��������� ������ �� ������� ����
	unsigned short m_usFindProgramId;
	///������������� ��������� ������������� ������ �� ������� ����
	unsigned short m_usSpanFindProgramId;
};

//--------------------------------------------------------------------//

///��������� ���������
///������������ �� ������������ �������� ���� ������� �����:
///1. ��������� ���� ������ �� ��������� ����
///2. ��������� �������� ���� �� ������� �� ������ ������ �����
class CTableStorage : public CBasisStorage
{
public:
	///������� ����� �������
	typedef set<CTableStorageDataField> TDataFieldExtracts;
	///��������� ���������� �� �������� ����� �������
	typedef vector<void*> TValuesCollection;
	///��������� ���������� �� �������� ����� �������
	typedef set<unsigned int> TRecordIdCollection;
	///��������� ���������� �� �������� ����� �������
	typedef vector<CTableStorageDataField> TDataFieldCollection;

	CTableStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* pNdxTableStorage);
	virtual ~CTableStorage(void); 
	
	///��������� ������ � �������
	void Append(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pDataRow);
	///��������� �������� ���� ������� �� �������
	void ExtractKeys(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pFilterDataRow, TDataFieldExtracts* pResultExtracts);
	///��������� ���� ������� �� �����
	void ExtractByKey(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pResultDataRow);
	///���������� ���������
	void ViewDataFieldExtracts(TDataFieldExtracts* pDataFieldExtracts);
	///���������� ������ �������
	void Scan(void);
	///����������� ������ ���� � �������
	unsigned int GetDataFieldIndex(const wchar_t* wszFieldName);
	///������� ������ ������� �� �����
	void DeleteByKey(SS::Interface::Core::NdxSE::CNdxMetaField* pKeyField);

protected:
	///��������� ��������� ����� �������
	void FillTextFieldCollection(void);
	///������� ��������� ����� �������
	void ClearTextFieldCollection(void){m_TextFieldCollection.clear();};
	///��������� �������� ���� �������
	void ExtractRecords(vector<unsigned short>* pFindProgramIDCollection, TRecordIdCollection* pRecordIdCollection);
	///��������� �������� ���� �������
	void SpanExtractRecords(vector<unsigned short>* pFindProgramIDCollection, TRecordIdCollection* pRecordIdCollection);

	///��������� ���������� �� �������� ����� ������� ��� ����������
	TValuesCollection m_AppendValuesCollection;
	///��������� ���������� �� �������� ����� ������� ��� ������ ������
	TValuesCollection m_FindKeysValuesCollection;
	///��������� ���������� �� �������� ����� ������� ��� ������ �� �����
	TValuesCollection m_FindByKeysValuesCollection;
	///��������� �������������� ������� ������� ��� ������ �� ��������� �������� ����
	TRecordIdCollection m_SpanFindCollection;
	///��������� ����� �������
	TDataFieldCollection m_TextFieldCollection;
	///����� ���� ������, �� ������� ����� ��� ������
	unsigned int m_uiKeyFieldIndex;

	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* m_pNdxTableStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}
