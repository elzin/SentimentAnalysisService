#pragma once

#include ".\basefeaturecollection.h"
#include "define.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				/// �������������� �����������
				class CConstructionFeature : public SS::Core::Features::Base::CBaseFeatureCollection
				{
				public:
					CConstructionFeature(void);
					~CConstructionFeature(void);
					CConstructionFeature& operator = (const CConstructionFeature& value)
					{
						Assign(&value);
						return *this;
					}
					CConstructionFeature(const CConstructionFeature& value){
						Init();
						*this = value;
					};

					///������ ��������� ��� ��������������
					const char* GetFeatureName() const {return "SentenceFeature";};
					///������ ��������� �������� ��������������
					const char* GetFeatureDescription() const {return "�������������� �����������";};

					/// ��� �����������
					Types::SentenceType		m_SentenceType;
					///// ������� ������� �����
					//Types::ChildrenAnalysisDepth	m_ChildrenAnalysisDepth;		// �� ����, �����, ������ ��� �����, ����
					
				private:
					void Init();
				};
			}
		}
	}
}