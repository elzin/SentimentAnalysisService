/*===============================================================*\
   ����������� ����������� �������� � ���������� �����������.
   ������ ���������� � ������ ������� ������������ H - �����

 + ���������� ������ APL_ASSERT( expr ), ������� ��-��������� ��������
   ��� assert, �� ����� ��������������

 + ���������� ������ APL_ASSERT_PTR( ptr ), ������� ��������� ��������� �� �� ��� �� �������
   �� ����� ��������� ����� ������ ��� ������ ������. (��� ������� ��������� �� ����� 0).
   ��� smart ���������� ������������ �������� �� ����������� 0
   
 + ���������� ������ APL_ASSERT_PTR_TYPE( ptr, type ), ������� APL_ASSERT_PTR, �� ���������
   ������� ��� �� ������� ��������� ptr �������� �� *ptr. �������� ��� ���������� void ��� �����-
   ����� �� ������� �����

 + ���������� ������ APL_CHECK( expr ), ������� � ���������� ������
   ��������������� � APL_ASSERT( expr ), � � ������� ������ ������� ������
   ( expr ). �.�. expr � ������� ������ �� ����� ����������, �� ��� ��������
   �� ����� ���������.

 + ���������� APL_CHECK_SUCCEEDED( arg ), ������� �������� ������� APL_CHECK, �� ���������� 
   �������� ��� ������ ������� SUCCEEDED
   
 + ���������� APL_CHECK_S_OK( arg ), ������� �������� ������� APL_CHECK, �� ���������� 
   �������� �� ��������� S_OK

 + DEBUG_MSG( arg ) - �������� ���������� ��������� (��-��������� � �������
   OutputDebugString), ���������� ������, ��� ��� ����� ������
   <��������_1> << <��������_2> << ... << <��������_n>,
   ��� ������� ��� ��� ������� ��������� �������� ��������
   istream &operator<<( istream &, const T & ), �� ������� ������ � ��
   ������ �������� ������������� �������, ���� �������� NOT_SHOW_DEBUG_MSG ��� 
   SHOW_DEBUG_MSG_LOG_LEVEL �������� � 0

 + DEBUG_MSG_IF( cond, arg ) - ������ ���� ��� � DEBUG_MSG, �� ������ � 
   ��� ������ ���� cond == true

 + DEBUG_MSG_LOG<N>( arg ) � DEBUG_MSG_IF_LOG<N>( cond, arg )
   ������ ���� ��� � DEBUG_MSG � DEBUG_MSG_IF, �� ��� ������� ��� ��������
   ������ SHOW_DEBUG_MSG_LOG_LEVEL �� ��������� ������� ��� ������ N.
   ��� �� ����� ��������� �������� ��������� ������� ���� N ��������� ������
   DONT_SHOW_DEBUG_MSG_LOG_LEVEL<N>

 + APP_ID - ������������� ����������, ������������ � DEBUG_MSG,
   ��� ������� ������ ����������� ������

 + ���������� ������ APL_DYNAMIC_CAST ������� ��������� ��������� ����������
   ����� ����� �� �������� ������������. ���� NDEBUG �������� �� ��� ����������
   ������������ static_cast, � ���� �� �������� �� dynamic_cast � ��������
   ������������� �������� �� == NULL. ���� ��� ��� �� ��������� ��������� �
   ������� _assert

 + ���������� ������ APL_ARRSIZE( arg ) ������� ��������� ������ ������� �
   ������� sizeof(arg) / sizeof( *arg )
   
 + APL_THROW ������� ������� ����������� � ������� ��� ����������. ���������
   ���� � DEBUG_MSG.
 
 + APL_LOG ���������� � ������� ����������� � ������� ���� ��������� ������. 
   ��������� ���� � DEBUG_MSG.

 + APL_TYPEID_NAME( arg ) ���������� typeid(arg).name() ���� �������� ����������
   � ����� � ������ ���������� (Enable Run-Time Type Information) � ������ ��������
   ���� ����� ���������� ����������
\*===============================================================*/
#ifndef FirstHeaderH
#define FirstHeaderH

//������ � VC ���������� ��� ���������� � ������ �������
#ifdef _DEBUG
   //������ ������ ��������� ��� ��������� ������� STL
#  if !defined( __BORLANDC__)
//#     define _STLP_DEBUG   //��� ����������� ������ stlport
#  endif
#else
#  ifndef NDEBUG
#		define NDEBUG           //��� assert
#  endif
#endif

#define  _WIN32_WINNT 0x0403 

#ifndef NDEBUG
   #include <windows.h>
#endif

#include <assert.h>
#include <crtdbg.h>

#define APL_BREAKPOINT() DebugBreak()

#define APL_ASSERT( arg ) _ASSERTE( arg )

//�� ����� ������������� ������ ��� �������� ������� ��������� � ������ ������ ��� ������ (�������� ������)
//��� ����� �������������� ������� �������� ��� ��������� �� ����������� ������
#ifndef NDEBUG
template< class T >
bool TestPtr__( T *pT )
{
   return pT != NULL && !IsBadReadPtr(pT, sizeof(*pT)) && !IsBadWritePtr((LPVOID)pT, sizeof(*pT));
}

template< class T >
bool TestPtr__( const T *pT )
{
   return pT != NULL && !IsBadReadPtr(pT, sizeof(*pT));
}

template< class T >
bool TestPtr__( const T &pSmartPointer )
{
   return pSmartPointer != 0;
}

#endif

#define APL_ASSERT_PTR( ptr ) \
APL_ASSERT( TestPtr__(ptr) )

#define APL_ASSERT_PTR_TYPE( ptr, type ) \
APL_ASSERT( ptr != NULL && !IsBadReadPtr(ptr, sizeof(type)) && !IsBadWritePtr((LPVOID)ptr, sizeof(type)))

//APL_CHECK
#ifndef NDEBUG
#  define APL_CHECK( arg ) APL_ASSERT( arg )
#else
#  define APL_CHECK( arg ) ( arg )
#endif

//APL_CHECK_HR
#ifndef NDEBUG
#  define APL_CHECK_SUCCEEDED( arg ) APL_ASSERT( SUCCEEDED(arg) )
#else
#  define APL_CHECK_SUCCEEDED( arg ) ( arg )
#endif

#ifndef NDEBUG
#  define APL_CHECK_S_OK( arg ) APL_ASSERT( (arg) == S_OK )
#else
#  define APL_CHECK_S_OK( arg ) ( arg )
#endif

//APL_ARRSIZE
#define APL_ARRSIZE( arg ) ( sizeof(arg) / sizeof(*(arg)) )

//APL_DYNAMIC_CAST
#ifndef NDEBUG
template <class T, class TArg>
inline T AplTestCast__( TArg V, char *File, unsigned int Line )
{
   T tmp = dynamic_cast<T>(V);
   if( tmp == NULL )
   {
      assert( "APL_DYNAMIC_CAST - See 'FirstHeader.h'", File, Line );
   }
   return tmp;
}

#  define APL_DYNAMIC_CAST( T, arg )  AplTestCast__<T>( arg, __FILE__, __LINE__ )
#else
#  define APL_DYNAMIC_CAST( T, arg )  static_cast<T>( arg )
#endif


//#define NOT_SHOW_DEBUG_MSG     //����� �������� ��������� c ������� DEBUG_MSG

//������������� ���������� ��������� ����� ����� ����������� DEBUG_MSG
#ifndef APP_ID
#define APP_ID "<APP_ID>"
#endif

//���� �� �������� ������� ������ ����, �� �� ����������� ��������� �.�. ������������ ��� ��������� ����� ���������� ������, ���� ��������
//NOT_SHOW_DEBUG_MSG �� �� ������������ ��������� ������
#ifndef SHOW_DEBUG_MSG_LOG_LEVEL 
   #ifdef NOT_SHOW_DEBUG_MSG
      #define SHOW_DEBUG_MSG_LOG_LEVEL 0
   #else
      #define SHOW_DEBUG_MSG_LOG_LEVEL 9
   #endif
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL > 0
#  include <sstream>
#  include <tchar.h>
#  include <windows.h>
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL > 0
#  define DEBUG_MSG( arg ) { std::basic_stringstream</*TCHAR*/CHAR> Stream; Stream << APP_ID << '\t' << arg << std::endl; OutputDebugStringA(Stream.str().c_str()); }
#  define DEBUG_MSG_IF( cond, arg ){ if( cond ) DEBUG_MSG( arg ) }
//�������� ���� �� ������� � ���� ���� ��� ��������� ����������� ������ � rvalue, �.�. �������� �� ���� ����������� ������ ������, � ������ � �������� operator<< ����.
//#  define DEBUG_MSG( arg ) OutputDebugStringA( static_cast<std::basic_stringstream</*TCHAR*/CHAR> &>(std::basic_stringstream</*TCHAR*/CHAR>() << APP_ID << '\t' << arg << std::endl).str().c_str() )
//#  define DEBUG_MSG_IF( cond, arg ) if( !cond ); else DEBUG_MSG( arg ) //if-else ��� ������ �������� ������������� � ���������� if-else
#else
#  define DEBUG_MSG( arg )
#  define DEBUG_MSG_IF( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 1 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL1)
#  define DEBUG_MSG_LOG1( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG1( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG1( arg )
#  define DEBUG_MSG_IF_LOG1( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 2 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL2)
#  define DEBUG_MSG_LOG2( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG2( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG2( arg )
#  define DEBUG_MSG_IF_LOG2( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 3 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL3)
#  define DEBUG_MSG_LOG3( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG3( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG3( arg )
#  define DEBUG_MSG_IF_LOG3( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 4 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL4)
#  define DEBUG_MSG_LOG4( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG4( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG4( arg )
#  define DEBUG_MSG_IF_LOG4( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 5 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL5)
#  define DEBUG_MSG_LOG5( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG5( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG5( arg )
#  define DEBUG_MSG_IF_LOG5( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 6 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL6)
#  define DEBUG_MSG_LOG6( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG6( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG6( arg )
#  define DEBUG_MSG_IF_LOG6( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 7 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL7)
#  define DEBUG_MSG_LOG7( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG7( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG7( arg )
#  define DEBUG_MSG_IF_LOG7( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 8 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL8)
#  define DEBUG_MSG_LOG8( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG8( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG8( arg )
#  define DEBUG_MSG_IF_LOG8( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 9 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL9)
#  define DEBUG_MSG_LOG9( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG9( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG9( arg )
#  define DEBUG_MSG_IF_LOG9( cond, arg )
#endif

#if SHOW_DEBUG_MSG_LOG_LEVEL >= 10 && !defined(DONT_SHOW_DEBUG_MSG_LOG_LEVEL10)
#  define DEBUG_MSG_LOG10( arg ) DEBUG_MSG( arg )
#  define DEBUG_MSG_IF_LOG10( cond, arg ) DEBUG_MSG_IF( cond, arg )
#else
#  define DEBUG_MSG_LOG10( arg )
#  define DEBUG_MSG_IF_LOG10( cond, arg )
#endif

#ifdef _CPPRTTI 
#  define APL_TYPEID_NAME( arg ) typeid(arg).name()
#else
#  define APL_TYPEID_NAME( arg ) "<Run-Time Type Information is not avalible>"
#endif

//VS ������������ ��� �������, � ����� ��� ������
#undef min
#undef max

#ifdef NWLIB_SS_FRAMEWORK
#include "SSFramework/FirstHeaderImpl.h"
#else
#include "StandartFramework/FirstHeaderImpl.h"
#endif

#endif
