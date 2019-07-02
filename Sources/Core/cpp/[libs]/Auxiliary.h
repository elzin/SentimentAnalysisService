#ifndef Auxiliary_H
#define Auxiliary_H

///////////////////////////////////////////////////////////////////////////////
// ������ �������� ��������������� ������� � ������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////

namespace SS { namespace Lib {

//�������������� ����� char � wchar_t ���� � �����
std::wstring &Convert(const std::string &In, std::wstring &Out);
std::string &Convert(const std::wstring &In, std::string &Out);

//�������� ��������� ��� ������� ��
//template< class T > inline T &Convert(const T &In, T &Out){ return Out = In; }
//������ �.�. ��� ������ Convert �������� ������� �������������� �����, � ��������� 
//������� ������� �� �����
inline std::wstring &Convert(const std::wstring &In, std::wstring &Out){ return Out = In; }
inline std::string &Convert(const std::string &In, std::string &Out){ return Out = In; }

namespace Detail
{
   template< class TIn, class TOut >
   struct ConvertToBufImpl
   {
      typedef TOut TRetVal;
      static TRetVal F( const TIn &In ){ TOut Out; return Convert(In, Out); }
   };
   
   template< class T >
   struct ConvertToBufImpl< T, T >
   {
      typedef const T & TRetVal;
      static TRetVal F( const T &In ){ return In; }
   };
}

//����������� ������� �� ��������, � ��������� ����������� ������. ��������� ��������.
template< class TOut, class TIn >
inline typename Detail::ConvertToBufImpl<TIn, TOut>::TRetVal 
   ConvertToBuf( const TIn &In ){ return Detail::ConvertToBufImpl<TIn, TOut>::F(In); }

//������� ����� ��� ����������� �������������, ����� ������������ ConvertToBuf
inline std::wstring ConvertToWide(const std::string &In){ return ConvertToBuf<std::wstring>(In); }
inline const std::wstring &ConvertToWide(const std::wstring &In){ return ConvertToBuf<std::wstring>(In); }
inline std::string ConvertToNarrow(const std::wstring &In){ return ConvertToBuf<std::string>(In); }
inline const std::string &ConvertToNarrow(const std::string &In){ return ConvertToBuf<std::string>(In); }

//�������������� ������ � ������ �������, Src � Dst ����� ���������
std::wstring &ToLower( const std::wstring &Src, std::wstring &Dst );

///////////////////////////////////////////////////////////////////////////////

//���� � �������� ������
std::basic_string<TCHAR> GetExeDirPath();

//������ � ������� ��������
std::basic_string<TCHAR> GetTimeStampString();

// ���������� ��������� �������� HRESULT
std::basic_string<TCHAR> GetHRErrorInfo( HRESULT hr );

// ���������� ��������� �������� DWORD
inline std::basic_string<TCHAR> GetDWErrorInfo( DWORD dwErr )
{
   return GetHRErrorInfo( HRESULT_FROM_WIN32(dwErr) );
}

}} //namespace SS::Lib 

#ifdef NWLIB_SS_FRAMEWORK
#include "SSFramework/SSAuxiliary.h"
#endif


#endif