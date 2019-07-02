#pragma once

namespace SS{ 
namespace Dictionary{

 /*  namespace Types {
      inline bool operator<( const TDictionaryIndex &DI1, const TDictionaryIndex &DI2 ){ return DI1.GetDictionaryIndex() < DI2.GetDictionaryIndex(); }
   }*/

   //��������� ������� TDictNumber
   const std::string &DictNumberDescription( TDictNumber DictNumber );
   
   //��������� ������� TDictionaryInde, ��� GetId
   std::string DictionaryIndexDescription( TDictionaryIndex DictIndex );

   //��������� ������� EAnalyseMods
   const std::string &AnalyseModsDescription( EAnalyseMods AnalyseMods );
   
   //��������� ������� ECurrentSystemMode
   const std::string &CurrentSystemModeDescription( ECurrentSystemMode CurrentSystemMode );


namespace Detail{

//Read/Write ������� ����������� ���������� ����� �������������� �������
class CSharedObjectMutexBase {};
typedef ClassLevelLockable<CSharedObjectMutexBase, SSWMRImplStategy, CURRENT_THREAD_DEBUG_INFO> TSharedObjectMutex;

typedef std::list<CMorphoFeature> TFeatureList;

//��������� pIndex ����������� �� WIList
void FillUnit( const std::list<TWordInfo> &WIList, IUnit *pUnit, IBlackBoxTextStorage *pBB );

//��������� pIndex ����������� �� WordInfo
void FillUnit( const TWordInfo &WordInfo, IUnit *pUnit, IBlackBoxTextStorage *pBB );

//������� �������� �������� pUnit � ��������� �� ����������� �� WIList
void FillSubUnits( const std::list<TWordInfo> &WIList, IUnit *pUnit, IBlackBoxTextStorage *pBB );

//��������� pIndex ����������� �� MorhpoInfo, SpecialMorpho, IDForm 
void FillUnit( TMorphoInfo MorhpoInfo, TSpecialMorpho SpecialMorpho, TIDForm IDForm, const TDictionaryIndex &DI, IUnit *pUnit, IBlackBoxTextStorage *pBB );

//��������� pIndex ����������� �� FeatureList, IDForm 
void FillUnit( const TFeatureList &FeatureList, TIDForm IDForm, const TDictionaryIndex &DI, IUnit *pUnit, IBlackBoxTextStorage *pBB, IAMConverterMorpho *pAM );

//�������������� ������� ��������, ����������m �� ���������� �� TDictionaryIndex
template< class String >
inline void CorrectWordCase( String &Word, const TDictionaryIndex &DI )
{
   if( DI.GetFirstLetterUpperCase() )
      CharUpperBuffW( &Word[0], 1 );
}

///////////////////////////////////////////////////////////////////////////////
// ������������� ������ � ������ �������, ����������� � ��� ������ � �������� � 
// ������ LowerBuf (������ ���� �� ������ ����� ����� (������� ����������� \'0') ���,
// ���� ������ ����� �� ��������, ����������� ��������� ����� Constants::MAX_CHARS_IN_WORD) 
// ������������ ��� ����������� ����������� ��������.
// Len - ����� �����
// IsFirstLetterUpperCase - ������ ����� ����� � ������� ��������
///////////////////////////////////////////////////////////////////////////////
void PrepareWordForSearch( const TCHAR *wcWord, TCHAR LowerBuf[], size_t &Len, bool &IsFirstLetterUpperCase );

//����� ������������� ��������� ��� �������� ������� ������. ���������� ��� ������������ IMorphologyAnalyser
struct IBasicMorphologyAnalyser
{
   virtual ~IBasicMorphologyAnalyser() {}
   
   /// �������� ������� ����� � �������
   virtual bool IsExistWord(/*in*/const wchar_t* wcWord) = 0;

   /// ����� ������ ��������������� ���������� �� �����
   /// wcWord - ����� ���������� � ������� ��������
   /// wcWordOriginalCase - ����� � ������������ ���������
   /// IsFirstLetterUpperCase - ��������� �� ������ ����� ����� � ������� ��������
   virtual bool GetWordInfo/*ByWord*/(
      /*in*/const wchar_t* wcWord, 
      /*in*/const wchar_t* wcWordOriginalCase,
      /*in*/bool IsFirstLetterUpperCase,
      /*out*/std::list<SS::Dictionary::Types::TWordInfo>* p_l_WordInfo 
   ) = 0;

   /// ����� ������ ��������������� ���������� �� ������� �����
   virtual bool GetWordInfo/*ByWordIndex*/(
      /*in*/SS::Dictionary::Types::SWordIndex* pWordIndex, 
      /*out*/SS::Dictionary::Types::SWordInfo* pWordInfo
   ) = 0;

   /// ����� ����� �� ��� ������� 
   virtual bool GetWord(
      /*in*/SS::Dictionary::Types::SWordIndex* pWordIndex,
      /*out*/wchar_t* wcWord
   ) = 0;

   /// ����� ������ ����� ����� (����� ����� ��� ���������) �� ��� ������� 
   virtual bool GetWordSource(
      /*in*/const SS::Dictionary::Types::TDictionaryIndex &DictIndex,
      /*out*/wchar_t* wcWordSource
   ) = 0;


   /// ����� ��������� ����� �� ������� ������
   virtual bool GetWordFormsByIDSource(
      /*in*/SS::Dictionary::Types::TDictionaryIndex* pDictionaryIndex,
      /*out*/std::list<SS::Dictionary::Types::TWordInfo>* p_l_WordInfo
   ) = 0;
};
   
/*
 ����� �������� � ������ ������� ���� SourceToMorpho � ��������� ������ Type �� ���������������� Source
 ������������� �� ��� ����� ������ ����������� ������� ��������� � ������������� �����
*/
class CSourceToType: public OBJECT_LEVEL_LOCKABLE_SYNC_DEP<CSourceToType, SCriticalSectionImplStategy, CURRENT_THREAD_DEBUG_INFO>
{
public:
	typedef unsigned short TTypeIndex;

private:
	///�� ����� ������������ ������ ��� ������ ������� ������ �������� � ������� 
	///����� Source, � ���� �������� ����� Morpho. ������ ������� ��� ���� ����� 
	///�������� ���������� �������� Source. ��� ����� ������� ��������� �������� 
	///� ��� ��� ������� ����� ������������� � ��, ����� � � �������� Morpho ����� 
	///������������ ������� ����������� �������� ������ ������������ � ��. ��� 
	///����� ������� ��� �� ����� ���������� �������� �������� � �������� ���������
	///� ������, �� �� ��� ������������.
	typedef std::vector<TTypeIndex> TStorage;

private:
	TStorage m_Storage;
   DBMS::IDataBase *m_pDataBase;
   std::wstring m_TableName;

public:
   CSourceToType(): m_pDataBase(0){}
	
	///�������� Init
	CSourceToType(DBMS::IDataBase *pDataBase, const wchar_t *TableName ){ Init(pDataBase, TableName); }

	///�������������� ������, ����� ������� ���������� ��� ������� Load 
	void Init(DBMS::IDataBase * pDataBase, const wchar_t *TableName );

   //��������� �� ������
   bool Empty() const { return m_Storage.empty(); }


   //��������� ������ �� ������� � ������
   bool Load();

   //��������� ������ �� ������� � ������ ��� ������� ��� ��� �� ���� ��� ���������
   bool LoadIfNeed(){ if( Empty() ) return Load(); return true; }

	///������� ���� ��� ������ ������� �� ����
	static TTypeIndex EmptyIndex(){ return std::numeric_limits<TStorage::value_type>::max(); }

	///����� �� ������� IDSource �������� IDType � �������������� ������� ������ �������.
	///���� ������ �� ������� ����������� ����� EmptyIndex()
	TTypeIndex Find( size_t IDSource ) const
	{
		APL_ASSERT( !Empty() );

      if( IDSource >= m_Storage.size() )
			return EmptyIndex();

		return m_Storage[IDSource];
	}

	//������� ������
	void Clear(){ m_Storage.clear(); }
};

/**
	����� ��������� ���������� � ������ ��������� IDType � IDForm � MorphoInfo �� ������ MorphoTypeToMorphoInfo � 
	MorphoTypes	��������� �� ������������. �.�. ��� ������ ������� ������ ������ ��� IDType � �� ������ ����������� ������ 
	� �������������� �� ��� �����. ���� ������������ ������� ��� ��������� ����� �� �� ������ ��� ������� �� ������������ �������.
*/
class CIDTypeReferences
{
public:
	class TItem
	{
		//��������� TMorphoInfo � ������ ������ � �������
		typedef std::map<TMorphoInfo, UINT32> TMorphoInfoStorage;
		typedef std::map<TIDForm, UINT32> TIDFormStorage;
		
		mutable TMorphoInfoStorage  m_MorphoInfoStorage;
		mutable TIDFormStorage	m_IDFormStorage;

		friend CIDTypeReferences;

	public:
		static UINT32 UndefinedRecordID(){ return std::numeric_limits<UINT32>::max(); }
		
		//���������� MorphoInfoCount � IDFormCount
		size_t MorphoInfoCount() const { return m_MorphoInfoStorage.size(); }
		size_t IDFormCount() const { return m_IDFormStorage.size(); }

		//���� �� MorphoInfo
		bool IsExistsMorphoInfo( const TMorphoInfo &MI ) const
		{ return m_MorphoInfoStorage.find(MI) != m_MorphoInfoStorage.end(); }

		//���� �� IDForm
		bool IsExistsIDForm( const TIDForm &IDForm ) const
		{ return m_IDFormStorage.find(IDForm) != m_IDFormStorage.end(); }

		//�������� ������� MI ��� IDForm � ��������������� ����� ������
		void AddMorphoInfo( const TMorphoInfo &MI, UINT32 RecordNum = UndefinedRecordID() )
		{ APL_ASSERT( !IsExistsMorphoInfo(MI) ); m_MorphoInfoStorage.insert(TMorphoInfoStorage::value_type(MI,RecordNum)); }

		void AddIDForm( const TIDForm &IDForm, UINT32 RecordNum = UndefinedRecordID() )
		{ APL_ASSERT( !IsExistsIDForm(IDForm) ); m_IDFormStorage.insert(TIDFormStorage::value_type(IDForm, RecordNum)); }

		void DeleteMorphoInfo( const TMorphoInfo &MI )
		{ APL_ASSERT( IsExistsMorphoInfo(MI) ); m_MorphoInfoStorage.erase(MI); }
		
		void DeleteIDForm( const TIDForm &IDForm )
		{ APL_ASSERT( IsExistsIDForm(IDForm) ); m_IDFormStorage.erase(IDForm); }

		//���������� ����� ������ ������� ��� ����� ����������� MI ��� IDForm
		//���� ������ ��� ����� ������ ������������ UndefinedRecordID()
		UINT32 GetMorphoInfoRecordID( const TMorphoInfo &MI ) const
    	{
			TMorphoInfoStorage::const_iterator I = m_MorphoInfoStorage.find(MI);
			return I == m_MorphoInfoStorage.end() ? UndefinedRecordID() : I->second;
		}

		UINT32 GetIDFormRecordID( const TIDForm &IDForm ) const
		{
			TIDFormStorage::const_iterator I = m_IDFormStorage.find(IDForm);
			return I == m_IDFormStorage.end() ? UndefinedRecordID() : I->second;
		}

	};

	typedef std::map<TIDType, TItem> TStorage;

	//�������� �������� ���� ������������ �� ����� ������ ��������� ��������
	enum eUseTables
	{
		UTNotUseAnyTable = 0,
		UTMorphoTypes = 1 << 0,
		UTMorphoTypeToMorphoInfo = 1 << 1,
		UTAll = UTMorphoTypes | UTMorphoTypeToMorphoInfo
	};

private:
	//��������� ����������� ���������� ��������� �� ������������, ��� ���������� ������� ���������� mutable
	mutable TStorage m_Storage;
	mutable DBMS::IDataTable *m_pMorphoTypes;
	mutable DBMS::IDataTable *m_pMorphoTypeToMorphoInfo;
	int m_UseTables; //�� ����� ������ ������ ������ (��������� �� ������������)


private:
	//��������� TItem ������� �� ������ m_pMorphoTypes � m_pMorphoTypeToMorphoInfo ���� ��� ��� ����������� �������������� 
	//����� � m_UseTables
	void FillItem( const TIDType &IDType, TItem &Item  ) const;

	//������������ ����� �������� ��������� �� Find
	TItem &FindImpl( const TIDType &IDType ) const;

public:
	CIDTypeReferences(): m_pMorphoTypes(0), m_pMorphoTypeToMorphoInfo(0), m_UseTables(UTNotUseAnyTable) {}
	
	//�������� Init
	CIDTypeReferences( DBMS::IDataTable *pMorphoTypes,  DBMS::IDataTable *pMorphoTypeToMorphoInfo, int UseTables = UTAll )
	{ Init(pMorphoTypes, pMorphoTypeToMorphoInfo, UseTables); }

	//�������������  ���������� �� ������� � ������� ������
	void Init( DBMS::IDataTable *pMorphoTypes,  DBMS::IDataTable *pMorphoTypeToMorphoInfo, int UseTables = UTAll )
	{
		m_UseTables = UseTables;
		m_pMorphoTypes = pMorphoTypes;
		m_pMorphoTypeToMorphoInfo = pMorphoTypeToMorphoInfo;
		m_Storage.clear();
		
		APL_ASSERT( (m_UseTables & UTMorphoTypes) == 0  || m_pMorphoTypes != 0  );
		APL_ASSERT( (m_UseTables & UTMorphoTypeToMorphoInfo) == 0 || m_pMorphoTypeToMorphoInfo != 0  );
	}

	//������������ ����� ������ IDType � IDForm � MorphoInfo. ������ ������ �� ������ ���� ��� �� ��������� � 
	//������������� �� ������������
	TItem &Find( const TIDType &IDType ){ return FindImpl(IDType); }
	const TItem &Find( const TIDType &IDType ) const{ return FindImpl(IDType); }
};

///////////////////////////////////////////////////////////////////////////////
// ����������� ������� � �������� ����� � ��������. 
// ��� ������ ������� ����� ���������� ���� �����������:
// 1. ����� � ����� ������ ���� �� ���������� �� ����������, �.�. X ������ ���� ����� V.
//    ���������� ����� ����� ���� ������. ��� ���� ����������� ����� ��������� ����� (IV, IX, XL, XC, CD, CM)
// 2. ������������ �����, ������� ����� �������� �������� �������, ��� ������ �������� ��� �������� 
//    �������, �� ������� ������ ��������� (������ ������ ������� ����) - 3999 (MMMCMXCIX) - ������ 
//    ���� �� ��������� ���� ������ ������.
// 3. ���������� ������ ������ ���� ������ ���� ������: 
//    floor(<���������� �������� ���������� �����>/<���������� �������� �������� �����>) 
///////////////////////////////////////////////////////////////////////////////
class CRomanArabicConvertor
{
	//���������� �� ������� ������
   struct TRoman2ArabicBase
	{
		const TCHAR * const szRoman;        //����������� ������������� 
		unsigned int Arabic;                //��������� ��������
      unsigned char MaxSequenceLength;    //������������ ���������� ���������� ������ ������ ����
	};

	static const TRoman2ArabicBase rgRoman2ArabicBase[];

private:
   //�������������� ������� � ������ ������� (�� ������������ �������������, �� 
   //��� ����� ����� �������� � ������ ��������� 
   static TCHAR ToLowerImpl( TCHAR C ) { return C; }

public:
   //������������ ������� �����
   static unsigned int MaxRomanDigit(){ return 3999; }
   
   //������������ �������� ����� N � ������� szResult. ���������� � ����� ������ '\0'
   //BuffSize - ������������ ������ ������ (������� ����� ��� '\0')
   //�����: ��������� �� ����� ������ (�.�. �� '\0') ��� �������� ������������� � 0 ���� 
   //       �������� ������ 
	static TCHAR *Arabic2Roman( unsigned int N, TCHAR *szResult, size_t BuffSize );

	//������������ ������� ����� [Begin, End) � �������� N. 
   //�����: ������ ������ ������� �� ������� ��������������� � �������� ����� (��� End ��� ������� ����������� ���� �����)
	static const TCHAR *Roman2Arabic( const TCHAR *Begin, const TCHAR *End, unsigned int &N );
};

///////////////////////////////////////////////////////////////////////////////
// ������������ ����������� ������ ���������� ������������ (1st, 2nd) � ����� 
// � �������� 
///////////////////////////////////////////////////////////////////////////////
class CNumericOrderingConverter
{
   static const TCHAR * const rgPostfix[];

private:
   //���������� ��������� �� ������ ������� ���� �������� � �����, ��� ����
   //����� �������� ����������� ������ ���������� ������������
   static const TCHAR *GetLiteralString( unsigned int N );

public:
   //������������ ����� N � c���������� ������ ���������� ������������ szResult. 
   //���������� � ����� ������ '\0'
   //BuffSize - ������������ ������ ������ (������� ����� ��� '\0')
   //�����: ��������� �� ����� ������ (�.�. �� '\0') ��� �������� ������������� � 0 ���� 
   //       �������� ������ 
   static TCHAR *FromNumber( unsigned int N, TCHAR *szResult, size_t BuffSize );

   //������������ c���������� ������ ���������� ������������ [Begin, End) � ����� N. 
   //�����: ������ ������ ������� �� ������� ��������������� �  �����
   //(��� End ��� ������� ����������� ���� �����)
   static const TCHAR *ToNumber( const TCHAR *Begin, const TCHAR *End, unsigned int &N );
};


///////////////////////////////////////////////////////////////////////////////
// ��������� �����������, ����� � �������������� ������ � ������� ����� ����.
// ����������� ������������ ��������� �������:
//		��� ������, ������� ����������� ������ � ����, ���� ��� �� ��� �� � �������, ���� �
//		��� ����� �� ��������� ����� � ���.
//		��� ����������, ����������� ��� � ��� (���� ��� ��� ���) ��� � �� ���� (���� � ��� ��� ���).
//		��� �������� ��������� ��� �� ���� ��� � �� �������.
//
// ��������� �������� ������ � ����� � ������, �� ��������� � �� ����� ��������� ������.
//
// ��������� ������ �� Source - ���������� ������������� ������ � �� IDSource -
// ������� ������. ������ IDSource ������ ������ ���� ����������, � Source ����� 
// ����������� � ��� ������ �� Source ������������ ��������� �������� � ����� ������
///////////////////////////////////////////////////////////////////////////////
class CNewWordsCache
{
public:
   typedef wchar_t TChar;
   typedef std::basic_string<TChar> TString;

   //�������� ������ 
   class CSourceData
   {
      TDictionaryIndex m_IDSource; //������������� ������
      TIDType m_IDType;
      TString m_Source;
      TString m_SourceLower;       //Source ���������� ������� ������������ ��� ������
   
   public:
      CSourceData():  m_IDType(0) {}

      const TDictionaryIndex &GetIDSource() const{ return m_IDSource; }
      const TIDType &GetIDType() const { return m_IDType; }
      const TString &GetSource() const{ return m_Source; }
      
      //���������� Source ��� ��������� ������ (������ �������)
      const TString &GetSourceForFind() const{ /*return m_SourceLower;*/ return m_Source; }

      void SetIDSource(const TDictionaryIndex &V) { m_IDSource = V; } 
      void SetIDType(const TIDType &V) { m_IDType = V; } 
      void SetSource(const TString &V) { m_Source = V; ToLower( V, m_SourceLower); }

      //���������� Source � ��� ��������� �������������� Source ���������� �������.
      //�������� ������� ��� SetSource
      void SetSourceWithSourceLower( const TString &Source, const TString &SourceLower )
      {  m_Source = Source; m_SourceLower = SourceLower; }

      struct TDictionaryIndexesSet: public std::binary_function<CSourceData, CSourceData, bool>
      {
         bool operator()( const CSourceData &SD1, const CSourceData &SD2 ) const
         {
            return SD1.GetIDSource().GetId() == SD2.GetIDSource().GetId() ||
               ( SD1.GetSource() == SD2.GetSource() && SD1.GetIDType() == SD2.GetIDType() );
         }
      };
   };

private:
   // ���������� �����������, ��������� �������: ����� ������� ��������� CSourceData � ������ � 
   // ���������� ��� ������� �� IDSource � Source ��� ������ unordered_map � ������� ��� �������� ����� 
   // �������������� �������� ������.
   // ��� ���� ����� ���������� ��������� �������: 
   // 1. ���� � ������� �� ����������� Source ���� ������ �� � ������� ��
   //    IDSource ��� �� ����������� ���� ��� ������ ��� ���� Source (Source �� ��������). 
   // 2. �� ���� � ������� �� IDSource ���� ������ �� ��� �� ����������� ���� � ������� �� Source(IDSource). 
   // ���� ������ ����������� ������� 2 �� ����� ������� ��� ������ �� IDSource ������ ��� � �� Source, ��� ���� �����
   // �������� ��� ��������� �������� Source, � �� ������ �� ������� ������������� IDSource
   typedef std::list<CSourceData> TStorage;                                        //������ ���� ���������� � ���� �����

#if 0 //� unordered_map � ����������� ���������� VC ����� ������ ������������������ �� ����������� ������
   typedef std::unordered_map<unsigned int, TStorage::iterator> TIDSourceIndex;       //������ �� IDSource.GetID
   typedef std::unordered_multimap<TString, TStorage::iterator> TSourceIndex;         //������ �� Source
#else
   typedef std::map<unsigned int, TStorage::iterator> TIDSourceIndex;               //������ �� IDSource.GetID
   typedef std::multimap<TString, TStorage::iterator> TSourceIndex;                 //������ �� Source
#endif
   typedef ClassLevelLockable<CNewWordsCache> TMutex;                              //������������ ������� ��� ����������
   typedef std::pair<TSourceIndex::iterator, TSourceIndex::iterator> TSourceIndexIterPair;


public:
   //����� ������������ ��� ������ �� Source � ��������� ���������������� �� �����������
   //������� ������� �� ����������, �� �������� ���������� � ��������� ������ �����, ���� � 
   //����������� �� ������ ����������. 
   //TODO: ������ ������ � ������� CSelectIterator 
   class CCursor
   {
      typedef std::pair<TSourceIndex::const_iterator, TSourceIndex::const_iterator> TImpl;
      TImpl m_Impl;
      
      explicit CCursor( const TImpl &Impl ): m_Impl(Impl) {}
      
      //������ �� ��������
      static bool Empty( const TImpl &Impl ){ return Impl.first == Impl.second; }

      friend class CNewWordsCache;
   public:
      CCursor() { m_Impl.first = m_Impl.second; }

      //����������� �� ��������
      bool End() const { return Empty(m_Impl); }
      void Next() {APL_ASSERT(!End()); ++m_Impl.first; } 
      const CSourceData &Get() const { APL_ASSERT(!End()); return *m_Impl.first->second; }
   };

private:
   //mutable ��������� � ��� ����������� ���������� ��������� �� ������������ 
   mutable TStorage m_Storage;
   mutable TIDSourceIndex m_IDSourceIndex;
   mutable TSourceIndex m_SourceIndex;
   DBMS::IDataTable *m_pTable;   //������� � �� � ������� �������� ������, ����� ���� 0
   TDictNumber m_DictNumber;
   UINT32 m_NextAddID;           //��������� ������ ������� ���������� ��������� IDSource ��� ���������� ������
   TMutex m_Mutex;               //������ ������ ������. ��������� ��� ����������� ����������, ��� ������� ��� ��������� �������� ���������� ���� �������


private:
   //�������������� ������ � ������ �������, Src � Dst ����� ���������
   static void ToLower( const TString &Src, TString &Dst )
   {
      std::vector<TChar> Buff( Src.begin(), Src.end() ); 
      CharLowerBuff( &Buff[0], static_cast<DWORD>(Buff.size()) );
      Dst.assign( Buff.begin(), Buff.end() );
   }

   //���� � DBMS ������� �������� �� IDSource
   bool FindInTableByIDSource( const TDictionaryIndex &IDSource, CSourceData &SourceData ) const;
     
   //������� � DBMS ������� �������� �� IDSource
   bool DeleteInTableByIDSource( const TDictionaryIndex &IDSource );
   
   //������� � DBMS ������� �������� �� Source
   //Source - ��������� � ������� �������� ������
   bool DeleteInTableBySource( const TString &Source );

   //��������� ������ � �������
   //���������� SourceData.GetIDSource(). ������� ������ ������ � ��������� �� ���� � �������.
   //������ ������������ � m_NextAddID
   void AddToTable( const CSourceData &SourceData );

public:
   CNewWordsCache(): m_pTable(0), m_DictNumber(DATA_TYPE::NAMES::ednUnknown), m_NextAddID(1) {}
   
   //�������� SetTable
   explicit CNewWordsCache( DBMS::IDataTable *pTable, TDictNumber DictNumber ): m_pTable(0), m_DictNumber(DATA_TYPE::NAMES::ednUnknown), m_NextAddID(1)
   { SetTable(pTable, DictNumber); }
  
   //���� ������� �� ������� ��������� �� ����� ����� ������ � �������, (��. �������� ������) ����� ���� ���������� 0
   //��� ������ �� �������� ������� ��� ��������� ����� ����������� ������ � ������
   //DictNumber - ����� ������� � ������� �������������� ��������
   void SetTable( DBMS::IDataTable *pTable, TDictNumber DictNumber );
   
   //���������� ������ � ������ (������� ���)
   void Clear();
   
   //����� �� IDSource, ��� ��������� ������� ������ ������������ 0, ��������� ��. �������� ������
   const CSourceData *FindByIDSource( const TDictionaryIndex &IDSource ) const;
   
   //���������� ������ ���� ��������� � ���� ������
   CCursor GetData() const
   {
      return CCursor(CCursor::TImpl(m_SourceIndex.end(), m_SourceIndex.end()));
   }

   //����� �� Source, ���������� ������ ��������� ��������, ��������� ��. �������� ������
   //���������� ����� � ������� ������ ��������� ������� CCursor::End()
   CCursor FindBySource( const TString &Source ) const
   {  TString LString; ToLower( Source, LString ); return FindBySourceLower(LString); }

   //������ ���� ��� � FindBySource, �� ������� ����� Source ��� ������� � ������� ��������, ��������� ����� 
   //�������� �������
   CCursor FindBySourceLower( const TString &Source ) const;

   //�������� �� IDSource, ���� ���� ����� ������, ��������� ��. �������� ������
   void DeleteByIDSource( const TDictionaryIndex &IDSource );
   
   //�������� �� Source, ���� ���� ����� ������, ��������� ��. �������� ������
   void DeleteBySource( const TString &Source )
   {  TString LString; ToLower( Source, LString ); DeleteBySourceLower(LString);  }

   //������ ���� ��� � DeleteBySource, �� ������� ����� Source ��� ������� � ������� ��������, ��������� ����� 
   //�������� �������
   void DeleteBySourceLower( const TString &Source );

   //���������� ����� ������.������� �� ��������� 
   //������� SourceData � ������� � ��������� � ����� ������
   //SourceData.GetIDSource() ������������ ��� ����������, ���������� ���������� ������������� �
   //����� ���������� ��� � ������� ������������ � SourceData
   //���������� 
   void Add( CSourceData &SourceData );
};

} //namespace Detail
} //namespace Dictionary
} //namespace SS


