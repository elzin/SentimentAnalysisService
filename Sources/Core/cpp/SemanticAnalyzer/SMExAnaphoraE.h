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
				namespace English
				{
					/// ������� � ������
					class CSMExAnaphoraE :
						public CSMExAnaphora
					{
					public:
						CSMExAnaphoraE(void);
						~CSMExAnaphoraE(void);
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