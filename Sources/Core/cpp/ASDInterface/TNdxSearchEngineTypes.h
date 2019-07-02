#pragma once

#include "..\ASCInterface\IDBMS.h"
#include <string>

namespace SS
{
namespace Interface
{
namespace Core
{
namespace NdxSE
{

//--------------------------------------------------------------------//

///��������� ������ ���������� ������
class CNdxSearchSettings
{
public:
	///��������� ������
	struct SSearchSettings{ 
		SSearchSettings()
			: m_StorageUsingMode(esumAll)
			, m_SearchMode(esmBooleanSearch)
			, m_EvalRelevanceMode(erWordProximityWithStatistic)
		{
		}
		///������ ������
		enum EStorageUsingMode
		{
			///����� � ����� ��������� �������
			esumSingleStorage,
			///����� c ������ ������� � ����������
			esumHeadersAndTextStorage,
			///����� c ������ ������ � ����������
			esumHeadersAndTablesStorage,
			///��� ������ ������
			esumAll
		} m_StorageUsingMode;

		///������ ������
		enum ESearchMode
		{
			///�����������
			esmUndefined,
			///����� �����
			esmBooleanSearch,
			///�������� �����
			esmFuzzySearch
		} m_SearchMode;

		///����� ���������� �������������
		enum EEvalRelevanceMode
		{
			///�����������
			erUndefined,
			///���������� �� �������
			erTextsStatistic,
			///�������� ����
			erWordProximity,
			///�������� ���� � ������ ����������
			erWordProximityWithStatistic,
			///��������� ��� �������������
			erAll
		} m_EvalRelevanceMode;
	} m_SearchSettings;

	///��������� ���������� ������
	struct SPatternSearchSettings{ 
		///���� ����� ������������������ �������� � ����������, ����� ������������� ��������� ���� ������������������
		bool m_bCheckIndexSequence;
		///��������� ��� �� ��������
		unsigned int m_uiIndexProximityLimitWeight;
		///����������� ����� �� ������ ���� ���� � ���������, 
		///������� ������ ���������� ����� ����������� � ���������� ������
		unsigned int m_uiUnionLimitWordWeightPart;
		///������������ ���������� "������ ����", ����� ���� �����������
		unsigned int m_uiUnionSurplusWordsMaxCount;
		//��� ������ ������������� ����� �������� ���� �������� ����� ������������� ���� � ���������
		///����������� ���� �������� ���� �����������
		unsigned int m_uiUnionDistanceWeightKoef;
		///����������� ���������� ���� ���� �����������
		unsigned int m_uiUnionWordsWeightKoef;
		///����������� ������ ���� �����������, �� �������� ���� ���� ����������� � ����� ���� ����������
		unsigned int m_uiUnionWeightKoef;
		///���������� ��� � �������� ����� �����������, ���������� ������������
		unsigned int m_uiGrandWordWeightLimit;
	} m_PatternSearchSettings;

	///��������� ������ � ������ ����������
	struct SSmartSearchSettings{
		///����������� ���� ���� �����������
		float m_fWordsNormKoef;
		///��������� �������� ������� �����
		float m_fRarityWordLimit;
		///�������� ������� ������ ����, ����������� ������� ������ ���� � ���������� ������
		float m_fRarityWordsQuorum;
		///����������� �������� ���������������� ���� ����
		float m_fWordsLingvoWeightKoef;
		///������������ ����� ��������� ����������� �����-������
		unsigned int m_uiAnswerIntervalLimitLength;
		///������������ ����� ��������������� ��������� ����
		unsigned int m_uiCommonIntervalLimitLength;
	} m_SmartSearchSettings;

	///��������� ���������� �����������
	struct SResultsSettings{
		///�������� ���������� ������ ��������� ����������
		unsigned int m_uiIntervalExpandRange;
		///������ ������� ��������� ������� ������������
		unsigned int m_uiIntervalJoinRange;
		///������������ ���������� ���������� ����������� � ����� ������, 
		///�� ���������� ����� ������ ����� � ������� ������ �����������
		unsigned int m_uiIntervalInTextMaxCount;
	} m_ResultsSettings;
};

//--------------------------------------------------------------------//

///�������� ����-����
class CNdxMetaFieldValue
{
public:
	CNdxMetaFieldValue(SS::Interface::Core::DBMS::EFieldDataTypes ValueType) :
		m_ValueType(ValueType), m_pValue(NULL), m_uiValueByteSize(0)
	{ 
		Init(); 
	};
	CNdxMetaFieldValue(const CNdxMetaFieldValue &x) :
		m_ValueType(SS::Interface::Core::DBMS::EFieldDataTypes::TYPE_INT32), m_pValue(NULL), m_uiValueByteSize(0)
	{
		SetValue(x.GetValue(), x.GetValueType()); 
	};
	virtual ~CNdxMetaFieldValue(void) 
	{ 
		Reset(); 
	};

	///���������� ��� ����
	SS::Interface::Core::DBMS::EFieldDataTypes GetValueType(void) const {return m_ValueType;};

	///���������� ��������� �� ��������
	void* GetValue(void) const {return (m_ValueType==SS::Interface::Core::DBMS::TYPE_INT32 || m_ValueType==SS::Interface::Core::DBMS::TYPE_UINT32)?(void*)&m_uiValueByteSize:m_pValue;};

	///������������� �������� ����, � ������������ � �����
	void SetValue(void* pValue, SS::Interface::Core::DBMS::EFieldDataTypes eValueType)
	{
		if(m_ValueType!=eValueType) {
			return;
		}
		
		if(m_ValueType==SS::Interface::Core::DBMS::TYPE_INT32 || m_ValueType==SS::Interface::Core::DBMS::TYPE_UINT32){
			m_uiValueByteSize=*(reinterpret_cast<unsigned int*>(pValue));
		}else if(m_ValueType==SS::Interface::Core::DBMS::TYPE_WSTRING){
			((std::wstring*)m_pValue)->assign(((std::wstring*)pValue)->c_str());
		}else{
			memcpy(reinterpret_cast<char*>(m_pValue), reinterpret_cast<char*>(pValue), m_uiValueByteSize);
		}
	};

	///�������� ����������
	void operator=(const CNdxMetaFieldValue& RightValue)
	{
		SetValue(RightValue.GetValue(), RightValue.GetValueType()); 
	};

	///�������� ������
	bool operator<(const CNdxMetaFieldValue& RightValue) const
	{
		if(m_ValueType!=RightValue.GetValueType()){
			return true;
		}

		switch(m_ValueType)
		{
		case SS::Interface::Core::DBMS::TYPE_INT32: case SS::Interface::Core::DBMS::TYPE_UINT32: 
			return m_uiValueByteSize<RightValue.m_uiValueByteSize?true:false;
			break;
		case SS::Interface::Core::DBMS::TYPE_WSTRING:
			return wcscmp((const wchar_t*)GetValue(), (const wchar_t*)RightValue.GetValue())<0?true:false;
			break;
		case SS::Interface::Core::DBMS::TYPE_BYTE_10:
			return memcmp(GetValue(), RightValue.GetValue(), 10)<0?true:false;
			break;
		default:
			return true;
			break;
		}

	};

	void ToString(std::wstring& szValue) const
	{
		wchar_t buf[100];

		switch(m_ValueType)
		{
		case SS::Interface::Core::DBMS::TYPE_INT32: case SS::Interface::Core::DBMS::TYPE_UINT32: 
			swprintf(buf, L"\n\tFieldValue: %u\n\tFieldType: TYPE_INT32", m_uiValueByteSize);
			szValue.assign(buf);
			break;
		case SS::Interface::Core::DBMS::TYPE_WSTRING:
			szValue.append(L"\n\tFieldValue: ");
			if(m_pValue) szValue.append(((std::wstring*)m_pValue)->c_str());
			szValue.append(L"\n\tFieldType: TYPE_WSTRING");
			break;
		case SS::Interface::Core::DBMS::TYPE_BYTE_10:
			swprintf(buf, L"\n\tFieldType: TYPE_BYTE_10");
			szValue.assign(buf);
			break;
		default:
			swprintf(buf, L"Unsupported type!!!");
			szValue.assign(buf);
			break;
		}

	};

protected:

	///�������������� ��������
	void Init(void)
	{
		switch(m_ValueType)
		{
		case SS::Interface::Core::DBMS::TYPE_INT32:  case SS::Interface::Core::DBMS::TYPE_UINT32:
			m_uiValueByteSize=0/*4*/;
			break;
		case SS::Interface::Core::DBMS::TYPE_WSTRING:
			m_uiValueByteSize=0/*500*/;
			m_pValue=new std::wstring();
			break;
		case SS::Interface::Core::DBMS::TYPE_BYTE_10:
			m_uiValueByteSize=10;
			break;
		default:
			m_uiValueByteSize=0;
			break;
		}

		if(m_uiValueByteSize)
			m_pValue=(void*)(new char[m_uiValueByteSize]);
	};

	///���������� ��������
	void Reset(void)
	{
		if(m_pValue)
		{
			if(m_ValueType==SS::Interface::Core::DBMS::TYPE_WSTRING){
				delete (std::wstring*)m_pValue;
			}else{
				delete[] (char*)m_pValue;
			}
			m_pValue=NULL;
		}
	};

	///��� ��������
	const SS::Interface::Core::DBMS::EFieldDataTypes m_ValueType;
	///��������
	void* m_pValue;
	///�������� ������ �������� ���� !!!��� 4 �������� �������� ������ ���� ��������, � m_pValue = NULL!!!
	unsigned int m_uiValueByteSize;

};

//--------------------------------------------------------------------//

///���������� ��� ���������� �� ����-������ ������
class CNdxMetaField
{
public:
	CNdxMetaField(wchar_t* pwszFieldName, 
	SS::Interface::Core::DBMS::EFieldDataTypes FieldType,
	SS::Interface::Core::DBMS::EFieldModificatorTypes FieldModificator)
	:m_FieldModificator(FieldModificator), m_bEnable(true), m_bIsSingleValue(false),
	m_SingleValue(FieldType), m_LowerValue(FieldType), m_UpperValue(FieldType)
	{
		SetFieldName(pwszFieldName);
	};

	CNdxMetaField(const CNdxMetaField& DataField)
	:m_FieldModificator(DataField.GetFieldModificator()), m_bEnable(DataField.IsEnable()), m_bIsSingleValue(false),
	m_SingleValue(DataField.GetFieldType()), m_LowerValue(DataField.GetFieldType()), m_UpperValue(DataField.GetFieldType())
	{
		SetFieldName(DataField.m_wszFieldName);
		SetValue(DataField.GetValue(), DataField.GetFieldType());
		SetLowerValue(DataField.GetLowerValue(), DataField.GetFieldType()); 
		SetUpperValue(DataField.GetUpperValue(), DataField.GetFieldType()); 
	};

	///���������� �������� ����
	const wchar_t* GetFieldName(void){return m_wszFieldName;};
	///���������� ��� ����
	SS::Interface::Core::DBMS::EFieldDataTypes GetFieldType(void) const {return m_SingleValue.GetValueType();};
	///���������� ����������� ����
	SS::Interface::Core::DBMS::EFieldModificatorTypes GetFieldModificator(void) const {return m_FieldModificator;};

	///������������� ���� ���������� ����
	void Enable(void){m_bEnable=true;};
	///������������� ���� ���������� ����
	void Disable(void){m_bEnable=false;};
	///���������� ���� ���������� ����
	bool IsEnable(void) const {return m_bEnable;};
	///���������� ���� ���������� ����
	bool IsSingleValue(void) const {return m_bIsSingleValue;};
	
	///���������� ��������� �� ��������
	void* GetValue(void) const {return m_SingleValue.GetValue();};
	///���������� ��������� �� ���������� ��������� ��������
	void* GetLowerValue(void) const {return m_LowerValue.GetValue();};
	///���������� ��������� �� ����������� ��������� ��������
	void* GetUpperValue(void) const {return m_UpperValue.GetValue();};

	///������������� �������� ����, � ������������ � �����
	void SetValue(void* pValue, SS::Interface::Core::DBMS::EFieldDataTypes eFieldType){m_SingleValue.SetValue(pValue, eFieldType); m_bIsSingleValue=true;};
	///������������� �������� ����, � ������������ � �����
	void SetLowerValue(void* pValue, SS::Interface::Core::DBMS::EFieldDataTypes eFieldType){m_LowerValue.SetValue(pValue, eFieldType); m_bIsSingleValue=false;};
	///������������� �������� ����, � ������������ � �����
	void SetUpperValue(void* pValue, SS::Interface::Core::DBMS::EFieldDataTypes eFieldType){m_UpperValue.SetValue(pValue, eFieldType); m_bIsSingleValue=false;};

	///�������� ����������
	void operator=(const CNdxMetaField& RightDF)
	{
		SetValue(RightDF.GetValue(), RightDF.GetFieldType()); 
		SetLowerValue(RightDF.GetLowerValue(), RightDF.GetFieldType()); 
		SetUpperValue(RightDF.GetUpperValue(), RightDF.GetFieldType()); 
	};

	///������������ ������ � ��� ���� ������� DBMS 
	static SS::Interface::Core::DBMS::EFieldDataTypes StringToFieldDataTypes(wchar_t* wszFieldType)
	{
		std::wstring sFieldType(wszFieldType);
		
		if(sFieldType==L"TYPE_INT32"){
			// 32-�_�������_����� 
			return 	SS::Interface::Core::DBMS::TYPE_INT32;
		}
		
		if(sFieldType==L"TYPE_UINT32"){
			// 32-�_�������_����� 
			return 	SS::Interface::Core::DBMS::TYPE_UINT32;
		}

		if(sFieldType==L"TYPE_BYTE_10"){
			// 10-�_��������_���������
			return 	SS::Interface::Core::DBMS::TYPE_BYTE_10;
		}
		if(sFieldType==L"TYPE_STRING"){
			// ������ std::string
			return 	SS::Interface::Core::DBMS::TYPE_STRING;
		}
		if(sFieldType==L"TYPE_VECTOR"){
			// ������ std::vector<BYTE>
			return 	SS::Interface::Core::DBMS::TYPE_VECTOR;
		}
		if(sFieldType==L"TYPE_WSTRING"){
			// ������ std::wstring
			return 	SS::Interface::Core::DBMS::TYPE_WSTRING;
		}
		
		// �� ���������
		return 	SS::Interface::Core::DBMS::TYPE_INT32;
	}

	///������������ ������ � ����������� ���� ������� DBMS
	static SS::Interface::Core::DBMS::EFieldModificatorTypes StringToFieldModificatorTypes(wchar_t* wszFieldMod)
	{
		std::wstring sFieldMod(wszFieldMod);
		
		if(sFieldMod==L"MOD_COMMON"){
			// ������� ��������. (������������ �������� c ������������ ������).
			return 	SS::Interface::Core::DBMS::MOD_COMMON;
		}

		if(sFieldMod==L"MOD_IS_UNIC"){
			// �������� � ��������� ���� ����� �����������. 
			//������ ������ ����� ���������� �� ����� ����� ������, 
			//� ����� ���������� ������ S_FALSE � ������, 
			//����� �������� �������� ���� � ������� ��� ����. 
			//�������� ������ �� ���� ���������� ������ "NEXT". (������ �������������: ������� � ���������� ������)    
			return 	SS::Interface::Core::DBMS::MOD_IS_UNIC;
		}

		if(sFieldMod==L"MOD_NO_FIND"){
			// ��� ������ �� ������� ����. �������� ������ �� ���� ���������� ������ "NEXT". 
			//(������ �������������: ��������� ������ � �����������, ��������� �� ������� �������)   
			return 	SS::Interface::Core::DBMS::MOD_NO_FIND;
		}

		if(sFieldMod==L"MOD_IS_DATA"){
			// ��� ������ �� ������� ����. �������� ��������� ����� � ������ ������ INT32 � BYTE_10. 
			//�������� ��������� � ������� ����� HASH-������� (������������� �������� ����� �������� ����������� !!!). 
			//�������� ������ �� ���� ���������� ������ "NEXT". (������ �������������: �� �������������, �� �������� ������)   
			return 	SS::Interface::Core::DBMS::MOD_IS_DATA;
		}
		
		// �� ���������
		return 	SS::Interface::Core::DBMS::MOD_COMMON;
	}

	virtual void ToString(std::wstring& szValue) const
	{
		wchar_t buf[100];
		swprintf(buf, L"FieldName: %s", m_wszFieldName);
		szValue.append(buf);
		
		std::wstring wsValue;

		szValue.append(L"\nValue:\n");
		m_SingleValue.ToString(wsValue);
		szValue.append(wsValue);

		szValue.append(L"\nLowerValue:\n");
		m_LowerValue.ToString(wsValue);
		szValue.append(wsValue);

		szValue.append(L"\nUpperValue:\n");
		m_UpperValue.ToString(wsValue);
		szValue.append(wsValue);
	};

protected:
	///������������� �������� ����, ��� ���� �� ������ 10 ��������
	void SetFieldName(const wchar_t* wszFieldName)
	{
		if(wcslen(wszFieldName)>=10){
			return;
		}
		wcscpy(m_wszFieldName, wszFieldName);
	};

	///�������� ����, ��� ���� �� ������ 10 ��������
	wchar_t m_wszFieldName[10];
	///����������� ����
	const SS::Interface::Core::DBMS::EFieldModificatorTypes m_FieldModificator;
	///���� ���������� ����
	bool m_bEnable;
	///���� ��������� ������� ��������
	bool m_bIsSingleValue;
	///������ �������� ����
	CNdxMetaFieldValue m_SingleValue;
	///��� ��������� ������ �������� ����
	CNdxMetaFieldValue m_LowerValue;
	///��� ��������� ������� �������� ����
	CNdxMetaFieldValue m_UpperValue;
};

///��������� ����� ����-������
typedef std::vector<CNdxMetaField> TNdxMetaFieldCollection;

//--------------------------------------------------------------------//

///����� ������ ����� �������
struct STextPathChunk
{
	STextPathChunk(
		///����� ����
		const wchar_t* pMyPathChunk
		///������������� �����
		, unsigned int uiMyIndex)
	:m_pMyPathChunk(NULL), m_uiMyIndex(uiMyIndex), 
	m_uiMyOffset(0xffffffff)
	{
		if(pMyPathChunk){
			m_pMyPathChunk=new wchar_t[wcslen(pMyPathChunk)+1];
			wcscpy((wchar_t*)m_pMyPathChunk, pMyPathChunk);
		}
	}

	virtual ~STextPathChunk(void)
	{
		if(m_pMyPathChunk)
			delete[] m_pMyPathChunk;
	}
	
	///����� ����
	const wchar_t* m_pMyPathChunk;
	///������������� �����
	/**��� ����� �� ����� 0xFFFFFFFF, ��� ���� 0xFFFFFFFE, � ��� ��������� ��� ���. ����� ������*/
	const unsigned int m_uiMyIndex;
	///�������� ����� � �����
	unsigned int m_uiMyOffset;
};

//--------------------------------------------------------------------//

}
}
}
}
