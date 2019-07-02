#pragma once

#include ".\storage_manager.h"
#include ".\indexing_manager.h"
#include ".\extracting_manager.h"
#include ".\text_info_manager.h"
#include "../ASCInterface/ITextsInfoExtracting.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{

//--------------------------------------------------------------------//

///�������� ������ SS ������������ ���������� � �����
class CNdxSearchEngine : public SS::Interface::Core::NdxSE::INdxSearchEngine,
	public SS::Interface::Core::TextsInfo::ITextsInfoExtracting,
	public Indexing::CIndexingManager,
	public Extracting::CExtractingManager, 
	public Extracting::CTextInfoManager
{
public:
	CNdxSearchEngine(void);
	virtual ~CNdxSearchEngine(void);

	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������
	ULONG Release(void);
	///������������� ��������� �� ���� ��������
	void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
	//-----------Eof-IBase

	//-----------INdxSearchEngine
	///���������� ��������� ��� ���������� ������
	SS::Interface::Core::NdxSE::INdxSearchEngineFind* INdxSearchEngineFind(void){return (SS::Interface::Core::NdxSE::INdxSearchEngineFind*)this;};
	///���������� ��������� ��� ���������� ����������
	SS::Interface::Core::NdxSE::INdxSearchEngineIndexation* INdxSearchEngineIndexation(void){return (SS::Interface::Core::NdxSE::INdxSearchEngineIndexation*)this;};
	///���������� ��������� ��� ��������� ���������� �� ������������������ �������
	SS::Interface::Core::NdxSE::INdxSearchEngineTextsInfo* INdxSearchEngineTextsInfo(void){return (SS::Interface::Core::NdxSE::INdxSearchEngineTextsInfo*)this;};
	///���������� ��������� ��� ��������� ���������� �� ����� ������������������ �������
	SS::Interface::Core::NdxSE::INdxSearchEngineTextsPathsInfo* INdxSearchEngineTextsPathsInfo(void){return (SS::Interface::Core::NdxSE::INdxSearchEngineTextsPathsInfo*)this;};
	//-----------Eof-INdxSearchEngine

	//-----------ITextsInfoExtracting
	///��������� ITextFeature �� ������ ������
	void GetTextInfo(unsigned int uiTextIndex, 
		SS::Interface::Core::CommonContainers::ITextFeature* pTextFeature);
	///��������� �������� ���������� ������ ��� ������� ���������� ��������� �� ������ ������ � ��������� ��� � ITextBlock
	void FillTextContent(wstring* pwsIndexStorageName, 
			unsigned int uiHeadPosition,
			unsigned int uiTailPosition,
			SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock);
	//-----------Eof-ITextsInfoExtracting

protected:
	///�������� ���������� �������� ��������� ����
	Storages::CStorageManager* m_pStorageManager;
};

//--------------------------------------------------------------------//

}
}
}
}