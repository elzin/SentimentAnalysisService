#pragma once

namespace SS{ 
namespace Dictionary{

/** �������� �� ��������� ��� �����������, ��� �������������, ����� ���� � ����������.
	 ������������� ������ �� ������ ��������� ���������� � �����.
    ����� �������� ��� �������� �������.

    �������� � ������������ ����� ����������� �������� ���������. � ���������� ��. ����
*/

//struct SSDStatistic
//{
//   static unsigned TotalFillWordInfo;
//   static unsigned SuccessfulFillWordInfo;
//   static unsigned TotalFillHypothesisInfo;
//   static unsigned SuccessfulFillHypothesisInfo;
//};

	class CSmartDictionary: 
		//public NonCopyable,
		//�� ������� ������ ����������� ������� ���������� ���� �������� ������ �� ���� �������� ��� ������ ������ ��������� LockedPtr
		//� ���������� ���������� ������������� �������� ���������� �� ������ � �� ������ ������ ����������� � ������� ��������� �������,
		//�.�. ������ ������������� �� ������� ������ ���������� ����� ��������� ������, ���� ���� �������� �� �������.
		public NoLockable<CSmartDictionary, SCriticalSectionImplStategy, CURRENT_THREAD_DEBUG_INFO>
	{
	public:
		typedef std::vector<SPartOfWord> TPOFVector;
		typedef std::list<SMorphoType> TMTList;
		typedef std::list<TWordInfo> TWIList;
		typedef std::basic_string<TCHAR> TString;
		typedef std::vector<SHypothesisInfo> THIVector;

		typedef std::vector<int> TWordBounds;

		// ���������� � ���������, �.�. ������������ ����� ������ �� ������ ������� ��� ���� � ��������
		struct SHypothesisInfo 
		{
			//���������� ��������� �������� � �����
			int  m_ConcordanceChars;  

			struct WordInfo
			{
				SMorphoType m_MorphoType;           //��������������� ����������
				TDictionaryIndex m_DictIndex;       //������ � �������
				int m_EndingLen;                    //����� ��������� � �����, ������� �������� � ����� �������� ��������� 
			};

			typedef std::list<WordInfo> TFormsInfoList;

			//������ ���� ��������� ���� � ������� ���������� ��������� � ����� ������� =  m_ConcordanceChars
			TFormsInfoList m_FormsInfoList; 

		public:

			bool Empty() const { return m_FormsInfoList.empty(); }
			SHypothesisInfo(): m_ConcordanceChars(0) {}
			void Clear() { m_FormsInfoList.clear(); m_ConcordanceChars = 0; }

			//������������� �� IDType � �������� ������ ���������� IDType:m_EndingLen
			void UniqueIDTypeEndingLen();

			//������������� �� IDType � �� IDForm
			void SortIDTypeIDForm();

			//������������� �� IDType � �� IDForm � �������� ������ ���������� IDType:IDForm
			void UniqueIDTypeIDForm();

		};

		//��������, �������� �� �������� �������� ��� ���
		struct IDeterminationWordCheck
		{
			virtual ~IDeterminationWordCheck() {}

			//������ �������� ����� ��� ��� ������� � ������ ��� ���������� ��������� ����������� ���� ��������, � ������ ���� ��� ������� ���������  
			//true �������� � ������ ������� �� �����
			//wcWord - ����� ��� �������� ������������ ����� �������, � ������������ ��������
			//wcWordLower - ����� ��� �������� ������������ ����� �������, � ���������� ��������
			//DictionaryIndex, MorphoInfo, SpecialMorpho - �������������� ��������� ��������
			virtual bool IsDeterminationWord( const wchar_t* wcWord, const wchar_t* wcWordLower, bool IsFirstLetterUpperCase, TDictNumber DictionaryIndex, TMorphoInfo MorphoInfo, TSpecialMorpho SpecialMorpho, IAMConverterMorpho *pAMConverter ) const = 0;
		};

	public:
		typedef CMorphoTypesSearchCreateManager::TPointer TMorphoTypesSearchPtr;
		typedef CPartOfWordsSearchCreateManager::TPointer TPartOfWordsSearchPtr;
		typedef CSourceToTypeCreateManager::TPointer TSourceToTypePtr;

		typedef CMorphoTypesSearchCreateManager::TConstPointer TMorphoTypesSearchConstPtr;
		typedef CPartOfWordsSearchCreateManager::TConstPointer TPartOfWordsSearchConstPtr;
		typedef CSourceToTypeCreateManager::TConstPointer TSourceToTypeConstPtr;

	protected:
		mutable TMorphoTypesSearchPtr m_pMorphoTypesSearch;   //����� ��������� ����������
		TPartOfWordsSearchPtr m_pNominalWS;						   //����� �������������
		TPartOfWordsSearchPtr m_pProperWS;						   //����� ����������� 
		TPartOfWordsSearchPtr m_pEndingWS;						   //���������
		TSourceToTypePtr m_pNominalSourceToMorpho;			   //������������� -> MorphoType
		TSourceToTypePtr m_pProperSourceToMorpho;			      //����������� -> MorphoType
		Detail::CNewWordsCache m_NewWords;

		//������������ ��� ������ ��� ������
		mutable TPOFVector m_EndingVecBuf;
		mutable TPOFVector m_SourceVecBuf; 
		mutable THIVector m_HIVectorBuf;

		//������� ��������
		TDictNumber m_NominalDictionaryIndex;
		TDictNumber m_ProperDictionaryIndex;
		TDictNumber m_NewWordsDictionaryIndex;

		IAMConverterMorpho *m_pAMConverter;

		int m_MinRecognizableWordLen;

	private:
		CTablePtr m_pNominalDT;
		CTablePtr m_pProperDT;
		CTablePtr m_pEndingDT;

	private:
		static const wchar_t * const szNominalTable;
		static const wchar_t * const szProperTable;
		static const wchar_t * const szEndingTable;
		static const wchar_t * const szNominalSourceToMorphoTable;
		static const wchar_t * const szProperSourceToMorphoTable;
		static const wchar_t * const szMorphoTypesTable;

	//��������� ���������� ID ��� ����� ���� (���������� ��� ���������� ����������� ����������� �������� - ����� � 0)
	private:
		volatile long m_NextSourceID;

		int GetNextSourceID()
		{
			return _InterlockedIncrement(&m_NextSourceID);
		}

	private:

		/// ��������� ��� ���� SWordInfo
		static void FillSWordInfo( 
			const SMorphoType &MorphoType, 
			const std::wstring &wcWord,
			unsigned int IDSource,
			TDictNumber DictNumber,
			SWordInfo &WordInfo,
			bool FirstLetterUpperCase,
			bool isNewWord = false
			) 
		{
			WordInfo.m_wWord = wcWord;
			WordInfo.m_SpecialMorpho = MorphoType.m_SpecialMorpho;
			WordInfo.m_WordIndex.m_DictIndex.SetId(IDSource) ; 
			WordInfo.m_WordIndex.m_DictIndex.SetDictionaryNumber(DictNumber);
			WordInfo.m_WordIndex.m_DictIndex.SetFirstLetterUpperCase(FirstLetterUpperCase); 
			WordInfo.m_WordIndex.m_IDForm = MorphoType.m_IDForm; 
			WordInfo.m_MorphoTypeInfo = MorphoType.m_MorphoTypeInfo;
			WordInfo.m_NewWord = isNewWord;
		}

		/// �� ���������� IDEnding ������� � ������� pSourseWS ��� ��������� IDSource, ��� ������� IDSource ������� IDType � pSourceToType � 
		/// ��������� ���� �� ���������� IDType - IDEnding � ������� MorphoTypes ���� ���� �� ���������� TRUE
		///
		/// IDEnding - ������ ���������
		/// pSourseWS - ������� ����� (�� ���� ��������� �����������, �� ������ CPartOfWordsSearch ����� �� ���������)
		/// pSourceToType - ����������� ������ ���� ���������������
		bool IsFindWord(
			const wchar_t* wcWord,
			const SPartOfWord  &IDEnding,
			TPartOfWordsSearchPtr pSourseWS, 
			TSourceToTypeConstPtr pSourceToType
			) const;

		/// ������ ���� ��� � IsFindWords, �� ������ ���� ����� ��������������� �� ������ ���������� ����������  
		/// ��������� ���������� � TWIList. ��� ������ �������, ��� ���������� ������ ����� ������ ������� ������ �������� 1, � �������
		/// �������� ��� ��������� ����������  ��������������� ���������� � �����.
		///
		/// wcWord - ����� ���������� � ������� ��������
		/// wcWordOriginalCase - ����� � ������������ ��������
		/// DictionaryIndex - ������ ������� ��� ��������� � SWordInfo
		/// WIList - ������ ������� � ������� � ����� ��������� ������ ��������
		/// WordInfo - ������ � ������� � ����� ��������� ������ ��������
		void FillWordInfo(
			const wchar_t* wcWord,
			const wchar_t* wcWordOriginalCase,
			bool IsFirstLetterUpperCase,
			const SPartOfWord  &IDEnding,
			TPartOfWordsSearchPtr pSourseWS, 
			TSourceToTypeConstPtr pSourceToType,
			TDictNumber DictionaryIndex,
			TWIList &WIList
			) const;

		void FillWordInfo(
			const wchar_t* wcWord,
			const wchar_t* wcWordOriginalCase,
			int SearchPos,
			bool IsFirstLetterUpperCase,
			const SPartOfWord  &IDEnding,
			TPartOfWordsSearchPtr pSourseWS, 
			TSourceToTypeConstPtr pSourceToType,
			TDictNumber DictionaryIndex,
			TWordInfo &WordInfo
			) const;


		/// �� ���������� IDEnding ������� � ������� ����� ���� ������ � ��������� ������ �� ���
		/// wcWord - ����� ���������� � ������� ��������
		/// wcWordOriginalCase - ����� � ������������ ��������
		/// WIList - ������ ������� � ������� � ����� ��������� ������ ��������
		void FillWordInfoFromNewWords(
			const wchar_t* wcWord,
			const wchar_t* wcWordOriginalCase,
			/*in*/bool IsFirstLetterUpperCase,
			const SPartOfWord  &IDEnding,
			TWIList &WIList
			) const;


		//��������� ��������������� � ����� �����������
		bool CSmartDictionary::GetWordInfoOnlyNominal(
			const wchar_t* wcWord, 
			const wchar_t* wcWordOriginalCase,
			int SearchPos,
			bool IsFirstLetterUpperCase,
			TWordInfo &WordInfo
			) const;

		/// ���������� ����� �� ��������
		/// ��� �������� ��������� IDEnding, ������� ��� ��������� ������ � ���� 
		/// �������� ��� ������� � wcWordOriginalCase, �� ������� ��� �������� ��������� ��� 
		/// ���������� ����� � ��� ������� �� ��� �������� FindSubWordsBounds
		/// WordBounds - ������ �������� ������ ����� (������ ������� ������� � ��������, �������� ������ 0)
		bool FindSubWordsBounds( 		
			const wchar_t* wcWord, 
			const wchar_t* wcWordOriginalCase,
			const SPartOfWord  &IDEnding,
			TPartOfWordsSearchPtr pSourseWS, 
			TSourceToTypeConstPtr pSourceToType,
			TDictNumber DictionaryIndex,
			TWordBounds &WordBounds
			);


	protected:
		//������������ IDEnding ��� �������� � ����� �����
		//LastCharIndex - ����� �������� ����� - 1 
		static void CorrectIDEnding( SPartOfWord &IDEnding, int LastCharIndex )
		{
			//��� ���������� ��������������� ������� � ����� ���� ��� ��������� ������ ���������
			//-1 ������� ���� ��� ������� CPartOfWordsSearch::GetByWord ����� ������ ���������
			if( IDEnding.PositionInWord == -1 )
				IDEnding.PositionInWord = LastCharIndex;
			else
				--IDEnding.PositionInWord;	
		}

		//��������� ��� ������ ���� ��������� � ������ (�.�. ������ ����� Load ��� ReLoad)
		bool CheckLoad() const
		{    
			if( m_pMorphoTypesSearch->Empty() ) return false;
			if( m_pNominalWS->Empty() ) return false;
			if( m_pProperWS->Empty() ) return false;
			if( m_pEndingWS->Empty() ) return false;
			if( m_pNominalSourceToMorpho->Empty() ) return false;
			if( m_pProperSourceToMorpho->Empty() ) return false;

			return true;

			//return  !m_pMorphoTypesSearch->Empty() && !m_pNominalWS->Empty() && !m_pProperWS->Empty() &&
			//        !m_pEndingWS->Empty() && !m_pNominalSourceToMorpho->Empty() && !m_pProperSourceToMorpho->Empty();
		}

		int GetMinRecognizableWordLen() const { return m_MinRecognizableWordLen; } 

	public:
		CSmartDictionary(): m_pAMConverter(0),
					        m_NominalDictionaryIndex(DATA_TYPE::NAMES::ednUnknown),
					        m_ProperDictionaryIndex(DATA_TYPE::NAMES::ednUnknown),
					        m_NewWordsDictionaryIndex(DATA_TYPE::NAMES::ednUnknown),
					        m_NextSourceID(0),
							m_MinRecognizableWordLen(0)
		{
		}

		virtual ~CSmartDictionary() {}

		//�������������� ���� � ����������� �������, ����� ��������� ������ �������. ����� ������ ����� �������� ������
		/// pDataBase     - ������������ ��
		/// pAMConverter  - ���������  
		/// DBPath -        ���� � �������� �� � ������ ������� ���������� 
		///                 ������������ � �������
		/// ProperDictionaryIndex, NominalDictionaryIndex, NewWordsDictionaryIndex  - ������� �������� ��� ������������� � TDictionaryIndex
		/// GetMinRecognizableWordLen - ����������� ����� �������������� �����
		virtual void Init(
			DBMS::IDataBase *pDataBase,
			IAMConverterMorpho *pAMConverter, const TCHAR *DBPath, 
			TDictNumber NominalDictionaryIndex,
			TDictNumber ProperDictionaryIndex, 
			TDictNumber NewWordsDictionaryIndex,
			int MinRecognizableWordLen
			) = 0;

		/// �������� ������� ����� � �������
		/**
		��������:
		��������� ���� ������ ���������� [������ (����������� ��� �������������) + ���������] � �������.
		������� ����� ���� ��� ���� �� ������������
		*/
		bool IsExistWord(const wchar_t* wcWord);

		/// ����� ������ ��������������� ���������� �� ����� 
		/**
		��������:
		����� ���� �� �������� ������� ����� ��������� � wcWord � ������ ���������� �� ��� �
		p_l_WordInfo

		UseMainDictionary - ������������ ��� ������ �������� ������� (������������� � �����������)
		UseNewWordsDictionary - ������������ ��� ������ ������� ����� ����
		*/
		bool GetWordInfo/*ByWord*/(
			const wchar_t* wcWord, 
			const wchar_t* wcWordOriginalCase,
			/*in*/bool IsFirstLetterUpperCase,
			std::list<TWordInfo>* p_l_WordInfo,
			bool UseMainDictionary = true, bool UseNewWordsDictionary = true
			);

		bool GetWordInfoFromHypothesis(
			const wchar_t* wcWord, 
			const wchar_t* wcWordLower,
			bool IsFirstLetterUpperCase,
			SHypothesisInfo& HypothesisInfo,
			TWIList* p_l_WordInfo
			);

		/// ����������� ��������������� ���������� � ����� �� ������� ����������� �������� �����(����).
		/// �����: ������� �� ������� ��������������� ����������� ����� 
		/// wcWord - ������������ �����
		/// wcWordLower - ������������ ����� ���������� � ������� ��������
		/// HypothesisInfo - ���������� �� ���������
		/// DWC - �������� ��������
		virtual bool DeterminationWordInfo(
			const wchar_t* wcWord, 
			const wchar_t* wcWordLower, 
			bool IsFirstLetterUpperCase,
			SHypothesisInfo &HypothesisInfo,
			const IDeterminationWordCheck &DWC
			) = 0;

		/// ����� ������ ��������������� ���������� �� ������� �����
		bool GetWordInfo/*ByWordIndex*/(
			const SWordIndex* pWordIndex, 
			SWordInfo* pWordInfo
			);

		/// ����� ����� �� ��� ������� 
		/// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
		/**
		��������:
		����� ���� �� ���� �������� (������� ����� ����).
		*/
		bool GetWord(
			const SWordIndex* pWordIndex,
			wchar_t* wcWord
			);

		/// ����� ������ ����� ����� (����� ����� ��� ���������) �� ��� ������� 
		/// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
		/**
		��������:
		����� ����� �� ���� �������� (������� ����� ����).
		*/
		bool GetWordSource(
			const TDictionaryIndex &DictIndex,
			wchar_t* wcWordSource
			);

		/// ����� ��������� ����� �� ������� ������
		/**
		��������:
		����� ���� �� ���� �������� (������� ����� ����).
		*/

		bool GetWordFormsByIDSource(
			const TDictionaryIndex* pDictionaryIndex,
			/*out*/std::list<TWordInfo>* p_l_WordInfo
			);

		/// ��������
		bool GetMorphoInfoByIDType(
			/*in*/SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber eDictionariesNumber,
			/*in*/SS::Dictionary::Types::TIDType oIDType, 
			/*in*/SS::Dictionary::Types::TIDForm oIDForm, 
			/*out*/SS::Dictionary::Types::TMorphoInfo* pMorphoInfo, 
			/*out*/SS::Dictionary::Types::TSpecialMorpho* pSpecialMorpho) {}


		///��������� ����� � ������� ����� ���� 
		///���������� ��������� ��� ����� ����� ��� ���. �.�. ����� � ������� ����� �����
		/// Source - ����������� ����� (������ + ���������)
		/// SourceLower - Source ���������� � ������� ��������
		/// EndingLen - ����� ��������� �����
		/// DI  -  ������ ������ ��� ������������ �����.
		//void AddNewWord( const TString &Source, const TIDType IDType, int EndingLen, TDictionaryIndex &DI )
		//{
		//   TString SourceLower; ToLower( Source, SourceLower );

		//   AddNewWord( Source, SourceLower, IDType, EndingLen, DI );
		//}

		void AddNewWord( const TString &Source, const TString &SourceLower, const TIDType IDType, int EndingLen, TDictionaryIndex &DI );

		//������ ���������� �������������� ������ � CMorphoTypesSearch
		BOOL GetMorphoInfoByIDType(
			IN  SS::Dictionary::Types::TIDType oIDType, 
			IN  SS::Dictionary::Types::TIDForm oIDForm, 
			OUT SS::Dictionary::Types::TMorphoInfo * pMorphoInfo, 
			OUT SS::Dictionary::Types::TSpecialMorpho * pSpecialMorpho
			)
		{
			APL_ASSERT( CheckLoad() );
			return m_pMorphoTypesSearch->GetMorphoInfoByIDType( oIDType, oIDForm, pMorphoInfo, pSpecialMorpho );
		}

		///////////////////////////////////////////////////////////////////////////////
		//ILoad

		/// ��������� ������ � ������. �������������� ������������� �������.
		bool ReLoad();

		/// ��������� ������ � ������ ���� ��� �� ���������
		bool Load();

		/// ������� ������
		bool Clear();

		//���������� �������
		bool ToBinary();

		//���������� ������� � ������� ����� ������������ � ����������� ��� �����.
		//���� pDataTable == 0, �� ����� � ���������� ������������ ������ � ������
		void SetNewWordsTable( DBMS::IDataTable *pDataTable ){ m_NewWords.SetTable( pDataTable, m_NewWordsDictionaryIndex ); }

		//�������� ��� ����� ���� (���� �� ����������� ������� � ���� �� ������ �� ����� ������ ������������. 
		//����� �����������, �� ��������� ������ ������ � ������)
		void ClearNewWordsCache(){ m_NewWords.Clear(); }

		///////////////////////////////////////////////////////////////////////////////
		// ����������� ��������������� ���������� ���������� ����� ���������� �� ����� 
		// ������ ���� �������������� � �������. ����� ������� ����� �� ����� ���� �� 
		// ������ �����������.
		///////////////////////////////////////////////////////////////////////////////
		bool GetCompoundWordInfo( 		
			const wchar_t* wcWord, 
			const wchar_t* wcWordOriginalCase,
			bool IsFirstLetterUpperCase,
			TWIList &WIList
			);


		//������� ������������ ������ ��� �������!!!
		TPartOfWordsSearchPtr GetNominalWS() { return  m_pNominalWS; }						   
		TPartOfWordsSearchPtr GetProperWS() { return  m_pProperWS;	}					    
		TPartOfWordsSearchPtr GetEndingWS() { return  m_pEndingWS; }						   
		TSourceToTypeConstPtr GetNominalSourceToMorpho() { return  m_pNominalSourceToMorpho; }			
		TSourceToTypeConstPtr GetProperSourceToMorpho() { return  m_pProperSourceToMorpho; }			
		Detail::CNewWordsCache *GetNewWords() { return &m_NewWords; }
		IAMConverterMorpho *GetAMConverter() const { APL_ASSERT_PTR(m_pAMConverter); return m_pAMConverter; }
	};


///////////////////////////////////////////////////////////////////////////////
// ����������� ������� �� ������ �������� ���� ���� ������� � ������ �����������
// ����������
///////////////////////////////////////////////////////////////////////////////
class CStandartSmartDictionary: public CSmartDictionary
{
private:
   /// ����� ������. 
   /// ������� ��� ����� � ������� ���������� �� ������ HypothesisInfo.m_ConcordanceChars � ��������������� ��������
   /// ��������� � DeterminationWordInfo (����� 1). ���� ��������� ����� � ����������� ��������� �������� ������ ��� 
   /// HypothesisInfo.m_ConcordanceChars, �� ��� ������� �������� ���������. �.�. ���������� ����� �� �������� 
   /// ���������� �������.
   void FillHypothesisInfo(
      const wchar_t* wcWord,
      const wchar_t* wcWordLower, //����� � ������ ��������
      bool IsFirstLetterUpperCase,
      int WordLen,  //����� �����
      const SPartOfWord  &IDEnding,
      TPartOfWordsSearchPtr pSourseWS, 
      TSourceToTypeConstPtr pSourceToType,
      TDictNumber DictionaryIndex,
      SHypothesisInfo &HypothesisInfo,
      const IDeterminationWordCheck &DWC
   ) const;

public:
   //�������������� ���� � ����������� �������, ����� ��������� ������ �������. ����� ������ ����� �������� ������
   /// pDataBase     - ������������ ��
   /// pAMConverter  - ���������  
	/// DBPath -        ���� � �������� �� � ������ ������� ���������� 
	///                 ������������ � �������
	///	ProperDictionaryIndex, NominalDictionaryIndex, NewWordsDictionaryIndex  - ������� �������� ��� ������������� � TDictionaryIndex
	void Init(
      DBMS::IDataBase *pDataBase,
      IAMConverterMorpho *pAMConverter, const TCHAR *DBPath, 
		TDictNumber NominalDictionaryIndex,
		TDictNumber ProperDictionaryIndex, 
      TDictNumber NewWordsDictionaryIndex,
      int MinRecognizableWordLen
	)
   {  
      CSmartDictionary::Init( pDataBase, pAMConverter, DBPath, NominalDictionaryIndex, ProperDictionaryIndex, NewWordsDictionaryIndex, MinRecognizableWordLen ); 
   }

   /**
      ��������:
         ������� �� ��������� ���� �� ����� � ��������, � ����� �������� ����������           
         �������� ������� �� ���� � ����� ����� (��������) �� ��������� �������� (����� ����������� IDeterminationWordCheck):
            1. ����� ������ ������ 4-� ���� �� ������������ �������������
            2. �� �� ��������� �������� ��������� ������ �� ���������, �.�. ��� ���� ����� ��������� ����� ��������
               ��������� ���������� ����� ��������� �� ������ ���������(����� ������), �� � ������ ���� ������ ������
   */
   bool DeterminationWordInfo(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      SHypothesisInfo &HypothesisInfo,
      const IDeterminationWordCheck &DWC
   );
};

///////////////////////////////////////////////////////////////////////////////
// ����������� ������� �� ������ �������, ������������ ������ ������
// ��. MinimalHypothesisTree.h
///////////////////////////////////////////////////////////////////////////////
class CMinimalHypothesisTreeSmartDictionary: public CSmartDictionary
{
   TPartOfWordsSearchPtr m_pNewWordsDeductionWS;						   //����������� ������ ������
   CTablePtr m_pNewWordsDeductionDT;                                 

private:
   static const wchar_t * const szNewWordsDeductionTable;

public:
   //�������������� ���� � ����������� �������, ����� ��������� ������ �������. ����� ������ ����� �������� ������
   /// pDataBase     - ������������ ��
   /// pAMConverter  - ���������  
   /// DBPath -        ���� � �������� �� � ������ ������� ���������� 
   ///                 ������������ � �������
   ///	ProperDictionaryIndex, NominalDictionaryIndex, NewWordsDictionaryIndex  - ������� �������� ��� ������������� � TDictionaryIndex
   void Init(
      DBMS::IDataBase *pDataBase,
      IAMConverterMorpho *pAMConverter, const TCHAR *DBPath, 
      TDictNumber NominalDictionaryIndex,
      TDictNumber ProperDictionaryIndex, 
      TDictNumber NewWordsDictionaryIndex,
      int MinRecognizableWordLen
   );

   /**
      ��������:
         ������� �� ��������� ���� �� ����� � ��������, � ����� �������� ����������           
         �������� ������� �� ���� � ����� ����� (��������) �� ��������� �������� (����� ����������� IDeterminationWordCheck):
            1. ����� ������ ������ 4-� ���� �� ������������ �������������

         �� ������� ������������ ���������� � ����� � ������ ������ � ��� ����� ���������� IDType, ����� ����
         � �������� ����, �������� ������ �� ��������� �� ������� ���� ���������� ���������� � ����� (������� ������ 
         ���������, ���� ��� ������������ � IDType)
   */
   bool DeterminationWordInfo(
      const wchar_t* wcWord, 
      const wchar_t* wcWordLower, 
      bool IsFirstLetterUpperCase,
      SHypothesisInfo &HypothesisInfo,
      const IDeterminationWordCheck &DWC
   );

};

///////////////////////////////////////////////////////////////////////////////
struct TStandartDeterminationWordCheck: public CSmartDictionary::IDeterminationWordCheck
{
   //������������� �� �������� ���������:
   // ���� ����� � ������� �����, �� ����� - ���������������
   // Ec�� ����� � ��������� �����, �� ��� �� ��������� ����� ����
   bool IsDeterminationWord( const wchar_t* wcWord, const wchar_t* wcWordLower, bool IsFirstLetterUpperCase, TDictNumber DictionaryIndex, TMorphoInfo MorphoInfo, TSpecialMorpho SpecialMorpho, IAMConverterMorpho *pAMConverter ) const;
};

///////////////////////////////////////////////////////////////////////////////

struct TOnlyNounDeterminationWordCheck: public CSmartDictionary::IDeterminationWordCheck
{
   //�� ���� ������ ��������� ������ ���������������
   bool IsDeterminationWord( const wchar_t* wcWord, const wchar_t* wcWordLower, bool IsFirstLetterUpperCase, TDictNumber DictionaryIndex, TMorphoInfo MorphoInfo, TSpecialMorpho SpecialMorpho, IAMConverterMorpho *pAMConverter ) const;
};

///////////////////////////////////////////////////////////////////////////////
// ���������� CSmartDictionary � ���������� IBasicMorphologyAnalyser
///////////////////////////////////////////////////////////////////////////////
class CSmartDictionaryAdapter: public Detail::IBasicMorphologyAnalyser
{
public:
   typedef auto_ptr_ex<CSmartDictionary> TSmartDictionaryPtr;
   
   enum TDictionaryTypes
   {
      EStandart,
      EMinimalHypothesisTree,
   };

   static TSmartDictionaryPtr CreateSmartDictionary( TDictionaryTypes DictionaryTypes )
   {
      switch(DictionaryTypes)
      {
      case EStandart:
         return TSmartDictionaryPtr(new CStandartSmartDictionary);
         break;

      case EMinimalHypothesisTree:
         return TSmartDictionaryPtr(new CMinimalHypothesisTreeSmartDictionary);
      };

      APL_ASSERT( false );
      return TSmartDictionaryPtr(0);
   }

private:
   TSmartDictionaryPtr m_SmartDictionary;

public:
   
   //�������������� ���� � ����������� �������, ����� ��������� ������ �������. ����� ������ ����� �������� ������
   /// pDataBase     - ������������ ��
   /// pAMConverter  - ���������  
   /// DBPath -        ���� � �������� �� � ������ ������� ���������� 
   ///                 ������������ � �������
   ///	ProperDictionaryIndex, NominalDictionaryIndex, NewWordsDictionaryIndex  - ������� �������� ��� ������������� � TDictionaryIndex
   void Init(
      DBMS::IDataBase *pDataBase,
      IAMConverterMorpho *pAMConverter, const TCHAR *DBPath, 
      TDictNumber NominalDictionaryIndex,
      TDictNumber ProperDictionaryIndex, 
      TDictNumber NewWordsDictionaryIndex,
      int MinRecognizableWordLen,
      TDictionaryTypes DictionaryTypes = EStandart
   )
   { 
      m_SmartDictionary = CreateSmartDictionary( DictionaryTypes );

      APL_ASSERT( m_SmartDictionary != 0 );

      m_SmartDictionary->Init(pDataBase, pAMConverter, DBPath, NominalDictionaryIndex, ProperDictionaryIndex, NewWordsDictionaryIndex, MinRecognizableWordLen );
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   //IMorphologyAnalyser

   /// �������� ������� ����� � �������
   bool IsExistWord(/*in*/const wchar_t* wcWord){ return m_SmartDictionary->IsExistWord( wcWord ); }

   /// ����� ������ ��������������� ���������� �� ����� 
   bool GetWordInfo/*ByWord*/(
      /*in*/const wchar_t* wcWord, 
      /*in*/const wchar_t* wcWordOriginalCase, 
      /*in*/bool IsFirstLetterUpperCase,
      /*out*/std::list<TWordInfo>* p_l_WordInfo
      )
   { return m_SmartDictionary->GetWordInfo( wcWord, wcWordOriginalCase, IsFirstLetterUpperCase, p_l_WordInfo ); }


   /// ����� ������ ��������������� ���������� �� ������� �����
   bool GetWordInfo/*ByWordIndex*/(
      /*in*/SWordIndex* pWordIndex, 
      /*out*/SWordInfo* pWordInfo
      )
   { return m_SmartDictionary->GetWordInfo( pWordIndex, pWordInfo ); }

   /// ����� ����� �� ��� ������� 
   /// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
   bool GetWord(
      /*in*/SWordIndex* pWordIndex,
      /*out*/wchar_t* wcWord
      )
   { return m_SmartDictionary->GetWord( pWordIndex, wcWord ); }

   /// ����� ������ ����� ����� (����� ����� ��� ���������) �� ��� ������� 
   /// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
   bool GetWordSource(
      const TDictionaryIndex &DictIndex,
      wchar_t* wcWordSource
   )
   { return m_SmartDictionary->GetWordSource( DictIndex, wcWordSource ); }

   /// ����� ��������� ����� �� ������� ������
   bool GetWordFormsByIDSource(
      /*in*/TDictionaryIndex* pDictionaryIndex,
      /*out*/std::list<TWordInfo>* p_l_WordInfo
      )
   { return m_SmartDictionary->GetWordFormsByIDSource( pDictionaryIndex, p_l_WordInfo ); }

   //���������� ���������� CSmartDictionary
   CSmartDictionary &GetOrigin() { APL_ASSERT( m_SmartDictionary != 0 ); return *m_SmartDictionary; }
   const CSmartDictionary &GetOrigin() const { APL_ASSERT( m_SmartDictionary != 0 ); return *m_SmartDictionary; }
};


} //namespace Dictionary
} //namespace SS
