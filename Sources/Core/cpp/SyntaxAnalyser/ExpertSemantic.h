//ExpertSemantic.h
#pragma once
#include "Board.h"

namespace SS
{
namespace Syntax
{
namespace ExpertSemantic
{

	///������� ��� ������� ���������
	class CExpertSemantic
	{
	private:
		///�������� �������� Undefine �� �������� ������������� ����
		void DeleteUndefine(SS::Core::Features::CSemanticFeature* pSemFeature);
		///������� ��� ��������� ����������� ��� ����� �� ��������� TMetro
		void DetectMetro(SS::Syntax::BoardElements::CBoard & oBoard);

	public:
		///�����������
		CExpertSemantic(){};
		///����������
		~CExpertSemantic(){};
		///������ �� �����
		bool PassBoard(SS::Syntax::BoardElements::CBoard & oBoard);
	};

}
}
}


