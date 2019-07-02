#ifndef SSAuxiliary_H
#define SSAuxiliary_H
#include "../LikePointer.hpp"

#include "../../ASCInterface/IInterface.h"
#include <objbase.h>


///////////////////////////////////////////////////////////////////////////////
// ������ �������� ��������������� ������� � ������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������������� ����� ������� ��������� ��� �������� ������� QueryInterface
// � ����������� ������
///////////////////////////////////////////////////////////////////////////////
#define BEGIN_QI_MAP() \
HRESULT QueryInterface(REFIID pIID, void** pBase) \
{

/// ����������� ��������� ����������
#define QI_MAP_INHERIT_ENTRY( IID, Type ) \
	if(pIID==(IID)) \
		*pBase = static_cast<Type*>(this); \
	else

/// ����������� ��������� ����� �������� ���� ���������� ���������� ������
#define QI_MAP_MEMBER_ENTRY( IID, Type, Member ) \
	if(pIID==(IID)) \
		*pBase = static_cast<Type*>(&Member); \
	else
	
#define END_QI_MAP() \
	{\
		*pBase = NULL;  \
		return E_NOINTERFACE;  \
	}\
	return S_OK;  \
}

#define RELEASE_IMPL() ULONG Release(){ delete this;  return 0; }               


namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
//����� ��������� ��������� ILoadManager � ����������� ����������
//����� ������������� � �������� ILoadManager'�� ���������� ������� 
//Release, ��������� ������������� auto_ptr_ex, ���������� �������������
///////////////////////////////////////////////////////////////////////////////
class CLoadManagerCreater
{
   typedef SS::Interface::IBase TIBase;
   typedef HRESULT (*CREATE_INSTANCE)(const GUID* pGuid, void** pBase);

public:
   typedef SS::Interface::Core::ResourceManagers::ILoadManager TLoadManager;
   typedef auto_ptr_ex<TLoadManager, auto_ptr_ex_release_strategy> TAutoPtr;

private:
   HMODULE m_hLoadManager;
   CREATE_INSTANCE m_CreateInstanceFunc;

private:
   std::basic_string<TCHAR> GetStringFromGUID( REFGUID guid ) const
   {
      WCHAR Str[40];
      std::basic_string<TCHAR> Tmp;

      APL_CHECK( StringFromGUID2(guid, Str, APL_ARRSIZE(Str)) );
      
      return Convert( Str, Tmp);
   }

public:
   explicit CLoadManagerCreater( const std::basic_string<TCHAR> &FileName = _T("LoadManager.dll") );
   ~CLoadManagerCreater();

   //������� LoadManager
   //���������� �������� Release ����� ������������, (���������� ������������� ��������� auto_ptr_ex)
   TAutoPtr Create() const;   

   //�������� ������������� ����������
   //���� pLoadManager != 0 �� � ���������� ���������� SetLoadManager
   template< class T >
   auto_ptr_ex<T, auto_ptr_ex_release_strategy> GreateInstance( const CLSID &ClassID, const IID &InterfaceID, TLoadManager *pLoadManager = NULL ) const
   {
      TIBase *pBase = 0;
      T *pT = 0;

      if( (m_CreateInstanceFunc)(&ClassID, (void**)&pBase) != S_OK || pBase == NULL )
         APL_THROW( _T("������ ��� ��������� CLSID ") << GetStringFromGUID(ClassID) );

      if( pBase->QueryInterface(InterfaceID, (void**)&pT) != S_OK || pT == NULL )
         APL_THROW( _T("������ ��� ��������� IID ") << GetStringFromGUID(InterfaceID) );
      
      if( pLoadManager != 0 )
         pT->SetLoadManager( pLoadManager );

      return auto_ptr_ex<T, auto_ptr_ex_release_strategy>( pT );
   }
};
///////////////////////////////////////////////////////////////////////////////

}} //namespace SS::Lib 

#endif