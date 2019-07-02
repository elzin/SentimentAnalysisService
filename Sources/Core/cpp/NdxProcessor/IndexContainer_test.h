#pragma once

#ifdef _SS_UNITTESTS

#include <cppunit/extensions/HelperMacros.h>
#include ".\UnitTestsUsings.h"
#include ".\cnt_factory.h"
#include ".\storage_manager.h"

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

//--------------------------------------------------------------------//

class CIndexContainer_test : public CPPUNIT_NS::TestFixture,
		public SS::UnitTests::NdxSE::NdxProcessor::CUnitTestsUsings

{
	CPPUNIT_TEST_SUITE(CIndexContainer_test);
	//CPPUNIT_TEST(TestAll);
	CPPUNIT_TEST_SUITE_END();

public:
	void TestAll(void);

protected:
	///������� ������ ������� ����
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* CreateIndex(SS::Interface::Core::NdxSE::ENdxStorageConfig IndexConfig);
	///������� ������
	void DeleteIndex(void);

	void Test(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory);

	//������� �������� ��������
	SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* m_pStorageManager;
	//�������� ��������� ����
	SS::Interface::Core::NdxSE::INdxBaseManager* m_pNdxBaseManager;

};

//--------------------------------------------------------------------//

}
}
}
}
}

#endif //_SS_UNITTESTS
