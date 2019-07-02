#pragma once
#include "SMSentenceExpert.h"
namespace SS
{
	namespace Semantic
	{
		namespace PostAnalysisExperts
		{
			namespace PostSyntaxAnalysis
			{
				/// �������� ��������� �������������
				class CSMSpecifyCategory :
					public CSMSentenceExpert
				{
				public:
					CSMSpecifyCategory(void);
					~CSMSpecifyCategory(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
				private:
					///������������� ��� �����
					SS::Dictionary::Types::TDictionaryIndex m_semNumber;

					SS::Dictionary::Types::TDictionaryIndex m_questSemFirstName;
					SS::Dictionary::Types::TDictionaryIndex m_questSemLastName;

					/// ������� ���������_����
					std::map<UINT,IUnit*> m_CategoryUnitTable;

					/// ������������� �������������� 
					void SpecifyAjunct(IUnit * pHead);

					/// ���������� ������������ �������
					/** 
					\param pUnit - �������
					\return 	bool - ������ - ���� ����������
					*/
					bool IsLegalLexem(IUnit* pUnit);

					/// ��������� ���� �� ��������� � ������ ����������  �� ����
					bool IsCategory(SS::Core::Features::CSyntaxFeatureAposteriori * pSyntaxFeatureAposteriori);

					/// ��������� �� ������ ����� � �������
					bool IsNotEmptyWordsAndSymbols(IUnit* pUnit);
					
					/// ���������� ����� ��������� Ajunct
					bool MoveToAjunctChilds(IUnit * pGroup);

					/// ����������� ��������� PrepositionObject
					/** 
					\param pUnit - ����
					\param bPassive - ������, ���� ��� ������� �������
					*/
					bool MoveToPrepositionObject(IUnit * pUnit,bool bPassive);

					/// ��������� ���� �� ��������� ObjectPreposition
					void CheckObjectPreposition(IUnit * pHead, bool bPassive);

					/// ����������� ��������� �������
					void ProcessUnit(IUnit * pUnit, IUnit * pHead);

					/// ���������� ������, ���� ������ �����(����) �������
					//bool IsPretext(IUnit * pUnit);

					bool IsPassive(IUnit * pHead);

					/// ���������� Object �������������� ������ (��� �������� who, what)'
					void SetSyntaxQuestion();

					void PassiveProcess();

					void SpecifyCategories();
		
					void SetSyntaxSubjectObject();

					bool CheckSubjectInChilds(IUnit * pHead);
					bool CheckNameAndSetNameSemantic(IUnit * pUnit, IUnit * pQuestion);
					void AddPersonSemantic(IUnit * pUnit);

				};
			}
		}
	}
}