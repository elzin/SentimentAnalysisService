#pragma once

namespace SS{ 
namespace Dictionary{
namespace Detail{


///////////////////////////////////////////////////////////////////////////////
// ����� ��������� ����������� � ������ �������� (Unicode ��� �������), ����� ������ (true/false)
// ��������� � ������������� �����, ��� ������ �������� �����.
// ���������� � ���������� ������ ���� ��������
// ����� �������� � ����� ����� ����� ������� ��� Unicode
// CharT - ��� �������
// FlagCount - ���������� ������ �������������� � ������ ��������
// AndFlagsCount - ���������� ������ �� FlagCount ������� ��� �������� ������ �������� 
//    ����� ����������� ��� ������ �������� "�" ��������� ������� ������������ ��� 
//    ������ �������� "���"
// ����� ������ ����������� ������� ��������� � ������������� �����
///////////////////////////////////////////////////////////////////////////////
template<class CharT, size_t FlagCount, size_t AndFlagsCount = FlagCount>
class CSymbolCharacteristic: public NonCopyable
{
private:
   typedef CharT TChar;
   typedef unsigned short TFlagsInternal;
   typedef std::vector<TFlagsInternal> TItems; 

public:
   class TItem
   {
      TFlagsInternal m_Data;

   public:
      TItem(TFlagsInternal Data): m_Data(Data) {}

      bool test(size_t Bit) const{ return (m_Data & (1 << Bit)) != 0; }
   };

private:
   TItems m_Items;
   static const TFlagsInternal m_OrMask = TFlagsInternal(~TFlagsInternal(0) << AndFlagsCount);

private:
   //���������� ����� ������ ��� �������� �������
   TFlagsInternal GetFlagsImpl( TChar C ) const { APL_ASSERT( C >= 0 && C < m_Items.size() ); return m_Items[C]; }

   //���������� ����� ������ ��� ���������� �������� ������ ��� ������� 
   //������������ �������� ����������� � � ����������� ���, ��� ������ ������ 
   //������� ������������ �� ��� ���� �������� ������������ ��� ������ ��������� AndFlagsCount
   TItem GetFlagsImpl( const TChar *pString, Int2Type<0> ) const
   {
      APL_ASSERT_PTR( pString );
      TFlagsInternal AndValues = ~TFlagsInternal(0);
      TFlagsInternal OrValues = 0;

      for( ; *pString != 0; ++pString )
      {
         AndValues &= GetFlagsImpl(*pString);
         OrValues |= GetFlagsImpl(*pString);
      }

      return AndValues | (OrValues & m_OrMask);
   }

   TItem GetFlagsImpl( const TChar *pString, Int2Type<1> ) const
   {
      APL_ASSERT_PTR( pString );
      TFlagsInternal AndValues = ~TFlagsInternal(0);

      for( ; *pString != 0; ++pString )
      {
         AndValues &= GetFlagsImpl(*pString);
      }

      return AndValues;
   }

   template <class InputIterator>
   TItem GetFlagsImpl( InputIterator First, InputIterator Last, Int2Type<0> ) const
   {
      TFlagsInternal AndValues = ~TFlagsInternal(0);
      TFlagsInternal OrValues = 0;

      for( ; First != Last; ++First )
      {
         AndValues &= GetFlagsImpl(*First);
         OrValues |= GetFlagsImpl(*First);
      }

      return AndValues | (OrValues & m_OrMask);
   }

   template <class InputIterator>
   TItem GetFlagsImpl( InputIterator First, InputIterator Last, Int2Type<1> ) const
   {
      TFlagsInternal AndValues = ~TFlagsInternal(0);
      TFlagsInternal OrValues = 0;

      for( ; First != Last; ++First )
      {
         AndValues &= GetFlagsImpl(*First);
      }

      return AndValues;
   }


public:
   CSymbolCharacteristic(): m_Items( std::numeric_limits<CharT>::max() + 1 )
   { APL_ASSERT(AndFlagsCount <= FlagCount && sizeof(TFlagsInternal)* CHAR_BIT >= FlagCount); }
   
   //���������� ����� ������ ��� �������� �������
   TItem GetFlags( TChar C ) const { return GetFlagsImpl(C); }

   //���������� ����� ������ ��� ���������� �������� ������ ��� ������� 
   //������������ �������� ����������� � � ����������� ���, ��� ������ ������ 
   //������� ������������ �� ��� ���� �������� ������������ ��� ������ ��������� AndFlagsCount
   TItem GetFlags(const std::basic_string<TChar> &Str ) const
   {  return GetFlags( Str.begin(), Str.end() );  }

   TItem GetFlags( const TChar *pString ) const
   {  return GetFlagsImpl(pString, Int2Type<FlagCount == AndFlagsCount>()); }

   template <class InputIterator>
   TItem GetFlags( InputIterator First, InputIterator Last ) const
   {  return GetFlagsImpl(First, Last, Int2Type<FlagCount == AndFlagsCount>()); }

   //���������� � ������ �������� ���� FlagN
   //Clear - ������� �� � ��������� �������� FlagN
   template <class InputIterator>
   void SetFlags( InputIterator First, InputIterator Last, size_t FlagN, bool Clear = true )
   {
      APL_ASSERT( FlagN < FlagCount );
      
      if( Clear )
         for( size_t i = 0; i < m_Items.size(); ++i ) 
            m_Items[i] &= ~(1 << FlagN);

      for( ; First != Last; ++First )
      {
         APL_ASSERT( *First >= 0 && *First < m_Items.size() );

         m_Items[*First] |= 1 << FlagN;
      }
   }

   //���������� � ���� ��������, ����� ��� ������� ������������ � ������, ���� FlagN
   template <class InputIterator>
   void SetFlagsInvert( InputIterator First, InputIterator Last, size_t FlagN )
   {
      APL_ASSERT( FlagN < FlagCount );

      for( size_t i = 0; i < m_Items.size(); ++i ) 
         m_Items[i] |= 1 << FlagN;

      for( ; First != Last; ++First )
      {
         APL_ASSERT( *First >= 0 && *First < m_Items.size() );

         m_Items[*First] &= ~(1 << FlagN);
      }
   }


   //���������� � ������� ���� FlagN
   void SetFlags( TChar C, size_t FlagN )
   {
      APL_ASSERT( FlagN < FlagCount );
      APL_ASSERT( C >= 0 && C < m_Items.size() );

      m_Items[C] |= 1 << FlagN;
   }


   //���������� � ���� �������� ���� FlagN
   void SetFlags( size_t FlagN )
   {
      APL_ASSERT( FlagN < FlagCount );

      for( size_t i = 0; i < m_Items.size(); ++i ) 
         m_Items[i] |= 1 << FlagN;
   }


   //���������� � ������ �������� ���� FlagN �� �������� ������
   //hModule - ������ � ������� ��������� �������
   //ResourceType - ��� ������� 
   //ResourceID - ������������� �������
   //Clear - ������� �� � ��������� �������� FlagN
   void SetFlags( HMODULE hModule, const TCHAR *ResourceType, WORD ResourceID, size_t FlagN, bool Clear = true )
   {
      const TChar* pData;
      size_t Size;

      if( LoadResource(hModule, ResourceType, ResourceID, pData, Size) != ERROR_SUCCESS )
         APL_THROW(_T("������ ��� ������ ������� ResourceType = ") << ResourceType << _T(", ResourceID = ") << ResourceID );
      
      SetFlags( pData,  pData + Size, FlagN, Clear );
   }

   //���������� ���������� ������ �������
   size_t MemSize() const { return m_Items.capacity() * sizeof(m_Items[0]);  }
};

///////////////////////////////////////////////////////////////////////////////
// ����� ������������ ������ ��� ��������� ����������
///////////////////////////////////////////////////////////////////////////////
class TConstData
{
public:
   typedef AssocVector<std::wstring, std::wstring> TString2String;
   typedef AssocVector<wchar_t, wchar_t> TChar2Char;

private:
   TString2String m_EngNegationReduction;
   TChar2Char m_PreSearchTransform;


public:
   //��������� TString2String �� �������
   //hModule - ������ � ������� ��������� �������
   //ResourceType - ��� ������� 
   //ResourceID - ������������� �������
   static void LoadFromResource( HMODULE hModule, const TCHAR *ResourceType, WORD ResourceID, TString2String &String2String );
   

   //��������� TChar2Char �� �������
   //hModule - ������ � ������� ��������� �������
   //ResourceType - ��� ������� 
   //ResourceID - ������������� �������
   static void LoadFromResource( HMODULE hModule, const TCHAR *ResourceType, WORD ResourceID, TChar2Char &Char2Char );

   //����������: ����� ����� ����� �������� ����� n't � ������������ �����, ��� ���������� � not
   TString2String &GetEngNegationReduction(){ return m_EngNegationReduction; }
   const TString2String &GetEngNegationReduction() const { return m_EngNegationReduction; }
   
   //������������� �������� ����� ����� ������� �� ����� �����
   TChar2Char &GetPreSearchTransform(){ return m_PreSearchTransform; }
   const TChar2Char &GetPreSearchTransform() const { return m_PreSearchTransform; }
};


} //namespace Detail
} //namespace Dictionary
} //namespace SS
