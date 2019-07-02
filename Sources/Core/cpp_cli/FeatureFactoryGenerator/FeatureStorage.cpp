#include "StdAfx.h"
#include ".\featurestorage.h"
#using <mscorlib.dll>

namespace FeatureFactoryGenerator
{
	CFeatureStorage::CFeatureStorage(void)
	{
		m_FeatureGroupArray = new System::Collections::ArrayList();
		m_sPath = NULL;
	}

	CFeatureStorage::~CFeatureStorage(void)
	{
	}

	///��������� �������������� �� ������ � ���������� sPath
	void CFeatureStorage::LoadGroups(System::String* sPath)
	{
		m_FeatureGroupArray->Clear();

		// Create a reference to the current directory.
		System::IO::DirectoryInfo* di = new System::IO::DirectoryInfo(sPath);

		// Create an array representing the files in the current directory.
		System::IO::FileInfo* fi[] = di->GetFiles();

		System::Collections::IEnumerator* myEnum = fi->GetEnumerator();
		while (myEnum->MoveNext()) {
			System::IO::FileInfo* fiTemp = __try_cast<System::IO::FileInfo*>(myEnum->Current);

			if(fiTemp->Name->Length > 5){

				System::String* sName = fiTemp->Name->Substring(0, fiTemp->Name->Length - 5);
				System::String* sExt = fiTemp->Name->Substring(fiTemp->Name->Length - 5, 5);
				sExt = sExt->ToLower();

				if(sExt->Equals(".ffgg")){
					AddGroup(sName)->LoadFeatures(sPath);
				}

				//fiTemp->Name->Equals();
				fiTemp->Name;
			}
		}
		m_sPath = sPath;
	}

	///��������� �������������� � ����� � ���������� sPath
	void CFeatureStorage::SaveGroups(System::String* sPath)
	{
		CFeatureGroup* pFG = FirstGroup();
		while(pFG){
			pFG->SaveFeatures(sPath);
			pFG = NextGroup();
		}
	}

	///������� ������ ������ ������������� � �������� ������
	CFeatureGroup* CFeatureStorage::AddGroup(System::String* sGroupName)
	{
		CFeatureGroup* pFG = new CFeatureGroup(sGroupName);
		m_FeatureGroupArray->Add(pFG);

		return pFG;
	}

	///������ ��������� �� ������ 
	CFeatureGroup* CFeatureStorage::GetGroup(unsigned int nGroup)
	{
		if(nGroup < m_FeatureGroupArray->Count){
			return __try_cast<CFeatureGroup*>(m_FeatureGroupArray->Item[nGroup]);
		}
		else{
			return NULL;
		}
	}
	///������ ��������� �� ������ ������ 
	CFeatureGroup* CFeatureStorage::FirstGroup()
	{
		m_ArrayEnum = m_FeatureGroupArray->GetEnumerator();
		if(m_ArrayEnum->MoveNext()){
			return __try_cast<CFeatureGroup*>(m_ArrayEnum->Current);
		}
		else{
			return NULL;
		}
	}
	///������ ��������� �� ��������� ������ 
	CFeatureGroup* CFeatureStorage::NextGroup()
	{
		if(m_ArrayEnum->MoveNext()){
			return __try_cast<CFeatureGroup*>(m_ArrayEnum->Current);
		}
		else{
			return NULL;
		}
	}
}