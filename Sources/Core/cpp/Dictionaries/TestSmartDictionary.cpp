#include "stdafx.h"
#ifdef _SS_UNITTESTS

#include "TestSmartDictionary.h"
#include <iostream>
#include "../[libs]/Progress.hpp"
#include <shellapi.h>


namespace SS{ 
namespace UnitTests{ 
namespace Dictionary{
using namespace std;


bool operator==( const CTestSmartDictionary::CTestStorage::SWordInfo &Ob1, const CTestSmartDictionary::CTestStorage::SWordInfo &Ob2 )
{
   return
      Ob1.Str == Ob2.Str &&
      Ob1.Exist == Ob2.Exist &&
      Ob1.AutomaticDetermination == Ob2.AutomaticDetermination &&
      Ob1.HypothesisInfo == Ob2.HypothesisInfo &&
      Ob1.WIList == Ob2.WIList &&
      Ob1.WordByIDSourceList == Ob2.WordByIDSourceList;
}
///////////////////////////////////////////////////////////////////////////////

bool operator==( const CTestSmartDictionary::CTestStorage &Ob1, const CTestSmartDictionary::CTestStorage &Ob2 )
{
   return
      Ob1.WordInfoList == Ob2.WordInfoList;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class CTestSmartDictionary
///////////////////////////////////////////////////////////////////////////////

void CTestSmartDictionary::CreateThreads()
{
   APL_ASSERT( Shutdown == FALSE );
   DWORD dwThreadID;

   cout << "������ ��������� ������: ";
   ifstream FlInWords( "..\\CSmartDictionary_MT.txt" );
   std::copy( std::istream_iterator<std::string>(FlInWords), std::istream_iterator<std::string>(), std::back_inserter(WL) );
   APL_ERROR( !WL.empty() );

   CSmartDictionaryAdapter::TSmartDictionaryPtr Dictionary(CSmartDictionaryAdapter::CreateSmartDictionary(m_DictionaryType));
   Construct(Dictionary.get());   

   ThreadTestSaveData( Dictionary.get(), SampleTestStorage,  WL );

   cout << (unsigned int)SampleTestStorage.WordInfoList.size() << endl;

   for( size_t i = 0; i < ThreadsCout; ++i )
      rghThreads[i] = chBEGINTHREADEX(NULL, 0, TestThread, (PVOID)&rgThreadsData[i], 0, &dwThreadID);   
}
///////////////////////////////////////////////////////////////////////////////

void CTestSmartDictionary::StopThreads()
{
   InterlockedExchange(&Shutdown, TRUE);

   WaitForMultipleObjects(ThreadsCout, rghThreads, TRUE, INFINITE);

   for( size_t i = 0; i < ThreadsCout; ++i )
      CloseHandle(rghThreads[i]);
}
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CTestSmartDictionary::TestThread(PVOID pvParam) 
{
   ThreadsData *pTD = reinterpret_cast<ThreadsData *>(pvParam);

   APL_TRY()
   {
      try
      {
         Console.Write( pTD->ThreadNum, " ������ ����� " );

         while( !pTD->pTSD->Shutdown )
         {        
            Console.Write( pTD->ThreadNum, " ������������ CSmartDictionary" );
            CTestStorage TestStorage;
            CSmartDictionaryAdapter::TSmartDictionaryPtr Dictionary(CSmartDictionaryAdapter::CreateSmartDictionary(pTD->pTSD->m_DictionaryType));
            pTD->pTSD->Construct( Dictionary.get() );

            Console.Write( pTD->ThreadNum, " ��������� CSmartDictionary" );
            pTD->pTSD->ThreadTestSaveData( Dictionary.get(), TestStorage, pTD->pTSD->WL, &pTD->pTSD->Shutdown );

            if( pTD->pTSD->Shutdown == FALSE )
            {
               APL_ERROR( TestStorage.WordInfoList.size()  ==  pTD->pTSD->WL.size() );
               APL_ERROR( TestStorage == pTD->pTSD->SampleTestStorage );
            }
         }

         Console.Write( pTD->ThreadNum, " ��������� �����" );
      }
      catch(...)
      {
         Console.Write( pTD->ThreadNum, " �������� ����������. ��������� �����" );
         InterlockedExchange(&pTD->pTSD->Shutdown, TRUE);
         throw;
      }
   }			
   APL_CATCH()

      return 0;
}
///////////////////////////////////////////////////////////////////////////////

void CTestSmartDictionary::NoThreadTestImpl(CSmartDictionary *pSD, std::istream &InStream, std::ostream &OutStream)
{
   std::string InputStr;
   std::wstring CurWord;
   bool Exist;
   typedef std::list<TWordInfo> TWIList;
   TWIList WIList, WIList2, WIListCompaund;
   SWordInfo WordInfoTmp;
   typedef	std::set<unsigned int> TDictionaryIndexesSet;
   TDictionaryIndexesSet DictionaryIndexesSet;
   CSmartDictionary::SHypothesisInfo HypothesisInfo, HypothesisInfoTmp;
   SWordIndex WI;
   wchar_t Word[SS::Constants::MAX_CHARS_IN_WORD];
   wchar_t WordSource[SS::Constants::MAX_CHARS_IN_WORD];
   TStandartDeterminationWordCheck SDWC;

   while( std::getline(InStream, InputStr )  )
   {
      if( InputStr.empty() )
         continue;

      Convert( InputStr, CurWord );

      bool IsExistWord = pSD->IsExistWord( CurWord.c_str() );
      bool GetWordInfo = pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList);

      APL_ERROR( !IsExistWord || pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList2, true, false) );

      OutStream  << APL_LINE << "��������� � �������: '" << CurWord; 
      Exist =  IsExistWord || GetWordInfo;

      OutStream  <<	
         "' ��������� IsExistWord: " << IsExistWord << 
         " GetWordInfo: " << GetWordInfo << endl;

      if( !Exist )
      {  
         APL_ERROR( WIList.empty() );
         
         //��������� ���������� ��������� �����
         if( pSD->GetCompoundWordInfo(CurWord.c_str(), CurWord.c_str(), false, WIListCompaund) )
         {
            APL_ERROR( !WIListCompaund.empty() );

            OutStream << "���������� ��������� �����:"  << endl;
            Print( OutStream, WIListCompaund/*, pSD->GetAMConverter()*/ );
            OutStream << endl << endl;
         }
         else
         {
            //��������� ���������� ��������������� ���������� ��� ����� � �������� � �������
            pSD->DeterminationWordInfo( CurWord.c_str(), CurWord.c_str(), false ,HypothesisInfo, SDWC );

            if( HypothesisInfo.Empty() )
            {
               OutStream << "�� ������� ������������� ���������� ��������������� ���������� � �����"  << endl;
            }
            else
            {
               OutStream << "������������ ���������� " << HypothesisInfo.m_ConcordanceChars << ":" << endl;  
                        
               Print( OutStream, HypothesisInfo, pSD, pSD->GetAMConverter() );

               HypothesisInfoTmp = HypothesisInfo;

               HypothesisInfoTmp.UniqueIDTypeIDForm();

               OutStream << endl << "���������� IDType:IDForm:" << endl;
               Print( OutStream, HypothesisInfoTmp, pSD, pSD->GetAMConverter() );

               //��������� ���������� IDType
               HypothesisInfo.UniqueIDTypeEndingLen();
               OutStream << endl << "������� � ������� ���������� IDType:EndingLen:" << endl;
               Print( OutStream, HypothesisInfo, pSD, pSD->GetAMConverter() );

               APL_ERROR( !HypothesisInfo.m_FormsInfoList.empty() );

               TDictionaryIndex DI;

               CSmartDictionary::SHypothesisInfo::TFormsInfoList::iterator I;
               for( 
                  I = HypothesisInfo.m_FormsInfoList.begin();
                  I != HypothesisInfo.m_FormsInfoList.end();
               ++I
                  )   
               {
                  pSD->AddNewWord( CurWord, CurWord, I->m_MorphoType.m_MorphoTypeInfo.m_IDType, I->m_EndingLen, DI ); 
                  WI.m_DictIndex = DI;
                  WI.m_IDForm = I->m_MorphoType.m_IDForm;

                  APL_ERROR( pSD->GetWord(&WI, Word) );
                  APL_ERROR( StrCmp(Word, CurWord.c_str()) == 0 );
               }

               APL_ERROR( !pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList, true, false) );
               APL_ERROR( pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList, false, true) );
               Exist = true;
            }
         }
      }

      if( Exist )
      {
         APL_ERROR( !WIList.empty() && !WIList.front().empty() );
         pSD->GetWordSource( WIList.front().front().m_WordIndex.m_DictIndex, WordSource );

         OutStream << endl << "������ �����: '" << ConvertToNarrow(WordSource) << "' GetWordInfo: " << endl;

         Print( OutStream, WIList, pSD->GetAMConverter() );
         OutStream << endl << endl;

         DictionaryIndexesSet.clear();

         for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            for( TWordInfo::iterator J = I->begin(); J != I->end(); ++J )
            {
               APL_ERROR( pSD->GetWordInfo(&J->m_WordIndex, &WordInfoTmp) ); 

               APL_ERROR( Cmp(WordInfoTmp, *J, true) );
               APL_WARNING( Cmp(WordInfoTmp, *J, false) );

               APL_ERROR( pSD->GetWord(&J->m_WordIndex, Word) );
               APL_ERROR( Compare( CurWord.c_str(), Word, J->m_WordIndex.m_DictIndex.GetDictionaryNumber()) );
               APL_WARNING( CurWord == Word );

               unsigned int DictionaryIndex = J->m_WordIndex.m_DictIndex.GetDictionaryIndex();

               //������� �� ������ ������ ��� ���������� IDSource � ������� ������ ����������
               if( DictionaryIndexesSet.find(DictionaryIndex) == DictionaryIndexesSet.end() )
               {
                  APL_ERROR( pSD->GetWordFormsByIDSource(&J->m_WordIndex.m_DictIndex, &WIList2) );
                  APL_ERROR( !WIList2.empty() );

                  //���� ������� �� WIList2 ������ ���� ����� *J
                  bool CaseSensCmp = false, CaseInsensCmp = false;
                  for( TWIList::iterator K = WIList.begin(); K != WIList.end();	++K )
                     for( TWordInfo::iterator L = K->begin(); L != K->end(); ++L )
                     {
                        if( Cmp(*L, *J, true) )
                        {
                           APL_ERROR(!CaseInsensCmp);
                           CaseInsensCmp = true;
                        }

                        if( Cmp(*L, *J, false) )
                        {
                           APL_ERROR(!CaseSensCmp);
                           CaseSensCmp = true;
                        }
                     }

                     APL_ERROR( CaseInsensCmp );
                     APL_WARNING( CaseSensCmp );

                     OutStream <<  "GetWordFormsByIDSource: " << DictionaryIndexDescription( J->m_WordIndex.m_DictIndex ) 
                        << " " << J->m_WordIndex.m_DictIndex.GetId() << endl;

                     Print( OutStream, WIList2/*, pSD->GetAMConverter()*/ );
                     OutStream << endl << endl;

                     DictionaryIndexesSet.insert(DictionaryIndex);
               }
            }
      }

      OutStream  << APL_LINE;
   }
}
///////////////////////////////////////////////////////////////////////////////

void CTestSmartDictionary::ThreadTestSaveData(LockedPtr<CSmartDictionary> pSD, CTestStorage & TS, const TWordsList &WL, volatile LONG *pShutdown /*= 0*/)
{  
   std::wstring CurWord;
   bool Exist;
   typedef std::list<TWordInfo> TWIList;
   TWIList WIList, WIList2;
   SWordInfo WordInfoTmp;
   wchar_t Word[SS::Constants::MAX_CHARS_IN_WORD];
   typedef	std::set<unsigned int> TDictionaryIndexesSet;
   TDictionaryIndexesSet DictionaryIndexesSet;
   CSmartDictionary::SHypothesisInfo HypothesisInfo;
   SWordIndex WI;
   size_t WordCount = 0;
   TStandartDeterminationWordCheck SDWC;
   
   TS.WordInfoList.clear();

   for( TWordsList::const_iterator WLI = WL.begin(); WLI != WL.end() && (pShutdown == 0 || *pShutdown == FALSE); ++WLI, ++WordCount )
   {
      //static int i = 20;  
      //if( !i-- ) break;
     
      CTestStorage::SWordInfo WordInfo;
      
      Convert( *WLI, CurWord );
      WordInfo.Str = CurWord;

      bool IsExistWord = pSD->IsExistWord( CurWord.c_str() );
      bool GetWordInfo = pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList);

      APL_ERROR( !IsExistWord || pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList2, true, false) );

      Exist = IsExistWord || GetWordInfo;
      WordInfo.Exist = Exist;

      if( !Exist )
      {  
         APL_ERROR( WIList.empty() );
         
         //��������� ���������� ��������������� ���������� ��� ����� � �������� � �������
         pSD->DeterminationWordInfo(CurWord.c_str(), CurWord.c_str(), false, HypothesisInfo, SDWC);

         if( !HypothesisInfo.Empty() )
         {
            WordInfo.AutomaticDetermination = true;
            WordInfo.HypothesisInfo = HypothesisInfo;
            
            //��������� ���������� IDType
            HypothesisInfo.UniqueIDTypeEndingLen();

            APL_ERROR( !HypothesisInfo.m_FormsInfoList.empty() );

            TDictionaryIndex DI;
            CSmartDictionary::SHypothesisInfo::TFormsInfoList::iterator I;

            for( 
               I = HypothesisInfo.m_FormsInfoList.begin();
               I != HypothesisInfo.m_FormsInfoList.end();
            ++I
               )   
            {
               pSD->AddNewWord( CurWord, CurWord, I->m_MorphoType.m_MorphoTypeInfo.m_IDType, I->m_EndingLen, DI ); 
               WI.m_DictIndex = DI;
               WI.m_IDForm = I->m_MorphoType.m_IDForm;

               APL_ERROR( pSD->GetWord(&WI, Word) );
               APL_ERROR( StrCmp(Word, CurWord.c_str()) == 0 );
            }
            
            APL_ERROR( !pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList, true, false) );
            APL_ERROR( pSD->GetWordInfo(CurWord.c_str(), CurWord.c_str(), false, &WIList, false, true) );

            Exist = true;
         }
      }

      if( Exist )
      {
         APL_ERROR( !WIList.empty()  );

         WordInfo.WIList = WIList;
         DictionaryIndexesSet.clear();

         for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            for( TWordInfo::iterator J = I->begin(); J != I->end(); ++J )
            {
               APL_ERROR( pSD->GetWordInfo(&J->m_WordIndex, &WordInfoTmp) ); 

               APL_ERROR( Cmp(WordInfoTmp, *J, true) );
               //APL_WARNING( Cmp(WordInfoTmp, *J, false) );

               APL_ERROR( pSD->GetWord(&J->m_WordIndex, Word) );
               APL_ERROR( Compare( CurWord.c_str(), Word, J->m_WordIndex.m_DictIndex.GetDictionaryNumber()) );

               //APL_WARNING( CurWord == Word );

               unsigned int DictionaryIndex = J->m_WordIndex.m_DictIndex.GetDictionaryIndex();

               //������� �� ������ ������ ��� ���������� IDSource � ������� ������ ����������
               if( DictionaryIndexesSet.find(DictionaryIndex) == DictionaryIndexesSet.end() )
               {
                  APL_ERROR( pSD->GetWordFormsByIDSource(&J->m_WordIndex.m_DictIndex, &WIList2) );
                  APL_ERROR( !WIList2.empty() );

                  //���� ������� �� WIList2 ������ ���� ����� *J
                  bool CaseSensCmp = false, CaseInsensCmp = false;
                  for( TWIList::iterator K = WIList.begin(); K != WIList.end();	++K )
                     for( TWordInfo::iterator L = K->begin(); L != K->end(); ++L )
                     {
                        if( Cmp(*L, *J, true) )
                        {
                           APL_ERROR(!CaseInsensCmp);
                           CaseInsensCmp = true;
                        }

                        if( Cmp(*L, *J, false) )
                        {
                           APL_ERROR(!CaseSensCmp);
                           CaseSensCmp = true;
                        }
                     }

                     APL_ERROR( CaseInsensCmp );
                     //APL_WARNING( CaseSensCmp );

                     SWordByIDSource WordByIDSource;

                     WordByIDSource.DI = J->m_WordIndex.m_DictIndex;
                     WordByIDSource.WIList = WIList2;

                     WordInfo.WordByIDSourceList.push_back(WordByIDSource); 

                     DictionaryIndexesSet.insert(DictionaryIndex);
               }
            }
      }

      TS.WordInfoList.push_back( WordInfo );
   }

   APL_ERROR( WordCount == TS.WordInfoList.size() );
   //static int RunCount = 5;
   //APL_ERROR( RunCount-- != 0 );
}
///////////////////////////////////////////////////////////////////////////////

void CTestSmartDictionary::Construct( LockedPtr<CSmartDictionary> pDictionary )
{
   SS::Interface::Core::AMConverter::IAMConverterMorpho  *pAMConverter = 
      (SS::Interface::Core::AMConverter::IAMConverterMorpho*)
      m_pLoadManager->GetInterface(L"./core/linguistics/AMConverter.dll", CLSID_AMConverterMorpho, IID_AMConverterMorpho);


   switch(m_Language)
   {
   case InitData::Languages::English:
      pDictionary->Init(
         m_pDataBase, pAMConverter, L"..\\..\\..\\..\\Database\\MorphoEnglish",  
         DATA_TYPE::NAMES::ednENominalName, DATA_TYPE::NAMES::ednEProperName, DATA_TYPE::NAMES::ednUnknownEng,
         Constants::Dictionary::MIN_MORPHO_RECOGNIZABLE_WORD_LEN_ENG
         );
      break;

   case InitData::Languages::Russian:
      pDictionary->Init(
         m_pDataBase, pAMConverter, L"..\\..\\..\\..\\Database\\MorphoRussian",  
         DATA_TYPE::NAMES::ednRNominalName, DATA_TYPE::NAMES::ednRProperName, DATA_TYPE::NAMES::ednUnknownRus,
         Constants::Dictionary::MIN_MORPHO_RECOGNIZABLE_WORD_LEN_RUS
         );
      break;
   
   default:
      APL_ERROR(false);
   };

}
///////////////////////////////////////////////////////////////////////////////


void CTestSmartDictionary::NoThreadTest( CSmartDictionaryAdapter::TDictionaryTypes DictionaryType/*= CSmartDictionaryAdapter::EStandart*/ )
{
   cout << APL_LINE << "BEGIN CTestSmartDictionary::NoThreadTest" << endl;
   
   cout << "������������ CSmartDictionary" << endl;
   CSmartDictionaryAdapter::TSmartDictionaryPtr Dictionary(CSmartDictionaryAdapter::CreateSmartDictionary(DictionaryType));
   Construct(Dictionary.get());   

   ifstream IStr( "..\\CSmartDictionary.txt" );
   
   cout << "�������� ������������ CBaseDictionary" << endl;

   NoThreadTestImpl( Dictionary.get(), IStr, cout );

   cout << "�������� ������������ ThreadTestSaveData" << endl;

   CTestStorage TS1, TS2;
   TWordsList WL;
   ifstream FlInWords( "..\\CSmartDictionary_MT.txt" );
   std::copy( std::istream_iterator<std::string>(FlInWords), std::istream_iterator<std::string>(), std::back_inserter(WL) );
   APL_ERROR( !WL.empty() );

   CSmartDictionaryAdapter::TSmartDictionaryPtr D1(CSmartDictionaryAdapter::CreateSmartDictionary(DictionaryType)), D2(CSmartDictionaryAdapter::CreateSmartDictionary(DictionaryType));

   Construct(D1.get());   
   Construct(D2.get());   

   ThreadTestSaveData( D1.get(), TS1,  WL );
   ThreadTestSaveData( D2.get(), TS2,  WL );
   APL_ERROR( TS1 == TS2 );

   cout << "END CTestSmartDictionary::NoThreadTest" << endl << APL_LINE;
}

void CTestSmartDictionary::ThreadTest( CSmartDictionaryAdapter::TDictionaryTypes DictionaryType/*= CSmartDictionaryAdapter::EStandart*/ )
{
   cout << APL_LINE << "BEGIN CTestSmartDictionary::ThreadTest" << endl;
   
   CreateThreads();
   getch();
   StopThreads();

   cout << "END CTestSmartDictionary::ThreadTest" << endl << APL_LINE;

}

///////////////////////////////////////////////////////////////////////////////
// class CTestIDictionary
///////////////////////////////////////////////////////////////////////////////
bool operator==( const CTestIDictionary::CTestStorage::SWordInfo &Ob1, const CTestIDictionary::CTestStorage::SWordInfo &Ob2 )
{
   //bool b1 = Ob1.Str == Ob2.Str;
   //bool b2 = Ob1.IsExistResult == Ob2.IsExistResult;
   //bool b3 = Ob1.GetWordInfoResult == Ob2.GetWordInfoResult;
   //bool b4 = Ob1.WIList == Ob2.WIList;
   //bool b5 = Ob1.WordByIDSourceList == Ob2.WordByIDSourceList;
   //
   //if( !b4 )
   //{
   //   cout << APL_LINE << "OB 1:" << endl;
   //   Print( cout, Ob1.WIList );
   //   cout << endl;

   //   cout <<  "OB 2:" << endl;
   //   Print( cout, Ob2.WIList );
   //   cout << endl;
   //}

   return
      Ob1.Str == Ob2.Str &&
      Ob1.IsExistResult == Ob2.IsExistResult &&
      Ob1.GetWordInfoResult == Ob2.GetWordInfoResult &&
      Ob1.WIList == Ob2.WIList &&
      Ob1.WordByIDSourceList == Ob2.WordByIDSourceList;
}
///////////////////////////////////////////////////////////////////////////////

bool operator==( const CTestIDictionary::CTestStorage &Ob1, const CTestIDictionary::CTestStorage &Ob2 )
{
   return
      Ob1.WordInfoList == Ob2.WordInfoList;
}

CTestIDictionary::CTestIDictionary( ILoadManager *pLoadManager ): 
   Shutdown(FALSE), m_pLoadManager(pLoadManager)
{
   for( size_t i = 0; i < ThreadsCout; ++i )
   {
      rgThreadsData[i].pTSD = this;
      rgThreadsData[i].ThreadNum = (int)i;
      rghThreads[i] = 0;
   }

   std::srand( (unsigned)time( NULL ) );
}
///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::CreateThreads()
{
   APL_ASSERT( Shutdown == FALSE );
   DWORD dwThreadID;

   cout << "������ ��������� ������ : ";
   ifstream FlInWords( "..\\IDictionary_IMorphologyAnalyser_MT.txt" );
   std::copy( std::istream_iterator<std::string>(FlInWords), std::istream_iterator<std::string>(), std::back_inserter(WL) );
   APL_ERROR( !WL.empty() );
   cout << ".";

   {
      CLoadManagerCreater::TAutoPtr pLM1 = m_LoadManagerCreater.Create();
      IDictionary *pD1 = GetIDictionary(pLM1.get());
      ThreadTestSaveData( pD1->GetMorphologyAnalyser(), SampleTestStorage,  WL );
      cout << ".";

      //������ ��� �.�. ���������� ��� �� ����� ����� ���� ��������� � �������
      //���� ��� �� ��� �� ������ ��� ������ ����� �������� ������ �� � ��� �������
      CLoadManagerCreater::TAutoPtr pLM2 = m_LoadManagerCreater.Create();
      IDictionary *pD2 = GetIDictionary(pLM2.get());
      ThreadTestSaveData( pD2->GetMorphologyAnalyser(), SampleTestStorage,  WL ); 
      cout << ".";
   }

   cout << (unsigned int)SampleTestStorage.WordInfoList.size() << endl;
   
   for( size_t i = 0; i < ThreadsCout; ++i )
      rghThreads[i] = chBEGINTHREADEX(NULL, 0, TestThread, (PVOID)&rgThreadsData[i], 0, &dwThreadID);   
}
///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::StopThreads()
{
   InterlockedExchange(&Shutdown, TRUE);

   WaitForMultipleObjects(ThreadsCout, rghThreads, TRUE, INFINITE);

   for( size_t i = 0; i < ThreadsCout; ++i )
      CloseHandle(rghThreads[i]);
}
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CTestIDictionary::TestThread(PVOID pvParam) 
{
   ThreadsData *pTD = reinterpret_cast<ThreadsData *>(pvParam);

   APL_TRY()
   {
      try
      {
         Console.Write( pTD->ThreadNum, " ������ ����� " );

         while( !pTD->pTSD->Shutdown )
         {        
            Console.Write( pTD->ThreadNum, " ������������ IDictionary" );
            CTestStorage TestStorage;
            
            IDictionary *pDictionary;
            CLoadManagerCreater::TAutoPtr pLM;
            
            {
               typedef ClassLevelLockable<CTestIDictionary> TMutex;
               TMutex m_Mutex;
               TMutex::Lock Guard(m_Mutex);
 
               pLM = pTD->pTSD->m_LoadManagerCreater.Create();
               pDictionary = GetIDictionary(pLM.get());
            }
            
            if( pTD->ThreadNum + WriteThreadsCount < ThreadsCout )
            {
               Console.Write( pTD->ThreadNum, " ��������� IDictionary" );
               pTD->pTSD->ThreadTestSaveData( pDictionary->GetMorphologyAnalyser(), TestStorage, pTD->pTSD->WL, &pTD->pTSD->Shutdown );

               if( pTD->pTSD->Shutdown == FALSE )
               {
                  APL_ERROR( TestStorage.WordInfoList.size()  ==  pTD->pTSD->WL.size() );
                  APL_ERROR( TestStorage == pTD->pTSD->SampleTestStorage );
               }
            }
            else
            {
               switch(std::rand() % 3)
               {
               case 0:
                  Console.Write( pTD->ThreadNum, " ��������� ILoad::Load" );
                  pDictionary->GetLoader()->Load();
               break;
               case 1:
                  Console.Write( pTD->ThreadNum, " ��������� ILoad::ReLoad" );
                  pDictionary->GetLoader()->ReLoad();
               break;
               case 2:
                  Console.Write( pTD->ThreadNum, " ��������� ILoad::ToBinary" );
                  //pDictionary->GetLoader()->ToBinary();
               break;
               };
               
               for( int i = 0; i < 10 && !pTD->pTSD->Shutdown; ++i )
                  Sleep(1000);
            }
         }

         Console.Write( pTD->ThreadNum, " ��������� �����" );
      }
      catch(...)
      {
         Console.Write( pTD->ThreadNum, " �������� ����������. ��������� �����" );
         InterlockedExchange(&pTD->pTSD->Shutdown, TRUE);
         throw;
      }
   }			
   APL_CATCH()

      return 0;
}

///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::ThreadTest()
{
   cout << APL_LINE << "BEGIN CTestIDictionary::ThreadTest" << endl;

   CreateThreads();
   getch();
   StopThreads();

   cout << "END CTestIDictionary::ThreadTest" << endl << APL_LINE;
}

void CTestIDictionary::NoThreadTestImpl(IMorphologyAnalyser *pMA, CUnicodeFileReader &FR, std::ostream &OutStream, IOneRoot *pOneRoot /*= 0*/)
{
   std::wstring CurWord;
   bool Exist;
   typedef std::list<TWordInfo> TWIList;
   TWIList WIList, WIList2;
   SWordInfo WordInfoTmp;
   wchar_t Word[SS::Constants::MAX_CHARS_IN_WORD];
   wchar_t WordSource[SS::Constants::MAX_CHARS_IN_WORD];
   typedef	std::set<unsigned int> TDictionaryIndexesSet;
   TDictionaryIndexesSet DictionaryIndexesSet;
   CSmartDictionary::SHypothesisInfo HypothesisInfo;
   SWordIndex WI;
   TMorphoInfo MorphoInfo; 
   TSpecialMorpho SpecialMorpho;
   CMorphoFeature MorphoFeature;
   
   CMALanguagesManager *pLangManager = APL_DYNAMIC_CAST( CMALanguagesManager *, pMA );
   IAMConverterMorpho *pAMConverter = pLangManager->GetAMConverter();
   int iMorphoInfo;
   int iPartOfSpeech;

   APL_ERROR( !FR.Eof() );

   while( !FR.Eof()  )
   {
      FR.Read(CurWord, CUnicodeFileReader::SNewLineCharacter()); 
      
      if( CurWord.empty()  )
         continue;

      bool IsExistWord = pMA->IsExistWord( CurWord.c_str() );
      bool GetWordInfo = pMA->GetWordInfo( CurWord.c_str(), &WIList, efzOnlySearch );

      APL_ERROR( !IsExistWord || pMA->GetWordInfo(CurWord.c_str(), &WIList2, efzBaseAndAbbreviation) );

      OutStream  << APL_LINE << "��������� � �������: '" << CurWord; 
      Exist =  IsExistWord || GetWordInfo;

      OutStream  <<	
         "' ��������� IsExistWord: " << IsExistWord << 
         " GetWordInfo(efzOnlySearch): " << GetWordInfo << endl;

      if( !Exist )
      {  
         APL_ERROR( WIList.empty()  );

         //��������� ����� � �������
         APL_ERROR( pMA->GetWordInfo(CurWord.c_str(), &WIList, efzFullAddNewWords) )
         APL_ERROR( !WIList.empty() );
         APL_ERROR( pMA->GetWordInfo(CurWord.c_str(), &WIList2, efzOnlySearch) );

         //������� �������� APL_ERROR( WIList == WIList2 ); ������, �.�. ������ ����� ���� �� ������� �������������

         bool ListCmp = true;

         if( WIList.size() != WIList2.size() )
            ListCmp = false;

         for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            if( std::find(WIList2.begin(), WIList2.end(), *I) == WIList.end() )
               ListCmp = false;

         if( !ListCmp )
         {
            OutStream << "WIList: " << endl;
            Print( OutStream, WIList );
            OutStream << endl << endl;

            OutStream << "WIList2: " << endl;
            Print( OutStream, WIList2 );
            OutStream << endl << endl;
         }

         APL_ERROR( ListCmp );

         Exist = true;
      }

      if( Exist )
      {
         APL_ERROR( !WIList.empty() && !WIList.front().empty() );
         pMA->GetWordSource( WIList.front().front().m_WordIndex.m_DictIndex, WordSource );

         OutStream << "������ �����: '" << ConvertToNarrow(WordSource) << "' GetWordInfo: " << endl;
         Print( OutStream, WIList, pAMConverter );
         OutStream << endl << endl;

#if 0
         //�� ����� ��������� ������ ���� ������� ���������� ����������� ����������
         if( 
            pMA->GetAnalyseParams() != 0 && 
            (pMA->GetAnalyseParams()->GetAnalyseMod() == eamQuery || pMA->GetAnalyseParams()->GetAnalyseMod() == eamRTFQuery)
         )
            continue;
#endif

         DictionaryIndexesSet.clear();

         if( pOneRoot )
         {
            typedef std::list<TDictionaryIndex> TDIList;
            
            TWIList OneRoots;
            TWIList::value_type OneRootsValue;
            TDIList DIList;

            for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            {              
               for( TWordInfo::iterator J = I->begin(); J != I->end(); ++J )
               { 
                  if( !pOneRoot->SetDictionaryIndex(J->m_WordIndex.m_DictIndex) )
                     continue;

                  pOneRoot->Get( &DIList );

                  for( TDIList::iterator K = DIList.begin(); K != DIList.end(); ++K )
                  {
                     SWordInfo WI;
                     SWordIndex WordIndex;
                     
                     WordIndex.m_DictIndex = *K;
                     WordIndex.m_IDForm = J->m_WordIndex.m_IDForm;

                     if( !pMA->GetWordInfo( &WordIndex, &WI ) )
                     {
                        WI = *J;
                        WI.m_WordIndex.m_DictIndex = *K;
                        WI.m_wWord = L"<GetWordInfo ERROR>";
                     }

                     OneRootsValue.push_back(WI);
                  } 
               }
               
               OneRoots.push_back( TWIList::value_type() );
               OneRoots.back().splice( OneRoots.back().end(), OneRootsValue );
            }

            OutStream <<  "OneRoots Values: " << endl;

            Print( OutStream, OneRoots );
            OutStream << endl << endl;
         }

         for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            for( TWordInfo::iterator J = I->begin(); J != I->end(); ++J )
            {
               APL_ERROR( pMA->GetWordInfo(&J->m_WordIndex, &WordInfoTmp) ); 

               APL_ERROR( Cmp(WordInfoTmp, *J, true) );
               APL_WARNING( Cmp(WordInfoTmp, *J, false) );

               APL_ERROR( pMA->GetWord(&J->m_WordIndex, Word) );
               APL_ERROR( Compare( CurWord.c_str(), Word, J->m_WordIndex.m_DictIndex.GetDictionaryNumber()) );
               APL_WARNING( CurWord == Word );

               pMA->GetMorphoInfoByIDType( J->m_WordIndex.m_DictIndex.GetDictionaryNumber(), J->m_MorphoTypeInfo.m_IDType, J->m_WordIndex.m_IDForm, &MorphoInfo, &SpecialMorpho );

               APL_ERROR(  
                  (J->m_MorphoTypeInfo.m_IDType == 0 && J->m_WordIndex.m_IDForm == 0) ||
                  (MorphoInfo == 0 && SpecialMorpho == 0) ||
                  (J->m_MorphoTypeInfo.m_MorphoInfo == MorphoInfo && J->m_SpecialMorpho == SpecialMorpho) 
               );

               unsigned int DictionaryIndex = J->m_WordIndex.m_DictIndex.GetDictionaryIndex();

               //������� �� ������ ������ ��� ���������� IDSource � ������� ������ ����������
               if( DictionaryIndexesSet.find(DictionaryIndex) == DictionaryIndexesSet.end() )
               {
                  APL_ERROR( pMA->GetWordFormsByIDSource(&J->m_WordIndex.m_DictIndex, &WIList2) );
                  APL_ERROR( !WIList2.empty() );

                  //���� ������� �� WIList2 ������ ���� ����� *J
                  bool CaseSensCmp = false, CaseInsensCmp = false;
                  for( TWIList::iterator K = WIList.begin(); K != WIList.end();	++K )
                     for( TWordInfo::iterator L = K->begin(); L != K->end(); ++L )
                     {
                        if( Cmp(*L, *J, true) )
                        {
                           APL_ERROR(!CaseInsensCmp);
                           CaseInsensCmp = true;
                        }

                        if( Cmp(*L, *J, false) )
                        {
                           APL_ERROR(!CaseSensCmp);
                           CaseSensCmp = true;
                        }
                     }

                  APL_ERROR( CaseInsensCmp );
                  APL_WARNING( CaseSensCmp );

                  OutStream <<  "GetWordFormsByIDSource: " << DictionaryIndexDescription(J->m_WordIndex.m_DictIndex) 
                     << " " << J->m_WordIndex.m_DictIndex.GetId() << endl;

                  Print( OutStream, WIList2 );
                  OutStream << endl << endl;

                  DictionaryIndexesSet.insert(DictionaryIndex);

                  //��������� ����������������� IAMConverterMorpho
                  SWordInfo &WordInfoRef = *J;

                  iMorphoInfo = WordInfoRef.m_MorphoTypeInfo.m_MorphoInfo;
                  iPartOfSpeech = WordInfoRef.m_SpecialMorpho;

                  pAMConverter->EnCode( 
                     WordInfoRef.m_WordIndex.m_DictIndex.GetDictionaryNumber(),
                     WordInfoRef.m_MorphoTypeInfo.m_MorphoInfo,
                     WordInfoRef.m_SpecialMorpho,
                     &MorphoFeature
                     );

                  iMorphoInfo = std::numeric_limits<int>::max();
                  iPartOfSpeech = std::numeric_limits<int>::max();

#if 0
                  pAMConverter->Code( 
                     WordInfoRef.m_WordIndex.m_DictIndex.GetDictionaryNumber(),
                     &MorphoFeature,
                     &iMorphoInfo,
                     &iPartOfSpeech
                     );
                  
                  APL_ERROR( 
                     iMorphoInfo == WordInfoRef.m_MorphoTypeInfo.m_MorphoInfo 
                     && WordInfoRef.m_SpecialMorpho == iPartOfSpeech 
                  );
#endif

               }
            }
      }

      OutStream  << APL_LINE;
   }
}
///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::ThreadTestSaveData(IMorphologyAnalyser *pMA, CTestStorage & TS, const TWordsList &WL, volatile LONG *pShutdown /*= 0*/)
{  
   std::wstring CurWord;
   bool Exist;
   typedef std::list<TWordInfo> TWIList;
   TWIList WIList, WIList2;
   SWordInfo WordInfoTmp;
   wchar_t Word[SS::Constants::MAX_CHARS_IN_WORD];
   typedef	std::set<unsigned int> TDictionaryIndexesSet;
   TDictionaryIndexesSet DictionaryIndexesSet;
   CSmartDictionary::SHypothesisInfo HypothesisInfo;
   SWordIndex WI;
   size_t WordCount = 0;
   TMorphoInfo MorphoInfo; 
   TSpecialMorpho SpecialMorpho;

   TS.WordInfoList.clear();

   for( TWordsList::const_iterator WLI = WL.begin(); WLI != WL.end() && (pShutdown == 0 || *pShutdown == FALSE); ++WLI, ++WordCount )
   {
      //static int i = 20;  
      //if( !i-- ) break;

      CTestStorage::SWordInfo WordInfo;

      Convert( *WLI, CurWord );
      WordInfo.Str = CurWord;

      bool IsExistWord = pMA->IsExistWord( CurWord.c_str() );
      bool GetWordInfo = pMA->GetWordInfo(CurWord.c_str(), &WIList, efzOnlySearch);

      APL_ERROR( !IsExistWord || pMA->GetWordInfo(CurWord.c_str(), &WIList2, efzBaseAndAbbreviation) );

      Exist = IsExistWord || GetWordInfo;
      WordInfo.IsExistResult = IsExistWord;
      WordInfo.GetWordInfoResult = GetWordInfo;

      if( !Exist )
      {  
         APL_ERROR( WIList.empty()  );

         //��������� ����� � �������
         APL_ERROR( pMA->GetWordInfo(CurWord.c_str(), &WIList, efzFullAddNewWords) )
            APL_ERROR( !WIList.empty() );
         APL_ERROR( pMA->GetWordInfo(CurWord.c_str(), &WIList2, efzOnlySearch) );

         //������� �������� APL_ERROR( WIList == WIList2 ); ������, �.�. ������ ����� ���� �� ������� �������������

         bool ListCmp = true;

         if( WIList.size() != WIList2.size() )
            ListCmp = false;

         for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            if( std::find(WIList2.begin(), WIList2.end(), *I) == WIList.end() )
               ListCmp = false;

         APL_ERROR( ListCmp );

         Exist = true;
      }

      if( Exist )
      {
         APL_ERROR( !WIList.empty()  );

         WordInfo.WIList = WIList;

         DictionaryIndexesSet.clear();

         for( TWIList::iterator I = WIList.begin(); I != WIList.end();	++I )
            for( TWordInfo::iterator J = I->begin(); J != I->end(); ++J )
            {
               APL_ERROR( pMA->GetWordInfo(&J->m_WordIndex, &WordInfoTmp) ); 

               APL_ERROR( Cmp(WordInfoTmp, *J, true) );
               //APL_WARNING( Cmp(WordInfoTmp, *J, false) );

               APL_ERROR( pMA->GetWord(&J->m_WordIndex, Word) );
               APL_ERROR( Compare( CurWord.c_str(), Word, J->m_WordIndex.m_DictIndex.GetDictionaryNumber()) );
               //APL_WARNING( CurWord == Word );

               pMA->GetMorphoInfoByIDType( J->m_WordIndex.m_DictIndex.GetDictionaryNumber(), J->m_MorphoTypeInfo.m_IDType, J->m_WordIndex.m_IDForm, &MorphoInfo, &SpecialMorpho );

               APL_ERROR(  
                  (J->m_MorphoTypeInfo.m_IDType == 0 && J->m_WordIndex.m_IDForm == 0) ||
                  (MorphoInfo == 0 && SpecialMorpho == 0) ||
                  (J->m_MorphoTypeInfo.m_MorphoInfo == MorphoInfo && J->m_SpecialMorpho == SpecialMorpho) 
               );

               unsigned int DictionaryIndex = J->m_WordIndex.m_DictIndex.GetDictionaryIndex();

               //������� �� ������ ������ ��� ���������� IDSource � ������� ������ ����������
               if( DictionaryIndexesSet.find(DictionaryIndex) == DictionaryIndexesSet.end() )
               {
                  APL_ERROR( pMA->GetWordFormsByIDSource(&J->m_WordIndex.m_DictIndex, &WIList2) );
                  APL_ERROR( !WIList2.empty() );

                  //���� ������� �� WIList2 ������ ���� ����� *J
                  bool CaseSensCmp = false, CaseInsensCmp = false;
                  for( TWIList::iterator K = WIList.begin(); K != WIList.end();	++K )
                     for( TWordInfo::iterator L = K->begin(); L != K->end(); ++L )
                     {
                        if( Cmp(*L, *J, true) )
                        {
                           APL_ERROR(!CaseInsensCmp);
                           CaseInsensCmp = true;
                        }

                        if( Cmp(*L, *J, false) )
                        {
                           APL_ERROR(!CaseSensCmp);
                           CaseSensCmp = true;
                        }
                     }

                     APL_ERROR( CaseInsensCmp );
                     //APL_WARNING( CaseSensCmp );

                     SWordByIDSource WordByIDSource;

                     WordByIDSource.DI = J->m_WordIndex.m_DictIndex;
                     WordByIDSource.WIList = WIList2;

                     WordInfo.WordByIDSourceList.push_back(WordByIDSource); 

                     DictionaryIndexesSet.insert(DictionaryIndex);
               }
            }
      }

      TS.WordInfoList.push_back( WordInfo );
   }

   APL_ERROR( WordCount == TS.WordInfoList.size() );
   //static int RunCount = 5;
   //APL_ERROR( RunCount-- != 0 );

   //if( ++RunCount % 2 )
   //{
   //   TS.WordInfoList.back(). = L"TTT";
   //}
}
///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::NoThreadTest()
{
   cout << APL_LINE << "BEGIN CTestIDictionary::NoThreadTest" << endl;

   cout << "��������� ����� IDictionary" << endl;
   IDictionary *pDictionary = GetIDictionary(m_pLoadManager);
   
   CUnicodeFileReader FR( L"..\\IDictionary_IMorphologyAnalyser.txt" );

   cout << "�������� ������������ IDictionary" << endl;

   NoThreadTestImpl( pDictionary->GetMorphologyAnalyser(), FR, cout, pDictionary->GetOneRoot() );
   pDictionary->GetMorphologyAnalyser()->NextText();  //����� �������� ���

   cout << "�������� ������������ ThreadTestSaveData" << endl;

   CTestStorage TS1, TS2;
   TWordsList WL;
   ifstream FlInWords( "..\\IDictionary_IMorphologyAnalyser_MT.txt" );
   std::copy( std::istream_iterator<std::string>(FlInWords), std::istream_iterator<std::string>(), std::back_inserter(WL) );
   APL_ERROR( !WL.empty() );

#if 0
{
   CLoadManagerCreater::TAutoPtr pLM1 = m_LoadManagerCreater.Create();
   CLoadManagerCreater::TAutoPtr pLM2 = m_LoadManagerCreater.Create();

   IDictionary *pD1 = GetIDictionary(pLM1.get());
   IDictionary *pD2 = GetIDictionary(pLM2.get());

   ThreadTestSaveData( pD1->GetMorphologyAnalyser(), TS1,  WL );
   ThreadTestSaveData( pD2->GetMorphologyAnalyser(), TS2,  WL );
   APL_ERROR( TS1 == TS2 );
}
#endif

#if 0
   cout << "��������� BackUpBase" << endl;
   SS::Interface::Core::ResourceManagers::IBaseManager* pBaseManager;

   pBaseManager = (SS::Interface::Core::ResourceManagers::IBaseManager*)
      m_pLoadManager->GetInterface(L"./core/linguistics/LingvoBaseManager.dll", CLSID_LinguoBaseManager, IID_BaseManager);

   APL_ERROR(pBaseManager != 0);
   APL_ERROR( pBaseManager->BackUpBase(_T("c:\\!MY_DOCS\\BACKUP2")) == ERROR_SUCCESS );
#endif


#if 0
   cout << "��������� ClearBase" << endl;
   SS::Interface::Core::ResourceManagers::IBaseManager* pBaseManager;

   pBaseManager = (SS::Interface::Core::ResourceManagers::IBaseManager*)
      m_pLoadManager->GetInterface(L"./core/linguistics/LingvoBaseManager.dll", CLSID_LinguoBaseManager, IID_BaseManager);

   APL_ERROR(pBaseManager != 0);
   
   APL_ERROR( pBaseManager->ClearBase() == S_OK );
#endif

   cout << "END CTestIDictionary::NoThreadTest" << endl << APL_LINE;
}
///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::TestFullWordsIDictionary( std::ofstream &OutStream )
{
   cout << APL_LINE << "BEGIN CTestIDictionary::TestFullWordsIDictionary " << GetTimeStampString() << endl;

   cout << "��������� ����� IDictionary" << endl;
   IDictionary *pDictionary = GetIDictionary(m_pLoadManager);
   APL_ERROR(pDictionary != 0);

   wstring Ext[] = { _T("rpts") };
   wstring Path( L"..\\" );

   wstring *ExtFirst = Ext;
   wstring *ExtLast = Ext + APL_ARRSIZE(Ext);

   CDirectoryFileList DirectoryFileList( Path , ExtFirst, ExtLast );
   unsigned int WordsCount;
   unsigned int ErrorsCount;
   unsigned int MorphoFeatureErrorsCount;

   string CurLine;
   typedef std::list<SS::Dictionary::Types::TWordInfo> TWIList;
   TWIList DictData, FileData;
   std::list<string> LogStrings;
   string PrevString;
   string CurString;
   wstring SearchString;

   SWordInfo WordInfo;
   int IDSource, DictNumber;

   CMorphoFeature MorphoFeature;
   CMALanguagesManager *pLangManager = APL_DYNAMIC_CAST( CMALanguagesManager *, pDictionary->GetMorphologyAnalyser() );
   IAMConverterMorpho *pAMConverter = pLangManager->GetAMConverter();
   int iMorphoInfo;
   int iPartOfSpeech;

   cout << "�������� ������������" << endl;
   while( DirectoryFileList.Next() )
   {
      WordsCount = 0;
      ErrorsCount = 0;
      MorphoFeatureErrorsCount = 0;
      FileData.clear();
      LogStrings.clear();

      OutStream << "�������� ���������: " <<
         DirectoryFileList.GetDir() + DirectoryFileList.GetFile() << endl;

      cout << "�������� ���������: " <<
         DirectoryFileList.GetDir() + DirectoryFileList.GetFile() << endl;  

      ifstream flIn(Convert(DirectoryFileList.GetDir() + DirectoryFileList.GetFile(), string()).c_str());

      CFileProgres<> PD( flIn );

      while( getline(flIn, CurLine) && !CurLine.empty() )
      {
         std::stringstream Stream( CurLine );

         Stream 
            >> CurString 
            >> DictNumber
            >> IDSource
            >> WordInfo.m_MorphoTypeInfo.m_IDType
            >> WordInfo.m_WordIndex.m_IDForm
            >> WordInfo.m_MorphoTypeInfo.m_MorphoInfo
            >> WordInfo.m_SpecialMorpho;

         Convert( CurString, WordInfo.m_wWord );
         WordInfo.m_WordIndex.m_DictIndex.SetId(IDSource); 
         WordInfo.m_WordIndex.m_DictIndex.SetDictionaryNumber((TDictNumber)DictNumber); 

         if( WordsCount == 0 )
            PrevString = CurString;

         if( StrCmpIA(PrevString.c_str(), CurString.c_str()) != 0 )
         {
            //��������� ������
            FileData.sort(SWordInfoPredLess());

            Convert(PrevString, SearchString);

            pDictionary->GetMorphologyAnalyser()->GetWordInfo(SearchString.c_str(), &DictData,  efzBaseDictionary);

            DictData.sort(SWordInfoPredLess());

            TWIList::iterator I, J;
            TWIList::value_type::iterator L, M;

            for( 
               I = FileData.begin(), J = DictData.begin(); 
               I != FileData.end() && J != DictData.end(); 
            ++I, ++J
               )
            {
               for( 
                  L = I->begin(), M = J->begin();
                  L != I->end() && M != J->end() && Cmp( *L, *M, true );
               ++L, ++M
                  )
               { 
                  //��������� ����������������� IAMConverterMorpho
                  SWordInfo &WordInfoRef = *L;
                  bool ISException = false;

                  try
                  {
                     iMorphoInfo = WordInfoRef.m_MorphoTypeInfo.m_MorphoInfo;
                     iPartOfSpeech = WordInfoRef.m_SpecialMorpho;
                     
                     pAMConverter->EnCode( 
                        WordInfoRef.m_WordIndex.m_DictIndex.GetDictionaryNumber(),
                        iMorphoInfo,
                        iPartOfSpeech,
                        &MorphoFeature
                        );

                     iMorphoInfo = std::numeric_limits<int>::max();
                     iPartOfSpeech = std::numeric_limits<int>::max();

                     //pAMConverter->Code( 
                     //   WordInfoRef.m_WordIndex.m_DictIndex.GetDictionaryNumber(),
                     //   &MorphoFeature,
                     //   &iMorphoInfo,
                     //   &iPartOfSpeech
                     //   );
                  }
                  catch(...)
                  {
                     ISException = true;
                  }

                  if( 
                     ISException /*||
                     iMorphoInfo != WordInfoRef.m_MorphoTypeInfo.m_MorphoInfo || 
                     WordInfoRef.m_SpecialMorpho != iPartOfSpeech*/ 
                     )
                  {
                     OutStream << APL_LINE;
                     OutStream << (ISException ? "�������� ���������� � AMConverter:" : "������� ������ � AMConverter:") << endl;
                     Print( OutStream, WordInfoRef );
                     OutStream << APL_LINE << endl;
                     ++MorphoFeatureErrorsCount;
                  }
               }

               if( L != I->end() || M != J->end() )
                  break;
            }

            if( I != FileData.end() || J != DictData.end() )
            {
               //������������ �� �����, ����������� �� ������������ ��� �� ����!
               OutStream << APL_LINE;
               OutStream << "������� �������������� �����������:" << endl;

               for( std::list<string>::iterator I = LogStrings.begin(); I != LogStrings.end(); ++I )
               {
                  OutStream << *I << endl;
               }

               OutStream << "������ � �����:" << endl;
               Print( OutStream, FileData );

               OutStream << endl;

               OutStream << "������ � �������:" << endl;

               Print( OutStream, DictData );
               OutStream << endl;

               OutStream << APL_LINE << endl;
               ++ErrorsCount;
            }

            FileData.clear();
            LogStrings.clear();

            PrevString = CurString;   
         }

         FileData.push_back( TWIList::value_type() );
         FileData.back().push_back( WordInfo );

         LogStrings.push_back(CurLine);

         ++WordsCount;

         PD.Update();
      }

      cout << endl;
      OutStream << "���������� ����:                     " << WordsCount << endl;
      cout      << "���������� ����:                     " << WordsCount << endl;
      OutStream << "�� ��� ������ ����:                  " << ErrorsCount << endl;
      cout      << "�� ��� ������ ����:                  " << ErrorsCount << endl;
      OutStream << "�� ��� ������ MorphoFeature ����:    " << MorphoFeatureErrorsCount << endl;
      cout      << "�� ��� ������ MorphoFeature ����:    " << MorphoFeatureErrorsCount << endl;

      OutStream << APL_LINE;
      cout << APL_LINE;
   }

   cout << "END CTestIDictionary::TestFullWordsIDictionary " << GetTimeStampString() << endl << APL_LINE;
}
///////////////////////////////////////////////////////////////////////////////

void CTestIDictionary::TestGetWordForIUnit()
{
   cout << APL_LINE << "BEGIN CTestIDictionary::TestGetWordForIUnit" << endl;
   
   cout << "��������� ����� IDictionary" << endl;
   IMorphologyAnalyser *pMA = GetIDictionary(m_pLoadManager)->GetMorphologyAnalyser();

   CUnicodeFileReader FR( L"..\\IDictionary_IMorphologyAnalyser_IUnit.txt" );
   std::wstring CurWord;
   std::wstring Xml;
   std::wstringstream Stream;

   cout << "�������� ������������ IDictionary" << endl;

   SS::Interface::Core::BlackBox::IBlackBoxTextStorage *pBlackBoxTextStorage =
      (SS::Interface::Core::BlackBox::IBlackBoxTextStorage *)
      m_pLoadManager->GetInterface(L"./core/linguistics/BlackBox.dll", CLSID_BlackBoxTextStorage, IID_BlackBoxTextStorage);

   APL_ERROR( pBlackBoxTextStorage != 0 );

   IText *pText = pBlackBoxTextStorage->CreateText();
   IParagraph *pParagraph = pBlackBoxTextStorage->CreateParagraph();
   ISentence *pSentence = pBlackBoxTextStorage->CreateSentence();
   IUnit *pUnit = pBlackBoxTextStorage->CreateUnit();

   pSentence->AddUnit( pUnit );
   pParagraph->AddSentence( pSentence );
   pText->AddParagraph( pParagraph );

   Stream << L"<?xml version='1.0' ?>\n";
   Stream << L"<?xml-stylesheet type=\"text/xsl\" href=\"../../../../Sources/Core/Dictionaries/ForTest/TestGetWordForIUnit.xslt\"?>\n";

   Stream << L"<TestGetWordForIUnit>";
   while( !FR.Eof()  )
   {
      FR.Read(CurWord, CUnicodeFileReader::SNewLineCharacter()); 

      if( CurWord.empty()  )
         continue;
      
      IIndex *pIndex = pUnit->GetFirstIndex();

      for(;pIndex != 0; pIndex = pUnit->GetFirstIndex())
         pIndex->ReleaseIndex();
      
      pUnit->ClearUnit();

      pUnit->SetWord( (CurWord + L" <NOT CHANGE>").c_str() );
//      pMA->GetWordInfo( CurWord.c_str(), pUnit, efzFullAddNewWordsCompound );  
      pText->GetXML( &Xml );

      Stream << L"<Test word=\"" << CurWord << L"\">" << Xml << L"</Test>";
   }
   Stream << L"</TestGetWordForIUnit>";

   basic_ofstream<CHAR> FileStream ( "TestGetWordForIUnitResult.xml", ios::binary );  
   FileStream << CHAR( 0xFF ) << CHAR(0xFE);
   WriteUnicode( FileStream, Stream.str() );

   cout << "������ ���� TestGetWordForIUnitResult.xml" << endl;
   cout << "END CTestIDictionary::TestGetWordForIUnit" << endl << APL_LINE;
   ShellExecute( GetActiveWindow(), _T("open"), _T("iexplore.exe"), (GetExeDirPath() + _T("TestGetWordForIUnitResult.xml")).c_str(), NULL, SW_SHOWNORMAL );
}



} //namespace Dictionary
} //namespace UnitTests
} //namespace SS

#endif //_SS_UNITTESTS
