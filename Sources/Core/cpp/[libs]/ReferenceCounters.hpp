#ifndef ReferenceCounters_HPP
#define ReferenceCounters_HPP

///////////////////////////////////////////////////////////////////////////////
// ��������� ���������� ��������� ������
///////////////////////////////////////////////////////////////////////////////

namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
// ����� ��������� ��������� ������� ������ ������ ������ �� �������� ����� 
// ������������� � ������� ����� ����������� ��-���������.
// ��� ������ ������������ ������ Create ����� �������� �����-�� ��������� �� 
// �� ��� ���������� ��� �������� ������� � CAutoRefCount, ������� ����� 
// ���������� ���� � �����. ������� � STL ����������� � �.�. ����� ���� ��� 
// ��������� ����� ��������� ����� ��������� ������������� ��������� ����� 
// delete
///////////////////////////////////////////////////////////////////////////////
template< class ObjectT >
class CAutoRefCount
{
   //���������� ����� ������� ������������� ������ �� �������� ������
   class CImpl: public ObjectT
   {
      size_t m_RefCount;

      CImpl(): m_RefCount(1) {}
   public:
      static CImpl *Create() { return new CImpl; }

      void AddRef(){ ++m_RefCount; }
      void Release(){ APL_ASSERT( m_RefCount > 0 ); if( --m_RefCount == 0 ) delete this; }
   };

   //���������� ����������������� ���������
   template<class ResultT>
   class CPtrBase
   {
      CImpl *m_pT;

   public:                                           
      //template< class > template< class T2 > friend class CAutoRefCount<T1>::CPtrBase;
      template< class T2 > friend class CPtrBase;

      CPtrBase( CImpl *pT = 0 ): m_pT(pT) {}
      //CPtrBase( TUndefinedBoolType pT = 0 ): m_pT(0) {} //��������� �������������� ������ �� 0


      CPtrBase( const CPtrBase &Other )
      { 
         m_pT = Other.m_pT;

         if( m_pT != 0 )
            m_pT->AddRef();
      }

      ~CPtrBase()
      {
         if( m_pT != 0 )
            m_pT->Release();
      }

      void Swap( CPtrBase &Other )
      {
         std::swap(m_pT, Other.m_pT);
      }

      void Release()
      {
         if( m_pT != 0 )
         {
            m_pT->Release();
            m_pT = 0;
         }
      }

      CPtrBase &operator=( const CPtrBase &Other )
      {
         CPtrBase(Other).Swap(*this);
         return *this;
      }

      //�������� ��������� ��������� �� ���������/����������� ���� � ��������� � ���� bool
   private:  
      struct OperatorHelper{ int i; }; //��. ��������������(loki)
      typedef int OperatorHelper::*TUndefinedBoolType;
   public:
      //�������� ��������� ��������� �� ���������/����������� ���� � ��������� � ���� bool
      operator TUndefinedBoolType() const { return m_pT != 0? &OperatorHelper::i : 0; }

      ResultT *Get() const { return m_pT; }
      ResultT &operator*() const { APL_ASSERT( Get() != 0 ); return *Get(); }
      ResultT *operator->() const { return &**this; }
  
      //���� �� ���������� �� ����� �������������� �������������� �������������� � TUndefinedBoolType
      //� ���������� ���������
      friend bool operator==( const CPtrBase &P1, const CPtrBase &P2 ){ return P1.m_pT == P2.m_pT; }
      friend bool operator!=( const CPtrBase &P1, const CPtrBase &P2 ){ return P1.m_pT != P2.m_pT; }

      //���� �� ���������� �� ��� �������� P1 == 0, 0 == P1, P1 != 0, 0 != P1 ��������� 
      //��������������� �.�. ���������� �� explicit
      friend bool operator==( const CPtrBase &P1, TUndefinedBoolType P2 ){ return P1.m_pT == 0; }
      friend bool operator==( TUndefinedBoolType P2, const CPtrBase &P1 ){ return P1.m_pT == 0; }
      friend bool operator!=( const CPtrBase &P1, TUndefinedBoolType P2 ){ return P1.m_pT != 0; }
      friend bool operator!=( TUndefinedBoolType P2, const CPtrBase &P1 ){ return P1.m_pT != 0; }


   protected:
      template< class T >
         CPtrBase( const CPtrBase<T> &Other ) //�������� ����������� �� �������� ����������� �� ���������
      { 
         m_pT = Other.m_pT;

         if( m_pT != 0 )
            m_pT->AddRef();
      }

      template< class T >
         CPtrBase &operator=( const CPtrBase<T> &Other ) //�������� �������� ������������ �� �������� �������� ������������ �� ���������
      {
         CPtrBase(Other).Swap(*this);
         return *this;
      }
   };
public:

   //���������������� ��������� ����������� �������� Create
   class SmartPtr: public CPtrBase<ObjectT>
   {
   public:
      SmartPtr( CImpl * pImpl = 0 ): CPtrBase<ObjectT>(pImpl){}
   };

   //����������� ����-�� ��������� (��������� �������� ������ ������ � const ObjectT)
   //����� ���� ������������� �� SmartPtr, �� �� ��������
   class ConstSmartPtr: public CPtrBase<const ObjectT>
   {
   public:
      ConstSmartPtr( CImpl * pImpl = 0 ): CPtrBase<const ObjectT>(pImpl){}
      ConstSmartPtr( const SmartPtr &SM ): CPtrBase<const ObjectT>(SM) {}
      ConstSmartPtr &operator=( const SmartPtr &SM ){ CPtrBase<const ObjectT>::operator=(SM); return *this; }
   };

   //������ ����� ������ ���� ObjectT
   static SmartPtr Create(){ return SmartPtr( CImpl::Create() ); }
};

}} //namespace SS::Lib 

#endif
