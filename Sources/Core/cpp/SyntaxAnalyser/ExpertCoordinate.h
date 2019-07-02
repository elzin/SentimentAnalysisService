//ExpertCoordinate.h
#pragma once
#include "BaseExpert.h"

namespace SS
{
namespace Syntax
{
namespace ExpertClause
{
	using namespace ExpertModel;
	///������� ��� ������� ���������������� ����������� 
	class CExpertCoordinate : public CBaseExpert
	{
	public:
		///�����������
		CExpertCoordinate(){};
		///����������
		~CExpertCoordinate(){};
		///������ �� ����� 
		bool PassBoard(CBoard & rBoard, PBLOCK pBlock);
		///���������� ��������� �������� ��������
		std::wstring GetName() const;
	};
}
}
}