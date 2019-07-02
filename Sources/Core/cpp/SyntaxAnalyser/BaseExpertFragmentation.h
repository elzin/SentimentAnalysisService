//BaseExpertFragmentation.h
#pragma once

#include "BaseExpert.h"
#include "BoardElement.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{

			class CBaseExpertFragmentation : public CBaseExpert
			{
			private:
				///����� �������-�������� �����������
				std::vector<std::wstring> m_CommonDivisors;
				///����� ������(�������)
				std::wstring m_sLeftBracket;
				///������ ������(�������)
				std::wstring m_sRightBracket;
				///����� � �������
				std::wstring m_sDivisor;
				///�������� ������� ������
				bool m_bBracketAnalyse;
			
			private:
				///���������, �������� �� ������ ������� ������.
				virtual bool IsConj(BoardElements::BoardElementsIterator elem) const = 0;
			
			protected:
				///����� �����������
				BoardElements::BoardElementsIterator m_last;
				///��������� ��������� ������� ������
				void SetBracketAnalyse(bool b) { m_bBracketAnalyse = b; };
			
			public:
				//�����������
				CBaseExpertFragmentation();
				//����������
				virtual ~CBaseExpertFragmentation(){};
				///������ �� �����
				virtual bool PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock);
			};

		}
	}
}