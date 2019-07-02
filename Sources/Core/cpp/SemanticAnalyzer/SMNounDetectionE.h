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
				/// ��������� ��������������� � ������ - � ���������, � ��� ���� 
				class CSMNounDetectionE :
					public CSMSentenceExpert
				{
				public:
					CSMNounDetectionE(void);
					~CSMNounDetectionE(void);
					bool AnalizeSentence();
				private:
					/// ����� ������� ����� ������� ������ ��� ����������
					/** 
					\param uiDepth - ������� ������ - ���� �� �����
					\param pUnit - ���� ����� ������� ������ ������
					*/
					bool IsVerbBeforeE(UINT uiDepth);
					
					/// ���������� ������� ������ �������
					UINT CalculateDepth(IUnit * pPrep,const UINT uiLimit);
					bool IsOneOf(UINT uiDepth);
				};

			}
		}
	}
}