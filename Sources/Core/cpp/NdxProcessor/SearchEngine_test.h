#pragma once

#ifdef _SS_UNITTESTS

#include <cppunit/extensions/HelperMacros.h>
#include ".\CommonContainersUsing.h"
#include ".\search_engine.h"

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Indexing
{

//--------------------------------------------------------------------//

class CSearchEngine_test : public CPPUNIT_NS::TestFixture, 
	public SS::UnitTests::NdxSE::NdxProcessor::CCommonContainersUsing
{
	CPPUNIT_TEST_SUITE(CSearchEngine_test);
		//CPPUNIT_TEST(TestAll);
		//CPPUNIT_TEST(Test);
		//CPPUNIT_TEST(TestMultiQueries);
		//CPPUNIT_TEST(TestIndexes);
		//CPPUNIT_TEST(TestIndexesCoordinates);
		CPPUNIT_TEST(TestNdxQuery);
	CPPUNIT_TEST_SUITE_END();

public:
	void TestAll(void);
	void Test(void);
	void TestIndexes(void);
	void TestMultiQueries(void);
	void TestIndexesCoordinates(void);
	void TestNdxQuery(void);

protected:
	///��������� ����� ����������� ������� � ���������� ����
	void TestSearching(const wchar_t* wszIndexBasePath,	const wchar_t* wszIndexBaseName, vector<wstring>& Queries, vector<wstring>* pStringQueries = NULL);
	///��������� ���������� ������ �� ���������� ����
	void TestTextInfoExtracting(const wchar_t* wszIndexBasePath, const wchar_t* wszIndexBaseName, unsigned int uiTextIndex);

	///��������� ����������
	void TestIndexing(SS::Core::NdxSE::NdxProcessor::CNdxSearchEngine* pSearchEngine, unsigned int uiTextsCount);
	///��������� ����������
	void TestExtracting(SS::Core::NdxSE::NdxProcessor::CNdxSearchEngine* pSearchEngine);
	///��������� ����� �� �������
	void GetWordFromDictionary(vector<unsigned int>* pIndexCollection, wstring* pwsWords);
	void GetWordFromDictionary(wstring* pwsWords);
	void QueryToLogicView(wstring& wsBasePath, wstring& wsBaseName, vector<wstring>& Queries, vector<wstring>& LogicQueries);
	//	��������� ���� ��� ������
	bool	ReadTestingPaths();
	wstring					m_wsBasePath;//	���� � ��
	wstring					m_wsBaseName;//	�������� ����� � ��
	wstring					m_wsQueryFile;//	�������� ����� ��������
};

//--------------------------------------------------------------------//

}
}
}
}
}

#endif //_SS_UNITTESTS