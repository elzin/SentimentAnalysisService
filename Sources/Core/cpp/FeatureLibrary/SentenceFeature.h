#pragma once

#include ".\basefeaturecollection.h"
#include "define.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			/// �������������� �����������
			class CSentenceFeature :
				public SS::Core::Features::CBaseFeatureCollection
			{
			public:
				CSentenceFeature(void);
				~CSentenceFeature(void);
				CSentenceFeature& operator = (const CSentenceFeature& value)
				{
					Assign(&value);
					return *this;
				}
				CSentenceFeature(const CSentenceFeature& value){
					Init();
					*this = value;
				};

				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "SentenceFeature";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "�������������� �����������";};

				/// ��� �����������
				Types::SentenceType		m_SentenceType;
			private:
				void Init();
			};
		}
	}
}