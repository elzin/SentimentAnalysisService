#pragma once

//#include <vector>
//#include <string>
#include ".\featurevalue.h"
namespace FeatureFactoryGenerator
{
	public __gc class CFeature
	{
	public:
		CFeature(CFeature* pFeature);

		CFeature(
			System::String* sFeatureName
			, System::String* sFeatureDescription
			, System::String* sFeatureType
			, System::String* sFeatureTypeDescription);

		~CFeature(void);

		System::String* GetFeatureName(){return m_sFeatureName;};
		System::String* GetFeatureDescription(){return m_sFeatureDescription;};
		System::String* GetFeatureType(){return m_sFeatureType;};
		System::String* GetFeatureTypeDescription(){return m_sFeatureTypeDescription;};

		void SetFeatureName(System::String* value){m_sFeatureName = value;};
		void SetFeatureDescription(System::String* value){m_sFeatureDescription = value;};
		void SetFeatureType(System::String* value){m_sFeatureType = value;};
		void SetFeatureTypeDescription(System::String* value){m_sFeatureTypeDescription = value;};

		///��������� ���� �������� �� ������
		void LoadValues(System::String* sFeature);
		///3������� ���� �������� B �����y
		System::String* Write(System::String* sText);

		///������� ������ ���-��������
		void ClearMapValues();
		///������� ����� �������� � ���
		CFeatureValue* AddMapValue(System::String* sValueName, System::String* sValueDescription, bool bEnabled);
		///������ ���-�������� ��� ������������ �������
		void DeleteFeatureValue(unsigned int nFeatureValue);

		unsigned int GetValueCount(){return m_ValueArray->Count;};

		///������ ��������� �� �������������� 
		CFeatureValue* GetFeatureValue(unsigned int nFeatureValue);
		///������ ��������� �� ������ �������������� 
		CFeatureValue* FirstValue();
		///������ ��������� �� ��������� �������������� 
		CFeatureValue* NextValue();
	protected:
		System::String* m_sFeatureName;
		System::String* m_sFeatureDescription;
		System::String* m_sFeatureType;
		System::String* m_sFeatureTypeDescription;

		///����� ��������, �������� � ���-��������������
		System::Collections::ArrayList* m_ValueArray;
		///�������� �� ������� ��������
		System::Collections::IEnumerator* m_ArrayEnum;
	};
}