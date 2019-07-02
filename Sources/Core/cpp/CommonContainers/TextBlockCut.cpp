//TextBlockCut.cpp
#include "StdAfx.h"
#include "textblockcut.h"
#include "IndexAndPosition.h"

namespace SS
{
namespace Core
{
namespace CommonContainers
{
	
//������������
CTextBlockCut::CTextBlockCut(IBlackBoxTextStorage* pBlackBoxTextStorage, TLinguisticProcessorMode*	pLinguisticProcessorMode) 
	: 
	m_wszTextCut(NULL), m_wszPluginName(NULL), 
	m_wsIndexTypeName(L""), m_pBlackBoxTextStorage(pBlackBoxTextStorage),
	m_pLinguisticProcessorMode(pLinguisticProcessorMode),
	m_uiRelevance(0),
	m_pContainersFactory(NULL)
{
	SS_TRY
	{
		m_wszTextCut = new wchar_t[1];
		m_wszPluginName = new wchar_t[1];
		wcscpy(m_wszTextCut, L"");
		wcscpy(m_wszPluginName, L"");
		m_oBlockCutData.Level = 0;
		m_oBlockCutData.Number = 0;
		m_oBlockCutData.TextCutType = 0;
		m_listIter = m_list_pIndexAndPosition.end();
	}
	SS_CATCH(L"")
}

///���������� "�����" ���� ������� ������ ��������� �����
void CTextBlockCut::SetIndexTypeName(const wchar_t* wszName)
{
	SS_TRY
	{
		m_wsIndexTypeName = wszName;
	}
	SS_CATCH(L"")
}
///��������� "�����" ���� ������� ������ ��������� �����
const wchar_t* CTextBlockCut::GetIndexTypeName()
{
	SS_TRY
	{
		return m_wsIndexTypeName.c_str();
	}
	SS_CATCH(L"")
}

CTextBlockCut::~CTextBlockCut()
{
	Clear();
	if (m_wszTextCut)
	{
		delete [] m_wszTextCut;
	}
	if (m_wszPluginName) 
	{
		delete [] m_wszPluginName;
	}
}

//������ ������
void CTextBlockCut::Clear()										// ������� ������� (������ ��� �������)
{
	SS_TRY
		for (m_listIter = m_list_pIndexAndPosition.begin(); m_listIter != m_list_pIndexAndPosition.end(); m_listIter++)
		{
			if ((*m_listIter)) 
			{
				delete (*m_listIter);
			}						
		}	

		m_list_pIndexAndPosition.clear();
		
	SS_CATCH(L"")
}

IIndexAndPosition* CTextBlockCut::AddIndexAndPosition()			// ���������� ������� � ��������� (������� � ���� � ������ ���������)
{
	SS_TRY
		IIndexAndPosition *pIndexAndPosition;
		pIndexAndPosition = m_pContainersFactory->CreateIndexAndPosition(m_pBlackBoxTextStorage, m_pLinguisticProcessorMode);
		m_list_pIndexAndPosition.push_back(pIndexAndPosition);
		return pIndexAndPosition;
	SS_CATCH(L"")
}

IIndexAndPosition* CTextBlockCut::GetFirstIndexAndPosition()	// ��������� ������� ������� ��������� (0 - ���� ���)
{
	SS_TRY
		if (m_list_pIndexAndPosition.empty())
		{
			return NULL;
		}
		m_listIter = m_list_pIndexAndPosition.begin();
		return (*m_listIter);
	SS_CATCH(L"")
}

IIndexAndPosition* CTextBlockCut::GetNextIndexAndPosition()		// ��������� ���������� ������� ��������� (�� �������� ������� 
{																// ��������� ������� �������) (0 - ���� �����������)
	SS_TRY
		if (m_listIter == m_list_pIndexAndPosition.end())
		{
			//SS_THROW(L" �� ������ ����� GetFirstIndexAndPosition() ")
			SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L" �� ������ ����� GetFirstIndexAndPosition() ");
			return NULL;
		}
		m_listIter++;
		if (m_listIter == m_list_pIndexAndPosition.end())
		{
			return NULL;
		}
		return (*m_listIter);
	SS_CATCH(L"")
}

// ���������� ���������� ����� � ���� ������ (������������ ��������� GlobalSearch)
void CTextBlockCut::SetTextCut(const wchar_t* wszText)
{
	SS_TRY
		if (m_wszTextCut)
		{
			delete [] m_wszTextCut;
			m_wszTextCut = NULL;
		}
		if (wszText)
		{
			int len;
			len = (int) wcslen(wszText);
			m_wszTextCut = new wchar_t[len + 1];
			wcscpy(m_wszTextCut, wszText);
		}	
	SS_CATCH(L"")
}
// ��������� ���������� ����� � ���� ������
const wchar_t* CTextBlockCut::GetTextCut()
{
	SS_TRY
		if (m_wszTextCut)
		{
			return m_wszTextCut;
		}
		return NULL;
	SS_CATCH(L"")
}

// ������������ "�����" �������
void CTextBlockCut::SetPluginName(const wchar_t* wsName)
{
	SS_TRY
		if (m_wszPluginName) 
		{
			delete [] m_wszPluginName;
			m_wszPluginName = NULL;
		}
		if (wsName) 
		{
			int len;
			len = (int) wcslen(wsName);
			m_wszPluginName = new wchar_t[len + 1];
			wcscpy(m_wszPluginName, wsName);
		}
	SS_CATCH(L"")
}

// ��������� "�����" �������
const wchar_t* CTextBlockCut::GetPluginName() const
{
	SS_TRY
		if (m_wszPluginName) 
		{
			return m_wszPluginName;
		}
		return NULL;
	SS_CATCH(L"")
}

// ��������� XML - ������ ����������� ����������
std::wstring* CTextBlockCut::GetXML()
{
	SS_TRY
		CIndexAndPosition* pIndexAndPosition = NULL;

		pIndexAndPosition = dynamic_cast <CIndexAndPosition*> (GetFirstIndexAndPosition());
		
		m_ws = L"<ITextBlockCut>";
		while (pIndexAndPosition)
		{
			m_ws += (*(pIndexAndPosition->GetXML()));
			pIndexAndPosition = dynamic_cast <CIndexAndPosition*> (GetNextIndexAndPosition());
		}
		m_ws += L"</ITextBlockCut>";
		return &m_ws;
	SS_CATCH(L"")
}

// ���������� ��� ����� ����
SS::Core::Types::IndexationSearch::ETextCutType CTextBlockCut::GetType()
{
	return (SS::Core::Types::IndexationSearch::ETextCutType) m_oBlockCutData.TextCutType;
}
// ������������� ��� ����� �����
void CTextBlockCut::SetType(SS::Core::Types::IndexationSearch::ETextCutType eTextCutType)
{
	m_oBlockCutData.TextCutType = eTextCutType;
}
// ���������� ������� ���������
unsigned int CTextBlockCut::GetLevel()
{
	return m_oBlockCutData.Level;
}
// ������������� ������� ���������
void CTextBlockCut::SetLevel(unsigned int uiLevel)
{
	m_oBlockCutData.Level = uiLevel;
}
// ���������� ����� ������ ����� ���� �����
unsigned int CTextBlockCut::GetNumber()
{
	return m_oBlockCutData.Number;
}
// ������������� ����� ������ ����� ���� �����
void CTextBlockCut::SetNumber(unsigned int uiNumber)
{
	m_oBlockCutData.Number = uiNumber;
}	

}
}
}