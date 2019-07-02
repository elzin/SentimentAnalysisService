#pragma once

namespace SS{ 
namespace Dictionary{


///////////////////////////////////////////////////////////////////////////////
// ����� ���������� ��� ������� � ���� (������������ � �������) � ������������� 
// ��� ������ ���������� IMorphologyAnalyser ������ � ��� ��� � ������ ������.
// �������������� ������� ������������ ������ (������� ���� ���� �������� � ��������
// ������������ �����), ��������� �������� ������� � ������� ��������� ����� 
// ������� ��������� ��� ������ (����� ���������� ������ � ���)
///////////////////////////////////////////////////////////////////////////////
class CMALanguagesManager: public IMorphologyAnalyser, public ILoad
{
public: 
   typedef unsigned int TIDSource;
   typedef std::list<SS::Dictionary::Types::TWordInfo> TWIList;

   //������������� ��� ������
   struct SLanguage 
   {      
      //���������������� ������ ��� CSmartDictionary
      struct SSmartDictionaryInitData
      {
         std::wstring DBPath; 
         
         enum eDictNumbers
         {
            EDNNominal,
            EDNProper,
            EDNNewWords,

            EDNCOUNT
         };

         TDictNumber DictionaryIndexes[EDNCOUNT];
         CSmartDictionaryAdapter::TDictionaryTypes DictionaryTypes; 
         int MinRecognizableWordLen;
      };

      //���������������� ������ ��� CAbbreviationsDictionary
      struct CAbbreviationsInitData
      {
         DBMS::IDataBase *pAbbreviationsDataBase; 

         enum eDictNumbers
         {
            SingleNominal,
            SingleProper,
            Multiple,
            CombinatorySingle,

            EDNCOUNT
         };

         CAbbreviationsDictionary::SInitStruct InitStruct[EDNCOUNT]; 
      };

      //����� �������� �������������� � CMorphoTypesSearch, ��� CMorphoTypesSearch ���������� ��� ������ CSmartDictionary
      struct CMorphoTypesSearcInitData
      {
         const TDictNumber *First;
         const TDictNumber *Last;
      };

      //����� ������ � ���� ������ ��� ������������� ��������� ��� ��� ����� ����
      struct CNdxInitData
      {
         std::wstring TableName;
      };

   public:
      //����� ����������������� ������
      DBMS::IDataBase *pMorphoDataBase;

      //������ ��� ��������� �������
      SSmartDictionaryInitData SmartDictionaryInitData;
      CAbbreviationsInitData AbbreviationsInitData;
      CMorphoTypesSearcInitData MorphoTypesSearcInitData;
      CNdxInitData NdxInitData;
   };

private:
   typedef CObjectsSelectorMultiObject<TDictNumber, Detail::IBasicMorphologyAnalyser> TDictNumberToMorphoAnal;
   typedef AssocVector<TDictNumber, CSmartDictionary *> TDictNumberToSmartDictionary;
   typedef CSymbolCharacteristicCreateManager::TCreateType::TItem TDictsCharacteristic;
   
   struct SLangBasedDicts
   {
      CSmartDictionaryAdapter *pSmartAdpter;
      CSmartDictionary *pSmart;
      CAbbreviationsDictionary *pAbbreviations;
   };

   //���������� �� �������� �����
   struct SCurWordInfo
   {  
      //������� ������������� ��������
      const Detail::TConstData::TChar2Char *m_pPreSearchTransform;
            
      //����� � ������� �������������� ������� ���������� � ������� ��������
      TCHAR LowerBuf[Constants::MAX_CHARS_IN_WORD];
      
      //����� ������
      size_t Len;

      bool IsFirstLetterUpperCase; //������� ������� ������ �����

   public:
      SCurWordInfo(): m_pPreSearchTransform(0), IsFirstLetterUpperCase(false), Len(0) 
	  {
		  memset(LowerBuf, 0, sizeof(TCHAR) * Constants::MAX_CHARS_IN_WORD);
	  }

      //��������� ������ 
      void Fill( const TCHAR *wcWord )
      {
         Detail::PrepareWordForSearch( wcWord, LowerBuf, Len, IsFirstLetterUpperCase );
      }

      void Fill_NEW( const TCHAR *wcWord )
      {
         // ����� ����� Fill �������� ������ �� �������� ������� ��� �������, ��� ��� 
         // ������������� ��� ���� ���������������
         APL_ASSERT_PTR( m_pPreSearchTransform );
         
         TCHAR *pBuf = LowerBuf;
         Detail::TConstData::TChar2Char::const_iterator I/* = m_pPreSearchTransform->end()*/;

         for( ; *wcWord; ++wcWord )
         {
            APL_ASSERT( pBuf - LowerBuf < Constants::MAX_CHARS_IN_WORD );
            
            I = m_pPreSearchTransform->find( *wcWord );

            *(pBuf++) = I == m_pPreSearchTransform->end() ? *wcWord : I->second;
         }
         
         *pBuf = _T('\0');
         Len = pBuf - LowerBuf;
      }

   };

   struct TDictionaryIndexCmp: public std::binary_function<TWordInfo, TWordInfo, bool>
   {
      bool operator()( const TWordInfo &WI1, const TWordInfo &WI2 ) const
      {
         APL_ASSERT( WI1.size() == 1 && WI2.size() );

         return 
            WI1.front().m_WordIndex.m_DictIndex.GetDictionaryIndexWithoutFlags() < 
            WI2.front().m_WordIndex.m_DictIndex.GetDictionaryIndexWithoutFlags();
      }
   };

   struct TIDFormCmp: public std::binary_function<TWordInfo, TWordInfo, bool>
   {
      bool operator()( const TWordInfo &WI1, const TWordInfo &WI2 ) const
      {
         APL_ASSERT( WI1.size() == 1 && WI2.size() );

         return 
            WI1.front().m_WordIndex.m_IDForm < 
            WI2.front().m_WordIndex.m_IDForm;
      }
   };

private:
   TDictNumberToMorphoAnal m_DictNumberToMorphoAnal;           //������ ��� ������ �� ��������� �������� 
   TDictNumberToSmartDictionary m_DictNumberToSmartDictionary; //���������� ��������� ������ �������� ����������� ������� SmartDictionary
   Detail::IBasicMorphologyAnalyser *m_ObjectIDToMorphoAnal[InitData::ObjectID::DICTS_COUNT];
   SLangBasedDicts m_LangToLangBasedDicts[InitData::Languages::COUNT];                  
   CSymbolCharacteristicCreateManager::TConstPointer m_pSymbolCharacteristic; 
   CConstDataCreateManager::TConstPointer m_pConstData; 
   CTablePtr m_IndexTables[InitData::Languages::COUNT];                                  //��������� ������� ����� ����
   std::wstring m_IntdexTableNames[InitData::Languages::COUNT];                          //����� ��������� ������
   Detail::TSharedObjectMutex m_SharedMutex;
   
   mutable SCurWordInfo m_CurWordInfo;
   IOneRoot *m_pOneRoot;
   IBlackBoxTextStorage *m_pBlackBoxTextStorage;
   IAMConverterMorpho *m_pAMConverter;
   bool m_UseNewWordsTables;    //������������ ������� ����� ����

   TStandartDeterminationWordCheck m_StandartDeterminationWordCheck;
   TOnlyNounDeterminationWordCheck m_OnlyNounDeterminationWordCheck;
   
   TCompoundWordAnalysis m_CompoundWordAnalysis;

private:
   //����� �� TDictNumber ������������������� ������ IMorphologyAnalyser.
   //���� ������ ������ ��� �������� ����������.
   TDictNumberToMorphoAnal::TResultPair GetMorphologyAnalyserFormDictNumber( TDictNumber DictNumber )
   {
      TDictNumberToMorphoAnal::TResultPair ResultPair(m_DictNumberToMorphoAnal.Get(DictNumber) );

      return ResultPair;
   }
   
   //���������� p_l_WordInfo ���������������� ���������� �� ����������� ��������.
   //�� ������� p_l_WordInfo � ������������ ��� ���� p_l_WordInfo->empty() �� ���������� 
   //������ ���������� ��������, ������� ����� ������ ����� ����� � �������� ������� � ������� �����������
   bool FillVirtualPartInSearch(    
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic
   );


   //���������� p_l_WordInfo ���������������� ���������� �� ��������� ������� � ������� �����������.
   //�� ������� p_l_WordInfo.
   // UseSmartDictionary - ������ � �������� �������
   // UseAbbreviationsDictionary - ������ � ������� �����������
   // UseMainDictionary - ��� ������ � �������� ������� ������������ ��� ������ ���������� ������������� � �����������
   // UseNewWordsDictionary - ��� ������ � �������� ������� ������������ ��� ������ ���������� ����� ����
   // FirstExistLang - ������ ����� � ������� ����������� ��� ����� �� wcWord ��� Undefined ���� ���� ����������
   template<bool UseSmartDictionary, bool UseAbbreviationsDictionary>
   void FillBaseDictionaryPart(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic,
      bool UseMainDictionary, bool UseNewWordsDictionary,
      InitData::Languages::eLanguages &FirstExistLang
   );


   //����������� ����� ���� ����������� �� ����� FirstExistLang
   //DWC - ��������� ��� �������� �������� �� �������� �������� ��� ���
   bool CMALanguagesManager::FillDeterminatonWordsPart(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const CSmartDictionary::IDeterminationWordCheck &DWC,
      InitData::Languages::eLanguages FirstExistLang
   );

   //���������� GetWordInfo ��� eFindZone = efzNewWord
   bool GetWordInfo_NewWord(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic 
   );

   //���������� GetWordInfo ��� eFindZone = efzBaseDictionary
   bool GetWordInfo_BaseDictionary(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic
   );

   //���������� GetWordInfo ��� eFindZone = efzAbbreviation
   bool GetWordInfo_Abbreviation(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic
   );

   //���������� GetWordInfo ��� eFindZone = efzOnlySearch
   //UseCompoundSearch - ������������ �� ����������� ��������� ���� ��� ������
   template<bool UseCompoundSearch>
   bool GetWordInfo_OnlySearch(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic
   );

   //���������� GetWordInfo ��� eFindZone = efzFullAddNewWords
   //DWC - ��������� ��� �������� �������� �� �������� �������� ��� ���
   //AddEmptyData - ��������� �� ������ �������� � �����, ���� AddEmptyData == true ����� ������ ���������� �������
   //UseCompoundSearch - ������������ �� ����������� ��������� ���� ��� ������
   template<bool UseCompoundSearch>
   bool GetWordInfo_FullAddNewWords(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const CSmartDictionary::IDeterminationWordCheck &DWC,
      bool IsAddEmptyData,
      const TDictsCharacteristic &DictsCharacteristic
   );

   //���������� GetWordInfo ��� ������� ����� ����� �� ������������ � ������ 
   //����������� ������ ������. �������� �����
   bool GetWordInfo_FullAddEmptyWords(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic
      );

   //���������� GetWordInfo ��� eFindZone = efzBaseAndbbreviation
   bool GetWordInfo_BaseAndAbbreviation(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList* p_l_WordInfo,
      const TDictsCharacteristic &DictsCharacteristic
   );

   //�������� ���� ������� � WordInfoList, ����������� �� wcWord, DI � WI
   static void AddToList( 
      const wchar_t* wcWord,
      const TDictionaryIndex &DI,
      const CSmartDictionary::SHypothesisInfo::WordInfo &WI,
      TWIList &WordInfoList 
   )
   {
      WordInfoList.push_back( CSmartDictionary::TWIList::value_type() );
      WordInfoList.back().push_back( SWordInfo() /*TWIList::value_type::value_type()*/ );
      SWordInfo &WordInfo = WordInfoList.back().back();

      WordInfo.m_wWord = wcWord;
      WordInfo.m_SpecialMorpho = WI.m_MorphoType.m_SpecialMorpho;
      WordInfo.m_WordIndex.m_DictIndex = DI;
      WordInfo.m_WordIndex.m_IDForm = WI.m_MorphoType.m_IDForm;
      WordInfo.m_MorphoTypeInfo = WI.m_MorphoType.m_MorphoTypeInfo;
   }

   //�������� � pSmartDictionary ����� ����� � ������ ����������������. ����� �������� ������ 
   //��������������� � ����� � WordInfoList
   static void AddEmptyData(
      CSmartDictionary *pSmartDictionary,
      const wchar_t* wcWord,
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      TWIList &WordInfoList
   )
   {
      APL_ASSERT_PTR( pSmartDictionary );

      TDictionaryIndex DI;
      CSmartDictionary::SHypothesisInfo::WordInfo WI;

      WI.m_EndingLen = 0;
      WI.m_MorphoType.m_IDEnding = 0;
      WI.m_MorphoType.m_IDForm = 0;
      WI.m_MorphoType.m_MorphoTypeInfo.m_IDType = 0;
      WI.m_MorphoType.m_MorphoTypeInfo.m_MorphoInfo = 0;
      WI.m_MorphoType.m_SpecialMorpho = 0;

      pSmartDictionary->AddNewWord( wcWord, wcWordLower, WI.m_MorphoType.m_MorphoTypeInfo.m_IDType, WI.m_EndingLen, DI );
      DI.SetFirstLetterUpperCase(IsFirstLetterUpperCase);
      AddToList( wcWord, DI, WI, WordInfoList );
   };

   //���������� ��� ��������� ��������� ������� ����� ���� � ��������, �� �� ��������� 
   void SetAnalyseParamsNoLock(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);


   //��������� ������ WIList ������������ �������
   //��� ��� ��� ���� IDSource �� WIList ������������ ����� ���������� ������������ ����, ����� ������������
   //��������������� ���������� �� ��� (��� IDForm = 0) � ����������� � ����� WIList
   void AppendOneRoot( TWIList &WIList );

   //��������� ������ WIList ����������� �����������
   //��� ������� ����� ��������� ���������� �� �� �������� �����������
   void AppendUndepDict( TWIList &WIList );

   //�������� �������� ������ ����� ����
   void CheckNewWordsTables()
   {
      if( m_UseNewWordsTables )
         for( size_t i = 0; i < InitData::Languages::COUNT; ++i )
            if( !m_IndexTables[i].IsOpen() )
               SS_THROW(L"�� ���������������� ������� ����� ����, ��������� ������� ������ ������ IBaseManager::OpenBase");
   }

   //������ �������� ������ ��� ������� GetWordInfo, ����� ���� ��� �� ��������� m_SharedMutex, 
   //�� ��������� m_CurWordInfo � �� �������� CheckNewWordsTables();
   //DWC - ��������� ��� �������� �������� �� �������� �������� ��� ���
   //AddEmptyData - ��������� �� ������ �������� � �����, ���� AddEmptyData == true ����� ������ ���������� �������
   //DictsCharacteristic - ������� �����������, �������������� �����.
   bool GetWordInfoImpl(
      /*in*/const wchar_t* wcWord, 
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      /*out*/TWIList* p_l_WordInfo,
      /*in*/EFindZone eFindZone,
      const CSmartDictionary::IDeterminationWordCheck &DWC,
      bool IsAddEmptyData,
      const TDictsCharacteristic &DictsCharacteristic
      );

   //��������� ���������� ����� ��������������� �� 's
   //�����: ������� �� ���������� �����
   bool GenetiveCompoundWord(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      size_t WordLen,
      IUnit * pUnit,
      EFindZone eFindZone,
      const TDictsCharacteristic &DictsCharacteristic
   );

   //��������� ���������� ����� ��������������� �� n't
   //�����: ������� �� ���������� �����
   bool NegateCompoundWord(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      size_t WordLen,
      IUnit * pUnit
   );

   
   //��������� ���������� ����� ����������� ����� �����
   //�����: ������� �� ���������� �����
   bool HyphenCompoundWord(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower,
      bool IsFirstLetterUpperCase,
      size_t WordLen,
      IUnit * pUnit,
      EFindZone eFindZone,
      const TDictsCharacteristic &DictsCharacteristic
   );

   ///������������ eFindZone ��� ������ ������ �����
   EFindZone CorrectFindZoneForPartSearch( EFindZone eFindZone ) const
   {
      switch(eFindZone)
      {
      case efzFullAddNewWordsCompound:
         return efzFullAddNewWords;

      default:
         return eFindZone;
      }
   }

public:
   CMALanguagesManager();
   
   //������������������� �������
   //[First, Last) - ��������� �� ��������� SLanguage
   template< class InputIterator >
   void Init( InputIterator First, InputIterator Last, IAMConverterMorpho *pAMConverter, IOneRoot *pOneRoot, IBlackBoxTextStorage *pBlackBoxTextStorage );
   
   
   /// �������� ������� ����� � �������
   /*
      �������� ������� ����� �� ���� ��������, ����� ����� ���� � �����������
   */
   bool IsExistWord(/*in*/const wchar_t* wcWord);
   
   /// ����� ������ ��������������� ���������� �� ����� 
   bool GetWordInfo/*ByWord*/(
      /*in*/const wchar_t* wcWord, 
      /*out*/TWIList* p_l_WordInfo,
      /*in*/EFindZone eFindZone = efzFullAddNewWords
   );

   bool GetWordInfo/*ByWord*/(	
      /*in*/const wchar_t* wcWord, 
      /*in out*/SS::Interface::Core::BlackBox::IUnit * pUnit,
      /*in*/EFindZone eFindZone = efzFullAddNewWords
   );

   /// ����� ������ ��������������� ���������� �� ������� �����
   bool GetWordInfo/*ByWordIndex*/(
      /*in*/SS::Dictionary::Types::SWordIndex* pWordIndex, 
      /*out*/SS::Dictionary::Types::SWordInfo* pWordInfo);
   
   /// ����� ����� �� ��� ������� 
   bool GetWord(
      /*in*/SS::Dictionary::Types::SWordIndex* pWordIndex,
      /*out*/wchar_t* wcWord
   );

   /// ����� ������ ����� ����� (����� ����� ��� ���������) �� ��� ������� 
   bool GetWordSource(
      /*in*/const SS::Dictionary::Types::TDictionaryIndex &DictIndex,
      /*out*/wchar_t* wcWordSource
   );

   /// ����� ��������� ����� �� ������� ������
   bool GetWordFormsByIDSource(
      /*in*/SS::Dictionary::Types::TDictionaryIndex* pDictionaryIndex,
      /*out*/TWIList* p_l_WordInfo);

   /// ���������� ��������������� ���������� �� ���� ����������������
   /*
         ���� �� ������ ����� ���������� �� ����������� oIDForm, �� �� �������� � ����� �� IDForm == 0
   */
   void GetMorphoInfoByIDType(
         /*in*/SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber eDictionariesNumber,
         /*in*/SS::Dictionary::Types::TIDType oIDType, 
         /*in*/SS::Dictionary::Types::TIDForm oIDForm, 
         /*out*/SS::Dictionary::Types::TMorphoInfo* pMorphoInfo, 
         /*out*/SS::Dictionary::Types::TSpecialMorpho* pSpecialMorpho
         );
         
   /// �������� ���������������� ������� � ���, ���������� ���������� � ������� ���������� ������
   void NextText();

   //���������� ��� ��������� ��������� ������� ����� ���� � ��������
   void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);

   //������� ������������ ������ ��� �������
   CSmartDictionary *GetSmartDictionary( InitData::Languages::eLanguages Lang )
   { 
      APL_ASSERT( m_pSymbolCharacteristic != 0 && !m_DictNumberToMorphoAnal.Empty() );
      return m_LangToLangBasedDicts[Lang].pSmart; 
   }

   IAMConverterMorpho *GetAMConverter() const 
   { 
      APL_ASSERT( m_pSymbolCharacteristic != 0 && !m_DictNumberToMorphoAnal.Empty() );
      return m_LangToLangBasedDicts[InitData::Languages::English].pSmart->GetAMConverter(); 
   }
      
   SCurWordInfo &GetCurWordInfo()const
   {
      return m_CurWordInfo;
   }
   ///////////////////////////////////////////////////////////////////////////////
   // ILoad
   bool ToBinary(); 
   bool ReLoad();
   bool Load();
   bool Clear();


   ///////////////////////////////////////////////////////////////////////////////
    
   //������� ������� ����� ���� � ������� SetAnalyseParams(GetAnalyseParams())
   void OpenNewWordsTables( DBMS::IDataBase *pDB );

   //������� ������� ����� ���� � ������� SetAnalyseParams(GetAnalyseParams())
   void CloseNewWordsTables();

   ///////////////////////////////////////////////////////////////////////////////
   //�������� �������

   //������ ����������� ���������� ����. ��� ����� ��� ����� �����
   bool GetDeterminationWordInfo(
      const wchar_t* wcWord, 
      CSmartDictionary::SHypothesisInfo &HypothesisInfo
   );

   ~CMALanguagesManager();
};

} //namespace Dictionary
} //namespace SS
