#pragma once

#include ".\index_stat_storage.h"
#include ".\tbl_containers.h"

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
class CIndexStorageTables : public CIndexStatisticStorage
{
public:
	CIndexStorageTables(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorageWithStatistic* pNdxStorage);
	virtual ~CIndexStorageTables(void){};
	
	///������ � ��������� ������� � ������������
	void AddTableIndexes(SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult);
	///��������� ������������������ ������ ��� ������
	void CompleteDocumentIndexing(void);
	///��������� ������� ������� �� ��������������
	void FillTablePositions(unsigned int uiDocumentIndex, 
		unsigned int uiTableIndex, Containers::STablePositions* pOutTablePositions, unsigned int uiHeadRowIndex = 0, unsigned int uiTailRowIndex = EMPTY_VALUE);
	///��������� ���� ������ �� ���������
	void FillTablesToTextBlock(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
			Containers::CInterval* pInterval, unsigned int uiGroupID);
	///��������� ��������� ��������� ������ ���������
	void FillTablesStructure(unsigned int uiTextIndex, std::wstring* pwsTablesStructure);

protected:
	typedef vector<Containers::STablePositions> TTablePositionsCollection;

	///���������� ����� ����� � �����
	unsigned int GetTextBlockCutCount(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock);
	///���������� ��������� ������� ������ � ������� ������
	unsigned int GetCellTailPosition(unsigned int uiCellIndex);

	///��������� ������� ����� ������ ������� ���������
	void FillTablePositions(unsigned int uiDocumentIndex, unsigned int uiTableIndex, unsigned int uiRowIndex);
	///������ � ��������� ������ � ������������
	void AddIndexationIndex(SS::Interface::Core::CommonContainers::IIndexationIndex* pIndexationIndex);

	///������� TRC-�������������
	Containers::CTrcID m_CurrentTrcID;

	///��������� �������� �� ������ �� �������� �������� ���������
	vector<Containers::STableInfo> m_TablesOffsets;
	///��������� ������� ����� ������� �������
	vector<unsigned int> m_CellPositions;

	//��� ���������� ���������� �� ����������
	///������ ���������� �������������� ���������
	unsigned int m_uiLastFilledDocumentIndex;
	unsigned int m_uiLastFilledTableIndex;
	unsigned int m_uiLastFilledRowIndex;

	///��������� ���������� �� ��������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* m_pTablesInfoStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}