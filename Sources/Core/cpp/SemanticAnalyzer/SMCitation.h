#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			/// ����������� �������� ������ � ������
			class CSMCitation :
				public CSMSentenceExpert
			{
			public:
				CSMCitation(void);
				~CSMCitation(void);
				bool AnalizeSentence();
				bool Init(IText * pIText);
			private:
				SS::Dictionary::Types::TDictionaryIndex m_uiSemanticCitation;
			};

		}
	}
}
