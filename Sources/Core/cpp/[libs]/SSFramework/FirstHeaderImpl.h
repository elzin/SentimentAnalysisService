#ifndef FirstHeaderImplH
#define FirstHeaderImplH

//SS_THROW �� ������ ������ ����������, � ��������� ������ ��� ������ ���������� �������� SS_THROW
//����� ��������� ������ ����� ������� ���������. � ����� ������� �������� ����������� ��� ����������
//std::exception 
#include "../ASCInterface/defines.h"

SET_LOAD_MANAGER_DEFINE;
USES_LOAD_MANAGER;
///////////////////////////////////////////////////////////////////////////////
// !!! ���������� � ����� �� ������� CPP ���������� SET_LOAD_MANAGER_IMPLEMENTATION; !!!
///////////////////////////////////////////////////////////////////////////////

#ifndef USES_IBASE
#define APL_THROW( arg ){                                                                       \
   std::basic_stringstream<TCHAR> Stream__; Stream__ << arg;                                    \
   if( !(!spLoadManager ) ) {                                                                   \
      SS_THROW( const_cast<wchar_t*>(ConvertToBuf<std::wstring>(Stream__.str()).c_str()) );     \
   } else {                                                                                     \
      throw std::exception( ConvertToBuf<std::string>(Stream__.str()).c_str() );                \
   }                                                                                            \
}
#else
#define APL_THROW( arg ){                                                                       \
   std::basic_stringstream<TCHAR> Stream__; Stream__ << arg;                                    \
   SS_THROW( const_cast<wchar_t*>(ConvertToBuf<std::wstring>(Stream__.str()).c_str()) );        \
}
#endif

#define APL_LOG( arg ){                                                                         \
   std::basic_stringstream<TCHAR> Stream__; Stream__ << arg <<                                  \
       std::endl << _T("\t") << __WFUNCTION__ << std::endl;                                     \
   SAVE_LOG(SS_WARNING AND const_cast<wchar_t*>(                                                \
       ConvertToBuf<std::wstring>(Stream__.str()).c_str()) );                                   \
}

#include "Auxiliary.h" //��� ������� Convert

#endif