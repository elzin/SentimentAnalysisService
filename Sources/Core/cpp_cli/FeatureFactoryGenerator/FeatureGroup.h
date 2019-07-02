#pragma once

#include "Feature.h"
namespace FeatureFactoryGenerator
{
	public __gc class CFeatureGroup
	{
	public:
		CFeatureGroup(System::String* sGroupName);
		~CFeatureGroup(void);

		///������ ��� ������
		System::String* GetGroupName(){return m_sGroupName;};

		///��������� �������������� �� ����a � ���������� sPath
		void LoadFeatures(System::String* sPath);
		///��������� �������������� � ���� � ���������� sPath
		void SaveFeatures(System::String* sPath);

		///��������� ����� ��������������
		CFeature* AddFeature(
			System::String* sFeatureName
			, System::String* sFeatureDescription
			, System::String* sFeatureType
			, System::String* sFeatureTypeDescription);

		///������ ��������������  ��� ������������ �������
		void DeleteFeature(unsigned int nFeature);
		///������ ��������� �� �������������� 
		CFeature* GetFeature(unsigned int nFeature);
		///������ ��������� �� ������ �������������� 
		CFeature* First();
		///������ ��������� �� ��������� �������������� 
		CFeature* Next();
	protected:
		///����� �������������, �������� � ������
		System::Collections::ArrayList* m_FeatureArray;
		///�������� �� ������� ��������������
		System::Collections::IEnumerator* m_ArrayEnum;

		///��� ������
		System::String* m_sGroupName;
	};
}