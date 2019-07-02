#pragma once

#include ".\index_storage.h"
#include ".\norm_storage.h"
#include ".\freq_storage.h"
#include ".\index_stat_cash.h"


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

///��������� ��������� � ���������� �������� ����������
class CIndexStatisticStorage : public CIndexStorage 
{
public:
	typedef map<unsigned int,unsigned int> TFrequencyCollection;
	typedef map<unsigned int, float> TIndexFreqCollection;

	CIndexStatisticStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorageWithStatistic* pNdxStorage);
	virtual ~CIndexStatisticStorage(void);

	///������ � ��������� ������� � ������������
	void AddIndexes(SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut);

	///���������� ��������� ������� ��������� ������� � ��������
	CIndexFrequencyStorage* GetIndexFrequencyStorage(void){return m_pIndexFrequencyStorage;};
	///���������� ��������� ���� ����������
	CDocNormStorage* GetDocNormStorage(void){return m_pDocNormStorage;};
	///��������� ������������������ ������ ��� ������
	void CompleteDocumentIndexing(void);

protected:
	///������� ��� �������� ������
	void CreateIndexCash(void);
	///���������� ��� �������� ������
	SS::Core::NdxSE::NdxProcessor::Containers::CIndexStatisticCash*  GetIndexCash(void);

	///������ ����������� ������������� ������������������ ���������� 
	void ComputeDocumentsNorm(void);
	///��������� ��������� �������������� ����������� �������������
	bool PreComputeDocumentNorm(unsigned int uiNumberOfDocuments,  TFrequencyCollection& IndexesDocumentFreqCollection);
	///��������� ����������� ����������� ��� ������� ������, �� ������� �������� ��� ��������
	unsigned int ComputeDocumentNorm(TFrequencyCollection& IndexesFreqInTextCollection);
	
	///��������� ������� ��������� ������� � ��������
	CIndexFrequencyStorage* m_pIndexFrequencyStorage;
	///��������� ���� ����������
	CDocNormStorage* m_pDocNormStorage;
	///�������� �������� ����������������� ������ ���������� �� ������
	TIndexFreqCollection m_IndexInverseDocFreqCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}