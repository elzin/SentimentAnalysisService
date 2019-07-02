#pragma once

#include ".\index_cash.h"

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
	class CIndexStatisticStorage;
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
namespace Containers
{

//--------------------------------------------------------------------//

class CIndexStatisticCash : public CIndexCash
{
public:
	CIndexStatisticCash(CContainersFactory* pContainersFactory, unsigned int uiCashMaxSize, unsigned int uiIndexFreqMinSize);
	virtual ~CIndexStatisticCash(void);

	///��������� "������" ������
	void AddFrequentIndex(unsigned int uiIndex, unsigned int uiFreqIncreaseKoef);
	///���������� ���������� � ������� � ����
	bool Add(unsigned int uiIndex, unsigned int* pCoordBuffer, unsigned int uiCoordBufferSize);
	///���������� ����������� �������� ����������� � ���
	unsigned int GetAddedIndexesNumber(void){return m_uiAddedIndexesNumber;};
	///��������� ������������������ ������ ��� ������
	void CompleteDocumentIndexing(unsigned int uiTextIndex);
	
protected:
	///���������� ����������� �������� ����������� � ���
	void ResetAddedIndexesNumber(void){m_uiAddedIndexesNumber=0;};

	typedef map<unsigned int, unsigned int > TFrequentIndexCollection;
	///��������� "������" ��������
	TFrequentIndexCollection m_FrequentIndexCollection;
	///������� �������� ����������� � ���
	unsigned int m_uiAddedIndexesNumber;
};

//--------------------------------------------------------------------//

}
}
}
}
}

