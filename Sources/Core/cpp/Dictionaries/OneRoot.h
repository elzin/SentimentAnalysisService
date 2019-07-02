#pragma once

namespace SS{ 
namespace Dictionary{
namespace Edit{


struct IOneRootBasic
{
   typedef std::list<TDictionaryIndex> TDIList;
   typedef unsigned int TIDSource;

   virtual ~IOneRootBasic() {}

   /// ���������� ������ ������������ ���� ��� �������� ������� ������
   virtual void Get( TIDSource IDSource, TDIList &SourceList ) const = 0;

   /// ��������� ������������ ����� � ��������
   virtual void Add( TIDSource IDSource, const TDIList &SourceList )
   {  APL_THROW( _T("��� ������� ���� ������� �� �������������� ���������� ������������ ����") ); }

   /// ������� ������������ ����� � �������� �����
   virtual void Delete( TIDSource IDSource, const TDIList &SourceList )
   {  APL_THROW( _T("��� ������� ���� ������� �� �������������� �������� ������������ ����") ); } 
};


/*
   ������� ��������������� DictionariesNumber
*/
class COneRootSimpleConvert: public IOneRootBasic
{
   DATA_TYPE::NAMES::DictionariesNumber m_DictNumber;

public:
   COneRootSimpleConvert( DATA_TYPE::NAMES::DictionariesNumber DictNumber ): m_DictNumber(DictNumber) {} 
   
   void Get( TIDSource IDSource, TDIList &SourceList ) const;
};

/*
   ��������������� ��� ������� �����
*/
class CArabic2RomanConvert: public IOneRootBasic
{

public:
   void Get( TIDSource IDSource, TDIList &SourceList ) const;
};

/*
   ��������������� ��������, �������� ����� ������� ������������ " � �� �
*/
class CSymbolsOneRoot: public IOneRootBasic
{
public:
   typedef std::wstring TSymbols;

private:
   typedef AssocVector<TSymbols::value_type, TSymbols> TStorage;

private:
   TStorage m_Storage;

private:
   void AddData( const TSymbols &Symbols );

public:
   CSymbolsOneRoot();
   
   void Get( TIDSource IDSource, TDIList &SourceList ) const;
};


/*
   ������ � ������������� �������
*/
class COneRoot: public IOneRootBasic
{
	wchar_t m_wzOneRootTableName[50];
	DBMS::IDataBase *m_pDataBase;
	mutable CTablePtr m_pTable;
	TDictNumber m_CurInitDictNumber; //����� ������� ��� �������� ���������������� �������

private:
	void Open() const;
	void Close() const;
	//��������� ������������ ������� ��� ������� ��� ��������� ������� DictionaryIndex
	void InitTable();

public:
	COneRoot() : m_CurInitDictNumber(TDictNumber::ednUnknown), m_pDataBase(NULL) 
	{
		memset(m_wzOneRootTableName, 0, sizeof(wchar_t) * 50);
	}

	/// �������������� �������
   /**
      CurInitDictNumber - ����� ������� (�������� ����� ����������� � �������� ������)
      OneRootTableName - ��� ������� � ��
   */
   void Init( DBMS::IDataBase *pDataBase, TDictNumber CurInitDictNumber, const wchar_t *OneRootTableName );
	
	/// ���������� ������ ������������ ���� ��� �������� ������� ������
	/**
		��������:
			������� � ������� NominalOneRoot ��� ������ � IDSource
	*/
	void Get( TIDSource IDSource, TDIList &SourceList ) const;

	/// ��������� ������������ ����� � ��������
	/**
		��������:
			��������� � ������� NominalOneRoot ��� ������ � IDSource  � IDOneRoot == �������� � ������
	*/
	void Add( TIDSource IDSource, const TDIList &SourceList );
	
	/// ������� ������������ ����� � �������� �����
	/**
		��������:
			������� �� ������� NominalOneRoot ��� ������ � IDSource  � IDOneRoot == �������� � ������
	*/
	void Delete( TIDSource IDSource, const TDIList &SourceList );
};

///////////////////////////////////////////////////////////////////////////////
// ���������� COneRoot ��� ��������� IOneRoot
// �������� ������������� ���������� �������� COneRoot
///////////////////////////////////////////////////////////////////////////////
class COneRootAdapter: public IOneRoot
{
public:
   //��������� ������ ����������������� ������ ��� ��������������� ��������� �������� COneRoot
   struct SInitStruct
   {
      //������ ��� ������ COneRoot::Init
      DBMS::IDataBase *pDataBase;
      TDictNumber CurInitDictNumber; 
      std::wstring OneRootTableName;   
   };

private:
   typedef CObjectsSelector<TDictNumber, IOneRootBasic> TOneRoots;

private:
   TOneRoots m_OneRoots;
   IOneRootBasic *m_pCurOneRoot;
   IOneRootBasic::TIDSource m_CurIDSource;

public:
   COneRootAdapter(): m_pCurOneRoot(0), m_CurIDSource(0) {}

   //������ � �������������� ���������� ������� COneRoot ��� ������ ���������� [First, Last) ����������� �� ��������� SInitStruct
   //���������� ������� ���������
   template<class InputIterator>
   void Init( InputIterator First, InputIterator Last )
   {
      TOneRoots::TAutoPtr AutoPtr;
      CObjectsSelector<TDictNumber, COneRoot>::TAutoPtr AutoPtrTmp;

      m_OneRoots.Clear();
      m_pCurOneRoot = 0;

      for( ; First != Last; ++First )
      {
         AutoPtrTmp.reset( new COneRoot() );

         AutoPtrTmp->Init(
            First->pDataBase,
            First->CurInitDictNumber, 
            First->OneRootTableName.c_str() 
         );

         AutoPtr = AutoPtrTmp;

         if( !m_OneRoots.Add(First->CurInitDictNumber, AutoPtr) )
         {
            m_OneRoots.Clear();
            SS_THROW( L"������ COneRootAdapter::Init" );
         }
      }

      AutoPtr.reset( new COneRootSimpleConvert(DATA_TYPE::NAMES::ednNumeric) );

      if( !m_OneRoots.Add(DATA_TYPE::NAMES::ednRomanNumeric, AutoPtr) )
      {
         m_OneRoots.Clear();
         SS_THROW( L"������ COneRootAdapter::Init" );
      }

      AutoPtr.reset( new CArabic2RomanConvert );

      if( !m_OneRoots.Add(DATA_TYPE::NAMES::ednNumeric, AutoPtr) )
      {
         m_OneRoots.Clear();
         SS_THROW( L"������ COneRootAdapter::Init" );
      }

      AutoPtr.reset( new CSymbolsOneRoot );  
      if( !m_OneRoots.Add(DATA_TYPE::NAMES::ednSymbols, AutoPtr) )
      {
         m_OneRoots.Clear();
         SS_THROW( L"������ COneRootAdapter::Init" );
      }
   }

   ///////////////////////////////////////////////////////////////////////////////
   // IOneRoot
   
   /// ������������� ������ �����
   unsigned int SetDictionaryIndex(SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex);
  
   /// ���������� ������ ������������ ���� ��� �������� ������� ������
   void Get(std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_IDSource);
   
   /// ��������� ������������ ����� � ��������
   void Add(std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_IDSource);
   
   /// ������� ������������ ����� � �������� �����
   void Delete(std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_IDSource);
};

} //namespace Edit
} //namespace Dictionary
} //namespace SS
