#include "stdafx.h"
#include "SSAuxiliary.h"

namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
// class LoadManagerCreater
///////////////////////////////////////////////////////////////////////////////
CLoadManagerCreater::CLoadManagerCreater( const std::basic_string<TCHAR> &FileName /*= _T("LoadManager.dll")*/ )
{
   std::basic_string<TCHAR> Path( GetExeDirPath() );

   ::SetCurrentDirectory(Path.c_str());  

   m_hLoadManager = ::LoadLibrary(FileName.c_str());			//�������� ���������� � ��������� �� �� ���������
   if( m_hLoadManager == NULL )
      APL_THROW( _T("������ ��� �������� ����� ") << Path << FileName );

    m_CreateInstanceFunc = (CREATE_INSTANCE)GetProcAddress(m_hLoadManager, "CreateInstance" );	//����� ����. �� �-� CreateInstance

   if( m_CreateInstanceFunc == NULL )
      APL_THROW( _T("������ ��� ��������� ��������� �� �������") );
}
///////////////////////////////////////////////////////////////////////////////

CLoadManagerCreater::~CLoadManagerCreater()
{
   ::FreeLibrary(m_hLoadManager);

   /*---
   if( ::FreeLibrary(m_hLoadManager) == FALSE )
      APL_THROW( _T("������ ��� �������� ����������") );
   */
}
///////////////////////////////////////////////////////////////////////////////

CLoadManagerCreater::TAutoPtr CLoadManagerCreater::Create() const
{
   TLoadManager *pLoadManager;

   if((m_CreateInstanceFunc)(&CLSID_LoadManager, (void**)&pLoadManager) != S_OK || pLoadManager == NULL )
      APL_THROW( _T("������ ��� ��������� CLSID_LoadManager") );

   return TAutoPtr(pLoadManager);
}
///////////////////////////////////////////////////////////////////////////////

}} //namespace SS::Lib 
