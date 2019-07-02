#pragma once

namespace SS{ 
namespace Dictionary{


class CAbbreviationsBasic
{
protected:
   CAbbreviationsBasic():  m_DictIndex( DATA_TYPE::NAMES::ednUnknown ) {}

   TDictNumber m_DictIndex;

   void FillSWordInfo( 
      const std::wstring &wcWord,
      unsigned int IDSource,
      const TIDForm &IDForm,
      const TIDType &IDType,
      const TSpecialMorpho &SpecialMorpho,
      const TMorphoInfo &MorphoInfo,
      SWordInfo &WordInfo,
      bool FirstLetterUpperCase
   ) const
   {
      WordInfo.m_wWord = wcWord;
      WordInfo.m_SpecialMorpho = SpecialMorpho;
      WordInfo.m_WordIndex.m_DictIndex.SetId(IDSource) ; 
      WordInfo.m_WordIndex.m_DictIndex.SetDictionaryNumber(m_DictIndex); 
      WordInfo.m_WordIndex.m_DictIndex.SetFirstLetterUpperCase(FirstLetterUpperCase); 
      WordInfo.m_WordIndex.m_IDForm = IDForm; 
      WordInfo.m_MorphoTypeInfo.m_IDType = IDType;
      WordInfo.m_MorphoTypeInfo.m_MorphoInfo = MorphoInfo;
   }
};
///////////////////////////////////////////////////////////////////////////////   
   
/** 
   �������� � �������� ���������� �� ����. ����������:
      0  DictionaryIndex     : INT32   - COMMON KEY-FIELD
      1  FormLower           : WSTRING - COMMON KEY-FIELD
      2  Form                : WSTRING - SEARCH IS NOT AVAILABLE
      3  IDType              : INT32   - DATA (search is not available)
      4  IDForm              : INT32   - DATA (search is not available)

   ����� �������������� �� ���� FormLower, �� ������������ �������� �� Form
   ��� ���� ���������� ����� ��� ������� ������ ��� ������ ���� ��������� � ������� ��������.

   IDForm � ������� ���������� �� ���� IDForm �� MorphoTypes � ��� ������ � MorphoTypes IDForm ������ ����� 0 
*/

class CAbbreviationsDictionaryBase: public CAbbreviationsBasic
{
   typedef std::list<TWordInfo> TWIList;
   typedef CMorphoTypesSearchCreateManager::TPointer TMorphoTypesSearchPointer;

private:
    CTablePtr m_pTable;
    TMorphoTypesSearchPointer m_pMorphoTypesSearch;

public:
   CAbbreviationsDictionaryBase(): m_pMorphoTypesSearch(0) {}
     
   //�������������� ���� � ����������� �������
   /// pMorphoDataBase, pAbbreviationsDataBase - ������������ ��
	/// TableName  -   ��� �������   
	/// DictionaryIndex - �����c ������� ��� ������������� � TDictionaryIndex
	void Init(
		DBMS::IDataBase *pMorphoDataBase, DBMS::IDataBase *pAbbreviationsDataBase, const TCHAR *TableName, 
		TDictNumber DictionaryIndex 
	);
	
   /// ������������� ������ ���������� ����� Init ��� ������
   bool Reload() { /*������ ������ �� ����*/ return true; }

	///////////////////////////////////////////////////////////////////////////////
	//IMorphologyAnalyser

	/// �������� ������� ����� � �������
	bool IsExistWord(/*in*/const wchar_t* wcWord);
	
	/// ����� ������ ��������������� ���������� �� ����� 
	bool GetWordInfo/*ByWord*/(
		/*in*/const wchar_t* wcWord,
      /*in*/const wchar_t* wcWordOriginalCase,
      /*in*/bool IsFirstLetterUpperCase,
		/*out*/std::list<TWordInfo>* p_l_WordInfo
	);

	/// ����� ������ ��������������� ���������� �� ������� �����
	bool GetWordInfo/*ByWordIndex*/(
		/*in*/SWordIndex* pWordIndex, 
		/*out*/SWordInfo* pWordInfo
	);


	/// ����� ����� �� ��� ������� 
	/// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
    bool GetWord(
		/*in*/SWordIndex* pWordIndex,
		/*out*/wchar_t* wcWord
	);

	/// ����� ��������� ����� �� ������� ������
    bool GetWordFormsByIDSource(
		/*in*/TDictionaryIndex* pDictionaryIndex,
		/*out*/std::list<TWordInfo>* p_l_WordInfo
	);
};

/**
  �������� ��� �� ��� � CAbbreviationsDictionaryBase, �� ��� ������������� ��������� 
  ��� ������ �� ������� � ������.

  ����� ����������� ������� ��������� � ������������� �����
*/
class CAbbreviationsDictionaryBaseMemory: public CAbbreviationsBasic
{
   typedef std::list<TWordInfo> TWIList;
   typedef CMorphoTypesSearchCreateManager::TPointer TMorphoTypesSearchPointer;

   //������ � �������
   struct SRecord
   {
      INT32 IDSource;
      std::wstring FormLower;
      std::wstring Form;           
      INT32  IDType;             
      INT32  IDForm; 
   };

   //������������� � ������ ������� ��� ������ �� FormLower � DictionaryIndex
   typedef std::unordered_multimap< std::wstring, SRecord > TFormLowerToRecord;
   typedef std::unordered_multimap< INT32, SRecord * > TDictionaryIndexToRecordPtr;
   //typedef std::multimap< std::wstring, SRecord > TFormLowerToRecord;
   //typedef std::multimap< INT32, SRecord * > TDictionaryIndexToRecordPtr;

   typedef std::pair<TFormLowerToRecord::const_iterator, TFormLowerToRecord::const_iterator> TFormToRecordIterPair;
   typedef std::pair<TDictionaryIndexToRecordPtr::const_iterator, TDictionaryIndexToRecordPtr::const_iterator> TDIToRecordPtrIterPair;

private:
   TMorphoTypesSearchPointer m_pMorphoTypesSearch;
   TFormLowerToRecord m_FormLowerToRecord;
   TDictionaryIndexToRecordPtr m_DictionaryIndexToRecordPtr;

   DBMS::IDataBase *m_pMorphoDataBase;
   DBMS::IDataBase *m_pAbbreviationsDataBase;
   std::basic_string<TCHAR> m_TableName;

public:
   CAbbreviationsDictionaryBaseMemory(): m_pMorphoTypesSearch(0), m_pMorphoDataBase(0), m_pAbbreviationsDataBase(0) {}

   /// �������������� ���� � ����������� ������� � ��������� ������
   /// pMorphoDataBase, pAbbreviationsDataBase - ������������ ��
   /// TableName  -   ��� �������   
   /// DictionaryIndex - �����c ������� ��� ������������� � TDictionaryIndex
   bool Init(
      DBMS::IDataBase *pMorphoDataBase, DBMS::IDataBase *pAbbreviationsDataBase, const TCHAR *TableName, 
      TDictNumber DictionaryIndex 
      );

   /// ������������� ������ ���������� ����� Init ��� ������
   bool Reload();

   ///////////////////////////////////////////////////////////////////////////////
   //IMorphologyAnalyser

   /// �������� ������� ����� � �������
   bool IsExistWord(/*in*/const wchar_t* wcWord) const;

   /// ����� ������ ��������������� ���������� �� ����� 
   bool GetWordInfo/*ByWord*/(
      /*in*/const wchar_t* wcWord, 
      /*in*/const wchar_t* wcWordOriginalCase,
      /*in*/bool IsFirstLetterUpperCase,
      /*out*/TWIList* p_l_WordInfo
   ) const;

   /// ����� ������ ��������������� ���������� �� ������� �����
   bool GetWordInfo/*ByWordIndex*/(
      /*in*/SWordIndex* pWordIndex, 
      /*out*/SWordInfo* pWordInfo
   ) const;


   /// ����� ����� �� ��� ������� 
   /// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
   bool GetWord(
      /*in*/SWordIndex* pWordIndex,
      /*out*/wchar_t* wcWord
   ) const;

   /// ����� ��������� ����� �� ������� ������
   bool GetWordFormsByIDSource(
      /*in*/TDictionaryIndex* pDictionaryIndex,
      /*out*/TWIList* p_l_WordInfo
   ) const;
};


///////////////////////////////////////////////////////////////////////////////
// ���������� ��������� IBasicMorphologyAnalyser ��� ������ � ���� ��������
// CAbbreviationsDictionaryBase
///////////////////////////////////////////////////////////////////////////////
class CAbbreviationsDictionary: public Detail::IBasicMorphologyAnalyser
{
   //typedef CObjectsSelector<TDictNumber, CAbbreviationsDictionaryBase> TDictNumberToAbbreviation;
   typedef AssocVector<TDictNumber, CAbbreviationsDictionaryBaseMemoryManager::TPointer> TDictNumberToAbbreviation;

private:
   TDictNumberToAbbreviation m_DictNumberToAbbreviation;

private:
   CAbbreviationsDictionaryBaseMemoryManager::TConstPointer Get( TDictNumber DictNumber ) const 
   {
      //CAbbreviationsDictionaryBase *pADB = m_DictNumberToAbbreviation.Get( DictNumber );

      //if( pADB == 0 )
      //   SS_THROW( L"������ ��� ������ ������������������� DictionaryNumber" );

      //return pADB;
      TDictNumberToAbbreviation::const_iterator I = m_DictNumberToAbbreviation.find(DictNumber);

      if( I == m_DictNumberToAbbreviation.end() )
         SS_THROW( L"������ ��� ������ ������������������� DictionaryNumber" );

      return  I->second;
   }

public:
   struct SInitStruct
   {
      template<class Iterator>
      struct SSelectDictNumber: public SelectorHelper<Iterator, const TDictNumber>
      {
         reference operator ()( origin_iterator_reference V ) const { return V.DictNumber; }
      };

      TDictNumber DictNumber;      //����� �������
      std::wstring TableName;      //��������������� ����� �������
   };

public:
   //������ � �������������� ���������� ������� CAbbreviationsDictionary
   //�������������� ���� � ����������� �������
   /// pMorphoDataBase, pAbbreviationsDataBase - ������������ ��
   /// [First, Last) - �������� ���������� ��� ��������� SInitStruct
   template<class InputIterator>
   void Init(
      DBMS::IDataBase *pMorphoDataBase, DBMS::IDataBase *pAbbreviationsDataBase, 
      InputIterator First, InputIterator Last
   )
   {
      //TDictNumberToAbbreviation::TAutoPtr AutoPtr;

      m_DictNumberToAbbreviation.clear();

      for( ; First != Last; ++First )
      {
         //AutoPtr.reset( new CAbbreviationsDictionaryBase() );

         //AutoPtr->Init(
         //   pMorphoDataBase,
         //   pAbbreviationsDataBase, 
         //   First->TableName.c_str(), 
         //   First->DictNumber 
         //   );

         //if( !m_DictNumberToAbbreviation.Add(First->DictNumber, AutoPtr) )
         //{
         //   m_DictNumberToAbbreviation.Clear();
         //   SS_THROW( L"������ CAbbreviationsDictionary::Init" );
         //}

         m_DictNumberToAbbreviation.insert( TDictNumberToAbbreviation::value_type
            ( 
               First->DictNumber,
               CAbbreviationsDictionaryBaseMemoryManager::Create()->Construct(
                  pMorphoDataBase,
                  pAbbreviationsDataBase, 
                  First->TableName.c_str(), 
                  First->DictNumber 
               )
            )
         );
      }
   }

   ///////////////////////////////////////////////////////////////////////////////
   //IMorphologyAnalyser

   /// ������������� ������ �� ��
   bool Reload();


   /// �������� ������� ����� � �������
   bool IsExistWord(/*in*/const wchar_t* wcWord);

   /// ����� ������ ��������������� ���������� �� ����� 
   bool GetWordInfo/*ByWord*/(
      /*in*/const wchar_t* wcWord,
      /*in*/const wchar_t* wcWordOriginalCase,
      /*in*/bool IsFirstLetterUpperCase,
      /*out*/std::list<TWordInfo>* p_l_WordInfo
      );

   /// ����� ������ ��������������� ���������� �� ������� �����
   bool GetWordInfo/*ByWordIndex*/(
      /*in*/SWordIndex* pWordIndex, 
      /*out*/SWordInfo* pWordInfo
      );


   /// ����� ����� �� ��� ������� 
   /// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
   bool GetWord(
      /*in*/SWordIndex* pWordIndex,
      /*out*/wchar_t* wcWord
      );

   /// ����� ������ ����� ����� (����� ����� ��� ���������) �� ��� ������� 
   /// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
   bool GetWordSource(
      /*in*/const TDictionaryIndex &DictIndex,
      /*out*/wchar_t* wcWordSource
   );									   

   /// ����� ��������� ����� �� ������� ������
   bool GetWordFormsByIDSource(
      /*in*/TDictionaryIndex* pDictionaryIndex,
      /*out*/std::list<TWordInfo>* p_l_WordInfo
   );
};

} //namespace Dictionary
} //namespace SS
