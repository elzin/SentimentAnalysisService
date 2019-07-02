#include "stdafx.h"
#include "UnitChecker.h"

#include "..\ASSInterface\Iterators.h"
using namespace SS::Iterators;

#include "..\ASSInterface\TMainAnalyseTypes.h"
using namespace SS::Core::Types;

#include "..\ASSInterface\TDictionaryManager.h"
using namespace SS::Dictionary::Types;

#include "TextCopy.h"



namespace SS
{
namespace LexicalAnalyzer
{

static const int nSuffixCount = 108;

static const SRusLNSuffixInfo sRusLNSiffixes[] =
{
	L"��", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"ov", L"ov", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"�va", L"�va", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,

	L"ev", L"ev", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"eva", L"eva", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,

	L"in", L"in", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"ina", L"ina", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	
	

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	L"��", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	L"��", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"��", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	L"����", L"����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"�����", L"����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"�����", L"����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"�����", L"����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"�����", L"����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"����", L"����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"����", L"����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"����", L"����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"����", L"����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"����", L"����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	// ��������� �������. �������, �����
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	//* ������� - ��������
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"�����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"����", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"�����", L"�����", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctNominative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctDative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtMasculine, SS::Core::Features::Values::CaseType.ctLocative,

	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctNominative,
    L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctGenitive,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctAccusative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctDative,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctInstrumental,
	L"���", L"���", SS::Core::Features::Values::GenderType.gtFemale, SS::Core::Features::Values::CaseType.ctLocative,



};


/////////////////////////////////////////////////////////////////////////////////////
// Constructors
/////////////////////////////////////////////////////////////////////////////////////

CUnitChecker::CUnitChecker() :
		m_pSemanticConverter(NULL),
		m_pMorphoConverter(NULL),
		m_pSemanticFeature(NULL),
		m_pMorphoFeature(NULL),
		m_pStorage(NULL),
		m_bMorpho(false),
		m_bSemantic(false),
		m_bSyntax(false),
		m_bIndexation(false)
{
}

CUnitChecker::~CUnitChecker()
{
	if(m_pSemanticFeature)
		delete m_pSemanticFeature;
	if(m_pMorphoFeature)
		delete m_pMorphoFeature;
}

/////////////////////////////////////////////////////////////////////////////////////
// CUnitChecker interface

void CUnitChecker::SetAnalyseParams(IAnalyseParams* pAnalyseParams)
{
	SS_TRY;

	CAnalyseParams::SetAnalyseParams(pAnalyseParams);
	m_bMorpho = pAnalyseParams->GetAnalyseDepthParams()->IsMorpho();
	m_bSemantic = pAnalyseParams->GetAnalyseDepthParams()->IsSemantic();
	m_bSyntax = pAnalyseParams->GetAnalyseDepthParams()->IsSyntax();

	m_bIndexation = 
		pAnalyseParams->GetAnalyseMod() == eamIndexation ;

	SS_CATCH(L"");
}

void CUnitChecker::Init(ILoadManager* pLoadManager, IBlackBoxTextStorage* pStorage)
{
	SS_TRY;

	// converters
	m_pSemanticConverter = (IAMConverterSemantic*)
		pLoadManager->GetInterface(L"./core/linguistics/AMConverter.dll", CLSID_AMConverterSemantic, IID_AMConverterSemantic);
	m_pMorphoConverter = (IAMConverterMorpho*)
		pLoadManager->GetInterface(L"./core/linguistics/AMConverter.dll", CLSID_AMConverterMorpho, IID_AMConverterMorpho);

	assert(!m_pSemanticFeature && !m_pMorphoFeature);
	m_pSemanticFeature = new CSemanticFeature;
	m_pMorphoFeature = new CMorphoFeature;
	

	m_pStorage = pStorage;

	SS_CATCH(L"");
}

bool CUnitChecker::HasSemantic(IUnit* pUnit, const TSemanticType& Type)
{
	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; )
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitSemanticIndex)
		{
			pIndex = pUnit->GetNextIndex();
			continue;
		}

		m_pSemanticFeature->Undefine();
		m_pSemanticConverter->EnCode(pIndex->GetDictionaryIndex()->GetFirst().GetId(), m_pSemanticFeature);

		if(m_pSemanticFeature->m_SemanticType.Equal(Type))
			return true;
		else
			pIndex = pIndex->ReleaseIndex();
	}

	return false;
}

bool CUnitChecker::HasSemantic1(IUnit* pUnit, const TSemanticType& semType, 
								const TSPersonType& persType)
{
	SS::Interface::Core::BlackBox::IIndex* pIndex;
		SS::Interface::Core::BlackBox::IDictionaryIndex* pDictionaryIndex;
		SS::Interface::Core::BlackBox::EIndexType oIndexType;
			

	for(pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		pDictionaryIndex = pIndex->GetDictionaryIndex();
			
		if(pDictionaryIndex)
		{
			SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex = pDictionaryIndex->GetFirst();
			oIndexType = oDictionaryIndex.GetIndexType();
			if (oIndexType==SS::Interface::Core::BlackBox::eitSemanticIndex)
			{							
				int index = oDictionaryIndex.GetDictionaryIndex();
				SS::Core::Features::CSemanticFeature oSemanticFeature;							
   				m_pSemanticConverter->EnCode(index, &oSemanticFeature);					
				if (oSemanticFeature.m_SemanticType.IsContain(semType) &&
					(oSemanticFeature.m_SPersonType.Equal(persType) || 
					persType.Equal(SS::Core::Features::Values::TSPersonType.Undefined)))
				{
					return true;
				}
			}
		}
	}	
	return false;
}

bool CUnitChecker::HasProfession(IUnit* pUnit)
{
	SS::Interface::Core::BlackBox::IIndex* pIndex;
		SS::Interface::Core::BlackBox::IDictionaryIndex* pDictionaryIndex;
		SS::Interface::Core::BlackBox::EIndexType oIndexType;
			

	for(pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		pDictionaryIndex = pIndex->GetDictionaryIndex();
			
		if(pDictionaryIndex)
		{
			SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex = pDictionaryIndex->GetFirst();
			oIndexType = oDictionaryIndex.GetIndexType();
			if (oIndexType==SS::Interface::Core::BlackBox::eitSemanticIndex)
			{							
				int index = oDictionaryIndex.GetDictionaryIndex();
				SS::Core::Features::CSemanticFeature oSemanticFeature;							
   				m_pSemanticConverter->EnCode(index, &oSemanticFeature);					
				if (oSemanticFeature.m_SemanticType.IsContain(SS::Core::Features::Values::TSemanticType.smtPerson) &&
					oSemanticFeature.m_SPersonType.IsContain(SS::Core::Features::Values::TSPersonType.semprstProfession))						
				{
					return true;
				}
			}
		}
	}
	return false;
}

void CUnitChecker::AddDateIndex(IUnit* pUnit, const TSTimeIntervalType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtTimeInterval;
	m_pSemanticFeature->m_STimeIntervalType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddPersonIndex(IUnit* pUnit, const TSPersonType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtPerson;
	m_pSemanticFeature->m_SPersonType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddMeasureIndex(IUnit* pUnit, const TSMeasureType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtMeasure;
	m_pSemanticFeature->m_SMeasureType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddPartOfSpeechIndex(IUnit* pUnit, const PartOfSpeechTypes& Type, const CaseType& Case, 
										const NumberType& Number, EAnalyseLanguage eal)
{
	if(!m_bMorpho)
		return;

	m_pMorphoFeature->Undefine();
	m_pMorphoFeature->m_PartOfSpeechTypes = Type;
	m_pMorphoFeature->m_CaseType = Case;
	m_pMorphoFeature->m_NumberType = Number;

	AddMorphoIndex(pUnit, eal);
}

void CUnitChecker::AddPartOfSpeechIndex(IUnit* pUnit, const PartOfSpeechTypes& Type, const CaseType& Case, 
										const NumberType& Number,const GenderType& Gender, EAnalyseLanguage eal)
{
	if(!m_bMorpho)
		return;

	m_pMorphoFeature->Undefine();
	m_pMorphoFeature->m_PartOfSpeechTypes = Type;	
	m_pMorphoFeature->m_CaseType = Case;
	m_pMorphoFeature->m_NumberType = Number;
	m_pMorphoFeature->m_GenderType = Gender;

	AddMorphoIndex(pUnit, eal);
}

void CUnitChecker::AddPartOfSpeechIndexWithAnim(IUnit* pUnit, const PartOfSpeechTypes& Type, const CaseType& Case, 
										const NumberType& Number,const GenderType& Gender, EAnalyseLanguage eal)
{
	if(!m_bMorpho)
		return;

	m_pMorphoFeature->Undefine();
	m_pMorphoFeature->m_AnimInAnimType = SS::Core::Features::Values::AnimInAnimType.aiaAnimation;
	m_pMorphoFeature->m_PartOfSpeechTypes = Type;
	m_pMorphoFeature->m_CaseType = Case;
	m_pMorphoFeature->m_NumberType = Number;
	m_pMorphoFeature->m_GenderType = Gender;

	AddMorphoIndex(pUnit, eal);
}


void CUnitChecker::AddNumericPartOfSpeechIndex(IUnit* pUnit, const NumericType& NumericType, wstring numEnd)
{
	if(!m_bMorpho)
		return;

	EAnalyseLanguage eal = ealEnglish;

	m_pMorphoFeature->Undefine();
	m_pMorphoFeature->m_PartOfSpeechTypes = Values::PartOfSpeechTypes.postNumeric;
	m_pMorphoFeature->m_NumericType = NumericType;
	if (numEnd==L"�" || numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtMasculine;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;	
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctNominative;
		eal = ealRussian;
	}else
	if (numEnd==L"���" || numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtMasculine;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;	
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctGenitive;
		eal = ealRussian;
	}else
	if (numEnd==L"��" || numEnd==L"�")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtMasculine;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;	
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctInstrumental;
		eal = ealRussian;
	}else
	if (numEnd==L"���" || numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtMasculine;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;	
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctDative;
		eal = ealRussian;
	}else
	if (numEnd==L"��" ) 	 
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtMasculine;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctLocative;
		eal = ealRussian;

	}else
	if (numEnd==L"�" || numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtFemale;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctNominative;
		eal = ealRussian;
	}else
	if (numEnd==L"��" || numEnd==L"�")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtFemale;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctAccusative;
		eal = ealRussian;
	}else
	if (numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtFemale;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctDative;
		eal = ealRussian;
	}else
	if (numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtGeneral;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntPlural;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctNominative;
		eal = ealRussian;
	}else
	if (numEnd==L"��" || numEnd==L"�")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtGeneral;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntPlural;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctAccusative;
		eal = ealRussian;
	}else
	if (numEnd==L"���" || numEnd==L"��")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtGeneral;
	    m_pMorphoFeature->m_NumberType = Values::NumberType.ntPlural;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctInstrumental;
		eal = ealRussian;
	}
	else
	if (numEnd==L"��" || numEnd==L"�")
	{
		m_pMorphoFeature->m_GenderType = Values::GenderType.gtNeutral;
		m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;
		m_pMorphoFeature->m_CaseType = Values::CaseType.ctNominative;
		eal = ealRussian;
	}
	AddMorphoIndex(pUnit,eal);
}

void CUnitChecker::AddPartOfSpeechIndexProper(IUnit* pUnit, IUnit* pSourceUnit)
{
	SS_TRY;

	for(IIndex* pIndex = pSourceUnit->GetFirstIndex(); pIndex; pIndex = pSourceUnit->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitMorphoIndex)
			continue;
		

		 IIndex* pNewIndex = m_pStorage->CreateIndex();
		pNewIndex->GetDictionaryIndex()->AppendIndex(TDictionaryIndex(0, pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()));
		for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
		{
			m_pMorphoFeature->Undefine();
			m_pMorphoConverter->EnCode(	pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber(), 
								pFeature->GetMorphoInfo(), 
								pFeature->GetPartOfSpeech(), 
								m_pMorphoFeature);

			m_pMorphoFeature->m_CommonType.Assign(Values::CommonType.cmtProper);

			int iMorphoInfo = 0;
			int iPartOfSpeech = 0;
			m_pMorphoConverter->Code(pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber(), 
				m_pMorphoFeature, &iMorphoInfo, &iPartOfSpeech);
			IFeature* pNewFeature = m_pStorage->CreateFeature();
			pNewFeature->SetMorphoIndex(0);
			pNewFeature->SetMorphoInfo(iMorphoInfo);
			pNewFeature->SetPartOfSpeech(iPartOfSpeech);
			pNewIndex->AddFeature(pNewFeature);
		}

		pUnit->AddIndex(pNewIndex);
	}

	SS_CATCH(L"");
}

void CUnitChecker::AddPartOfSpeechIndex(IUnit* pUnit, IUnit* pSourceUnit)
{
	SS_TRY;

	for(IIndex* pIndex = pSourceUnit->GetFirstIndex(); pIndex; pIndex = pSourceUnit->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitMorphoIndex)
			continue;

		IIndex* pNewIndex = m_pStorage->CreateIndex();
		pNewIndex->GetDictionaryIndex()->AppendIndex(TDictionaryIndex(0, pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()));
		for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
		{
			IFeature* pNewFeature = m_pStorage->CreateFeature();
			pNewFeature->SetMorphoIndex(pFeature->GetMorphoIndex());
			pNewFeature->SetMorphoInfo(pFeature->GetMorphoInfo());
			pNewFeature->SetPartOfSpeech(pFeature->GetPartOfSpeech());

			pNewIndex->AddFeature(pNewFeature);
		}

		pUnit->AddIndex(pNewIndex);
	}

	SS_CATCH(L"");
}

void CUnitChecker::AddOrganizationIndex(IUnit* pUnit, const TSOrganizationType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtOrganization;
	m_pSemanticFeature->m_SOrganizationType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddServiceTypeIndex(IUnit* pUnit, const TSServiceTypes& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtService;
	m_pSemanticFeature->m_SServiceTypes = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddPlaceIndex(IUnit* pUnit, const TSPlaceType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtPlace;
	m_pSemanticFeature->m_SPlaceType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddBeSemanticIndex(IUnit* pUnit, const TSVBeType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Values::TSemanticType.smtVerb;
	m_pSemanticFeature->m_SVerbType = Values::TSVerbType.semvtBe;
	m_pSemanticFeature->m_SVBeType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddSyntaxCategoryIndex(IUnit* pUnit, const SyntaxCategories& sc)
{
	SS_TRY;

	if(!m_bSyntax)
		return;

	IIndex* pIndex = m_pStorage->CreateIndex();
	pIndex->GetDictionaryIndex()->AppendIndex(sc.GetSingleValue() | ednSyntax << 24);
	pUnit->AddIndex(pIndex);

	SS_CATCH(L"");
}

void CUnitChecker::FillMorphoTypes(IR::CUnit* pUnit)
{
	SS_TRY;

	for(IIndex* pIndex = pUnit->GetUnit()->GetFirstIndex(); pIndex; pIndex = pUnit->GetUnit()->GetNextIndex())
	{
		EIndexType eit = pIndex->GetDictionaryIndex()->GetFirst().GetIndexType();
		if(eit == eitMorphoIndex)
			SetMorphoInfo(pIndex, pUnit);
		if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknownEng  ||
			pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknownRus ||
			pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknown)
		{
			pUnit->GetUnit()->SetUnknownWord(true);
		}
	}

	SS_CATCH(L"");
}

void CUnitChecker::FillSemanticTypes(IR::CUnit* pUnit)
{
	SS_TRY;

	bool b = HasPartOfSpeechType(pUnit->GetUnit(), Values::PartOfSpeechTypes.postOfficial);

	EAnalyseLanguage language = pUnit->GetUnit()->GetFirstIndex()->GetDictionaryIndex()->GetFirst().GetLanguage();
	for(IIndex* pIndex = pUnit->GetUnit()->GetFirstIndex(); pIndex; pIndex = pUnit->GetUnit()->GetNextIndex())
	{
		EIndexType eit = pIndex->GetDictionaryIndex()->GetFirst().GetIndexType();
		if(eit == eitSemanticIndex)
			SetSemanticInfo(pIndex->GetDictionaryIndex()->GetFirst(), pUnit, language, b);
	}

	EWordType type = pUnit->GetType(wmQuarterTo);
	if(type == wtVolume && (_wcsicmp(pUnit->GetUnit()->GetWord(), L"quarter") == 0) )
		pUnit->SetWordType(wtQuarter, wmDates);
	if (_wcsicmp(pUnit->GetUnit()->GetWord(), L"�������") == 0)
		pUnit->SetWordType(wtYearQuarter, wmDates);

	SS_CATCH(L"");
}

void CUnitChecker::ChangeFeature(IUnit* pUnit, EChangeFeature ecf)
{
	SS_TRY;

	if(ecf == cfSetGenitive && !HasPartOfSpeechType(pUnit, Values::PartOfSpeechTypes.postNoun))
		return;

	CFeatureChanger oChanger(m_pStorage, m_pMorphoFeature, m_pMorphoConverter);
	oChanger.ChangeUnitFeature(pUnit, ecf);

	SS_CATCH(L"");
}

void CUnitChecker::RemoveExtremeChildren(IUnit* pParentUnit)
{
	assert(pParentUnit->GetChildCount() >= 2);

	pParentUnit->GetLeftChildUnit()->ReleaseUnitHorizontal();
	pParentUnit->GetRightChildUnit()->ReleaseUnitHorizontal();
}

void CUnitChecker::ClearChildrenSemantics(IUnit* pParentUnit, const TSemanticType& TypeToLeave)
{
	SS_TRY;

	for(IUnit* pUnit = pParentUnit->GetLeftChildUnit(); pUnit; pUnit = pUnit->GetRightUnit())
		ClearSemantics(pUnit, TypeToLeave);

	SS_CATCH(L"");
}

void CUnitChecker::ClearSemantics(IUnit* pUnit, const TSemanticType& TypeToLeave)
{
	SS_TRY;

	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; )
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitSemanticIndex)
		{
			pIndex = pUnit->GetNextIndex();
			continue;
		}

		m_pSemanticFeature->Undefine();
		m_pSemanticConverter->EnCode(pIndex->GetDictionaryIndex()->GetFirst().GetId(), m_pSemanticFeature);

		if(m_pSemanticFeature->m_SemanticType.Equal(TypeToLeave))
			pIndex = pUnit->GetNextIndex();
		else
			pIndex = pIndex->ReleaseIndex();
	}

	SS_CATCH(L"");
}

bool CUnitChecker::CopyIndexes(IUnit* pFrom, IUnit* pTo, const TSemanticType& Type)
{
	SS_TRY;

	bool bCopied = false;
	for(IIndex* pIndex = pFrom->GetFirstIndex(); pIndex; pIndex = pFrom->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitSemanticIndex)
			continue;

		m_pSemanticFeature->Undefine();
		m_pSemanticConverter->EnCode(pIndex->GetDictionaryIndex()->GetFirst().GetId(), m_pSemanticFeature);

		if(m_pSemanticFeature->m_SemanticType.Equal(Type))
		{
			IIndex* pNewIndex = m_pStorage->CreateIndex();
			TDictionaryIndex oInd(pIndex->GetDictionaryIndex()->GetFirst());
			oInd.SetGenericMarker(false);
			pNewIndex->GetDictionaryIndex()->AppendIndex(oInd);
			pTo->AddIndex(pNewIndex);
			bCopied = true;
		}
	}

	return bCopied;

	SS_CATCH(L"");
	return false;
}

IUnit* CUnitChecker::ChildHasCase(IUnit* pParentUnit, const CaseType& Type)
{
	SS_TRY;

	for(IUnit* pUnit = pParentUnit->GetLeftChildUnit(); pUnit; pUnit = pUnit->GetRightUnit())
	{
		if(UnitHasCase(pUnit, Type))
			return pUnit;
	}

	SS_CATCH(L"");
	return NULL;
}


void CUnitChecker::GetChildCases(IUnit* pParentUnit, list<CaseType>& Types)
{
	SS_TRY;

	set<int> Cases;
	
	for(IUnit* pUnit = pParentUnit->GetLeftChildUnit(); pUnit; pUnit = pUnit->GetRightUnit())
	{
		for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitMorphoIndex)
				continue;
			DictionariesNumber edn = pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber();
			for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
			{
	 		 m_pMorphoFeature->Undefine();
	 		 m_pMorphoConverter->EnCode(edn, pFeature->GetMorphoInfo(), pFeature->GetPartOfSpeech(), m_pMorphoFeature);
			 if (Cases.find(m_pMorphoFeature->m_CaseType.GetValue())==Cases.end())
			 {
				 Types.push_back(m_pMorphoFeature->m_CaseType);
				 Cases.insert(m_pMorphoFeature->m_CaseType.GetValue());
			 }
			}
		}
	}
	SS_CATCH(L"");
}

bool CUnitChecker::UnitHasCase(IUnit* pUnit, const CaseType& Type)
{
	SS_TRY;

	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitMorphoIndex)
			continue;

		if(HasCase(pIndex, Type))
			return true;
	}

	SS_CATCH(L"");
	return false;
}

struct CFeature
{
	CFeature(IFeature* p) : pFeature(p)
	{}
	bool operator<(const CFeature& oFeature) const
	{
		bool b = false;
		try
		{
			b = pFeature->GetMorphoInfo() < oFeature.pFeature->GetMorphoInfo() ||
				pFeature->GetPartOfSpeech() < oFeature.pFeature->GetPartOfSpeech();

			bool b1 = pFeature->GetMorphoInfo() > oFeature.pFeature->GetMorphoInfo() ||
				pFeature->GetPartOfSpeech() > oFeature.pFeature->GetPartOfSpeech();
			if (b && b1) b = pFeature->GetMorphoInfo() < oFeature.pFeature->GetMorphoInfo();
		}
		catch(...)
		{
			b = false;
		}

		return	b;
	}
	IFeature* pFeature;
};

void CUnitChecker::CopyFeaturesFromChildren(IUnit* pParentUnit,const Types::PartOfSpeechTypes& PartOfSpeech)
{
	//SS_TRY;

	if(!pParentUnit->HasChilds())
		return;

	typedef set<CFeature> TFeatureSet;

	//typedef list<CFeature> TFeatureList;
	//TFeatureList ltFeatures;
	TFeatureSet stFeatures;


	EAnalyseLanguage eal = ealUndefined;
	for(IUnit* pUnit = pParentUnit->GetLeftChildUnit(); pUnit; pUnit = pUnit->GetRightUnit())
	{
		for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			EAnalyseLanguage ealCurr = pIndex->GetDictionaryIndex()->GetFirst().GetLanguage();
			if(eal != ealUndefined && ealCurr != ealUndefined && eal != ealCurr)
			{
				stFeatures.clear();
	//			ltFeatures.clear();
				break;
			}
			if(ealCurr != ealUndefined)
				eal = ealCurr;

			for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
	//			ltFeatures.push_back(CFeature(pFeature));
				try
				{
					stFeatures.insert(CFeature(pFeature));
				}catch(...)
				{
					continue;
				}

		}
	}

	DictionariesNumber edn = GetChildrenDictionary(pParentUnit, ednUnknown);
	if(stFeatures.empty() || edn == ednUnknown)
	{
		AddPartOfSpeechIndex(pParentUnit, Values::PartOfSpeechTypes.postNoun, 
			Values::CaseType.ctCommon, Values::NumberType.ntSingle);
	}
	else
	{
		IIndex* pIndex = m_pStorage->CreateIndex();
		pIndex->GetDictionaryIndex()->AppendIndex(TDictionaryIndex(0, edn));
		pParentUnit->AddIndex(pIndex);
	
		for(TFeatureSet::iterator it = stFeatures.begin(); it != stFeatures.end(); ++it)
		{
			IFeature* pFeature = m_pStorage->CreateFeature();
			pFeature->SetMorphoIndex(it->pFeature->GetMorphoIndex());
			pFeature->SetMorphoInfo(it->pFeature->GetMorphoInfo());
			pFeature->SetPartOfSpeech(it->pFeature->GetPartOfSpeech());
	        
			m_pMorphoFeature->Undefine();

			int i1 = it->pFeature->GetMorphoInfo();
			int i2 = it->pFeature->GetPartOfSpeech();
			m_pMorphoConverter->EnCode(edn, i1, i2, m_pMorphoFeature);
			if (PartOfSpeech.IsUndefined() || 
				m_pMorphoFeature->m_PartOfSpeechTypes.IsIntersectsWith(&PartOfSpeech))
			{
			   pIndex->AddFeature(pFeature);
			}
		}
	}

	//SS_CATCH(L"");
}

void CUnitChecker::CopyFeaturesFromChildren1(IUnit* pParentUnit)
{
	SS_TRY;

	if(!pParentUnit->HasChilds())
		return;

	typedef set<CFeature> TFeatureSet;
	TFeatureSet stFeatures;

	EAnalyseLanguage eal = ealUndefined;
	DictionariesNumber edn = GetChildrenDictionary(pParentUnit, ednUnknown);
	for(IUnit* pUnit = pParentUnit->GetLeftChildUnit(); pUnit; pUnit = pUnit->GetRightUnit())
	{			
		if (pUnit->HasIndexType(eitSemanticIndex)) // ����� � �������
		{
			IIndex* pIndex = m_pStorage->CreateIndex();
			pIndex->GetDictionaryIndex()->AppendIndex(TDictionaryIndex(0, edn));
			pParentUnit->AddIndex(pIndex);
			for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
			{				
				for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
				{
					IFeature* pFeature1 = m_pStorage->CreateFeature();
					pFeature1->SetMorphoIndex(pFeature->GetMorphoIndex());
					pFeature1->SetMorphoInfo(pFeature->GetMorphoInfo());
					pFeature1->SetPartOfSpeech(pFeature->GetPartOfSpeech());			
					pIndex->AddFeature(pFeature1);
				}				
			}			
		}
		else
		{
			eal = pUnit->GetFirstIndex()->GetDictionaryIndex()->GetFirst().GetLanguage();
			m_pMorphoFeature->Undefine();
			m_pMorphoFeature->m_PartOfSpeechTypes = Values::PartOfSpeechTypes.postNoun;
			m_pMorphoFeature->m_CaseType = Values::CaseType.ctCommon;
			m_pMorphoFeature->m_NumberType = Values::NumberType.ntSingle;
			m_pMorphoFeature->m_CommonType = Values::CommonType.cmtProper;
			AddMorphoIndex(pUnit, eal);						
			break;
		}
	}	

	SS_CATCH(L"");
}

SS::Core::Features::Types::PartOfSpeechTypes CUnitChecker::GetPartOfSpeech(IIndex* pIndex)
{
	SS_TRY;

	IFeature* pFeature = pIndex->GetFirstFeature();
	if(!pFeature)
		return Values::PartOfSpeechTypes.Undefined;

	m_pMorphoFeature->Undefine();
	m_pMorphoConverter->EnCode(	pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber(), 
								pFeature->GetMorphoInfo(), 
								pFeature->GetPartOfSpeech(), 
								m_pMorphoFeature);
	return m_pMorphoFeature->m_PartOfSpeechTypes;

	SS_CATCH(L"");
	return Values::PartOfSpeechTypes.Undefined;
}

bool CUnitChecker::HasSyntaxCategory(IUnit* pUnit, const SyntaxCategories& sc)
{
	SS_TRY;

	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitSyntaxIndex)
			continue;

		unsigned int uiIndex = pIndex->GetDictionaryIndex()->GetFirst().GetId();
		if(uiIndex == sc.GetSingleValue())
			return true;
	}

	SS_CATCH(L"");
	return false;
}

bool CUnitChecker::HasPartOfSpeechType(IUnit* pUnit, const PartOfSpeechTypes& Type)
{
	SS_TRY;

	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		if(GetPartOfSpeech(pIndex).Equal(Type))
			return true;
	}

	SS_CATCH(L"");
	return false;
}

bool CUnitChecker::IsOrdinal(IUnit* pUnit)
{
	SS_TRY;

	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		DictionariesNumber edn = pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber();
		if(edn == ednOrderingEnglish || edn == ednOrderingRussian)
			return true;
	}

	SS_CATCH(L"");
	return false;
}

IUnit* CUnitChecker::SetKeywordSyntax(IUnit* pUnit)
{
	SS_TRY;

	bool bVerb = HasPartOfSpeechType(pUnit, Values::PartOfSpeechTypes.postVerb),
		 bNoun = HasPartOfSpeechType(pUnit, Values::PartOfSpeechTypes.postNoun);
	if(!bVerb && !bNoun)
		return NULL;

	CTextCopy oCopy(m_pStorage);
	IUnit* pClone = oCopy.CopyUnit(pUnit);
	ISyntaxFeature* pFeature = pClone->CreateSyntaxFeature();
	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() != eitSemanticIndex)
			continue;

		m_pSemanticFeature->Undefine();
		m_pSemanticConverter->EnCode(pIndex->GetDictionaryIndex()->GetFirst().GetId(), m_pSemanticFeature);
		if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtTimeInterval))
		{
			pFeature->SetIsQuestion();
			pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeFixedPoint);
			pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeDuration);
			pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeEnd);
			pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeSource);
		}
		else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtInfo))
		{
			pFeature->SetIsQuestion();
			pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAdditionalEntity);
		}
		else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtMeasure))
		{
			pFeature->SetIsQuestion();
			pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctMeasure);
		}
		else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtVerb))
		{
			if(	m_pSemanticFeature->m_SVerbType.Equal(Values::TSVerbType.semvtWeigh) ||
				m_pSemanticFeature->m_SVerbType.Equal(Values::TSVerbType.semvtCost))
			{
				pFeature->SetIsQuestion();
				pFeature->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctMeasure);
			}
		}
	}
	if(pClone->GetSyntaxFeature()->IsQuestion())
		return pClone;
	pClone->ReleaseUnitHorizontal();

	SS_CATCH(L"");
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////
// CUnitChecker functions


void CUnitChecker::SetSemanticInfo(TDictionaryIndex oIndex, IR::CUnit* pUnit, EAnalyseLanguage language, bool isOfficial)
{
	SS_TRY;
	//pUnit->GetUnit()->GetL

	UINT idSource = oIndex.GetId();
	
	m_pSemanticFeature->Undefine();
	m_pSemanticConverter->EnCode(idSource, m_pSemanticFeature);
	
	if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtTimeInterval))
	{
		if(m_pSemanticFeature->m_STimeIntervalType.Equal(Values::TSTimeIntervalType.semtitDateDay))
			pUnit->SetWordType((pUnit->GetType(wmDates) == wtMeasureDay) ? wtMeasureDay : wtWordDay, wmDates);
		else if(m_pSemanticFeature->m_STimeIntervalType.Equal(Values::TSTimeIntervalType.semtitDateMonth))
		{
			wstring word = pUnit->GetUnit()->GetWord();
			if ((language == ealRussian) || (!word.empty() && iswupper(word[0])))
				pUnit->SetWordType((pUnit->GetType(wmDates) == wtMeasureDay) ? wtMeasureMonth : wtMonth, wmDates);
		}
		else if(m_pSemanticFeature->m_STimeIntervalType.Equal(Values::TSTimeIntervalType.semtitDateYear))
			pUnit->SetWordType(wtWordYear, wmDates);
		else if(m_pSemanticFeature->m_STimeIntervalType.Equal(Values::TSTimeIntervalType.semtitCentury))
			pUnit->SetWordType(wtWordCentury, wmDates);
		else if(m_pSemanticFeature->m_STimeIntervalType.Equal(Values::TSTimeIntervalType.semtitDayTime))
			pUnit->SetWordType(wtWordDayTime, wmDates);
		else if(pUnit->GetTypeStrict(wmDates) == wtUndefined)
			//&& m_pSemanticFeature->m_STimeIntervalType.Equal(Values::TSTimeIntervalType.semtitIndef)		
			pUnit->SetWordType(wtWordDecade, wmDates);
	}
	else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtPerson))
	{
		if(m_pSemanticFeature->m_SPersonType.IsContain(Values::TSPersonType.semprstLastName)||
			m_pSemanticFeature->m_SPersonType.Equal(Values::TSPersonType.Undefined))
			pUnit->SetWordType((pUnit->GetType(wmNames) == wtFName) ? wtName : wtLName, wmNames);
		else 
		if(m_pSemanticFeature->m_SPersonType.Equal(Values::TSPersonType.semprstFirstName))
			pUnit->SetWordType((pUnit->GetType(wmNames) == wtLName) ? wtName : wtFName, wmNames);
		else if(m_pSemanticFeature->m_SPersonType.Equal(Values::TSPersonType.semprstMiddleName))			
			pUnit->SetWordType(wtMName, wmNames);

		if (m_pSemanticFeature->m_SPersonType.Equal(Values::TSPersonType.semprstProfession))
		{
			pUnit->SetWordType(wtNounSeqRoot, wmInSequences);
		}		
	}
	else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtOrganization))
	{
		if(oIndex.GetGenericMarker())
			pUnit->SetWordType(wtOrg, wmOrganizations);
		else
			if (pUnit->GetType(wmOrganizations)!=wtOrg &&
				pUnit->GetType(wmOrganizations)!=wtOrgAbbr) pUnit->SetWordType(wtSpecificOrg, wmOrganizations);
		pUnit->SetWordType(wtNounSeqRoot, wmInSequences);		
	}
	else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtPlace))
	{
		//if  (pUnit->GetType(wmLSequences)!=wtLWord)
		//pUnit->SetWordType(wtUndefined, wmLSequences);
		/*if(m_pSemanticFeature->m_SPlaceType.Equal(Values::TSPlaceType.pltCity))
		{
			if(pUnit->GetType(wmPlaces) == wtState)
				pUnit->SetWordType(wtCityState, wmPlaces);
			else
				pUnit->SetWordType(wtCity, wmPlaces);
		}
		else if(m_pSemanticFeature->m_SPlaceType.Equal(Values::TSPlaceType.pltState))
		{
			if(pUnit->GetType(wmPlaces) == wtCity)
				pUnit->SetWordType(wtCityState, wmPlaces);
			else
				pUnit->SetWordType(wtState, wmPlaces);
		}
		else if(m_pSemanticFeature->m_SPlaceType.Equal(Values::TSPlaceType.pltProvince))
			pUnit->SetWordType(wtState, wmPlaces);
		else if(m_pSemanticFeature->m_SPlaceType.Equal(Values::TSPlaceType.pltCountry))
			pUnit->SetWordType(wtCountry, wmPlaces);
		else */
		if(m_pSemanticFeature->m_SPlaceType.Equal(Values::TSPlaceType.pltPrision))
			pUnit->SetWordType(wtOrg, wmOrganizations);

		wstring wstr = pUnit->GetUnit()->GetWord();
		if (!isOfficial && pUnit->GetType(wmPlaces)!=wtProperName && pUnit->GetType(wmPlaces)!=wtProperNameUnknown && wstr.size()>0 &&
			!oIndex.GetFirstLetterUpperCase())		
			pUnit->SetWordType(wtWord, wmPlaces);
		else if (wstr.size()==0) pUnit->SetWordType(wtUndefined, wmPlaces);
		

		int id = oIndex.GetId();				
	}
	else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtMeasure))
	{
		if(m_pSemanticFeature->m_SMeasureType.Equal(Values::TSMeasureType.msrtTime))
		{
			EWordType eType = pUnit->GetTypeStrict(wmDates);
			if(eType == wtMonth)
				pUnit->SetWordType(wtMeasureMonth, wmDates);
			else if(eType == wtUndefined || eType == wtWordDay)
				pUnit->SetWordType(wtMeasureDay, wmDates);
		}
		else if(m_pSemanticFeature->m_SMeasureType.Equal(Values::TSMeasureType.msrtVolume))
		{
			pUnit->SetWordType(wtVolume, wmQuarterTo);
			pUnit->SetWordType(wtVolume, wmDates);
		}
	}
	else if(m_pSemanticFeature->m_SemanticType.Equal(Values::TSemanticType.smtInfo))
	{
		if(m_pSemanticFeature->m_SInfoTypes.Equal(Values::TSInfoType.smtInfoTelefon))
			pUnit->SetWordType(wtTelephoneWord, wmTelephones);
	}

	SS_CATCH(L"");
}

//bool CUnitCheckert::IsSemantic(IUnit* pUnit, SS::Core::Features::Types::TSemanticType semType)
//	{
//		SS::Interface::Core::BlackBox::IIndex* pIndex;
//		SS::Interface::Core::BlackBox::IDictionaryIndex* pDictionaryIndex;
//		SS::Interface::Core::BlackBox::EIndexType oIndexType;
//			
//		for(pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
//		{
//			pDictionaryIndex = pIndex->GetDictionaryIndex();
//			
//			if(pDictionaryIndex)
//			{
//				SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex = pDictionaryIndex->GetFirst();
//				oIndexType = oDictionaryIndex.GetIndexType();
//				if (oIndexType==SS::Interface::Core::BlackBox::eitSemanticIndex)
//				{							
//					int index = oDictionaryIndex.GetDictionaryIndex();
//					SS::Core::Features::CSemanticFeature oSemanticFeature;							
//   					m_pSemanticConverter->EnCode(index, &oSemanticFeature);					
//					if (oSemanticFeature.m_SemanticType.IsContain(semType))						
//					{
//						return true;
//					}
//				}
//			}
//		}
//
//		return false;
//	}	

void CUnitChecker::SetMorphoInfo(IIndex* pIndex, IR::CUnit* pUnit)
{
	SS_TRY
	{
		wstring str = pUnit->GetUnit()->GetWord();
		int isPoint = str.find(L".");
		DictionariesNumber edn = pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber();
		bool isNoun = false;
		for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
		{
			m_pMorphoFeature->Undefine();
			m_pMorphoConverter->EnCode(edn, pFeature->GetMorphoInfo(), pFeature->GetPartOfSpeech(), m_pMorphoFeature);
			if(pUnit->GetType(wmDefault) == wtLWord && m_pMorphoFeature->m_CaseType.Equal(Values::CaseType.ctGenitive))
				pUnit->SetWordType(wtGenitive, wmOrganizations, false);

			if(m_pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun))
			{
				isNoun = true;
			}

			if (!pIndex->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase() &&
				isNoun &&
				m_pMorphoFeature->m_CaseType.IsIntersectsWithout(&Values::CaseType.ctGenitive) &&
				m_pMorphoFeature->m_AnimInAnimType.Equal(SS::Core::Features::Values::AnimInAnimType.aiaInanimation))
			{
				//if (pUnit->GetType(wmInSequences)==wtDativeNoun)
					pUnit->SetWordType(wtDativeAndGenNoun, wmInSequences);
				//else
				//	pUnit->SetWordType(wtGenetiveNoun, wmInSequences);
			}

			if (!pIndex->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase() &&
				isNoun &&
				m_pMorphoFeature->m_CaseType.IsIntersectsWithout(&Values::CaseType.ctDative) &&
				m_pMorphoFeature->m_AnimInAnimType.Equal(SS::Core::Features::Values::AnimInAnimType.aiaInanimation))
			{
				//if (pUnit->GetType(wmInSequences)==wtGenetiveNoun)
					pUnit->SetWordType(wtDativeAndGenNoun, wmInSequences);
				//else
				//	pUnit->SetWordType(wtDativeNoun, wmInSequences);
				
			}

			if (!pIndex->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase() &&
				m_pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postAdjective) &&
				m_pMorphoFeature->m_CaseType.IsIntersectsWithout(&Values::CaseType.ctGenitive))
			{
				pUnit->SetWordType(wtDativeAndGenAdj, wmInSequences);
			}

			if (!pIndex->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase() &&
				m_pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postAdjective) &&
				m_pMorphoFeature->m_CaseType.IsIntersectsWithout(&Values::CaseType.ctDative))
			{
				pUnit->SetWordType(wtDativeAndGenAdj, wmInSequences);			
			}

			if(m_pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNumeric))
			{
				pUnit->SetTag(pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryIndex());
				pUnit->SetWordType(wtNumber, wmNumberSemantic);
				pUnit->SetWordType(wtNumber, wmLSequences);
			}
			else if(m_pMorphoFeature->m_OfficialType.Equal(Values::OfficialType.otDeterminers))
				pUnit->SetWordType(wtWord, wmLSequences);
			else if(m_pMorphoFeature->m_OfficialType.Equal(Values::OfficialType.otConjunction))
				pUnit->SetTag(pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryIndex());
			
			if(m_pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postVerb) && isPoint<0 &&
				!m_pMorphoFeature->m_VerbForm.Equal(Values::VerbForm.vfParticiple) &&
				!m_pMorphoFeature->m_VerbForm.Equal(Values::VerbForm.vfDeepr) &&
				 m_pMorphoFeature->m_VerbType.IsUndefined()
				)
			{
				pUnit->SetWordType(wtVerb, wmQuotations);
			}else 
				if (pIndex->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase())
				{
				  pUnit->SetWordType(wtProperName, wmQuotations);
				  pUnit->SetWordType(wtProperName, wmMultiNames);

				  if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknownRus ||
					  IsAdjectiveEvrisctic(pUnit->GetUnit()))
				  {
					  pUnit->SetWordType(wtProperName, wmOrganizations);
				  }
				
				  if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknownRus)
					  //pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::edn ||)
				     pUnit->SetWordType(wtWord, wmPlaces);
				  else
					  if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednRProperName)
						 pUnit->SetWordType(wtProperName, wmPlaces);
				}	


		}
	//	if (isNoun) pUnit->SetWordType(wt, wmQuotations);
	}
	SS_CATCH(L"");
}

void CUnitChecker::AddSemanticIndex(IUnit* pUnit, const TSemanticType& Type)
{
	if(!m_bSemantic)
		return;

	m_pSemanticFeature->Undefine();
	m_pSemanticFeature->m_SemanticType = Type;
	AddSemanticIndex(pUnit);
}

void CUnitChecker::AddSemanticIndex(IUnit* pUnit)
{
	SS_TRY;

	SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex;
	m_pSemanticConverter->Code(m_pSemanticFeature, &oDictionaryIndex);

	if(!oDictionaryIndex.GetDictionaryIndex())
	{
		SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������������� ��������� ������ ������� ������������� ������");
		return;
	}

	IIndex* pIndex = m_pStorage->CreateIndex();
	oDictionaryIndex.SetDictionaryNumber(ednSemantic);
	pIndex->GetDictionaryIndex()->AppendIndex(oDictionaryIndex);
	pUnit->AddIndex(pIndex);

	SS_CATCH(L"");
}

void CUnitChecker::AddMorphoIndex(IUnit* pUnit,EAnalyseLanguage eal)
{
	SS_TRY;

	DictionariesNumber ednDefault = ednENominalName;

	wstring str = pUnit->GetWord();	 

	if (!str.empty() && _istupper(str[0]))
	{
		if (eal==ealRussian || eal==ealUndefined)
			ednDefault = ednRProperName;
		else
			ednDefault = ednEProperName;
	}
	else if (eal==ealRussian || eal==ealUndefined)
		ednDefault = ednRNominalName;
	else
		ednDefault = ednENominalName;


	DictionariesNumber edn = GetChildrenDictionary(pUnit, ednDefault);

	int iMorphoInfo = 0, iPartOfSpeech = 0;
	m_pMorphoConverter->Code(edn, m_pMorphoFeature, &iMorphoInfo, &iPartOfSpeech);
	if(iMorphoInfo || iPartOfSpeech)
	{
		IFeature* pFeature = m_pStorage->CreateFeature();
		pFeature->SetMorphoIndex(0);
		pFeature->SetMorphoInfo(iMorphoInfo);
		pFeature->SetPartOfSpeech(iPartOfSpeech);

		IIndex* pIndex = m_pStorage->CreateIndex();
		pIndex->AddFeature(pFeature);
		

		if (!str.empty() && _istupper(str[0])) 
			pIndex->GetDictionaryIndex()->AppendIndex((edn << 24) + (unsigned int)(1<<31));
		else 
			pIndex->GetDictionaryIndex()->AppendIndex((edn << 24));

		pUnit->AddIndex(pIndex);
	}

	SS_CATCH(L"");
}

bool CUnitChecker::HasCase(IIndex* pIndex, const CaseType& Type)
{
	SS_TRY;

	assert(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() == eitMorphoIndex);

	DictionariesNumber edn = pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber();
	for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
	{
		m_pMorphoFeature->Undefine();
		m_pMorphoConverter->EnCode(edn, pFeature->GetMorphoInfo(), pFeature->GetPartOfSpeech(), m_pMorphoFeature);
		if(m_pMorphoFeature->m_CaseType.Equal(Type))
			return true;
	}

	SS_CATCH(L"");
	return false;
}

DictionariesNumber CUnitChecker::GetChildrenDictionary(IUnit* pParent, DictionariesNumber ednDefault)
{
	SS_TRY;

	for(IUnit* pChild = pParent->GetLeftChildUnit(); pChild; pChild = pChild->GetRightUnit())
	{
		if (!pChild->IsInitial() && this->HasSemantic1(pChild, SS::Core::Features::Values::TSemanticType.smtTimeInterval))
			continue; // ���� � ������������ �������� ��������� �� ����
		for(IIndex* pChildIndex = pChild->GetFirstIndex(); pChildIndex; pChildIndex = pChild->GetNextIndex())
		{
			if(pChildIndex->GetDictionaryIndex()->GetFirst().GetLanguage() != ealUndefined)
				return pChild->GetFirstIndex()->GetDictionaryIndex()->GetFirst().GetDictionaryNumber();
		}
	}

	SS_CATCH(L"");
	return ednDefault;
}

bool CUnitChecker::isXZ(IUnit* pUnit)
{
	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknownRus ||
			pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednUnknownEng)
		{
			return true;
		}
	}
	return false;
}

bool CUnitChecker::IsAdjectiveEvrisctic(IUnit* pUnit)
{
	wstring str = pUnit->GetWord();
	if (str.size()<5) return false;
	wstring str1 = str.substr(str.size()-4, 4);
	wstring str2 = str.substr(str.size()-3, 3);
	if (str1==L"����" || str1==L"����" || str1==L"����" || str1==L"����" ||str1==L"����" ||str1==L"����" || str1==L"����" || str1==L"����" ||
		str1==L"����" || str2==L"���" || str2==L"���" || str1==L"����" || str2==L"���" || str2==L"���" || str2==L"���" || str2==L"���" ||
		str1==L"����" || str1==L"����" || str1==L"����" || str1==L"����")
	{
		return true;
	}else return false;
}

void CUnitChecker::AddRusLastNameIndexEvrisctic(IUnit* pUnit)
{
	SMIList forms;

	IUnit* prevUnit = pUnit->GetLeftUnit();
	/*bool b = true;
	if (prevUnit==NULL || pUnit->GetFirstIndex()->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase()==0)
		b = false;*/

	

	if (!isXZ(pUnit) || this->HasSemantic1(pUnit,SS::Core::Features::Values::TSemanticType.smtPerson,
		SS::Core::Features::Values::TSPersonType.semprstLastName) ||
		!pUnit->GetFirstIndex()->GetDictionaryIndex()->GetFirst().GetFirstLetterUpperCase()==1) return;

	GetRusLNForms(pUnit, forms);

	for(SMIList::iterator it = forms.begin(); it!=forms.end(); it++)
	{
		SMorphoInfo smi = *it;
		this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postNoun,
			smi.caseType, Values::NumberType.ntSingle,
			smi.genType, SS::Core::Types::ealRussian);		
	}

	if (forms.size()!=0)
	{
		this->AddPersonIndex(pUnit,SS::Core::Features::Values::TSPersonType.semprstLastName);
		pUnit->SetEvristicLN(true);
	}

}

void CUnitChecker::AddAdjectiveIndexEvrisctic(IUnit* pUnit)
{
	//if (isXZ(pUnit)) // ����������� �����
	if (!this->HasPartOfSpeechType(pUnit, Values::PartOfSpeechTypes.postAdjective))
	{
		wstring str = pUnit->GetWord();
		if (str.size()<5) return;
		wstring str1 = str.substr(str.size()-4, 4);
		if (str1==L"����" || str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctNominative, Values::NumberType.ntSingle,
				Values::GenderType.gtMasculine, SS::Core::Types::ealRussian);
			
		}else 
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctGenitive, Values::NumberType.ntSingle,
				Values::GenderType.gtMasculine, SS::Core::Types::ealRussian);
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctAccusative, Values::NumberType.ntSingle,
				Values::GenderType.gtMasculine,SS::Core::Types::ealRussian);
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctGenitive, Values::NumberType.ntSingle,
				Values::GenderType.gtNeutral,SS::Core::Types::ealRussian);
			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctDative, Values::NumberType.ntSingle,
				Values::GenderType.gtMasculine,SS::Core::Types::ealRussian);
			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctLocative, Values::NumberType.ntSingle,
				Values::GenderType.gtMasculine,SS::Core::Types::ealRussian);
			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctInstrumental, Values::NumberType.ntSingle,
				Values::GenderType.gtMasculine,SS::Core::Types::ealRussian);
			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctNominative, Values::NumberType.ntSingle,
				Values::GenderType.gtFemale,SS::Core::Types::ealRussian);
			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctGenitive, Values::NumberType.ntSingle,
				Values::GenderType.gtFemale,SS::Core::Types::ealRussian);
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctDative, Values::NumberType.ntSingle,
				Values::GenderType.gtFemale,SS::Core::Types::ealRussian);	
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctInstrumental, Values::NumberType.ntSingle,
				Values::GenderType.gtFemale,SS::Core::Types::ealRussian);	
			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctAccusative, Values::NumberType.ntSingle,
				Values::GenderType.gtFemale,SS::Core::Types::ealRussian);	
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctLocative, Values::NumberType.ntSingle,
				Values::GenderType.gtFemale,SS::Core::Types::ealRussian);			
		}
		else
		if (str1==L"����")
		{
			this->AddPartOfSpeechIndex(pUnit, Values::PartOfSpeechTypes.postAdjective,
				Values::CaseType.ctNominative, Values::NumberType.ntSingle,
				Values::GenderType.gtNeutral,SS::Core::Types::ealRussian);			
		}		
	}
}

void CUnitChecker::GetRusLNForms(SS::Interface::Core::BlackBox::IUnit *pUnit, SMIList& forms)
 {
	wstring str= pUnit->GetWord();
	
	for(int i=0;i<nSuffixCount; i++)
	{
		SRusLNSuffixInfo sinfo = sRusLNSiffixes[i];
		wstring curSuffix = L"";
		for(int j = str.size()-1; j>=0; j--)
		{
			curSuffix = str[j] + curSuffix;
			if (curSuffix==sinfo.suffix)
			{
				SMorphoInfo smi;
				smi.caseType.Undefine(); smi.genType.Undefine();
				smi.caseType.Assign(sinfo.caseType);
				smi.genType.Assign(sinfo.genType);				
				forms.push_back(smi);
			}
		}
	}	
 }

bool CUnitChecker::IsRusLNForms(SS::Interface::Core::BlackBox::IUnit *pUnit)
{
	SMIList list;
	GetRusLNForms(pUnit, list);
	return list.size() > 0;
}

bool CUnitChecker::IsProper(SS::Interface::Core::BlackBox::IUnit *pUnit)
{
	bool isProper = false;
	wstring word = pUnit->GetWord();
	if (!word.empty())
	{
		for(IIndex *pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			TDictionaryIndex index = pIndex->GetDictionaryIndex()->GetFirst();
			TDictNumber number = index.GetDictionaryNumber();
			if ((index.GetIndexType() == eitMorphoIndex) &&
				((number == SS::Dictionary::DATA_TYPE::NAMES::ednRProperName) ||
				(number == SS::Dictionary::DATA_TYPE::NAMES::ednEProperName)))
			{
				isProper = true;
				break;
			}
		}
	}
	return isProper;
}

void CUnitChecker::GetMorpho(IUnit *pUnit, SS::Core::Features::CMorphoFeature& resMorphoFeature)
{
	resMorphoFeature.Undefine();
	SS::Interface::Core::BlackBox::IIndex* pIndex;
	SS::Interface::Core::BlackBox::IDictionaryIndex* pDictionaryIndex;		

	bool first = true;
	wstring value = pUnit->GetWord();
	for(pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		pDictionaryIndex = pIndex->GetDictionaryIndex();

		if(pDictionaryIndex)
		{
			SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex = pDictionaryIndex->GetFirst();
			SS::Interface::Core::BlackBox::EIndexType oIndexType;
			oIndexType = oDictionaryIndex.GetIndexType();	

			if ((oIndexType == SS::Interface::Core::BlackBox::eitMorphoIndex) ||
				(value.empty() && (oIndexType == SS::Interface::Core::BlackBox::eitCombinatoryIndex)))
			{
				for(IFeature * pFeature = pIndex->GetFirstFeature();pFeature; pFeature = pIndex->GetNextFeature())
				{
					SS::Core::Features::CMorphoFeature oMorphoFeature;											

					m_pMorphoConverter->EnCode(oDictionaryIndex.GetDictionaryNumber(), 
						pFeature->GetMorphoInfo(),
						pFeature->GetPartOfSpeech(), &oMorphoFeature);

					resMorphoFeature.m_GenderType.AssignOR(&oMorphoFeature.m_GenderType, first);
					resMorphoFeature.m_NumberType.AssignOR(&oMorphoFeature.m_NumberType, first);
					resMorphoFeature.m_PartOfSpeechTypes.AssignOR(&oMorphoFeature.m_PartOfSpeechTypes, first);
					resMorphoFeature.m_OfficialType.AssignOR(&oMorphoFeature.m_OfficialType, first);
					resMorphoFeature.m_CaseType.AssignOR(&oMorphoFeature.m_CaseType, first);
					first = false;
				}
			}
		} // if (pDictionaryIndex)
	} // ���� �� ��������
}

}
}
