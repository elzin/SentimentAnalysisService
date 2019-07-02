//ExpertDetectQuestionQuery.h

#pragma once

#include "BaseExpert.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{

			///������� ����������� ��� ����������� ��������������� �����, ������ � "�������" 
			class CExpertDetectQuestionQuery : public CBaseExpert
			{
			private:
				//��������� �������������� ����
				std::vector<std::wstring> m_vQuestions;
			public:
				//�����������
				CExpertDetectQuestionQuery();
				//����������
				virtual ~CExpertDetectQuestionQuery();
				//������������� ������
				///���������� true, ���� � ����������� ������ ��� ������ ������ �������� ������
				bool PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock);
				///�������� ��� �����������
				std::wstring GetName() const;
			};

		}
	}
}