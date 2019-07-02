#ifndef DBMSAuxiliary_HPP
#define DBMSAuxiliary_HPP

#include <limits>

#include "..\ASCInterface\IDBMS.h"
#include "..\ASsInterface\ILingvoBaseManager.h"

/*
   ��� ������� (� �������� ���������������� ���������) ����������� ������ � DBMS
*/

namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
// ������ ������ ��� ������� �������� �������������  ����� Close
///////////////////////////////////////////////////////////////////////////////
class CTablePtr: public NonCopyable
{
public:
	typedef SS::Interface::Core::DBMS::IDataTable TTable;
	typedef SS::Interface::Core::DBMS::IDataBase TDataBase;

private:
	TTable *m_pTable;

public:
	CTablePtr(): m_pTable(0) {}
	~CTablePtr(){ Close(); }
	
	bool IsOpen() const { return m_pTable != 0 &&  m_pTable->IsOpen(); }
	
	void Close()
	{ 
      DEBUG_MSG_IF_LOG10( m_pTable != 0 && !m_pTable->IsOpen(), "TABLE CLOSE NOT OPENED " << Convert( m_pTable->GetName(), std::string()) );
      
      if( m_pTable != 0 && m_pTable->IsOpen() ) //IsOpen, �.�. ��� �� ��� ��� ������� �������
		{ 
         DEBUG_MSG_LOG10("TABLE CLOSE " << Convert( m_pTable->GetName(), std::string()) );

         m_pTable->Close(); 
			m_pTable = 0; 
		} 
	}

	HRESULT Open( TDataBase *pDB,  UINT32  nDTableIndex )
	{
		APL_ASSERT(pDB != 0);
		
		Close(); 
		HRESULT Rez = pDB->MoveToDataTable( nDTableIndex );
      
		if( Rez != S_OK ) return Rez;

		m_pTable = pDB->OpenDataTable();
		APL_ASSERT( m_pTable != 0 );

      DEBUG_MSG_LOG10("TABLE OPEN " << Convert( m_pTable->GetName(), std::string()) );

		return S_OK;
	};

	HRESULT Open( TDataBase *pDB,  CONST _TCHAR * pDTableName )
	{
		APL_ASSERT(pDB != 0);

		Close(); 
		HRESULT Rez = pDB->MoveToDataTable( pDTableName );

		if( Rez != S_OK ) return Rez;

		m_pTable = pDB->OpenDataTable();
		APL_ASSERT( m_pTable != 0 );

      DEBUG_MSG_LOG10("TABLE OPEN " << Convert( m_pTable->GetName(), std::string()) );

		return S_OK;
	}

	TTable *operator->(){ return m_pTable; }
	const TTable *operator->() const { return m_pTable; }
	TTable &operator*() { return *m_pTable; }
	const TTable &operator*() const{ return *m_pTable; }
	TTable *Get(){ return m_pTable; }
	const TTable *Get() const { return m_pTable; }
};


///////////////////////////////////////////////////////////////////////////////
//������������� ������ � ������� ������ � DBMS::IDataTable
//��������� �� ��������� � ��������� ������� FindId � ������������� �������� 
//FindCancel, � �����������
///////////////////////////////////////////////////////////////////////////////
class CFindHelper: public NonCopyable
{
public:
	typedef SS::Interface::Core::DBMS::IDataTable TTable;

private:
	TTable *m_pTable;
	WORD m_FindID;

private:
	static WORD NotInitFindID() { return std::numeric_limits<WORD>::max(); }

public:
	CFindHelper(): m_pTable(0), m_FindID(NotInitFindID()) {}
	explicit CFindHelper(TTable *pTable): m_pTable(pTable), m_FindID(NotInitFindID()) { APL_ASSERT(m_pTable != 0); }
	explicit CFindHelper(CTablePtr &TablePtr): m_pTable(TablePtr.Get()), m_FindID(NotInitFindID()) { APL_ASSERT(m_pTable != 0); }

	//���� �� �������� ����������� � ���������� - ��������, �� ���������� �������� ����� Construct
	void Construct(TTable *pTable)
	{
		Close();
		m_pTable = pTable; 
		m_FindID = NotInitFindID();
	}

	void Construct(CTablePtr &TablePtr)
	{
		Close();
		m_pTable = TablePtr.Get(); 
		m_FindID = NotInitFindID();
	}

	//�������������� �����, ������������� ��������� ������� �����, ���� ���
	HRESULT Init( _TCHAR * pKeyName, VOID * pKeyValue, VOID * ArrayOfPointersToData[] )
	{									    
		Close();
		return m_pTable->FindInitEx( pKeyName, pKeyValue, ArrayOfPointersToData, &m_FindID );
	}

	HRESULT Init( UINT32   nKeyIndex, VOID * pKeyValue, VOID * ArrayOfPointersToData[] )
	{
		Close();
		return m_pTable->FindInitEx( nKeyIndex, pKeyValue, ArrayOfPointersToData, &m_FindID );
	}

	//��������� ����� ���� �� ��� ������ �����
	void Close()
	{
		if(m_FindID != NotInitFindID())
		{ 
			APL_ASSERT(m_pTable != 0); 
			m_pTable->FindCancel(m_FindID);
			m_FindID = NotInitFindID();
		}
	}

	//������� Close
	~CFindHelper(){ Close(); }

	//������ �������
	HRESULT Find() { APL_ASSERT(m_FindID != NotInitFindID() && m_pTable != 0); return m_pTable->Find(m_FindID); }
	HRESULT FindOne() { APL_ASSERT(m_FindID != NotInitFindID() && m_pTable != 0); return m_pTable->FindOne(m_FindID); }
	UINT32 GetFoundIdx() { APL_ASSERT(m_FindID != NotInitFindID() && m_pTable != 0); APL_ASSERT( m_pTable->GetFoundIdx(m_FindID) != 0xFFFFFFFF ); return m_pTable->GetFoundIdx(m_FindID); }
	
	//����� ������ FindStart ������������ FindStop
	//HRESULT FindStart() { APL_ASSERT(m_FindID != NotInitFindID() && m_pTable != 0); return m_pTable->FindStart(m_FindID); }
	HRESULT FindStop() { APL_ASSERT(m_FindID != NotInitFindID() && m_pTable != 0); return m_pTable->FindStop(m_FindID); }
};

///////////////////////////////////////////////////////////////////////////////
// ����� �������� ��������� � ������������� ��������� DBMS ������� ��� ������ 
// ILingvoBaseManager
///////////////////////////////////////////////////////////////////////////////
class CDBMSPtrsManager
{
public:   
   typedef SS::Interface::Core::ResourceManagers::ILingvoBaseManager TLingvoBaseManager;
   typedef SS::Interface::Core::DBMS::IDataBase TDataBase;

private:
   struct SData
   {
      std::wstring BaseType;   //��� ����
      TDataBase **ppDataBase;  //������� ��������� �� �� 
   };

   typedef std::vector<SData> TStorage;

   struct SelectBaseType: SelectorHelper<TStorage::iterator, std::wstring> 
   {
      reference operator ()( origin_iterator_reference V ) const { return V.BaseType; }
   };

   struct SelectDataBase: SelectorHelper<TStorage::iterator, TDataBase **> 
   {
      reference operator ()( origin_iterator_reference V ) const { return V.ppDataBase; }
   };

   typedef CSelectIterator<TStorage::iterator, SelectBaseType> TBaseTypeIterator;
   typedef CSelectIterator<TStorage::iterator, SelectDataBase> TDataBaseIterator;

private:
   TLingvoBaseManager *m_pLingvoBaseManager;
   TStorage m_Storage;

public:   
   CDBMSPtrsManager(): m_pLingvoBaseManager(0) {}
   explicit CDBMSPtrsManager( TLingvoBaseManager *pLingvoBaseManager ): m_pLingvoBaseManager(0) { SetLingvoBaseManager(pLingvoBaseManager); }
   ~CDBMSPtrsManager() { Close(); }

   //���������� ����� LingvoBaseManager, ������ ���� ������ ��� ���������� � �� ����� ���� �� ����������� ����������� � ��������
   void SetLingvoBaseManager( TLingvoBaseManager *pLingvoBaseManager )
   {
      Close();
      m_pLingvoBaseManager = pLingvoBaseManager;
   }

   //������� ����������� ���� LingvoBaseManager ��� ���������� �� � 0 � ������ ��������� �� �� �� ����� ����
   void Close()
   {
      if( m_pLingvoBaseManager != 0 )
         for( TStorage::iterator I = m_Storage.begin(); I != m_Storage.end(); ++I )
            if( *I->ppDataBase != 0 )
            {
               m_pLingvoBaseManager->UnRegisterDeleteAndClose( I->BaseType.c_str(), I->ppDataBase );
               *I->ppDataBase = 0;
            }
   }

   //������� ����������� ���� LingvoBaseManager ��� ���������� �� � 0 � ������ ����������� �� ����� ����
   //�������������� ���������� Close()
   void Open()
   {
      Close();
      
      if( m_pLingvoBaseManager != 0 )
         for( TStorage::iterator I = m_Storage.begin(); I != m_Storage.end(); ++I )
            if( *I->ppDataBase == 0 )
            {
               m_pLingvoBaseManager->CreateOpenAndRegister( I->BaseType.c_str(), I->ppDataBase );

               if( *I->ppDataBase == 0 )
                  APL_THROW( _T("������ ��� ������� �������� ��������� �� ���� ������ ") << I->BaseType );
            }
   }

   //�������� �����������
   //�������������� ���������� Close()
   void Clear()
   {
      Close();

      m_Storage.clear();
   }

   //���������������� ������ 
   //*ppDataBase �������������� � 0
   void Register( std::wstring BaseType, TDataBase **ppDataBase )
   {
      APL_ASSERT_PTR( ppDataBase );

      APL_ASSERT( std::find(TBaseTypeIterator(m_Storage.begin()), TBaseTypeIterator(m_Storage.end()), BaseType ) == TBaseTypeIterator(m_Storage.end()) );
      APL_ASSERT( std::find(TDataBaseIterator(m_Storage.begin()), TDataBaseIterator(m_Storage.end()), ppDataBase ) == TDataBaseIterator(m_Storage.end()) );
      
      m_Storage.push_back( SData() );
      m_Storage.back().BaseType = BaseType;
      m_Storage.back().ppDataBase = ppDataBase;

      *ppDataBase = 0;
   }
};


///////////////////////////////////////////////////////////////////////////////
// �������������� ����������� � ����������� ���
///////////////////////////////////////////////////////////////////////////////
class TTableAutoOpenClose: NonCopyable
{
public:
   typedef SS::Interface::Core::DBMS::IDataBase TDataBase;

private:
   struct TData
   {
      CTablePtr *pTablePtr;
      TDataBase *pDB;  
      CONST _TCHAR *pDTableName;

      TData( CTablePtr *pTablePtr = 0, TDataBase *pDB = 0, CONST _TCHAR *pDTableName = 0 ):
         pTablePtr(pTablePtr), pDB(pDB), pDTableName(pDTableName) {}
   };

   typedef std::list<TData> TStorage;

private:
   TStorage m_Storage;
   bool m_IsOpen;

private:
   bool Open()
   {
      for( TStorage::iterator I = m_Storage.begin(); I != m_Storage.end(); ++I )
         if( I->pTablePtr->Open( I->pDB, I->pDTableName ) != S_OK )
            return false;

      m_IsOpen = true;

      return true;
   }

   void Close()
   {
      for( TStorage::iterator I = m_Storage.begin(); I != m_Storage.end(); ++I )
      {
         I->pTablePtr->Close();
      }

      m_IsOpen = false;
   }

   bool IsOpen() const { return m_IsOpen; }

   friend class TOpenHolder;

public:
   TTableAutoOpenClose(): m_IsOpen( false ) {}
   ~TTableAutoOpenClose() { Close(); }
   
   void Clear()
   {
      m_Storage.clear();
   }

   void Add( CTablePtr *pTablePtr = 0, TDataBase *pDB = 0, CONST _TCHAR *pDTableName = 0 )
   {
      APL_ASSERT_PTR(pTablePtr);
      APL_ASSERT_PTR(pDB);
      APL_ASSERT_PTR(pDTableName);

      m_Storage.push_back( TData(pTablePtr, pDB, pDTableName) );
   }

   class TOpenHolder
   {
      TTableAutoOpenClose *m_pData;
      bool m_NeadClose;
   
   public:
      explicit TOpenHolder( TTableAutoOpenClose &TableAutoOpenClose ): m_pData(&TableAutoOpenClose), m_NeadClose(false)
      {
         APL_ASSERT_PTR(m_pData);

         if( !m_pData->IsOpen() )
         {
            if( !m_pData->Open() )
            {
               for( TTableAutoOpenClose::TStorage::iterator I = m_pData->m_Storage.begin(); I != m_pData->m_Storage.end(); ++I )
                  if( !I->pTablePtr->IsOpen() )
                     APL_THROW( "������ ��� �������� ����: " << I->pDTableName );

               APL_ASSERT( false ); //���� ����� �� ������
            }

            m_NeadClose = true;
         }
      }

      ~TOpenHolder()
      {
         APL_ASSERT_PTR(m_pData);

         if( m_NeadClose )
            m_pData->Close();
      }
   };
};



}} //namespace SS::Lib 

#endif