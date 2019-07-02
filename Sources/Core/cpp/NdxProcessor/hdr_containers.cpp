#include "StdAfx.h"
#include ".\hdr_containers.h"

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

void CDocumentHeadersInfo::UpdateHeaderPosition(unsigned int uiPosition)
{
	//!!!���� �� ������� ������������ ������� ������� ���������

	SHeaderInfo HeaderInfo;
	HeaderInfo.m_HeaderID=m_CurrentHeaderID;
	if(m_HeaderInfoCollection.empty()){
		//���� ��������� ������ ���������
		//��������� ����� ���������, ��������� ��� ��������� �������
		
		if(HeaderInfo.m_HeaderID.GetValueAtLevel(0)==0){
			//��������� ������ ��������� ������ ���� �������
			TO_CONSOLE(L"First header not Root header");
			HeaderInfo.m_HeaderID.View();
			//������������� ������� ���������
			m_CurrentHeaderID.Reset();
			m_CurrentHeaderID.IncAtLevel(0);
			HeaderInfo.m_HeaderID=m_CurrentHeaderID;
		}

		m_HeaderInfoCollection.push_back(HeaderInfo);
		m_HeaderInfoCollection.back().m_HeaderPositions.m_uiHeadPosition=uiPosition;
		m_HeaderInfoCollection.back().m_HeaderPositions.m_uiTailPosition=uiPosition;

	}else if(m_HeaderInfoCollection.back().m_HeaderID.GetID()!=m_CurrentHeaderID.GetID()){
		//���� ������������� ��������� ����������� ��������� �� ����� ��������
		//��������� ����� ���������, ��������� ��� ��������� �������

		//��� ���������� ��������� ����� ������� ������ � ������ ������ ��, ����������� ������� ��������
		THeaderInfoCollection::iterator itHeaderInfo=(--m_HeaderInfoCollection.end());
		do{
			//��� ���������� ��������� ������ �� ��� ����� ������� ������, 
			//����������� �������
			if(itHeaderInfo->m_HeaderID.IsAtSameLevel(&m_CurrentHeaderID)){
				//���� ��������� ������ ���������� ������� � �������
				itHeaderInfo->m_HeaderPositions.m_uiBoundPosition=uiPosition;
				break;
			}else if(itHeaderInfo->m_HeaderID<m_CurrentHeaderID){
				//���� ��������� ������, ���������� ������� � ����������
				itHeaderInfo->m_HeaderPositions.m_uiBoundPosition=uiPosition;
				itHeaderInfo--;
			}else{
				break;
			}
		}while(itHeaderInfo!=m_HeaderInfoCollection.begin());
		
		//������ ����� ���������, ������������� ��� �������� �������
		m_HeaderInfoCollection.push_back(HeaderInfo);
		m_HeaderInfoCollection.back().m_HeaderPositions.m_uiHeadPosition=uiPosition;
	
	}else{
		//���� ������������� ��������� ����������� ��������� ����� ��������
		//��������� ��������� �������
		m_HeaderInfoCollection.back().m_HeaderPositions.m_uiTailPosition=uiPosition;
	}
}

bool CDocumentHeadersInfo::IncCurrentHeaderID(unsigned int uiHeaderLevel)
{
	//!!!������������� ������������� �������
	if(m_HeaderInfoCollection.empty()){
		uiHeaderLevel=0;
	}else{
		uiHeaderLevel=1;
	}

	if(GetCurrentHeaderID()->GetValueAtLevel(uiHeaderLevel)>=0xffff) return false;

	//��������� ������� ������������ ���������
    GetCurrentHeaderID()->IncAtLevel(uiHeaderLevel);
	return true;
}

void CDocumentHeadersInfo::ToString(wstring& wszValue)
{
	wszValue.assign(L"\n//--------Bof-CDocumentHeadersInfo:\n");
	wstring wszTemp;
	for(unsigned int i=0; i<m_HeaderInfoCollection.size(); i++){
		wszValue.append(L"\n");
		m_HeaderInfoCollection[i].ToString(wszTemp);
		wszValue.append(wszTemp);
	}
	wszValue.append(L"\n\n//--------Eof-CDocumentHeadersInfo:\n");
}

//--------------------------------------------------------------------//

CHeaderNode::CHeaderNode(CLevelHeaderID* pHeaderID)
:CTreeNode< CHeaderWords<Extracting::Logics::CHeaderLogic::MaxBlockCount>* >
	(new CHeaderWords<Extracting::Logics::CHeaderLogic::MaxBlockCount>)
{
	//������������� ���� �� �������������
	CLevelHeaderID* pHID=GetMyself()->GetHeaderID();
	(*pHID)=(*pHeaderID);
}

void CHeaderNode::InsertHeaderNode(unsigned int uiWordID, CLevelHeaderID* pHeaderID)
{
	if(ISNULL(pHeaderID)) return;

	//��������� ������������� ���������
	CLevelHeaderID* pMyHID=GetMyself()->GetHeaderID();
	if((*pMyHID)==(*pHeaderID)){

		//���� ������ �� ���� ���� ������� �����	
		GetMyself()->SetWordID(uiWordID);

	}else if(pMyHID->GetValueAtLevel(GetHeaderLevel())==pHeaderID->GetValueAtLevel(GetHeaderLevel())){

		//���� ��� ����� ������� ����, �� ���� ��������������� ��������� �� ������ ������
		//���� ������� � ������ ���������, ��� ������� ��� � ���������� ��� ���
		unsigned int uiTemp=pHeaderID->GetValueAtLevel(GetHeaderLevel()+1);
		if(!uiTemp){
			TO_CONSOLE(L"InsertHeaderNode error, imposible value!!!");
			return;
		}
		
		CHeaderNode* pChildNode=static_cast<CHeaderNode*>(GetChild(uiTemp));
		if(!pChildNode){
			//������� �������������� ������������� �� ������� ������
			CLevelHeaderID ChildHeaderID(pHeaderID->GetIDTillLevel(GetHeaderLevel()+1));
			//������� � ��������� �������
			pChildNode=new CHeaderNode(&ChildHeaderID);
			AddChild(uiTemp, pChildNode);
		}
		
		//���������� �������
		pChildNode->InsertHeaderNode(uiWordID, pHeaderID);
	}
}

void CHeaderNode::ToString(wstring& szValue, wstring szOffset)
{
	szOffset.append(L" ");	
	szValue.append(L"\n");
	szValue.append(szOffset);
	szValue.append(L"|-->");
	wstring wszTemp;
	GetMyself()->ToString(wszTemp);
	szValue.append(wszTemp);

	CHeaderNode* pCurrentNode=NULL;
	if(MoveFirstChild())
	do{
		pCurrentNode=static_cast<CHeaderNode*>(GetCurrentChild());
		pCurrentNode->ToString(szValue, szOffset);
	}while(MoveNextChild());
}

//--------------------------------------------------------------------//

CHeadersTree::CHeadersTree(unsigned int uiDocumentIndex)
:m_uiDocumentIndex(uiDocumentIndex), m_pRootNode(NULL)
{
	//������� ������� ����
	CLevelHeaderID RootHeaderID;
	RootHeaderID.IncAtLevel(0);
	m_pRootNode=new CHeaderNode(&RootHeaderID);
	//m_pRootNode->View();

	//������ ������
	//BuildTree(pBlockHIDCollection);
}

CHeadersTree::~CHeadersTree(void)
{
	if(m_pRootNode) delete m_pRootNode;
}

void CHeadersTree::AddNodes(vector<unsigned int>* pWordIDCollection, CFindResult::THIDCollection* pHIDCollection)
{
	if(ISNULL(pWordIDCollection)) return;
	if(ISNULL(pHIDCollection)) return;
	
	//������� ��������� ��������� ����
	for(unsigned int i=0; i<pWordIDCollection->size(); i++){
		for(unsigned int k=0; k<pHIDCollection->size(); k++){
			//��������� ����
			CLevelHeaderID HeaderID(pHIDCollection->at(k));
			//HeaderID.View();
			m_pRootNode->InsertHeaderNode(pWordIDCollection->at(i), &HeaderID);
		}
	}
}

//void CHeadersTree::BuildTree(CFindResult::TBlockHIDCollection* pBlockHIDCollection)
//{
//	if(ISNULL(pBlockHIDCollection)) return;
//	
//	//������� ��������� ��������� ����
//	for(unsigned int i=0; i<pBlockHIDCollection->size(); i++){
//		if(pBlockHIDCollection->at(i)){
//			for(unsigned int k=0; k<pBlockHIDCollection->at(i)->size(); k++){
//				//��������� ����
//				CLevelHeaderID HeaderID(pBlockHIDCollection->at(i)->at(k));
//				//HeaderID.View();
//				m_pRootNode->InsertHeaderNode(i, &HeaderID);
//			}
//		}
//	}
//}

bool CHeadersTree::MoveFirstBranch(void)
{
	m_CurrentBranch.clear();
	if(ISNULL(m_pRootNode)) return false;
	
	//��������������� �� ������� ����� ������
	CHeaderNode* pCurrentNode=m_pRootNode;
	while(pCurrentNode){
		pCurrentNode->MoveFirstChild();
		m_CurrentBranch.push_back(pCurrentNode);
		pCurrentNode=static_cast<CHeaderNode*>(pCurrentNode->GetCurrentChild());
	}

	return true;
}

bool CHeadersTree::MoveNextBranch(void)
{
	if(ISNULL(m_pRootNode)) return false;

	if(m_CurrentBranch.empty()) return false;
	//���������� ��������� ����
	m_CurrentBranch.pop_back();
	if(m_CurrentBranch.empty()) return false;

	//�������� ������ ������������� ����
	CHeaderNode* pCurrentNode=*(--m_CurrentBranch.end());
	if(pCurrentNode->MoveNextChild()){
		//��������� � ��������� �������, ������� ���
		pCurrentNode=static_cast<CHeaderNode*>(pCurrentNode->GetCurrentChild());
		pCurrentNode->MoveFirstChild();
		m_CurrentBranch.push_back(pCurrentNode);
	}

	return true;
}

CHeaderNode* CHeadersTree::GetCurrentLastHeaderAndWordsIDs(
	CHeaderWords<Extracting::Logics::CHeaderLogic::MaxBlockCount>* pHeaderBranchWords)
{
	if(ISNULL(m_pRootNode)) return NULL;
	if(ISNULL(pHeaderBranchWords)) return NULL;
	if(m_CurrentBranch.empty()) return NULL;

	pHeaderBranchWords->Reset();
	//��������� ��������� ��������������� ����
	//������� ����� � ����������� �������������� ����
	for(unsigned int i=0; i<m_CurrentBranch.size(); i++){
		for(unsigned int k=0; k<m_CurrentBranch[i]->GetMyself()->GetMaxWordsNumber(); k++){
			if(m_CurrentBranch[i]->GetMyself()->IsWordExist(k)){
				pHeaderBranchWords->SetWordID(k);
			}
		}
	}	
	

	return m_CurrentBranch.back();
}

void CHeadersTree::ToString(wstring& wszValue)
{
	wszValue.assign(L"\n//--------Bof-CHeadersTree:\n");

	wchar_t buf[100];
	wsprintf(buf, L"DocumentIndex: %u\n", m_uiDocumentIndex);
	wszValue.append(buf);

	wstring wszTemp;
	wstring wszOffset;
	m_pRootNode->ToString(wszTemp, wszOffset);
	wszValue.append(wszTemp);

	wszValue.append(L"\n\n//--------Eof-CHeadersTree:\n");
}

//--------------------------------------------------------------------//


}
}
}
}
}
