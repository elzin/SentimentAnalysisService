#pragma once

#include ".\index_stat_storage.h"
#include ".\hdr_containers.h"

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

///��������� ���������
class CIndexStorageHeaders : public CIndexStatisticStorage
{
public:
	CIndexStorageHeaders(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorageWithStatistic* pNdxStorage);
	virtual ~CIndexStorageHeaders(void);

	///������ � ��������� ������� � ������������
	void AddIndexes(SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut);
	///������ � ��������� ������ � ������������
	void AddIndexationIndex(SS::Interface::Core::CommonContainers::IIndexationIndex* pIndexationIndex);
	
	///��������� ������������������ ������ ��� ������
	void CompleteDocumentIndexing(void);
	///��������� ������� ���������
	void FillHeaderPositions(unsigned int uiDocumentIndex, 
		Containers::CLevelHeaderID* pLevelHeaderID, Containers::SHeaderPositions* pOutHeaderPositions);
	///��������� ���� ������ �� ���������
	void FillHeadersToTextBlock(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
			Containers::CIntervalAndHeader* pInterval, unsigned int uiGroupID);
	///��������� ��������� ��������� ������
	Containers::CDocumentHeadersInfo* FillHeadersInfo(unsigned int uiDocumentIndex);

protected:
	///������������� �������� ���������
	Containers::CDocumentHeadersInfo m_DocumentHeadersInfo;
	
	//��� ���������� ���������� �� ����������
	///������ ���������� �������������� ���������
	unsigned int m_uiLastFilledDocumentIndex;

	///��������� ���������� �� ����������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* m_pHeadersInfoStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}