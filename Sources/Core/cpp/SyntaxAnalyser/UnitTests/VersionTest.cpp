//VersionTest.cpp

#include "StdAfx.h"
#include ".\versiontest.h"

//���� ������������
#ifdef _SS_UNITTESTS

#include "../BoardElement.h"

namespace SS
{
namespace UnitTests
{
	///���������������� ��������
	void CVersionTest::AnalyseVersion(CBlockVersion* pBlockVersion) const
	{
		SAVE_LOG(L"-----------------------------------------------------------------------------------");
		for (PVERELEMENT pVElem = pBlockVersion->GetFirst(); pVElem; pVElem = pBlockVersion->GetNext())
		{
			//����� ����������
			ShowElementInfo(pVElem);
		}
	}

	///���������������� �������� �� CBoard
	void CVersionTest::AnalyseVersion(BoardElementsIterator itF, BoardElementsIterator itL) const
	{
		SAVE_LOG(L"-----------------------------------------------------------------------------------");
		for (BoardElementsIterator it = itF; it != itL; ++it)
		{ 
			//����� ���������� �������� ��������
			ShowElementInfo((*it)->GetVerElem(), (*it)->GetWord()); 
		}
	}

	///������������ ������
	void CVersionTest::SetStandartWide(std::wstring & ws) const
	{
		const 
		unsigned short NeedSize = 17;
		unsigned short Size = (unsigned short)ws.size();
		if (Size > NeedSize) return;
		for (short i = 0; i < (NeedSize-Size); i++)
		{ ws.push_back(L' '); }
	}

	///�������������� string � wstring
	std::wstring CVersionTest::StrToWstr(const std::string & s) const
	{
		const int MaxSize = 30;
		wchar_t Buff[30];
		MultiByteToWideChar(0, 0, s.c_str(), MaxSize, Buff, MaxSize);
		return Buff;
	}

	///�������� ���������� �������� ��������
	void CVersionTest::ShowElementInfo(PVERELEMENT pVElem, std::wstring wsWord) const
	{
		//����������� �������������
		SetStandartWide(wsWord);
		//�������� ����� ����
		std::string sPartOfSpeach = pVElem->m_pMorpho->GetMorphoFeature().m_PartOfSpeechTypes.ToString();
		std::wstring wsPartOfSpeech = StrToWstr(sPartOfSpeach);
		SetStandartWide(wsPartOfSpeech);
		//��������/����������
		std::wstring wsHead;
		if (pVElem->m_isHead) 
		{ wsHead = L"head"; }
		else
		{ wsHead = L"child"; }
		SetStandartWide(wsHead);
		//����� � ���
		SAVE_LOG((wchar_t*)wsWord.c_str() AND (wchar_t*)wsPartOfSpeech.c_str() AND (wchar_t*)wsHead.c_str());
	}
	

}
}

#endif //_SS_UNITTESTS