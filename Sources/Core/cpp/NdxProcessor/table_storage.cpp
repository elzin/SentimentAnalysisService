#include "StdAfx.h"
#include ".\table_storage.h"
#include "console.h"
#include "const.h"
#include <iterator>


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

using namespace SS::Interface::Core::NdxSE::NdxDataStorage;
using namespace SS::Interface::Core::NdxSE;
using namespace SS::Interface::Core::DBMS;

//--------------------------------------------------------------------//

CTableStorageDataField::CTableStorageDataField(wchar_t* pwszFieldName, 
					   EFieldDataTypes FieldType, EFieldModificatorTypes FieldModificator) :
	CNdxMetaField(pwszFieldName, FieldType, FieldModificator), 
	m_usFindProgramId(UC_EMPTY), m_usSpanFindProgramId(UC_EMPTY)
{
}

CTableStorageDataField::CTableStorageDataField(const CTableStorageDataField& DataField) :
	CNdxMetaField(DataField), m_usFindProgramId(0), m_usSpanFindProgramId(UC_EMPTY)
{
}

void CTableStorageDataField::View(void) const
{
	ToConsole(L"//------DataField");

	wstring szValue;
	ToString(szValue);
	ToConsole(szValue.c_str());

	ToConsole(L"//------Eof-DataField");
}

//--------------------------------------------------------------------//

CTableStorage::CTableStorage(INdxTableStorage* pNdxTableStorage)
:m_pNdxTableStorage(pNdxTableStorage), m_uiKeyFieldIndex(EMPTY_VALUE)
{
	if(ISNULL(m_pNdxTableStorage)) return;

	if(!m_pNdxTableStorage->IsOpen()){
		TO_CONSOLE(L"NdxTableStorage not opened");
		ToConsole(m_pNdxTableStorage->GetDataUnitName());
		return;
	}

	FillTextFieldCollection();
}

CTableStorage::~CTableStorage(void)
{
	ClearTextFieldCollection();
}

void CTableStorage::FillTextFieldCollection(void)
{
	if(ISNULL(m_pNdxTableStorage)) return;

	INdxTableStorage::TTableFieldCollection* pTableFieldCollection=m_pNdxTableStorage->GetFieldsCollection();

	if(ISNULL(pTableFieldCollection)) return;
	ClearTextFieldCollection();
	//��������� ��������� ����� �������

	for(INdxTableStorage::TTableFieldCollection::iterator 
		itFD=pTableFieldCollection->begin(); itFD!=pTableFieldCollection->end(); itFD++)
	{
		if(itFD->etFieldType==TYPE_FINAL) break;
		m_TextFieldCollection.push_back(CTableStorageDataField(itFD->szFieldName, (EFieldDataTypes)itFD->etFieldType, (EFieldModificatorTypes)itFD->etFieldModificator));
	}
	
	for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
	{
		m_AppendValuesCollection.push_back(m_TextFieldCollection[i].GetValue());
		if(m_TextFieldCollection[i].GetFieldModificator()==MOD_IS_UNIC){
			m_uiKeyFieldIndex=i;
			m_FindKeysValuesCollection.push_back(m_TextFieldCollection[i].GetValue());
			m_FindByKeysValuesCollection.push_back(0);	
		}else{
			m_FindKeysValuesCollection.push_back(0);
			m_FindByKeysValuesCollection.push_back(m_TextFieldCollection[i].GetValue());
		}
	}

	//������ ���������� ��� ������ � ���������� ������
	unsigned short usFindProgramID;
	unsigned short usSpanFindProgramID;
	for(TDataFieldCollection::iterator itDataField=m_TextFieldCollection.begin(); itDataField!=m_TextFieldCollection.end(); itDataField++)
	{
		if(itDataField->GetFieldModificator()&MOD_INDEXED){
			//������� ����� �������� ID ��������� ������, ��� ���������� ����� �� �����
			m_pNdxTableStorage->SpanFindInit((wchar_t*)itDataField->GetFieldName(), 
				itDataField->GetLowerValue(), itDataField->GetUpperValue(), &m_SpanFindCollection, &usSpanFindProgramID);
		
			//������������� ��������� ������ �� ������� ����
			itDataField->SetSpanFindProgramId(usSpanFindProgramID);
		}

		if(itDataField->GetFieldModificator()==MOD_IS_UNIC){
			//������� ����� �������� ID ��������� ������, ��� ���������� ����� �� �����
			m_pNdxTableStorage->InitFind((wchar_t*)itDataField->GetFieldName(), 
				itDataField->GetValue(), &m_FindByKeysValuesCollection[0], &usFindProgramID);
		}else{
			//������� ����� �������� ID ��������� ������, ��� ���������� ������
			m_pNdxTableStorage->InitFind((wchar_t*)itDataField->GetFieldName(), 
				itDataField->GetValue(), &m_FindKeysValuesCollection[0], &usFindProgramID);
		}

		//������������� ��������� ������ �� ������� ����
		itDataField->SetFindProgramId(usFindProgramID);
	}
		
	//������� ����������
	if(m_pNdxTableStorage->InitAdd(&m_AppendValuesCollection[0])!=S_OK) return;
}

void CTableStorage::Scan(void)
{
	TValuesCollection m_ScanValuesCollection;
	for(TDataFieldCollection::iterator itDataField=m_TextFieldCollection.begin(); itDataField!=m_TextFieldCollection.end(); itDataField++)
	{
		m_ScanValuesCollection.push_back(itDataField->GetValue());
	}
	
	//����� �������
	if(m_pNdxTableStorage->InitScan(0, &m_ScanValuesCollection[0])!=S_OK) return;
	while(m_pNdxTableStorage->Scan()==S_OK)
	{
		for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
		{
			m_TextFieldCollection[i].View();
		}
	}

}

void CTableStorage::Append(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pDataRow)
{
	if(ISNULL(pDataRow)) return;
	if(m_AppendValuesCollection.size()!=pDataRow->size()){
		TO_CONSOLE(L"Not correct row format...");
		return;
	}

	for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
	{
		m_TextFieldCollection[i].SetValue(pDataRow->at(i).GetValue(), pDataRow->at(i).GetFieldType());
	}

	//����������� �������� ������ ��� ����������
	//for(unsigned int i=0; i<pDataRow->size(); i++)
	//{
	//	m_AppendValuesCollection[i]=pDataRow->at(i).GetValue();
	//}

	//��������� ������ � �������
	m_pNdxTableStorage->Add();
}

void CTableStorage::ExtractKeys(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pFilterDataRow, TDataFieldExtracts* pResultExtracts)
{
	if(ISNULL(pFilterDataRow)) return;
	if(ISNULL(pResultExtracts)) return;

	if(m_TextFieldCollection.size()!=pFilterDataRow->size()){
		TO_CONSOLE(L"Not correct row format...");
		return;
	}

	///��������� ��������������� �������� ������
	vector<unsigned short> FindProgramIDCollection;
	vector<unsigned short> SpanFindProgramIDCollection;
	//����������� �������� ����� ������������ ��� ������
	//��������� ��������� ������
	for(unsigned int i=0; i<pFilterDataRow->size(); i++)
	{
		if(pFilterDataRow->at(i).IsEnable()){
			if(m_TextFieldCollection[i].GetFieldType()==pFilterDataRow->at(i).GetFieldType()){
				if(pFilterDataRow->at(i).IsSingleValue()){
					//����������� �������� ���������������� �����
					m_TextFieldCollection[i].SetValue(pFilterDataRow->at(i).GetValue(), pFilterDataRow->at(i).GetFieldType());

					//��������� ������������� ��������� ������
					FindProgramIDCollection.push_back(m_TextFieldCollection[i].GetFindProgramId());
				}else{
					//����������� �������� ���������������� �����
					m_TextFieldCollection[i].SetLowerValue(
						pFilterDataRow->at(i).GetLowerValue(), pFilterDataRow->at(i).GetFieldType());
					m_TextFieldCollection[i].SetUpperValue(
						pFilterDataRow->at(i).GetUpperValue(), pFilterDataRow->at(i).GetFieldType());
					
					//��������� ������������� ��������� ������
					SpanFindProgramIDCollection.push_back(m_TextFieldCollection[i].GetSpanFindProgramId());
				}
			}else{
				TO_CONSOLE(L"Not correct field format...");
				ToConsole(pFilterDataRow->at(i).GetFieldName());
			}
		}
	}
	
	//��������� ����� �� �������� ���������� ������ � ���������� ����������� ������
	TRecordIdCollection RecordIdCollection;
	if(!FindProgramIDCollection.empty()){
		ExtractRecords(&FindProgramIDCollection, &RecordIdCollection);
		if(RecordIdCollection.empty()) return;
	}

	SpanExtractRecords(&SpanFindProgramIDCollection, &RecordIdCollection);
	if(RecordIdCollection.empty()) return;

	TValuesCollection m_ScanValuesCollection;
	for(TDataFieldCollection::iterator itDataField=m_TextFieldCollection.begin(); itDataField!=m_TextFieldCollection.end(); itDataField++)
	{
		if(itDataField->GetFieldModificator()==MOD_IS_UNIC){
			m_ScanValuesCollection.push_back(itDataField->GetValue());
		}else{
			m_ScanValuesCollection.push_back(0);
		}
	}
	
	//����� �������
	if(m_pNdxTableStorage->InitScan(0, &m_ScanValuesCollection[0])!=S_OK) return;

	for(TRecordIdCollection::iterator itRecordID=RecordIdCollection.begin(); itRecordID!=RecordIdCollection.end(); itRecordID++)
	{
		if(m_pNdxTableStorage->ScanOne(*itRecordID)==S_OK)
		{
			//m_TextFieldCollection[m_uiKeyFieldIndex].View();
			pResultExtracts->insert(CTableStorageDataField(m_TextFieldCollection[m_uiKeyFieldIndex]));
		}
	}
	
}

void CTableStorage::ExtractRecords(vector<unsigned short>* pFindProgramIDCollection, TRecordIdCollection* pRecordIdCollection)
{
	if(ISNULL(pFindProgramIDCollection)) return;
	if(ISNULL(pRecordIdCollection)) return;

	//��������� ����� �� �������� ���������� ������ � ���������� ����������� ������
	TRecordIdCollection FindRecordIdCollection;
	for(vector<unsigned short>::iterator itFP=pFindProgramIDCollection->begin(); itFP!=pFindProgramIDCollection->end(); itFP++)
	{
		//������� �������� �������
		FindRecordIdCollection.clear();
		//��������� �����, ��������� ������� ������������
		while(m_pNdxTableStorage->Find(*itFP)==S_OK)
		{
			FindRecordIdCollection.insert(m_pNdxTableStorage->GetFoundRecordIndex(*itFP));
		}

		//���� �������� ������� ������, ��������� ����� ����� ������
		if(FindRecordIdCollection.empty()){
			pRecordIdCollection->clear();		
			return;
		}

		if(itFP==pFindProgramIDCollection->begin()){
			//��� ������� ������ ������ ��������� ����������
			pRecordIdCollection->swap(FindRecordIdCollection);
			//ViewDataFieldExtracts(pResultExtracts);
		}
		else
		{
			//ViewDataFieldExtracts(&FindExtracts);
			//ViewDataFieldExtracts(pResultExtracts);
			
			TRecordIdCollection TempRecordIdCollection;//(pRecordIdCollection->begin(), pRecordIdCollection->end());

			//��� ����������� ������� ���������� ����������� 
			//�������������� �������, � ���������, ��������� �������������� (���������)
			//TRecordIdCollection::iterator itBound=
			set_intersection(FindRecordIdCollection.begin(), FindRecordIdCollection.end(), 
				pRecordIdCollection->begin(), pRecordIdCollection->end(),
				std::inserter(TempRecordIdCollection, TempRecordIdCollection.begin()));
			//TempRecordIdCollection.erase(itBound, TempRecordIdCollection.end());
			pRecordIdCollection->swap(TempRecordIdCollection);

			//ViewDataFieldExtracts(pResultExtracts);
		}
	}
}

void CTableStorage::SpanExtractRecords(vector<unsigned short>* pFindProgramIDCollection, TRecordIdCollection* pRecordIdCollection)
{
	if(ISNULL(pFindProgramIDCollection)) return;
	if(ISNULL(pRecordIdCollection)) return;

	//��������� ����� �� �������� ���������� ������ � ���������� ����������� ������
	for(vector<unsigned short>::iterator itFP=pFindProgramIDCollection->begin(); itFP!=pFindProgramIDCollection->end(); itFP++)
	{
		//������� �������� �������
		m_SpanFindCollection.clear();
		//��������� �����, ��������� ������� ������������
		m_pNdxTableStorage->SpanFind(*itFP);

		//���� �������� ������� ������, ��������� ����� ����� ������
		if(m_SpanFindCollection.empty()){
			pRecordIdCollection->clear();		
			return;
		}

		if(itFP==pFindProgramIDCollection->begin()){
			//��� ������� ������ ������ ��������� ����������
			pRecordIdCollection->swap(m_SpanFindCollection);
			//ViewDataFieldExtracts(pResultExtracts);
		}
		else
		{
			//ViewDataFieldExtracts(&FindExtracts);
			//ViewDataFieldExtracts(pResultExtracts);
			
			TRecordIdCollection TempRecordIdCollection;//(pRecordIdCollection->begin(), pRecordIdCollection->end());

			//��� ����������� ������� ���������� ����������� 
			//�������������� �������, � ���������, ��������� �������������� (���������)
			//TRecordIdCollection::iterator itBound=
			set_intersection(m_SpanFindCollection.begin(), m_SpanFindCollection.end(), 
				pRecordIdCollection->begin(), pRecordIdCollection->end(),
				std::inserter(TempRecordIdCollection, TempRecordIdCollection.begin()));
			//TempRecordIdCollection.erase(itBound, TempRecordIdCollection.end());
			pRecordIdCollection->swap(TempRecordIdCollection);

			//ViewDataFieldExtracts(pResultExtracts);
		}
	}
}

void CTableStorage::ExtractByKey(TNdxMetaFieldCollection* pResultDataRow)
{
	if(ISNULL(pResultDataRow)) return;

	if(m_TextFieldCollection.size()!=pResultDataRow->size()){
		TO_CONSOLE(L"Not correct row format...");
		return;
	}

	//����������� �������� �����
	m_TextFieldCollection[m_uiKeyFieldIndex].SetValue(
		pResultDataRow->at(m_uiKeyFieldIndex).GetValue(), pResultDataRow->at(m_uiKeyFieldIndex).GetFieldType());

	//��������� �����, ��������� ������� ������������
	if(m_pNdxTableStorage->FindOne(m_TextFieldCollection[m_uiKeyFieldIndex].GetFindProgramId())!=S_OK)
	{
		TO_CONSOLE(L"Find not successed...");
		return;
	}
	
	//��������� ���������
	for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
	{
		//m_TextFieldCollection[i].View();
		if(pResultDataRow->at(i).IsEnable()){
			//����������� ��������� �������� �����
			pResultDataRow->at(i).SetValue(
				m_TextFieldCollection[i].GetValue(), m_TextFieldCollection[i].GetFieldType());
		}
	}
}

void CTableStorage::ViewDataFieldExtracts(TDataFieldExtracts* pDataFieldExtracts)
{
	if(ISNULL(pDataFieldExtracts)) return;
	ToConsole(L"//-----------DataFieldExtracts:");
	for(CTableStorage::TDataFieldExtracts::iterator itDF=pDataFieldExtracts->begin(); itDF!=pDataFieldExtracts->end(); itDF++)
	{
		(itDF)->View();
	}
	ToConsole(L"//-----------Eof-DataFieldExtracts");
}

unsigned int CTableStorage::GetDataFieldIndex(const wchar_t* wszFieldName)
{
	wstring wsFieldName(wszFieldName);
	wcslwr((wchar_t*)wsFieldName.c_str());
	wstring wsTemp;
	for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
	{
		wsTemp.assign(m_TextFieldCollection[i].GetFieldName());
		wcslwr((wchar_t*)wsTemp.c_str());
		if(!wcscmp(wsTemp.c_str(), wsFieldName.c_str())){
			return i;
		}
	}

	return EMPTY_VALUE;
}

void CTableStorage::DeleteByKey(SS::Interface::Core::NdxSE::CNdxMetaField* pKeyField)
{
	if(ISNULL(pKeyField)) return;
	
	if(GetDataFieldIndex(pKeyField->GetFieldName())==EMPTY_VALUE && pKeyField->GetFieldModificator()!=MOD_IS_UNIC){
		TO_CONSOLE(L"Not correct key field...");
		return;
	}

	//����������� �������� �����
	m_TextFieldCollection[m_uiKeyFieldIndex].SetValue(
		pKeyField->GetValue(), pKeyField->GetFieldType());

	//��������� �����, ��������� ������� ������������
	if(m_pNdxTableStorage->FindOne(m_TextFieldCollection[m_uiKeyFieldIndex].GetFindProgramId())!=S_OK)
	{
		TO_CONSOLE(L"Find not successed...");
		return;
	}

	//�������� ������ ������
	unsigned int uiRowIndex=m_pNdxTableStorage->GetFoundRecordIndex(m_TextFieldCollection[m_uiKeyFieldIndex].GetFindProgramId());
	
	//������� ������
	m_pNdxTableStorage->DeleteRecord(uiRowIndex);
}

//--------------------------------------------------------------------//

}
}
}
}
}