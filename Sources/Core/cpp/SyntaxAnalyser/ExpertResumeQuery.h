//ExpertResumeQuery.h
#pragma once

#include "BaseExpert.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			class CExpertResumeQuery : public CBaseExpert
			{
			private:
				std::vector<std::wstring> m_vConj;
			public:
				//�����������/����������
				CExpertResumeQuery();
				virtual ~CExpertResumeQuery();
				//������������� ������
				///���������� �������� ������ �������, ���� true �� 
				///��������� ������ ������ � ���������� �� ����� 
				bool PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pCurrBlock);
				///�������� ��� �����������
				std::wstring GetName() const;
			};

		}
	}
}