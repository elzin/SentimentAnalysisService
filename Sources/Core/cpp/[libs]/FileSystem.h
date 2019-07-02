#ifndef FileSystem_H
#define FileSystem_H

#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include "StlAuxiliary.h"

/*
   ������ � ������� � �������� ��������
*/

namespace SS { namespace Lib {

//������� UNICODE �����
extern const BYTE g_UnicodeFilePrefix[2];

///////////////////////////////////////////////////////////////////////////////
// ��������������� ���������
///////////////////////////////////////////////////////////////////////////////
struct TAutoFindClose
{
   HANDLE hFind;

   TAutoFindClose( HANDLE hFind = INVALID_HANDLE_VALUE ): hFind(hFind) {}
   ~TAutoFindClose() { if(hFind != INVALID_HANDLE_VALUE) APL_CHECK(FindClose(hFind)); }
};

struct TAutoFileClose
{
   HANDLE hFile;

   TAutoFileClose( HANDLE hFile = INVALID_HANDLE_VALUE ): hFile(hFile) {}
   ~TAutoFileClose() { if(hFile != INVALID_HANDLE_VALUE) APL_CHECK(CloseHandle(hFile)); }
};


///////////////////////////////////////////////////////////////////////////////
//����� ��������� ������������� � �������� � �� ���� ��������� ��������� (���� 
//����������) ������ ������
//��� ���� ����� ����������� ����������� �� ���������� �����
///////////////////////////////////////////////////////////////////////////////
class CDirectoryFileList
{
   typedef TCHAR CharT;
   typedef std::basic_string<TCHAR> StringT;

   struct SDirItem //���������� � ��������
   {
      HANDLE Handle;                      //����� ��� FindNextFile    
      StringT::size_type DirNameSize;     //����� ������ � ��������� �������� � ������� "<���_��������>\"
      WIN32_FIND_DATA FindData;           //������ �� �������� �����

      SDirItem(): Handle(INVALID_HANDLE_VALUE), DirNameSize(0) 
	  {
		  memset(&FindData, 0, sizeof(WIN32_FIND_DATA));
	  }
   };

   typedef std::vector<SDirItem> TFindHandles;
   typedef std::vector<StringT> TExtensions;

private:
   StringT m_CurFile;                  //������� ����
   StringT m_CurDir;                   //������� �������
   StringT m_Mask;                     //����� ������
   bool m_RrecurSearch;                //������ ����� ����������
   WIN32_FIND_DATA m_FindData;         //������ �� �������� �����, ������������ ������ ��� ����������� �� ���
   TExtensions  m_Extensions;          //���������� ���������� ������

   TFindHandles m_FindHandles;         //������ ������� ���������� � ��������� ���������

private:
   //������� ������ ���� � �������� m_CurDir, �� ����� m_Mask
   void FindFirst( SDirItem &DirItem )
   {
      DirItem.Handle = FindFirstFile( (m_CurDir + _T("*")).c_str(), &DirItem.FindData );
   }

   //����� ��������� ���� � �������� DirItem, ���� ������ ����� ��� �� ����������� ����� �������� 
   //FindClose � DirItem.Handle �������������� � INVALID_HANDLE_VALUE
   void FindNextOrClose( SDirItem &DirItem )
   {
      APL_ASSERT( DirItem.Handle != INVALID_HANDLE_VALUE );

      if( FindNextFile(DirItem.Handle, &DirItem.FindData) == FALSE )
      {
         APL_CHECK( FindClose(DirItem.Handle) );
         DirItem.Handle = INVALID_HANDLE_VALUE;
      }
   }

public:  
   CDirectoryFileList(): m_RrecurSearch(true) 
   {
	   memset( &m_FindData, 0, sizeof(WIN32_FIND_DATA) );
   }
   template<class InputIterator>
      explicit CDirectoryFileList(const StringT &DirName, InputIterator First, InputIterator Last, bool Recursive = true)
   {  OpenDir(DirName, First, Last, Recursive); }

   explicit CDirectoryFileList(const StringT &DirName, bool Recursive = true)
   {  OpenDir(DirName, Recursive); }


   ~CDirectoryFileList() { Clear(); }

   //������������ ����� � DirName ���� ������ � ������������ [First, Last), � ���� Recursive == true �� � �� ���� ��������
   //���������. ��� ������ ������� ����� ���������� �������� Next()
   template<class InputIterator>
   void OpenDir( const StringT &DirName, InputIterator First, InputIterator Last, bool Recursive = true )
   {
      Clear(); 

      //��������� ������ � ������������ ��� ��������� ������
      m_Extensions.assign( First, Last );
      std::sort(m_Extensions.begin(), m_Extensions.end());

      m_CurDir = DirName;
      m_RrecurSearch = Recursive;

      if( m_CurDir[m_CurDir.size() - 1] != _T('\\') )
         m_CurDir +=  _T('\\');

      SDirItem DirItem;

      DirItem.DirNameSize = m_CurDir.size();
      FindFirst(DirItem);

      m_FindHandles.push_back( DirItem );
   }

   //������������ ����� � DirName ���� ������, � ���� Recursive == true �� � �� ���� ��������
   //���������. ��� ������ ������� ����� ���������� �������� Next()
   void OpenDir( const StringT &DirName, bool Recursive = true )
   {
      OpenDir( DirName, static_cast<const StringT *>(0), static_cast<const StringT *>(0), Recursive );
   }


   //�������� ��� ������ ������
   void Clear();

   //����� �������� (������ ����)
   bool Next();

   const StringT &GetDir() const { return m_CurDir; }
   const StringT &GetFile() const { return m_CurFile; }
   const WIN32_FIND_DATA &GetFindData() const { return m_FindData; }
};

///////////////////////////////////////////////////////////////////////////////
// ����� ��������� ��������� ������ ������ �� UNICODE ��� ANSI ������, ��� 
// ���� ��������� ��������� ���������� ��� �����.
// ����� �������� ������������������ \n\r �� \n (� ������ ������� \r)
// ����� ������� �������� ������������� � ����� ���, ������������ ����������.
///////////////////////////////////////////////////////////////////////////////
class CUnicodeFileReader: public NonCopyable
{
   typedef wchar_t TChar;
   typedef BYTE TByte;

private:   
   static const size_t BuffSize = 4 * 1024;
   //static const TByte UnicodePref[]; //������� ��� UNICODE �����
private:
   HANDLE m_hFile;
   TChar m_Buff[BuffSize];
   std::vector<CHAR> m_AuxBuff; //�������������� ����� ��� ������
   TChar *m_pBuffBegin, *m_pBuffEnd;
   bool m_IsUnicode; //�������� �� ���� ������ UNICODE
   bool m_IsEof;     //��� ��������� ����� ����� � ����������� ������ ��� ����������

private:
   
   //��������������� �����, �������� ������� �������� 
   //�������� � ����� ������ ���� �������� ����� ������
   //� ������ ������� ��� ������� \r
   void CorrectBuffer();
   
   //��������� ������ � ��������� ���������
   void FillBuffer();

public:
   struct SNoDelimCharacter: public std::unary_function<TChar, bool>
   {
      bool operator()( TChar Char ) const
      {
         return false;
      }
   };

   struct SSpaceCharacter: public std::unary_function<TChar, bool>
   {
      bool operator()( TChar Char ) const
      {
         return iswspace(Char) != 0;
      }
   };

   struct SNewLineCharacter: public std::unary_function<TChar, bool>
   {
      bool operator()( TChar Char ) const
      {
         return Char == L'\n';
      }
   };

   struct SNotAlphaNumericCharacter: public std::unary_function<TChar, bool>
   {
      bool operator()( TChar Char ) const
      {
         return !IsCharAlphaNumericW(Char) != 0;
      }
   };

public:
   CUnicodeFileReader(): m_hFile(INVALID_HANDLE_VALUE), m_pBuffBegin(0), m_pBuffEnd(0), m_IsEof(false), m_IsUnicode(false) 
   {
	   memset(m_Buff, 0, sizeof(TChar) * BuffSize);
   } 

   //������������� �������� Open
   explicit CUnicodeFileReader( LPCTSTR szFileName ): m_hFile(INVALID_HANDLE_VALUE), m_pBuffBegin(0), m_pBuffEnd(0), m_IsUnicode(false)
   {
      Open( szFileName );
   }

   //������� ����
   void Close() 
   { 
      if( m_hFile != INVALID_HANDLE_VALUE )
      { 
         ::CloseHandle(m_hFile); 
         m_hFile = INVALID_HANDLE_VALUE; 
      } 

      m_pBuffBegin = m_pBuffEnd;
   } 

   //�������������� �������� �����
   ~CUnicodeFileReader(){ Close(); }

   //����� �� ���������� ������ �����
   bool Eof() const { return m_pBuffBegin == 0; }

   enum EOpenResult 
   { 
      EOROk,              //���� ������ ������, ����� �������� ������
      EORCantOpen,        //������ ��� �������� �����
      //EORUndefinedFromat  //���� ������ �� ����� �������� ������
   };

   //������� ����� ���� (������������� ����������� ������� �������� ����)
   EOpenResult Open( LPCTSTR szFileName );

   //��������� �� ����� ������ ������� �������� �� ������ ���������� ���������
   //������ ������ ����� ����������� �.�. ������ ������������ �� ��������� �� ����
   //Str - ��������� �� ������ �������� ������� MaxLen
   //MaxLen - ������ ������ (������� ����� ��� '\0')
   //CurLen - ����� �������� ������
   //IsDelim - �������� ������������ true ���� ������ - �����������
   //�����: true - ���� ������� �������� ������ ����� � Str
   template<class TCmp>
   bool Read( TChar *Str, size_t MaxLen, size_t &CurLen, TCmp IsDelim )
   {
      APL_ASSERT_PTR( Str );
      
      bool CurDelim;
      TChar *pBegWord;
      ptrdiff_t FindSize; 

      CurLen = 0;

      if( Eof() )
      {
         *Str = _T('\0');
         return false;
      }

      --MaxLen; //�� ������ ��������� '\0'

      for(;;) 
      {
         pBegWord = m_pBuffBegin;

         //������� �����������, ���� �� ����, �� �� ����� ������ �����
         CurDelim = false;
         while( m_pBuffBegin != m_pBuffEnd && MaxLen > 0 && !(CurDelim = IsDelim(*m_pBuffBegin))  ){ ++m_pBuffBegin; --MaxLen; }

         //�������� �� ��� �����
         FindSize = m_pBuffBegin - pBegWord;

         //�������� ��������� std::copy, � ������� Str ����������, 
         //�� ��� ���������� � ����� ���������� memmove, ��� ��������� � ����� ������ ��� memcpy
         std::memcpy( Str, pBegWord, FindSize * sizeof(*pBegWord) ); 
         CurLen += FindSize;
         Str += FindSize;

         if( CurDelim ) //�� ��������� ��������� ����������� ������
         {
            ++m_pBuffBegin; //��������� �����������
            *Str = _T('\0');
           
            //��������� �����, ���� ����������
            if( m_pBuffBegin == m_pBuffEnd ) FillBuffer();

            return true;
         }

         //��������� �����, ���� ����������
         if( m_pBuffBegin == m_pBuffEnd ) FillBuffer();

         //�� ��� � �� ����� �����������, �� ������ ��� ��������
         if( MaxLen == 0 ) 
         {
            *Str = _T('\0');
            return m_pBuffBegin == m_pBuffEnd; //�������� �������� ����, ����� �� ����� ������ ������
         }

         //�������� �������� ����
         if( m_pBuffBegin == m_pBuffEnd )
         {
            *Str = _T('\0');
            return true;
         }
      }
   }

   //��������� �� ����� ������ ������� �������� �� ������ ���������� ���������
   //������ ������ ����� ����������� �.�. ������ ������������ �� ��������� �� ����
   //Str - �������� ������
   //IsDelim - �������� ������������ true ���� ������ - �����������
   //�����: true - ���� ������� �������� ������ ����� � Str
   template<class TCmp>
   bool Read( std::basic_string<TChar> &Str, TCmp IsDelim )
   {
      bool CurDelim;
      TChar *pBegWord;

      Str.clear();

      if( Eof() ) return false;

      for(;;) 
      {
         pBegWord = m_pBuffBegin;

         //������� �����������, ���� �� ����, �� �� ����� ������ �����
         CurDelim = false;
         while( m_pBuffBegin != m_pBuffEnd && !(CurDelim = IsDelim(*m_pBuffBegin))  ){ ++m_pBuffBegin; }

         //�������� �� ��� �����         
         Str.append( pBegWord, m_pBuffBegin );

         if( CurDelim ) //�� ��������� ��������� ����������� ������
         {
            ++m_pBuffBegin; //��������� �����������

            //��������� �����, ���� ����������
            if( m_pBuffBegin == m_pBuffEnd ) FillBuffer();

            return true;    
         }

         //��������� �����, ���� ����������
         if( m_pBuffBegin == m_pBuffEnd ) FillBuffer();

         //�������� �������� ����
         if( m_pBuffBegin == m_pBuffEnd )
         {
            return true;
         }
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
// �������� ��� ����������� � ����� �� ������ �������� � ������
// From -  �� ���� ����������
// To -    ���� ����������
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD CopyDirectory( const std::basic_string<TCHAR> &From, const std::basic_string<TCHAR> &To );

///////////////////////////////////////////////////////////////////////////////
// ������� ������� � ��� ��������� ����� � ��������
// Dir -  ��������� �������
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD DeleteDirectory( const std::basic_string<TCHAR> &Dir );

///////////////////////////////////////////////////////////////////////////////
// ������ ��� �������� �� ���� Dir, ���� ��� ��� �� �������. �.�. ����� ������
// ������� ����� ���� ��������� ��� � ������� ���������� ���� Dir (�� ����������� 
// ������������� ����� ���� ��������� ������)
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD CreateFullPath( const std::basic_string<TCHAR> &Dir );

///////////////////////////////////////////////////////////////////////////////
// ����� ��������� ��������� �� ����� ����� (������������������ �� ���� ��� ����)
///////////////////////////////////////////////////////////////////////////////
class CFileWordReader
{
   std::ifstream m_flIn;
   std::string m_Buf;
   std::string::iterator m_Cur;

private:
   bool ValidChar( char C ) const
   {
      return IsCharAlphaNumericA(C) == TRUE;
   }

public:
   CFileWordReader(): m_Cur(m_Buf.end()) {}
   CFileWordReader( const char *FileName ): m_Cur(m_Buf.end()) { OpenFile(FileName); }

   bool OpenFile( const char *FileName )
   {
      m_flIn.close();
      m_flIn.clear();
      m_Cur = m_Buf.end();
      m_flIn.open(FileName);

      return m_flIn.good();
   }

   bool Get( std::string &Str );

   std::ifstream &GetStream() {return m_flIn;}
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// �������� ����� �������� ������
///////////////////////////////////////////////////////////////////////////////
template< class CharT, class CharTraitsT>
inline void ClearIStreamBuff( std::basic_istream<CharT, CharTraitsT> &IStream )
{
   IStream.clear();
   IStream.ignore(IStream.rdbuf()->in_avail());
}

///////////////////////////////////////////////////////////////////////////////
// ��������� �������� � ���� UNICODE ������
// OStream ���������� ��������� � �������� ������
///////////////////////////////////////////////////////////////////////////////
inline std::ostream &WriteUnicode( std::ostream &OStream, std::wstring Str )
{
   return OStream.write( 
      reinterpret_cast<const char *>(Str.c_str()), 
      static_cast<std::streamsize>( sizeof(std::wstring::value_type) * Str.size() ) 
   );
}

inline std::ostream &WriteUnicode( std::ostream &OStream, const wchar_t *Str )
{
   return OStream.write( 
      reinterpret_cast<const char *>(Str), 
      static_cast<std::streamsize>( sizeof(*Str) * lstrlenW(Str) ) 
   );
}

///////////////////////////////////////////////////////////////////////////////
// ��������� ������ Str �� UNICODE ����� c ������ FileName
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD ReadUnicodeFile( const std::basic_string<TCHAR> &FileName, std::basic_string<WCHAR> &Str );

///////////////////////////////////////////////////////////////////////////////
// �������� ������ Str � UNICODE ���� c ������ FileName
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD WriteUnicodeFile( const std::basic_string<TCHAR> &FileName, const std::basic_string<WCHAR> &Str );

///////////////////////////////////////////////////////////////////////////////
// �������� ������ Str � ANSI ���� c ������ FileName
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD WriteAnsiFile( const std::basic_string<TCHAR> &FileName, const std::basic_string<WCHAR> &Str );

///////////////////////////////////////////////////////////////////////////////
// ��������� ������ Str �� UNICODE ��� ANSI ����� (������ ������������ �������������) c ������ FileName
// ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError � ������ �������
///////////////////////////////////////////////////////////////////////////////
DWORD ReadUnicodeAnsiFile( const std::basic_string<TCHAR> &FileName, std::basic_string<WCHAR> &Str );

///////////////////////////////////////////////////////////////////////////////
// ��������� ������ �� ���������� ����� ������ ��� ������ �������� ���� T
//    hModule - ������ � ������� ��������� �������
//    ResourceType - ��� ������� 
//    ResourceID - ������������� ������� 
//    pData - ��������� �� ������. ������������ ������ ����� ������������� 
//       �� ��������� - �� ���� ��������� Windows
//    Size - ���������� �������� ���� T �� ������� ���������� Size
//    ����� - ERROR_SUCCESS - ������� ���������� ��� �������� �� GetLastError 
//       � ������ �������. ���� �� ������� �������� �� ������ ������ ���� T, ��
//       ����� ERROR_INVALID_DATA.
///////////////////////////////////////////////////////////////////////////////
template<class T>
DWORD LoadResource( HMODULE hModule, const TCHAR *ResourceType, WORD ResourceID, T *&pData, size_t &Size )
{
   APL_ASSERT( hModule );
   APL_ASSERT_PTR( ResourceType );

   HRSRC hResource;
   HGLOBAL hMemory;
   DWORD ResourceSize;

   hResource = ::FindResource( hModule, MAKEINTRESOURCE(ResourceID), ResourceType );
   if( !hResource ) return GetLastError();

   ResourceSize = ::SizeofResource( hModule, hResource ); 
   if( !ResourceSize ) return GetLastError();
   
   if( ResourceSize % sizeof(T) != 0 ) return ERROR_INVALID_DATA;

   Size = ResourceSize / sizeof(T);

   hMemory = ::LoadResource( hModule, hResource );
   if( !hMemory ) return GetLastError();

   pData  = (T *)::LockResource( hMemory );
   if( !pData ) return ERROR_INVALID_DATA;


   return ERROR_SUCCESS;
}


}} //namespace SS::Lib 

#endif