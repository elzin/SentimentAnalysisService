#pragma once

#include ".\basefeaturecollection.h"
#include "define.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			/// ������ ��������� �������������� ����������
			class CSyntaxFeatureApriori :
				public SS::Core::Features::Base::CBaseFeatureCollection
			{
			public:
				CSyntaxFeatureApriori(void);
				~CSyntaxFeatureApriori(void);

				CSyntaxFeatureApriori& operator = (const CSyntaxFeatureApriori& value)
				{
					Assign(&value);
					return *this;
				}
				CSyntaxFeatureApriori(const CSyntaxFeatureApriori& value){
					Init();
					*this = value;
				};

 				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "SyntaxFeatureApriori";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "������ ��������� �������������� ����������";};

				/// ��� ����������� �������
				Types::VerbConstruction			m_VerbConstruction;
				/// ��� ����������� ����������������
				Types::NounConstruction			m_NounConstruction;
				/// ��� ����������� ���������������
				Types::AdjectiveConstruction	m_AdjectiveConstruction;
				/// ��� ���������� �������
				Types::TypeOfEndingObject		m_TypeOfEndingObject;		
				/// ��� ����������
				Types::CombiType				m_CombiType;	
				/// �������������� ���������
				Types::SyntaxCategories			m_SyntaxCategories;		

				///�������� ����������� � ������ ������� �������������
				bool IsIntersectsWith(const CSyntaxFeatureApriori& value) const;
			private:
				void Init();
			};
		}
	}
}