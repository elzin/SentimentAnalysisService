#pragma once

#include ".\console.h"
#include ".\const.h"

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

class CIndexInTextInfo
{
public:
    typedef set<unsigned int> TPositionsCollection;

	CIndexInTextInfo(void)
		:m_uiTextIndex(EMPTY_VALUE), m_pPositionsCollection(NULL){};
	~CIndexInTextInfo(void){if(m_pPositionsCollection){ delete m_pPositionsCollection; m_pPositionsCollection=NULL;}};
	
	///���������� ������ ������
	unsigned int GetTextIndex(void){return m_uiTextIndex;};
	///������������� ������ ������
	void SetTextIndex(unsigned int uiTextIndex){m_uiTextIndex=uiTextIndex;};

	///��������� ������� ������
	void AddPosition(unsigned int uiPosition)
	{
		if(!m_pPositionsCollection){
			m_pPositionsCollection=new vector<unsigned int>();
		}
		m_pPositionsCollection->push_back(uiPosition);
	};
	
	///������������ ������� � ������ ���������
	void ConvertPosition(TPositionsCollection* pPositionsCollection)
	{
		if(!pPositionsCollection) return;

		for(unsigned int i=0; i<m_pPositionsCollection->size(); i++){
			pPositionsCollection->insert(m_pPositionsCollection->at(i));
		}
	}

protected:
	///������ ������
	unsigned int m_uiTextIndex;
	///��������� ������� � ������
	vector<unsigned int>* m_pPositionsCollection;
};

//--------------------------------------------------------------------//

///��������� �������������� �������� � ���������
class CLoggedIndexContainer
{
public:
    typedef vector<CIndexInTextInfo*> TIndexInTextInfoCollection;
    typedef map<unsigned int, TIndexInTextInfoCollection*> TLoggedIndexesCollection;
	typedef vector<CIndexInTextInfo::TPositionsCollection*> TTextCollection;

	CLoggedIndexContainer(void);
	~CLoggedIndexContainer(void);
	
	///�������������� ��������� �� ���-�����
	void Init(wstring* pwsLogFilePath);
	
	///��������� � ������� �������
	bool MoveFirstIndex(void);
	///��������� � ���������� �������
	bool MoveNextIndex(void);
	///���������� ������� ������ 
	unsigned int GetCurrentIndex(void){return (m_itCurrentIndex==m_NullCollection.end())?SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE:m_itCurrentIndex->first;};
	///��������� ���������� �������� �������
	void CurrentIndexCheckCoordinates(unsigned int uiTextIndex, unsigned int uiPosition);

	///������� ������� ����� �������
	void SetCurrBasisTextsNumber(unsigned int uiCurrBasisTextsNumber){m_uiCurrBasisTextsNumber=uiCurrBasisTextsNumber;};

protected:
	///��������� ���� �� �������
	void AddIndexInfo(const wchar_t* pwszIndexInfo);
	///��������� ���� �� ������ ���������� ��� ��������
	void FillIndexInfoForChecking(TLoggedIndexesCollection::iterator itCurrentIndex);
	///������ � ��� ���������� �������� �������
	void LogCheckResults(void);
	///������� ��� ���������
	void Clear(void);

	///��������� �������� � ������������
	TLoggedIndexesCollection m_LoggedIndexesCollection;
	///������� ������
	TLoggedIndexesCollection::iterator m_itCurrentIndex;
	///��������� ��� ������������� ����������
	TLoggedIndexesCollection m_NullCollection;

	///��������� ������� � ��������� �� ��������
	TTextCollection m_CheckingTextCollection;
	///��������� ������� ������� ��� � ����
	vector<unsigned int> m_LostPositions;
	///��������� ������� ������� ���� � ����, �� �� �� ���� ��� ����������
	vector<unsigned int> m_NotCorrectPositions;

	///���-���� ����������� ��������
	FILE* m_pCheckResultLog;

	///������� ������� ����� �������
	unsigned int m_uiCurrBasisTextsNumber;

};

//--------------------------------------------------------------------//

}
}
}
}
}