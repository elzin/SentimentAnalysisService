#ifndef StlAuxiliary_H
#define StlAuxiliary_H

/*
   ������ ������������� ��������� ������� � ������� ������� ����� ������� ����������� stl
*/

namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
// ������ ���
///////////////////////////////////////////////////////////////////////////////
class NullType {};

///////////////////////////////////////////////////////////////////////////////
// ��������� ����������� �������
///////////////////////////////////////////////////////////////////////////////
class NonCopyable
{
protected:
   NonCopyable() {}
   ~NonCopyable() {}
private:  
   NonCopyable( const NonCopyable& );
   NonCopyable& operator=( const NonCopyable& ); 
};

///////////////////////////////////////////////////////////////////////////////
// ��������� ��������� ����� ����� ������� ������� �������� ����������� � 
// ������� ����� ������� ������� �������� ����������.
// �������� ��� ����� ������������ ��� ���������� ������ �������� ��������.
// ��� �������������� ��������������� (C4624) � ��� ��� ���������� �� ����� ���� 
// ������������ ���� ���� ��� �������� (�� ����������) � ���������� ������
///////////////////////////////////////////////////////////////////////////////
struct NonCreateable 
{
private:
   NonCreateable();    
   ~NonCreateable();  
};

////////////////////////////////////////////////////////////////////////////////
// class template Int2Type
// Converts each integral constant into a unique type
// Invocation: Int2Type<v> where v is a compile-time constant integral
// Defines 'value', an enum that evaluates to v
// ���������� �� loki
////////////////////////////////////////////////////////////////////////////////
template <int v>
struct Int2Type
{
   enum { value = v };
};

////////////////////////////////////////////////////////////////////////////////
// class template Type2Type
// Converts each type into a unique, insipid type
// Invocation Type2Type<T> where T is a type
// Defines the type OriginalType which maps back to T
// ���������� �� loki
////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct Type2Type
{   
   typedef T OriginalType;
   Type2Type(){} // VC7
};

////////////////////////////////////////////////////////////////////////////////
// class template Select
// Selects one of two types based upon a boolean constant
// Invocation: Select<flag, T, U>::Result
// where:
// flag is a compile-time boolean constant
// T and U are types
// Result evaluates to T if flag is true, and to U otherwise.
// ���������� �� loki
////////////////////////////////////////////////////////////////////////////////
template <bool flag, typename T, typename U>
struct Select
{
private:
   template<bool>
   struct In 
   { typedef T Result; };

   template<>
   struct In<false>
   { typedef U Result; };

public:
   typedef typename In<flag>::Result Result;
};


////////////////////////////////////////////////////////////////////////////////
// class template IsSameType
// Return true if two given types are the same
// Invocation: IsSameType<T, U>::value
// where:
// T and U are types
// Result evaluates to true if U == T (types equal)
// ���������� �� loki
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
struct IsSameType
{
private:
   template<typename>
   struct In 
   { enum { value = false }; };

   template<>
   struct In<T>
   { enum { value = true };  };

public:
   enum { value = In<U>::value };
};

///////////////////////////////////////////////////////////////////////////////
// ������� ������������ const, ���� ������� ������� � ����.
// ���������� �� loki
///////////////////////////////////////////////////////////////////////////////
template <class U> struct UnConst
{
   typedef U Result;
   enum { isConst = 0 };
};

template <class U> struct UnConst<const U>
{
   typedef U Result;
   enum { isConst = 1 };
};

////////////////////////////////////////////////////////////////////////////////
// class template Conversion
// Figures out the conversion relationships between two types
// Invocations (T and U are types):
// a) Conversion<T, U>::exists
// returns (at compile time) true if there is an implicit conversion from T
// to U (example: Derived to Base)
// b) Conversion<T, U>::exists2Way
// returns (at compile time) true if there are both conversions from T
// to U and from U to T (example: int to char and back)
// c) Conversion<T, U>::sameType
// returns (at compile time) true if T and U represent the same type
//
// Caveat: might not work if T and U are in a private inheritance hierarchy.
// ���������� �� loki
////////////////////////////////////////////////////////////////////////////////

template <class T, class U>
struct Conversion
{
   template <class T2, class U2>
   struct ConversionHelper
   {
      typedef char Small;
      struct Big { char dummy[2]; };
      static Big   Test(...);
      static Small Test(U2);
      static T2 MakeT();
   };
  
   typedef ConversionHelper<T, U> H;
#ifndef __MWERKS__
   enum { exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT()))) };
#else
   enum { exists = false };
#endif
   enum { exists2Way = exists && Conversion<U, T>::exists };
   enum { sameType = false };
};

template <class T>
struct Conversion<T, T>    
{
   enum { exists = 1, exists2Way = 1, sameType = 1 };
};

template <class T>
struct Conversion<void, T>    
{
   enum { exists = 0, exists2Way = 0, sameType = 0 };
};

template <class T>
struct Conversion<T, void>    
{
   enum { exists = 0, exists2Way = 0, sameType = 0 };
};

template <>
struct Conversion<void, void>    
{
public:
   enum { exists = 1, exists2Way = 1, sameType = 1 };
};

///////////////////////////////////////////////////////////////////////////////
// �������� �� ������ ���� �������, ������ � ��� ������ ���� ��� ��������. 
// ���� �������� ���������� �� ������ ��� �������� �� ������������ �� ���������
// ���������:
//    T1 t1;
//    T2 t2(TryConvertOrCreate<T1, T2>::Get(t1));
// ��������� 2:
//    T1 t1;
//    T2 t2;
//    t2 = TryConvertOrCreate<T1, T2>::Get(t1);
// ������� ������:
//    ���� �������� �������������� �� T1 � T2 �� ������� Get ��������� ������ 
//    �� t1 � t2 ��������� ��������� �� t1, � ���� �������������� �� ����������
//    �� Get ��������� T2 ��������� ��� ������ ������������ �� ��������� � t2
//    ��������� �� ������������ �����������.
///////////////////////////////////////////////////////////////////////////////
namespace Private
{
template<class FromT, class ToT, bool Flag>
struct TryConvertOrCreateHelper
{
   static const FromT &Get( const FromT &From ) { return From; }
};

template<class FromT, class ToT>
struct TryConvertOrCreateHelper<FromT, ToT, false>
{
   static ToT Get( const FromT &From ) { return ToT(); }
};
} //namespace Private

template<class FromT, class ToT>
struct TryConvertOrCreate: Private::TryConvertOrCreateHelper<FromT, ToT, Conversion<FromT, ToT>::exists>{};

///////////////////////////////////////////////////////////////////////////////
// ��������� ������� ���������� ���������������� � ������ ������ ��������
///////////////////////////////////////////////////////////////////////////////
template< class T >
class CObjectCount
{
   static size_t m_N;

private:
   static void Increment(){ APL_ASSERT(m_N < std::numeric_limits<size_t>::max() ); ++m_N; }
   static void Decrement(){ APL_ASSERT( m_N > 0 ); --m_N; }

public:
   CObjectCount() { Increment(); }
   CObjectCount( const CObjectCount& ) { Increment(); }
   ~CObjectCount() { Decrement(); }

   static size_t Count(){ return m_N; }
};

template< class T >
size_t CObjectCount<T>::m_N = 0;

///////////////////////////////////////////////////////////////////////////////
// ���������������� ������ � ������ ����� ���� int
// ������ �������� ������ ����� ��������� ������:
//    [ws][sn][ddd]
// ���:
//    [ws]  = �������������� ������� ��� ���������;
//    [sn]  = �������������� ���� (+ ��� -);
//    [ddd] = ������������ �����;
//
// Beg  = �������� ������� � �������� ������� �������������;
// End  = �������� ����� ������;
//
// ��� ����������� ������� ���������������� ������� ��� ��� ���������� End
// ������� ���������� ��������������, ���������� �������� �������� �������
// � ���������� ������������ ����� � Val (���� �� ����������� �� ������ �����
// �� 0). ���� �� ����������� �� ���� ����� �� ���������� Beg
// ������� �� ��������� ����� �� ������������
///////////////////////////////////////////////////////////////////////////////
template<class InputIterator, class T>
InputIterator ConvertStringToInteger( InputIterator Beg, InputIterator End, T &Val )
{
//� ����� � ��� ��� ��� ������� ��� �������� ������� ������������ � ���� ������� � UNICODE �������������
//����� ��� �� ��� ��� � � ANSI (������ 16 ������) ����� ������������ ���� ������� ��� ��� UNICODE ��� � ��� 
//ANSI �����
#ifdef WIDE_PREF
   #error "��� �������� WIDE_PREF"
#endif

#define WIDE_PREF( arg ) /*L##arg*/ arg

   bool IsNegate = false;

   InputIterator BegBack(Beg); //��������� ������� ���������� ���������

   Val = 0;

   //���������� �������
   while( Beg != End && (*Beg == WIDE_PREF('\t') || *Beg == WIDE_PREF(' ') ) ) ++Beg;

   if( Beg == End ) return BegBack;

   //����������� �� ������
   if( *Beg == WIDE_PREF('-') )
   {
      IsNegate = true;
      ++Beg;
   }
   else if( *Beg == WIDE_PREF('+') )
   {
      ++Beg;
   }

   InputIterator FirstDigit(Beg); //��������� ������� �������������� ������ �����

   //�������� ������������ �����
   while( Beg != End && (*Beg >= WIDE_PREF('0') && *Beg <= WIDE_PREF('9')) )
   {
      Val = 10 * Val + *Beg - WIDE_PREF('0');
      ++Beg;
   }

   if( Beg == FirstDigit ) //�� �� ������������� �� ���� �����
      return BegBack;

   #pragma warning( push )
   #pragma warning( disable: 4146 )
   if( IsNegate ) Val = -Val;
   #pragma warning( pop )

   return  Beg;

#undef WIDE_PREF
}

///////////////////////////////////////////////////////////////////////////////
// ������������� ����� ���� int � ������, ���� ����� ������������� ��� �� ��������� ���� '-'
// Val - ������������� �����
// [Beg, End) - ������ � ������� ����� �������� ����������� ������������� ����������� �����
// �����: �������� ������� �� ��������� ���������� ��������. ���� ��������� [Beg, End) ���
//        ������ ���� �������� ����� �� ������� ������������ Beg
//
// ������� �� ���������� � ����� '\0' � ������� ��� ������ � ������ �������
// ����� ������ ���������� End = Beg + RG_SIZE - 1, ��� RG_SIZE - ������ ������� 
// ��� ���� ����� �������� ���� ������� ��� '\0'
///////////////////////////////////////////////////////////////////////////////

template<class InputIterator, class T>
InputIterator ConvertIntegerToString( T Val, InputIterator Beg, InputIterator End )
{
   InputIterator Cur(Beg);        //������� ������
   InputIterator FirstDigit(Beg); //������ ���������� �����
   T Radix(10);                   //���� ������� ����������
   
   if( Val < 0 ) //���� ����� ������������� ������� ����
   {
      if( Cur == End ) return Beg;

      #pragma warning( push )
      #pragma warning( disable: 4146 )
      Val = -Val;
      #pragma warning( pop )

      *Cur = '-';
      ++Cur;
      ++FirstDigit;
   }

   do
   {
      if( Cur == End ) return Beg;

      *Cur = (Val % Radix) + '0';   
      ++Cur;

      Val /= Radix;
   }
   while( Val > 0 );

   InputIterator RetVal(Cur); //�������� ������� �� ��������� ���������� ��������

   //�� �������� ����������� �����. �������������� ���������� �������
   --Cur;

   while( FirstDigit < Cur ) 
   {
      //���������� Radix, ��� ��������� ����������
      Radix = *Cur; *Cur = *FirstDigit; *FirstDigit = Radix;
      ++FirstDigit;
      --Cur;
   } 

   return RetVal;
}

///////////////////////////////////////////////////////////////////////////////
//��������� ���� ��� � stl::mismatch, �� ���������� ��� ��� �� ������� �����
//������ �������� ��� �� ������ ��� ������. �.�. ������� ��������������� ���
//��� first1 != last1 ��� � ��� first2 != last2
///////////////////////////////////////////////////////////////////////////////
template <class InputIterator1, class InputIterator2>
std::pair<InputIterator1, InputIterator2>
Mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, InputIterator2 last2 )
{
   while( first1 != last1 && first2 != last2 && *first1 == *first2 )
   {
      ++first1;
      ++first2;
   }

   return std::pair< InputIterator1, InputIterator2 >( first1, first2 );
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
std::pair<InputIterator1, InputIterator2>
Mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, InputIterator2 last2, BinaryPredicate binary_pred )
{
   while( first1 != last1 && first2 != last2 && binary_pred(*first1, *first2) )
   {
      ++first1;
      ++first2;
   }

   return std::pair< InputIterator1, InputIterator2 >( first1, first2 );
}

}} //namespace SS::Lib 

#endif