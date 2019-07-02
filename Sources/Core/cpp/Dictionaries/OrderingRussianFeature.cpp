#include "stdafx.h"
#include "OrderingRussianFeature.h"

using namespace SS::Core::Features;
using namespace std;


namespace SS
{
namespace Dictionary
{
namespace Virtual
{

/////////////////////////////////////////////////////////////////////////////////////
// Static members


struct SRusOrderingSuffix
{
	TIDForm idForm;
	LPCWSTR szSuffix;
};

static const SRusOrderingSuffix s_rgSuffix[] = 
{
	0, L"���",
	1, L"��",
	2, L"�",
	3, L"�",
	4, L"��",
	5, L"�",
	6, L"��",
	7, L"�",
	8, L"��",
	9, L"���",
	10, L"��",
	11, L"��",
	12, L"��",
	13, L"��",
	14, L"�",
	15, L"�",
	16, L"��",
	17, L"���",
	18, L"���",
	19, L"��",
	20, L"��",
	21, L"�",
	22, L"��",
	23, L"���",
	24, L"��",
	25, L"��",
	26, L"��",
	27, L"��",
	28, L"��",
	29, L"���",
	30, L"��",
	31, L"��",
	32, L"��",
	33, L"��",
	34, L"��",
	35, L"��",
};

static const SOrderingFeature s_Types_491[] = 
{
	0, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	4, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	6, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	8, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	14, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	15, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	25, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	25, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	26, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	26, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	27, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
};

static const SOrderingFeature s_Types_490[] = 
{
	0, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	4, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	6, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	8, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	15, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	25, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	25, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	26, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	26, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	27, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
};

static const SOrderingFeature s_Types_511[] = 
{
	0, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	4, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	6, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	8, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	14, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	15, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	25, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	25, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	27, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	34, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
};

static const SOrderingFeature s_Types_510[] = 
{
	0, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	4, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	6, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	8, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	14, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	15, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	25, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	25, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	26, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	26, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	27, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	34, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
};

static const SOrderingFeature s_Types_512[] = 
{
	1, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	1, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	1, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	2, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	2, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	3, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	3, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	4, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	9, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	9, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	9, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	11, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	13, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	15, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	17, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	17, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	18, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	19, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	19, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	22, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	24, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	24, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	31, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	31, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	32, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	32, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	32, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	33, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	33, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	35, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	35, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	35, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	35, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
};

static const SOrderingFeature s_Types_513[] = 
{
	0, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	3, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	4, Values::CaseType.ctInstrumental, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	5, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	6, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	7, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	8, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctGenitive, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctDative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	10, Values::CaseType.ctLocative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	12, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	14, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	14, Values::CaseType.ctAccusative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	15, Values::CaseType.ctNominative, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctNominative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	16, Values::CaseType.ctAccusative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	20, Values::CaseType.ctLocative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	21, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctGenitive, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	23, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaAnimation, 
	25, Values::CaseType.ctNominative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	25, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaInanimation, 
	26, Values::CaseType.ctNominative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	26, Values::CaseType.ctAccusative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.aiaInanimation, 
	27, Values::CaseType.ctInstrumental, Values::GenderType.gtFemale, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctInstrumental, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	28, Values::CaseType.ctDative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	29, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctGenitive, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctLocative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.Undefined, 
	30, Values::CaseType.ctAccusative, Values::GenderType.Undefined, Values::NumberType.ntPlural, Values::AnimInAnimType.aiaAnimation, 
	34, Values::CaseType.ctDative, Values::GenderType.gtMasculine, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
	34, Values::CaseType.ctDative, Values::GenderType.gtNeutral, Values::NumberType.ntSingle, Values::AnimInAnimType.Undefined, 
};


/////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////////////

COrderingRussianFeature::COrderingRussianFeature()
{
}

COrderingRussianFeature::~COrderingRussianFeature()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// COrderingRussianFeature interface

void COrderingRussianFeature::Init(IAMConverterMorpho* pAMConverter)
{
	SS_TRY;

	InitVect(&m_vFeatures_490, (SOrderingFeature*) s_Types_490, APL_ARRSIZE(s_Types_490), pAMConverter);
	InitVect(&m_vFeatures_491, (SOrderingFeature*) s_Types_491, APL_ARRSIZE(s_Types_491), pAMConverter);
	InitVect(&m_vFeatures_511, (SOrderingFeature*) s_Types_511, APL_ARRSIZE(s_Types_511), pAMConverter);
	InitVect(&m_vFeatures_510, (SOrderingFeature*) s_Types_510, APL_ARRSIZE(s_Types_510), pAMConverter);
	InitVect(&m_vFeatures_512, (SOrderingFeature*) s_Types_512, APL_ARRSIZE(s_Types_512), pAMConverter);
	InitVect(&m_vFeatures_513, (SOrderingFeature*) s_Types_513, APL_ARRSIZE(s_Types_513), pAMConverter);

	SS_CATCH(L"");
}

TConvFeatureList* COrderingRussianFeature::GetConvertedFeature(TIDForm idForm, UINT uiValue)
{
	SS_TRY;

	int iLastDigit = uiValue - uiValue / 10 * 10;
    if(iLastDigit != uiValue)
    {
        uiValue /= 10;
        int iPrevLastDigit = uiValue - uiValue / 10 * 10;
        if(iPrevLastDigit == 1)
            iLastDigit += 10;
    }
	if(iLastDigit == 1)
		return &m_vFeatures_510[idForm];
	else if(iLastDigit == 2 || iLastDigit == 6 || iLastDigit == 7 || iLastDigit == 8 || uiValue == 40 || uiValue == 0)
		return &m_vFeatures_511[idForm];
	else if(iLastDigit == 3)
		return &m_vFeatures_512[idForm];
	else if(uiValue == 300 || uiValue == 400 || uiValue == 500 || uiValue == 600 || uiValue == 700 || uiValue == 800 || uiValue == 900)
		return &m_vFeatures_490[idForm];
	else if(uiValue == 200)
		return &m_vFeatures_491[idForm];
	else
		return &m_vFeatures_513[idForm];

	SS_CATCH(L"");
	return NULL;
}

LPCWSTR COrderingRussianFeature::GetSuffix(TIDForm idForm)
{
	SS_TRY;

	if(idForm >= APL_ARRSIZE(s_rgSuffix))
		return NULL;
	return s_rgSuffix[idForm].szSuffix;

	SS_CATCH(L"");
	return NULL;
}

TIDForm COrderingRussianFeature::GetIDForm(LPCWSTR szSuffix)
{
	SS_TRY;

	for(int i = 0; i < APL_ARRSIZE(s_rgSuffix); i++)
	{
		if(wcsicmp(szSuffix, s_rgSuffix[i].szSuffix) == 0)
			return s_rgSuffix[i].idForm;
	}

	SS_CATCH(L"");
	return -1;
}

int COrderingRussianFeature::GetSuffixCount()
{
	return APL_ARRSIZE(s_rgSuffix);
}

/////////////////////////////////////////////////////////////////////////////////////
// COrderingRussianFeature functions

void COrderingRussianFeature::InitVect(TFeatureVect* pVect, SOrderingFeature* rgFeatures, int iCount, IAMConverterMorpho* pAMConverter)
{
	SS_TRY;

	pVect->resize(APL_ARRSIZE(s_rgSuffix));
	for(int i = 0; i < iCount; i++)
	{
		const SOrderingFeature* pFeature = &rgFeatures[i];

		m_oMorphoFeature.Undefine();
		m_oMorphoFeature.m_PartOfSpeechTypes.Assign(Values::PartOfSpeechTypes.postNumeric);   
		m_oMorphoFeature.m_NumericType.Assign(Values::NumericType.ntOrdering);
		m_oMorphoFeature.m_CaseType = pFeature->ct;
		m_oMorphoFeature.m_GenderType = pFeature->gt;
		m_oMorphoFeature.m_NumberType = pFeature->nt;
		m_oMorphoFeature.m_AnimInAnimType = pFeature->at;

		SConvertedFeature oConv = { 0, 0 };
		pAMConverter->Code(DATA_TYPE::NAMES::ednOrderingRussian, &m_oMorphoFeature, 
			&oConv.iMorphoInfo, &oConv.iSpecialMorpho);

		pVect->at(pFeature->idForm).push_back(oConv);
	}

	SS_CATCH(L"");
}

}
}
}
