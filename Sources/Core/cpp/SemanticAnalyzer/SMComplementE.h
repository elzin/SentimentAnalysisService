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

				/// ��������� ���������
				class CSMComplementE :
					public CSMSentenceExpert
				{
				public:
					CSMComplementE(void);
					~CSMComplementE(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);

				private:
					SS::Dictionary::Types::TDictionaryIndex m_semName;
					/// ��������� ����������� ���� X+ "semabtic=represent,become"/is + Y
					/** 
					\param oSemanticFeature - ��������� ��������� �
					\return bool - ������ - ���� ����������� ����� �����
					*/
					bool ProcessToBeCompliment(SS::Core::Features::CSemanticFeature & oSemanticFeatureFirst,TBoxUnits & l_UnitsFirst);
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
					void DetectVerbDefinitionConstructions();
					/// ��������� ����� ������������� ��������� � ��������� �������� ������
					/** 
					\param l_Units - �����
					\param oSyntaxCategories ���������
					*/
					void AddSyntaxCategoryIndices(TBoxUnits & l_Units, const Types::SyntaxCategories & oSyntaxCategories);
					/// ���������� ������ � ����� � �������
					void SkipBrackets();


				};


			}
		}
	}
}