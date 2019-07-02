//SyntaxConstructionsTest.h
#pragma once
#include "..\ASSInterface\ISyntaxConstructions.h"

namespace SS
{
namespace UnitTests
{
namespace SyntaxConstructions
{
	///����� ��� ������������ ������	
	class CSyntaxConstructionsTest
	{
	private:
		///�������� ��� ������ � �������������
		SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionsManager*	m_pSyntaxConstructionsManagerSQL;
		///�������� ��� ��������� �����������
		SS::Interface::Core::ResourceManagers::ILoadManager*						m_pLoadManager;
	
	private:
		///���������� �������� ��� ������ � �������������
		void SetConstructionsManager();

	public:
		///�����������
		CSyntaxConstructionsTest(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
		///����������
		~CSyntaxConstructionsTest(){};
		///���� ������ ����������� DBMS
		void TestToBinary();
	};

}
}
}