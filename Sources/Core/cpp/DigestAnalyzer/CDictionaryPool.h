#pragma once

#include "stdafx.h"
#include "../LexicalAnalyzer/TreeDictionary.h"
#include "HelpFunc.h"

using namespace SS::LexicalAnalyzer::TreeDictionary;

enum eDictionary
{
	/// ����������
    reductions = 0,
	/// ��������� �������� �����������
	deletedOrgPrefixes = 1,
	/// ������ ���������������
	homonymyNouns = 2,
	/// ������ ��������������
	homonymyAdjectives = 3,
	/// ������������ ���������������, ��������������� �� �� "��"
	nounVerbsNoIE = 4,
	/// ���������������, ��������������� �� "��", �� �� ������������
	nounVerbExclusionIE = 5,
	/// ���������
	posts,
};

class CDictionaryPool
{
private:
	static CTreeDictionary* m_pDeletedOrgPrefixes;
	static CTreeDictionary* m_pDeletedReductions;
	static CTreeDictionary* m_pHomonymyNouns;
	static CTreeDictionary* m_pHomonymyAdjectives;
	static CTreeDictionary* m_pNounVerbsNoIE;
	static CTreeDictionary* m_pNounVerbExclusionIE;
	static CTreeDictionary* m_pPosts;
public:
	static void Load(wstring strDatabasePath, UnitPropertiesOperator* unitOperator);

	/// �������� �������� �� ���������
    static void LoadFromCollection(vector<vector<wstring>> &dictionaries, UnitPropertiesOperator* unitOperator);
	
	static bool IsFindOrgPrefixes(wstring strWordForCheck);

	static bool IsFindReduction(wstring strWordForCheck);

	static bool IsOnlyNoun(wstring strWordForCheck);

	static bool IsOnlyAdjective(wstring strWordForCheck);

	static bool IsNounVerb(wstring normalWord);

	static bool IsPost(const wstring &normalWord);
};


