#include "StdAfx.h"
#include ".\index_container_s.h"

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

using namespace SS::Interface::Core::NdxSE::NdxDataStorage;

//--------------------------------------------------------------------//

CCoordinateContainer_4s::CCoordinateContainer_4s(CContainersFactory* pContainersFactory, unsigned int uiEntryPoint)
:CValuesContainer(uiEntryPoint), CFactoryClient<CContainersFactory>(pContainersFactory), m_pRootNode(NULL)
{
}

CCoordinateContainer_4s::~CCoordinateContainer_4s(void)
{
	if(m_pRootNode) delete m_pRootNode;
}

void CCoordinateContainer_4s::SetFreshValues(CValue* pPrevValue, TValuePtrsBuffer* pValuePtrsBuffer)
{
 	if(ISNULL(pValuePtrsBuffer)) return;
	if(pValuePtrsBuffer->size()==0) return;

	SCompositeOffset Offset;
	if(!pPrevValue){

		if(m_uiEntryPoint==EMPTY_OFFSET) return;

		//���� ���������� ���� �� ��������, ������ �������� ������� �������
		m_pRootNode=GetFactory()->CreateCoordinateNode_4s(0);
		//������ ���� �� ���������
		Offset.ucFileIndex=0;
		Offset.uiOffset=m_uiEntryPoint;
		//������ ���� ����
		m_pRootNode->ReadNode(m_pRootNode, &Offset);
		((*pValuePtrsBuffer)[0])=dynamic_cast<CValue*>(m_pRootNode);

	}else{

		//���� ���������� ���� ��������, ������� ���� ����������� ��������
		CBmCoordinateNode_4s* pParentNode=dynamic_cast<CBmCoordinateNode_4s*>(pPrevValue);
		CCoordinateNode_4s* pCoordinateNode=NULL;
		unsigned int uiValue;
		//������� ������� ����, ������� � ������ ���� �� ��� ���������, 
		if(pParentNode->MoveFirstOrt()){
			do{
				uiValue=pParentNode->GetCurrentOrt();
				
				//��������� ����� �� ����� �� �������
				if(uiValue>=pValuePtrsBuffer->size()) break;

				//�������� ����
				pCoordinateNode=pParentNode->MoveUpChildNode(uiValue);

				//������ � �������� ��������
				((*pValuePtrsBuffer)[uiValue])=dynamic_cast<CValue*>(pCoordinateNode);
			}while(pParentNode->MoveNextOrt());
		}
	}
}

void CCoordinateContainer_4s::FreeValues(CValue* pGenerativeValue)
{
	if(ISNULL(pGenerativeValue)) return;
	CCoordinateNode_4s* pCoordinateNode=dynamic_cast<CCoordinateNode_4s*>(pGenerativeValue);
	pCoordinateNode->ResetNode();
}

//--------------------------------------------------------------------//

}
}
}
}
}