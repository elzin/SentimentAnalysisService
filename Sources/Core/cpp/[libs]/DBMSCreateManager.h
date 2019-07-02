#ifndef DBMSCreateManager_H
#define DBMSCreateManager_H

#include <map>
#include "StlAuxiliary.h"
#include "Threads.h"
#include "..\ASCInterface\IDBMS.h"

namespace SS { namespace Lib {

/**
   ��������� ��������� � ��������� ��������, ����������� ��������� IDBManager. 
   Singleton
   ��������� �������� ������� IDataBase
   ����������� ��� ������ ��� ����� ����� ����������������� ���������� (���� � ��) ����� 
   �� ����� ������ ������� ������������ ��������� IDBManager
   �� ������� �� ��� IDBManager, ������ ������� IDataBase

   ���� ������� ������ �������� IDataBase ��������� �� ������������ � �������������� ������� ��� ������� 
   ����������� ��������� IDBManager, ��� ������ ����� ����������� ��� ������� ���� IDataBase.

   ��� ���� ����� �������� ��������� �� IDataBase ���������� ������� 
      CDBMSCreateManager::Create()->OpenDataBase(...)
   
   � ��� ������������ ���� (������������� ���������� Close) 
      CDBMSCreateManager::Create()->CloseDataBase(...)
*/

class CDBMSCreateManager: public NonCopyable
{
private:
   CDBMSCreateManager() {} //��������� ��������������� �� ���

private:              
   typedef std::wstring TMapKey;                          //���� � ����
   typedef Interface::Core::DBMS::IDBManager IDBManager;  
   typedef Interface::Core::DBMS::IDataBase IDataBase;  
   typedef Interface::Core::ResourceManagers::ILoadManager ILoadManager;  

   class CRefCounter
   {
      size_t m_RefCount; //���������� ������ �� ������

   public:
      CRefCounter(): m_RefCount(0) {}
      size_t RefCount() const { return m_RefCount; }
      size_t IncRef(){ return ++m_RefCount; }
      size_t DecRef(){ APL_ASSERT(m_RefCount > 0); return --m_RefCount; }
   };

   class CManagerData: public CRefCounter
   {
      IDBManager *m_pDBManager;    //��� ���������� ��������

   public:
      CManagerData( IDBManager *pDBManager = 0 ): m_pDBManager(pDBManager) {}
      IDBManager *GetDBManager() const { return m_pDBManager; }
   };

   typedef std::map<TMapKey, CManagerData> TObjectsMap;

   class CDataBaseData: public CRefCounter
   {
      typedef TObjectsMap::iterator TIter;
      TIter m_Iter;   //���������� �������� 

   public:
      CDataBaseData( TIter Iter = TIter() ): m_Iter(Iter) {}
      TIter GetIter() const { return m_Iter; }

      friend inline bool operator==( const CDataBaseData &ob1, const CDataBaseData &ob2 )
      {
         return ob1.GetIter() == ob2.GetIter();
      }
   };

   typedef std::map<IDataBase*, CDataBaseData> TIDataBase2ObjectsMapIter;  //�������� ���� � ����������

   typedef ClassLevelLockable<CDBMSCreateManager> TMutex;

public:
   typedef IDataBase *TPointer;
   typedef const IDataBase *TConstPointer;
   typedef CDBMSCreateManager ThisType;

private:
   //����� ����� ��� ������ � ������� �������� �� ��� ����� ���� ������� �������.
   TObjectsMap m_ObjectsMap;
   TIDataBase2ObjectsMapIter m_IDataBase2ObjectsMapIter;
   static TMutex m_Mutex;
   static ThisType *pInstance_;

   static ThisType *CreateImpl()
   {
      static ThisType Obj;
      return &Obj;
   }


public:
   //�������� ��������� �� CDBMSCreateManager
   static ThisType *Create()
   {
      //�� ��������� ���������� � ����� ����������
      if( pInstance_ == 0 )
      {
         TMutex::Lock Guard(m_Mutex);

         if( pInstance_ == 0 )
            pInstance_ = CreateImpl();
      }
      
      return pInstance_;
   }

   // ������� �� IDataBase, ��� ���� ���� ��� �� ������, �������� IDBManager
   // pLoadManager - ������������ ��� �������� IDBManager (������� Create)
   // FullPathToIniFile - ���� � ini-����� ��
   // FullPathToDbmsBases - ���� � ����� ������
   // DBName - ���  ��
   TPointer OpenDataBase( 
      ILoadManager *pLoadManager,
      const std::wstring &FullPathToIniFile, 
      const std::wstring &FullPathToDbmsBases, 
      const std::wstring &DBName 
   );

   //������� �� (������������� ����������� Close), ���� ��� ������ �������� ������ �� IDBManager
   //�� �� ���������
   void CloseDataBase(TPointer pDB);

   ~CDBMSCreateManager();
};


}} //namespace SS::Lib 

#endif //DBMSCreateManager_H
