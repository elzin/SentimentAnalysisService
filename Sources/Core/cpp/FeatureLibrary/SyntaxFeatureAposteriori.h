#pragma once

#include ".\basefeaturecollection.h"
#include "define.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			/// ������ ������������� �������������� ����������
			class CSyntaxFeatureAposteriori :
				public SS::Core::Features::Base::CBaseFeatureCollection
			{
			public:
				CSyntaxFeatureAposteriori(void);
				~CSyntaxFeatureAposteriori(void);

				CSyntaxFeatureAposteriori& operator = (const CSyntaxFeatureAposteriori& value)
				{
					Assign(&value);
					return *this;
				}
				CSyntaxFeatureAposteriori(const CSyntaxFeatureAposteriori& value){
					Init();
					*this = value;
				};

				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "SyntaxFeatureAposteriori";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "������ ������������� �������������� ����������";};

				/// �������������� ���������
				Types::SyntaxCategories			m_SyntaxCategories;		
				/// �������� ����������� �������������� ���������
				Types::SyntaxCategoryPower		m_SyntaxCategoryPower;
				/// ����� ��������
					/*	�� ����������� � �� ������������� � ������ ������ ��������������� �����������	*/
				Types::IdParent					m_IdParent;
				///	���� ����� ������ �����������
				Types::DependencyPower			m_DependencyPower;								
			private:
				void Init();
			};
		}
	}
}