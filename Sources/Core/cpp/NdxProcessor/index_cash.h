#pragma once
#include ".\index_container.h"
#include ".\pool_client.h"

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
	class CIndexStorage;
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

///��������� ������� � ����
class CIndexAttributes
{
public:
	CIndexAttributes(CContainersFactory* pContainersFactory)
		:m_uiIndexEntryPoint(EMPTY_OFFSET), m_uiFreqKoef(0), m_uiAppearedTextsNumber(0), m_uiFreqInCollection(0), m_BmTree(pContainersFactory){};
	virtual ~CIndexAttributes(void){};
	
	///���������� ��������� ��������� �������
	TCoordinateContainer* const GetCoordinatesContainer(void){return &m_BmTree;};

	///���������� ����� ����� ������� � ��������� �������
	unsigned int GetIndexEntryPoint(void){return m_uiIndexEntryPoint;};
	///������������� ����� ����� ������� � ��������� �������
	void SetIndexEntryPoint(unsigned int uiValue){m_uiIndexEntryPoint=uiValue;};

	///���������� ������� ��������� ������� � �������
	unsigned int GetAppearedTextsNumber(void){return m_uiAppearedTextsNumber;};
	///������������� ������� ��������� ������� � �������
	void SetAppearedTextsNumber(unsigned int uiValue){m_uiAppearedTextsNumber=uiValue;};
	///����������� ������� ������� � ������� ���������� ������
	void OneMoreText(void){m_uiAppearedTextsNumber++;};

	///���������� ������� ��������� ������� � �������
	unsigned int GetFreqInCollection(void){return m_uiFreqInCollection;};
	///������������� ������� ��������� ������� � �������
	void SetFreqInCollection(unsigned int uiValue){m_uiFreqInCollection=uiValue;};
	

	///���������� ������� ��������� �������
	unsigned int GetFreqKoef(void){return m_uiFreqKoef;};
	///������������� ������� ��������� �������
	void SetFreqKoef(unsigned int uiValue){m_uiFreqKoef=uiValue;};
	///����������� ������� ��������� �������
	void OneMoreIndex(void){m_uiFreqKoef++; m_uiFreqInCollection++;};

protected:
	///������ ���������
	TCoordinateContainer m_BmTree;
	///�������� �� ������ � ��������� ��������� (����� �����)
	unsigned int m_uiIndexEntryPoint;
	///��������� ����������, �� ������������ ������� ��� ��� ������ �� ����
	unsigned int m_uiFreqKoef;
	///���������� ���������� ���� ������ ������ (������� � ����������)
	unsigned int m_uiAppearedTextsNumber;
	///���������� ������� ������� �� ���� ��������� ����������
	unsigned int m_uiFreqInCollection;
};

//--------------------------------------------------------------------//

///��� �������� ������������� ��������� ����������
class CIndexCash : public CFactoryClient<CContainersFactory>
{
public:
	typedef map<unsigned int, CIndexAttributes*> TIndexCollection;

	CIndexCash(CContainersFactory* pContainersFactory, unsigned int uiCashMaxSize, unsigned int uiIndexFreqMinSize);
	virtual ~CIndexCash(void);
	
	///���������� ����
	virtual bool Update(void);
	///����� ���� �� ����
	void Flush(void);
	///���������� ���������� � ������� � ����
	virtual bool Add(unsigned int uiIndex, unsigned int* pCoordBuffer, unsigned int uiCoordBufferSize);
	///����������� ������� ����
	void  View();
	///����������� ���������� ��������� ��������
	void  ViewRemovedSize();
	///������� ���
	void Clear(void);

protected:
	///�������� ���������� �� ������� � �����
	CIndexCash::TIndexCollection::iterator MoveUpIndexInfo(unsigned int uiIndex);
	///���������� ���������� �� ������� �� ����
	void MoveDownIndexInfo(CIndexCash::TIndexCollection::iterator itIndex);

	///��� ��������
	TIndexCollection m_IndexCash;
	
	///������������ ������ ����, ��� ������� �� �� ���������
	unsigned int m_uiCashMaxSize;
	///����������� ������� ������� ��� ������� �� ������������� �� ����
	unsigned int m_uiIndexFreqMinSize;
	///��������� ��� ������������� ����������
	CIndexCash::TIndexCollection m_NullCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
