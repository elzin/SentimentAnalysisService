#pragma once

#include ".\storage_manager.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASDInterface\INdxSearchEngine.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Indexing
{

//--------------------------------------------------------------------//

///���������� ��������� ����������
class CIndexingManager : public SS::Interface::Core::NdxSE::INdxSearchEngineIndexation
{
public:
	CIndexingManager(void);
	virtual ~CIndexingManager(void);

	///�������������� �������� �������� ����������
	void Init(SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* pStorageManager);

	///������ ������ ���������� ��������� ����������
	HRESULT StartIndexationSession(void);
	///������� ������ ���������� ��������� ����������
	HRESULT EndIndexationSession(void);
	///������ �������� ���������� ���������
	HRESULT StartDocumentIndexation(
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult);
	///���������� ���������� ����� ���������
	HRESULT IndexateDocumentChunk(
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult);

	///���������� ��������������� ��������� ���������� !!! ���������� ���� ��� ��� ���������
	HRESULT IndexateTextFeature(
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult);

	///������� �������� ���������� ���������
	HRESULT EndDocumentIndexation(
		SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pNdxMetaFieldCollection,
		SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult);

protected:
	///�������� ���������� �������� ��������� ����
	SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* m_pStorageManager;
	///��� ��������� �������� �� ������ ����������
	map<wstring, Storages::CIndexStorage*> m_IndexStorageCollection;

	///���� ��������� ���������� �� ������, ���������
	bool m_bTextFeatureAdded;
};

//--------------------------------------------------------------------//

}
}
}
}
}