#pragma once

#include ".\node_containers.h"
#include "../ASDInterface/INdxDataStorage.h"
#include "../ASDInterface/TNdxSearchEngineTypes.h"
#include ".\const.h"
#include ".\basis_storage.h"
#include ".\texts_field_storage.h"

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

//--------------------------------------------------------------------//

///������ �� ��������
class CStringService
{
public:
	///���������� ������
	inline static bool StrEqual(const wchar_t* sz1, const wchar_t* sz2);
};

//--------------------------------------------------------------------//

///���� ������ ����� �������
class CTextPathNode 
	: public SS::Core::NdxSE::NdxProcessor::Containers::CVecTreeNode<SS::Interface::Core::NdxSE::STextPathChunk*>
{
public:
	CTextPathNode(const wchar_t* pMyPathChunk, unsigned int uiMyIndex = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE);
	virtual ~CTextPathNode(void);

	///��������� ������� ������� ����
	CTextPathNode* AddChild(const wchar_t* pMyPathChunk, unsigned int uiMyIndex = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE);
	///������ ���� �� ���� ������
	void MoveDown(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxFile);

protected:
	///��������� ������� ������� ����
	SS::Core::NdxSE::NdxProcessor::Containers::CVecTreeNode<SS::Interface::Core::NdxSE::STextPathChunk*>* 
		AddChild(SS::Core::NdxSE::NdxProcessor::Containers::CVecTreeNode<SS::Interface::Core::NdxSE::STextPathChunk*>* pChildNode){TO_CONSOLE(L"Proxed"); return NULL;};
};

//--------------------------------------------------------------------//

//��������� �������� �����:
//	��� ����:
//		���� �������� - 1����
//		�������� �� �������� - 4�����
//		�������� �� �������� ����� - 4�����
//		������������� ���� - 4�����
//		������ ����� ���� ������  - 4�����
//		������ ���� ������ - ������ ����� ���� ������
//	�������� �����:
//		���������� ����� - 4�����
//		�������� ����� - 4�����*���������� ����� 

///������ ����� �������
class CTextsPathsTreeStorage : public CBasisStorage
{
public:
	CTextsPathsTreeStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxCashedFile);
	virtual ~CTextsPathsTreeStorage(void);

	///������������ ���������� ��������� ����������
	void PrepareIndexing(void){};
	///��������� �������� ��������� �� ��������� ����������
	void CompleteIndexing(void){};
	///��������� �������� ��������� �� ��������� ���������� ���������
	void CompleteDocumentIndexing(void){};
	
	///������� ������ ����� �� ���������� �� �������
	void BuildTree(CTextsFieldsStorage* pTextsInfo);
	///��������� ���� � ������
	void AddTextPath(unsigned int uiTextIndex, wchar_t* pszTextPath);
	///����� ���� ������ �� �����
	void HackTextPathOnChunks(wchar_t* pszTextPath, vector<wstring>* pChunksCollection);
	///������ ������ �� ���� ������
	void MoveDown(void);
	///���������� ���������� �� �������� ����
	void FillTextPathChunk(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk);
	///���������� �������� ����� ����
	void GetChildsOffsets(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk, vector<unsigned int>* pChildsOffsetsCollection);
	///���������� �������� �������� ����
	void GetParentOffset(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk, unsigned int* pParentOffset);
	///������� ���� ������ � ������
	void DeleteTextPathChunk(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk, std::vector<unsigned int>* pDeletedTextsNumbers);
	///��������� ������ �� ������ ����
	bool IsTextPathChunkDeleted(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk);
	///��������� ���� �� ���� � ������ ����� �������
	bool IsTextPathExist(const wchar_t* pszTextPath);
	///������� ����� �� ����
	void DeleteTextByPath(const wchar_t* pszTextPath, std::vector<unsigned int>* pDeletedTextsNumbers);
		
protected:
	///������� ���� ������
	CTextPathNode m_RootPathNode;
	///���������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* m_pNdxCashedFile;
};

//--------------------------------------------------------------------//

}
}
}
}
}