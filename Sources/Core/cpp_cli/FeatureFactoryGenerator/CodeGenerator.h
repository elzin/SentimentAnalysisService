#pragma once

#include "FeatureStorage.h"

namespace FeatureFactoryGenerator
{
	class CCodeGenerator
	{
	public:
		CCodeGenerator(void);
		~CCodeGenerator(void);

		///����������� ��� � ������� �� ����������� ��������� �������������
		System::String* Generate(CFeatureStorage* pFeatureStorage);
		///����������� ��� � ������� �� ���������� ������ �������������
		System::String* Generate(CFeatureGroup* pFeatureGroup);
		///����������� ��� � ������� �� ���������� ��������������
		System::String* Generate(CFeature* pFeature);

		///����������� ��� � ������� �� ���������� ��������������
		System::String* GenerateMap(CFeature* pFeature);
		///����������� ��� � ������� �� ���������� ��������������
		System::String* GenerateInteger(CFeature* pFeature);
		///����������� ��� � ������� �� ���������� ��������������
		System::String* GeneratePercent(CFeature* pFeature);
	};
};