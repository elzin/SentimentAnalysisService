#pragma once
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{

			class CSMExSimpleQueryParser : public CSMSentenceExpert
			{
			public:
				CSMExSimpleQueryParser(void);
				~CSMExSimpleQueryParser(void);
				bool AnalizeSentence();
				bool Init(IText * pIText);
			protected:
				/// �����, ��� ���� � ������  () 
				set<wstring> m_Words;
				/// ���������� ��� ����� �������
				/** 
				\param sWord - ����� 
				\return 		bool - ������, ���� �������
				*/
				bool IsWord(const TCHAR * sWord);
			};

		}
	}
}

