#pragma once

namespace SS{ 
namespace Dictionary{
namespace Edit{

/*
   ��������� �������������� ������� ����������� �� ����������:
      #DATA_FIELD_INFO = "DictionaryIndex" : INT32              // ����� ������� � ������ ������/�����
      #DATA_FIELD_INFO = "FormLower"       : WSTRING            // ����������� ���� � ������ ��������
      #DATA_FIELD_INFO = "Form"            : WSTRING - NO_FIND  // ����������� �����
      #DATA_FIELD_INFO = "IDType"          : INT32   - IS_DATA  // ������ �� �����-���
      #DATA_FIELD_INFO = "IDForm"          : INT32   - IS_DATA  // ����� �����-�����
*/
class CAbbreviationSource
{
private:
	typedef ClassLevelLockable<CAbbreviationSource> TMutex; //������������ ������� ��� ����������
private:
	DBMS::IDataBase *m_pDataBase;
	DBMS::IDataBase *m_pMorphoTypeToMorphoInfoDataBase;
	mutable CTablePtr m_pAbbreviation;
	mutable CTablePtr m_pMorphoTypeToMorphoInfo;
	wchar_t m_wzAbbreviationTableName[50];
	wchar_t m_szMorphoTypeToMorphoInfoTable[50];
	TDictNumber m_CurInitDictNumber; //����� ������� ��� �������� ���������������� �������
	TMutex m_Mutex;                  //������ ������ ������. ��������� ��� ����������� ����������, ��� ������� ��� ��������� �������� ���������� ���� �������
public:
	typedef unsigned int TIDSource;
private:
	void Open() const;
	void Close() const;
public:
	CAbbreviationSource(); 
	//�������������� �������, �������� ����������� ����� ���������� ��������
	/*
		CurInitDictNumber - ����� ������� (�������� ����� ����������� � �������� ������)
		SourceFormTableName - ����� ����� ������
	*/
	void Init( 
		DBMS::IDataBase *pDataBase, 
		DBMS::IDataBase *pMorphoTypeToMorphoInfoDataBase, 
		TDictNumber CurInitDictNumber, 
		const wchar_t *AbbreviationTableName 
	);

	/// ���������� ��� ��������� ���������� �� ������
	/**
		��������:
			�� IDSource ������� � �������� Abbreviation, MorphoTypeToMorphoInfo ������ � ������.
	*/
	bool Get( TIDSource IDSource, SSource &Source ) const;

	/// ��������� ��� ��������� ���������� ��� ������
	/**
		��������:
			������� � ������� Abbreviation ���������� ����� � 
			���������� � IDSource. ��������� � ��� ������� ������ - ���� FormLower, Form, IDType � 
			��������� ������(IDSource) � �������������� ���������� ����� � �������.
	*/
	void Add( const SSource &Source, TIDSource &IDSource );

	/// ��������� ���������� ���������� �� ������� IDSource (��� ��������� ����� ���� ����� ���������� ���)
	/**
		��������:
			������� � ������� Abbreviation ������ � IDSource � ��������� ����� ������
			� IDSource � ����������� �� Source
	*/
	void Update( TIDSource IDSource, const SSource &Source );


	/// ������� ��� ���������� �� ������
	/**
		��������:
			������� �� ������� Abbreviation, ������ � IDSource .
	*/
	void Delete( TIDSource IDSource );
};


///////////////////////////////////////////////////////////////////////////////
// ���������� CSource ��� ��������� ISource
// �������� ������������� ���������� �������� CSource
///////////////////////////////////////////////////////////////////////////////
class CAbbreviationSourceAdatper: public ISourceEx
{
public:
   //��������� ������ ����������������� ������ ��� ��������������� ��������� �������� CSource
   struct SInitStruct
   {
      //������ ��� ������ CSource::Init
      DBMS::IDataBase *pDataBase; 
      DBMS::IDataBase *pMorphoTypeToMorphoInfoDataBase;
      TDictNumber CurInitDictNumber; 
      std::wstring AbbreviationTableName; 
   };

private:
   typedef CObjectsSelector<TDictNumber, CAbbreviationSource> TAbbreviationSources;

private:
   TAbbreviationSources m_Abbreviation;
   CAbbreviationSource *m_pCurAbbreviation;
   CAbbreviationSource::TIDSource m_CurIDSource;

public:
   CAbbreviationSourceAdatper(): m_pCurAbbreviation(0), m_CurIDSource(0) {}
   
   //������ � �������������� ���������� ������� CSource ��� ������ ���������� [First, Last) ����������� �� ��������� SInitStruct
   //���������� ������� ���������
   template<class InputIterator>
   void Init( InputIterator First, InputIterator Last )
   {
      TAbbreviationSources::TAutoPtr AutoPtr;

      m_Abbreviation.Clear();
      m_pCurAbbreviation = 0;

      for( ; First != Last; ++First )
      {
         AutoPtr.reset( new CAbbreviationSource() );

         AutoPtr->Init(
            First->pDataBase,
            First->pMorphoTypeToMorphoInfoDataBase,
            First->CurInitDictNumber, 
            First->AbbreviationTableName.c_str() 
         );

         if( !m_Abbreviation.Add(First->CurInitDictNumber, AutoPtr) )
         {
            m_Abbreviation.Clear();
            SS_THROW( L"������ CAbbreviationSourceAdatper::Init" );
         }
      }
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   // ISource
   /// ������������� ������ �����
   unsigned int SetDictionaryIndex(SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex);
   
   /// ���������� ��� ��������� ���������� �� ������
   unsigned int Get(SS::Dictionary::Types::SSource* pSource);
   
   /// �������� ��� ��������� ���������� ��� ������
   void Add(SS::Dictionary::Types::SSource* pSource);
   
   /// �������� ���������� �� ������� IDSource
   void Update(SS::Dictionary::Types::SSource* pSource);
   
   /// ������� ��� ���������� �� ������
   void Delete();
};

} //namespace Edit
} //namespace Dictionary
} //namespace SS
