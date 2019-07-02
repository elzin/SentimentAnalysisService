#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Russian
			{
			/// ��������� ��������� ����������� �����
			class CSMPassiveR :
				public CSMSentenceExpert
			{
			public:
				CSMPassiveR(void);
				~CSMPassiveR(void);
				bool AnalizeSentence();
			private:
				//SS::Core::Features::CMorphoFeature m_MorphoFeature;
				/// ��� ����� ��� ���������
				enum EWordType
				{
					ewtSkip, /// ����������
					ewtStop,/// ������������, ���������� ������
					ewtProcess /// ����������
				};
				bool InitExpert();
				/// ���������� ��� ����� �� ����� ���� ���������
				/** 
				\param pWord - �����
				\return 		bool - ������, ���� ����� ������� ���������
				*/
				bool IsBreakWord(IUnit * pWord);
				/// ����� ����� �� ������� �������
				/** 
				\return	bool - ������, ���� ���� ��������� �������/������
				*/
				bool FindLeft();
				/// ����� ������ �� ������� �������
				/** 
				\return	bool - ������, ���� ���� ��������� �������/������
				*/
				bool FindRight();
				
				/// ������, ���� ������� � ��������������� ����������� �� ������
				/** 
					\param pPretext - �������
					\param pNoun - ���������������
					\return 				bool
				*/
				bool IsCoordinatedPrepWithNounByCase(IUnit * pPretext, IUnit * pNoun);
				/// ���������� ��� �����
				/** 
					\param pWord - ����� 
					\return 				EWordType - ��� 
				*/
				EWordType GetWordType(IUnit * pWord);
				/// ������������� ������ ����� 
				/** 
					\param pUnit ����� 
				*/
				void SetIndex(IUnit * pUnit);

			};
			}
		}
	}
}