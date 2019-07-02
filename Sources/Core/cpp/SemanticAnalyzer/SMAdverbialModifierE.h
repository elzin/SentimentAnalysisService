#pragma once
#include "smadverbialmodifier.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace English
			{
				/// �������������� ����� � ������� � ����������
				class CSMAdverbialModifierE :
					public CSMAdverbialModifier
				{
				public:
					CSMAdverbialModifierE(void);
					~CSMAdverbialModifierE(void);
					bool AnalizeSentence();
				private:
					/// ��������� ��������� ����� � ��������
					void AddPlaceUnit(TBoxUnits & l_Units);
				};
			}
		}
	}
}
