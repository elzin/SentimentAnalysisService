#include "StdAfx.h"
#include ".\feature.h"
#using <mscorlib.dll>

namespace FeatureFactoryGenerator
{
	CFeature::CFeature(
			System::String* sFeatureName
			, System::String* sFeatureDescription
			, System::String* sFeatureType
			, System::String* sFeatureTypeDescription)
	{
		m_sFeatureName = sFeatureName;
		m_sFeatureDescription = sFeatureDescription;
		m_sFeatureType = sFeatureType;
		m_sFeatureTypeDescription = sFeatureTypeDescription;

		m_ValueArray = new System::Collections::ArrayList();
	}

	CFeature::CFeature(CFeature* pFeature)
	{
		m_sFeatureName = pFeature->m_sFeatureName;
		m_sFeatureDescription = pFeature->m_sFeatureDescription;
		m_sFeatureType = pFeature->m_sFeatureType;
		m_sFeatureTypeDescription = pFeature->m_sFeatureTypeDescription;

		m_ValueArray = new System::Collections::ArrayList();
		ClearMapValues();
		CFeatureValue* pFV = pFeature->FirstValue();
		while(pFV){
			AddMapValue(pFV->GetValueName(), pFV->GetValueDescription(), pFV->IsEnabled());
			pFV = pFeature->NextValue();
		}
	}

	CFeature::~CFeature(void)
	{
	}
	///��������� ���� �������� �� ������
	void CFeature::LoadValues(System::String* sFeature)
	{
		System::String* sValue;
		int nBeg = 0;
		sFeature = sFeature->Concat(sFeature, "\n");

		int nEnd = sFeature->IndexOf("\n");

		m_ValueArray->Clear();

		//��������� ��������� ��������
		while(nEnd != -1){
			System::String* sValueName = "";
			System::String* sValueDescription = "";
			bool bEnabled = true;

			sValue = sFeature->Substring(nBeg, nEnd - nBeg)->Trim();

			nBeg = nEnd;
			nEnd = sFeature->IndexOf("\n", nEnd + 1);
			if(sValue->Length > 0){
				int nNameBeg;
				int nNameEnd;
				//������ ������ �������� � ��������� ���
				nNameBeg = sValue->IndexOf("\"");
				nNameEnd = sValue->IndexOf("\"", nNameBeg + 1);
				sValueName = sValue->Substring(0, nNameBeg)->Trim();
				sValueDescription = sValue->Substring(nNameBeg + 1, nNameEnd - nNameBeg - 1)->Trim();

				nNameBeg = sValueName->IndexOf("/");
				//���� ������ �����
				unsigned int SlashCount = 0;
				nNameEnd = 0;
				while(nNameBeg != -1){
					SlashCount++;
					nNameEnd = nNameBeg;
					nNameBeg = sValueName->IndexOf("/", nNameBeg + 1);
				}
				if(SlashCount > 1){
					nNameEnd++;
					bEnabled = false;
				}

				sValueName = sValueName->Substring(nNameEnd, sValueName->Length - nNameEnd);
				AddMapValue(sValueName, sValueDescription, bEnabled);
			}
		}

	}
	///3������� ���� �������� B �����y
	System::String* CFeature::Write(System::String* sText)
	{
		System::String* sTemp = "";
		//������� ���������� ���������
		sTemp = sTemp->Concat(sTemp, new System::String("["));
		sTemp = sTemp->Concat(sTemp, GetFeatureName());
		sTemp = sTemp->Concat(sTemp, new System::String(" "));
		sTemp = sTemp->Concat(sTemp, new System::String("\""));
		sTemp = sTemp->Concat(sTemp, GetFeatureDescription());
		sTemp = sTemp->Concat(sTemp, new System::String("\""));
		sTemp = sTemp->Concat(sTemp, new System::String("]"));
		sTemp = sTemp->Concat(sTemp, new System::String(" "));
		sTemp = sTemp->Concat(sTemp, GetFeatureType());
		sTemp = sTemp->Concat(sTemp, new System::String(" "));
		sTemp = sTemp->Concat(sTemp, new System::String("\""));
		sTemp = sTemp->Concat(sTemp, GetFeatureTypeDescription());
		sTemp = sTemp->Concat(sTemp, new System::String("\""));
		sTemp = sTemp->Concat(sTemp, new System::String("\n"));
		//������ ���������� ��������
		CFeatureValue* pFV = FirstValue();
		while(pFV){
			sTemp = pFV->Write(sTemp);
			pFV = NextValue();
		}
		sTemp = sTemp->Concat(sTemp, new System::String("\n"));

		sTemp = sText->Concat(sText, sTemp);

		return sTemp;
	}


	///������� ������ ���-��������
	void CFeature::ClearMapValues()
	{
		m_ValueArray->Clear();
	}

	///������� ����� �������� � ���
	CFeatureValue* CFeature::AddMapValue(System::String* sValueName, System::String* sValueDescription, bool bEnabled)
	{
		CFeatureValue* pFV = new CFeatureValue(sValueName, sValueDescription, bEnabled);
		m_ValueArray->Add(pFV);

		return pFV;
	}
	///������ ���-�������� ��� ������������ �������
	void CFeature::DeleteFeatureValue(unsigned int nFeatureValue)
	{
		if(nFeatureValue < m_ValueArray->Count){
			m_ValueArray->RemoveAt(nFeatureValue);
		}
	}
	///������ ��������� �� �������������� 
	CFeatureValue* CFeature::GetFeatureValue(unsigned int nFeatureValue)
	{
		if(nFeatureValue < m_ValueArray->Count){
			return __try_cast<CFeatureValue*>(m_ValueArray->Item[nFeatureValue]);
		}
		else{
			return NULL;
		}
	}
	///������ ��������� �� ������ �������������� 
	CFeatureValue* CFeature::FirstValue()
	{
		m_ArrayEnum = m_ValueArray->GetEnumerator();
		if(m_ArrayEnum->MoveNext()){
			return __try_cast<CFeatureValue*>(m_ArrayEnum->Current);
		}
		else{
			return NULL;
		}
	}
	///������ ��������� �� ��������� �������������� 
	CFeatureValue* CFeature::NextValue()
	{
		if(m_ArrayEnum->MoveNext()){
			return __try_cast<CFeatureValue*>(m_ArrayEnum->Current);
		}
		else{
			return NULL;
		}
	}
}