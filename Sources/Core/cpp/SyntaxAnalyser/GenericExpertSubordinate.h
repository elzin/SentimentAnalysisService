//GenericExpertSubordinate.h
//����������� - �������� �������

#pragma once

#include "BaseExpert.h"
#include <algorithm>


namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///��������������� ������� � ������ �������� ��������.
			/** ��� ����� ������������ ����������� � ������ 
			���������� � ��������
			*/
			class CGenericExpertSubordinate : public CBaseExpert
			{
			private:
				//����� � ����� ����������, ����������� ���������� ����� �����������
				std::list<std::wstring> m_Conjunctions;
			
			public:
				//�����������
				CGenericExpertSubordinate();
				//����������
				virtual ~CGenericExpertSubordinate(){};
				///������ �� �����
				bool PassBoard(BoardElements::CBoard & Board, BoardElements::PBLOCK pCurrBlock);
				///��������� �������� ��������
				std::wstring GetName() const
				{
					return L"Generic Expert Subordinate";
				}
			};


		}
	}
}