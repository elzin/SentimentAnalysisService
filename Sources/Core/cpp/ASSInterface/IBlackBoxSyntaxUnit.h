#pragma once

#include "..\FeatureLibrary\define.h"
#include "IBlackBoxDictionaryIndex.h"

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace BlackBox
			{
				///������������ �������������� ������������� (���������� �������)
				class ISyntaxFeature
				{
				public:
					///������������� �������������� ��������������
					virtual void SetSyntaxCategory(unsigned int uiSyntaxCategory) = 0;
					///������������� �������������� ��������������
					virtual void SetSyntaxFeatureApriori(SS::Core::Features::CSyntaxFeatureApriori * pSyntaxFeatureApriori) = 0;
					///������������� �������������� ������������� �������������� 
					virtual void SetSyntaxFeatureAposteriori(SS::Core::Features::CSyntaxFeatureAposteriori * pSyntaxFeatureAposteriori) = 0;
					///���������� �������������� ��������������
					virtual unsigned int GetSyntaxCategory(void) = 0;
					///���������� �������������� ������������� �������������� 
					virtual SS::Core::Features::CSyntaxFeatureAposteriori * GetSyntaxFeatureAposteriori()=0;
					///���������� ��������������  �������������� 
					virtual SS::Core::Features::CSyntaxFeatureApriori * GetSyntaxFeatureApriori()=0;
					///������������� ��� ���� ������
					virtual void SetIsQuestion(void) = 0;
					///������������� ��� ���� �� ������
					virtual void SetIsNotQuestion(void) = 0;
					///��������� �������� �� ���� ��������
					virtual unsigned int IsQuestion(void) = 0;
				};


				///������������ �����, ����������� ��������� ������ ���������� ��������������� ������� �����������
				/**� ������ ������ �� ������������*/
				class ISyntaxUnit
				{
				public:
					virtual ~ISyntaxUnit(){};
					///��������� �������������� �������������
					virtual ISyntaxFeature* GetSyntaxFeature() = 0;
					///�������� �� ��������� ������� � ������� �������� �����
					virtual bool IsUnitIndex(IDictionaryIndex* pDictionaryIndex);
				};

			}
		}
	}
}
