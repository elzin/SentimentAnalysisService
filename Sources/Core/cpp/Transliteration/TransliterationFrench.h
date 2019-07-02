#pragma once
#include "stdafx.h"
#include "../ASSInterface/ITransliteration.h"
#include <vector>

namespace SS
{
    namespace Transliteration
    {
        using std::wstring;
        using std::vector;

        class CTransliterationFrench : public SS::Interface::Core::ITransliteration
        {
            public:
                CTransliterationFrench();
                virtual ~CTransliterationFrench();
                CTransliterationFrench(const CTransliterationFrench &obj);
                CTransliterationFrench& operator=(const CTransliterationFrench &obj);

                /// ������������
			    ULONG Release();
			    /// ���������� � ���������� � �������� REFIID. 
                /// pBase ����� NULL, ���� ������ ��������� �� ��������������
			    HRESULT QueryInterface(REFIID pIID, void** pBase);
                ///������������� �� IBase
			    void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

                wstring CorrectString(const wstring &str);

                void SetDictionary(const wstring &path);

            private:
                
                void SplitString(const wstring &str, const wstring addSymbs, bool containDigits,
                                 vector<wstring> &parts);

                /// �������� �������� �� ������ ���������� ������������������
                bool isGoodSymb(const wchar_t symb, const wstring addSymbs, bool containDigits);

                /// �������������� �����, ���� ��� ���������
                wstring WordTransliteration(const wstring &word);

                /// �������� �� com ������������ ��� word ����������
                void CorrectVectorOfPossibleCombinations(vector<wstring> &com, const wstring &word,
                                                         bool consideSize);

                /// ������������������� ���������� �� ��������
                bool TransliterationCombinationByRules(wstring &collectedWord, const wstring &combination,
                                                       int position);

                /// ������������� m_sFrenchLetterCombinations
                static vector<wstring> InitFrenchLetterCombinations();

                /// ������� ����������������� �����
                wstring m_CurrentTransliteringWord;

                /// ��������� �����, ������� �� �������� ��������������
                vector<wstring> m_DictionaryWords;

                /// ������� �������
                static wstring m_sRussianAlphabet;
                /// ������� ������������ ��������
                static wstring m_sFrenchVowels;
                /// ��������� ������������ ��������
                static wstring m_sFrenchConsonants;
                /// ����������� ��������������
                static vector<wstring> m_sFrenchLetterCombinations;
        };
    }
}