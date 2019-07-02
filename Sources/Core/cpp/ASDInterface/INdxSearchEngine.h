#pragma once
#include "..\ASCInterface\IInterface.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASCInterface\TCoommonTypes.h"
#include "..\ASCInterface\ITextsInfoExtracting.h"
#include "..\ASDInterface\INdxQuery.h"
#include ".\TNdxSearchEngineTypes.h"
#include "IISContainer.h"
#include <vector>

//--------------------------------------------------------------------//

// {AA99ECEA-3DB7-4e86-AB00-E9BB9849E973}
static const GUID IID_NdxSearchEngine = 
{ 0xaa99ecea, 0x3db7, 0x4e86, { 0xab, 0x0, 0xe9, 0xbb, 0x98, 0x49, 0xe9, 0x73 } };

//--------------------------------------------------------------------//

namespace SS
{
namespace Interface
{
namespace Core
{
namespace NdxSE
{

//--------------------------------------------------------------------//

///��������� ��� ������ � ��������� �������
class INdxSearchEngineFind
{
public:
	//----------------------------------------------
	//�����
	//----------------------------------------------
	///������ ������ ������, �������� ��������� ����������� ������ 
	//��� �� ��������� ��������� ������ ����� ������ ����������
	virtual HRESULT StartFindSession(
		///��������� ����������� ������ 
		SS::Interface::Core::IISContainerUM* pISContainer) = 0;

	///������� ������ ������, ���������� � ��������� �������� � StartFindSession ���������� ������ 
	virtual HRESULT EndFindSession(void) = 0;

	///	����� � ��������� ��������� �� ����������������� �������
	virtual HRESULT Find(
		///��� ���������� ���������, ��� ��������� �����
		const wchar_t* wszIndexStorageName,
		///��������� ����������������� ���������� �������
		SS::Interface::Core::NdxSE::IParametrizedQuery*	pPrmQueryResult,
		///����� ��������� ������
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
		///��������� ������ ���������� ������
		CNdxSearchSettings* pSearchSettings) = 0;

	///����� � ������� ���� ����� �� �������
	virtual HRESULT Find(
		///��������� ����-����� ��������� (������)
		TNdxMetaFieldCollection* pNdxMetaFieldCollection,
		///����� ��������� ������
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
		///��������� ������ ���������� ������
		CNdxSearchSettings* pSearchSettings) = 0;

	///������� ������ ������, ���������� � ��������� �������� � StartFindSession ���������� ������ 
	///��� ������������ ����������� ������ ������ �� ����� ������� ��������
	virtual HRESULT EndFindByFieldSession(void) = 0;

	//----------------------------------------------

};

//--------------------------------------------------------------------//

///��������� ��� ������ � ��������� �������
class INdxSearchEngineIndexation
{
public:
	//----------------------------------------------
	//����������
	//----------------------------------------------
	///������ ������ ���������� ��������� ����������
	virtual HRESULT StartIndexationSession(void) = 0;

	///������� ������ ���������� ��������� ����������
	virtual HRESULT EndIndexationSession(void) = 0;

	///������ �������� ���������� ���������
	virtual HRESULT StartDocumentIndexation(
		///��������� �������� ��� ����������
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult) = 0;

	///���������� ���������� ����� ���������
	virtual HRESULT IndexateDocumentChunk(
		///��������� �������� ��� ����������
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult) = 0;

	///���������� ��������������� ��������� ���������� !!! ���������� ���� ��� ��� ���������
	virtual HRESULT IndexateTextFeature(
		///��������� �������� ��� ����������
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult) = 0;

	///������� �������� ���������� ���������
	virtual HRESULT EndDocumentIndexation(
		///��������� ����-����� ���������
		TNdxMetaFieldCollection* pNdxMetaFieldCollection,
		///��������� �������� ��� ����������
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult) = 0;
	//----------------------------------------------
};

//--------------------------------------------------------------------//

///������ � ����������� �� �������
class INdxSearchEngineTextsInfo
{
public:				
	///���������� ���������� ������� � ����
	virtual unsigned int GetTextsNumber(void) = 0;
	///���������� ���� ������ �� �������
	virtual void GetTextPath(unsigned int uiTextIndex, std::wstring* pPath) = 0;
	///���������� ���������� �� ������
	virtual void GetTextInfo(unsigned int uiTextIndex, SS::Interface::Core::CommonContainers::ITextFeature* pTextFeature) = 0;
	///���������� ���������� �� ������
	virtual void GetTextInfo(
		///������ ������
		unsigned int uiTextIndex, 
		///����������� ����, � ���� ������ ���� ��������� �������� � ��� ����
		CNdxMetaField* pNdxMetaField) = 0;
	///���������� ���������� �� ������
	virtual void GetTextInfo(
		///������ ������
		unsigned int uiTextIndex, 
		///��������� ����������� �����, � ����� ������ ���� ��������� �������� � ���� ����
		TNdxMetaFieldCollection* pNdxMetaFieldCollection) = 0;
	///���������� ������ ������ �� �������
	virtual unsigned int GetTextSize(unsigned int uiTextIndex) = 0;
	///������� ����� �� ����
	virtual void DeleteText(unsigned int uiTextIndex) = 0;
	///��������� ������ �� ����� �� ����
	virtual unsigned int IsTextDeleted(unsigned int uiTextIndex) = 0;
	///��������� ��������� ���������� �� ������� ������
	virtual void GetHeadersStructure(unsigned int uiTextIndex, std::wstring* pwsHeaderStructure) = 0;
	///��������� ��������� ������ �� ������� ������
	virtual void GetTablesStructure(unsigned int uiTextIndex, std::wstring* pwsTablesStructure) = 0;
};

//--------------------------------------------------------------------//

//������ � ������ �������
class INdxSearchEngineTextsPathsInfo
{
public:				
	//��������� � pTextPathChunk �� �������� ���� ���������� �� ����
	virtual void FillTextPathChunk(
		///���� ������ ����
		STextPathChunk* pTextPathChunk) = 0;
	//��������� �� pTextPathChunk �������� ����� ���� pChildsOffsetsCollection
	virtual void GetTextPathChunkChildsOffsets(
		STextPathChunk* pTextPathChunk, 
		std::vector<unsigned int>* pChildsOffsetsCollection) = 0;
	///��������� �� pTextPathChunk �������� �������� ���� pParentOffset
	virtual void GetTextPathChunkParentOffset(
		STextPathChunk* pTextPathChunk, 
		unsigned int* pParentOffset) = 0;
	///������� ���� ������ � ������
	virtual void DeleteTextPathChunk(
		///���� ������ ����
		STextPathChunk* pTextPathChunk) = 0;
	///��������� ���� �� ���� � ������ ����� �������
	virtual unsigned int IsTextPathExist(const wchar_t* pwcszTextPath) = 0;
	///������� ����� �� ����
	virtual void DeleteTextByPath(const wchar_t* pwcszTextPath) = 0;
};

//--------------------------------------------------------------------//

//������ � ������ �������
class INdxSearchEngine : public virtual SS::Interface::IBase
{
public:				
	///���������� ��������� ��� ���������� ������
	virtual INdxSearchEngineFind* INdxSearchEngineFind(void) = 0;
	///���������� ��������� ��� ���������� ����������
	virtual INdxSearchEngineIndexation* INdxSearchEngineIndexation(void) = 0;
	///���������� ��������� ��� ��������� ���������� �� ������������������ �������
	virtual INdxSearchEngineTextsInfo* INdxSearchEngineTextsInfo(void) = 0;
	///���������� ��������� ��� ��������� ���������� �� ����� ������������������ �������
	virtual INdxSearchEngineTextsPathsInfo* INdxSearchEngineTextsPathsInfo(void) = 0;
};

}
}
}
}