#include "stdafx.h"
#include "DBMSCreateManager.h"
#include "Compose.hpp"

namespace SS { namespace Lib {

CDBMSCreateManager::TMutex CDBMSCreateManager::m_Mutex;
CDBMSCreateManager::ThisType *CDBMSCreateManager::pInstance_ = 0;

///////////////////////////////////////////////////////////////////////////////

CDBMSCreateManager::TPointer CDBMSCreateManager::OpenDataBase( 
   ILoadManager *pLoadManager,
   const std::wstring &FullPathToIniFile, 
   const std::wstring &FullPathToDbmsBases, 
   const std::wstring &DBName 
)
{
   APL_ASSERT_PTR( pLoadManager );
   TMutex::Lock Guard(m_Mutex);

   DEBUG_MSG_LOG4( 
      "��������� DB LoadManager: " << pLoadManager << 
      " FullPathToIniFile: " << Convert( FullPathToIniFile, std::string() ) << 
      " FullPathToDbmsBases: " << Convert( FullPathToDbmsBases, std::string() ) <<
      " DBName: " << Convert( DBName, std::string() ) 
   ); 

   TMapKey Key(FullPathToDbmsBases);   
   TObjectsMap::iterator I = m_ObjectsMap.find(Key);

   //�������� ���� ���������� IDBManager
   if( I == m_ObjectsMap.end() )
   {
      DEBUG_MSG_LOG2( "������ DBMS::IDBManager �������: "  << GetCurrentProcessId() << 
         " �����: " << GetCurrentThreadId() << 
         " FullPathToIniFile: " << Convert( FullPathToIniFile, std::string() ) <<
         " FullPathToDbmsBases: " << Convert( FullPathToDbmsBases, std::string() ) 
      );

      IDBManager *pDBManager = 0;
      pLoadManager->Create(L"./core/linguistics/DBMS.dll", CLSID_DBMS, IID_DBManager, reinterpret_cast<void**>(&pDBManager));

      auto_ptr_ex<IDBManager, auto_ptr_ex_release_strategy> pNewObj( pDBManager );

      if( pNewObj == 0 )
         SS_THROW( L"������ ��� ��������� IID_DBManager" );

      
      if( pNewObj->Init(FullPathToIniFile.c_str(), FullPathToDbmsBases.c_str()) != S_OK )
         SS_THROW( L"������ ��� ������������� IDBManager" );

      std::pair<TObjectsMap::iterator, bool> RezPair = m_ObjectsMap.insert( TObjectsMap::value_type(Key, pNewObj.get()) );
      pNewObj.release();

      APL_ASSERT( RezPair.second );
      I = RezPair.first;
   }

   //�������� IDataBase
   if( I->second.GetDBManager()->MoveToDataBase(DBName.c_str()) != S_OK )
      SS_THROW( L"������ ��� ������� ������� � ��" );

   IDataBase *pDataBase = I->second.GetDBManager()->OpenDataBase();
   APL_ASSERT_PTR( pDataBase );
   I->second.IncRef(); //� IDBManager ����� �� ���� ������ ������

   m_IDataBase2ObjectsMapIter.insert(TIDataBase2ObjectsMapIter::value_type(pDataBase, I)).first->second.IncRef(); //���������� ��, ��� �� ����� �� ���� ������ (��� ��������� �����)

   return pDataBase;
}

///////////////////////////////////////////////////////////////////////////////

void CDBMSCreateManager::CloseDataBase(TPointer pDB)
{  
   APL_ASSERT_PTR(pDB);
   TMutex::Lock Guard(m_Mutex);

   TIDataBase2ObjectsMapIter::iterator IAux = m_IDataBase2ObjectsMapIter.find(pDB);

   if( IAux == m_IDataBase2ObjectsMapIter.end() )
      SS_THROW( L"��������� �� DB �� �������� ���������� ������" );
   
   TObjectsMap::iterator IMain = IAux->second.GetIter();
   
   DEBUG_MSG_LOG4( 
      "��������� DB Name: " << Convert( pDB->GetName(), std::string() )  << 
      " FullPathToDbmsBases: " << Convert( IMain->first, std::string() ) 
   ); 

   pDB->Close();

   //������� ���� ���������� ������� � ������ m_IDataBase2ObjectsMapIter
   IAux->second.DecRef();

   if( IAux->second.RefCount() == 0 )
      m_IDataBase2ObjectsMapIter.erase(IAux);

   //������� ���� ���������� ������� � ������ m_ObjectsMap
   IMain->second.DecRef();

   if( IMain->second.RefCount() == 0 )
   {
      //�� ������ ���� ������� �� ������ IDBManager
      APL_ASSERT( 
         std::find_if( m_IDataBase2ObjectsMapIter.begin(), m_IDataBase2ObjectsMapIter.end(),
            bind2nd(
               binary_compose_1arg( 
                  std::equal_to<CDataBaseData>(), 
                  select_second_t<TIDataBase2ObjectsMapIter::value_type>(),
                  select_dummy_t<CDataBaseData>()
               ),
               IMain
            )
         ) == m_IDataBase2ObjectsMapIter.end()  
      );

      DEBUG_MSG_LOG2( "������� DBMS::IDBManager �������: "  << GetCurrentProcessId() << 
         " �����: " << GetCurrentThreadId() << 
         " FullPathToDbmsBases: " << Convert( IMain->first, std::string() )
      );

      IMain->second.GetDBManager()->Release();
      m_ObjectsMap.erase(IMain);
   }
}
///////////////////////////////////////////////////////////////////////////////

CDBMSCreateManager::~CDBMSCreateManager()
{
   TMutex::Lock Guard(m_Mutex); //� �������� �� �����

   //�������� � ��� ��� ���� �������� ����, ���� �� ���� �� ������ ����
   for( TObjectsMap::iterator I = m_ObjectsMap.begin(); I != m_ObjectsMap.end(); ++I )
   {
      std::wstringstream OutStr;
      std::wstring Str;

      OutStr << L"�� ��� ���� ������ ���� �������, �� ����: " << I->first << L". �������� ������� �������������...";
      Str = OutStr.str();
      DEBUG_MSG_LOG2( Convert( Str, std::string() ) );
      SAVE_LOG( (wchar_t *)Str.c_str() );
   }

   //���������� ������� �� ��� ���� �������
   TIDataBase2ObjectsMapIter::iterator IAux = m_IDataBase2ObjectsMapIter.begin();
   TIDataBase2ObjectsMapIter::iterator ICur;
   size_t CurRefCount;
   
   while( IAux != m_IDataBase2ObjectsMapIter.end() )
   {
      ICur = IAux++;
      
      CurRefCount = ICur->second.RefCount();
      
      DEBUG_MSG_LOG2( "��������� ������������� ��: " << Convert( ICur->first->GetName(), std::string() ) << ", " << (unsigned int)CurRefCount << " ���" );

      while( CurRefCount-- )
         CloseDataBase( ICur->first );
   }

   APL_ASSERT( m_ObjectsMap.empty() );
   APL_ASSERT( m_IDataBase2ObjectsMapIter.empty() );
}

}} //namespace SS::Lib 

