#include "stdafx.h"

#include ".\AbbreviationSource.h"

namespace SS{ 
namespace Dictionary{
namespace Edit{
	
///////////////////////////////////////////////////////////////////////////////
// class CSource
///////////////////////////////////////////////////////////////////////////////

CAbbreviationSource::CAbbreviationSource() : m_CurInitDictNumber(DATA_TYPE::NAMES::ednUnknown), m_pDataBase(NULL),
	 m_pMorphoTypeToMorphoInfoDataBase(NULL)
{
	memset(m_wzAbbreviationTableName, 0, sizeof(wchar_t) * 50);
	memset(m_szMorphoTypeToMorphoInfoTable, 0, sizeof(wchar_t) * 50);
} 

void CAbbreviationSource::Init( 
          DBMS::IDataBase *pDataBase, 
          DBMS::IDataBase *pMorphoTypeToMorphoInfoDataBase, 
          TDictNumber CurInitDictNumber, 
          const wchar_t *AbbreviationTableName 
)
{
	SS_TRY
	{
		APL_ASSERT(pDataBase != 0);
		APL_ASSERT(pMorphoTypeToMorphoInfoDataBase != 0);
		APL_ASSERT(AbbreviationTableName != 0);

		m_CurInitDictNumber = CurInitDictNumber;
		m_pDataBase = pDataBase;
		m_pMorphoTypeToMorphoInfoDataBase = pMorphoTypeToMorphoInfoDataBase;
		wcscpy(m_wzAbbreviationTableName, AbbreviationTableName);
		wcscpy(m_szMorphoTypeToMorphoInfoTable, L"MorphoTypeToMorphoInfo" );

		Open();
	}
	SS_CATCH(L"")
}
void CAbbreviationSource::Open() const
{
	SS_TRY
	{
		if( m_pAbbreviation.Open(m_pDataBase, m_wzAbbreviationTableName) != S_OK)
			SS_THROW( L"Open Abbreviation" );

		if( m_pMorphoTypeToMorphoInfo.Open(m_pMorphoTypeToMorphoInfoDataBase, m_szMorphoTypeToMorphoInfoTable) != S_OK )
			SS_THROW( L"Open MorphoTypeToMorphoInfo" );
	}
	SS_CATCH(L"")
}
void CAbbreviationSource::Close() const
{
	SS_TRY
	{
		m_pAbbreviation.Close();
		m_pMorphoTypeToMorphoInfo.Close();
	}
	SS_CATCH(L"")
}


///////////////////////////////////////////////////////////////////////////////
	
bool CAbbreviationSource::Get( TIDSource IDSource, SSource &Source ) const
{
	SS_TRY
	{
		Open();

		APL_ASSERT( m_pAbbreviation.IsOpen() && m_pMorphoTypeToMorphoInfo.IsOpen() );

		INT32 dbIDSource = IDSource;
		std::wstring dbSource;
		INT32 dbIDType = 0;
		INT32 dbMorphoInfo = 0;

		void *RecMapAbbreviationForm[10] = { 0, 0, &dbSource, &dbIDType };
		void *RecMapMorphoTypeToMorphoInfo[2] = { 0, &dbMorphoInfo };
		CFindHelper FindHelperAbbreviationForm(m_pAbbreviation);
		CFindHelper FindHelperMorphoTypeToMorphoInfo(m_pMorphoTypeToMorphoInfo);

		//������� ���������� ����� � �������������
		if( FindHelperAbbreviationForm.Init( 0u, &dbIDSource, RecMapAbbreviationForm) != S_OK )
			SS_THROW( L"������ ��� ������������� ������ � Abbreviation �� ID" );

		if( FindHelperAbbreviationForm.FindOne() != S_OK )
			return false;

		//����� MorphoInfo
		if( FindHelperMorphoTypeToMorphoInfo.Init(_T("IDType"), &dbIDType, RecMapMorphoTypeToMorphoInfo) != S_OK )
			SS_THROW( L"������ ��� ������������� ������ � MorphoTypeToMorphoInfo �� IDType" );

		if( FindHelperMorphoTypeToMorphoInfo.FindOne() != S_OK )
			SS_THROW( L"� ������� MorphoTypeToMorphoInfo ��� ������ ��� IDType" );

		//�������� ���������
		Source.m_DictIndex.SetId(IDSource);
		Source.m_DictIndex.SetDictionaryNumber( m_CurInitDictNumber );
		Source.m_MorphoTypeInfo.m_IDType = dbIDType;
		Source.m_MorphoTypeInfo.m_MorphoInfo  = dbMorphoInfo;
		Source.m_wSource = dbSource;

		Close();
		Open();
		return true;
	}
	SS_CATCH(L"")
	return false;
}
///////////////////////////////////////////////////////////////////////////////

void CAbbreviationSource::Add( const SSource &Source, TIDSource &IDSource )
{
	SS_TRY
	{
		Open();
		APL_ASSERT( m_pAbbreviation.IsOpen() && m_pMorphoTypeToMorphoInfo.IsOpen() );
		APL_ASSERT( Source.m_DictIndex.GetDictionaryNumber() == m_CurInitDictNumber );

		INT32 dbIDSource = 0;
		std::wstring dbSource = Source.m_wSource;
		std::vector<wchar_t> LowerBuff(Source.m_wSource.length() + 1);
		size_t Len;
		INT32 dbIDType = Source.m_MorphoTypeInfo.m_IDType;
		INT32 dbIDForm = 0;
		bool IsFirstLetterUpperCase;


		Detail::PrepareWordForSearch( dbSource.c_str(), &LowerBuff[0], Len, IsFirstLetterUpperCase );
		std::wstring dbFormLower( &LowerBuff[0] );

		APL_ASSERT( dbFormLower.length() == Source.m_wSource.length() );

		void *RecMapSourceForm[10] = { &dbIDSource, &dbFormLower, &dbSource, &dbIDType, &dbIDForm };

		//�.�. ����� GetUserValue Add � SetUserValue � ���� ������� ����� ���������� ������ ������� ����� ������
		//���������� �� ���� ��������� � ��� ������
		//�������, �� ������������ ��� ��� � ������� ����� ��������� �� ��� ����� ������
		{
			TMutex::Lock Guard(m_Mutex); 

			IDSource = dbIDSource = m_pAbbreviation->GetUserValue(0);

			if( m_pAbbreviation->AddInit(RecMapSourceForm) != S_OK )
				SS_THROW(L"������ ��� ������������� ����������� � Abbreviation");

			if( m_pAbbreviation->Add() != S_OK )
				SS_THROW(L"������ ��� ����������� � Abbreviation");

			if( m_pAbbreviation->SetUserValue(0, dbIDSource + 1) != S_OK )
				SS_THROW(L"������ SetUserValue ������� Abbreviation");
		}
		Close();
		Open();
	}
	SS_CATCH(L"")
}
///////////////////////////////////////////////////////////////////////////////

void CAbbreviationSource::Update( TIDSource IDSource, const SSource &Source )
{
	SS_TRY
	{
		Open();

		APL_ASSERT( m_pAbbreviation.IsOpen() && m_pMorphoTypeToMorphoInfo.IsOpen() );
		APL_ASSERT( Source.m_DictIndex.GetDictionaryNumber() == m_CurInitDictNumber );

		//������� ������� ������
		Delete( IDSource );

		//��������� ����� ������
		INT32 dbIDSource = 0;
		std::wstring dbSource = Source.m_wSource;
		std::vector<wchar_t> LowerBuff(Source.m_wSource.length() + 1);
		size_t Len;
		INT32 dbIDType = Source.m_MorphoTypeInfo.m_IDType;
		INT32 dbIDForm = 0;
		bool IsFirstLetterUpperCase;

		Detail::PrepareWordForSearch( dbSource.c_str(), &LowerBuff[0], Len, IsFirstLetterUpperCase );
		std::wstring dbFormLower( &LowerBuff[0] );

		APL_ASSERT( dbFormLower.length() == Source.m_wSource.length() );

		void *RecMapSourceForm[10] = { &dbIDSource, &dbFormLower, &dbSource, &dbIDType, &dbIDForm };

		//�.�. ����� GetUserValue Add � SetUserValue � ���� ������� ����� ���������� ������ ������� ����� ������
		//���������� �� ���� ��������� � ��� ������
		//�������, �� ������������ ��� ��� � ������� ����� ��������� �� ��� ����� ������
		{
			TMutex::Lock Guard(m_Mutex); 

			if( IDSource > m_pAbbreviation->GetUserValue(0) )
				if( m_pAbbreviation->SetUserValue(0, IDSource) != S_OK )
				SS_THROW(L"������ SetUserValue ������� Abbreviation");

			dbIDSource = IDSource;

			if( m_pAbbreviation->AddInit(RecMapSourceForm) != S_OK )
				SS_THROW(L"������ ��� ������������� ����������� � Abbreviation");

			if( m_pAbbreviation->Add() != S_OK )
				SS_THROW(L"������ ��� ����������� � Abbreviation");
		}
		Close();
		Open();
	}
	SS_CATCH(L"")
}
///////////////////////////////////////////////////////////////////////////////

void CAbbreviationSource::Delete( TIDSource IDSource )
{
	SS_TRY
	{
		Open();

		APL_ASSERT( m_pAbbreviation.IsOpen() && m_pMorphoTypeToMorphoInfo.IsOpen() );

		INT32 dbIDSource = IDSource;
		void *RecMapAbbreviation[10] = {};

		CFindHelper FindAbbreviation(m_pAbbreviation);

		if( FindAbbreviation.Init(_T("DictionaryIndex"), &dbIDSource, RecMapAbbreviation) != S_OK )
			SS_THROW( L"������ ��� ������������� ������ � Abbreviation �� DictionaryIndex" );

		while( FindAbbreviation.Find() == S_OK )
		{
			if( m_pAbbreviation->DeleteRecord(FindAbbreviation.GetFoundIdx()) != S_OK )
			{
				SS_THROW(L"������ �������� ������ �� Abbreviation");
			}	
		}
		Close();
		Open();
	}
	SS_CATCH(L"")
}
///////////////////////////////////////////////////////////////////////////////
// CAbbreviationSourceAdatper
///////////////////////////////////////////////////////////////////////////////
unsigned int CAbbreviationSourceAdatper::SetDictionaryIndex(SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex)
{
   SS_TRY
   {
      CAbbreviationSource *pCurAbbreviation = m_Abbreviation.Get( oDictionaryIndex.GetDictionaryNumber() );

      if( pCurAbbreviation == 0 )
         return false;
         //SS_THROW( L"������ ��� ������ ������������������� DictionaryNumber" );

      m_pCurAbbreviation = pCurAbbreviation;
      m_CurIDSource = oDictionaryIndex.GetId();
   }
   SS_CATCH(L"")

   return true;
}
///////////////////////////////////////////////////////////////////////////////

unsigned int CAbbreviationSourceAdatper::Get(SS::Dictionary::Types::SSource* pSource)
{
   APL_ASSERT_PTR( m_pCurAbbreviation );
   APL_ASSERT_PTR( pSource );
   
   SS_TRY
   {
      return m_pCurAbbreviation->Get( m_CurIDSource, *pSource );
   }
   SS_CATCH(L"")

   return false;
}
///////////////////////////////////////////////////////////////////////////////

void CAbbreviationSourceAdatper::Add(SS::Dictionary::Types::SSource* pSource)
{
   APL_ASSERT_PTR( m_pCurAbbreviation );
   APL_ASSERT_PTR( pSource );

   SS_TRY
   {
      CSource::TIDSource IDSource;
      m_pCurAbbreviation->Add( *pSource, IDSource );
      pSource->m_DictIndex.SetId( IDSource );
      m_CurIDSource = IDSource;
   }
   SS_CATCH(L"")
}
///////////////////////////////////////////////////////////////////////////////

void CAbbreviationSourceAdatper::Update(SS::Dictionary::Types::SSource* pSource)
{
   APL_ASSERT_PTR( m_pCurAbbreviation );
   APL_ASSERT_PTR( pSource );

   SS_TRY
   {
       m_pCurAbbreviation->Update( m_CurIDSource, *pSource );
       pSource->m_DictIndex.SetId( m_CurIDSource );
   }
   SS_CATCH(L"")
}
///////////////////////////////////////////////////////////////////////////////

void CAbbreviationSourceAdatper::Delete()
{
   APL_ASSERT_PTR( m_pCurAbbreviation );

   SS_TRY
   {
      m_pCurAbbreviation->Delete( m_CurIDSource );
   }
   SS_CATCH(L"")
}

} //namespace Edit
} //namespace Dictionary
} //namespace SS
					  