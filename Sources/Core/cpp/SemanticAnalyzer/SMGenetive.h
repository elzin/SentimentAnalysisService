#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace English
			{

			/// ����������� ��������
			class CSMGenetive :
				public CSMSentenceExpert
			{
			public:
				CSMGenetive(void);
				~CSMGenetive(void);
				bool AnalizeSentence();
			private:			
				/// ������������� ����������� ����� ����������������
				/** 
				\param pUnit - ���������������
				\return bool
				*/
				bool SetNounGenetiveCase(IUnit * pUnit);
				/// ����������� ����� ��������
				bool CheckGenetiveRecursive(IUnit * pUnit);
				/// ��������� ������������ ������
				bool GenetiveProcess(IUnit * pUnit);
			};

			}
		}
	}
}