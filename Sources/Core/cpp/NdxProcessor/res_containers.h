#pragma once

#include ".\const.h"
#include ".\consoleclient.h"
#include ".\int_containers.h"
#include <functional>

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

///��������� ���������� ������
class CFindResult : public CConsoleClient
{
public:
	///��������� ��������� �������� �� ����������, � ������� ��� ���� �������
	typedef map<wstring, TIntervalCollection*> TIntervalByStorageCollection;
	///��������� ��������������� ����������
	typedef vector<unsigned int> THIDCollection;
	///��������� ��������� ��������������� ���������� �� ��������
	typedef map<unsigned int, THIDCollection*> TBlockHIDCollection;
	
	CFindResult(unsigned int uiTextIndex, unsigned int uiRelevance);
	virtual ~CFindResult(void);
	
	///���������� ������������� ������ ����������
	unsigned int GetTextIndex(void){return m_uiTextIndex;};
	///���������� �������� ������������� ����������
	unsigned int GetRelevance(void){return m_uiRelevance;};
	///������������� �������� ������������� ����������
	void SetRelevance(unsigned int uiValue){m_uiRelevance=uiValue;};
	///��������� ��������� ��������� � ���������
	void MoveIntervalCollection(const wchar_t* wszIndexStorageName, TIntervalCollection* pIntervalCollection);
	///��������� ��������� ��������� �������� �� ����������
	TIntervalByStorageCollection* GetIntervalCollection(void){return m_pIntervalByStorageCollection;};
	///��������� ��������� ��������������� ���������� �� �������
	THIDCollection* GetHIDCollection(unsigned int uiIndex);
	///������������� ��������� ��������������� ���������� � ���������
	void MoveBlockHIDCollection(TBlockHIDCollection* pBlockHIDCollection);

	///������������ � ������
	void ToString(wstring& wszValue);
	///���������� ���������� ������� ������
	void View(void);

protected:
	///������� ��������� ��������� �������� �� ����������, � ������� ��� ���� �������
	void DeleteIntervalByStorageCollection(void);
	void DeleteBlockHIDCollection(void);

	///������������� ������ ����������
	const unsigned int m_uiTextIndex;
	///�������� ������������� ����������
	unsigned int m_uiRelevance;
	///��������� ��������� �������� �� ����������, � ������� ��� ���� �������
	TIntervalByStorageCollection* m_pIntervalByStorageCollection;
	///��������� ��������������� ���������� �� ������, ������ �� ������� �����
	TBlockHIDCollection* m_pBlockHIDCollection;
};


//--------------------------------------------------------------------//

///���������-��������� ����������� ���������� ������ ������������� �� �������������
class CFindResultsByRelevanceCollection : public CConsoleClient
{
public:
	///��������� ����������� ���������� ������ ������������� �� �������������
	typedef list<CFindResult*> TFindResultsList;
	typedef map<unsigned int, TFindResultsList*, greater<int> > TFindResultsByRelevanceCollection;

	CFindResultsByRelevanceCollection(void);
	virtual ~CFindResultsByRelevanceCollection(void);

	///��������� ��������� � ���������
	void AddFindResult(CFindResult* pFindResult);
	///������� ��������� �� ���������
	void RemoveFindResult(CFindResult* pFindResult);
	///������� ���������
	void Clear(void);

	//����� �� ����������� � ������� �������� �������������
	///���������������� �� ������ ����������
	bool MoveFirstFindResult(void);
	///���������������� �� ��������� ����������
	bool MoveNextFindResult(void);
	///���������� ������� ���������
	CFindResult* GetCurrentFindResult(void);

protected:	
	///��������� ����������� ���������� ������ ������������� �� �������������
	TFindResultsByRelevanceCollection m_FindResultsByRelevanceCollection;
	TFindResultsByRelevanceCollection::iterator m_itCurrFindResultsList;
	TFindResultsList::iterator m_itCurrFindResult;
	///��������� ��� ������������� ����������
	TFindResultsByRelevanceCollection m_NullCollection;
	TFindResultsList m_NullCollectionList;
};

//--------------------------------------------------------------------//

///���������-��������� ����������� ���������� ������
class CFindResultCollection : public CConsoleClient
{
public:
	///��������� ����������� ���������� ������
	typedef map<unsigned int, CFindResult*> TFindResultsCollection;
	
	///������ ���������� ����������� � ���������
	enum EAddingMode
	{
		///�����������
		eamUndefined,
		///���������� ������ ���� ��������� ��� ����
		eamIfExist,
		///���������� ������
		eamAlways,
	};

	CFindResultCollection(void);
	virtual ~CFindResultCollection(void);
	
	///��������� ������ ���������� ����������� ������ � ����������� ������
	void StartFindResultAdding(EAddingMode AddingMode);
	///��������� ������ ���������� ����������� ������ � ����������� ������
	void StopFindResultAdding(void);
	///��������� ��������� ��������� � ���������
	CFindResult* AddFindResult(unsigned int uiTextIndex, unsigned int uiRelevance);
	///���������� ��������� �� ������ ������
	CFindResult* GetFindResult(unsigned int uiTextIndex);
	///��������� ��������� ��������� �������� �� ����������
	TFindResultsCollection* GetFindResultsCollection(void){return &m_FindResultsCollection;};
	///������� ��������� ����������� ���������� ������
	void Clear(void);
	///���������� ������ �� ����������
	void ResetAddingSession(void){m_uiCurrentAddingSession=0;};
	///��������� ���������� ����������� ���������� ������
	unsigned int Count(void){return (unsigned int)m_FindResultsCollection.size();};
	///��������� �� �������
	bool IsEmpty(void){return m_FindResultsCollection.empty();};
	///���������-��������� ����������� ���������� ������ ������������� �� �������������
	CFindResultsByRelevanceCollection* GetFindResultsByRelevanceCollection(void){return &m_FindResultsByRelevanceCollection;};

	///������������ � ������
	void ToString(wstring& wszValue);
	///���������� ���������� ������� ������
	void View(void);

protected:
	///������� ��������� ����������� ���������� ������
	void Clear(TFindResultsCollection* pFindResultsCollection);
	///������������� ������� ����� ���������� ����������� � ���������
	void SetAddingMode(EAddingMode AddingMode){m_CurrentAddingMode=AddingMode;};

	///��������� ����������� ���������� ������
	TFindResultsCollection m_FindResultsCollection;
	///��������������� ��������� ����������� ���������� ������
	TFindResultsCollection m_TempFindResultsCollection;
	///������� ����� ���������� ����������� � ���������
	EAddingMode m_CurrentAddingMode;
	///������� ������
	unsigned int m_uiCurrentAddingSession;
	///���������-��������� ����������� ���������� ������ ������������� �� �������������
	CFindResultsByRelevanceCollection m_FindResultsByRelevanceCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
