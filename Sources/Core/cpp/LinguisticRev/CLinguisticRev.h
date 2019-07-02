#pragma once

#include "..\ASSInterface\IRev.h"

using namespace SS::Interface::Core::BlackBox::Query;
using namespace SS::Interface::Core::BlackBox;
using namespace SS::Interface::Core::Rev;
using namespace SS::Core::Types::IndexationSearch;

#include "..\ASSInterface\IMainAnalyse.h"
using namespace SS::Interface::Core::MainAnalyse;

#include "RelevanceCalculator.h"


namespace SS
{
namespace LinguisticRev
{

class CLinguisticRev : public ILinguisticRelevance
{
public:
	CLinguisticRev();
	virtual ~CLinguisticRev();

// IBase
public:
	ULONG Release();
	HRESULT QueryInterface(REFIID pIID, void** pBase);

	virtual void SetAnalyseParams(IAnalyseParams* pAnalyseParams);

// ILinguisticRelevance
public:
	///���������� ������� ������
	virtual void SetQuery(IQuery* pQuery);
	///��������� ������� ������ �� ������� ���� ������
	virtual bool IsExistAnswerWord(IText* pText);
	///��������� ������� ������ � ��������� ���������� �������������
	virtual __int32 UpdateRelevance(IText* pText, IText* pTextTitle);
	///������������ �����, ������� ����������� ������������ �� ������� �� ������ ������������� �������
	virtual void HighlightKeywords(IText* pText);

private:
	IQuery* m_pQuery;
	bool m_bSynonyms;

	CRelevanceCalculator m_oRevCalc;
};

}
}
