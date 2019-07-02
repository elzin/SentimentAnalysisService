#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{

			/// ������� ����� ��� ����������� ������������� ����� , �������
			class CSMAdverbialModifier :
				public CSMSentenceExpert
			{
			public:
				CSMAdverbialModifier(void);
				~CSMAdverbialModifier(void);
			protected:

				/// ����������� ������ ������, ��������� �������������� ���������
				/** 
					\param l_Unit - ������
					\param pPrep - �������
					\param bTime - ����� - ��������� �������, ���� - �����
					\return 				bool - ������ - ���� ����������� ������
				*/
				bool ProcessPreposition(TBoxUnits &  l_Unit , IUnit * pPrep, bool bTime);
			};

		}
	}
}