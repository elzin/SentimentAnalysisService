//ExpertFragmentationRussian.h
#pragma once

#include "BaseExpertFragmentation.h"
#include <vector>

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	///������������ ������� �� ����� � ������� �����
	class CExpertFragmentationRusInd : public CBaseExpertFragmentation
	{
	private:
		///��������� �������� �� �����(�������)
		std::wstring m_Divisor;
		///������� ������� ����������� �� �����
		std::vector<std::wstring> m_Symbols;
		///������� ������� ����������� �������
		std::vector<std::wstring> m_Adverbs;

	private:
		///��������� ������� �������� ������� �� �����
		bool IsConj(BoardElements::BoardElementsIterator elem) const;
		///�������� ������� �������
		bool IsSymbol(BoardElements::BoardElementsIterator elem) const;
		///�������� ������� ������ ��������
		bool IsMultiSimbol(BoardElements::BoardElementsIterator elem) const;
		///�������� ������� �������
		bool IsAdverb(BoardElements::BoardElementsIterator elem) const;

	public:
		///�����������
		CExpertFragmentationRusInd();
		///����������
		virtual ~CExpertFragmentationRusInd(){};
		///���������� ��������� �������� �������� 
		std::wstring GetName() const;
	};

}
}
}