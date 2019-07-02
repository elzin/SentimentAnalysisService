#pragma once

#include "..\ASDInterface\INdxDataStorage.h"
#include "..\ASCInterface\ICommonContainers.h"
#include ".\iep_storage.h"
#include ".\texts_binary_storage.h"
#include ".\basis_storage.h"
#include ".\coordinate_counter.h"

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
	class CIndexCash;
	class CContainersFactory;
}
}
}
}
}

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
class CIndexStorage : public CBasisStorage
{
public:
	typedef vector<SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo const*> TCoordinateLevelInfo;

	CIndexStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* pNdxStorage);
	virtual ~CIndexStorage(void);

	///���������� ��� ���������� ���������
	const wchar_t* GetIndexStorageName(void){return m_pNdxStorage->GetDataUnitName();};
	///���������� ������� ����� ����� �������� � ������������ �������
	CIndexEntryPointTable* GetIndexEntryPointTable(void){return m_pIndexEntryPointTable;};
	///���������� ��������� ��������� ����������� ������
	CTextsBinaryStorage* GetTextsBinaryStorage(void){return m_pTextsBinaryStorage;};
	///���������� ��������� ��������� 
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* GetCoordinateStorage(void){return m_pCoordinateStorage;};

	///���������� ��������� �������� ������ ��������� �� ������
	TCoordinateLevelInfo* GetCoordinateLevelCollection(void){return &m_CoordinateLevelInfo;};
	///���������� ���������� �������
	unsigned int GetLevelStoragesNumber(void){return (unsigned int)m_CoordinateLevelInfo.size();};
	///���������� ����� ������ � ��������� �����������
	unsigned int GetSentencesControlLevelNumber(void){return m_uiSentencesControlLevelNumber;};
	///���������� ����� ������ � ��������� ������� ����
	unsigned int GetWordsControlLevelNumber(void){return m_uiWordsControlLevelNumber;};
	///���������� ������ ������� ����� �� ������ ������
	unsigned int GetBitMapSizeByLevel(unsigned char ucLevel);
	///���������� ������� ����������� ������� �������
	SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* GetContainersFactory(void){return m_pContainersFactory;};

	///������� � ����������
	void PrepareIndexing(void);
	///������ � ��������� ������ � ������������
	void AddIndex(SS::Interface::Core::CommonContainers::IIndexAndPosition* pIndexAndPosition);
	virtual void AddIndexationIndex(SS::Interface::Core::CommonContainers::IIndexationIndex* pIndexationIndex);
	///������ � ��������� ������� � ������������
	virtual void AddIndexes(SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut);
	///��������� ������������������ ������
	virtual void UpdateIndexedData(void);
	///��������� ������������������ ������ ��� ������
	virtual void CompleteDocumentIndexing(void);
	///���������� ��������� ������ � ���������
	virtual void CompleteIndexing(void);

protected:
	///������� ��� �������� ������
	virtual void CreateIndexCash(void);
	///���������� ��� �������� ������
	virtual SS::Core::NdxSE::NdxProcessor::Containers::CIndexCash*  GetIndexCash(void);

	///������� ����� ����� �������� � ������������ �������
	CIndexEntryPointTable* m_pIndexEntryPointTable;
	///��������� �������� ������� �������
	CTextsBinaryStorage* m_pTextsBinaryStorage;
	///��������� ��������� ��������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* m_pCoordinateStorage;
	///��������� ��������� �������� ������������ ��������
	TCoordinateLevelInfo m_CoordinateLevelInfo;

	///��� �������� ������
	SS::Core::NdxSE::NdxProcessor::Containers::CIndexCash* m_pIndexCash;
	///������� ����������� ������� �������
	SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* m_pContainersFactory;

	///����� ������ � ��������� �����������
	unsigned int m_uiSentencesControlLevelNumber;
	///����� ������ � ��������� ������� ����
	unsigned int m_uiWordsControlLevelNumber;
	
	///������� ���������
	SS::Core::NdxSE::NdxProcessor::Indexing::CCoordinateCounter m_CoordinateCounter;

	//��������� ����
	///������������ ������ ����
	unsigned int m_uiCashMaxSize;
	///����������� ������� ��� ������� ������ �������� � ����
	unsigned int m_uiCashIndexMinFreq;

	///���������� ��������� �������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage* m_pNdxStorage;
	
	///���� ������� ���� ��������� ��������
	bool m_bLogIndexCoordinates;
	///���-���� ��������� ��������
	FILE* m_pLogIndexCoordinatesFileStream;
};

//--------------------------------------------------------------------//

}
}
}
}
}