#pragma once

#include "Board.h"
#include <atlbase.h>
#include <atldbcli.h>

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			using namespace BoardElements;
			
			/// ������� ����� ��� ���� ���������
			class CBaseExpert
			{
			public:
				///�����������
				CBaseExpert();
				///����������
				virtual ~CBaseExpert(){};
				/// ������ �� ����� 
				virtual bool PassBoard(CBoard & board, PBLOCK pBlock) = 0;
				/// ���������� ��������� �������� ��������. 
				virtual std::wstring GetName() const = 0;
				///������������� ���� ������������ ��������
				void ClearApplicableState();
				///���������� �������������� � ���������� ��������
				void SetAsAmbiguity();
			
			protected:
				///����������, �������� �� �������
				bool m_isApplicable;
				///����������, �������� �� ������� �� ������������
				bool m_isCheckedApplication;
				///�������������� � ���������� ��������
				bool m_bIsAmbiguity;
			};
		}
	}
}