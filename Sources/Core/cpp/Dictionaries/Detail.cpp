#include "stdafx.h"


namespace SS{ 
namespace Dictionary{

const std::string &DictNumberDescription( TDictNumber DictNumber )
{
   class CMapImpl
   {
      typedef std::map<TDictNumber, std::string> TDictToString;
      TDictToString m_DictToString;
      std::string NotFind;

   public:
      CMapImpl(): NotFind( "<ERROR_DICT_NUMBER>" )
      {
#define REGISTER_HELPER( arg )  m_DictToString.insert( TDictToString::value_type( arg, #arg) );

         using namespace SS::Dictionary::DATA_TYPE::NAMES;

         REGISTER_HELPER( ednRNominalName );
         REGISTER_HELPER( ednRProperName );
         REGISTER_HELPER( ednNumeric );
         REGISTER_HELPER( ednUnknown );
         REGISTER_HELPER( ednSymbols );
         REGISTER_HELPER( ednENominalName );
         REGISTER_HELPER( ednEProperName );
         REGISTER_HELPER( ednAbbreviationsRus );
         REGISTER_HELPER( ednAbbreviationsEng );
         REGISTER_HELPER( ednDates );
         REGISTER_HELPER( ednSyntax );
         REGISTER_HELPER( ednSemantic );
         REGISTER_HELPER( ednRCombinatory );
         REGISTER_HELPER( ednECombinatory );
         REGISTER_HELPER( ednUnknownRus );
         REGISTER_HELPER( ednUnknownEng );
         REGISTER_HELPER( ednSynonimsRus );
         REGISTER_HELPER( ednSynonimsEng );
         REGISTER_HELPER( ednRomanNumeric );
         REGISTER_HELPER( ednFloatPointNumeric );
         REGISTER_HELPER( ednOrderingEnglish );
		 REGISTER_HELPER( ednOrderingRussian );

#undef REGISTER_HELPER
      }

      const std::string &Find( TDictNumber DictNumber ) const
      {
         TDictToString::const_iterator I = m_DictToString.find(DictNumber);

         if( I != m_DictToString.end() )
            return I->second;


         return NotFind;
      }
   };

   static CMapImpl MapImpl;


   return  MapImpl.Find(DictNumber);
}
///////////////////////////////////////////////////////////////////////////////

const std::string &CurrentSystemModeDescription( ECurrentSystemMode CurrentSystemMode )
{
   class CMapImpl
   {
      typedef std::map<ECurrentSystemMode, std::string> TDictToString;
      TDictToString m_DictToString;
      std::string NotFind;

   public:
      CMapImpl(): NotFind( "<ERROR_ECurrentSystemMode>" )
      {
#define REGISTER_HELPER( arg )  m_DictToString.insert( TDictToString::value_type( arg, #arg) );

         using namespace SS::Dictionary::DATA_TYPE::NAMES;
         REGISTER_HELPER( ecsmLocal )
         REGISTER_HELPER( ecsmGlobal )

#undef REGISTER_HELPER
      }

      const std::string &Find( ECurrentSystemMode CurrentSystemMode ) const
      {
         TDictToString::const_iterator I = m_DictToString.find(CurrentSystemMode);

         if( I != m_DictToString.end() )
            return I->second;

         return NotFind;
      }
   };

   static CMapImpl MapImpl;


   return  MapImpl.Find(CurrentSystemMode);
}
///////////////////////////////////////////////////////////////////////////////

std::string DictionaryIndexDescription( TDictionaryIndex DictIndex )
{
   std::string Ret(DictNumberDescription(DictIndex.GetDictionaryNumber()) );

   Ret += (DictIndex.GetFirstLetterUpperCase() ? "_U": "_L");	
   
   return Ret;
}
///////////////////////////////////////////////////////////////////////////////

const std::string &AnalyseModsDescription( EAnalyseMods AnalyseMods )
{
   class CMapImpl
   {
      typedef std::map<EAnalyseMods, std::string> TDictToString;
      TDictToString m_DictToString;
      std::string NotFind;

   public:
      CMapImpl(): NotFind( "<ERROR_EAnalyseMods>" )
      {
#define REGISTER_HELPER( arg )  m_DictToString.insert( TDictToString::value_type( arg, #arg) );

         using namespace SS::Dictionary::DATA_TYPE::NAMES;

         REGISTER_HELPER( eamIndexation )
         REGISTER_HELPER( eamQuery )
         REGISTER_HELPER( eamStrictQuery )
         REGISTER_HELPER( eamOnlyKeyWords )
         REGISTER_HELPER( eamQueryAndSearchString )
         REGISTER_HELPER( eamRejectUnimportant )
         REGISTER_HELPER( eamSearch )

#undef REGISTER_HELPER
      }

      const std::string &Find( EAnalyseMods AnalyseMods ) const
      {
         TDictToString::const_iterator I = m_DictToString.find(AnalyseMods);

         if( I != m_DictToString.end() )
            return I->second;

         return NotFind;
      }
   };

   static CMapImpl MapImpl;


   return  MapImpl.Find(AnalyseMods);
}
///////////////////////////////////////////////////////////////////////////////


namespace Detail{

//template CObjectsSelector<int, int>;
//template CObjectsSelectorMultiKey<int, int>;
//template CObjectsSelectorMultiObject<int, int>;
//template bool CObjectsSelectorMultiKey<int, int>::Add( int *, int *, CObjectsSelectorMultiKey<int, int>::TAutoPtrRef AutoPtrRef );


void FillUnit( const std::list<TWordInfo> &WIList, IUnit *pUnit, IBlackBoxTextStorage *pBB )
{
   APL_ASSERT_PTR(pUnit);
   APL_ASSERT_PTR(pBB);
   
   typedef std::list<TWordInfo> TWIList;
   TWIList::const_iterator I;
   TWordInfo::const_iterator J;


   for( I = WIList.begin(); I != WIList.end(); ++I )
      for( J = I->begin(); J != I->end(); ++J )
         FillUnit( J->m_MorphoTypeInfo.m_MorphoInfo, J->m_SpecialMorpho, J->m_WordIndex.m_IDForm, J->m_WordIndex.m_DictIndex, pUnit, pBB );
}
///////////////////////////////////////////////////////////////////////////////

void FillUnit( const TWordInfo &WordInfo, IUnit *pUnit, IBlackBoxTextStorage *pBB )
{
   APL_ASSERT_PTR(pUnit);
   APL_ASSERT_PTR(pBB);

   TWordInfo::const_iterator I;


   for( I = WordInfo.begin(); I != WordInfo.end(); ++I )
      FillUnit( I->m_MorphoTypeInfo.m_MorphoInfo, I->m_SpecialMorpho, I->m_WordIndex.m_IDForm, I->m_WordIndex.m_DictIndex, pUnit, pBB );
}
///////////////////////////////////////////////////////////////////////////////

void FillSubUnits( const std::list<TWordInfo> &WIList, IUnit *pUnit, IBlackBoxTextStorage *pBB )
{
   APL_ASSERT_PTR(pUnit);
   APL_ASSERT_PTR(pBB);

   typedef std::list<TWordInfo> TWIList;

   if( WIList.empty() )
      return;
   
   IUnit *pPrev = 0;
   IUnit *pCur = pBB->CreateUnit();
   TWIList::const_iterator I = WIList.begin();
 
   pUnit->AddUnitVertical(pCur);
   
   for( ;; )
   {
      APL_ASSERT( !I->empty() );
      pCur->SetWord( I->front().m_wWord.c_str() );
      FillUnit( *I, pCur, pBB );

      ++I;
      
      if( I == WIList.end() )
         break;
      
      pPrev = pCur;
      pCur = pBB->CreateUnit();
      pPrev->AddUnitHorizontal(pCur);
   }
}
///////////////////////////////////////////////////////////////////////////////

void FillUnit( TMorphoInfo MorhpoInfo, TSpecialMorpho SpecialMorpho, TIDForm IDForm, const TDictionaryIndex &DI, IUnit *pUnit,  IBlackBoxTextStorage *pBB )
{
   APL_ASSERT_PTR(pUnit);
   APL_ASSERT_PTR(pBB);

   IIndex *pIndex = pBB->CreateIndex();
   IFeature *pFeature =  pBB->CreateFeature();

   pFeature->SetMorphoIndex( IDForm );
   pFeature->SetMorphoInfo( MorhpoInfo ); 
   pFeature->SetPartOfSpeech( SpecialMorpho ); 
   pIndex->GetDictionaryIndex()->AppendIndex( DI.GetDictionaryIndex() );
   
   pIndex->AddFeature( pFeature );
   pUnit->AddIndex( pIndex );
}
 
void FillUnit( const TFeatureList &FeatureList, TIDForm IDForm, const TDictionaryIndex &DI, IUnit *pUnit, IBlackBoxTextStorage *pBB, IAMConverterMorpho *pAM )
{
   APL_ASSERT_PTR(pUnit);
   APL_ASSERT_PTR(pBB);
   APL_ASSERT_PTR(pAM);

   int MorphoInfo;
   int SpecialMorpho;
   IIndex *pIndex = pBB->CreateIndex();
   IFeature *pFeature;

   for( TFeatureList::const_iterator I = FeatureList.begin(); I != FeatureList.end(); ++I )
   {
      pAM->Code( 
         DI.GetDictionaryNumber(),
         &*I,
         &MorphoInfo, 
         &SpecialMorpho
         );

      pFeature = pBB->CreateFeature();

      pFeature->SetMorphoIndex( IDForm );
      pFeature->SetMorphoInfo( MorphoInfo ); 
      pFeature->SetPartOfSpeech( SpecialMorpho ); 

      pIndex->AddFeature( pFeature );
   }

   pIndex->GetDictionaryIndex()->AppendIndex( DI.GetDictionaryIndex() );
   pUnit->AddIndex( pIndex );
}
///////////////////////////////////////////////////////////////////////////////

void PrepareWordForSearch( const TCHAR *wcWord, TCHAR LowerBuf[], size_t &Len, bool &IsFirstLetterUpperCase )
{
   Len = std::wcslen( wcWord );
   
   //APL_ASSERT( Len < Constants::MAX_CHARS_IN_WORD );

   if( Len >= Constants::MAX_CHARS_IN_WORD )
	   Len = Constants::MAX_CHARS_IN_WORD-1;
      //APL_THROW( _T("������ �������� ����� ������ ���� ������ ") << Constants::MAX_CHARS_IN_WORD << _T(". ������� �����: ") << wcWord );

   std::memcpy( LowerBuf, wcWord, (Len + 1) * sizeof(TCHAR) ); 
   CharLowerBuff( LowerBuf, static_cast<DWORD>(Len) );

   IsFirstLetterUpperCase = *LowerBuf != *wcWord;

   for( size_t i = 0; i < Len; ++i )
   {
      switch(LowerBuf[i])
      {
      case _T('�'):
         LowerBuf[i] = _T('�');
         break;

      case _T('�'):
         LowerBuf[i] = _T('\'');
         break;

      case _T('�'):
         LowerBuf[i] = _T('\'');
         break;
      }
   }
}
 
///////////////////////////////////////////////////////////////////////////////
// class CSourceToMorpho
///////////////////////////////////////////////////////////////////////////////
void CSourceToType::Init(DBMS::IDataBase *pDataBase, const wchar_t *TableName)
{
   APL_ASSERT_PTR(pDataBase);
   APL_ASSERT_PTR(TableName);

   m_pDataBase = pDataBase;
   m_TableName = TableName;



}
///////////////////////////////////////////////////////////////////////////////

bool CSourceToType::Load()
{
   APL_ASSERT_PTR(m_pDataBase);
   INT32   IDSource;
   INT32   IDType;			
   void    *TableRecord[]= {&IDSource,    &IDType};

   CTablePtr pTable;

   if( pTable.Open(m_pDataBase, m_TableName.c_str()) != S_OK )
      return false;

   APL_ASSERT( pTable.IsOpen() );
   APL_CHECK_S_OK( pTable->ScanInit(0, TableRecord) );

   //��������� ��� ������ � m_Storage
   m_Storage.clear();
   m_Storage.reserve(pTable->GetRecordsNumber()); //� ��� ����� ��������� �� ������ ��� ������� � �������

   while( pTable->Scan() == S_OK )
   {
      //������� ��������� �������� ���������� ������
      APL_ASSERT( 
         IDType >= std::numeric_limits<TStorage::value_type>::min() && 
         IDType <= std::numeric_limits<TStorage::value_type>::max() &&
         IDType != EmptyIndex()
         );

      APL_ASSERT(IDSource >= 0);

      //���� ���������� �������� ������ �������
      if(static_cast<TStorage::size_type>(IDSource) >= m_Storage.size())
         m_Storage.resize(IDSource + 1, EmptyIndex()); 

      APL_ASSERT(m_Storage[IDSource] == EmptyIndex());

      m_Storage[IDSource] = IDType;
   }

   return true;
}

///////////////////////////////////////////////////////////////////////////////
// class CIDTypeReferences
///////////////////////////////////////////////////////////////////////////////
CIDTypeReferences::TItem &CIDTypeReferences::FindImpl( const TIDType &IDType ) const
{
	TStorage::iterator I = m_Storage.find(IDType);

	if(	I == m_Storage.end() )
	{
		//������ ��� �� ������������, ��������� ����� �������
		I = m_Storage.insert( TStorage::value_type(IDType, TItem()) ).first;

		FillItem( IDType, I->second );
	}

	return I->second;
}
///////////////////////////////////////////////////////////////////////////////

void CIDTypeReferences::FillItem( const TIDType &IDType, TItem &Item ) const
{
	INT32 dbIDType = IDType;

	Item.m_IDFormStorage.clear();
	Item.m_MorphoInfoStorage.clear();

	//������������ ����� ������ � MorphoTypes � ��������� ��� IDForm
	if( m_UseTables & UTMorphoTypes )
	{
		APL_ASSERT(m_pMorphoTypes != 0);
		INT32 dbIDForm;
		void *RecMapMorphoTypes[4] = { &dbIDForm };

		CFindHelper MorphoTypesFind(m_pMorphoTypes);

		if( MorphoTypesFind.Init(_T("IDType"), &dbIDType, RecMapMorphoTypes) != S_OK )   
			SS_THROW( L"������ ��� ������������� ������ � MorphoType �� IDType" );

		while( MorphoTypesFind.Find() == S_OK )
		{
			APL_ASSERT( Item.m_IDFormStorage.find(dbIDForm) == Item.m_IDFormStorage.end() );
			Item.AddIDForm(dbIDForm, MorphoTypesFind.GetFoundIdx());
		}
	}

	if( m_UseTables & UTMorphoTypeToMorphoInfo )
	{
		APL_ASSERT(m_pMorphoTypeToMorphoInfo != 0);

		INT32 dbMorphoInfo;
		void *RecMapMorphoTypeToMorphoInfo[2] = { 0, &dbMorphoInfo };

		CFindHelper MorphoTypeToMorphoInfoFind(m_pMorphoTypeToMorphoInfo);

		if( MorphoTypeToMorphoInfoFind.Init(_T("IDType"), &dbIDType, RecMapMorphoTypeToMorphoInfo) != S_OK )   
			SS_THROW( L"������ ��� ������������� ������ � MorphoTypeToMorphoInfo �� IDType" );

		while( MorphoTypeToMorphoInfoFind.Find() == S_OK )
		{
			APL_ASSERT( Item.m_MorphoInfoStorage.find(dbMorphoInfo) == Item.m_MorphoInfoStorage.end() );
			Item.AddMorphoInfo(dbMorphoInfo, MorphoTypeToMorphoInfoFind.GetFoundIdx());
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
// class CRomanArabicConvertor
///////////////////////////////////////////////////////////////////////////////
CRomanArabicConvertor::TRoman2ArabicBase const CRomanArabicConvertor::rgRoman2ArabicBase[] =
{
   {_T("i"), 1, 3},{_T("iv"), 4, 1}, {_T("v"), 5, 1}, {_T("ix"), 9, 1}, {_T("x"), 10, 3}, {_T("xl"), 40, 1}, 
   {_T("l"), 50, 1}, {_T("xc"), 90, 1}, {_T("c"), 100, 3}, {_T("cd"), 400, 1}, {_T("d"), 500, 1},
   {_T("cm"), 900, 1}, {_T("m"), 1000, 3}
};
///////////////////////////////////////////////////////////////////////////////

TCHAR *CRomanArabicConvertor::Arabic2Roman( unsigned int N, TCHAR *szResult, size_t BuffSize )
{
	APL_ASSERT_PTR( szResult );

	size_t i = APL_ARRSIZE(rgRoman2ArabicBase) - 1;
	const TCHAR	*pCpy;

   if( 
      BuffSize < 1 || //����� ���� �� �������� '\0'��� N == 0
      N > MaxRomanDigit() 
   ) 
      return 0;

	while( N > 0 )
	{
		//������� ���������� �������� �����
		while( rgRoman2ArabicBase[i].Arabic > N ) --i;

      APL_ASSERT( i >= 0 );

		//�������� �������������� �������
		for( 
         pCpy = rgRoman2ArabicBase[i].szRoman; 
         *pCpy != _T('\0'); 
         ++pCpy, ++szResult, --BuffSize 
      ) 
      {
         if( BuffSize < 2 )  //��� ���� ����� �������� ������� ������ � '\0'
            return 0;

         *szResult = *pCpy;
      }

		N -= rgRoman2ArabicBase[i].Arabic;
	}
   
   APL_ASSERT( BuffSize > 0 );
	*szResult = _T('\0');

   return szResult;
}
///////////////////////////////////////////////////////////////////////////////

const TCHAR *CRomanArabicConvertor::Roman2Arabic( const TCHAR *Begin, const TCHAR *End, unsigned int &N )
{
   APL_ASSERT_PTR( Begin );
   APL_ASSERT_PTR( End );
   size_t i = APL_ARRSIZE(rgRoman2ArabicBase) - 1;
	const TCHAR *pCurInput;
	const TCHAR *pCurTempl;
   size_t PrevDigitIndex = APL_ARRSIZE(rgRoman2ArabicBase);  //������ � ������� rgRoman2ArabicBase ���������� ������������ �����
   unsigned int SequenceLength = 0;                          //���������� ��������������� ������ ���������� �������� 

	N = 0;

	while( Begin != End )
	{
		//������� ���������� ������� �����
		//��������� ��������������� ��� ��������� ����������
		for(;;)
		{
			for(
				pCurInput = Begin, pCurTempl = rgRoman2ArabicBase[i].szRoman;
				pCurInput != End && *pCurTempl != _T('\0') && ToLowerImpl(*pCurInput) == *pCurTempl;
				++pCurInput, ++pCurTempl
			) {;}

			if( *pCurTempl == _T('\0') ) break;	
				
			if( i == 0 )
				return Begin;

			--i;
		}
		 
      //�������� ������� � �������� �����������
      if( i == PrevDigitIndex )
      {
         if( ++SequenceLength > rgRoman2ArabicBase[i].MaxSequenceLength )
            return Begin;
      }
      else
      {
         PrevDigitIndex = i;
         SequenceLength = 1;
      }

		//�� ����� ���������� ��������������� ������������ ����������
		Begin = pCurInput;
		N += rgRoman2ArabicBase[i].Arabic;
	}

	return Begin;
}

///////////////////////////////////////////////////////////////////////////////
// class CNumericOrderingConverter
///////////////////////////////////////////////////////////////////////////////
const TCHAR * const CNumericOrderingConverter::rgPostfix[] = { 
   _T("th"), _T("st"), _T("nd"), _T("rd")
};
///////////////////////////////////////////////////////////////////////////////

const TCHAR *CNumericOrderingConverter::GetLiteralString( unsigned int N )
{
   if( N > 3 && N <= 20 )
      return rgPostfix[0];

   N %= 10;

   if( N < APL_ARRSIZE(rgPostfix) )
      return rgPostfix[N];


   return rgPostfix[0];
}
///////////////////////////////////////////////////////////////////////////////

TCHAR *CNumericOrderingConverter::FromNumber( unsigned int N, TCHAR *szResult, size_t BuffSize )
{
   TCHAR *pLiteralPos = ConvertIntegerToString( N, szResult, szResult + BuffSize - 1 );

   if( pLiteralPos == szResult )
      return 0;

   APL_ASSERT( pLiteralPos > szResult );

   const TCHAR *pPostfix = GetLiteralString( N );
   APL_ASSERT_PTR(pPostfix);
   
   //������ ������ ���������
   BuffSize = BuffSize - (pLiteralPos - szResult);

   //�������� ��������
   APL_ASSERT( BuffSize > 0 );

   do 
   {
      if( --BuffSize == 0 ) return 0;  //��������� � ������ ���� ������
      
      *(pLiteralPos++) = *(pPostfix++);
   } 
   while( *pPostfix );
   
   APL_ASSERT( BuffSize > 0 );
   
   *pLiteralPos = _T('\0');

   return pLiteralPos;  
}
///////////////////////////////////////////////////////////////////////////////

const TCHAR *CNumericOrderingConverter::ToNumber( const TCHAR *Begin, const TCHAR *End, unsigned int &N )
{
   const TCHAR *pLiteralPos = ConvertStringToInteger(Begin, End, N);

   if( pLiteralPos == Begin )
      return Begin;

   //���������� ���������� �����: �������� ����� ��������
   const TCHAR *pOrigin;
   const TCHAR *pTemplate;

   for( size_t i = 0; i < APL_ARRSIZE(rgPostfix); ++i )
   {
      pOrigin = pLiteralPos;
      pTemplate = rgPostfix[i];

      while( pOrigin != End && *pTemplate && *pOrigin == *pTemplate )
      {
         ++pOrigin;
         ++pTemplate;
      }

      if( !*pTemplate )
         return pOrigin;
   }

   return Begin; //�� �� ������ ����� �����, ���������� Begin
}


///////////////////////////////////////////////////////////////////////////////
// class CNewWordsCache
///////////////////////////////////////////////////////////////////////////////
void CNewWordsCache::Clear()
{
   m_Storage.clear();
   m_IDSourceIndex.clear();
   m_SourceIndex.clear();

   m_NextAddID = 1;
}
///////////////////////////////////////////////////////////////////////////////

void CNewWordsCache::SetTable( DBMS::IDataTable *pTable, TDictNumber DictNumber )
{
   if( pTable != m_pTable )
      Clear(); 

   m_pTable = pTable;  
   m_DictNumber = DictNumber; 
}
///////////////////////////////////////////////////////////////////////////////

const CNewWordsCache::CSourceData *CNewWordsCache::FindByIDSource( const TDictionaryIndex &IDSource ) const
{
   //�������� ����� ������� � ����
   TIDSourceIndex::const_iterator IIndex = m_IDSourceIndex.find( IDSource.GetId() );

   if( IIndex != m_IDSourceIndex.end() ) //�� ����� � ����
   {
      //������ �� Source ����� ���� ����
      return &*IIndex->second;
   }

   //��������� ����� � �������
   if( m_pTable != 0 )
   {
      CSourceData SourceData;

      if( FindInTableByIDSource(IDSource, SourceData) )
      {
         //�� ����� ������ � ������� ���������� �������� � ���
         TStorage::iterator IStorage;

         //�������� � ������ ������ ��� ��������� ����������� ����������
         m_Storage.push_front( SourceData );
         IStorage = m_Storage.begin();
         
         //�� ����� ��������� ������ � ������ �� IDSource, �.�. �������� Source � ����� ������ �� ���������
         //� � ������ �������� �� �� �����
         APL_CHECK( m_IDSourceIndex.insert( TIDSourceIndex::value_type(IDSource.GetId(), IStorage) ).second );

         return &*IStorage;
      }
   }
      
   return 0;
}
///////////////////////////////////////////////////////////////////////////////

CNewWordsCache::CCursor CNewWordsCache::FindBySourceLower( const TString &Source ) const
{   
   //�������� ����� ������� � ����
   CCursor::TImpl IterPair = m_SourceIndex.equal_range( Source );

   if( !CCursor::Empty(IterPair) ) //�� ����� � ���� Source, � ���� IDSource ��� ���� ������ ����
      return CCursor(IterPair);

   //��������� ����� � �������
   if( m_pTable != 0 )
   {
      INT32 dbIDSource;
      TString dbSource;
      TString dbSourceLower = Source;
      INT32 dbIDType;
      TDictionaryIndex DI;
      TStorage::iterator IStorage;
      TIDSourceIndex::iterator IIDSourceIndex;
      CSourceData SourceData;

      void *RecMap[4] = {&dbIDSource, &dbSource,  0, &dbIDType};

      CFindHelper FH( m_pTable );

      if( FH.Init(2u, &dbSourceLower, RecMap) != S_OK )
         SS_THROW( _T("������ ��� ������������� ������ � NewWords �� SourceLower") );
      
      if( FH.Find() == S_OK )
      {
         do 
         {    
            //���� ��� �� ���������, ��������� � ���������
            IIDSourceIndex = m_IDSourceIndex.find( dbIDSource );

            if( IIDSourceIndex == m_IDSourceIndex.end() )
            {
               DI.SetDictionaryNumber( m_DictNumber );
               DI.SetId( dbIDSource );

               SourceData.SetIDSource(DI);
               SourceData.SetSourceWithSourceLower(dbSource, dbSourceLower);
               SourceData.SetIDType( dbIDType );

               //�������� � ������ ������ ��� ��������� ����������� ����������
               m_Storage.push_front( SourceData );
               IStorage = m_Storage.begin();
              
               //������� � ������ �� IDSource
               APL_CHECK( m_IDSourceIndex.insert( TIDSourceIndex::value_type(SourceData.GetIDSource().GetId(), IStorage) ).second );
            }
            else
            {
               IStorage = IIDSourceIndex->second;
            }

            //������� � ������ �� Source
            m_SourceIndex.insert( TSourceIndex::value_type(Source, IStorage) );	
         } 
         while( FH.Find() == S_OK );

         IterPair = m_SourceIndex.equal_range(Source);
         APL_ASSERT( !CCursor::Empty(IterPair) );
      }
   }

   return CCursor(IterPair);

   //return CCursor(CCursor::TImpl(m_SourceIndex.end(), m_SourceIndex.end()));
}
///////////////////////////////////////////////////////////////////////////////

void CNewWordsCache::DeleteByIDSource( const TDictionaryIndex &IDSource )
{
   //�������� ����� ������� � ����
   TIDSourceIndex::iterator IIndex = m_IDSourceIndex.find( IDSource.GetId() );

   if( IIndex != m_IDSourceIndex.end() ) //�� ����� � ����
   {
      //������� �� �����������
      TSourceIndexIterPair IterPair = m_SourceIndex.equal_range( IIndex->second->GetSourceForFind() );
      
      //�� ���������� Source ������� ��� � �������� IDSource ����� ���������� (�� ������ ���� ����� ����)
      while( IterPair.first != IterPair.second && IterPair.first->second != IIndex->second ) ++IterPair.first;

      APL_ASSERT( IterPair.first != IterPair.second );
      m_SourceIndex.erase(IterPair.first);
      m_Storage.erase( IIndex->second );
      m_IDSourceIndex.erase( IIndex );
   }

   //��������� ������� �� �������
   if( m_pTable != 0 )
      DeleteInTableByIDSource( IDSource );
}
///////////////////////////////////////////////////////////////////////////////

void CNewWordsCache::DeleteBySourceLower( const TString &Source )
{ 
   TSourceIndexIterPair IterPair = m_SourceIndex.equal_range( Source );
   
   APL_ASSERT( std::distance(IterPair.first, IterPair.second) ==  m_SourceIndex.count(Source) );

   for( TSourceIndex::iterator I = IterPair.first; I !=  IterPair.second; ++I ) 
   {
      //������� �� �����������
      APL_CHECK( m_IDSourceIndex.erase(I->second->GetIDSource().GetId()) == 1 );
      m_Storage.erase( I->second );
   }

   m_SourceIndex.erase( IterPair.first, IterPair.second );

   //��������� ������� �� �������
   if( m_pTable != 0 )
      DeleteInTableBySource( Source );
}
///////////////////////////////////////////////////////////////////////////////

void CNewWordsCache::Add( CSourceData &SourceData )
{
   if( m_pTable != 0 )
   {
      //��� ���������� ��������� ������ �� ������� � ���. �.�. ����� ����� ����������
      //�� ����� ��������� ��� ���� ������ � ���� � � ������� ��� �� �������
      /*FindBySourceLower( SourceData.GetSourceForFind() );

      AddToTable( SourceData );*/
   }

   TStorage::iterator IStorage;
   TDictionaryIndex DI;
   
   APL_ASSERT( m_NextAddID <= TDictionaryIndex::MaxId() );

   DI.SetId( m_NextAddID );
   DI.SetDictionaryNumber( m_DictNumber );
   APL_ASSERT( m_IDSourceIndex.find(DI.GetId()) == m_IDSourceIndex.end() );

   SourceData.SetIDSource( DI );

   APL_ASSERT( std::find_if(m_Storage.begin(), m_Storage.end(), std::bind2nd(CSourceData::TDictionaryIndexesSet(), SourceData)) == m_Storage.end() );

   //�������� � ������ ������ ��� ��������� ����������� ����������
   m_Storage.push_front( SourceData );
   IStorage = m_Storage.begin();

   APL_CHECK( m_IDSourceIndex.insert( TIDSourceIndex::value_type(SourceData.GetIDSource().GetId(), IStorage) ).second );
   m_SourceIndex.insert( TSourceIndex::value_type(SourceData.GetSourceForFind(), IStorage) );
   
   ++m_NextAddID;
}
///////////////////////////////////////////////////////////////////////////////

bool CNewWordsCache::FindInTableByIDSource( const TDictionaryIndex &IDSource, CSourceData &SourceData ) const
{
   APL_ASSERT( m_pTable != 0 );
   APL_ASSERT( IDSource.GetDictionaryNumber() == m_DictNumber );
   
   INT32 dbIDSource = IDSource.GetId();
   TString dbSource;
   TString dbSourceLower;
   INT32 dbIDType;
   
   void *RecMap[4] = {0, &dbSource,  &dbSourceLower, &dbIDType};

   CFindHelper FH( m_pTable );

   if( FH.Init( 0u, &dbIDSource, RecMap ) != S_OK )
      SS_THROW( _T("������ ��� ������������� ������ � NewWords �� IDSource") );

   if( FH.FindOne()  == S_OK )
   {
      TDictionaryIndex DI;
      DI.SetDictionaryNumber( m_DictNumber );
      DI.SetId( dbIDSource );

      SourceData.SetIDSource(DI);
      SourceData.SetSourceWithSourceLower(dbSource, dbSourceLower);
      SourceData.SetIDType( dbIDType );

      return true;
   }

   return false;
}
///////////////////////////////////////////////////////////////////////////////

bool CNewWordsCache::DeleteInTableByIDSource( const TDictionaryIndex &IDSource )
{
   APL_ASSERT( m_pTable != 0 );
   APL_ASSERT( IDSource.GetDictionaryNumber() == m_DictNumber );
   
   INT32 dbIDSource = IDSource.GetId();

   void *RecMap[4] = {};

   CFindHelper FH( m_pTable );

   if( FH.Init( 0u, &dbIDSource, RecMap ) != S_OK )
      SS_THROW( _T("������ ��� ������������� ������ � NewWords �� IDSource") );

   while( FH.Find() == S_OK )
   {
      if( FAILED(m_pTable->DeleteRecord(FH.GetFoundIdx())) )
         SS_THROW( _T("������ ��� �������� ������ �� NewWords") );
   }
   return false;
}
///////////////////////////////////////////////////////////////////////////////

bool CNewWordsCache::DeleteInTableBySource( const TString &Source )
{
   APL_ASSERT( m_pTable != 0 );

   TString dbSourceLower = Source;

   void *RecMap[4] = {};

   CFindHelper FH( m_pTable );

   FH.Init( 2u, &dbSourceLower, RecMap );

   while( FH.Find() == S_OK )
   {
      if( FAILED(m_pTable->DeleteRecord(FH.GetFoundIdx())) )
         SS_THROW( _T("������ ��� �������� ������ �� NewWords") );
   }

   return false;
}
///////////////////////////////////////////////////////////////////////////////

void CNewWordsCache::AddToTable( const CSourceData &SourceData )
{
   DEBUG_MSG_LOG5("AddToTable " << Convert(SourceData.GetSource(), std::string()) << " IDType " << SourceData.GetIDType() );
   
   APL_ASSERT( m_pTable != 0 );
   
   INT32 dbIDSource;
   TString dbSource = SourceData.GetSource();
   TString dbSourceLower = SourceData.GetSourceForFind();
   INT32 dbIDType = SourceData.GetIDType();

   void *RecMap[4] = {&dbIDSource, &dbSource,  &dbSourceLower, &dbIDType};

   if( m_pTable->AddInit(RecMap) != S_OK )
      SS_THROW( _T("������ ��� ������������� ���������� � NewWords") );

   //�.�. ����� GetUserValue Add � SetUserValue � ���� ������� ����� ���������� ������ ������� ����� ������
   //���������� �� ���� ��������� � ��� ������
   //�������, �� ������������ ��� ��� � ������� ����� ��������� �� ��� ����� ������
   TMutex::Lock Guard(m_Mutex); 
   dbIDSource = m_NextAddID = m_pTable->GetUserValue(0) + 1; //� ������� �� ������ ���� ������� �������� 

   if( m_pTable->Add() != S_OK )
      SS_THROW( _T("������ ��� ���������� � NewWords") );

   APL_CHECK_S_OK( m_pTable->SetUserValue(0, m_NextAddID) );

   //�� ����������� �������� m_NextAddID ��� ���� �������
}

} //namespace Detail
} //namespace Dictionary
} //namespace SS

///////////////////////////////////////////////////////////////////////////////