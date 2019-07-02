#pragma once

#include "FeatureGroup.h"
namespace FeatureFactoryGenerator
{
	public __gc class CFeatureStorage
	{
	public:
		CFeatureStorage(void);
		~CFeatureStorage(void);
		///��������� �������������� �� ������ � ���������� sPath
		void LoadGroups(System::String* sPath);
		///��������� �������������� � ����� � ���������� sPath
		void SaveGroups(System::String* sPath);

		///������� ������ ������ ������������� � �������� ������
		CFeatureGroup* AddGroup(System::String* sGroupName);

		///������ ��������� �� ������ 
		CFeatureGroup* GetGroup(unsigned int nGroup);

		///������ ��������� �� ������ ������ 
		CFeatureGroup* FirstGroup();
		///������ ��������� �� ��������� ������ 
		CFeatureGroup* NextGroup();
	protected:
		///����� ����� �������������
		//std::vector<CFeatureGroup*> m_v_FeatureGroups;
		System::Collections::ArrayList* m_FeatureGroupArray;
		//CFeatureGroup* m_FeatureGroupArray[];

		///�������� �� ������� ������
		System::Collections::IEnumerator* m_ArrayEnum;

		///������ ����, �� �������� ��������� ���-�� (��� ������������ ����������)
		System::String* m_sPath;
	};
}