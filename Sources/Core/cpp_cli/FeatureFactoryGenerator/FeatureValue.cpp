#include "StdAfx.h"
#include ".\featurevalue.h"
#using <mscorlib.dll>

namespace FeatureFactoryGenerator
{
	CFeatureValue::CFeatureValue(System::String* sValueName, System::String* sValueDescription, bool bEnabled)
	{
		m_sValueName = sValueName;
		m_sValueDescription = sValueDescription;
		m_bEnabled = bEnabled;
	}

	CFeatureValue::~CFeatureValue(void)
	{
	}
	///3������� ���� �������� B �����y
	System::String* CFeatureValue::Write(System::String* sText)
	{
		System::String* sTemp = "";
		//������� ���������� ���������
		if(!IsEnabled()){
			sTemp = sTemp->Concat(sTemp, new System::String("//"));
		}
		sTemp = sTemp->Concat(sTemp, GetValueName());
		sTemp = sTemp->Concat(sTemp, new System::String(" "));
		sTemp = sTemp->Concat(sTemp, new System::String("\""));
		sTemp = sTemp->Concat(sTemp, GetValueDescription());
		sTemp = sTemp->Concat(sTemp, new System::String("\""));
		sTemp = sTemp->Concat(sTemp, new System::String("\n"));

		sTemp = sText->Concat(sText, sTemp);

		return sTemp;
	}
}