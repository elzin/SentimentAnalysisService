#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{

			/// ��������� � ������ ��������� ����� ���� "�����, ������" ��� "������, ���������"
			class CSMPlaceSpecification :
				public CSMSentenceExpert
			{
			public:
				CSMPlaceSpecification(void);
				~CSMPlaceSpecification(void);
				bool AnalizeSentence();
			private:
				void PlaceProcess(TBoxUnits & l_Units);
			};

		}
	}
}