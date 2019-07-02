#pragma once
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Russian
			{
				/// ��������� � ������ ���������
				class CSMComplementR : public CSMSentenceExpert
				{
				public:
					CSMComplementR(void);
					~CSMComplementR(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
				private:
					/// ���������� ��������� 
					SS::Dictionary::Types::TDictionaryIndex m_semRepresent;
					/*SS::Dictionary::Types::TDictionaryIndex m_semName;*/
					/// ��������� ����������� ���� X+ "semabtic=represent,become"/is + Y
					/** 
					\param oSemanticFeature - ��������� ��������� �
					\return bool - ������ - ���� ����������� ����� �����
					*/
					bool ProcessToBeCompliment(SS::Core::Features::CSemanticFeature & oSemanticFeatureFirst,TBoxUnits & l_UnitsFirst,bool bVerbRB);
					bool InitExpert();
					/// ���������� ��������� ����� � ���� ���������� ����������� 
					/** 
					\param l_Units - ����� �� �
					\param oSemanticFeature - ��������� �
					*/
					bool PersonBefore(TBoxUnits & l_Units,SS::Core::Features::CSemanticFeature & oSemanticFeature);
					/// �������������� ����������� ���� X(person),Y,...
					/** 
					\param pPerson - ��������� �� �
					\return bool - ������ ���� ����������� ���� � ������
					*/
					bool AfterPersonInComma(IUnit * pPerson);
					/// �������������� ����������� ����   ...,Y, X(person)...
					/** 
					\param pPerson - ��������� �� �
					\return bool - ������ ���� ����������� ���� � ������
					*/
					bool BeforePersonInComma(IUnit * pPerson);
					/// �������������� ����������� ����   ...Y X(person)...
					/** 
					\param pPerson - ��������� �� �
					\return bool - ������ ���� ����������� ���� � ������
					*/
					bool BeforePersonSimple(IUnit * pPerson);
					/// ����� ����������� ���� X+ "semabtic=represent,become"/is + Y
					void DetectVerbDefinitionConstructions(bool bTire=false);
					/// �������� ��� ���� �������� �����, ���������� ���������� �������
					bool IsLatinWord(IUnit * pUnit=NULL);
					///�������� ������� �������� ����� ������ 
					/** 
					\param uiDepth - ������� ������ �������� - �� ����� ��� ����
					\return 		bool - ������ ���� ������� ����
					*/
					bool IsPrepositionBefore(UINT uiDepth);

					/// �������� ��������������� ���� �� ������, ����, �����
					/** 
					\param pFirst - ������ �����
					\param pSecond - ������ �����
					\param bCheckGender=false - ��������� ��������������� �� ����
					\param bSkipInstrumentalCaseSecond=false - ���������� ��������������� �� ������, ���� ������ ����� � ������������ ������
					\return 		bool - ������ - ���� ����� �����������
					*/
					bool IsCoordinatedCaseGenderNumber(IUnit * pFirst, IUnit * pSecond,bool bCheckGender=false,bool bSkipInstrumentalCaseSecond=false);
					/// ��������� ����� ������������� ��������� � ��������� �������� ������
					/** 
					\param l_Units - �����
					\param oSyntaxCategories ���������
					*/
					void AddSyntaxCategoryIndices(TBoxUnits & l_Units, const Types::SyntaxCategories & oSyntaxCategories);

				};
			}
		}
	}
}