#pragma once

#include "LexemeBoard.h"
#include "InternalRepresentation.h"
#include "IndexLoader.h"
#include "Unit.h"
#include "UnitChecker.h"
#include "IReparser.h"

using namespace SS::Interface::Core::Common;


namespace SS
{
namespace LexicalAnalyzer
{
namespace Walker
{

enum ELexicalPattern
{
	lpWord = 1,					// any other word
	lpFIO,						// first, last, middle name
	lpFI,						// first, last name
	lpF,						// first name
	lpIO,						// first, middle name
	lpYM,						// year, month
	lpDM,						// day, month
	lpDMY,						// day, month, year
	lpDMW,						// day, month, day of week
	lpDMYW,						// day, monty, year, day of week
	lpMeasureDay,				// day interval
	lpMeasureMonth,				// month interval
	lpYear,						// year
	lpNumericYear,				// year with 's or s
	lpCentury,					// century
	lpOrg,						// bank, company, fund, party, intern. org., or a sequence of LWords
	lpQuotation,				// quoted sequence of words
	lpCityCountry,				// city and country
	lpStateCountry,				// state/province and coutry
	lpCityState,				// city and state/province
	lpComplexNumber,			// number, divided with commas, points, apostrophs etc.
	lpInetLocation,				// any number, word or sign within url, ip-address or e-mail
	lpTime,						// ����� � ������� 22:25[:14]
	lpTime1,					// ����� � ������� 22-25
	lpTimeInterval,				// ��������� �������� (� 15:50 �� 16:00)
	lpFloat,					// float point numbers
	lpLSequence,				// any sequence of LWords
	lpGenitiveEng,				// genitive case in Engilish {words with 's)
	lpOrdinalNumber,			// ordinal number with particle 1st, 2nd, 3d, 4th...
	lpNegVerb,					// couldn't, wouldn't, wasn't etc...
	lpSimpleSequence,			// any sequence that should be joined with Noun Common Single morphology
	lpSimpleFraction,			// simple fractions like 1/10, 3/2...
	lpList,						// part of query, that should be replaced with "what are"
	lpGeoSemantic,			
	lpYear1, 
	lpYear2,					//
	lpYearPart1,				// I ���������, II ���������
	lpYearPart2,				// ������ ���������, 1*� ���������
	lpMI,                       // ������� ������� (������, ������, ������ � ��������� 3 ������)
	lpMI1,                      // ������� ������� (������, ������, ������ � ��������� 3 ������)
	lpMI2,                      // ������� ������� (������, ������, ������ � ��������� 3 ������)
	lpMI3,						// ������� ������� (������, ������, ������ � ��������� 3 ������)
	lpM,						// �����
	lpDecade,					// 1�� ������ ����, I ����������� ����
	lpDecade1,					// ������ [20] ����, �������� ����
	lpDecade2,					// 1 �����������, II �����������
	lpWeekEnd,					// ��������, �������� ���, weekend
	lpFiveDigitsPhoneNumber,	// 5-������� ���������� ������ (5 ������ ��� ����� ���� ������ � ���� ������)
	lpSixDigitsPhoneNumber,		// 6-������� ���������� ������ (6 ������ ��� ����� ���� ������ � ���� ������)
	lpSevenDigitsPhoneNumber,	// 7-������� ���������� ������ (7 ������ ��� ����� ���� ������ � ���� ������)
	lpTenDigitsPhoneNumber,		// 10-������� ���������� ������ +0953213454
	lpElevenDigitsPhoneNumber,	// 11-������� ���������� ������ 79053531721
	lpDM1,
	lpDMY1,
	lpDMY2,
	lpDMY3,
	lpDMY4,
	lpDMY5,
	lpDMY6,
	lpYMD,						/// ���.�����.���� ��� ���/�����/���� ��� ���-�����-���� 
	lpDMW1,
	lpDMW2,
	lpDMYW1,					// �����, �����, ���, ���� ������
	lpDMYW2,					// �����, �����, ���, ���� ������
	lpDMYW3,					// �����, �����, ���, ���� ������
	lpDMYW4,					// �����, �����, ���, ���� ������
	lpDI,						// �������� (� 12 �� 18 ������� 2008)
	lpDYI,
	lpDayTime,					// ����� ��� ( ����, ����)
	lpQuotationSimple,
	lpNounSequence
};


#undef yyFlexLexer
#define yyFlexLexer WalkerFlexLexer
#include "FlexLexer.h"

class CWalker : 
		public yyFlexLexer,
		public CAnalyseParams
{
public:
	CWalker();
	~CWalker();

// CAnalyseParams
public:
	virtual void SetAnalyseParams(IAnalyseParams* pAnalyseParams);

public:
	void Init(CUnitChecker* pUnitChecker, CIndexLoader* pIndexLoader, IBlackBoxTextStorage* pStorage, 
		IR::TUnitStorage* pUnitStorage);
	void Process(IR::CSentence* pSentence, EWalkerMode eMode);
	void SetNumberSemantic(IR::CSentence* pSent);
	void SetBeRepresentSemantic(IR::CSentence* pSent);
	void SetNounToUnknownWords(IR::CSentence* pSent);

private:
	virtual int LexerInput(char* buf, int max_size);

	void ProcessPattern(ELexicalPattern lp);
	void ProcessOrganizations(IR::CUnit* pUnit);
	void ProcessNames(IR::CUnit* pUnit, bool bFirst, bool bLast, bool bMiddle);
	void ProcessDates(IR::CUnit* pUnit, bool bYear, bool bMonth, bool bNumber, bool bDay);

	void CheckAndSetGenitive(IUnit* pUnit);
	LPCTSTR GetNegativeVerb(LPCTSTR szLexem);

private:
	int GetMode(EWalkerMode eMode);
	EWalkerMode GetMode(int iMode);

private:
	/// current mode
	EWalkerMode m_eMode;
	/// current sentence
	IR::CSentence* m_pSent;
	/// current unit
	IR::CUnit* m_pUnit;

	/// AMConverter helper
	CUnitChecker* m_pUnitChecker;
	/// dictionaries helper
	CIndexLoader* m_pIndexLoader;
	/// creating black box items
	IBlackBoxTextStorage* m_pStorage;
	IR::TUnitStorage* m_pUnitStorage;

	/// count of units, processed by flex
	int m_nProcessed;
	/// count of units, pushed to flex
	int m_nInserted;

	/// analyze params query mode
	bool m_bQuery;
};

}
}
}
