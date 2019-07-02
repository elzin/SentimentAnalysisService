#pragma once
#include "./smexanaphora.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace IndexationExperts
			{
				namespace Russian
				{
					/// ������� � ������
					class CSMExAnaphoraR :
						public CSMExAnaphora
					{
					public:
						CSMExAnaphoraR(void);
						~CSMExAnaphoraR(void);
						bool Init(IText * pIText);
					protected:
						/// ������, ���� ����� - ��� ��� �������, ��� �����������
						bool IsNameAgent();

					};


				}

			}
		}
	}
}