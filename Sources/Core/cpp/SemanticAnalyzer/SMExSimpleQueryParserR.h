#pragma once
#include ".\SMExSimpleQueryParser.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Russian
			{
				///���������� ����������� ����������� ��� ����� ����� ������ � ���������� ��� Ajunct 
				class CSMExSimpleQueryParserR :
					public CSMExSimpleQueryParser
				{
				public:
					CSMExSimpleQueryParserR(void);
					~CSMExSimpleQueryParserR(void);

					bool Init(IText * pIText);

				};


			}

		}
	}
}