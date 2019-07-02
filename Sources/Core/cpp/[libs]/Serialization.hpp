#ifndef Serialization_H
#define Serialization_H

#include <objbase.h>
#include <msxml.h>
#include <sstream>
#include "Atlbase.h"
#include "Auxiliary.h"


/*
   ����� ������� ������� ��������� ��������� XML ������ ��������� � ��������� ������ ������ ���������
   ������� � �����������.
   
   ��� ���� ����� ��������������� �����������/��������� ����������� �������� (����� ��� int, double, 
   std::string ) ������ ��������� [������� 1] 

   [������� 1: ������]
      ��������� ��� ������ ������ ����������� ������� ReadFromStream, WriteToStream. 
      ���������� ���� ������� ��-��������� ������� ���������� >> � << ��������������, 
      ��� ������� ������������ ������.

      template< class ObjectT, class CharT, class CharTraitsT >
      void WriteToStream( std::basic_ostream<CharT, CharTraitsT> &Ostream, const ObjectT &Object );

      template< class ObjectT, class CharT, class CharTraitsT >
      void ReadFromStream( std::basic_istream<CharT, CharTraitsT> &Istream, ObjectT &Object );

      ���� ������ ���������� >> � << �����������������, �� ���������� ������ �� �����������.
   [������� 1: �����]


   ��� ���� ����� ��������������� �����������/��������� ������ ����� (��� ���������) � ������� 
   ��������� ��������� ��������� ���������� ������ ��������� [������� 2] 

   [������� 2: ������]
      ����� ������ ���������� �����:       
      template< class Archive > void Serialize( Archive &A ) 

      ���� ����������� ������� 

      template< class Archive >void SS::Lib::Serialize ( Archive &A, T& ob )
      ��� T ����� ������� ��������� ������/������.

      Archive - ����� ������� ��������� ���������/���������� ��� ��������� ����������, 
      ��� � ��������� ������ � ����������, ����� ����-�� ���������:*/
#if 0
      //���������/��������� ��������� ���� ob ��������� ������ (class ��� struct) ��� ������ Name
      //��� ���� T ������ ��������� [������� 1]
      void Element( const TChar *Name, /*const*/ T &ob );

      //���������/��������� ��������� ���� ��������� ������ (class ��� struct) ob ��� ������ Name
      //��� ���� T ������ ��������� [������� 1] 
      //Accessor - ����� ������� ��������� �������� ������ � ����� ��������� ������ [������� 3]
      template< class T, class AccessorT >
      void Element( const TChar *Name, /*const*/ T &ob, AccessorT Accessor );

      //���������/��������� ��������� ��������� ob ��������� ������ (class ��� struct) ��� ������ Name
      //��� ���� T ������ ��������� [������� 2]
      template< class T >
      void Group( const TChar *Name, /*const*/ T &ob );

      //���������/��������� ��������� ��������� ob ��������� ������ (class ��� struct) ��� ������ Name
      //��� ���� T ������ ��������� [������� 2] 
      //Accessor - ����� ������� ��������� �������� ������ � ����� ��������� ������ [������� 3]
      template< class T, class AccessorT >
      void Group( const TChar *Name, /*const*/ T &ob, AccessorT Accessor );

      //���������/��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
      //ob �������� ������� �������� ��� ������� ������ ����������� [������� 1].
      //������ ��������� ������� ����������� ��� ������ ItemName
      template< class T >
      void STLContainerElement( const TChar *Name, const TChar *ItemName, /*const*/ T &ob );
      
      //���������/��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
      //ob �������� ������� �������� ��� ������� ������ ����������� [������� 1].
      //������ ��������� ������� ����������� ��� ������ ItemName
      //Accessor - ����� ������� ��������� �������� ������ � ��������� [������� 3]
      template< class T, class AccessorT >
      void STLContainerElement( const TChar *Name, const TChar *ItemName, /*const*/ T &ob, AccessorT Accessor );

      //���������/��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
      //ob �������� �������� ������ ��� ������� ������ ����������� [������� 2].
      //������ ��������� ������� ����������� ��� ������ ItemName
      template< class T >
      void STLContainerGroup( const TChar *Name, const TChar *ItemName, /*const*/ T &ob );
      
      //���������/��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
      //ob �������� �������� ������ ��� ������� ������ ����������� [������� 2].
      //������ ��������� ������� ����������� ��� ������ ItemName
      //Accessor - ����� ������� ��������� �������� ������ � ��������� [������� 3]
      template< class T, class AccessorT >
      void STLContainerGroup( const TChar *Name, const TChar *ItemName, /*const*/ T &ob, AccessorT Accessor );
#endif
/*
   [������� 2: �����]

   [������� 3: ������]
      ��������� AccessorT
      ���������� ����������� ���������������� �� ����������� ���� ��������� 
      ���������� ��� ������ ��������� Accessor � �������� ������ CWriteArchive. ��� ���� Accessor
      ������ ������������ ���� �� ����-��� �����������.

      interface AccessorT
      {
         typedef ... ValueType; //��������� ��� � �������� ����������� ������

         //����� � ��������� ������ �������� ���������� �����
         ValueType Get( Object &Obj ) const;  

         //���������� � ��������� ������ �������� ���������� �����
         void Set( Object &Obj, ValueType Val ) const;
      };

      interface AccessorT
      {
         typedef ... ValueType; //��������� ��� � �������� ����������� ������

         //����� � ��������� ������ �������� ���������� �����
         const ValueType &Get( Object &Obj ) const;

         //���������� � ��������� ������ �������� ���������� �����
         void Set( Object &Obj, const ValueType & Val ) const;
      };
   [������� 3: �����]

   ��� ������ ���������� �������������� ����� CWriteArchive. ����� ������� �����: */
#if 0  
   //��������� ��� �������� ��������� � ��� ��������� � �� ��������� � �����
   //Name - �������� ����� ��������� ������
   //ob - ������ �� ��������� ������ (class ��� struct)
   //��� ���� T ������ ��������� [������� 2]
   template< class T > void Save( const TChar *Name,  T &ob );
#endif
/*
   ��� ������ ���������� �������������� ����� CReadArchive. ����� ������� �����: */
#if 0  
   //��������� ��� �������� ��������� � ��� ��������� � �� ��������� � �����
   //Name - �������� ����� ��������� ������
   //ob - ������ �� ��������� ������ (class ��� struct)
   //��� ���� T ������ ��������� [������� 2]
   template< class T > void Load( const TChar *Name,  T &ob );
#endif


#if 0
//������� ������ (����� ������� ��. Test\Serialization\Main.cpp)
struct Foo
{
   int m_A;
   double m_B;
   std::basic_string<TCHAR> m_C;

   Foo(): m_A(1), m_B(-12.3e55), m_C(_T("Any String")) {}

   template< class Archive >
   void Serialize( Archive &A ) 
   {
      A.Element( _T("a"), m_A );
      A.Element( _T("b"), m_B );
      A.Element( _T("c"), m_C );
   }
};

struct Bar
{
   Foo F1;
   Foo F2;
   std::basic_string<TCHAR> m_Name;
   
   Bar(): m_Name(_T("Any Name")) {}

   template< class Archive >
   void Serialize( Archive &A ) 
   {
      A.Element( _T("name"), m_Name );
      A.Group( _T("foo1"), F1 );
      A.Group( _T("foo2"), F2 );
   }

   basic_string<TCHAR> GetXML()
   {
      basic_stringstream<TCHAR> Stream;
      Bar B;
      CWriteArchive<basic_stringstream<TCHAR> > Archive(Stream);
      Archive.Save( _T("bar"), B );
      return Stream.str();
   }
};

/* GetXML() ����������:
<bar>
	<name>Any Name</name>
	<foo1>
		<a>1</a>
		<b>-1.23e+056</b>
		<c>Any String</c>
	</foo1>
	<foo2>
		<a>1</a>
		<b>-1.23e+056</b>
		<c>Any String</c>
	</foo2>
</bar>
*/

#endif

namespace SS { namespace Lib {

///////////////////////////////////////////////////////////////////////////////
// ������� �������������� �������� ��-���������, �� ����������� �������� ��� � 
// ������� ����������
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ��������� �� ��������� ��� ������� ������� ����������� ������-������.
// ����� ������ Serialize. ����� ����������� ��� ��������� �������, � �� ������
// �������-����.
///////////////////////////////////////////////////////////////////////////////
template< class Archive, class T >
void Serialize( Archive &A, T& ob )
{
   ob.Serialize( A );
}

///////////////////////////////////////////////////////////////////////////////
// ������ � ����� ��-���������. ����� ��������� <<
///////////////////////////////////////////////////////////////////////////////
template< class ObjectT, class CharT, class CharTraitsT >
void WriteToStream( std::basic_ostream<CharT, CharTraitsT> &Ostream, const ObjectT &Object )
{
   Ostream << Object;
}

///////////////////////////////////////////////////////////////////////////////
// ������ �� ������ ��-���������. ����� ��������� >>
///////////////////////////////////////////////////////////////////////////////
template< class ObjectT, class CharT, class CharTraitsT >
void ReadFromStream( std::basic_istream<CharT, CharTraitsT> &Istream, ObjectT &Object )
{
   Istream >> Object;
}

template< class CharT, class CharTraitsT >
void ReadFromStream( std::basic_istream<CharT, CharTraitsT> &Istream, std::basic_string<CharT, CharTraitsT> &Object )
{
   std::getline( Istream, Object );
}


///////////////////////////////////////////////////////////////////////////////
// ������ ����������� ���������������� �� ����������� ������� �����. 
// ���������� ������ ����� ������ ������ ����������� ������ ����������� ���������� � 
// �������� ������� ����� �� ������ ������.
// ������� ����������� ����� ������� ���� ����������� ����, ��� ���� ��������� ������� 
// � ������. ��� ���� ����� ������� ��, ��� ������ �� ������������, �.�. ������� ����������� 
// ������ ���������� ����� ������� �������, � ����� ����� ������.
// ������ ����� ��������� ���� � �� �� ����������. ����� �� ��� ����������� 
// ������ ��� ���������������� ������ � ������.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
//�������� ��� ���� ������� �������� ������ ��� ������
//Ostream - ����� ������� ���������� �������� << ��� ������ ����������, ����
//          ��� �������� ����������� ������� WriteToStream
template < class CharT, class CharTraitsT = std::char_traits<CharT> >
interface Writer
{
protected:
   typedef std::basic_ostream< CharT, CharTraitsT > TOstream;
   typedef typename CharT TChar; 
   
   explicit Writer( TOstream &Os );

   //������ ����� ������� ����������� � ������ Name
   void BeginLevel( const TChar *Name );
   
   //��������� ������� ����������� � ������ Name
   void EndLevel( const TChar *Name );
   
   //��������� Ob � ������ Name
   //T ������ ��������� [������� 1]
   template< class T >
   void SaveItem( const TChar *Name, const T &Ob );

   //������/��������� ����������
   void BeginSave();
   void EndSave();
};
*/
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
//�������� ��� ���� ������� �������� ������ ��� ������
//Istream - ����� ������� ���������� �������� >> ��� ����� ����������, ����
//          ��� �������� ����������� ������� ReadFromStream
template < class IstreamT >
interface Reader
{
protected:
   typedef std::basic_istream< CharT, CharTraitsT > TIstream;  
   typedef typename CharT TChar;  
   
   //������, ������������� ���������� ���������� ������
   class TFindCursor{};
 
   explicit Reader( TIstream &Is );

   //������� �� ������� Name
   void BeginLevel( const TChar *Name );
   
   //����� � ������ Name
   void EndLevel( const TChar *Name );
   
   //��������� Ob � ������ Name
   //T ������ ��������� [������� 1]
   template< class T >
   void LoadItem( const TChar *Name, T &Ob );

   //���������������� ����� ���� ��������� � ������ Name
   void FindInit( const TChar *Name, TFindCursor &FindCursor );
   
   //����� ��������� (� �.�. ������) ������� � �������� ��� �������� � ob.
   //FindCursor - ������ ���� ������� ��������������� �������� FindInit
   //����� - true ������� ������� �������, false - ������� ����� �� �������
   //T ������ ��������� [������� 1]
   template< class T >
   bool FindNext( TFindCursor &FindCursor, T &Ob);

   //����� ��������� (� �.�. ������) �������.
   //FindCursor - ������ ���� ������� ��������������� �������� FindInit
   //����� - true ������� ������� �������, false - ������� ����� �� �������
   template< class T >
   bool FindNext( TFindCursor &FindCursor);

   //������/��������� ��������
   void BeginLoad();
   void EndLoad();
};
*/
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ ����� ������: ���������� ������ � XML
// �� �������� ������� ( �������� "<" �� "&lt;" � �.�. )  
///////////////////////////////////////////////////////////////////////////////
template <  class CharT, class CharTraitsT = std::char_traits<CharT> >
class CSimpleXMLWriter
{
protected:
   typedef std::basic_ostream< CharT, CharTraitsT > TOstream;
   typedef typename CharT TChar;

private:
   TOstream &m_Os;

private:
   //������� � ����� ������������� ���
   void OpenTag( const TChar *Name )
   {
      //��� ��� Unicode ��� � ��� ANSI ����� ������ (static_cast<TChar>) ����� ��������
      m_Os << static_cast<TChar>('<') << Name << static_cast<TChar>('>');
   }
   
   //������� � ����� ������������� ���
   void CloseTag( const TChar *Name )
   {
      //��� ��� Unicode ��� � ��� ANSI ����� ������ (static_cast<TChar>) ����� ��������
      m_Os << static_cast<TChar>('<') << static_cast<TChar>('/') << Name << static_cast<TChar>('>');
   }

protected:
   explicit CSimpleXMLWriter( TOstream &Os ): m_Os(Os) {}

   //������ ����� ������� ����������� � ������ Name
   void BeginLevel( const TChar *Name )
   {
      OpenTag( Name );   
   }
   
   //��������� ������� ����������� � ������ Name
   void EndLevel( const TChar *Name )
   {
      CloseTag( Name );
   }

   //��������� ������ Ob � ������ Name
   //T ������ ��������� [������� 1]
   template< class T >
   void SaveItem( const TChar *Name, const T &Ob )
   {
      OpenTag( Name );   
      WriteToStream(m_Os, Ob);
      CloseTag( Name );
   }

   //������/��������� ��������
   void BeginSave() {}
   void EndSave() {}
};

///////////////////////////////////////////////////////////////////////////////
// ������ ����� ������: ������ � XML ��� ������ MSXML
// �� �������� ������� ( �������� "<" �� "&lt;" � �.�. )  
///////////////////////////////////////////////////////////////////////////////

struct CCOMBase
{
   CCOMBase()
   {
      //��� ����� �� �������� ���� �������� CoInitialize � ������������
      //� CoUninitialize � �����������, �� ��� ���������� ������ �.�.
      //"��� �������� ��� ������� ��� �������"
      ::CoInitialize(NULL);
   }
   
   ~CCOMBase()
   {
      ::CoUninitialize();
   }

};
///////////////////////////////////////////////////////////////////////////////

//������ � ����� ������ BSTR
template < class CharT, class CharTraitsT >
void WriteBSTRToStream( std::basic_ostream< CharT, CharTraitsT > &Ostream, BSTR Str )
{
   std::basic_string<CharT, CharTraitsT> StrTmp;
   Convert( std::wstring(Str), StrTmp );
   WriteToStream( Ostream, StrTmp );
}

template < class CharTraitsT >
void WriteBSTRToStream( std::basic_ostream< WCHAR, CharTraitsT > &Ostream, BSTR Str )
{
   //� ���� ������ ������� �������������� �� �����
   WriteToStream( Ostream, static_cast<const WCHAR *>(Str) );
}
///////////////////////////////////////////////////////////////////////////////

//��������� �� ������ ������ BSTR
template < class CharT, class CharTraitsT >
void ReadBSTRFromStream( std::basic_istream< CharT, CharTraitsT > &Istream, CComBSTR &Str )
{ 
   Str.Empty();

   CharT Buff[1024];

   do 
   {
      Istream.read( Buff, APL_ARRSIZE(Buff) );
      CComBSTR TmpStr(Istream.gcount(), Buff);
      Str.Append(TmpStr);   

   } while(Istream.gcount() == APL_ARRSIZE(Buff));
}

template < class CharTraitsT >
void ReadBSTRFromStream( std::basic_istream< WCHAR, CharTraitsT > &Istream, CComBSTR &Str )
{ 
   //����������� ����������� ��������� �������
   Str.Empty();

   WCHAR Buff[1024];

   do 
   {
      Istream.read( Buff, APL_ARRSIZE(Buff) );
      Str.Append(Buff, Istream.gcount());   

   }
   while(Istream.gcount() == APL_ARRSIZE(Buff));

}


//��������������� ����������� ������ � �������������
template< class T >
static T &RemoveConst( const T & Obj )
{
   //������� �� ������� ������������ const_cast, �� ����� ������� �� ��������� �.�. 
   //����� Serialize ��������� ������������� ������
   return const_cast<T &>(Obj);
}

///////////////////////////////////////////////////////////////////////////////
// ������ � XML ��� ������ MSXML
///////////////////////////////////////////////////////////////////////////////
template < class CharT, class CharTraitsT = std::char_traits<CharT> >
class CXMLWriter: public CCOMBase
{
   typedef CComPtr<IXMLDOMDocument> TDOMDocument;
   typedef CComPtr<IXMLDOMElement> TDOMElement;
   typedef CComPtr<IXMLDOMNode> TDOMNode;
   typedef CComPtr<IXMLDOMText> TDOMText; 

protected:
   typedef std::basic_ostream< CharT, CharTraitsT > TOstream;
   typedef std::basic_ostringstream< CharT, CharTraitsT > TStringStream;
   typedef typename CharT TChar;

private:
   TOstream &m_Os;
   TDOMDocument m_DOMDocument;
   TDOMNode m_CurRootNode;
    
protected:
   explicit CXMLWriter( TOstream &Os ): m_Os(Os) {}

   //������/��������� ��������
   void BeginSave() 
   {
      m_DOMDocument.Release();
      m_CurRootNode.Release();

      if( m_DOMDocument.CoCreateInstance(__uuidof(DOMDocument)) != S_OK  )
         APL_THROW( _T("������ ��� �������� DOMDocument") );

      APL_CHECK_S_OK( m_DOMDocument.QueryInterface(&m_CurRootNode) );
   }

   void EndSave() 
   {
      CComBSTR Xml;
      BSTR TmpStr = 0;
      
      //���� ������������ &Xml ��� �������� �� BoundsChecker 7.2, ������������� �������� �� ������ ������
      m_DOMDocument->get_xml( &TmpStr ); 
      Xml.Attach(TmpStr);
      
      WriteBSTRToStream( m_Os, Xml );
   }


   //������ ����� ������� ����������� � ������ Name
   void BeginLevel( const TChar *Name )
   {
      TDOMElement Element;
      CComBSTR tagName( Name );
      TDOMNode NewChild;

      APL_CHECK_S_OK( m_DOMDocument->createElement(tagName, &Element) );
      APL_CHECK_S_OK( m_CurRootNode->appendChild(Element, &NewChild) );

      m_CurRootNode = NewChild;
   }

   //��������� ������� ����������� � ������ Name
   void EndLevel( const TChar *Name )
   {
      TDOMNode NewChild;
      
      APL_CHECK_S_OK( m_CurRootNode->get_parentNode(&NewChild) );
      m_CurRootNode = NewChild;
   }

   //��������� ������ Ob � ������ Name
   //����� ���� �������� �������� Ostream << Ob
   template< class T >
   void SaveItem( const TChar *Name, const T &Ob )
   {
      TStringStream StringStream;
      StringStream.copyfmt( m_Os );    //����������� �����

      WriteToStream( StringStream, Ob );
      
      CComBSTR Value( StringStream.str().c_str() );
      TDOMText TextNode;
      CComBSTR tagName( Name );
      TDOMNode NewChild;

      BeginLevel( Name );
      APL_CHECK_S_OK( m_DOMDocument->createTextNode(Value, &TextNode) );
      APL_CHECK_S_OK( m_CurRootNode->appendChild(TextNode, &NewChild) );
      EndLevel( Name );
   }
};


///////////////////////////////////////////////////////////////////////////////
// ������ �� XML ��� ������ MSXMl
///////////////////////////////////////////////////////////////////////////////
template < class CharT, class CharTraitsT = std::char_traits<CharT> >
class CXMLReader: public CCOMBase
{
   typedef CComPtr<IXMLDOMDocument> TDOMDocument;
   typedef CComPtr<IXMLDOMElement> TDOMElement;
   typedef CComPtr<IXMLDOMNode> TDOMNode;
   typedef CComPtr<IXMLDOMText> TDOMText; 
   typedef CComPtr<IXMLDOMNodeList> TDOMNodeList; 

protected:
   typedef std::basic_istream< CharT, CharTraitsT > TIstream;
   typedef std::basic_stringstream< CharT, CharTraitsT > TStringStream;
   typedef typename CharT TChar;

private:
   TIstream &m_Is;
   TDOMDocument m_DOMDocument;
   TDOMNode m_CurRootNode;


private:
   //����� � ���� ParentNode ������� � ������ Name � ��������� ChildNode ��������� �� ����
   //�����: ������� �� �����
   bool FindChild( TDOMNode ParentNode, const CComBSTR &Name, TDOMNode &ChildNode )
   {
      TDOMNodeList NodeList;
      TDOMNode CurNode;
      CComBSTR NodeName;

      APL_CHECK_S_OK( ParentNode->get_childNodes(&NodeList) );

      long Length, i;

      APL_CHECK_S_OK( NodeList->get_length(&Length) );

      for( i = 0; i < Length; ++i )
      {
         CurNode.Release();
         NodeName.Empty();
         APL_CHECK_S_OK( NodeList->get_item(i, &CurNode) );
         APL_CHECK_S_OK( CurNode->get_nodeName(&NodeName) );

         if( Name == NodeName )
            break;
      }

      if( i != Length )
      {
         ChildNode = CurNode;

         return true;
      }

      return false;
   }

   //��������� ����� ���� 
   //T ������ ��������� [������� 1]
   template< class T >
   void ReadNode( TDOMNode Node, T &Ob )
   {
      TDOMNode TextNode;
      DOMNodeType NodeType;
      CComVariant Value;
      TDOMNodeList NodeList;
      long Length, i;

      APL_CHECK_S_OK( Node->get_childNodes(&NodeList) );
      APL_CHECK_S_OK( NodeList->get_length(&Length) );

      for( i = 0; i < Length; ++i )
      {
         TextNode.Release();
         APL_CHECK_S_OK( NodeList->get_item(i, &TextNode) );
         APL_CHECK_S_OK( TextNode->get_nodeType(&NodeType) );

         if( NodeType == NODE_TEXT )
            break;
      }

      TStringStream Stream;
      Stream.copyfmt(m_Is);   //����������� �����

      if( i < Length )
      {
         //��� ������ ������ ������ ��������� ������� �� ��������
         //APL_THROW( _T("� �������� �� ������ �� ���� ��������� �������") );

         APL_CHECK_S_OK( TextNode->get_nodeValue(&Value) );
         APL_ASSERT( Value.vt == VT_BSTR );

         WriteBSTRToStream( Stream, Value.bstrVal );
      }

      ReadFromStream( Stream, Ob );
   }

protected:
   //������, ������������� ���������� ���������� ������
   struct TFindCursor
   {
   private:
      CComBSTR ElementName;   //��� �������� ��������
      TDOMNodeList NodeList;  //������� ������ �����
      TDOMNode RootNode;      //����, ������� ��� ������� ������ �� ������ ������

      friend class CXMLReader;   
   };

   explicit CXMLReader( TIstream &Is ): m_Is(Is) {}

   //������/��������� ��������
   void BeginLoad()
   {
      m_DOMDocument.Release();
      m_CurRootNode.Release();

      if( m_DOMDocument.CoCreateInstance(__uuidof(DOMDocument)) != S_OK  )
         APL_THROW( _T("������ ��� �������� DOMDocument") );
      
      APL_CHECK_S_OK( m_DOMDocument->put_async( FALSE ) );
      APL_CHECK_S_OK( m_DOMDocument->put_resolveExternals( FALSE ) );
      APL_CHECK_S_OK( m_DOMDocument.QueryInterface(&m_CurRootNode) );
      
      CComBSTR Str;
      VARIANT_BOOL isSuccessful;
      ReadBSTRFromStream( m_Is, Str );

      if( m_DOMDocument->loadXML( Str, &isSuccessful ) != S_OK || !isSuccessful/*isSuccessful != TRUE */) // isSuccessful ������-�� ����� -1
         APL_THROW( _T("������ ��� �������� XML") );
   }

   void EndLoad(){}

   //������� �� ������� Name
   void BeginLevel( const TChar *Name )
   {
      TDOMNode CurNode;

      if( !FindChild(m_CurRootNode, Name, CurNode) )
         APL_THROW( _T("�� ������ ������� � ������ ") << Name );

      m_CurRootNode = CurNode;
   }

   //����� � ������ Name
   void EndLevel( const TChar *Name )
   {
      TDOMNode NewChild;

      APL_CHECK_S_OK( m_CurRootNode->get_parentNode(&NewChild) );
      m_CurRootNode = NewChild;
   }

   //��������� Ob � ������ Name
   //T ������ ��������� [������� 1]
   template< class T >
   void LoadItem( const TChar *Name, T &Ob )
   {
      TDOMNode CurNode;

      if( !FindChild(m_CurRootNode, Name, CurNode) )
         APL_THROW( _T("�� ������ ������� � ������ ") << Name );
      
      ReadNode(CurNode, Ob);
   }

   //���������������� ����� ���� ��������� � ������ Name
   void FindInit( const TChar *Name, TFindCursor &FindCursor )
   {
      FindCursor.ElementName = Name;
      FindCursor.NodeList.Release();
      FindCursor.RootNode = m_CurRootNode;
      APL_CHECK_S_OK( m_CurRootNode->get_childNodes(&FindCursor.NodeList) );
   }

   //����� ��������� (� �.�. ������) �������.
   //FindCursor - ������ ���� ������� ��������������� �������� FindInit
   //����� - true ������� ������� �������, false - ������� ����� �� �������
   //T ������ ��������� [������� 1]
   template< class T >
   bool FindNext( TFindCursor &FindCursor, T &Ob)
   {
      TDOMNode CurNode;
      CComBSTR NodeName;

      for( ;; )
      {
         CurNode.Release();
         if( FindCursor.NodeList->nextNode(&CurNode) != S_OK )
         {
            m_CurRootNode = FindCursor.RootNode;
            return false;
         }

         NodeName.Empty();
         APL_CHECK_S_OK( CurNode->get_nodeName(&NodeName) );

         if( NodeName == FindCursor.ElementName )
         {
            ReadNode(CurNode, Ob);
            return true;
         }
      }
   }

   bool FindNext( TFindCursor &FindCursor )
   {
      TDOMNode CurNode;
      CComBSTR NodeName;

      for( ;; )
      {
         CurNode.Release();
         if( FindCursor.NodeList->nextNode(&CurNode) != S_OK )
         {
            m_CurRootNode = FindCursor.RootNode;
            return false;
         }

         NodeName.Empty();
         APL_CHECK_S_OK( CurNode->get_nodeName(&NodeName) );

         if( NodeName == FindCursor.ElementName )
         {
            m_CurRootNode = CurNode;
            return true;
         }
      }
   }

};

///////////////////////////////////////////////////////////////////////////////
// ����� ��� ������ ����������. 
// Writer - ����� ����������� ������ ������
///////////////////////////////////////////////////////////////////////////////
template<class CharT, template<class, class> class WriterT = CXMLWriter, class CharTraits = std::char_traits<CharT> >
class CWriteArchive: public WriterT<CharT, CharTraits>
{
public:
   typedef WriterT<CharT, CharTraits> TWriter;
   typedef typename TWriter::TChar TChar;
   typedef typename TWriter::TOstream TOstream;

public:
   //����������� ������ ����������� ��������� ������ �� �����
   explicit CWriteArchive( TOstream &Os ): TWriter( Os ) {}
   
   //��������� ��� �������� ��������� � ��� ��������� � �� ��������� � �����
   //Name - �������� ����� ��������� ������
   //ob - ������ �� ��������� ������ (class ��� struct)
   //��� ���� T ������ ��������� [������� 2]
   template< class T >
   void Save( const TChar *Name, /*const*/ T &ob )
   {
      TWriter::BeginSave();
      TWriter::BeginLevel( Name );
      Serialize( *this, ob );
      TWriter::EndLevel( Name );
      TWriter::EndSave();
   }

   //��������� ��������� ���� ob ��������� ������ (class ��� struct) ��� ������ Name
   //��� ���� T ������ ��������� [������� 1]
   template< class T >
   void Element( const TChar *Name, /*const*/ T &ob )
   {
      TWriter::SaveItem( Name, ob );
   }

   //��������� ��������� ���� ��������� ������ (class ��� struct) ob ��� ������ Name
   //��� ���� T ������ ��������� [������� 1] 
   //Accessor - ����� ������� ��������� �������� ������ � ����� ��������� ������ [������� 3]
   template< class T, class AccessorT >
   void Element( const TChar *Name, /*const*/ T &ob, AccessorT Accessor )
   {
      TWriter::SaveItem( Name, Accessor.Get(ob) );
   }

   //��������� ��������� ��������� ob ��������� ������ (class ��� struct) ��� ������ Name
   //��� ���� T ������ ��������� [������� 2]
   template< class T >
   void Group( const TChar *Name, /*const*/ T &ob )
   {
      TWriter::BeginLevel( Name );
      Serialize( *this, ob );
      TWriter::EndLevel( Name );
   }

   //��������� ��������� ��������� ob ��������� ������ (class ��� struct) ��� ������ Name
   //��� ���� T ������ ��������� [������� 2] 
   //Accessor - ����� ������� ��������� �������� ������ � ����� ��������� ������ [������� 3]
   template< class T, class AccessorT >
   void Group( const TChar *Name, /*const*/ T &ob, AccessorT Accessor )
   {
      TWriter::BeginLevel( Name );
      Serialize( *this, RemoveConst(Accessor.Get(ob)) );
      TWriter::EndLevel( Name );
   }

   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� ������� �������� ��� ������� ������ ����������� [������� 1].
   //������ ��������� ������� ����������� ��� ������ ItemName
   template< class T >
   void STLContainerElement( const TChar *Name, const TChar *ItemName, /*const*/ T &ob )
   {
      TWriter::BeginLevel( Name );
      
      for( typename T::const_iterator I = ob.begin(); I != ob.end(); ++I )
         TWriter::SaveItem( ItemName, *I );

      TWriter::EndLevel( Name );
   }
   
   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� ������� �������� ��� ������� ������ ����������� [������� 1].
   //������ ��������� ������� ����������� ��� ������ ItemName
   //Accessor - ����� ������� ��������� �������� ������ � ��������� [������� 3]
   template< class T, class AccessorT >
   void STLContainerElement( const TChar *Name, const TChar *ItemName, /*const*/ T &ob, AccessorT Accessor )
   {
      TWriter::BeginLevel( Name );
      
      for( typename AccessorT::ValueType::const_iterator I = Accessor.Get(ob).begin(); I != Accessor.Get(ob).end(); ++I )
         TWriter::SaveItem( ItemName, *I );

      TWriter::EndLevel( Name );
   }

   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� �������� ������ ��� ������� ������ ����������� [������� 2].
   //������ ��������� ������� ����������� ��� ������ ItemName
   template< class T >
   void STLContainerGroup( const TChar *Name, const TChar *ItemName, /*const*/ T &ob )
   {
      TWriter::BeginLevel( Name );

      for( typename T::iterator I = ob.begin(); I != ob.end(); ++I )
      {
         TWriter::BeginLevel( ItemName );
         Serialize( *this, *I );
         TWriter::EndLevel( ItemName );
      }

      TWriter::EndLevel( Name );
   }
   
   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� �������� ������ ��� ������� ������ ����������� [������� 2].
   //������ ��������� ������� ����������� ��� ������ ItemName
   //Accessor - ����� ������� ��������� �������� ������ � ��������� [������� 3]
   template< class T, class AccessorT >
   void STLContainerGroup( const TChar *Name, const TChar *ItemName, /*const*/ T &ob, AccessorT Accessor )
   {
      TWriter::BeginLevel( Name );

      for( typename AccessorT::ValueType::const_iterator I = Accessor.Get(ob).begin(); I != Accessor.Get(ob).end(); ++I )
      {
         TWriter::BeginLevel( ItemName );
         Serialize( *this, RemoveConst(*I) );
         TWriter::EndLevel( ItemName );
      }

      TWriter::EndLevel( Name );
   }
};

///////////////////////////////////////////////////////////////////////////////
// ����� ��� ������ ����������. 
// Reader - ����� ����������� ������ ������
///////////////////////////////////////////////////////////////////////////////
template<class CharT, template<class, class> class ReaderT = CXMLReader, class CharTraits = std::char_traits<CharT> >
class CReadArchive: public ReaderT<CharT, CharTraits>
{
public:
   typedef ReaderT<CharT, CharTraits> TReader;
   typedef typename TReader::TChar TChar;
   typedef typename TReader::TIstream TIstream;
   typedef typename TReader::TFindCursor TFindCursor;


public:
   //����������� ������ ����������� ��������� ������ �� �����
   CReadArchive( TIstream &Is ): TReader( Is ) {}
   
   //��������� ��� �������� ��������� � ��� ��������� � �� ��������� � �����
   //Name - �������� ����� ��������� ������
   //ob - ������ �� ��������� ������ (class ��� struct)
   //��� ���� T ������ ��������� [������� 2]
   template< class T >
   void Load( const TChar *Name, T &ob )
   {
      TReader::BeginLoad();
      TReader::BeginLevel( Name );
      Serialize( *this, ob );
      TReader::EndLevel( Name );
      TReader::EndLoad();
   }

   //��������� ��������� ���� ob ��������� ������ (class ��� struct) ��� ������ Name
   //��� ���� T ������ ��������� [������� 1]
   template< class T >
   void Element( const TChar *Name, T &ob )
   {
      TReader::LoadItem( Name, ob );
   }

   //��������� ��������� ���� ��������� ������ (class ��� struct) ob ��� ������ Name
   //��� ���� T ������ ��������� [������� 1] 
   //Accessor - ����� ������� ��������� �������� ������ � ����� ��������� ������ [������� 3]
   template< class T, class AccessorT >
   void Element( const TChar *Name, /*const*/ T &ob, AccessorT Accessor )
   {
      typename AccessorT::ValueType TmpOb;
      TReader::LoadItem( Name, TmpOb );
      Accessor.Set(ob, TmpOb);
   }

   //��������� ��������� ��������� ob ��������� ������ (class ��� struct) ��� ������ Name
   //��� ���� T ������ ��������� [������� 2]
   template< class T >
   void Group( const TChar *Name, T &ob )
   {
      TReader::BeginLevel( Name );
      Serialize( *this, ob );
      TReader::EndLevel( Name );
   }

   //��������� ��������� ��������� ob ��������� ������ (class ��� struct) ��� ������ Name
   //��� ���� T ������ ��������� [������� 2] 
   //Accessor - ����� ������� ��������� �������� ������ � ����� ��������� ������ [������� 3]
   template< class T, class AccessorT >
   void Group( const TChar *Name, T &ob, AccessorT Accessor )
   {
      TReader::BeginLevel( Name );
      Serialize( *this, RemoveConst(Accessor.Get(ob)) );
      TReader::EndLevel( Name );
   }

   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� ������� �������� ��� ������� ������ ����������� [������� 1].
   //������ ��������� ������� ����������� ��� ������ ItemName
   template< class T >
   void STLContainerElement( const TChar *Name, const TChar *ItemName, T &ob )
   {
      typename T::value_type TmpOb;
      TFindCursor FindCursor;

      ob.clear();

      TReader::BeginLevel( Name );

      TReader::FindInit( ItemName, FindCursor );

      while( TReader::FindNext(FindCursor, TmpOb) )
         ob.push_back( TmpOb );

      TReader::EndLevel( Name );
   }
   
   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� ������� �������� ��� ������� ������ ����������� [������� 1].
   //������ ��������� ������� ����������� ��� ������ ItemName
   //Accessor - ����� ������� ��������� �������� ������ � ��������� [������� 3]
   template< class T, class AccessorT >
   void STLContainerElement( const TChar *Name, const TChar *ItemName, T &ob, AccessorT Accessor )
   {
      typename AccessorT::ValueType TmpContainer;
      typename AccessorT::ValueType::value_type TmpValue;

      TFindCursor FindCursor;

      TReader::BeginLevel( Name );

      TReader::FindInit( ItemName, FindCursor );

      while( TReader::FindNext(FindCursor, TmpValue) )
      {
         TmpContainer.push_back(TmpValue);
      }

      TReader::EndLevel( Name );

      Accessor.Set(ob, TmpContainer);
   }

   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� �������� ������ ��� ������� ������ ����������� [������� 2].
   //������ ��������� ������� ����������� ��� ������ ItemName
   template< class T >
   void STLContainerGroup( const TChar *Name, const TChar *ItemName, T &ob )
   {
      typename T::value_type TmpOb;
      TFindCursor FindCursor;

      ob.clear();

      TReader::BeginLevel( Name );

      TReader::FindInit( ItemName, FindCursor );

      while( TReader::FindNext(FindCursor) )
      {
         Serialize( *this, TmpOb );
         ob.push_back( TmpOb );
      }

      TReader::EndLevel( Name );
   }
   
   //��������� STL ��������� ob ��������� ������ (class ��� struct) ��� ������ Name.
   //ob �������� �������� ������ ��� ������� ������ ����������� [������� 2].
   //������ ��������� ������� ����������� ��� ������ ItemName
   //Accessor - ����� ������� ��������� �������� ������ � ��������� [������� 3]
   template< class T, class AccessorT >
   void STLContainerGroup( const TChar *Name, const TChar *ItemName,  T &ob, AccessorT Accessor )
   {
      typename AccessorT::ValueType TmpContainer;
      typename AccessorT::ValueType::value_type TmpValue;

      TFindCursor FindCursor;

      TReader::BeginLevel( Name );

      TReader::FindInit( ItemName, FindCursor );

      while( TReader::FindNext(FindCursor) )
      {
         Serialize( *this, TmpValue );
         TmpContainer.push_back(TmpValue);
      }

      TReader::EndLevel( Name );

      Accessor.Set(ob, TmpContainer);
   }
};



///////////////////////////////////////////////////////////////////////////////
// ���������� ���������� AccessorT [������� 3] ��� ������ ���������� �� ������� Set/Get
// ��� ������������� ���������� ������� ������� 
//    SetGetBind</*��� ��������� ������*/, /*��� ����������� ������������� �����*/>(/*��������� �� ������� ���� Set*/, /*��������� �� ������� ���� Get*/)
//    ��� ��������� �� ������� ����� ����� ���� 0;
///////////////////////////////////////////////////////////////////////////////
template< class Object, class T >
struct CSetGetBindImpl
{
   typedef T ValueType;
   typedef void (Object::*SetFunc)(const T &);
   typedef const T &(Object::*GetFunc)() const;
   
   CSetGetBindImpl( SetFunc SF, GetFunc GF ): m_SetFunc(SF), m_GetFunc(GF) {}
   const T &Get( Object &Obj ) const { return (Obj.*m_GetFunc)(); }
   void Set( Object &Obj, const T &Val ) const { (Obj.*m_SetFunc)(Val); }

private:
   SetFunc m_SetFunc;
   GetFunc m_GetFunc;
};

template< class Object, class T >
struct CSetGetBindImplNoRef
{
   typedef T ValueType;
   typedef void (Object::*SetFunc)( T );
   typedef T (Object::*GetFunc)() const;

   CSetGetBindImplNoRef( SetFunc SF, GetFunc GF ): m_SetFunc(SF), m_GetFunc(GF) {}
   const T Get( Object &Obj ) const { return (Obj.*m_GetFunc)(); }
   void Set( Object &Obj, const T Val ) const { (Obj.*m_SetFunc)(Val); }

private:
   SetFunc m_SetFunc;
   GetFunc m_GetFunc;
};


template< class Object, class T >
CSetGetBindImpl<Object, T> SetGetBind(void (Object::*SetFunc)(const T &), const T &(Object::*GetFunc)() const )
{
   return CSetGetBindImpl<Object, T>( SetFunc, GetFunc);
}

template< class Object, class T >
CSetGetBindImplNoRef<Object, T> SetGetBind(void (Object::*SetFunc)(T), T (Object::*GetFunc)() const )
{
   return CSetGetBindImplNoRef<Object, T>(SetFunc, GetFunc);
}


/**
   �������������� ������� ����������� ������
*/

//�������� �� ������ Object � ������� ��������� ����� Serialize XML ������ OutXML � 
//��������� ��������� ���� RootName
template< class Object, class CharT >
void GetSerializeXMLString( Object &Object, const CharT *RootName, std::basic_string<CharT> &OutXML )
{
   std::basic_stringstream<CharT> Stream;
   CWriteArchive<CharT> Archive(Stream);
   Archive.Save( RootName, Object );
   OutXML = Stream.str();
}

//��������� �� XML ������, � �������� ����� RootName, ������ Object � ������� ��������� ����� Serialize
template< class Object, class CharT >
void SetSerializeXMLString( Object &Object, const CharT *RootName, const std::basic_string<CharT> &InXML )
{
   std::basic_stringstream<CharT> Stream(InXML);
   CReadArchive<CharT> Archive(Stream);
   Archive.Load( RootName, Object );
}
}} //namespace SS::Lib 

#endif