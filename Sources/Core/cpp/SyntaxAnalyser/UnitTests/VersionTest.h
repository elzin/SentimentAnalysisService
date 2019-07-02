//VersionTest.h
#pragma once

//���� ������������
#ifdef _SS_UNITTESTS

#include "../BlockVersion.h"

namespace SS
{
namespace UnitTests
{
	
	using namespace SS::Syntax::BoardElements;
	
	///����� ��� ������������ �������
	class CVersionTest
	{
	private:
		///�������� ���������� �������� ��������
		void ShowElementInfo(PVERELEMENT pVElem, std::wstring wsWord = L" ") const;
		///������������ ������
		void SetStandartWide(std::wstring & ws) const;
		///�������������� string � wstring
		std::wstring StrToWstr(const std::string & s) const;

	public:
		///���������������� ��������
		void AnalyseVersion(CBlockVersion* pBlockVersion) const;
		///���������������� �������� �� CBoard
		void AnalyseVersion(BoardElementsIterator itF, BoardElementsIterator itL) const;
	};

}
}

#endif //_SS_UNITTESTS