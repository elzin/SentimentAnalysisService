//ExpertFragmentationQuery.h
#pragma once

#include "BaseExpertFragmentation.h"
#include <vector>

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			
			class CExpertFragmentationQuery : public CBaseExpertFragmentation
			{
			private:
				///����� ����, ������ ����������� �� ����� ('and' 'or' ',') 
				std::vector<std::wstring> m_ConjQuery;
				///��������� �������
				std::wstring m_Divisor;
			
			private:
				///���������, �������� �� ������ ������� ������.
				virtual bool IsConj(BoardElements::BoardElementsIterator elem) const;
				///������������� ��������� ������.
				bool IsConjQuery(BoardElements::BoardElementsIterator elem) const;
			
			public:
				//����������� � ����������
				CExpertFragmentationQuery();
				virtual ~CExpertFragmentationQuery(){};
				//������ ������
				///��������� �������� ��������
				std::wstring GetName() const
				{
					return L"Fragmentation Expert Query";
				}
			};

		}
	}
}