#pragma once

#include ".\basis_containers.h"
#include ".\cnt_factory.h"
#include ".\index_container_nodes.h"
#include ".\coordinate_convertor.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

//--------------------------------------------------------------------//

///��������� ���������, �������� ���������� �������
///����� ��������� ���������� �������� ����� �����, ��������� �������������� ��������� ��� �������� ���������
///���������� ��������� � ����������� ����, � ����������� �� �������� ���������,
///����� ��������� �������� � �����, ��� ��������� �������� ������ ����� �����
#pragma pack(push,1)  // Fix packing size 
template <unsigned char LevelsNumber>
class CCoordinateContainer_4i : public CValuesContainer, public CFactoryClient<CContainersFactory>
{
public:
	CCoordinateContainer_4i(CContainersFactory* pContainersFactory, unsigned int uiEntryPoint = EMPTY_VALUE)
	:CValuesContainer(uiEntryPoint), CFactoryClient<CContainersFactory>(pContainersFactory)
	{
		for(unsigned int i=0; i<LevelsNumber; i++){
			m_CoordinateNodes[i]=pContainersFactory->CreateCoordinateNode_4i(i);
		}
	}

	~CCoordinateContainer_4i(void)
	{
		for(unsigned int i=0; i<LevelsNumber; i++){
			delete m_CoordinateNodes[i];
		}
	}

	///��������� �������� � ������
	bool AddCoordinate(unsigned int* pBuffer, unsigned int uiBufferSize)
	{
		if(ISNULL(GetFactory())) return false;
		if(ISNULL(GetFactory()->GetIndexStorage())) return false;
		if(ISNULL(pBuffer)) return false;

		unsigned int uiSplitCoord=0;
		bool bNewTextAdded=false;

		//� ����� ���������� ���������� ������ � ����� ������ � ����������� �� ������������ �������
		SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage::TCoordinateLevelInfo* pLevelCollection=GetFactory()->GetIndexStorage()->GetCoordinateLevelCollection();
		SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=pLevelCollection->begin();
		SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo const* pLevelInfo=NULL;
		do{
			pLevelInfo=(*itLevelStorage);
			if(ISNULL(pLevelInfo)) break;
			//����������� �� ���������� ������� ��� ������
			uiSplitCoord=CCoordinateConvertor::SplitCoordinate(
				*(pBuffer+(unsigned int)(pLevelInfo->m_IndexCoordinateType)), 
				pLevelInfo->m_ucStartBit,
				pLevelInfo->m_ucBitPerLevel);
			
			//START_TICK(L"AddValue");
			//��������� ������� ���������� � ���������
			if(m_CoordinateNodes[pLevelInfo->m_ucLevelNumber]->AddCoordinate(uiSplitCoord)){
				//����� �������� ���������� ���������� ��������, ���������� ����
				UpdateChildNodes(pLevelInfo->m_ucLevelNumber);			

				//���� ����� ������� ������ ������������� ����
				if(pLevelInfo->m_eControlType==SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::lctWords){
					bNewTextAdded=true;
				}
			}

			if(pLevelInfo->m_eControlType==SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::lctWords){
				m_CoordinateNodes[LevelsNumber-1]->AddCoordinate(*(pBuffer+4));
			}
			//STOP_TICK(L"AddValue");
		}while(++itLevelStorage!=pLevelCollection->end());
		
		//View();
		
		return bNewTextAdded;
	}
	///��������� ���������� �� ��������
	void MoveUp(unsigned int uiOffset)
	{
		if(uiOffset==EMPTY_OFFSET){
			ERR_TO_CONSOLE(erCommon, L"Offset is empty!!!");
			return;
		}
		
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pCoordinatesStorage=GetCoordinatesStorage();
		if(ISNULL(pCoordinatesStorage)) return;
		
		//�������� ���� �� ������� � �������
		SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset CurrentOffset;
		CurrentOffset.ucFileIndex=0;
		CurrentOffset.uiOffset=uiOffset;
		unsigned char i=0; 
		unsigned int uiDataSize=0; 
		unsigned int uiTemp=0;
		do{
			//������ ���� � ���������
			if(!pCoordinatesStorage->StartRead(&CurrentOffset, &uiDataSize)){
				TO_CONSOLE(L"StartRead failed!!!");
				return;
			}
			m_CoordinateNodes[i]->Read(pCoordinatesStorage);
			pCoordinatesStorage->StopRead(&uiTemp);

			//� ��������� �� ��� ������ �� ����� ������� ������ ��� ������ ������
			pCoordinatesStorage->Delete(&CurrentOffset);
					
			if(i==LevelsNumber-2){
				//��� �������������� ��������� ��������� ����
				m_CoordinateNodes[i]->PopLastChild(m_CoordinateNodes[i+1]);
			}else{
				//��� �������� ���� �������� �������� �� ��������� ����
				m_CoordinateNodes[i]->PopLastChildOffset(&CurrentOffset);
			}
		}while(++i<LevelsNumber-1);
		
		//ToConsole(L"Eof-MoveUp");
	}

	///����� ����������, ���������� �������� 
	unsigned int MoveDown(void)
	{
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pCoordinatesStorage=GetCoordinatesStorage();
		if(ISNULL(pCoordinatesStorage)) return EMPTY_VALUE;

		//ToConsole(L"MoveDown");
		
		//������� � ������ ���������� ���� ������ �� � ���������
		SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset CurrentOffset;
		unsigned char i=LevelsNumber; 
		unsigned int uiTemp=0;
		do{
			--i;

			if(i==LevelsNumber-1){
				//��������� ���� ����� ������ � �������������
				m_CoordinateNodes[i-1]->AddChild(m_CoordinateNodes[i]);
				//���������� ���������� ���� ��� ������ ����������
				m_CoordinateNodes[i]->ResetNode();
				continue;
			}

			memset((void*)&CurrentOffset, 0xff, sizeof(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset));
			
			if(m_CoordinateNodes[i]->IsEmptyNode()){ 
				ERR_TO_CONSOLE(erCommon, L"Cann't write empty node")		
					return CurrentOffset.uiOffset;
			}

			//������ ���� � ���������
			pCoordinatesStorage->StartUnCompleteDataAppend(&CurrentOffset);
			m_CoordinateNodes[i]->Write(pCoordinatesStorage);
			pCoordinatesStorage->StopAppend(&uiTemp);

			//�������� �������� ������������� ����
			if(i!=0) m_CoordinateNodes[i-1]->AddChildOffset(&CurrentOffset);
			
			//���������� ���������� ���� ��� ������ ����������
			m_CoordinateNodes[i]->ResetNode();
		}while(i>0);

		//ToConsole(L"Eof-MoveDown");

		return CurrentOffset.uiOffset;
	}

	///��������� �������� ����������� ���������� �������, ��� ���������� ����������
	bool UpdateFreqIncreaseKoef(unsigned int* pBuffer, unsigned int uiBufferSize, unsigned char ucFreqIncreaseKoef){return false;};

	/////���������� ���������� ������� ������
	//void View(void);
	/////������������ � ������
	//void ToString(wstring& szValue, wstring szOffset);

protected:
	///��������� ����������� ���� ������� � ������������ ������
	void UpdateChildNodes(unsigned char ucParentNodeLevel)
	{
		//ToConsole(L"UpdateChildNodes");
		if(ucParentNodeLevel>=LevelsNumber-1) return;
		
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pCoordinatesStorage=GetCoordinatesStorage();
		if(ISNULL(pCoordinatesStorage)) return;
		
		//������� � ������ ���������� ���� ������ �� � ���������
		SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset CurrentOffset;
		unsigned char i=LevelsNumber-1; 
		unsigned int uiTemp=0;
		do{
			//���� ���� ������ ��� ������ ����������, ���� �� ���������� 
			if(m_CoordinateNodes[i]->IsEmptyNode()) return;

			if(i==LevelsNumber-1){
				//��������� ���� ����� ������ � �������������
				m_CoordinateNodes[i-1]->AddChild(m_CoordinateNodes[i]);
				//���������� ���������� ���� ��� ������ ����������
				m_CoordinateNodes[i]->ResetNode();
				continue;
			}

			memset((void*)&CurrentOffset, 0xff, sizeof(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset));

			//������ ���� � ���������
			pCoordinatesStorage->StartCompleteDataAppend(&CurrentOffset);
			m_CoordinateNodes[i]->Write(pCoordinatesStorage);
			pCoordinatesStorage->StopAppend(&uiTemp);

			//�������� �������� ������������� ����
			m_CoordinateNodes[i-1]->AddChildOffset(&CurrentOffset);
			
			//���������� ���������� ���� ��� ������ ����������
			m_CoordinateNodes[i]->ResetNode();
		}while(--i!=ucParentNodeLevel);
		
		//ToConsole(L"Eof-UpdateChildNodes");
	}

	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* GetCoordinatesStorage(void){return GetFactory()->GetIndexStorage()->GetCoordinateStorage();};

	///������ ������������ �����,
	CCoordinateNode_4i* m_CoordinateNodes[LevelsNumber];
};
#pragma pack(pop)

typedef CCoordinateContainer_4i<3> TCoordinateContainer;

//--------------------------------------------------------------------//

}
}
}
}
}