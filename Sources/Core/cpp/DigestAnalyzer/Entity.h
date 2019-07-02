#pragma once

#include "stdafx.h"
#include "../ASSInterface/IDigestManager.h"
#include "../ASSInterface/IDictionaryManager.h"
#include "../ASSInterface/IAMConverter.h"
#include "../assinterface/iblackbox.h"
#include "../ASSInterface/ISyntaxAnalyzer.h"
#include <list>
#include <map>
#include "HelpFunc.h"
#include "CDictionaryPool.h"
using namespace std;

enum eEntityBaseType
{
    Default,
    /// �������
    Person,
    /// �����������
    Organization,
    /// ���������
    Place,
    /// ����
    Date,
    /// ���������������
    Other,
    /// ������������ ���������������
    NounVerb,
    /// ������
    Verb,
    /// �����������
    Pronoun,
    /// �������
    Adverb,
    /// ������ ����: �������, ����������, ������������
    Ceterus,
	/// ��������������
	Adjective,
	/// ����� ��������
	Phone,
	/// �������
	Event,
	/// �������
	Product,
};

enum EEntityType
{
	entDefault,
	entUnknown, // ����������� ���
	entPersonName,  // ������� � ������
	entPersonInfo, // ������� � ���. �����
	entPersonNoInfo, // ������� ��� ����� � ����
	entOrgName, // ����������� � ������	
	entOrgNoInfo, // ����������� ��� �����
	entPlaceName, // ����� � ������
	entPlaceNoInfo, // ����� ��� �����
	entDate, // ����
	entUnknownProper, // �����������, �� �������� ����� � ������� ����� - �������� ������������ ����-����
	entNounVerb, // ������������ ���������������
	entVerb,  // ������
	entPronoun, // �����������
	entOrgAbbr, // ����������� ������������
	entOrgInfo, // ����� ����������� (����������� ��������)
    entAdverb, // �������
    entPretext, // �������
    entPredicative, // ����������
    entNumeric, // ������������
	entQuote, // �������
	entAdjective, // ��������������
	entShortAdjective, // ������� ��������������
	entComparative, // ������������� ������� ���������������
	entSuperlative, // ������������ ������� ���������������
	entPhone, // ����� ��������
	entEvent, // ����� ��������
	entProduct, // ����� ��������
};

struct CDate
{
	int nYear;
	int nMonth;
	int nDay;
	CDate()
	{
		nYear = 0;
		nMonth = 0;
		nDay = 0;
	}

	CDate(wstring strDate);
	wstring GetString();

	void Increment(int n);
	void Decrement(int n);

	void ClearDate()
	{
		nYear = 0; nMonth = 0; nDay = 0;
	}


	bool operator<=(const CDate& inDate) const
	{	
		if (inDate.nYear == nYear && inDate.nMonth == nMonth && inDate.nDay == nDay) return true;	  
		return inDate.nYear > nYear || inDate.nMonth > nMonth || inDate.nDay > nDay;			
	}

	bool operator>=(const CDate& inDate) const
	{	
		if (inDate.nYear == nYear && inDate.nMonth == nMonth && inDate.nDay == nDay) return true;
		return inDate.nYear < nYear || inDate.nMonth < nMonth || inDate.nDay < nDay;				  
	}

	bool operator<(const CDate& inDate) const
	{	
		//if (inDate.nYear == nYear && inDate.nMonth == nMonth && inDate.nDay == nDay) return true;
		return inDate.nYear > nYear || inDate.nMonth > nMonth || inDate.nDay > nDay;			
	}

	bool operator>(const CDate& inDate) const
	{	
		//if (inDate.nYear == nYear && inDate.nMonth == nMonth && inDate.nDay == nDay) return true;
		return inDate.nYear < nYear || inDate.nMonth < nMonth || inDate.nDay < nDay;			
	}

	void operator=(const CDate& inDate)
	{
		this->nDay = inDate.nDay;
		this->nMonth = inDate.nMonth;
		this->nYear = inDate.nYear;
	}
};

struct CDateInterval
{
	CDate begin;
	CDate end;
	CDateInterval()
	{

	}
	CDateInterval(const CDateInterval& di)
	{
		begin = di.begin;
		end = di.end;
	}
	int GetLength();

	bool isBad()
	{
		if (begin.nYear>3000 || begin.nMonth>12 || begin.nDay>31 ||
			end.nYear>3000 || end.nMonth>12 || end.nDay>31)
		{
			return true;
		}
		return false;
	}

	void Clear()
	{
		begin.nYear = 0;
		begin.nMonth = 0;
		begin.nDay = 0;
		end.nYear = 0;
		end.nMonth = 0;
		end.nDay = 0;
	}

	bool IsDateClear()
	{
		if (begin.nYear==0 && end.nYear==0) return true; return false;
	}

	list <CDate> extDates; // ������������ ��� �������� ���� 15 � 16 ����

	wstring GetString();
};

class CEntity
{
private:
	UnitPropertiesOperator* m_pUnitOperator;	
	CDate* m_pBaseDate;
	wstring m_strHash;
	wstring m_strValue;

	set<wstring> m_Adjectives;

	wstring GetDateNormalString();
	wstring GetRegionNormalString();
	wstring GetPersonNormalString();
	wstring GetPersonNormalStringEng();
	wstring GetOrgNormalString();
	wstring GetVerbType();

	void AddUnitToNameGroup(SS::Interface::Core::BlackBox::IUnit* pUnit);

	CDateInterval  GetValueForDateForUnit(SS::Interface::Core::BlackBox::IUnit* pUnit,
		set<SS::Interface::Core::BlackBox::IUnit* >& stopUnits);
	CDateInterval  GetNormalForSimpleDate(SS::Interface::Core::BlackBox::IUnit* pDate,CDateInterval inputInt,
		set<SS::Interface::Core::BlackBox::IUnit* >& stopUnits, int mode = 0);
	wstring OKATONorm(SS::Interface::Core::BlackBox::IUnit* pUnit,SS::Core::Features::CMorphoFeature& oMorfoPattern, int num);
	void GetGenderForEntList(TUnitList& unitList,SS::Core::Features::CMorphoFeature& oMorfoPattern);

	wstring AbbrNorm(SS::Interface::Core::BlackBox::IUnit* pUnit);	

	bool IsDelOrgPrefix(SS::Interface::Core::BlackBox::IUnit* pUnit);

	wstring GetVerbNormalString();
    /// ��������� ���������������� �������� ��� ������������ ������ ����
    wstring GetUnchangeableNormalString();
    wstring GetNormalStringByPartOfSpeech(SS::Core::Features::Types::PartOfSpeechTypes partOfSpeech,
        SS::Core::Features::Types::GenderType gender = SS::Core::Features::Values::GenderType.Undefined);

	wstring GetPhoneNormalString();
	int GetPhoneNumberLength(wstring phoneType);

	wstring GetDefaultNormalString(TUnitList& unitList1);
	wstring GetMorphoPropStr();
	void UpdateVector(vector<wstring> &collection, wstring value);
	void InsertInVector(vector<wstring> &collection, int length, wstring value);

	bool isMiddleNameEvristic(wstring str);

public:
	wstring GetFirstNameXML();
	wstring GetMiddleNameXML();
	wstring GetLastNameXML();
	wstring GetNameXML();
	wstring GetPseudoPlaceXML();
	wstring GetLinkedPlaces();
	wstring GetLinkedPlacesXML();

	vector<wstring> GetAdjectives();
	void AddAdjective();
	vector<wstring> GetMorphoProp();
	CEntity(UnitPropertiesOperator* unitOperator, SS::Core::Types::EAnalyseLanguage lang);
	bool IsGoodEnt();
	bool IsHaveNecessaryNoun();
	bool IsUnknownHaveReduction();
	bool IsEngGoodEnt();
	void SetDate(wstring strBaseDate);
	wstring GetTypeStr();
    /// ��������� ���������������� ��������
    wstring GetValue();
    /// ������������ ��������
	wstring GetNormalString();
    /// ������������ �������� ��������
    wstring NormalizeValue();
	wstring GetXML(wstring value, int sentOffset, bool isEntityTeg = true);
	void ProcessValueForDate();
	int GetBeginOffset();
	int GetEndOffset();
	int GetEndOffsetNew(const wstring &srcText);
	SS::Interface::Core::BlackBox::IUnit* GetLastUnit();
	wstring GetHash();	
	wstring GetDefaultNormalString();
	bool IsEntCaseCoincident(CEntity* pEnt);
	bool IsEntSemanticCoincident(CEntity* pEnt);
	SS::Interface::Core::BlackBox::IUnit* GetFirstUnit();
	bool IsHomogeneousUnionPossible(CEntity* pEnt);
	int GetNominalNounCount();
	bool IsSingleOrgInQuote();
	bool IsMorpho(SS::Core::Features::CMorphoFeature oMorfoPattern);
	bool IsOgrNameWithoutNameGroup();
	bool IsUnitInEntity(SS::Interface::Core::BlackBox::IUnit* pUnit);
	wstring GetSubthemesXML(const wstring &srcText);
	/// �������� ��������� � �������� � ������ �������
	void DeleteUncorrectUnitsFromBorders();
	void AddAdjectiveHomogeneousPrefix(SS::Interface::Core::BlackBox::IUnit* pUnit);
    /// ��������� ����� � ������ ������ ��������
    void AddUnitsToList(TUnitList list);
    /// �������� �� ����������
    bool IsReduction(SS::Interface::Core::BlackBox::IUnit* pUnit);
	/// ���������� �����������
	void AddSubEntity(CEntity *pSubEntity);

	eEntityBaseType nType;
	eEntityBaseType rootType;
	int begin;
	int end;
	int ID;

	bool isProcessed;
	bool isPseudoPlace;
	bool isAnaphora;
	bool isUsed;
	bool isHaveHomogenousAdj; // true ���� ��� ���� ������� ���� ����������� ���������� ��������������

	wstring hashStr;
	wstring m_strProfession;
	wstring m_strFirstName;
	wstring m_strMiddleName;
	wstring m_strLastName;
	wstring m_Name;
	wstring m_strPrefix;
	wstring m_strPost;

	TUnitList unitList; 
	TUnitList unitListRef; 
	EEntityType entType;
	SS::Interface::Core::BlackBox::IUnit* rootUnit;
    SS::Interface::Core::BlackBox::IUnit* nounUnit;
	TUnitList hashList; 
	
	list<list<SS::Interface::Core::BlackBox::IUnit*>> unitResolutions; // ������������ ��� ���������� �����������
	// ������� �����-������������ � ������ ������ �������� ����� �����. ������ ������, �� �������
	// ������ ������������ �����������. ��� ������� ������ ��� ��� ������������� ����������� �����. ������ ����
	list<CEntity*> lstSynonims;
	list<CEntity*> lstRootEntities;
	list<SS::Interface::Core::BlackBox::IUnit*> lstLinkUnits;

	CDateInterval m_DateInterval;
	SS::Interface::Core::BlackBox::IUnit* extDateRootUnit; // ������������ � ������������ ���� � �������� �� �������� �������� ����

	SS::Core::Types::EAnalyseLanguage m_lang;

	set<SS::Interface::Core::BlackBox::IUnit*> m_setNameGroupUnits;
	SS::Interface::Core::BlackBox::ISentence* m_pSent;
	SMIList propList;

	list<CEntity*> m_lstSubEntites; // ����� �������� ���� � ������ ����������

	list<SS::Interface::Core::BlackBox::IUnit*> m_lstHomogeneousAdjUnits;

	

};


typedef list<CEntity*> TEntityList;