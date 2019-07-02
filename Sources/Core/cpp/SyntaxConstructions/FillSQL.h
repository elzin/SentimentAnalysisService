//FillSQL.h
#pragma once
#include "./Connect.h"
#include "../ASSInterface/TBaseNames.h"

namespace SS
{
namespace UnitTests
{
namespace SyntaxConstructions
{
	///���������� SQL ��� �� DBMS
	class CFillSQL : public SS::CConnectSQL
	{
	public:
		///�����������
		CFillSQL(): CConnectSQL((wchar_t*)SS::MANAGER::Constants::c_szSyntaxConstructionsRus){};
		///����������
		~CFillSQL(){};
		///���������� SQL ���� �� DBMS
		void Fill();
	};

}
}
}