#pragma once
#include <vector>
#include "../DigestAnalyzer/HelpFunc.h"

namespace SS
{
	namespace LexicalAnalyzer
	{
		namespace TreeDictionary
		{
			class CTreeDictionary
			{	
			    private:
				    UnitPropertiesOperator* m_pUnitOperator;
                    void AddWord(wstring word, string info);
                    /// ���������� ����� ����� � �������
                    void AddNewLine(const wstring &line);
			    
				    std::vector<wchar_t> m_Slots; // �����-�����
				    std::vector<CTreeDictionary*> m_ChildForSlots;
				    string m_Info;

                public:				
                    CTreeDictionary();
				    CTreeDictionary(UnitPropertiesOperator* pUnitOperator);

                    /// �������� ������� �� ���������
                    void LoadDict(const vector<wstring> &dictionary);
				    void LoadDict(const wchar_t* str);
				    void FindWord(const wstring &word, vector<string>& find_types, bool isFullWordFind = false);
			};
		}
	}
}