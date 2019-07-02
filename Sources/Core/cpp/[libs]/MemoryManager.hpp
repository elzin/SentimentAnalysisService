///////////////////////////////////////////////////////////////////////////////
// ������ �������� ���������� ���������� �� ���������� ����������� � ������ � 
// �������, ������������, ����� � �.�.
///////////////////////////////////////////////////////////////////////////////
#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include "LikePointer.hpp"

namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
// ��� ��������
// ��������� ��������� � ������� �������, ������ ��� �������� ������� �� 
// ������������ ��������� � ����������� �� ��� ��� ���� � ��� ����� �� ��������� 
// �������������. ��� �������� ��� �������������� �������� �� ��������� 
// ��������/�������� ��������.
// � ����������� ��� ������� ����������� � ���� ������������.
//
// ������ ������ ������� ������������ � ��� ������ ����� ������� ����� ��������� � 
// ������������ � ������� �� �� ��������������� �/��� ���������� ������������.
//
// ��������� �������
// ObjectT - ��� �������� ������� �������������� ���������
// InitStrategyT - ��������� ������������� � �������� �������� ObjectT
///////////////////////////////////////////////////////////////////////////////
 
///////////////////////////////////////////////////////////////////////////////
// ������� ��������� ��� ��������� ������������� � �������� ����������� ��������
// ��� ������������ �������� ��������� ������ ������������� �� ��������� ���������
// ������� �� ������������� ������ ������. ��������� ��������� � TObjectsPool
// � �������� ���������� ��������� InitStrategyT
///////////////////////////////////////////////////////////////////////////////
template<class ObjectT>
struct TObjectsPoolBaseInitStrategy
{
   typedef ObjectT TObject;
   
   //������� ������ � ��� ���������� ������� ������ �������� sizeof(ObjectT)
   //� TObjectsPoolBaseInitStrategy ������������ placement new � ����������� ��-���������
   void Construct( void *pBuf ) const { new(pBuf) ObjectT(); }
   
   //���������� ������ pT, �� ���������� ��� ���� ������� �� ������ pT, �.�.
   //������� ���������� ������� pT (��� ���� ������ �����������), ��� ����
   //�� ������� �������� delete ��� pT
   //� TObjectsPoolBaseInitStrategy ������������ ����� �����������
   void Destroy( TObject &Obj ) const { Obj.~ObjectT(); }
   
   //����������� ������ ObjectT � ���������� �������������.
   //������� � ��������� ��������� ������ ����� ��� ��� ��, ������ ������� 
   //�������������� ��������, ������ �����������, ��� ������� � ���, ����� 
   //����� ��������� ������� �� ����.
   //� TObjectsPoolBaseInitStrategy ������� ������ �� ������
   void ReInit( TObject &Obj ) const { /*��-��������� ������ �� ������*/ }
};

template<class ObjectT, class InitStrategyT = TObjectsPoolBaseInitStrategy<ObjectT> >
class TObjectsPool: private InitStrategyT, public NonCopyable
{ 
   // �������� ������� ������������� � ��������� ������������� ������ - ��� � ����
   // ������� �������� �������. ��� �������� ������� ���� ��� �� ���� ������ ����������� 
   // �� ����, � ���� ���� �� �������� ����� ������.

private:   
   //������� ����, �������� ��� ������ � �������� �� ��������� ����� �� ������� 
   //��� ����������� ������. ������ ������� �� ������ ����������� � ������������ � 
   //�������� ����.
   struct TStoreData: NonCreateable
   {
      ObjectT Object; //���������� ������ 
   
   private:    
      friend class TObjectsPool;
      TStoreData *pNext;  //��������� ������� ������

   private:
      ~TStoreData(); //������� �������������� C4624
   };

   template<class Iterator, class Value>
   struct TObjectSelector: SelectorHelper<Iterator, Value> 
   {
      reference operator ()( origin_iterator_reference V ) const { return V.Object; }
   };

public:
   //��������� �� ����������� ������
   typedef CSelectIterator< TStoreData *, TObjectSelector< TStoreData *, ObjectT> > TPointer;
   typedef CSelectIterator< const TStoreData *, TObjectSelector< const TStoreData *, const ObjectT> > TConstPointer;

private: 
   //������� ����� ��������� �������� �� �������������� ��� ������������ ����������
   template< class T >  
   struct TObjectsPoolDeleteStrategyBase: public auto_ptr_ex_strategy_base<T, TPointer> {};
   
   template< class T >
   struct TObjectsPoolDeleteStrategyBase<const T>: public auto_ptr_ex_strategy_base<T, TConstPointer> {};

public:
   //��������� �������� ��� ������� auto_ptr_ex � �������� 
   template< class T >
   class TObjectsPoolDeleteStrategy: public TObjectsPoolDeleteStrategyBase<T> 
   {
      TObjectsPool *m_pObjectsPool;  
      
   public: 
      //�� explicit
      TObjectsPoolDeleteStrategy( TObjectsPool *pObjectsPool ): m_pObjectsPool(pObjectsPool) {}

      template< class Y >
         TObjectsPoolDeleteStrategy( const TObjectsPoolDeleteStrategy<Y> &Other ): m_pObjectsPool(Other.m_pObjectsPool) {}

      template< class Y >
         TObjectsPoolDeleteStrategy &operator=( const TObjectsPoolDeleteStrategy<Y> &Other ) { m_pObjectsPool = Other.m_pObjectsPool; return *this; }

      void operator()( pointer pT ) const { if(pT != 0){ APL_ASSERT_PTR(m_pObjectsPool); m_pObjectsPool->Dealloc(pT); } }

      TObjectsPool &GetObjectsPool() const { APL_ASSERT_PTR(m_pObjectsPool); return *m_pObjectsPool; }
   };

public:
   //���� smart-����������
   typedef auto_ptr_ex<ObjectT, TObjectsPoolDeleteStrategy> TAutoPtr;
   typedef auto_ptr_ex<const ObjectT, TObjectsPoolDeleteStrategy> TConstAutoPtr;

private:
   TStoreData *m_pFirst; //������ ����, ���������� ������
   
public:
   explicit TObjectsPool(const InitStrategyT &IS): InitStrategyT(IS), m_pFirst(0) {}
   TObjectsPool(): m_pFirst(0) {}
   ~TObjectsPool() { Clear(); } 

   //��������� ����������� �� ����������
   const InitStrategyT &GetInitStrategy() const { return *this; }
   void SetInitStrategy( const InitStrategyT &IS ) { static_cast<InitStrategyT &>(*this) = IS; }

   //��������� ��������� �� ������� � ������������� ������ ObjectT. ����� ������������� ������� 
   //��� ���������� ���������� ������� Dealloc
   TPointer Allo�Ptr()
   {
      if( m_pFirst == 0 )
      {
         TPointer RetVal( static_cast<TStoreData *>(operator new(sizeof(TStoreData))) );
         InitStrategyT::Construct(&*RetVal);
         
         return RetVal;   
      }
      else
      {
         TStoreData *pCur = m_pFirst;
         m_pFirst = pCur->pNext;

         InitStrategyT::ReInit(pCur->Object);
         return TPointer(pCur);
      }
   }
   
   //��������� smart ��������� �� ������� � ������������� ������ ObjectT. ����� �������������
   //smart ��������� ������������� ���������� ������ (�������� Dealloc �� ����)
   TAutoPtr Alloc()
   {
      return TAutoPtr(Allo�Ptr(), this);
   }

   //������������ ������� ����������� ��� ������ ������ Allo�Ptr, ����� �������������
   void Dealloc( TPointer pObject )
   {
      pObject.GetOriginIterator()->pNext = m_pFirst;
      m_pFirst = pObject.GetOriginIterator();
   }

   //�������� ���� �������� ���������� � ����
   void Clear()
   {
      TStoreData *pCur;

      while( m_pFirst != 0 )
      {
         pCur = m_pFirst;
         m_pFirst = m_pFirst->pNext;
        
         InitStrategyT::Destroy(pCur->Object);
         operator delete( pCur );
      }
   }
};

}} //namespace SS::Lib 
#endif // MEMORYMANAGER_HPP

