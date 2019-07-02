#pragma once

#include "RootItem.h"

#include "..\ASSInterface\IBlackBoxItems.h"
using namespace SS::Interface::Core::BlackBox;

#include "..\ASSInterface\TMainAnalyseTypes.h"
using namespace SS::Core::Types;


namespace SS
{
namespace Core
{
namespace BlackBox
{

class CSentence :
		public CMiddleItem,
		public ISentence
{
public:
	CSentence();
	virtual ~CSentence();

public:
	virtual void AddUnit(IUnit* pUnit);
	virtual ISentence* GetNextSentence();
	virtual ISentence* GetPrevSentence();
	virtual IUnit* GetFirstUnit();
	virtual IUnit* GetLastUnit();
	virtual void ClearSentence();
	virtual ISentence* ReleaseSentence();
	virtual void SetLanguage(EAnalyseLanguage eLanguage);
	virtual EAnalyseLanguage GetLanguage();
	virtual void SetRelevance(unsigned int uiRelevance);
	virtual unsigned int GetRelevance();
	virtual int isEnabled();
	virtual void SetEnabled(int test);

	virtual int IsDigest();
	virtual void SetDigest(int val);

	virtual int IsPreDigest();
	virtual void SetPreDigest(int val);

	virtual int GetToneNeg();
	virtual void SetToneNeg(int val);

	virtual int GetTonePos();
	virtual void SetTonePos(int val);

	virtual wstring GetMarkers();
	virtual void SetMarkers(wstring val);

	virtual eProcessed GetProcessed();
	virtual void SetProcessed(eProcessed val);

	virtual void GetLinearUnits(list<IUnit*>& allUnits);
	virtual void GetLinearUnitsFull(list<IUnit*>& allUnits);
	virtual void GetLinearUnitsNonEmpty(list<IUnit*>& allUnits);

	virtual ISentence* GetPrevSentenceLinear();
	virtual void SetPrevSentenceLinear(ISentence* val);
	
private:
	void AddChildUnits(IUnit* unit, list<IUnit*>& findedUnits, bool isEmpty=true);	


	unsigned int m_uiRelevance;
	EAnalyseLanguage m_eLanguage;
	//bool m_bEnabled;
	//int m_nTest;
	int m_nEnabled;	// ������ ��� �������� ������ �� ����������� � ������ ��������� ��������� ��� ���
	int m_nDigest; // ������ �� ����������� � ��������
	int m_nPreDigest; // ������ � ��������� ��������
//	int m_nOffset; // �������� ����������� � ������. �������� �� �������� ������� �����. ����������������
	// � ������ ���������� ���������
	int m_nTonePos;
	int m_nToneNeg;
	ISentence* m_pPrevSent;
	wstring m_strMarkers;

	eProcessed m_processed;
};

}
}
}
