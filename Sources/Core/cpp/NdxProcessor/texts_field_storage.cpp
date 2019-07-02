#include "StdAfx.h"
#include ".\texts_field_storage.h"
#include "console.h"
#include "const.h"


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
using namespace SS::Interface::Core::DBMS;
using namespace SS::Interface::Core::NdxSE;
using namespace SS::Core::Types::IndexationSearch;

//--------------------------------------------------------------------//

CTextsFieldsStorage::CTextsFieldsStorage(INdxTableStorage* pNdxTableStorage)
:CTableStorage(pNdxTableStorage)
{
}

CTextsFieldsStorage::~CTextsFieldsStorage(void)
{
}

void CTextsFieldsStorage::PrepareIndexing(void)
{
	if(ISNULL(m_pNdxTableStorage)) return;

	//���������� ������� ���������
	m_CoordinateCounter.Reset();
	//������� ������� ���������
	m_CoordinateCounter.Update(SNdxLevelInfo::ictTextAbsNumber, GetTextsNumber());
}

void CTextsFieldsStorage::AddTextInfo(TNdxMetaFieldCollection* pNdxMetaFieldCollection)
{
	if(ISNULL(m_pNdxTableStorage)) return;
	
	//������������� �������� ����������� ���� - �������������� ���������
	for(unsigned int i=0; i<pNdxMetaFieldCollection->size(); i++)
	{
		if(pNdxMetaFieldCollection->at(i).GetFieldModificator()==MOD_IS_UNIC){
			unsigned int uiTextID=m_CoordinateCounter.GetCoordinate(SNdxLevelInfo::ictTextAbsNumber);
			pNdxMetaFieldCollection->at(i).SetValue(&uiTextID, pNdxMetaFieldCollection->at(i).GetFieldType());
			break;
		}
	}
	
	//��������� ���������� � �������
	Append(pNdxMetaFieldCollection);
	
	//����������� �������
	m_CoordinateCounter.Increment(SNdxLevelInfo::ictTextAbsNumber);
}

void CTextsFieldsStorage::GetTextInfo(unsigned int uiTextIndex, CNdxMetaField* pNdxMetaField)
{
	if(ISNULL(m_pNdxTableStorage)) return;
	if(ISNULL(pNdxMetaField)) return;

	unsigned int uiDataFieldID=GetDataFieldIndex(pNdxMetaField->GetFieldName());
	//��������� ���� �� ������������� ���� � �������
	if(uiDataFieldID==EMPTY_VALUE){
		TO_CONSOLE(L"DataField does not exist!!!");
		ToConsole(pNdxMetaField->GetFieldName());
		return;
	}
	
    //��������� �������� ������ ������
	TNdxMetaFieldCollection ResultDataRow;
	for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
	{
		ResultDataRow.push_back(
			CNdxMetaField((wchar_t*)m_TextFieldCollection[i].GetFieldName(), 
				m_TextFieldCollection[i].GetFieldType(), m_TextFieldCollection[i].GetFieldModificator()));
		if(m_TextFieldCollection[i].GetFieldModificator()==MOD_IS_UNIC){
			//������������� ���� ������
			ResultDataRow.back().SetValue((void*)&uiTextIndex, m_TextFieldCollection[i].GetFieldType());
		}
	}
	
	//��������� �����
	ExtractByKey(&ResultDataRow);
	
	//���������� ��������� ��������
	pNdxMetaField->SetValue(ResultDataRow[uiDataFieldID].GetValue(), ResultDataRow[uiDataFieldID].GetFieldType());
}

void CTextsFieldsStorage::GetTextInfo(unsigned int uiTextIndex, TNdxMetaFieldCollection* pNdxMetaFieldCollection)
{
	if(ISNULL(m_pNdxTableStorage)) return;
	if(ISNULL(pNdxMetaFieldCollection)) return;

	vector<pair<unsigned int, unsigned int> > DataFieldIDCollection;
	unsigned int uiDataFieldID;
	for(unsigned int i=0; i<pNdxMetaFieldCollection->size(); i++)
	{
		if(pNdxMetaFieldCollection->at(i).IsEnable()){
			uiDataFieldID=GetDataFieldIndex(pNdxMetaFieldCollection->at(i).GetFieldName());
			//��������� ���� �� ������������� ���� � �������
			if(uiDataFieldID==EMPTY_VALUE){
				TO_CONSOLE(L"DataField does not exist!!!");
				ToConsole(pNdxMetaFieldCollection->at(i).GetFieldName());
			}else{
				DataFieldIDCollection.push_back(pair<unsigned int, unsigned int>(i, uiDataFieldID));
			}
		}
	}
	
	if(DataFieldIDCollection.empty()) return;
	
    //��������� �������� ������ ������
	TNdxMetaFieldCollection ResultDataRow;
	for(unsigned int i=0; i<m_TextFieldCollection.size(); i++)
	{
		ResultDataRow.push_back(
			CNdxMetaField((wchar_t*)m_TextFieldCollection[i].GetFieldName(), 
				m_TextFieldCollection[i].GetFieldType(), m_TextFieldCollection[i].GetFieldModificator()));
		if(m_TextFieldCollection[i].GetFieldModificator()==MOD_IS_UNIC){
			//������������� ���� ������
			ResultDataRow.back().SetValue((void*)&uiTextIndex, m_TextFieldCollection[i].GetFieldType());
		}
	}
	
	//��������� �����
	ExtractByKey(&ResultDataRow);
	
	//���������� ��������� ��������
	for(vector<pair<unsigned int, unsigned int> >::iterator itDataField=DataFieldIDCollection.begin(); itDataField!=DataFieldIDCollection.end(); itDataField++){
		pNdxMetaFieldCollection->at(itDataField->first).
			SetValue(ResultDataRow[itDataField->second].GetValue(), ResultDataRow[itDataField->second].GetFieldType());
	}
}

void CTextsFieldsStorage::GetTexts(TNdxMetaFieldCollection* pNdxMetaFieldCollection, 
	Containers::CFindResultCollection* pFindResults, TSearchParams* pSearchParams)
{
	if(ISNULL(pNdxMetaFieldCollection)) return;
	if(ISNULL(pFindResults)) return;
	
	TDataFieldExtracts ResultTextFields;
	/*---UNUSED
	unsigned int uiMaxResultsCount = EMPTY_VALUE;
	if (pSearchParams) {
		uiMaxResultsCount = pSearchParams->m_uiMaxSearchResultsCount;
	}
	*/
	
	//����������� �����, �� ���� ������� �������
	ExtractKeys(pNdxMetaFieldCollection, &ResultTextFields);
	
	//���������� �� � ����������, � ������ �����������
	ToConsole(L"Finded by Fields:");
	/*---UNUSED
	unsigned int uiResultsNumber = 0;*/
	unsigned int uiTextID = 0;
	TDataFieldExtracts::iterator itTextField = ResultTextFields.begin();
	while (itTextField != ResultTextFields.end() /*---ALWAYS TRUE--- && uiResultsNumber <= uiMaxResultsCount*/)
	{
		//�������� ID ������
		memcpy((void*)&uiTextID, itTextField->GetValue(), sizeof(unsigned int));
		ToConsole(L"TextID", uiTextID);
		//��������� ���������, ������������� ��� ���
		pFindResults->AddFindResult(uiTextID, 0);
		
		itTextField++;
	}
}

unsigned int CTextsFieldsStorage::GetTextsNumber(void)
{
	if(ISNULL(m_pNdxTableStorage)) return 0;
	return m_pNdxTableStorage->GetDataUnitSize();
}

void CTextsFieldsStorage::DeleteText(unsigned int uiTextIndex)
{
	if(uiTextIndex==EMPTY_VALUE){
		TO_CONSOLE(L"uiTextIndex is empty!!!");
		return;
	}
	
	CNdxMetaField NdxMetaField(L"FileId", TYPE_UINT32, MOD_IS_UNIC);
	NdxMetaField.SetValue((void*)&uiTextIndex, TYPE_UINT32);	
	DeleteByKey(&NdxMetaField);
}

//--------------------------------------------------------------------//

}
}
}
}
}
