#pragma once

namespace SS{ 
namespace Dictionary{

///////////////////////////////////////////////////////////////////////////////
// ����� ��������� ������������� ������� ����� ����
///////////////////////////////////////////////////////////////////////////////
class CNewWordsListBasic
{
   typedef CMorphoTypesSearchCreateManager::TPointer TMorphoTypesSearchPtr;

   CTablePtr m_Table;
   TDictNumber m_DictNumber; 
   TMorphoTypesSearchPtr m_pMorphoTypesSearch;
   INT32 m_dbIDSource;
   std::wstring m_dbSource;
   std::wstring m_dbSourceLower;
   INT32 m_dbIDType;
   void *m_RecMap[4];

public:
   CNewWordsListBasic(): m_DictNumber(DATA_TYPE::NAMES::ednUnknown), m_dbIDSource(0), m_dbIDType(0) 
   {
      m_RecMap[0] = &m_dbIDSource;
      m_RecMap[1] = &m_dbSource;
      m_RecMap[2] = &m_dbSourceLower;
      m_RecMap[3] = &m_dbIDType;
   
   }
   void Init( DBMS::IDataBase *pNewWordsDataBase, DBMS::IDataBase *pMorphoDataBase, TDictNumber DictNumber, const TCHAR *TableName );
   
   //������� �������� ������� ����� �����������
   void CloseTables() { m_Table.Close(); }

   /// ������ ����������� ���� ������� ����
   unsigned int GetCount();
   
   /// �������� � ������� ����� � ������ (� ������� ���������).
   bool MoveFirst();
   
   /// �������� � ���������� ����� � ������ (� ������� ���������).
   /// ���� ��������� ������� true ������������� ����� ����, ���� false �� ���� ������ ���
   bool MoveNext(TWordInfo &WordInfo);
   
   /// ������ ������� �����
   void GetWord(TWordInfo &WordInfo);
};

///////////////////////////////////////////////////////////////////////////////
// ���������� ���������� IWordsList
// ������ ������� ����� ����
///////////////////////////////////////////////////////////////////////////////
class CNewWordsList: public IWordsList
{
public:
   //��������� ������ ����������������� ������ ��� ��������������� ��������� �������� CNewWordsListBasic
   struct SInitStruct
   {
      //������ ��� ������ CNewWordsList::Init
      DBMS::IDataBase *pNewWordsDataBase; 
      DBMS::IDataBase *pMorphoDataBase;
      TDictNumber CurInitDictNumber; 
      std::wstring TableName;   
   };

private:
   typedef CObjectsSelector<TDictNumber, CNewWordsListBasic> TNewWordsLists;

private:
   TNewWordsLists m_NewWordsLists;
   CNewWordsListBasic *m_pCurNewWordsList;

public:
   CNewWordsList(): m_pCurNewWordsList(0) {}

   //������ � �������������� ���������� ������� CNewWordsListBasic ��� ������ ���������� [First, Last) ����������� �� ��������� SInitStruct
   //���������� ������� ���������
   template<class InputIterator>
   void Init( InputIterator First, InputIterator Last )
   {
      TNewWordsLists::TAutoPtr AutoPtr;

      m_NewWordsLists.Clear();
      m_pCurNewWordsList = 0;

      for( ; First != Last; ++First )
      {
         AutoPtr.reset( new CNewWordsListBasic() );

         AutoPtr->Init(
            First->pNewWordsDataBase,
            First->pMorphoDataBase,
            First->CurInitDictNumber, 
            First->TableName.c_str() 
         );

         if( !m_NewWordsLists.Add(First->CurInitDictNumber, AutoPtr) )
         {
            m_NewWordsLists.Clear();
            SS_THROW( L"������ CNewWordsList::Init" );
         }
      }
   }

   //������� �������� ������� ����� �����������
   void CloseTables() 
   { 
      for( TNewWordsLists::TIterator I = m_NewWordsLists.Begin(); I != m_NewWordsLists.End(); ++I )
         I->CloseTables(); 
   }

   ///////////////////////////////////////////////////////////////////////////////
   // IWordsList

   /// ���������� ����� �������, �� �������� ���������� �������� ������ ����
   void SetDictionaryNumber( TDictNumber eDictionariesNumber );
   
   /// ������ ����������� ���� ������� ����
   unsigned int GetCount();
   
   /// �������� � ������� ����� � ������ (� ������� ���������).
   unsigned int MoveFirst();
   
   /// ������� � ���������� ����� � ������ (� ������� ���������).
   /// ���� ��������� ������� true ������������� ����� ����, ���� false �� ���� ������ ���
   unsigned int MoveNext( TWordInfo * pWordInfo );
   
   /// ������ ������� �����
   void GetWord( TWordInfo * pWordInfo );
};


} //namespace Dictionary
} //namespace SS
