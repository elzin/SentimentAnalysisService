#include "StdAfx.h"
#include ".\texts_path_storage.h"
#include ".\console.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Storages
{

using namespace SS::Core::NdxSE::NdxProcessor;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Interface::Core::NdxSE::NdxDataStorage;
using namespace SS::Interface::Core::NdxSE;

//--------------------------------------------------------------------//

bool CStringService::StrEqual(const wchar_t* sz1, const wchar_t* sz2)
{
	if(ISNULL(sz1)) return false;
	if(ISNULL(sz2)) return false;

	int i = 0;

	wchar_t chbuf1[2];
	wchar_t chbuf2[2];

	chbuf1[1] = 0;
	chbuf2[1] = 0;

	do{
		chbuf1[0] = sz1[i];
		chbuf2[0] = sz2[i];
		_wcslwr(chbuf1);
		_wcslwr(chbuf2);


		if(chbuf1[0] != chbuf2[0]) return false;
		if(chbuf1[0] == 0) break;
		i++;
	}while(chbuf1[0] != 0);

	return true;
}

//--------------------------------------------------------------------//

CTextPathNode::CTextPathNode(const wchar_t* pMyPathChunk, unsigned int uiMyIndex)
:CVecTreeNode<STextPathChunk*>
(new STextPathChunk(pMyPathChunk, uiMyIndex))
{
}

CTextPathNode::~CTextPathNode(void){

}

CTextPathNode* CTextPathNode::AddChild(const wchar_t* pMyPathChunk, unsigned int uiMyIndex)
{
	TChilds::iterator itChild=m_Childs.begin();
	while(itChild!=m_Childs.end()){
		if(*itChild){
			//���������� ������
			if(CStringService::StrEqual((*itChild)->GetMyself()->m_pMyPathChunk, pMyPathChunk)){
				return static_cast<CTextPathNode*>(*itChild);
			}
		}
		itChild++;
	}
	
	//���� ����������� ����� �� ���� ��������� ������ �������
	return static_cast<CTextPathNode*>(CVecTreeNode<STextPathChunk*>::AddChild(new CTextPathNode(pMyPathChunk, uiMyIndex)));
}

void CTextPathNode::MoveDown(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxFile)
{
	if(ISNULL(pNdxFile)) return;

	//����� ������� ���� ������� ����
	STextPathChunk* pTextPathChunk=GetMyself();
	if(ISNULL(pTextPathChunk)) return;
	
	//���������� ���� ��������
	pTextPathChunk->m_uiMyOffset=pNdxFile->GetDataUnitSize();
	
	
	//��������� ���� ��������
	bool bDeleted=false;
	pNdxFile->Append((unsigned char*)&bDeleted, sizeof(unsigned char));

	unsigned int uiTemp=EMPTY_VALUE;
	//��������� �������� �� ��������
	if(GetParent())
		uiTemp=GetParent()->GetMyself()->m_uiMyOffset;
	pNdxFile->Append((unsigned char*)&uiTemp, sizeof(unsigned int));

	//��������� �������� �� �����
	uiTemp=EMPTY_VALUE;
	pNdxFile->Append((unsigned char*)&uiTemp, sizeof(unsigned int));

	//��������� ������ �����
	pNdxFile->Append((unsigned char*)&pTextPathChunk->m_uiMyIndex, sizeof(unsigned int));

	//��������� ����� ����� ���� � ������ 
	uiTemp=(unsigned int)(wcslen(pTextPathChunk->m_pMyPathChunk)*sizeof(wchar_t));
	pNdxFile->Append((unsigned char*)&uiTemp, sizeof(unsigned int));
	//��������� ����� ����
	pNdxFile->Append((unsigned char*)pTextPathChunk->m_pMyPathChunk, uiTemp);
	
	//���������� �����
	vector<unsigned int> ChildsOffsets;
	ChildsOffsets.reserve(m_Childs.size());
	TChilds::iterator itChild=m_Childs.begin();
	while(itChild!=m_Childs.end()){
		if((*itChild)){
			((CTextPathNode*)(*itChild))->MoveDown(pNdxFile);
			//������ � ����� �������� �������
			ChildsOffsets.push_back((*itChild)->GetMyself()->m_uiMyOffset);
		}
		itChild++;
	}
	
	if(!ChildsOffsets.empty()){
		//���� ���� �������� ���� 

		//���������� �������� �� �����
		unsigned int uiChildsOffset=pNdxFile->GetDataUnitSize();

		//��������� ���������� �����
		uiTemp=(unsigned int)ChildsOffsets.size();
		pNdxFile->Append((unsigned char*)&uiTemp, sizeof(unsigned int));
		//��������� ����� �������� �����
		pNdxFile->Append((unsigned char*)(&ChildsOffsets.front()), ((unsigned int)ChildsOffsets.size()*sizeof(unsigned int)));
		
		//����� ���� �������� �� �����
		pNdxFile->SeekPos(pTextPathChunk->m_uiMyOffset+sizeof(unsigned int)+sizeof(unsigned char), SEEK_SET);
		pNdxFile->Write((unsigned char*)&uiChildsOffset, sizeof(unsigned int));
	}
}	

//--------------------------------------------------------------------//

CTextsPathsTreeStorage::CTextsPathsTreeStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxCashedFile)
:m_pNdxCashedFile(pNdxCashedFile), m_RootPathNode(L"Root")
{
}

CTextsPathsTreeStorage::~CTextsPathsTreeStorage(void)
{
}

void CTextsPathsTreeStorage::BuildTree(CTextsFieldsStorage* pTextsInfo)
{
	if(ISNULL(pTextsInfo)) return;

	if(m_pNdxCashedFile->IsOpen()){
		unsigned int uiTextsNumber=pTextsInfo->GetTextsNumber();
		wstring wszTextPath(L"");

		SS::Interface::Core::NdxSE::CNdxMetaField NdxMetaField(
			L"FileName", 
			SS::Interface::Core::DBMS::TYPE_WSTRING, 
			SS::Interface::Core::DBMS::MOD_COMMON);

		for(unsigned int uiTextIndex=0; uiTextIndex<uiTextsNumber; uiTextIndex++){
			//������� ���� �� ������� ������
			pTextsInfo->GetTextInfo(uiTextIndex, &NdxMetaField);
			wszTextPath.assign(((wstring*)NdxMetaField.GetValue())->c_str());
			//ToConsole(wszTextPath.c_str());
			if(wszTextPath.size()!=0){
				//���� ���� ���� ��������� ��� � ������
				//����� ���� �� �����, �� ������� ����� ����� ����� ��������� ����
				vector<wstring> ChunksCollection;
				HackTextPathOnChunks((wchar_t*)wszTextPath.c_str(), &ChunksCollection);
				CTextPathNode* pCurrNode=&m_RootPathNode;
				
				//� ����� ������� ����� �����, ������� ���� ������ �����
				for(unsigned int uiCurrChunkIndex=0; uiCurrChunkIndex<ChunksCollection.size(); uiCurrChunkIndex++){
					if(uiCurrChunkIndex==ChunksCollection.size()-1){
						//���� ����� ���� ���������, ������� ���� � �������� �����
						pCurrNode=pCurrNode->AddChild(ChunksCollection[uiCurrChunkIndex].c_str(), uiTextIndex);
					}else{
						pCurrNode=pCurrNode->AddChild(ChunksCollection[uiCurrChunkIndex].c_str());
					}
				}


			}
		}
		
		//������� ��������� ������ �� ����
		MoveDown();	
	}else{
		TO_CONSOLE(L"TextsPathsTree not opened!!!");
	}
}

void CTextsPathsTreeStorage::AddTextPath(unsigned int uiTextIndex, wchar_t* pszTextPath)
{
	if(ISNULL(pszTextPath)) return;
	if(uiTextIndex==EMPTY_VALUE){ 
		TO_CONSOLE(L"TextIndex is empty!!!");	
		return;
	}

	if(wcslen(pszTextPath)!=0){
		//���� ���� ���� ��������� ��� � ������
		//����� ���� �� �����, �� ������� ����� ����� ����� ��������� ����
		vector<wstring> ChunksCollection;
		HackTextPathOnChunks(pszTextPath, &ChunksCollection);
		CTextPathNode* pCurrNode=&m_RootPathNode;
		
		//� ����� ������� ����� �����, ������� ���� ������ �����
		for(unsigned int uiCurrChunkIndex=0; uiCurrChunkIndex<ChunksCollection.size(); uiCurrChunkIndex++){
			if(uiCurrChunkIndex==ChunksCollection.size()-1){
				//���� ����� ���� ���������, ������� ���� � �������� �����
				pCurrNode=pCurrNode->AddChild(ChunksCollection[uiCurrChunkIndex].c_str(), uiTextIndex);
			}else{
				pCurrNode=pCurrNode->AddChild(ChunksCollection[uiCurrChunkIndex].c_str());
			}
		}


	}
}

void CTextsPathsTreeStorage::HackTextPathOnChunks(wchar_t* pszTextPath, vector<wstring>* pChunksCollection)
{
	bool bEmptyFileName=false;
	//���������� ����� ������ ����
	unsigned int ln = (unsigned int)wcslen(pszTextPath) - 1;
	if(pszTextPath[ln] == '/' || pszTextPath[ln] == '\\'){
		pszTextPath[ln]= 0 ;
		//������������� ���� ������� ����� �����
		bEmptyFileName=true;
	}

	wchar_t* buff=new wchar_t[wcslen(pszTextPath)+1];
	bool bCanBreakPath = true;
	unsigned int i=0;
	unsigned int k=0;

	//� ����� ����������� ����� ���� � ������ ����� ������ �����
	while(pszTextPath[i] != 0){
		if((pszTextPath[i] == '\\' || pszTextPath[i] == '/' /*|| pszTextPath[i] == '?' || pszTextPath[i] == '|'*/) && bCanBreakPath){

			//if(pszTextPath[i] == '?'){
			//	bCanBreakPath = false;
			//}

			//���� ���� �������� ����� ���� ������
			if(k>0){
				//�������� ������
				buff[k] = 0;
				//��������� ��������� �����
				pChunksCollection->push_back(buff);
				//������ ������
				k = 0;
			}
		}
		else{
			//���� ��� ��������� �������� ����� ���� ������
			buff[k] = pszTextPath[i];
			k++;
		}
		i++;
	}

	//�������� ������
	buff[k] = 0;
	
	//��������� ��������� �����
	pChunksCollection->push_back(buff);
	
	if(bEmptyFileName){
		//���� ���������� ���� ������� ����� �����, ������ ��� ������
		pChunksCollection->push_back(L" ");
	}

	delete[] buff;
}

void CTextsPathsTreeStorage::MoveDown(void)
{
	if(m_pNdxCashedFile->IsOpen()){
		//������� �� ��� ����
		m_pNdxCashedFile->Clear();
		//���������� �� ����
		m_RootPathNode.MoveDown(m_pNdxCashedFile);	
		//���������� ������ �� ����
		m_pNdxCashedFile->Flush();
	}else{
		TO_CONSOLE(L"TextsPathsTree not opened!!!");
	}
}

void CTextsPathsTreeStorage::FillTextPathChunk(STextPathChunk* pTextPathChunk)
{
	if(ISNULL(pTextPathChunk)) return;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		if(pTextPathChunk->m_uiMyOffset==EMPTY_OFFSET){
			TO_CONSOLE(L"TextPathChunk offset not filled!!!");		
			return;
		}

		if(pTextPathChunk->m_pMyPathChunk){
			//���� ����� ���� ��� ������� ���
			delete[] pTextPathChunk->m_pMyPathChunk;
			pTextPathChunk->m_pMyPathChunk=NULL;
		}
		
		if(IsTextPathChunkDeleted(pTextPathChunk)){ 
			//���� ���� ������ ������ �� ��������� �� ����
			return;
		}

		//��������� � ����� ��� �������� ������
		unsigned int uiDataOffset=pTextPathChunk->m_uiMyOffset+(sizeof(unsigned int)*2)+sizeof(unsigned char);
		m_pNdxCashedFile->SeekPos(uiDataOffset, SEEK_SET);

		//������ ������������� ����
		m_pNdxCashedFile->Read((unsigned char*)&pTextPathChunk->m_uiMyIndex, sizeof(unsigned int));

		//������ ����� ����� ���� � ������
		unsigned int uiTemp=0;
		m_pNdxCashedFile->Read((unsigned char*)&uiTemp, sizeof(unsigned int));

		//������ ����� ����
		unsigned int uiTextPathChunkSize=uiTemp/sizeof(wchar_t);
		pTextPathChunk->m_pMyPathChunk=new wchar_t[uiTextPathChunkSize+1];
		m_pNdxCashedFile->Read((unsigned char*)pTextPathChunk->m_pMyPathChunk, uiTemp);
		*((wchar_t*)(pTextPathChunk->m_pMyPathChunk)+uiTextPathChunkSize)=0;
	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
	}
}

void CTextsPathsTreeStorage::GetChildsOffsets(STextPathChunk* pTextPathChunk, vector<unsigned int>* pChildsOffsetsCollection)
{
	if(ISNULL(pTextPathChunk)) return;
	if(ISNULL(pChildsOffsetsCollection)) return;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		if(pTextPathChunk->m_uiMyOffset==EMPTY_OFFSET){
			TO_CONSOLE(L"TextPathChunk offset not filled!!!");		
			return;
		}

		//��������� � ����� ��� �������� ������
		unsigned int uiChildsOffsetPos=pTextPathChunk->m_uiMyOffset+sizeof(unsigned int)+sizeof(unsigned char);
		m_pNdxCashedFile->SeekPos(uiChildsOffsetPos, SEEK_SET);

		//������ �������� �� �������� �����
		unsigned int uiChildsOffset=EMPTY_OFFSET;
		m_pNdxCashedFile->Read((unsigned char*)&uiChildsOffset, sizeof(unsigned int));
		if(uiChildsOffset!=EMPTY_OFFSET){
			//��������� � ����� ��� �������� �������� �� �����
			m_pNdxCashedFile->SeekPos(uiChildsOffset, SEEK_SET);
					
			//������ ���������� �����
			unsigned int uiChildsNumber=0;
			m_pNdxCashedFile->Read((unsigned char*)&uiChildsNumber, sizeof(unsigned int));
			
			pChildsOffsetsCollection->assign(uiChildsNumber, EMPTY_OFFSET);
			//������ �������� �� �����
			m_pNdxCashedFile->Read((unsigned char*)(&(pChildsOffsetsCollection->front())), (uiChildsNumber*sizeof(unsigned int)));
		}

	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
	}
}

void CTextsPathsTreeStorage::GetParentOffset(STextPathChunk* pTextPathChunk, unsigned int* pParentOffset)
{
	if(ISNULL(pTextPathChunk)) return;
	if(ISNULL(pParentOffset)) return;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		if(pTextPathChunk->m_uiMyOffset==EMPTY_OFFSET){
			TO_CONSOLE(L"TextPathChunk offset not filled!!!");		
			return;
		}

		//��������� � ����� ��� �������� ������
		unsigned int uiParentOffset=pTextPathChunk->m_uiMyOffset+sizeof(unsigned char);
		m_pNdxCashedFile->SeekPos(uiParentOffset, SEEK_SET);
		//������ �������� �� ��������		
		m_pNdxCashedFile->Read((unsigned char*)pParentOffset, sizeof(unsigned int));

	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
	}
}

void CTextsPathsTreeStorage::DeleteTextPathChunk(STextPathChunk* pTextPathChunk, std::vector<unsigned int>* pDeletedTextsNumbers)
{
	if(ISNULL(pTextPathChunk)) return;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		if(pTextPathChunk->m_uiMyOffset==EMPTY_OFFSET){
			TO_CONSOLE(L"TextPathChunk offset not filled!!!");		
			return;
		}

		//������ ���� ����� � ������

		//�������� �������� �����
		vector<unsigned int> ChildsOffsets;
		STextPathChunk TextPathChunk(NULL, EMPTY_VALUE);
		GetChildsOffsets(pTextPathChunk, &ChildsOffsets);

		if(!ChildsOffsets.empty()){
			//���� ���� ���� � ����� ������� � ������� ����� �� ���������
			for(unsigned int i=0; i<ChildsOffsets.size(); i++){
				TextPathChunk.m_uiMyOffset=ChildsOffsets[i];
				//������� ����� ������
				DeleteTextPathChunk(&TextPathChunk, pDeletedTextsNumbers);
			}
		}else{
			//���� ����� ��� �������� ���� �� ����
			FillTextPathChunk(pTextPathChunk);
			if(pTextPathChunk->m_uiMyIndex!=EMPTY_VALUE && pDeletedTextsNumbers){
				//���� ��� ����� ������ ��� � ������ ��������� �������
				pDeletedTextsNumbers->push_back(pTextPathChunk->m_uiMyIndex);
			}
		}
		
		//� ����� ������ ������� ����
		//��������� � ����� ��� �������� ������
		m_pNdxCashedFile->SeekPos(pTextPathChunk->m_uiMyOffset, SEEK_SET);
		//������� ���� (���������� ���� ��������)
		bool bDeleted=true;
		m_pNdxCashedFile->Write((unsigned char*)&bDeleted, sizeof(unsigned char));

	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
	}
}

bool CTextsPathsTreeStorage::IsTextPathChunkDeleted(STextPathChunk* pTextPathChunk)
{
	if(ISNULL(pTextPathChunk)) return false;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		if(pTextPathChunk->m_uiMyOffset==EMPTY_OFFSET){
			TO_CONSOLE(L"TextPathChunk offset not filled!!!");		
			return false;
		}

		//��������� � ����� ��� �������� ������
		m_pNdxCashedFile->SeekPos(pTextPathChunk->m_uiMyOffset, SEEK_SET);
		//������ ���� ��������
		bool bDeleted=true;
		m_pNdxCashedFile->Read((unsigned char*)&bDeleted, sizeof(unsigned char));
		//���������� ���
		return bDeleted;
	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
		return false;
	}
}

bool CTextsPathsTreeStorage::IsTextPathExist(const wchar_t* pszTextPath)
{
	if(ISNULL(pszTextPath)) return false;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		//����� ���� �� �����, �� ������� ����� ����� ����� ��������� ����
		vector<wstring> ChunksCollection;
		HackTextPathOnChunks((wchar_t*)pszTextPath, &ChunksCollection);

		vector<unsigned int> ChildsOffsets;
		STextPathChunk RootTextPathChunk(NULL, 0);
		STextPathChunk CurrTextPathChunk(NULL, 0);
		RootTextPathChunk.m_uiMyOffset=0;
		bool bStopChecking=true;

		for(unsigned int uiCurrChunkIndex=0; uiCurrChunkIndex<ChunksCollection.size(); uiCurrChunkIndex++){
			//�������� �������� ����� ��� �������� ����
			GetChildsOffsets(&RootTextPathChunk, &ChildsOffsets);
			//������������� ���� ���������� ��������
			bStopChecking=true;
			for(vector<unsigned int>::iterator itCurrChildOffset=ChildsOffsets.begin(); itCurrChildOffset<ChildsOffsets.end(); itCurrChildOffset++){
				//������������� ��������
				CurrTextPathChunk.m_uiMyOffset=(*itCurrChildOffset);
				//������ ����� ���� �������
				FillTextPathChunk(&CurrTextPathChunk);
				//��������� ����� ����� �� ���������
				if(CurrTextPathChunk.m_pMyPathChunk && CStringService::StrEqual(ChunksCollection[uiCurrChunkIndex].c_str(), CurrTextPathChunk.m_pMyPathChunk)){
					//���� ���� ����� ��������� � ���������� �����
					//������ ������� ����� �������
					RootTextPathChunk.m_uiMyOffset=CurrTextPathChunk.m_uiMyOffset;
					//���������� ���� ���������� ��������
					bStopChecking=false;
					break;
				}
			}
			if(bStopChecking){
				//���� �������� ������ �������� �������
				return false;
			}
		}

		//���� ������ �� ���� ������
		return true;

	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
		return false;
	}
}

void CTextsPathsTreeStorage::DeleteTextByPath(const wchar_t* pszTextPath, std::vector<unsigned int>* pDeletedTextsNumbers)
{
	if(ISNULL(pszTextPath)) return;

	if(m_pNdxCashedFile->IsOpen() && m_pNdxCashedFile->GetDataUnitSize()){
		//����� ���� �� �����, �� ������� ����� ����� ����� ��������� ����
		vector<wstring> ChunksCollection;
		HackTextPathOnChunks((wchar_t*)pszTextPath, &ChunksCollection);

		vector<unsigned int> ChildsOffsets;
		STextPathChunk RootTextPathChunk(NULL, 0);
		STextPathChunk CurrTextPathChunk(NULL, 0);
		RootTextPathChunk.m_uiMyOffset=0;
		bool bStopChecking=true;

		for(unsigned int uiCurrChunkIndex=0; uiCurrChunkIndex<ChunksCollection.size(); uiCurrChunkIndex++){
			//�������� �������� ����� ��� �������� ����
			GetChildsOffsets(&RootTextPathChunk, &ChildsOffsets);
			//������������� ���� ���������� ��������
			bStopChecking=true;
			for(vector<unsigned int>::iterator itCurrChildOffset=ChildsOffsets.begin(); itCurrChildOffset<ChildsOffsets.end(); itCurrChildOffset++){
				//������������� ��������
				CurrTextPathChunk.m_uiMyOffset=(*itCurrChildOffset);
				//������ ����� ���� �������
				FillTextPathChunk(&CurrTextPathChunk);
				//��������� ����� ����� �� ���������
				if(CurrTextPathChunk.m_pMyPathChunk && CStringService::StrEqual(ChunksCollection[uiCurrChunkIndex].c_str(), CurrTextPathChunk.m_pMyPathChunk)){
					//���� ���� ����� ��������� � ���������� �����
					//������ ������� ����� �������
					RootTextPathChunk.m_uiMyOffset=CurrTextPathChunk.m_uiMyOffset;
					//���������� ���� ���������� ��������
					bStopChecking=false;
					break;
				}
			}

			if(bStopChecking){
				//���� �������� ������ �������� �������
				return;
			}
		}

		//���� ������ �� ���� ������, ������� ���
		DeleteTextPathChunk(&CurrTextPathChunk, pDeletedTextsNumbers);

	}else{
		TO_CONSOLE(L"TextsPathsTree not opened or empty!!!");
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}