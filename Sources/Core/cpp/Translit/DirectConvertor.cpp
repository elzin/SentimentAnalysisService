#include "stdafx.h"
#include "DirectConvertor.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "ConfigReader.h"
#include "../[libs]/_Paths.h"


/////////////////////////////////////////////////////////////////////////////////////
// Static variables

static const LPCWSTR s_rgTranslit[] = 
{
	L"�", L"a", 0,
	L"�", L"b", 0,
	L"�", L"v", L"w", 0,
	L"�", L"g", 0,
	L"�", L"d", 0,
	L"�", L"e", L"je", L"ye", L"jo", L"yo", L"io", 0,
	L"�", L"zh", L"z", L"j", L"g", 0,
	L"�", L"z", L"3", 0,
	L"�", L"i", L"j", L"y", L"u", 0,
	L"�", L"j", L"y", L"i", 0,
	L"�", L"k", L"c", 0,
	L"�", L"l", 0,
	L"�", L"m", 0,
	L"�", L"n", 0,
	L"�", L"o", 0,
	L"�", L"p", 0,
	L"�", L"r", 0,
	L"�", L"s", L"c", 0,
	L"�", L"t", 0,
	L"�", L"u", L"y", 0,
	L"�", L"f", 0,
	L"�", L"h", L"kh", L"x", 0,
	L"�", L"ts", L"c", L"tc", 0,
	L"�", L"ch", L"4", L"c", 0,
	L"�", L"sh", L"sch", L"w", L"6", L"s", 0,
	L"�", L"sch", L"sh", L"w", L"shch", 0,
	L"�", L"'", L"b", 0,
	L"�", L"y", L"i", L"u", L"bi", 0,
	L"�", L"'", 0,
	L"�", L"e", 0,
	L"�", L"yu", L"ju", L"u", L"y", 0,
	L"�", L"ya", L"ja", L"a", L"ia", L"j", L"'a", 0,
	0,
};

/////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////////////

CDirectConvertor::CDirectConvertor() :
		m_pMorphoAnalyzer(NULL),
		m_pTable(NULL),
		m_pHypotesis(NULL),
		m_pBreaker(NULL)
{
}

CDirectConvertor::~CDirectConvertor()
{
	delete m_pTable;
	delete m_pHypotesis;
	delete m_pBreaker;
}

/////////////////////////////////////////////////////////////////////////////////////
// CDirectConvertor interface

void CDirectConvertor::SetLoadManager(ILoadManager* pLoadManager)
{
	SS_TRY;

	if(GetLoadManager())
		return;

	CBaseCoreClass::SetLoadManager(pLoadManager);

	// automaton
	if(!m_pTable)
	{
		m_pTable = new CTransitionTable;

		wchar_t szDir[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, szDir);
		PathAppendW(szDir, L"Config");
		PathAppendW(szDir, L"Translit.dat");

		CConfigReader oReader;
		if(!oReader.FillTable(szDir, m_pTable, true))
		{
			m_pTable->Clear();
			if(!m_pTable->InitByDefault((LPCWSTR*) s_rgTranslit))
				SS_THROW(L"���������� ���������������� ������� �������������� �� ���������");
		}
	}

	// storage
	if(!m_pHypotesis)
		m_pHypotesis = new CHypotesisStorage(10000);

	// word breaker
	if(!m_pBreaker)
		m_pBreaker = new CWordBreaker(pmTranslit);

	// analyse params
	IAnalyseParams* pAnalyseParams = (IAnalyseParams*)
		pLoadManager->GetInterface(L"./core/linguistics/MainAnalyse.dll", CLSID_AnalyseParams, IID_AnalyseParams);
	pAnalyseParams->SetCurrentSystemMode(ecsmGlobal);
	pAnalyseParams->SetAnalyseMod(eamIndexation);
	pAnalyseParams->GetAnalyseDepthParams()->SetIsMorpho(true);
	pAnalyseParams->GetAnalyseDepthParams()->SetIsSemantic(true);
	pAnalyseParams->GetAnalyseDepthParams()->SetIsSyntax(true);
	pAnalyseParams->GetAnalyseDepthParams()->SetIsSynonims(false);

	// morphology
	IDictionary* pDict = (IDictionary*) 
		pLoadManager->GetInterface( DICTIONARIES_DLL_PATH, CLSID_IDictionary, IID_IDictionary);
	m_pMorphoAnalyzer = pDict->GetMorphologyAnalyser();
	m_pMorphoAnalyzer->SetAnalyseParams(pAnalyseParams);

	SS_CATCH(L"");
}

void CDirectConvertor::Lat2Rus(LPCWSTR szText, wstring* pResult)
{
	SS_TRY;

	int iLen = lstrlenW(szText);
	pResult->reserve(iLen);

	for(ELexemType lt = m_pBreaker->GetFirstLexem(szText); lt; lt = m_pBreaker->GetNextLexem())
	{
		if(lt == ltWord)
			AddWord((LPWSTR) m_pBreaker->GetCurrLexemString(), pResult);
		else
			*pResult += m_pBreaker->GetCurrLexemString();
	}

	SS_CATCH(L"");
}

/////////////////////////////////////////////////////////////////////////////////////
// CDirectConvertor functions

void CDirectConvertor::AddWord(LPWSTR szLatWord, wstring* pResult)
{
	SS_TRY;

	m_pTable->Process(szLatWord, m_pHypotesis);
	for(LPCWSTR sz = m_pHypotesis->GetFirstHypotesis(); sz; sz = m_pHypotesis->GetNextHypotesis())
	{
		if(m_pMorphoAnalyzer->IsExistWord(sz))
		{
			*pResult += sz;
			return;
		}
	}

	*pResult += szLatWord;

	SS_CATCH(L"Failed on word" AND szLatWord);
}
