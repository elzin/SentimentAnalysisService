#pragma once

#include "IBlackBoxQuery.h"

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			/// �������� ����� �������, ��������� �� ���������������� ���������� ��� �������� ����������
			class ILinguisticQueryEx : public ILinguisticQuery
			{
			public:
				ILinguisticQueryEx(){}
				virtual ~ILinguisticQueryEx(){}
			public:
				///// ������ ������� ������������ ��� ������ ��� ��������� ������� � ���������� ���������� �� ������������ ������� 
				///**
				//	������������ ��� ������ ������� � ��������� �����������, ����������� �� ���� ����������� ��������� ������� SS
				//*/
				//virtual void GenerateQuery(
				//	/// ��������� ������
				//	SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
				//	/// ��������� ������� �������
				//	, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
				//	/// ���������, ������� ���������� ���������
				//	, SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult
				//	/// ���������, ������� ���������� ���������
				//	, SS::Interface::Core::CommonContainers::IQueryResult* pQueryResult
				//	/// �������� ���������� ���������� ������� �������� �������
				//	, bool bIsRememberQuery					
				//	) = 0;

				/// ���������� ��������� ��������� �������
				virtual SS::Interface::Core::BlackBox::Query::IQuery* GetLastQuery() = 0;
			};
		};
	}
}