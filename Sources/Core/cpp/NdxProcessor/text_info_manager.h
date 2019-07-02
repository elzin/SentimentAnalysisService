#pragma once

#include "..\ASDInterface\INdxSearchEngine.h"
#include ".\storage_manager.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{

//--------------------------------------------------------------------//

///��������� ����������� � ������������������ �������
class CTextInfoManager:
	public SS::Interface::Core::NdxSE::INdxSearchEngineTextsInfo, 
	public SS::Interface::Core::NdxSE::INdxSearchEngineTextsPathsInfo 
{
public:
	CTextInfoManager(void);
	virtual ~CTextInfoManager(void);

	//--------------ITextsInfo
	///���������� ���������� �� ������
	void GetTextInfo(unsigned int uiTextIndex, 
		SS::Interface::Core::CommonContainers::ITextFeature* pTextFeature);
	///���������� ���������� �� ������
	void GetTextInfo(unsigned int uiTextIndex, SS::Interface::Core::NdxSE::CNdxMetaField* pNdxMetaField);
	///���������� ���������� �� ������
	void GetTextInfo(unsigned int uiTextIndex, SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pNdxMetaFieldCollection);
	///���������� ���������� ������� � ����
	unsigned int GetTextsNumber(void);
	///���������� ���� ������ �� �������
	void GetTextPath(unsigned int uiTextIndex, std::wstring* pPath);
	///���������� ������ ������ �� �������
	unsigned int GetTextSize(unsigned int uiTextIndex);
	///������� ����� �� ����
	void DeleteText(unsigned int uiTextIndex);
	///��������� ������ �� ����� �� ����
	unsigned int IsTextDeleted(unsigned int uiTextIndex);
	///��������� ��������� ���������� �� ������� ������
	void GetHeadersStructure(unsigned int uiTextIndex, std::wstring* pwsHeaderStructure);
	///��������� ��������� ������ �� ������� ������
	void GetTablesStructure(unsigned int uiTextIndex, std::wstring* pwsTablesStructure) ;
	//--------------Eof-ITextsInfo

	//--------------ITextsPathsInfo
	//��������� � pTextPathChunk �� �������� ���� ���������� �� ����
	void FillTextPathChunk(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk);
	//��������� �� pTextPathChunk �������� ����� ���� pChildsOffsetsCollection
	void GetTextPathChunkChildsOffsets(
		SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk, 
		std::vector<unsigned int>* pChildsOffsetsCollection);
	///��������� �� pTextPathChunk �������� �������� ���� pParentOffset
	void GetTextPathChunkParentOffset(
		SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk, 
		unsigned int* pParentOffset);
	///������� ���� ������ � ������
	void DeleteTextPathChunk(SS::Interface::Core::NdxSE::STextPathChunk* pTextPathChunk);
	///��������� ���� �� ���� � ������ ����� �������
	unsigned int IsTextPathExist(const wchar_t* pwcszTextPath);
	///������� ����� �� ����
	void DeleteTextByPath(const wchar_t* pwcszTextPath);
	//--------------Eof-ITextsPathsInfo

	///�������������� �������� �������� ����������
	void Init(SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* pStorageManager);

protected:
	///�������� ���������� �������� ��������� ����
	SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* m_pStorageManager;

};

//--------------------------------------------------------------------//

}
}
}
}
}