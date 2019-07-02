#include "StdAfx.h"
#include ".\base_factory.h"
#include ".\base_manager.h"
#include ".\console.h"
#include "..\ASCInterface\ICommonServices.h"
#include "..\ASDInterface\TNdxSearchEngineTypes.h"
#include "..\ASCInterface\defines.h"

USES_LOAD_MANAGER;

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxBaseManager
{

using namespace SS::Interface::Core::NdxSE::NdxDataStorage;
using namespace SS::Interface::Core::NdxSE;
using namespace SS::Interface::Core::DBMS;

//--------------------------------------------------------------------//

CNdxBaseFactory::CNdxBaseFactory(void)
:m_pNdxDataStorageFactory(NULL)
{
}

CNdxBaseFactory::~CNdxBaseFactory(void)
{
	if(m_pNdxDataStorageFactory)
		m_pNdxDataStorageFactory->Release();
}

void CNdxBaseFactory::CreateBase(CNdxBaseManager* pNdxBaseManager)
{
	SS_TRY

	if(ISNULL(pNdxBaseManager)) SS_THROW(L"pNdxBaseManager is null!");
	if(ISNULL(pNdxBaseManager->GetLoadManager())) SS_THROW(L"pNdxBaseManager->GetLoadManager() is null!");

	//m_pNdxDataStorageFactory=(INdxDataStorageFactory*)pNdxBaseManager->GetLoadManager()->
	//	GetInterface(L"./core/NdxDataStorage.dll", CLSID_NdxDataStorageFactory, IID_NdxDataStorageFactory);

	if(!m_pNdxDataStorageFactory){
		pNdxBaseManager->GetLoadManager()->Create(L"./core/NdxDataStorage.dll", 
			CLSID_NdxDataStorageFactory, IID_NdxDataStorageFactory, (void**)&m_pNdxDataStorageFactory);
	}

	if(ISNULL(m_pNdxDataStorageFactory)) SS_THROW(L"m_pNdxDataStorageFactory is null!");

	CNdxBaseManager::TNdxBaseStructCollection* pBaseStructure=pNdxBaseManager->GetBaseStructure();
	
	if(pBaseStructure->empty()){
		//���� ��������� ������ ���������� ����������� �������������

		//��������� ��������� ���������
		CreateIndexStoragesBySettings(pNdxBaseManager);

		//��������� ������������ ���������
		//��������� ��������� ���������� � ����������������� �������
		CreateTextInfo(pNdxBaseManager);
		//��������� ��������� ����� � ������� � ���� ������ �����
		CreateTextPathStorage(pNdxBaseManager);
		//��������� ��������� ����� ������� � ���� ������� DBMS
		CreateTextFieldsStorage(pNdxBaseManager);

	}else{
		//���� ��������� �� ������ ���������� �� � ������� �����
		for(CNdxBaseManager::TNdxBaseStructCollection::iterator itBaseUtem=pBaseStructure->begin(); itBaseUtem!=pBaseStructure->end(); itBaseUtem++){
			
			if(itBaseUtem->first==ObligatoryStorageNames::TextsInfoStorage){
				//��������� ��������� ���������� � ����������������� �������
				CreateTextInfo(pNdxBaseManager);
			}else if(itBaseUtem->first==ObligatoryStorageNames::TextsPathTreeStorage){
				//��������� ��������� ����� � ������� � ���� ������ �����
				CreateTextPathStorage(pNdxBaseManager);
			}else if(itBaseUtem->first==ObligatoryStorageNames::TextsFieldsStorage){
				//��������� ��������� ����� ������� � ���� ������� DBMS
				CreateTextFieldsStorage(pNdxBaseManager);
			}else{
				//��������� ��������� ���������
				CreateIndexStorage(pNdxBaseManager, itBaseUtem->first.c_str(), itBaseUtem->second, true);
			}
		}
	}

	SS_CATCH(L"");
}

void CNdxBaseFactory::CreateTextInfo(CNdxBaseManager* pNdxBaseManager)
{
	if(ISNULL(pNdxBaseManager)) return;
	if(ISNULL(m_pNdxDataStorageFactory)) return;

	//��������� ��������� ��������� ����������� ������
	INdxVectorStorage* pNdxVectorStorage=m_pNdxDataStorageFactory->CreateNdxVectorStorage();
	pNdxVectorStorage->Create(ObligatoryStorageNames::TextsInfoStorage, L".srv");

	pNdxBaseManager->AddNdxBaseUnit(ObligatoryStorageNames::TextsInfoStorage, pNdxVectorStorage);
}

void CNdxBaseFactory::CreateTextPathStorage(CNdxBaseManager* pNdxBaseManager)
{
	if(ISNULL(pNdxBaseManager)) return;
	if(ISNULL(m_pNdxDataStorageFactory)) return;

	//��������� ��������� ��������� ����������� ������
	INdxFile* pNdxCashedFile=m_pNdxDataStorageFactory->CreateNdxFile();
	pNdxCashedFile->Create(ObligatoryStorageNames::TextsPathTreeStorage, L".srv");

	pNdxBaseManager->AddNdxBaseUnit(ObligatoryStorageNames::TextsPathTreeStorage, pNdxCashedFile);
}

void CNdxBaseFactory::CreateIndexStorage(CNdxBaseManager* pNdxBaseManager, const wchar_t* wszIndexStorageName, 
								  ENdxStorageConfig StorageConfig, bool bStorageWithStatistic)
{
	if(ISNULL(pNdxBaseManager)) return;
	if(ISNULL(m_pNdxDataStorageFactory)) return;

	SS::Interface::Core::CommonServices::ISettingsServer* pSettings=
	(SS::Interface::Core::CommonServices::ISettingsServer*)pNdxBaseManager->GetLoadManager()->
		GetInterface(L"./core/GSServer.dll", CLSID_SettingsServer , IID_SettingsServer);

	if(ISNULL(pSettings)) SS_THROW(L"pSettings is null!");

	INdxStorage* pNdxStorage=NULL;
	
	//���������� ���� ���������� � ���������
	if(bStorageWithStatistic){
		pNdxStorage=dynamic_cast<INdxStorage*>(m_pNdxDataStorageFactory->CreateNdxStorageWithStatistic());
	}else{
		pNdxStorage=m_pNdxDataStorageFactory->CreateNdxStorage();
	}
	
	//���������� ��� ���������
	pNdxStorage->Create(wszIndexStorageName, L".ndx");
	

	//������������� ���������
	if(StorageConfig==escText_WC){
		int iIndexBaseConfig=pSettings->GetInt(L"NdxBaseManager::IndexBaseConfig");
	
		if(iIndexBaseConfig==0){
			StorageConfig=escText_WC_Huge;
		}else if(iIndexBaseConfig==1){
			StorageConfig=escText_WC_ForSmall;
		}
	}
	m_NdxConfigurator.Cofigure(pNdxStorage, StorageConfig);

	//��������� ��������� � ����
	pNdxBaseManager->AddNdxBaseUnit(wszIndexStorageName, pNdxStorage);
}

void CNdxBaseFactory::CreateIndexStoragesBySettings(CNdxBaseManager* pNdxBaseManager)
{
	SS_TRY

	if(ISNULL(pNdxBaseManager)) SS_THROW(L"pNdxBaseManager is null!");

	SS::Interface::Core::CommonServices::ISettingsServer* pSettings=
	(SS::Interface::Core::CommonServices::ISettingsServer*)pNdxBaseManager->GetLoadManager()->
		GetInterface(L"./core/GSServer.dll", CLSID_SettingsServer , IID_SettingsServer);

	if(ISNULL(pSettings)) SS_THROW(L"pSettings is null!");

	SS::Interface::Core::CommonServices::EParameterType ParameterType=SS::Interface::Core::CommonServices::ptString;
	unsigned int uiArrayCount=0;
	vector<wstring> vFieldsNames;
	pSettings->GetArray(L"AMIS::TextFields", ParameterType, (void*)&vFieldsNames);
	wchar_t* wszField=NULL;
	for (unsigned int i = 0; i <vFieldsNames.size(); i++)
	{
		//�������� ��� ���������
		wszField=(wchar_t*)vFieldsNames[i].c_str();
		//��������� ��������� ���������
		CreateIndexStorage(pNdxBaseManager, wszField, /*escText*/escText_WC, true);
	}

	SS_CATCH(L"");
}

void CNdxBaseFactory::CreateTextFieldsStorage(CNdxBaseManager* pNdxBaseManager)
{
	if(ISNULL(pNdxBaseManager)) return;
	if(ISNULL(m_pNdxDataStorageFactory)) return;

	//��������� ��������� ��������� ����������� ������
	INdxTableStorage* pNdxTableStorage=m_pNdxDataStorageFactory->CreateNdxTableStorage();
	pNdxTableStorage->Create(ObligatoryStorageNames::TextsFieldsStorage, L".ndx");
	
	SS::Interface::Core::CommonServices::ISettingsServer* pSettings=
	(SS::Interface::Core::CommonServices::ISettingsServer*)pNdxBaseManager->GetLoadManager()->
		GetInterface(L"./core/GSServer.dll", CLSID_SettingsServer , IID_SettingsServer);

	if(ISNULL(pSettings)) return;

	TDataTableFieldDescription DataTableFieldDescription;
	SS::Interface::Core::CommonServices::EParameterType ParameterType=SS::Interface::Core::CommonServices::ptString;
	vector<wstring> vFieldsNames;
	pSettings->GetArray(L"AMIS::Fields", ParameterType, (void*)&vFieldsNames);
	wchar_t* wszField=NULL;
	wchar_t wszSeps[]=L" ";
	wchar_t *wszToken;
	for (unsigned int i = 0; i < vFieldsNames.size(); i++)
	{
		//������ ������ ���� ������� �� ���� ������: ��� ����, ��� ����, ����������� ����
		//����������� ��������
		wszField=(wchar_t*)vFieldsNames[i].c_str();
		wszToken=wcstok(wszField, wszSeps);
		int k=0;
		while(wszToken!=NULL)
		{
			switch(k){
			case 0:
				//��� ����
				DataTableFieldDescription.szFieldName=wszToken;
				break;
			case 1:
				//��� ����
				DataTableFieldDescription.etFieldType=SS::Interface::Core::NdxSE::CNdxMetaField::StringToFieldDataTypes(wszToken);
				break;
			case 2:
				//����������� ����
				DataTableFieldDescription.etFieldModificator=SS::Interface::Core::NdxSE::CNdxMetaField::StringToFieldModificatorTypes(wszToken);
				if(DataTableFieldDescription.etFieldModificator==MOD_COMMON) DataTableFieldDescription.etFieldModificator|=MOD_INDEXED;
				break;
			default:
				break;
			}

			wszToken=wcstok(NULL, wszSeps);
			k++;			
		}
		
		//��������� ���� � �������
		pNdxTableStorage->AddField(&DataTableFieldDescription);
	}

	pNdxBaseManager->AddNdxBaseUnit(ObligatoryStorageNames::TextsFieldsStorage, pNdxTableStorage);
}

//--------------------------------------------------------------------//

}
}
}
}