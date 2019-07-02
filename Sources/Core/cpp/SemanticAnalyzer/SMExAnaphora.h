#pragma once
//#include "smexpert.h"
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace IndexationExperts
			{
			
				/// ����� ������� � ������, ������� �����
				class CSMExAnaphora :
					public CSMSentenceExpert//CSMExpert
				{
				public:
					CSMExAnaphora(void);
					~CSMExAnaphora(void);
					
					//bool Analize();
					bool AnalizeSentence();
					
					bool Init(IText * pIText);
				protected:
					/// ������� ����� - �� ��� ���� � �����  ( ������ ����������� ) 
					set<wstring> m_AimWords;
					///����� � ������ ��������������� ���������� ����������� �� ���������������� ��� ���������� ����� ������������
					/** 
					\param uiWordCount - ���-�� ���������� ����
					\param oInfo - ���������� �� ������� ��������
					*/
					void ReplaceProNoun(UINT & uiWordCount, IUnit * poInfo, const TBoxUnits l_units);
					/// ���������� ��� ����� �������� ��� ������
					/** 
					\param sWord - ����� 
					\return 		bool - ������, ���� ��������
					*/
					bool IsAimWord(const TCHAR * sWord);

					/// ���������� ��� ������� ����� - ��� ��� �����
					virtual bool IsNameAgent()=0;

					/// �������� ��� ������� �������� �����
					void CopyUnit(IUnit * pUnit, bool bMorphoOnly);

					/// �������� �����, ���� ����� ��� �������
					void CollectListOfNameAgents(TBoxUnits & l_Units);

					/// ����������, ��� ���� ����� ��������� �����
					bool IsSemanticName(IUnit * pUnit);
					
					/// ���������� �� ������������ ���� �������� ������ � �����������
					bool IsValidGender(IUnit * pAgent);
				};
			}
		}
	}
}

