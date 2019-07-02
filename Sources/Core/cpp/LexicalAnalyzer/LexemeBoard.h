#pragma once

#include "..\ASSInterface\ILexicaLib.h"
#include "..\ASCInterface\ILinguisticProcessor.h"
#include <atlstr.h>
using namespace SS::Interface::Core;


#ifdef UNICODE
#	define GetLexemeT GetLexeme
#else
#	define GetLexemeT GetLexemeA
#endif


namespace SS
{
namespace LexicalAnalyzer
{

enum ELexemType
{
	accUndefined,

	accWord = 0x11,

	accSentBreak,
	accParaBreak,

	accNumber,

	accAbbrev,
	accAcronymCitation,
	accLQuote,
	accRQuote,
	accInitial,

	accComma,
	accApostroph,
	accAmpersand,
	accSmallWord,

	accDefis,
	accTire,

	accSign,
	accPoint,
	accSlash,

	accBreak,

	accLongNumber,
	accFirstComplexNumberPart,
	accComplexNumberPart,

	accColon,
	accEngWord,
	accURLPart,
	accAt,

	accUnclosedSentence,
	accTitleBreak,

	accOrdinalNumber,
	accNumberWord,
	accBrokenWord,
	accRomanNumber,

	accLeftBracket,
	accRightBracket,

	accURL
};

class CLexemeBoard : public SS::Interface::Core::ILexemeBoard
{
public:
	CLexemeBoard(unsigned int uiCapacity = MAX_WORDS_IN_BLOCK);
	~CLexemeBoard();

public:
	/// ������ ������� ��������� (���������� � ������������ ���������� ������������� ����������� ������ ������)
	virtual unsigned int GetCapacity();
	/// ������ ���������� ����������� ������ ������
	virtual unsigned int GetCount();
	/// ������� �� ������ �������, ������ 0, ���� ������ ���, ������ 1 ���� ����
	virtual unsigned int MoveFirst();
	/// ������� �� ��������� �������, ������ 0, ���� ��������� �� ��������� �������, , ������ 1 ���� �� �� ���������
	virtual unsigned int MoveNext();
	///	��������� �������
	virtual LPCWSTR GetLexeme();
	virtual LPCSTR GetLexemeA();
	/// ��������� ����������� ������ ������� ������� � ������ (��������� ���������� � 0)
	virtual unsigned int GetAbsoluteIndex();
	/// ��������� ����������� ������ ������� ������� ������� �������
	virtual unsigned int GetAbsoluteSymbolIndex();

public:
	ELexemType GetLexemType();
	bool IsEnd();

	bool MoveLast();
	bool MovePrev();

	void Reset();
	bool AddLexeme(LPCTSTR szText, ELexemType LexemType, int iAbsPosition, int iAbsCharPosition);

	ELexemType GetFirstLexem();
	ELexemType GetLastLexem();

	unsigned int GetFirstLexemPosition();
	unsigned int GetLastLexemPosition();

	ELexemType GetLexemType(int nToLeft);
	LPCTSTR GetLexemString(int nToLeft);
	UINT GetLexemPosition(int nToLeft);
	UINT GetLexemSymbolPosition(int nToLeft);

	void SetLexemeType(ELexemType eType);

	void SetHeaderLevelBegin(int iHeaderLevel);
	int GetHeaderLevelBegin();

	void SetHeaderLevelEnd(int iHeaderLevel);
	int GetHeaderLevelEnd();

private:
	struct SLexem
	{
		SLexem() : iAbsPosition(0), iAbsCharPosition(0), LexemType(ELexemType::accUndefined), iHeaderLevelBegin(0), iHeaderLevelEnd(0)
		{
		}

		ATL::CAtlString szText;
		int iAbsPosition;
		int iAbsCharPosition;
		ELexemType LexemType;
		int iHeaderLevelBegin;
		int iHeaderLevelEnd;
	};

	typedef vector<SLexem*> TLexemVect;

private:
	TLexemVect m_vLexems;
	int m_iCurrLexem;
	unsigned int m_uiTop;
};

}
}
