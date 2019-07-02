#pragma once
#ifdef _SS_UNITTESTS

namespace SS{ 
namespace UnitTests{ 
namespace Dictionary{

class CTestPerpformance
{
   ILoadManager *m_pLoadManager;
   DBMS::IDataBase *m_pDataBase;
   

   typedef std::list<std::wstring> TStringsForTest;
private:
   void InitNDXDataTable( CTablePtr &pTable );
   
   //��������� � Buf ��� ������ �� ����� FileName � ����. �������.
   //<����� �������� � Buf><���������� �������><��� �� ���>endl   
   void LoadToMemoryFileStrings( const std::string &FileName, TStringsForTest &Buf );
   
   //��������� � Buf ��� ����� �� ����� ���������� ����� FileName
   void LoadToMemoryFileText( const std::string &FileName, TStringsForTest &Buf );

   void TestIDictionaryTreeImpl( IDictionary *pDictionary, const TStringsForTest &StringsForTest );

public:
   explicit CTestPerpformance(ILoadManager *pLoadManager);
   ~CTestPerpformance();

   //��������� �� �������� ��� ����� cpp, ������� ����������� � ����������  ��� ����� � ��� � 
   //������� DBMS
   void FillNdxDBMS( const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );

   //����� �������� � ������� DBMS
   void FindNdxInDBMS( const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );

   //������ ������ �� ������  � ������
   void FindDummy( const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );
   
   //����� � ������� DBMS c ����������� ���� CWewWordsCache
   void FindNdxInCWewWordsCache( const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );

   void TestIDictionaryTree(const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );
   void TestIDictionaryTreeFromText(const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );

   void TestPerfForDir( const std::wstring &Dir, const std::wstring *ExtFirst, const std::wstring *ExtLast );
};

} //namespace Dictionary
} //namespace UnitTests
} //namespace SS

#endif //_SS_UNITTESTS
