#pragma once
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace IndexationExperts
			{

				/// ��������� ������������ ������ � �������, ������� �����
				class CSMCauseManner :
					public CSMSentenceExpert
				{
				public:
					CSMCauseManner(void);
					~CSMCauseManner(void);
				protected:
					/// ���������� ��� ����� ��������� �������
					void AddMannerCategory();
					/// ���������� ��� ����� ��������� �������
					void AddCauseCategory();
					/// ������, ���� � ������� ���� ������
					/**  
					\param pIndex - ������ 
					\param uiSourceIndex - ������
					*/
					bool IsIndexExist(IIndex * pIndex, UINT uiSourceIndex);

				};


			}
		}
	}
}