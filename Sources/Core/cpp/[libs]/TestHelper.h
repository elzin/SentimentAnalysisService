/** 
   ������ ������������� ��������� ������� ���������� ������ � ��������
*/
#ifndef TestHelper_H
#define TestHelper_H

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "Threads.h"


//������ ������ ��� ��������� ��������� ������
#define APL_LINE "-------------------------------------------------------------------------------\n"

//���� arg ����� ����� � ������� ���������� � ������ TSilentException
#define APL_ERROR( arg )	if( !(arg) ){ \
	std::stringstream Stream__; \
   Stream__ << APL_LINE;  \
	Stream__ << "   APL_ERROR( " ## #arg ## " )\n"; \
	Stream__ << "   " ## __FILE__ ## ", " << __LINE__ << std::endl;  \
	Stream__ << APL_LINE;  \
   std::cout << Stream__.str(); \
   throw TSilentException(); \
}

//���� ��� � APL_ERROR, �� �� ������ ����������
#define APL_WARNING( arg )	if( !(arg) ){ \
   std::stringstream Stream__; \
   Stream__ << APL_LINE;  \
   Stream__ << "   APL_WARNING( " ## #arg ## " )\n"; \
   Stream__ << "   " ## __FILE__ ## ", " << __LINE__ << std::endl;  \
   Stream__ << APL_LINE;  \
   std::cout << Stream__.str(); \
}

#define APL_TRY() SS_TRY { try
#define APL_CATCH()\
catch (const TSilentException &) \
{}   \
catch( const std::exception &e )   \
{ \
	std::cout << "std::exception: " << e.what() << std::endl; \
	throw;  \
} }  \
SS_CATCH(L"")


namespace SS { namespace Lib {

//��������� ������������� ��������� ����� ������� �� �� � ������� ������������ ������ �������
class TConsoleAutoStop
{
public:
	~TConsoleAutoStop()
	{
		std::cout << "\nPress any Key...";
		while( kbhit() ) getch();

      getch();
	}
};

///////////////////////////////////////////////////////////////////////////////
// ��������� ���� FilePath �� ���������� � ���� FilePath ����������� ����
// ��������� ����� ��� ����������. ������� ������������� ��� ������������ �����, 
// � �������� �������� ��������, ������� � ������� ��������� ���� FilePath � 
// ������� ��� ������ �������� ������ DEBUG, ���� ��������� ������ DEBUG � 
// RELEASE ���� �� ���������.
// ��������� ������������ �������� ����� (��� bat ����� ��������� exit <���>)
// � ���� ��� != 0 �� ������ ����������
///////////////////////////////////////////////////////////////////////////////
void ExecutePreRunFile( TCHAR *FilePath );

///////////////////////////////////////////////////////////////////////////////
// ����������� ����������� dll ��� LoadManager'a
///////////////////////////////////////////////////////////////////////////////
/*void CopyLoadManager();*/

///////////////////////////////////////////////////////////////////////////////
/**
	��������� �������� ��� �������� �������� ����-������.
	� ������ APL_TRY APL_CATCH ������ ���� ������� ���� ��� �����
	��� �������������� �������� ���������� � �������� ���������� � ��� �� �������.
	���-�� ������������� �������� ���������� TSilentException ������.
	APL_TRY()
	{
	   //��� ����-�����
	}
	APL_CATCH()


*/
//��������� ������� ������ ������ ������ ��� ������ �� �����.
//���������� � �� �� ������ ��������� ������������
class TSilentException: public std::exception  
{ 
public: 
	TSilentException():	std::exception("SilentException") {}
};  

//��������� ���������������� ����� �� �������
class ConsoleSynchronous
{
   typedef ClassLevelLockable<ConsoleSynchronous> TMutex;
   TMutex Mutex;

   void StdData();

public:
   template< class T1 >
      void Write( const T1 &o1 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << std::endl;
   }

   template< class T1, class T2 >
      void Write( const T1 &o1, const T2 &o2 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << o2 << std::endl;
   }

   template< class T1, class T2, class T3 >
      void Write( const T1 &o1, const T2 &o2, const T3 &o3 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << o2 << o3 <<std::endl;
   }

   template< class T1, class T2, class T3, class T4 >
      void Write( const T1 &o1, const T2 &o2, const T3 &o3, const T4 &o4 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << o2 << o3 << o4 << std::endl;
   }

   template< class T1, class T2, class T3, class T4, class T5 >
      void Write( const T1 &o1, const T2 &o2, const T3 &o3, const T4 &o4, const T5 &o5 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << o2 << o3 << o4 << o5 << std::endl;
   }

   template< class T1, class T2, class T3, class T4, class T5, class T6 >
      void Write( const T1 &o1, const T2 &o2, const T3 &o3, const T4 &o4, const T5 &o5, const T6 &o6 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << o2 << o3 << o4 << o5 << o6 << std::endl;
   }

   template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
      void Write( const T1 &o1, const T2 &o2, const T3 &o3, const T4 &o4, const T5 &o5, const T6 &o6, const T7 &o7 )
   {
      TMutex::Lock L(Mutex);
      StdData();
      std::cout << o1 << o2 << o3 << o4 << o5 << o6 << o7 << std::endl;
   }

};
extern ConsoleSynchronous Console;

///////////////////////////////////////////////////////////////////////////////
// ����� ������������� ������� �������� ��� �������������� ������������ (��� ������ 
// ����������, ��������� �������� ������ � ��������� ������
// Tester - ���������, ������� ����������� �������, �� ��������� �����������
//         interface Tester
//         {
//            //����������� ����������� ��� �������� ���������� ����������� �������
//            Tester(int ThreadCount);   
//
//            //������� ��� ������������, ������� ���������� ���������� �� ���� ��������� �������
//            //�� ��� ��� ���� ��� �� ����� false ��� ������������ �� ��������� ���������� �������
//            //ThreadNum - ����� �������� ������
//            //pShutdown - ���� �������� �� ����� ��������� ���������� ������ TRUE, �� ������������
//            //            ����� ���������� ������������ (���� �������� ����� TRUE, �� ��� ������������� �����������
//            //            false, �.�. ������� �� ����� ������ ���������� �� �����
//            bool Run( int ThreadNum, volatile LONG *pShutdown );
//         };  
///////////////////////////////////////////////////////////////////////////////
template< class Tester >
class CThreadTestBase: public Tester, public NonCopyable
{
   struct ThreadsData
   {
      CThreadTestBase *pThreadTestBase;
      int ThreadNum;
   };

   std::vector<ThreadsData> m_ThreadsData;
   volatile LONG Shutdown;

   std::vector<HANDLE> m_hThreads;

private:
   static DWORD WINAPI TestThreadImpl(PVOID pvParam);
   void CreateThreads();
   void StopThreads();
public:
   explicit CThreadTestBase( int ThreadCount ): Tester(ThreadCount), Shutdown(FALSE) 
   {
      APL_ASSERT( ThreadCount > 0 );

      m_ThreadsData.resize(ThreadCount);
      m_hThreads.resize(ThreadCount);

      for( size_t i = 0; i < m_ThreadsData.size(); ++i )
      {
         m_ThreadsData[i].pThreadTestBase = this;
         m_ThreadsData[i].ThreadNum = (int)i;
         m_hThreads[i] = 0;
      }
   }

   //��������� ������������� ����
   void ThreadTest();
};
///////////////////////////////////////////////////////////////////////////////

template< class Tester >
void CThreadTestBase<Tester>::CreateThreads()
{
   APL_ASSERT( Shutdown == FALSE );
   DWORD dwThreadID;

   for( size_t i = 0; i < m_hThreads.size(); ++i )
      m_hThreads[i] = chBEGINTHREADEX(NULL, 0, TestThreadImpl, (PVOID)&m_ThreadsData[i], 0, &dwThreadID);   
}
///////////////////////////////////////////////////////////////////////////////

template< class Tester >
void CThreadTestBase<Tester>::StopThreads()
{
   InterlockedExchange(&Shutdown, TRUE);

   WaitForMultipleObjects( (DWORD)m_hThreads.size(), &m_hThreads[0], TRUE, INFINITE);

   for( size_t i = 0; i < m_hThreads.size(); ++i )
      CloseHandle(m_hThreads[i]);

   Shutdown = FALSE;
}
///////////////////////////////////////////////////////////////////////////////

template<class Tester >
DWORD WINAPI CThreadTestBase<Tester>::TestThreadImpl(PVOID pvParam) 
{
   ThreadsData *pTD = reinterpret_cast<ThreadsData *>(pvParam);

   APL_TRY()
   {
      try
      {
         Console.Write( pTD->ThreadNum, " ������ �����" );

         while( 
            !pTD->pThreadTestBase->Shutdown && 
            pTD->pThreadTestBase->Tester::Run( pTD->ThreadNum, &pTD->pThreadTestBase->Shutdown ) 
            )
         {   
            //������ ������ �� ����
         }

         Console.Write( pTD->ThreadNum, " ��������� �����" );
      }
      catch(...)
      {
         Console.Write( pTD->ThreadNum, " �������� ����������. ��������� �����" );
         InterlockedExchange(&pTD->pThreadTestBase->Shutdown, TRUE);
         throw;
      }
   }			
   APL_CATCH()

   return 0;
}
///////////////////////////////////////////////////////////////////////////////

template< class Tester >
void CThreadTestBase< Tester>::ThreadTest()
{
   //cout << APL_LINE << "BEGIN CThreadTestBase::ThreadTest" << endl;

   CreateThreads();
   getch();
   StopThreads();

   //cout << "END CThreadTestBase::ThreadTest" << endl << APL_LINE;
}

}} //namespace SS::Lib 

#endif