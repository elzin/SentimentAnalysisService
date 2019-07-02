#pragma once

#include "BaseExpertFragmentation.h"
#include "../ASSInterface/IAMConverter.h"
#include <vector>
#include <string>

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///��������������� ������� � ����� �������� ��������.
			///������� �������� � ����������� �����. 
			///����� ����������� �������� ������ ���� �������� �������, ������������� �����.
			class CExpertFragmentationIndexation : public CBaseExpertFragmentation
			{
			private:
				///����� ����, ������ ����������� �� �����. ��������� �����.
				std::vector<std::wstring> m_conjSingle;
				///����� ����, ������ ����������� �� �����. ��������� �����, ������� � ������ �����������.
				std::vector<std::wstring> m_conjSingleBegin;
				///����� ����, ������ ����������� �� �����. �������� �����.
				std::vector< std::vector< std::wstring > > m_conjMultiple;
				///����� ����, ������ ����������� �� �����. ��������� ����������� �� � ������ �����������.
				std::vector<std::wstring> m_pronounSingleNotBegin;
				///����� ����, ������ ����������� �� �����. ��������� ������� �� � ������ �����.
				std::vector<std::wstring> m_adverbSingleNotBegin;
				///��������� �������
				std::wstring m_Divisor;
			
			private:
				///���������, �������� �� ������ ������� ������.
				bool IsConj( BoardElements::BoardElementsIterator elem ) const;
				///���������� ������ ������ ����, ������ �� �����.
				void InitDelim();
				///������������� ��������� ������
				bool IsConjSingle(BoardElements::BoardElementsIterator elem) const;
				///������������� ��������� ������ �� � ������ �����������
				bool IsConjSingleBegin(BoardElements::BoardElementsIterator elem) const;
				///������������� ������� ������
				bool IsConjMultiple(BoardElements::BoardElementsIterator elem) const;
				///������������� ��������� ����������� �� � ������ �����������
				bool IsPronounSingleNotBegin(BoardElements::BoardElementsIterator elem) const;
				///������������� ��������� ������� �� � ������ �����������
				bool IsAdverbSingleNotBegin(BoardElements::BoardElementsIterator elem) const;
			
			public:
				///�����������
				CExpertFragmentationIndexation();
				///��������� �������� ��������
				std::wstring GetName() const
				{
					return L"Fragmentation Expert Indexation";
				}
			};
		}
	}
}