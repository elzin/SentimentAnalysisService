#ifndef Threads_H
#define Threads_H

#include "StlAuxiliary.h"
#include <set>
#include <process.h>

/**
   ������ ������������� ��� ������� ��� ����������� ������������� � ������������� �����������
*/ 

//����� �������� ��������� ��������� ��� �������
//#define DEFAULT_THREAD_DEBUG_INFO LockDebugInfo
#define DEFAULT_THREAD_DEBUG_INFO NoDebugInfo

#ifndef NDEBUG
   #define CHECK_DEADLOCKS_FOR_POINTERS true
#else
   #define CHECK_DEADLOCKS_FOR_POINTERS false
#endif


// ������ �� �������� �������.
// This macro function calls the C runtime's _beginthreadex function.
// The C runtime library doesn't want to have any reliance on Windows' data
// types such as HANDLE. This means that a Windows programmer needs to cast
// values when using _beginthreadex. Since this is terribly inconvenient,
// I created this macro to perform the casting.
typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStack, pfnStartAddr,     \
   pvParam, fdwCreate, pdwThreadId)                     \
   ((HANDLE)_beginthreadex(                             \
   (void *)         (psa),                              \
   (unsigned)       (cbStack),                          \
   (PTHREAD_START) (pfnStartAddr),                      \
   (void *)         (pvParam),                          \
   (unsigned)       (fdwCreate),                        \
   (unsigned *)     (pdwThreadId)))


namespace SS { namespace Lib {

namespace Detail
{
/**
   ������������� � �������� "���� ��������/������ ���������" �� ������ �������.

   - ����� ���� ����� ���-�� ����� � ������� ����� ������, ������ ����� ������ �� �����. 
   - ����� ���� ����� ���-�� ����� � ������� ����� ������, ������ �� ����� ������ ��������� ������. 
   - ����� ���� ����� ��������� ���-�� �� ������� ����� ������, ������ �� ����� ���� ������ ����������. 
   - ����� ���� ����� ��������� ���-�� �� ������� ����� ������, ������ ���� ����� ��� ������. 
*/

class CSWMRG {
public:
   CSWMRG();                 // Constructor
   ~CSWMRG();                // Destructor

   VOID WaitToRead();        // Call this to gain shared read access
   VOID WaitToWrite();       // Call this to gain exclusive write access
   VOID Done();              // Call this when done accessing the resource

private:
   CRITICAL_SECTION m_cs;    // Permits exclusive access to other members
   HANDLE m_hsemReaders;     // Readers wait on this if a writer has access
   HANDLE m_hsemWriters;     // Writers wait on this if a reader has access
   int    m_nWaitingReaders; // Number of readers waiting for access
   int    m_nWaitingWriters; // Number of writers waiting for access
   int    m_nActive;         // Number of threads currently with access
   //   (0=no threads, >0=# of readers, -1=1 writer)
};
} // namespace Detail

//��������� ������������ ��� ���������� ����������
//��������� ����������� ������
struct SCriticalSectionImplStategy
{
   typedef CRITICAL_SECTION TLockType;

   static void Create( TLockType &LT ){ ::InitializeCriticalSectionAndSpinCount(&LT, 4000); }
   static void Destroy( TLockType &LT ){ ::DeleteCriticalSection(&LT); }
   static void Lock( TLockType &LT ){ ::EnterCriticalSection(&LT); }
   static void UnLock( TLockType &LT ){ ::LeaveCriticalSection(&LT); }
};

//��������� ��� ������������� �������� "���� ��������/������ ���������", �� ������ ������ CSWMRG
struct SSWMRImplStategy
{
   typedef Detail::CSWMRG TLockType;

   static void Create( TLockType &LT ) {}
   static void Destroy( TLockType &LT ) {}
   static void LockRead( TLockType &LT ) { LT.WaitToRead(); }
   static void UnLockRead( TLockType &LT ) { LT.Done(); }
   static void LockWrite( TLockType &LT ) { LT.WaitToWrite(); }
   static void UnLockWrite( TLockType &LT ) { LT.Done(); }
};

/**
   ��������� ���������������� ������� ��� ����������� ��������� ����� ����������.
   ���������� �������������� ��������� ������ Lo�k � ��������� ��� ��� ��������.

   ���� ������������ ����������� ���������� � �������������� ��������� 
   "���� ��������/��������� ���������" ��� ����� ��������� �������:
      LockRead - ��� ���������� ������
      LockWrite - ��� ���������� ������ 
*/

//����� ���������� ���������� � ���������� ��������
template<class Host>
class LockDebugInfo
{
   static size_t Count_;
   size_t CurNum_;

   void ShowMessage( const char *Str ) const 
   {  DEBUG_MSG( APL_TYPEID_NAME(Host) << " " << (unsigned int)CurNum_ << " " << Str << " " << GetCurrentThreadId() ); }
public:
   LockDebugInfo(): CurNum_( Count_++ ) {}

   void TryLock() const { ShowMessage( "TryLock" ); } 
   void LockOk() const { ShowMessage( "LockOk" ); }
   void Unlock() const { ShowMessage( "Unlock" ); }
   void TryLockRead() const { ShowMessage( "TryLockRead" ); } 
   void LockOkRead() const { ShowMessage( "LockOkRead" ); }
   void UnlockRead() const { ShowMessage( "UnlockRead" ); }
   void TryLockWrite() const { ShowMessage( "TryLockWrite" ); } 
   void LockOkWrite() const { ShowMessage( "LockOkWrite" ); }
   void UnlockWrite() const { ShowMessage( "UnlockWrite" ); }
};

template<class Host>
size_t LockDebugInfo<Host>::Count_ = 0;  

template<class Host>
class NoDebugInfo
{
public:
   void TryLock() const {}
   void LockOk() const {}
   void Unlock() const {}
   void TryLockRead() const {} 
   void LockOkRead() const {}
   void UnlockRead() const {}
   void TryLockWrite() const {} 
   void LockOkWrite() const {}
   void UnlockWrite() const {}
};

///��������� ������ ���������� (��������)
template <class Host, class ImplStategy = SCriticalSectionImplStategy, template<class> class DebugInfo = DEFAULT_THREAD_DEBUG_INFO>
class NoLockable: public NonCopyable
{
public:
   struct Lock: public NonCopyable
   {
      Lock() {}
      explicit Lock(const NoLockable&) {}
   };
   
   struct LockWrite: public NonCopyable
   {
      LockWrite() {}
      explicit LockWrite(const NoLockable&) {}
   };

   struct LockRead: public NonCopyable
   {
      LockRead() {}
      explicit LockRead(const NoLockable&) {}
   };

   enum { NoLockableClass = true }; //�������� �� ���� ����� NoLockable
};


//���������� �� ������ �������
template <class Host, class ImplStategy = SCriticalSectionImplStategy, template<class> class DebugInfo = DEFAULT_THREAD_DEBUG_INFO>
class ObjectLevelLockable: public NonCopyable, private DebugInfo<Host>
{
   mutable typename ImplStategy::TLockType mtx_;

public:
   explicit ObjectLevelLockable()
   {
      ImplStategy::Create(mtx_);
   }

   ~ObjectLevelLockable()
   {
      ImplStategy::Destroy(mtx_);
   }

   class Lock;
   class LockRead;
   class LockWrite;

   friend class Lock;
   friend class LockRead;
   friend class LockWrite;

   class Lock: public NonCopyable
   {
      const ObjectLevelLockable& host_;
      
      Lock(); //������ ��������
   public:

      explicit Lock(const ObjectLevelLockable& host) : host_(host)
      {
         host_.TryLock();
         ImplStategy::Lock(host_.mtx_);
         host_.LockOk();
      }

      ~Lock()
      {
         ImplStategy::UnLock(host_.mtx_);
         host_.Unlock();
      }
   };

   class LockRead: public NonCopyable
   {
      const ObjectLevelLockable& host_;

      LockRead(); //������ ��������
   public:

      explicit LockRead(const ObjectLevelLockable& host) : host_(host)
      {
         host_.TryLockRead();
         ImplStategy::LockRead(host_.mtx_);
         host_.LockOkRead();
      }

      ~LockRead()
      {
         ImplStategy::UnLockRead(host_.mtx_);
         host_.UnlockRead();
      }
   };

   class LockWrite: public NonCopyable
   {
      const ObjectLevelLockable& host_;

      LockWrite(); //������ ��������
   public:

      explicit LockWrite(const ObjectLevelLockable& host) : host_(host)
      {
         host_.TryLockWrite();
         ImplStategy::LockWrite(host_.mtx_);
         host_.LockOkWrite();
      }

      ~LockWrite()
      {
         ImplStategy::UnLockWrite(host_.mtx_);
         host_.UnlockWrite();
      }
   };

   enum { NoLockableClass = false }; //�������� �� ���� ����� NoLockable
};

//���������� �� ������ ������
template <class Host, class ImplStategy = SCriticalSectionImplStategy, template<class> class DebugInfo = DEFAULT_THREAD_DEBUG_INFO>
class ClassLevelLockable: public NonCopyable
{
   struct Initializer: public DebugInfo<Host> 
   {   
      typename ImplStategy::TLockType mtx_;

      Initializer()
      {
         ImplStategy::Create(mtx_);
      }
      ~Initializer()
      {
         ImplStategy::Destroy(mtx_);
      }
   };

   static Initializer initializer_;

public:
   class Lock;
   class LockRead;
   class LockWrite;

   friend class Lock;
   friend class LockRead;
   friend class LockWrite;

   class Lock: public NonCopyable
   {
    public:
      Lock()
      {
         initializer_.TryLock();
         ImplStategy::Lock(initializer_.mtx_);
         initializer_.LockOk();
      }
      explicit Lock(const ClassLevelLockable&)
      {
         initializer_.TryLock();
         ImplStategy::Lock(initializer_.mtx_);
         initializer_.LockOk();
      }
      ~Lock()
      {
         ImplStategy::UnLock(initializer_.mtx_);
         initializer_.Unlock();
      }
   };

   class LockRead: public NonCopyable
   {
   public:
      LockRead()
      {
         initializer_.TryLockRead();
         ImplStategy::LockRead(initializer_.mtx_);
         initializer_.LockOkRead();
      }
      explicit LockRead(const ClassLevelLockable&)
      {
         initializer_.TryLockRead();
         ImplStategy::LockRead(initializer_.mtx_);
         initializer_.LockOkRead();
      }
      ~LockRead()
      {
         ImplStategy::UnLockRead(initializer_.mtx_);
         initializer_.UnlockRead();
      }
   };

   class LockWrite: public NonCopyable
   {
   public:
      LockWrite()
      {
         initializer_.TryLockWrite();
         ImplStategy::LockWrite(initializer_.mtx_);
         initializer_.LockOkWrite();
      }
      explicit LockWrite(const ClassLevelLockable&)
      {
         initializer_.TryLockWrite();
         ImplStategy::LockWrite(initializer_.mtx_);
         initializer_.LockOkWrite();
      }
      ~LockWrite()
      {
         ImplStategy::UnLockWrite(initializer_.mtx_);
         initializer_.UnlockWrite();
      }
   };

   enum { NoLockableClass = false }; //�������� �� ���� ����� NoLockable
};

template <class Host, class ImplStategy, template<class> class DebugInfo>
typename ClassLevelLockable<Host, ImplStategy, DebugInfo>::Initializer ClassLevelLockable<Host, ImplStategy, DebugInfo>::initializer_;

/**
   LockedPtr
   ����� ��������� ����������� ��������� ���������, �� ��� ���� ������������� ��������� 
   ������ ��� ������ ��������� ->. �.�. �������� ��������� ������ � ������������ �� ���-
   ������ ������, ���������� ����������� ����� � ����� � ����������� ��������� ����������
   ������� ������ ����� �������� ����������� ���� ����� ��� ����� ���� �������� �������
   ���������� ����� �������������� ���������� ����� ������������ �� ������ �� ��������
   Lockable.
   
   + ���������� �� ����������� ������� ����� ����������� ��������� �� ������������� (�� �� �������)
   + ��������� ����� �������� � ���� bool � ��������� �� ��������� (����������� 0)

   ��������:
      ���� ����� ������ ������� ���������� � �������������� ����������� �� ������� ���������� ���, ��
      ��� ���������� ���� �������� � ��������� ������� �� �� ����� ���������� ���������. �.�. ������������ 
      ����� ���� ��������� ����� ��������� ��������, �������� ���� ��� ��������� � �������������� �����������
      ����������� �� ������ ������� pA � pB, ����� ���� �������� ���������:
         pA->AnyFunc1() && pB->AnyFunc2()
      
      ������� �� ������� ��������� pA � pB ���������� ��������� �� �� ����� ���������� AnyFunc1 � AnyFunc2. ���� 
      ������ ����� ������� pB->AnyFunc2() && pA->AnyFunc1() �� �������� DeadLock, �.�. �������� ���������� ���� 
      ������.

      � ����� � ���� ���������� �� ��������� �������� ���� �������� LockedPtrBase<T>::Proxy � ����� ������.
      ��� ����� ����� ������������ ��������� ������� ������ �� ����.
*/

namespace Detail
{
template <class T>
class LockedPtrBase
{
private:
   T *pObj_;

private:
   //���������� ����������� �������
   template<class LockObj>
   class Proxy;

protected:  
   LockedPtrBase( T *pObj = 0 ): pObj_(pObj) {}
   //LockedPtrBase( TUndefinedBoolType pT = 0 ): pObj_(0) {} //��������� �������������� ������ �� 0


   //����� ������ ��������� ����������� (���� �� VC7) �������� ��������� ��������� ������� �� ����������
   //������� ��������������� �� NoLockable (�.�. ������ ������� � ���������� �� ���������)
   //� �������� ����� ���� ������ ���������� Proxy, �� ���������� �� ���������� ������������ ����� ������
   //(� VC7 �������� ��� ������ �������)
   typedef typename Select< T::NoLockableClass, T *, Proxy<typename T::Lock> >::Result TReturnType;
public:
   void Set( T *pObj ){ pObj_ = pObj; }
   T *Get() const { return pObj_; }
   TReturnType operator->() const { APL_ASSERT(pObj_ != 0); return TReturnType(pObj_); }

   //�������� ��������� ��������� �� ��������� ����
private:  
   struct OperatorHelper{ int i; }; //��. ��������������(loki)
   typedef int OperatorHelper::*TUndefinedBoolType;
public:
   //�������� ��������� ��������� �� ���������/����������� ���� � ��������� � ���� bool
   operator TUndefinedBoolType() const { return pObj_ != 0? &OperatorHelper::i : 0; }

   //���� �� ���������� �� ����� �������������� �������������� �������������� � TUndefinedBoolType
   //� ���������� ���������
   friend bool operator==( const LockedPtrBase &P1, const LockedPtrBase &P2 ){ return P1.pObj_ == P2.pObj_; }
   friend bool operator!=( const LockedPtrBase &P1, const LockedPtrBase &P2 ){ return P1.pObj_ != P2.pObj_; }

   //���� �� ���������� �� ��� �������� P1 == 0, 0 == P1, P1 != 0, 0 != P1 ��������� 
   //��������������� �.�. ���������� �� explicit
   friend bool operator==( const LockedPtrBase &P1, TUndefinedBoolType P2 ){ return P1.pObj_ == 0; }
   friend bool operator==( TUndefinedBoolType P2, const LockedPtrBase &P1 ){ return P1.pObj_ == 0; }
   friend bool operator!=( const LockedPtrBase &P1, TUndefinedBoolType P2 ){ return P1.pObj_ != 0; }
   friend bool operator!=( TUndefinedBoolType P2, const LockedPtrBase &P1 ){ return P1.pObj_ != 0; }

};

//�������� �� ��� ����� ����������� �� ����� ������ ������� Proxy � ����� ������
template<bool Check, int Dummy>
class CDeadLockCheck
{};

//���������� Dummy ����� ��� ���� ����� �� ��������� cpp-���� ���� � ������������ ����������� ����������
template<int Dummy>
class CDeadLockCheck<true, Dummy>
{
   //����� � set ������� �������������� ������� � ������� ��� ������ ������ Proxy
   typedef std::set<DWORD> TThreadsID;
   typedef ObjectLevelLockable< CDeadLockCheck<true, Dummy> > TMutex;
   static TThreadsID m_ThreadsID;
   static TMutex m_Mutex;

public:
   CDeadLockCheck()
   {
      TMutex::Lock Guard( m_Mutex );

      //����������� ���� ������� ��������� �������� Proxy � ����� ������. ��. ����.
      APL_ASSERT( m_ThreadsID.insert(::GetCurrentThreadId()).second == true );
   }

   ~CDeadLockCheck()
   {
      TMutex::Lock Guard( m_Mutex );

      APL_ASSERT( m_ThreadsID.erase(::GetCurrentThreadId()) == 1 );
   }
};

template<int Dummy> typename CDeadLockCheck<true, Dummy>::TThreadsID CDeadLockCheck<true, Dummy>::m_ThreadsID;
template<int Dummy> typename CDeadLockCheck<true, Dummy>::TMutex CDeadLockCheck<true, Dummy>::m_Mutex;

//�������� ������ ������� �������� � �������� ������
template< class T >
template<class LockObj>
class LockedPtrBase<T>::Proxy: private LockObj, private CDeadLockCheck<CHECK_DEADLOCKS_FOR_POINTERS, 0>
{
   T *pObj_;

   Proxy& operator=( const Proxy& ); 
public:
   //���������� ������ �������� RVO � ������� �� ������ ��������� ����� ������ ��� ��������.
   //�������� � ����� �� ��������� � ������� �� ������������� ��� ����� �������� �� ���� ������������
   Proxy( const Proxy & ); 

   explicit Proxy( T *pObj ): pObj_(pObj), LockObj(*pObj) {}
   T *operator->() const { return pObj_; }
};

}  //namespace Detail

template <class T>
class LockedPtr: public Detail::LockedPtrBase<T>
{
public:
   /*explicit*/ LockedPtr( T *pObj = 0): Detail::LockedPtrBase<T>( pObj ) {}
};

//�������������� ��� ������������ �������
template <class T>
class LockedPtr<const T>: public Detail::LockedPtrBase<const T>
{
public:
   /*explicit*/ LockedPtr( T *pObj = 0): Detail::LockedPtrBase<const T>( pObj ) {}

   //�� ����� ��������� ������������ ��������� �������������, �� �� ��������
   LockedPtr( const LockedPtr<T> & Other ): Detail::LockedPtrBase<const T>( Other.Get() ) {}

   LockedPtr<const T> &operator=( const LockedPtr<T> & Other ) 
   {
      Set( Other.Get() );
      return *this;
   }
};

}} //namespace SS::Lib 

#endif