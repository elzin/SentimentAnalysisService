#pragma once

#include "MapFeature.h"
#include "PercentFeature.h"
#include "MapMacro.h"
#include "IntegerMacro.h"
#include "BitSize.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Types
			{

class PartOfSpeechTypesType;
typedef CMapFeature<8, 8, PartOfSpeechTypesType> PartOfSpeechTypes;
class PartOfSpeechTypesType
	: public CBaseType
{
public:
	PartOfSpeechTypes Undefined;
	PartOfSpeechTypes postOfficial;
	PartOfSpeechTypes postVerb;
	PartOfSpeechTypes postNoun;
	PartOfSpeechTypes postAdjective;
	PartOfSpeechTypes postNumeric;
	PartOfSpeechTypes postAdverb;
	PartOfSpeechTypes postPronoun;
	PartOfSpeechTypesType(void)
		: Undefined(0)
		, postOfficial(1)
		, postVerb(2)
		, postNoun(3)
		, postAdjective(4)
		, postNumeric(5)
		, postAdverb(6)
		, postPronoun(7)
	{
	}

	~PartOfSpeechTypesType(void){};

	unsigned int GetValueCount(void) const {return 8;};

	const char* GetTypeName() const {return "PartOfSpeechTypes";};

	const char* GetTypeDescription() const {return "����� ����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "postOfficial";
		case 2: return "postVerb";
		case 3: return "postNoun";
		case 4: return "postAdjective";
		case 5: return "postNumeric";
		case 6: return "postAdverb";
		case 7: return "postPronoun";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "���������";
		case 2: return "������";
		case 3: return "���������������";
		case 4: return "��������������";
		case 5: return "������������";
		case 6: return "�������";
		case 7: return "�����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class OfficialTypeType;
typedef CMapFeature<8, 11, OfficialTypeType> OfficialType;
class OfficialTypeType
	: public CBaseType
{
public:
	OfficialType Undefined;
	OfficialType otPretext;
	OfficialType otConjunction;
	OfficialType otParticle;
	OfficialType otInterjection;
	OfficialType otPredicative;
	OfficialType otSymbol;
	OfficialType otDeterminers;
	OfficialType otInfMarker;
	OfficialType otExistThere;
	OfficialType otVvodnoeSlovo;
	OfficialTypeType(void)
		: Undefined(0)
		, otPretext(1)
		, otConjunction(2)
		, otParticle(3)
		, otInterjection(4)
		, otPredicative(5)
		, otSymbol(6)
		, otDeterminers(7)
		, otInfMarker(8)
		, otExistThere(9)
		, otVvodnoeSlovo(10)
	{
	}

	~OfficialTypeType(void){};

	unsigned int GetValueCount(void) const {return 11;};

	const char* GetTypeName() const {return "OfficialType";};

	const char* GetTypeDescription() const {return "��������� ����� ����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "otPretext";
		case 2: return "otConjunction";
		case 3: return "otParticle";
		case 4: return "otInterjection";
		case 5: return "otPredicative";
		case 6: return "otSymbol";
		case 7: return "otDeterminers";
		case 8: return "otInfMarker";
		case 9: return "otExistThere";
		case 10: return "otVvodnoeSlovo";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������";
		case 2: return "����";
		case 3: return "�������";
		case 4: return "����������";
		case 5: return "����������";
		case 6: return "������";
		case 7: return "������������";
		case 8: return "������������ ������� to";
		case 9: return "There";
		case 10: return "������� �����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class AnimInAnimTypeType;
typedef CMapFeature<8, 3, AnimInAnimTypeType> AnimInAnimType;
class AnimInAnimTypeType
	: public CBaseType
{
public:
	AnimInAnimType Undefined;
	AnimInAnimType aiaAnimation;
	AnimInAnimType aiaInanimation;
	AnimInAnimTypeType(void)
		: Undefined(0)
		, aiaAnimation(1)
		, aiaInanimation(2)
	{
	}

	~AnimInAnimTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "AnimInAnimType";};

	const char* GetTypeDescription() const {return "��������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "aiaAnimation";
		case 2: return "aiaInanimation";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������������";
		case 2: return "��������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class UniquenessType;
typedef CMapFeature<8, 3, UniquenessType> Uniqueness;
class UniquenessType
	: public CBaseType
{
public:
	Uniqueness Undefined;
	Uniqueness unqNotUnique;
	Uniqueness unqUnique;
	UniquenessType(void)
		: Undefined(0)
		, unqNotUnique(1)
		, unqUnique(2)
	{
	}

	~UniquenessType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "Uniqueness";};

	const char* GetTypeDescription() const {return "������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "unqNotUnique";
		case 2: return "unqUnique";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�� ���������� �����";
		case 2: return "���������� �����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TDetectWordAnalyzeModeType;
typedef CMapFeature<8, 3, TDetectWordAnalyzeModeType> TDetectWordAnalyzeMode;
class TDetectWordAnalyzeModeType
	: public CBaseType
{
public:
	TDetectWordAnalyzeMode Undefined;
	TDetectWordAnalyzeMode mfamLetForm;
	TDetectWordAnalyzeMode mfamAllForms;
	TDetectWordAnalyzeModeType(void)
		: Undefined(0)
		, mfamLetForm(1)
		, mfamAllForms(2)
	{
	}

	~TDetectWordAnalyzeModeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TDetectWordAnalyzeMode";};

	const char* GetTypeDescription() const {return "����� ������� �����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "mfamLetForm";
		case 2: return "mfamAllForms";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������� ����������";
		case 2: return "��� ����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class OperationModType;
typedef CMapFeature<8, 5, OperationModType> OperationMod;
class OperationModType
	: public CBaseType
{
public:
	OperationMod Undefined;
	OperationMod opmSelect;
	OperationMod opmRemove;
	OperationMod opmAppoint;
	OperationMod opmAdd;
	OperationModType(void)
		: Undefined(0)
		, opmSelect(1)
		, opmRemove(2)
		, opmAppoint(3)
		, opmAdd(4)
	{
	}

	~OperationModType(void){};

	unsigned int GetValueCount(void) const {return 5;};

	const char* GetTypeName() const {return "OperationMod";};

	const char* GetTypeDescription() const {return "����� ������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "opmSelect";
		case 2: return "opmRemove";
		case 3: return "opmAppoint";
		case 4: return "opmAdd";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������";
		case 2: return "�������";
		case 3: return "��������� ���������";
		case 4: return "��������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class ExistenceModType;
typedef CMapFeature<8, 3, ExistenceModType> ExistenceMod;
class ExistenceModType
	: public CBaseType
{
public:
	ExistenceMod Undefined;
	ExistenceMod excmExist;
	ExistenceMod excmAbsent;
	ExistenceModType(void)
		: Undefined(0)
		, excmExist(1)
		, excmAbsent(2)
	{
	}

	~ExistenceModType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "ExistenceMod";};

	const char* GetTypeDescription() const {return "�������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "excmExist";
		case 2: return "excmAbsent";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����������";
		case 2: return "�� ����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class AspectTypeType;
typedef CMapFeature<8, 4, AspectTypeType> AspectType;
class AspectTypeType
	: public CBaseType
{
public:
	AspectType Undefined;
	AspectType atPerfective;
	AspectType atImperfective;
	AspectType atPerfectiveImperfective;
	AspectTypeType(void)
		: Undefined(0)
		, atPerfective(1)
		, atImperfective(2)
		, atPerfectiveImperfective(3)
	{
	}

	~AspectTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "AspectType";};

	const char* GetTypeDescription() const {return "���";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "atPerfective";
		case 2: return "atImperfective";
		case 3: return "atPerfectiveImperfective";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����������";
		case 2: return "�������������";
		case 3: return "����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class AdverbTypeType;
typedef CMapFeature<8, 10, AdverbTypeType> AdverbType;
class AdverbTypeType
	: public CBaseType
{
public:
	AdverbType Undefined;
	AdverbType adQualitativeCircumstance;
	AdverbType adQualitativeQuantitive;
	AdverbType adAction;
	AdverbType adDegree;
	AdverbType adTime;
	AdverbType adPlace;
	AdverbType adCause;
	AdverbType adAim;
	AdverbType adCondition;
	AdverbTypeType(void)
		: Undefined(0)
		, adQualitativeCircumstance(1)
		, adQualitativeQuantitive(2)
		, adAction(3)
		, adDegree(4)
		, adTime(5)
		, adPlace(6)
		, adCause(7)
		, adAim(8)
		, adCondition(9)
	{
	}

	~AdverbTypeType(void){};

	unsigned int GetValueCount(void) const {return 10;};

	const char* GetTypeName() const {return "AdverbType";};

	const char* GetTypeDescription() const {return "��� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "adQualitativeCircumstance";
		case 2: return "adQualitativeQuantitive";
		case 3: return "adAction";
		case 4: return "adDegree";
		case 5: return "adTime";
		case 6: return "adPlace";
		case 7: return "adCause";
		case 8: return "adAim";
		case 9: return "adCondition";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����������� - ������������� �������";
		case 2: return "�����������-�������������� �������";
		case 3: return "��������";
		case 4: return "�������";
		case 5: return "�����";
		case 6: return "�����";
		case 7: return "�������";
		case 8: return "����";
		case 9: return "�������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class CaseTypeType;
typedef CMapFeature<8, 8, CaseTypeType> CaseType;
class CaseTypeType
	: public CBaseType
{
public:
	CaseType Undefined;
	CaseType ctNominative;
	CaseType ctGenitive;
	CaseType ctDative;
	CaseType ctAccusative;
	CaseType ctInstrumental;
	CaseType ctLocative;
	CaseType ctCommon;
	CaseTypeType(void)
		: Undefined(0)
		, ctNominative(1)
		, ctGenitive(2)
		, ctDative(3)
		, ctAccusative(4)
		, ctInstrumental(5)
		, ctLocative(6)
		, ctCommon(7)
	{
	}

	~CaseTypeType(void){};

	unsigned int GetValueCount(void) const {return 8;};

	const char* GetTypeName() const {return "CaseType";};

	const char* GetTypeDescription() const {return "�����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "ctNominative";
		case 2: return "ctGenitive";
		case 3: return "ctDative";
		case 4: return "ctAccusative";
		case 5: return "ctInstrumental";
		case 6: return "ctLocative";
		case 7: return "ctCommon";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������������";
		case 2: return "�����������";
		case 3: return "���������";
		case 4: return "�����������";
		case 5: return "������������";
		case 6: return "����������";
		case 7: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class CountTypeType;
typedef CMapFeature<8, 3, CountTypeType> CountType;
class CountTypeType
	: public CBaseType
{
public:
	CountType Undefined;
	CountType cntNotCount;
	CountType cntCount;
	CountTypeType(void)
		: Undefined(0)
		, cntNotCount(1)
		, cntCount(2)
	{
	}

	~CountTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "CountType";};

	const char* GetTypeDescription() const {return "�������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "cntNotCount";
		case 2: return "cntCount";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�� �����������";
		case 2: return "�����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class CommonTypeType;
typedef CMapFeature<8, 3, CommonTypeType> CommonType;
class CommonTypeType
	: public CBaseType
{
public:
	CommonType Undefined;
	CommonType cmtCommon;
	CommonType cmtProper;
	CommonTypeType(void)
		: Undefined(0)
		, cmtCommon(1)
		, cmtProper(2)
	{
	}

	~CommonTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "CommonType";};

	const char* GetTypeDescription() const {return "���������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "cmtCommon";
		case 2: return "cmtProper";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������������";
		case 2: return "�����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class DegreeTypeType;
typedef CMapFeature<8, 4, DegreeTypeType> DegreeType;
class DegreeTypeType
	: public CBaseType
{
public:
	DegreeType Undefined;
	DegreeType dtComparative;
	DegreeType dtSuperlative;
	DegreeType dtEstimationsSubjectiveForm;
	DegreeTypeType(void)
		: Undefined(0)
		, dtComparative(1)
		, dtSuperlative(2)
		, dtEstimationsSubjectiveForm(3)
	{
	}

	~DegreeTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "DegreeType";};

	const char* GetTypeDescription() const {return "������� ���������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "dtComparative";
		case 2: return "dtSuperlative";
		case 3: return "dtEstimationsSubjectiveForm";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������������";
		case 2: return "������������";
		case 3: return "�������� - ������������ �����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class GenderTypeType;
typedef CMapFeature<8, 5, GenderTypeType> GenderType;
class GenderTypeType
	: public CBaseType
{
public:
	GenderType Undefined;
	GenderType gtFemale;
	GenderType gtMasculine;
	GenderType gtNeutral;
	GenderType gtGeneral;
	GenderTypeType(void)
		: Undefined(0)
		, gtFemale(1)
		, gtMasculine(2)
		, gtNeutral(3)
		, gtGeneral(4)
	{
	}

	~GenderTypeType(void){};

	unsigned int GetValueCount(void) const {return 5;};

	const char* GetTypeName() const {return "GenderType";};

	const char* GetTypeDescription() const {return "���";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "gtFemale";
		case 2: return "gtMasculine";
		case 3: return "gtNeutral";
		case 4: return "gtGeneral";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������";
		case 2: return "�������";
		case 3: return "�������";
		case 4: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class NumberTypeType;
typedef CMapFeature<8, 3, NumberTypeType> NumberType;
class NumberTypeType
	: public CBaseType
{
public:
	NumberType Undefined;
	NumberType ntSingle;
	NumberType ntPlural;
	NumberTypeType(void)
		: Undefined(0)
		, ntSingle(1)
		, ntPlural(2)
	{
	}

	~NumberTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "NumberType";};

	const char* GetTypeDescription() const {return "�����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "ntSingle";
		case 2: return "ntPlural";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������������";
		case 2: return "�������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class NumericTypeType;
typedef CMapFeature<8, 4, NumericTypeType> NumericType;
class NumericTypeType
	: public CBaseType
{
public:
	NumericType Undefined;
	NumericType ntCount;
	NumericType ntCollection;
	NumericType ntOrdering;
	NumericTypeType(void)
		: Undefined(0)
		, ntCount(1)
		, ntCollection(2)
		, ntOrdering(3)
	{
	}

	~NumericTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "NumericType";};

	const char* GetTypeDescription() const {return "��� �������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "ntCount";
		case 2: return "ntCollection";
		case 3: return "ntOrdering";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "��������������";
		case 2: return "�������������";
		case 3: return "����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class NegativeTypeType;
typedef CMapFeature<8, 3, NegativeTypeType> NegativeType;
class NegativeTypeType
	: public CBaseType
{
public:
	NegativeType Undefined;
	NegativeType ntNotNegation;
	NegativeType ntNegation;
	NegativeTypeType(void)
		: Undefined(0)
		, ntNotNegation(1)
		, ntNegation(2)
	{
	}

	~NegativeTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "NegativeType";};

	const char* GetTypeDescription() const {return "��� ���������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "ntNotNegation";
		case 2: return "ntNegation";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�� ���������";
		case 2: return "���������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class PhaseVerbTypeType;
typedef CMapFeature<8, 3, PhaseVerbTypeType> PhaseVerbType;
class PhaseVerbTypeType
	: public CBaseType
{
public:
	PhaseVerbType Undefined;
	PhaseVerbType pvPhaseInf;
	PhaseVerbType pvPhaseAll;
	PhaseVerbTypeType(void)
		: Undefined(0)
		, pvPhaseInf(1)
		, pvPhaseAll(2)
	{
	}

	~PhaseVerbTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "PhaseVerbType";};

	const char* GetTypeDescription() const {return "���������� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "pvPhaseInf";
		case 2: return "pvPhaseAll";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������� - ��������� ���������";
		case 2: return "������� - ��������� �����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class PersonTypeType;
typedef CMapFeature<8, 4, PersonTypeType> PersonType;
class PersonTypeType
	: public CBaseType
{
public:
	PersonType Undefined;
	PersonType ptFirstFace;
	PersonType ptSecondFace;
	PersonType ptThirdFace;
	PersonTypeType(void)
		: Undefined(0)
		, ptFirstFace(1)
		, ptSecondFace(2)
		, ptThirdFace(3)
	{
	}

	~PersonTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "PersonType";};

	const char* GetTypeDescription() const {return "����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "ptFirstFace";
		case 2: return "ptSecondFace";
		case 3: return "ptThirdFace";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������";
		case 2: return "������";
		case 3: return "������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class PronounGroupType;
typedef CMapFeature<8, 4, PronounGroupType> PronounGroup;
class PronounGroupType
	: public CBaseType
{
public:
	PronounGroup Undefined;
	PronounGroup pngNoun;
	PronounGroup pngAdjective;
	PronounGroup pngNumeric;
	PronounGroupType(void)
		: Undefined(0)
		, pngNoun(1)
		, pngAdjective(2)
		, pngNumeric(3)
	{
	}

	~PronounGroupType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "PronounGroup";};

	const char* GetTypeDescription() const {return "������ �����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "pngNoun";
		case 2: return "pngAdjective";
		case 3: return "pngNumeric";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "���������������";
		case 2: return "��������������";
		case 3: return "������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class PronounClassType;
typedef CMapFeature<8, 13, PronounClassType> PronounClass;
class PronounClassType
	: public CBaseType
{
public:
	PronounClass Undefined;
	PronounClass pncIndividual;
	PronounClass pncReturning;
	PronounClass pncPossessive;
	PronounClass pncIndicative;
	PronounClass pncInterrogative;
	PronounClass pncNegative;
	PronounClass pncIndefinative;
	PronounClass pncRelative;
	PronounClass pncDefinative;
	PronounClass pncInterrogativeRelative;
	PronounClass pncQuantifying;
	PronounClass pncReciprocal;
	PronounClassType(void)
		: Undefined(0)
		, pncIndividual(1)
		, pncReturning(2)
		, pncPossessive(3)
		, pncIndicative(4)
		, pncInterrogative(5)
		, pncNegative(6)
		, pncIndefinative(7)
		, pncRelative(8)
		, pncDefinative(9)
		, pncInterrogativeRelative(10)
		, pncQuantifying(11)
		, pncReciprocal(12)
	{
	}

	~PronounClassType(void){};

	unsigned int GetValueCount(void) const {return 13;};

	const char* GetTypeName() const {return "PronounClass";};

	const char* GetTypeDescription() const {return "����� �����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "pncIndividual";
		case 2: return "pncReturning";
		case 3: return "pncPossessive";
		case 4: return "pncIndicative";
		case 5: return "pncInterrogative";
		case 6: return "pncNegative";
		case 7: return "pncIndefinative";
		case 8: return "pncRelative";
		case 9: return "pncDefinative";
		case 10: return "pncInterrogativeRelative";
		case 11: return "pncQuantifying";
		case 12: return "pncReciprocal";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������";
		case 2: return "����������";
		case 3: return "��������������";
		case 4: return "������������";
		case 5: return "��������������";
		case 6: return "�������������";
		case 7: return "��������������";
		case 8: return "�������������";
		case 9: return "���������������";
		case 10: return "������������� - �������������";
		case 11: return "��������������";
		case 12: return "��������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class ShortTypeType;
typedef CMapFeature<8, 2, ShortTypeType> ShortType;
class ShortTypeType
	: public CBaseType
{
public:
	ShortType Undefined;
	ShortType stShort;
	ShortTypeType(void)
		: Undefined(0)
		, stShort(1)
	{
	}

	~ShortTypeType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "ShortType";};

	const char* GetTypeDescription() const {return "���������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "stShort";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TAdverbClassType;
typedef CMapFeature<8, 2, TAdverbClassType> TAdverbClass;
class TAdverbClassType
	: public CBaseType
{
public:
	TAdverbClass Undefined;
	TAdverbClass adcInterrogative_Relative;
	TAdverbClassType(void)
		: Undefined(0)
		, adcInterrogative_Relative(1)
	{
	}

	~TAdverbClassType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "TAdverbClass";};

	const char* GetTypeDescription() const {return "����� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "adcInterrogative_Relative";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������������� - �������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TConjunctionTypeType;
typedef CMapFeature<8, 3, TConjunctionTypeType> TConjunctionType;
class TConjunctionTypeType
	: public CBaseType
{
public:
	TConjunctionType Undefined;
	TConjunctionType cjtCoordinating;
	TConjunctionType cjtSubordinating;
	TConjunctionTypeType(void)
		: Undefined(0)
		, cjtCoordinating(1)
		, cjtSubordinating(2)
	{
	}

	~TConjunctionTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TConjunctionType";};

	const char* GetTypeDescription() const {return "����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "cjtCoordinating";
		case 2: return "cjtSubordinating";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����������������";
		case 2: return "�����������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TDeterminerTypeType;
typedef CMapFeature<8, 2, TDeterminerTypeType> TDeterminerType;
class TDeterminerTypeType
	: public CBaseType
{
public:
	TDeterminerType Undefined;
	TDeterminerType tdtPreDeterminer;
	TDeterminerTypeType(void)
		: Undefined(0)
		, tdtPreDeterminer(1)
	{
	}

	~TDeterminerTypeType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "TDeterminerType";};

	const char* GetTypeDescription() const {return "������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tdtPreDeterminer";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TimeTypeType;
typedef CMapFeature<8, 4, TimeTypeType> TimeType;
class TimeTypeType
	: public CBaseType
{
public:
	TimeType Undefined;
	TimeType tmtPresent;
	TimeType tmtPast;
	TimeType tmtFuture;
	TimeTypeType(void)
		: Undefined(0)
		, tmtPresent(1)
		, tmtPast(2)
		, tmtFuture(3)
	{
	}

	~TimeTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "TimeType";};

	const char* GetTypeDescription() const {return "�����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tmtPresent";
		case 2: return "tmtPast";
		case 3: return "tmtFuture";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "���������";
		case 2: return "���������";
		case 3: return "�������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TransitionalTypeType;
typedef CMapFeature<8, 3, TransitionalTypeType> TransitionalType;
class TransitionalTypeType
	: public CBaseType
{
public:
	TransitionalType Undefined;
	TransitionalType tltTransitional;
	TransitionalType tltNoTransitional;
	TransitionalTypeType(void)
		: Undefined(0)
		, tltTransitional(1)
		, tltNoTransitional(2)
	{
	}

	~TransitionalTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TransitionalType";};

	const char* GetTypeDescription() const {return "������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tltTransitional";
		case 2: return "tltNoTransitional";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����������";
		case 2: return "������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class VoiceTypeType;
typedef CMapFeature<8, 3, VoiceTypeType> VoiceType;
class VoiceTypeType
	: public CBaseType
{
public:
	VoiceType Undefined;
	VoiceType vtPassive;
	VoiceType vtActive;
	VoiceTypeType(void)
		: Undefined(0)
		, vtPassive(1)
		, vtActive(2)
	{
	}

	~VoiceTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "VoiceType";};

	const char* GetTypeDescription() const {return "�����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "vtPassive";
		case 2: return "vtActive";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������������";
		case 2: return "��������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class VerbFormType;
typedef CMapFeature<8, 8, VerbFormType> VerbForm;
class VerbFormType
	: public CBaseType
{
public:
	VerbForm Undefined;
	VerbForm vfParticiple;
	VerbForm vfDeepr;
	VerbForm vfPersonal;
	VerbForm vfImPersonal;
	VerbForm vfInfinitive;
	VerbForm vfImperative;
	VerbForm vfToInfinitive;
	VerbFormType(void)
		: Undefined(0)
		, vfParticiple(1)
		, vfDeepr(2)
		, vfPersonal(3)
		, vfImPersonal(4)
		, vfInfinitive(5)
		, vfImperative(6)
		, vfToInfinitive(7)
	{
	}

	~VerbFormType(void){};

	unsigned int GetValueCount(void) const {return 8;};

	const char* GetTypeName() const {return "VerbForm";};

	const char* GetTypeDescription() const {return "����� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "vfParticiple";
		case 2: return "vfDeepr";
		case 3: return "vfPersonal";
		case 4: return "vfImPersonal";
		case 5: return "vfInfinitive";
		case 6: return "vfImperative";
		case 7: return "vfToInfinitive";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "���������";
		case 2: return "������������";
		case 3: return "������ �����";
		case 4: return "��������� �����";
		case 5: return "���������";
		case 6: return "���������";
		case 7: return "��������� � �������� to";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class VerbTypeType;
typedef CMapFeature<8, 4, VerbTypeType> VerbType;
class VerbTypeType
	: public CBaseType
{
public:
	VerbType Undefined;
	VerbType vrbtMain;
	VerbType vrbtAux;
	VerbType vrbtMod;
	VerbTypeType(void)
		: Undefined(0)
		, vrbtMain(1)
		, vrbtAux(2)
		, vrbtMod(3)
	{
	}

	~VerbTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "VerbType";};

	const char* GetTypeDescription() const {return "������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "vrbtMain";
		case 2: return "vrbtAux";
		case 3: return "vrbtMod";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������";
		case 2: return "���������������";
		case 3: return "���������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class MoodTypeType;
typedef CMapFeature<8, 4, MoodTypeType> MoodType;
class MoodTypeType
	: public CBaseType
{
public:
	MoodType Undefined;
	MoodType mtImperative;
	MoodType mtIndicative;
	MoodType mtSubjunctive;
	MoodTypeType(void)
		: Undefined(0)
		, mtImperative(1)
		, mtIndicative(2)
		, mtSubjunctive(3)
	{
	}

	~MoodTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "MoodType";};

	const char* GetTypeDescription() const {return "����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "mtImperative";
		case 2: return "mtIndicative";
		case 3: return "mtSubjunctive";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������������";
		case 2: return "�������������";
		case 3: return "��������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSemanticTypeType;
typedef CMapFeature<8, 14, TSemanticTypeType> TSemanticType;
class TSemanticTypeType
	: public CBaseType
{
public:
	TSemanticType Undefined;
	TSemanticType smtTimeInterval;
	TSemanticType smtPlace;
	TSemanticType smtMeasure;
	TSemanticType smtPerson;
	TSemanticType smtOrganization;
	TSemanticType smtVerb;
	TSemanticType smtService;
	TSemanticType smtInfo;
	TSemanticType smtMaterial;
	TSemanticType smtBuilding;
	TSemanticType smtTransport;
	TSemanticType smtEvent;
	TSemanticType smtProduct;
	TSemanticTypeType(void)
		: Undefined(0)
		, smtTimeInterval(1)
		, smtPlace(2)
		, smtMeasure(3)
		, smtPerson(4)
		, smtOrganization(5)
		, smtVerb(6)
		, smtService(7)
		, smtInfo(8)
		, smtMaterial(9)
		, smtBuilding(10)
		, smtTransport(11)
		, smtEvent(12)
		, smtProduct(13)
	{
	}

	~TSemanticTypeType(void){};

	unsigned int GetValueCount(void) const {return 14;};

	const char* GetTypeName() const {return "TSemanticType";};

	const char* GetTypeDescription() const {return "������������� ����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtTimeInterval";
		case 2: return "smtPlace";
		case 3: return "smtMeasure";
		case 4: return "smtPerson";
		case 5: return "smtOrganization";
		case 6: return "smtVerb";
		case 7: return "smtService";
		case 8: return "smtInfo";
		case 9: return "smtMaterial";
		case 10: return "smtBuilding";
		case 11: return "smtTransport";
		case 12: return "smtEvent";
		case 13: return "smtProduct";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		case 2: return "�����";
		case 3: return "����";
		case 4: return "������";
		case 5: return "��� �����������";
		case 6: return "����������";
		case 7: return "���������";
		case 8: return "���������� ����������";
		case 9: return "������";
		case 10: return "������";
		case 11: return "���������";
		case 12: return "�������";
		case 13: return "�������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSServiceTypesType;
typedef CMapFeature<8, 13, TSServiceTypesType> TSServiceTypes;
class TSServiceTypesType
	: public CBaseType
{
public:
	TSServiceTypes Undefined;
	TSServiceTypes sstAcronymCitation;
	TSServiceTypes sstNominativeDefinition;
	TSServiceTypes sstWine;
	TSServiceTypes sstMusikalInstrument;
	TSServiceTypes sstColor;
	TSServiceTypes sstAnimal;
	TSServiceTypes sstSport;
	TSServiceTypes sstMovie;
	TSServiceTypes sstMusicStyle;
	TSServiceTypes sstIndustry;
	TSServiceTypes sstFood;
	TSServiceTypes sstTelephoneNumber;
	TSServiceTypesType(void)
		: Undefined(0)
		, sstAcronymCitation(1)
		, sstNominativeDefinition(2)
		, sstWine(3)
		, sstMusikalInstrument(4)
		, sstColor(5)
		, sstAnimal(6)
		, sstSport(7)
		, sstMovie(8)
		, sstMusicStyle(9)
		, sstIndustry(10)
		, sstFood(11)
		, sstTelephoneNumber(12)
	{
	}

	~TSServiceTypesType(void){};

	unsigned int GetValueCount(void) const {return 13;};

	const char* GetTypeName() const {return "TSServiceTypes";};

	const char* GetTypeDescription() const {return "��������� ���";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "sstAcronymCitation";
		case 2: return "sstNominativeDefinition";
		case 3: return "sstWine";
		case 4: return "sstMusikalInstrument";
		case 5: return "sstColor";
		case 6: return "sstAnimal";
		case 7: return "sstSport";
		case 8: return "sstMovie";
		case 9: return "sstMusicStyle";
		case 10: return "sstIndustry";
		case 11: return "sstFood";
		case 12: return "sstTelephoneNumber";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "������� ��� ������";
		case 2: return "������������ �����������";
		case 3: return "����������� �����";
		case 4: return "����������� ����������";
		case 5: return "����";
		case 6: return "��������";
		case 7: return "�����";
		case 8: return "������";
		case 9: return "����������� �����";
		case 10: return "��������� � ������";
		case 11: return "���";
		case 12: return "����� ��������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSTimeIntervalTypeType;
typedef CMapFeature<8, 7, TSTimeIntervalTypeType> TSTimeIntervalType;
class TSTimeIntervalTypeType
	: public CBaseType
{
public:
	TSTimeIntervalType Undefined;
	TSTimeIntervalType semtitDateYear;
	TSTimeIntervalType semtitDateMonth;
	TSTimeIntervalType semtitDateDay;
	TSTimeIntervalType semtitDayTime;
	TSTimeIntervalType semtitCentury;
	TSTimeIntervalType semtitDateNumber;
	TSTimeIntervalTypeType(void)
		: Undefined(0)
		, semtitDateYear(1)
		, semtitDateMonth(2)
		, semtitDateDay(3)
		, semtitDayTime(4)
		, semtitCentury(5)
		, semtitDateNumber(6)
	{
	}

	~TSTimeIntervalTypeType(void){};

	unsigned int GetValueCount(void) const {return 7;};

	const char* GetTypeName() const {return "TSTimeIntervalType";};

	const char* GetTypeDescription() const {return "��� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "semtitDateYear";
		case 2: return "semtitDateMonth";
		case 3: return "semtitDateDay";
		case 4: return "semtitDayTime";
		case 5: return "semtitCentury";
		case 6: return "semtitDateNumber";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "���";
		case 2: return "�����";
		case 3: return "����";
		case 4: return "����� ���";
		case 5: return "���";
		case 6: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSPlaceTypeType;
typedef CMapFeature<8, 10, TSPlaceTypeType> TSPlaceType;
class TSPlaceTypeType
	: public CBaseType
{
public:
	TSPlaceType Undefined;
	TSPlaceType pltCity;
	TSPlaceType pltCountry;
	TSPlaceType pltContinent;
	TSPlaceType pltState;
	TSPlaceType pltProvince;
	TSPlaceType pltHotel;
	TSPlaceType pltIsland;
	TSPlaceType pltOceans;
	TSPlaceType pltPrision;
	TSPlaceTypeType(void)
		: Undefined(0)
		, pltCity(1)
		, pltCountry(2)
		, pltContinent(3)
		, pltState(4)
		, pltProvince(5)
		, pltHotel(6)
		, pltIsland(7)
		, pltOceans(8)
		, pltPrision(9)
	{
	}

	~TSPlaceTypeType(void){};

	unsigned int GetValueCount(void) const {return 10;};

	const char* GetTypeName() const {return "TSPlaceType";};

	const char* GetTypeDescription() const {return "��� �����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "pltCity";
		case 2: return "pltCountry";
		case 3: return "pltContinent";
		case 4: return "pltState";
		case 5: return "pltProvince";
		case 6: return "pltHotel";
		case 7: return "pltIsland";
		case 8: return "pltOceans";
		case 9: return "pltPrision";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		case 2: return "������";
		case 3: return "���������";
		case 4: return "����";
		case 5: return "���������";
		case 6: return "�����";
		case 7: return "������";
		case 8: return "�����";
		case 9: return "������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSMeasureTypeType;
typedef CMapFeature<8, 14, TSMeasureTypeType> TSMeasureType;
class TSMeasureTypeType
	: public CBaseType
{
public:
	TSMeasureType Undefined;
	TSMeasureType msrtTemperature;
	TSMeasureType msrtVolume;
	TSMeasureType msrtWeight;
	TSMeasureType msrtLength;
	TSMeasureType msrtTime;
	TSMeasureType msrtSurface;
	TSMeasureType msrtPrice;
	TSMeasureType msrtSpeed;
	TSMeasureType msrtWidth;
	TSMeasureType msrtHeight;
	TSMeasureType msrtDepth;
	TSMeasureType msrtAge;
	TSMeasureType msrtNumber;
	TSMeasureTypeType(void)
		: Undefined(0)
		, msrtTemperature(1)
		, msrtVolume(2)
		, msrtWeight(3)
		, msrtLength(4)
		, msrtTime(5)
		, msrtSurface(6)
		, msrtPrice(7)
		, msrtSpeed(8)
		, msrtWidth(9)
		, msrtHeight(10)
		, msrtDepth(11)
		, msrtAge(12)
		, msrtNumber(13)
	{
	}

	~TSMeasureTypeType(void){};

	unsigned int GetValueCount(void) const {return 14;};

	const char* GetTypeName() const {return "TSMeasureType";};

	const char* GetTypeDescription() const {return "��� ����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "msrtTemperature";
		case 2: return "msrtVolume";
		case 3: return "msrtWeight";
		case 4: return "msrtLength";
		case 5: return "msrtTime";
		case 6: return "msrtSurface";
		case 7: return "msrtPrice";
		case 8: return "msrtSpeed";
		case 9: return "msrtWidth";
		case 10: return "msrtHeight";
		case 11: return "msrtDepth";
		case 12: return "msrtAge";
		case 13: return "msrtNumber";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����������";
		case 2: return "�����";
		case 3: return "���";
		case 4: return "�����";
		case 5: return "�����";
		case 6: return "�������";
		case 7: return "����";
		case 8: return "��������";
		case 9: return "������";
		case 10: return "������";
		case 11: return "�������";
		case 12: return "�������";
		case 13: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSPersonTypeType;
typedef CMapFeature<8, 9, TSPersonTypeType> TSPersonType;
class TSPersonTypeType
	: public CBaseType
{
public:
	TSPersonType Undefined;
	TSPersonType semprstFirstName;
	TSPersonType semprstLastName;
	TSPersonType semprstMiddleName;
	TSPersonType semprstProfession;
	TSPersonType semprstNationality;
	TSPersonType semprstAgent;
	TSPersonType semprstName;
	TSPersonType semprstActor;
	TSPersonTypeType(void)
		: Undefined(0)
		, semprstFirstName(1)
		, semprstLastName(2)
		, semprstMiddleName(3)
		, semprstProfession(4)
		, semprstNationality(5)
		, semprstAgent(6)
		, semprstName(7)
		, semprstActor(8)
	{
	}

	~TSPersonTypeType(void){};

	unsigned int GetValueCount(void) const {return 9;};

	const char* GetTypeName() const {return "TSPersonType";};

	const char* GetTypeDescription() const {return "��� ��������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "semprstFirstName";
		case 2: return "semprstLastName";
		case 3: return "semprstMiddleName";
		case 4: return "semprstProfession";
		case 5: return "semprstNationality";
		case 6: return "semprstAgent";
		case 7: return "semprstName";
		case 8: return "semprstActor";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "���";
		case 2: return "�������";
		case 3: return "��������";
		case 4: return "��������";
		case 5: return "��������������";
		case 6: return "�����";
		case 7: return "���";
		case 8: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSOrganizationTypeType;
typedef CMapFeature<8, 12, TSOrganizationTypeType> TSOrganizationType;
class TSOrganizationTypeType
	: public CBaseType
{
public:
	TSOrganizationType Undefined;
	TSOrganizationType orgtCompany;
	TSOrganizationType orgtBank;
	TSOrganizationType orgtInternationalOrganization;
	TSOrganizationType orgtFund;
	TSOrganizationType orgtParty;
	TSOrganizationType orgtBand;
	TSOrganizationType orgtUniversity;
	TSOrganizationType orgtCollege;
	TSOrganizationType orgtMilitaryBranch;
	TSOrganizationType orgtRestOrganization;
	TSOrganizationType orgtTransport;
	TSOrganizationTypeType(void)
		: Undefined(0)
		, orgtCompany(1)
		, orgtBank(2)
		, orgtInternationalOrganization(3)
		, orgtFund(4)
		, orgtParty(5)
		, orgtBand(6)
		, orgtUniversity(7)
		, orgtCollege(8)
		, orgtMilitaryBranch(9)
		, orgtRestOrganization(10)
		, orgtTransport(11)
	{
	}

	~TSOrganizationTypeType(void){};

	unsigned int GetValueCount(void) const {return 12;};

	const char* GetTypeName() const {return "TSOrganizationType";};

	const char* GetTypeDescription() const {return "��� �����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "orgtCompany";
		case 2: return "orgtBank";
		case 3: return "orgtInternationalOrganization";
		case 4: return "orgtFund";
		case 5: return "orgtParty";
		case 6: return "orgtBand";
		case 7: return "orgtUniversity";
		case 8: return "orgtCollege";
		case 9: return "orgtMilitaryBranch";
		case 10: return "orgtRestOrganization";
		case 11: return "orgtTransport";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "��������";
		case 2: return "����";
		case 3: return "������������� �����������";
		case 4: return "����";
		case 5: return "������";
		case 6: return "����������� ������";
		case 7: return "�����������";
		case 8: return "�����";
		case 9: return "������� �����������";
		case 10: return "��������� ���� ����";
		case 11: return "������������ �����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSVerbTypeType;
typedef CMapFeature<8, 9, TSVerbTypeType> TSVerbType;
class TSVerbTypeType
	: public CBaseType
{
public:
	TSVerbType Undefined;
	TSVerbType semvtBe;
	TSVerbType semvtAcquirePossess;
	TSVerbType semvtEndBegin;
	TSVerbType semvtEnd;
	TSVerbType semvtBecome;
	TSVerbType semvtWeigh;
	TSVerbType semvtLast;
	TSVerbType semvtCost;
	TSVerbTypeType(void)
		: Undefined(0)
		, semvtBe(1)
		, semvtAcquirePossess(2)
		, semvtEndBegin(3)
		, semvtEnd(4)
		, semvtBecome(5)
		, semvtWeigh(6)
		, semvtLast(7)
		, semvtCost(8)
	{
	}

	~TSVerbTypeType(void){};

	unsigned int GetValueCount(void) const {return 9;};

	const char* GetTypeName() const {return "TSVerbType";};

	const char* GetTypeDescription() const {return "��� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "semvtBe";
		case 2: return "semvtAcquirePossess";
		case 3: return "semvtEndBegin";
		case 4: return "semvtEnd";
		case 5: return "semvtBecome";
		case 6: return "semvtWeigh";
		case 7: return "semvtLast";
		case 8: return "semvtCost";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������������";
		case 2: return "��������";
		case 3: return "������ ����������";
		case 4: return "�����";
		case 5: return "�����������";
		case 6: return "���";
		case 7: return "������������";
		case 8: return "���������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSVBeTypeType;
typedef CMapFeature<8, 5, TSVBeTypeType> TSVBeType;
class TSVBeTypeType
	: public CBaseType
{
public:
	TSVBeType Undefined;
	TSVBeType tsvbtRepresent;
	TSVBeType tsvbtLocate;
	TSVBeType tsvbtOccur;
	TSVBeType tsvbtExist;
	TSVBeTypeType(void)
		: Undefined(0)
		, tsvbtRepresent(1)
		, tsvbtLocate(2)
		, tsvbtOccur(3)
		, tsvbtExist(4)
	{
	}

	~TSVBeTypeType(void){};

	unsigned int GetValueCount(void) const {return 5;};

	const char* GetTypeName() const {return "TSVBeType";};

	const char* GetTypeDescription() const {return "Existence";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tsvbtRepresent";
		case 2: return "tsvbtLocate";
		case 3: return "tsvbtOccur";
		case 4: return "tsvbtExist";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Value is not defined";
		case 1: return "Representation";
		case 2: return "Location";
		case 3: return "Occurence";
		case 4: return "Being";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSVAcquirePossessTypeType;
typedef CMapFeature<8, 3, TSVAcquirePossessTypeType> TSVAcquirePossessType;
class TSVAcquirePossessTypeType
	: public CBaseType
{
public:
	TSVAcquirePossessType Undefined;
	TSVAcquirePossessType tsvaptAcquire;
	TSVAcquirePossessType tsvaptPossess;
	TSVAcquirePossessTypeType(void)
		: Undefined(0)
		, tsvaptAcquire(1)
		, tsvaptPossess(2)
	{
	}

	~TSVAcquirePossessTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TSVAcquirePossessType";};

	const char* GetTypeDescription() const {return "Acquisition";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tsvaptAcquire";
		case 2: return "tsvaptPossess";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Value is not defined";
		case 1: return "Acquire subtype";
		case 2: return "Posess subtype";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSVEndTypeType;
typedef CMapFeature<8, 3, TSVEndTypeType> TSVEndType;
class TSVEndTypeType
	: public CBaseType
{
public:
	TSVEndType Undefined;
	TSVEndType tsveEliminate;
	TSVEndType tsveUse;
	TSVEndTypeType(void)
		: Undefined(0)
		, tsveEliminate(1)
		, tsveUse(2)
	{
	}

	~TSVEndTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TSVEndType";};

	const char* GetTypeDescription() const {return "End";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tsveEliminate";
		case 2: return "tsveUse";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Value is not defined";
		case 1: return "Eliminate subtype";
		case 2: return "Use subtype";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSVAcquireTypeType;
typedef CMapFeature<8, 3, TSVAcquireTypeType> TSVAcquireType;
class TSVAcquireTypeType
	: public CBaseType
{
public:
	TSVAcquireType Undefined;
	TSVAcquireType tsvatReceive;
	TSVAcquireType tsvatHire;
	TSVAcquireTypeType(void)
		: Undefined(0)
		, tsvatReceive(1)
		, tsvatHire(2)
	{
	}

	~TSVAcquireTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TSVAcquireType";};

	const char* GetTypeDescription() const {return "Acquire verb subtype";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "tsvatReceive";
		case 2: return "tsvatHire";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Value is not defined";
		case 1: return "Receive";
		case 2: return "Hire";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TShiftSemanticType;
typedef CIntegerFeature<TShiftSemanticType> TShiftSemantic;
class TShiftSemanticType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CIntegerFeature";};

	const char* GetTypeDescription() const {return "����� �������� �� �������� ���������� ������������ ���������";};

	const char* GetValueName(unsigned int n) const {return "TShiftSemantic";};

	const char* GetValueDescription(unsigned int n) const {return "����� �������� �� �������� ���������� ������������ ���������";};

};


class TCityType;
typedef CMapFeature<8, 2, TCityType> TCity;
class TCityType
	: public CBaseType
{
public:
	TCity Undefined;
	TCity smtcityArea;
	TCityType(void)
		: Undefined(0)
		, smtcityArea(1)
	{
	}

	~TCityType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "TCity";};

	const char* GetTypeDescription() const {return "������������� ���� ������� ���� ������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtcityArea";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TAreaType;
typedef CMapFeature<8, 2, TAreaType> TArea;
class TAreaType
	: public CBaseType
{
public:
	TArea Undefined;
	TArea smtareaDistrict;
	TAreaType(void)
		: Undefined(0)
		, smtareaDistrict(1)
	{
	}

	~TAreaType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "TArea";};

	const char* GetTypeDescription() const {return "������������� ���� ������� ���� ������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtareaDistrict";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TDistrictType;
typedef CMapFeature<8, 2, TDistrictType> TDistrict;
class TDistrictType
	: public CBaseType
{
public:
	TDistrict Undefined;
	TDistrict smtDistrMetro;
	TDistrictType(void)
		: Undefined(0)
		, smtDistrMetro(1)
	{
	}

	~TDistrictType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "TDistrict";};

	const char* GetTypeDescription() const {return "������������� ���� ������� ���� ������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtDistrMetro";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TMetroType;
typedef CMapFeature<8, 11, TMetroType> TMetro;
class TMetroType
	: public CBaseType
{
public:
	TMetro Undefined;
	TMetro smtMetroStreet;
	TMetro smtMetroPereulok;
	TMetro smtMetroProezd;
	TMetro smtMetroTupik;
	TMetro smtMetroProspekt;
	TMetro smtMetroPloshad;
	TMetro smtMetroBulvar;
	TMetro smtMetroAlleya;
	TMetro smtMetroNaberezhnaya;
	TMetro smtMetroLiniya;
	TMetroType(void)
		: Undefined(0)
		, smtMetroStreet(1)
		, smtMetroPereulok(2)
		, smtMetroProezd(3)
		, smtMetroTupik(4)
		, smtMetroProspekt(5)
		, smtMetroPloshad(6)
		, smtMetroBulvar(7)
		, smtMetroAlleya(8)
		, smtMetroNaberezhnaya(9)
		, smtMetroLiniya(10)
	{
	}

	~TMetroType(void){};

	unsigned int GetValueCount(void) const {return 11;};

	const char* GetTypeName() const {return "TMetro";};

	const char* GetTypeDescription() const {return "������������� ���� ������� ���� �����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtMetroStreet";
		case 2: return "smtMetroPereulok";
		case 3: return "smtMetroProezd";
		case 4: return "smtMetroTupik";
		case 5: return "smtMetroProspekt";
		case 6: return "smtMetroPloshad";
		case 7: return "smtMetroBulvar";
		case 8: return "smtMetroAlleya";
		case 9: return "smtMetroNaberezhnaya";
		case 10: return "smtMetroLiniya";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		case 2: return "��������";
		case 3: return "������";
		case 4: return "�����";
		case 5: return "��������";
		case 6: return "�������";
		case 7: return "�������";
		case 8: return "�����";
		case 9: return "����������";
		case 10: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TGenericType;
typedef CMapFeature<8, 3, TGenericType> TGeneric;
class TGenericType
	: public CBaseType
{
public:
	TGeneric Undefined;
	TGeneric smtGeneric;
	TGeneric smtNotGeneric;
	TGenericType(void)
		: Undefined(0)
		, smtGeneric(1)
		, smtNotGeneric(2)
	{
	}

	~TGenericType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "TGeneric";};

	const char* GetTypeDescription() const {return "������������� ��������� �����/�������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtGeneric";
		case 2: return "smtNotGeneric";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		case 2: return "�������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSInfoType;
typedef CMapFeature<8, 5, TSInfoType> TSInfo;
class TSInfoType
	: public CBaseType
{
public:
	TSInfo Undefined;
	TSInfo smtInfoSite;
	TSInfo smtInfoMail;
	TSInfo smtInfoTelefon;
	TSInfo smtInfoPlace;
	TSInfoType(void)
		: Undefined(0)
		, smtInfoSite(1)
		, smtInfoMail(2)
		, smtInfoTelefon(3)
		, smtInfoPlace(4)
	{
	}

	~TSInfoType(void){};

	unsigned int GetValueCount(void) const {return 5;};

	const char* GetTypeName() const {return "TSInfo";};

	const char* GetTypeDescription() const {return "���������� ����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "smtInfoSite";
		case 2: return "smtInfoMail";
		case 3: return "smtInfoTelefon";
		case 4: return "smtInfoPlace";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����";
		case 2: return "����������� �����";
		case 3: return "�������";
		case 4: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSMaterialType;
typedef CMapFeature<8, 8, TSMaterialType> TSMaterial;
class TSMaterialType
	: public CBaseType
{
public:
	TSMaterial Undefined;
	TSMaterial mtrlManufacture;
	TSMaterial mtrlFood;
	TSMaterial mtrlClothes;
	TSMaterial mtrlInstrument;
	TSMaterial mtrlGoods;
	TSMaterial mtrlBanknote;
	TSMaterial mtrlForFreeTime;
	TSMaterialType(void)
		: Undefined(0)
		, mtrlManufacture(1)
		, mtrlFood(2)
		, mtrlClothes(3)
		, mtrlInstrument(4)
		, mtrlGoods(5)
		, mtrlBanknote(6)
		, mtrlForFreeTime(7)
	{
	}

	~TSMaterialType(void){};

	unsigned int GetValueCount(void) const {return 8;};

	const char* GetTypeName() const {return "TSMaterial";};

	const char* GetTypeDescription() const {return "������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "mtrlManufacture";
		case 2: return "mtrlFood";
		case 3: return "mtrlClothes";
		case 4: return "mtrlInstrument";
		case 5: return "mtrlGoods";
		case 6: return "mtrlBanknote";
		case 7: return "mtrlForFreeTime";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "������������";
		case 1: return "�������� ������� � ���������";
		case 2: return "�������� �������";
		case 3: return "������ � ���������";
		case 4: return "�������, ���������";
		case 5: return "�������� �������";
		case 6: return "��������� ��������";
		case 7: return "�������� ��� ������, ���";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSTransportType;
typedef CMapFeature<8, 5, TSTransportType> TSTransport;
class TSTransportType
	: public CBaseType
{
public:
	TSTransport Undefined;
	TSTransport trnAuto;
	TSTransport trnWater;
	TSTransport trnRailway;
	TSTransport trnAir;
	TSTransportType(void)
		: Undefined(0)
		, trnAuto(1)
		, trnWater(2)
		, trnRailway(3)
		, trnAir(4)
	{
	}

	~TSTransportType(void){};

	unsigned int GetValueCount(void) const {return 5;};

	const char* GetTypeName() const {return "TSTransport";};

	const char* GetTypeDescription() const {return "���������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "trnAuto";
		case 2: return "trnWater";
		case 3: return "trnRailway";
		case 4: return "trnAir";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�������������";
		case 2: return "������";
		case 3: return "���������������";
		case 4: return "���������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSMFoodType;
typedef CMapFeature<8, 11, TSMFoodType> TSMFood;
class TSMFoodType
	: public CBaseType
{
public:
	TSMFood Undefined;
	TSMFood mtrl_fd_Dish;
	TSMFood mtrl_fd_Bread;
	TSMFood mtrl_fd_Milk;
	TSMFood mtrl_fd_Meat;
	TSMFood mtrl_fd_Fish;
	TSMFood mtrl_fd_Vegetables;
	TSMFood mtrl_fd_Drink;
	TSMFood mtrl_fd_Alcohol;
	TSMFood mtrl_fd_Sweets;
	TSMFood mtrl_fd_Fruit;
	TSMFoodType(void)
		: Undefined(0)
		, mtrl_fd_Dish(1)
		, mtrl_fd_Bread(2)
		, mtrl_fd_Milk(3)
		, mtrl_fd_Meat(4)
		, mtrl_fd_Fish(5)
		, mtrl_fd_Vegetables(6)
		, mtrl_fd_Drink(7)
		, mtrl_fd_Alcohol(8)
		, mtrl_fd_Sweets(9)
		, mtrl_fd_Fruit(10)
	{
	}

	~TSMFoodType(void){};

	unsigned int GetValueCount(void) const {return 11;};

	const char* GetTypeName() const {return "TSMFood";};

	const char* GetTypeDescription() const {return "�������� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "mtrl_fd_Dish";
		case 2: return "mtrl_fd_Bread";
		case 3: return "mtrl_fd_Milk";
		case 4: return "mtrl_fd_Meat";
		case 5: return "mtrl_fd_Fish";
		case 6: return "mtrl_fd_Vegetables";
		case 7: return "mtrl_fd_Drink";
		case 8: return "mtrl_fd_Alcohol";
		case 9: return "mtrl_fd_Sweets";
		case 10: return "mtrl_fd_Fruit";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "�����";
		case 2: return "������� ���������";
		case 3: return "�������� ���������";
		case 4: return "����";
		case 5: return "����";
		case 6: return "�����";
		case 7: return "�������";
		case 8: return "��������";
		case 9: return "��������";
		case 10: return "������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSMForFreeTimeType;
typedef CMapFeature<8, 4, TSMForFreeTimeType> TSMForFreeTime;
class TSMForFreeTimeType
	: public CBaseType
{
public:
	TSMForFreeTime Undefined;
	TSMForFreeTime mtrl_fftm_Sport;
	TSMForFreeTime mtrl_fftm_Toys;
	TSMForFreeTime mtrl_fftm_Music;
	TSMForFreeTimeType(void)
		: Undefined(0)
		, mtrl_fftm_Sport(1)
		, mtrl_fftm_Toys(2)
		, mtrl_fftm_Music(3)
	{
	}

	~TSMForFreeTimeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "TSMForFreeTime";};

	const char* GetTypeDescription() const {return "�������� ��� ������ � ���";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "mtrl_fftm_Sport";
		case 2: return "mtrl_fftm_Toys";
		case 3: return "mtrl_fftm_Music";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "��������������";
		case 2: return "�������";
		case 3: return "����������� �����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TSBuildingType;
typedef CMapFeature<8, 2, TSBuildingType> TSBuilding;
class TSBuildingType
	: public CBaseType
{
public:
	TSBuilding Undefine;
	TSBuilding NotUndefine;
	TSBuildingType(void)
		: Undefine(0)
		, NotUndefine(1)
	{
	}

	~TSBuildingType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "TSBuilding";};

	const char* GetTypeDescription() const {return "��������, ������, ����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefine";
		case 1: return "NotUndefine";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "��� ������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class VerbConstructionType;
typedef CMapFeature<8, 12, VerbConstructionType> VerbConstruction;
class VerbConstructionType
	: public CBaseType
{
public:
	VerbConstruction vcOnlyVerb;
	VerbConstruction vcOneObjectPlus;
	VerbConstruction vcTwoObjectPlus;
	VerbConstruction vcTwoObjectPlusCanChangePlace;
	VerbConstruction vcTwoObjectPlusCanBeObjectComplement;
	VerbConstruction vcTwoObjectPlusCanAddSentence;
	VerbConstruction vcThreeObjectPlus;
	VerbConstruction vcSubjectComplementPlus;
	VerbConstruction vcAdverbPlus;
	VerbConstruction vcItSubjectComplimentPlus;
	VerbConstruction vcThreeObjectPlusCanChangePlace;
	VerbConstruction vcIndirectObjectPlus;
	VerbConstructionType(void)
		: vcOnlyVerb(0)
		, vcOneObjectPlus(1)
		, vcTwoObjectPlus(2)
		, vcTwoObjectPlusCanChangePlace(3)
		, vcTwoObjectPlusCanBeObjectComplement(4)
		, vcTwoObjectPlusCanAddSentence(5)
		, vcThreeObjectPlus(6)
		, vcSubjectComplementPlus(7)
		, vcAdverbPlus(8)
		, vcItSubjectComplimentPlus(9)
		, vcThreeObjectPlusCanChangePlace(10)
		, vcIndirectObjectPlus(11)
	{
	}

	~VerbConstructionType(void){};

	unsigned int GetValueCount(void) const {return 12;};

	const char* GetTypeName() const {return "VerbConstruction";};

	const char* GetTypeDescription() const {return "���������� �����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "vcOnlyVerb";
		case 1: return "vcOneObjectPlus";
		case 2: return "vcTwoObjectPlus";
		case 3: return "vcTwoObjectPlusCanChangePlace";
		case 4: return "vcTwoObjectPlusCanBeObjectComplement";
		case 5: return "vcTwoObjectPlusCanAddSentence";
		case 6: return "vcThreeObjectPlus";
		case 7: return "vcSubjectComplementPlus";
		case 8: return "vcAdverbPlus";
		case 9: return "vcItSubjectComplimentPlus";
		case 10: return "vcThreeObjectPlusCanChangePlace";
		case 11: return "vcIndirectObjectPlus";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "������������ ������ ��� ���������� ����������";
		case 1: return "����������/������������ ������ � ��������� �����������";
		case 2: return "������ � ����� ���������";
		case 3: return "������ � ����� ����������������� ���������";
		case 4: return "������ � ����� ���������, ������ �� ������� ��������� ������";
		case 5: return "verb with two objects, of which the second is nonfinitary clause";
		case 6: return "������ � ����� ���������";
		case 7: return "Verb with object, which is object to subject";
		case 8: return "Verb with finite adverb";
		case 9: return "Verb with subject It";
		case 10: return "Verb with three objects, which can replace one another";
		case 11: return "Verb with indirect subject";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class NounConstructionType;
typedef CMapFeature<8, 3, NounConstructionType> NounConstruction;
class NounConstructionType
	: public CBaseType
{
public:
	NounConstruction ncOnlyNoun;
	NounConstruction ncAttributePlus;
	NounConstruction ncIsAdjunct;
	NounConstructionType(void)
		: ncOnlyNoun(0)
		, ncAttributePlus(1)
		, ncIsAdjunct(2)
	{
	}

	~NounConstructionType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "NounConstruction";};

	const char* GetTypeDescription() const {return "����������� ����������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "ncOnlyNoun";
		case 1: return "ncAttributePlus";
		case 2: return "ncIsAdjunct";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "������ ���������������";
		case 1: return "��������������� � ����������";
		case 2: return "������� � ���������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class AdjectiveConstructionType;
typedef CMapFeature<8, 4, AdjectiveConstructionType> AdjectiveConstruction;
class AdjectiveConstructionType
	: public CBaseType
{
public:
	AdjectiveConstruction acOnlyAdjective;
	AdjectiveConstruction acItObjectPlus;
	AdjectiveConstruction acOneObjectPlus;
	AdjectiveConstruction acSubjectAnimateObjectPlus;
	AdjectiveConstructionType(void)
		: acOnlyAdjective(0)
		, acItObjectPlus(1)
		, acOneObjectPlus(2)
		, acSubjectAnimateObjectPlus(3)
	{
	}

	~AdjectiveConstructionType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "AdjectiveConstruction";};

	const char* GetTypeDescription() const {return "����������� ���������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "acOnlyAdjective";
		case 1: return "acItObjectPlus";
		case 2: return "acOneObjectPlus";
		case 3: return "acSubjectAnimateObjectPlus";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Only attribute";
		case 1: return "Complex predicate with subject It";
		case 2: return "Complex predicate with an object";
		case 3: return "Complex predicate with an object and animate subject";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class TypeOfEndingObjectType;
typedef CMapFeature<8, 24, TypeOfEndingObjectType> TypeOfEndingObject;
class TypeOfEndingObjectType
	: public CBaseType
{
public:
	TypeOfEndingObject Undefined;
	TypeOfEndingObject toeoObject;
	TypeOfEndingObject toeoRelatives;
	TypeOfEndingObject toeoAdv;
	TypeOfEndingObject toeoPreposition;
	TypeOfEndingObject toeoInf;
	TypeOfEndingObject toeoToInf;
	TypeOfEndingObject toeoIng;
	TypeOfEndingObject toeoThat;
	TypeOfEndingObject toeoAdjective;
	TypeOfEndingObject toeoPastPart;
	TypeOfEndingObject toeoCaseDat;
	TypeOfEndingObject toeoCaseGen;
	TypeOfEndingObject toeoCaseInstr;
	TypeOfEndingObject toeoThatBoodto;
	TypeOfEndingObject toeoThatBoodtoKakKakbiKakoy;
	TypeOfEndingObject toeoThatEsliKogda;
	TypeOfEndingObject toeoThatKakKakbi;
	TypeOfEndingObject toeoThatKakKakoyNaskolkoSkolko;
	TypeOfEndingObject toeoThatKakPochemu;
	TypeOfEndingObject toeoThatChtobiBoodto;
	TypeOfEndingObject toeoThatChtobiEsliKogda;
	TypeOfEndingObject toeoThatChtobiKakKakbi;
	TypeOfEndingObject toeoThatChtobiKakKogdaKakoy;
	TypeOfEndingObjectType(void)
		: Undefined(0)
		, toeoObject(1)
		, toeoRelatives(2)
		, toeoAdv(3)
		, toeoPreposition(4)
		, toeoInf(5)
		, toeoToInf(6)
		, toeoIng(7)
		, toeoThat(8)
		, toeoAdjective(9)
		, toeoPastPart(10)
		, toeoCaseDat(11)
		, toeoCaseGen(12)
		, toeoCaseInstr(13)
		, toeoThatBoodto(14)
		, toeoThatBoodtoKakKakbiKakoy(15)
		, toeoThatEsliKogda(16)
		, toeoThatKakKakbi(17)
		, toeoThatKakKakoyNaskolkoSkolko(18)
		, toeoThatKakPochemu(19)
		, toeoThatChtobiBoodto(20)
		, toeoThatChtobiEsliKogda(21)
		, toeoThatChtobiKakKakbi(22)
		, toeoThatChtobiKakKogdaKakoy(23)
	{
	}

	~TypeOfEndingObjectType(void){};

	unsigned int GetValueCount(void) const {return 24;};

	const char* GetTypeName() const {return "TypeOfEndingObject";};

	const char* GetTypeDescription() const {return "��� ���������� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "toeoObject";
		case 2: return "toeoRelatives";
		case 3: return "toeoAdv";
		case 4: return "toeoPreposition";
		case 5: return "toeoInf";
		case 6: return "toeoToInf";
		case 7: return "toeoIng";
		case 8: return "toeoThat";
		case 9: return "toeoAdjective";
		case 10: return "toeoPastPart";
		case 11: return "toeoCaseDat";
		case 12: return "toeoCaseGen";
		case 13: return "toeoCaseInstr";
		case 14: return "toeoThatBoodto";
		case 15: return "toeoThatBoodtoKakKakbiKakoy";
		case 16: return "toeoThatEsliKogda";
		case 17: return "toeoThatKakKakbi";
		case 18: return "toeoThatKakKakoyNaskolkoSkolko";
		case 19: return "toeoThatKakPochemu";
		case 20: return "toeoThatChtobiBoodto";
		case 21: return "toeoThatChtobiEsliKogda";
		case 22: return "toeoThatChtobiKakKakbi";
		case 23: return "toeoThatChtobiKakKogdaKakoy";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Value is not defined";
		case 1: return "Noun";
		case 2: return "Relative pronoun and adverb + (whether and if)";
		case 3: return "Adverb";
		case 4: return "Preposition";
		case 5: return "Infinitive without to";
		case 6: return "Infinitive with to";
		case 7: return "Present participle";
		case 8: return "That introducing subordinate clause";
		case 9: return "Adjective";
		case 10: return "Past Participle";
		case 11: return "Governs dative case";
		case 12: return "Governs genitive case";
		case 13: return "Governs instrumental case";
		case 14: return "That Budto";
		case 15: return "That Budto Kak Kakbi Kakoi";
		case 16: return "That Esli Kogda";
		case 17: return "That Kak Kakbi";
		case 18: return "That Kak Kakoy Naskolko Skolko";
		case 19: return "What Kak Pochemu";
		case 20: return "What Chtobi Budto";
		case 21: return "What Chtobi Esli Kogda";
		case 22: return "What Chtobi Kak Kakbi";
		case 23: return "What Chtobi Kak Kogda Kakoi";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class CombiTypeType;
typedef CMapFeature<8, 7, CombiTypeType> CombiType;
class CombiTypeType
	: public CBaseType
{
public:
	CombiType Undefined;
	CombiType cmbtNewLexicalUnit;
	CombiType cmbtVerbWithParticle;
	CombiType cmbtVerbOrAdjWithPrep;
	CombiType cmbtVerbWithPrepPart;
	CombiType cmbtPhrasalVerbWithPrep;
	CombiType cmbtNounWithPrep;
	CombiTypeType(void)
		: Undefined(0)
		, cmbtNewLexicalUnit(1)
		, cmbtVerbWithParticle(2)
		, cmbtVerbOrAdjWithPrep(3)
		, cmbtVerbWithPrepPart(4)
		, cmbtPhrasalVerbWithPrep(5)
		, cmbtNounWithPrep(6)
	{
	}

	~CombiTypeType(void){};

	unsigned int GetValueCount(void) const {return 7;};

	const char* GetTypeName() const {return "CombiType";};

	const char* GetTypeDescription() const {return "��� ��������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "cmbtNewLexicalUnit";
		case 2: return "cmbtVerbWithParticle";
		case 3: return "cmbtVerbOrAdjWithPrep";
		case 4: return "cmbtVerbWithPrepPart";
		case 5: return "cmbtPhrasalVerbWithPrep";
		case 6: return "cmbtNounWithPrep";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�������� �� ����������";
		case 1: return "����� ����������� �������";
		case 2: return "������ � ��������";
		case 3: return "������ ��� �������������� � ��������";
		case 4: return "������ � ��������� ��� �������";
		case 5: return "������ � �������� � ���������";
		case 6: return "��������������� � ���������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class SyntaxCategoriesType;
typedef CMapFeature<8, 32, SyntaxCategoriesType> SyntaxCategories;
class SyntaxCategoriesType
	: public CBaseType
{
public:
	SyntaxCategories Undefined;
	SyntaxCategories scSubjectFin;
	SyntaxCategories scSubjectInfin;
	SyntaxCategories scMain;
	SyntaxCategories scObject;
	SyntaxCategories scPrepositionObject;
	SyntaxCategories scAttribute;
	SyntaxCategories scSubjectComplement;
	SyntaxCategories scObjectComplement;
	SyntaxCategories scAjunct;
	SyntaxCategories scAjunctTimeSource;
	SyntaxCategories scAjunctTimeFixedPoint;
	SyntaxCategories scAjunctTimeEnd;
	SyntaxCategories scAjunctTimeDuration;
	SyntaxCategories scAjunctPlaceSource;
	SyntaxCategories scAjunctPlaceFixedPoint;
	SyntaxCategories scAjunctPlaceEnd;
	SyntaxCategories scAjunctGoal;
	SyntaxCategories scAjunctCause;
	SyntaxCategories scAjunctMeasure;
	SyntaxCategories scAjunctManner;
	SyntaxCategories scDeterminer;
	SyntaxCategories scChain;
	SyntaxCategories scObjectOfPreposition;
	SyntaxCategories scMainEntity;
	SyntaxCategories scAdditionalEntity;
	SyntaxCategories scPredicate;
	SyntaxCategories scWhoDefinition;
	SyntaxCategories scWhatDefinition;
	SyntaxCategories scNameDefinition;
	SyntaxCategories scVerbModifier;
	SyntaxCategories scTitle;
	SyntaxCategoriesType(void)
		: Undefined(0)
		, scSubjectFin(1)
		, scSubjectInfin(2)
		, scMain(3)
		, scObject(4)
		, scPrepositionObject(5)
		, scAttribute(6)
		, scSubjectComplement(7)
		, scObjectComplement(8)
		, scAjunct(9)
		, scAjunctTimeSource(10)
		, scAjunctTimeFixedPoint(11)
		, scAjunctTimeEnd(12)
		, scAjunctTimeDuration(13)
		, scAjunctPlaceSource(14)
		, scAjunctPlaceFixedPoint(15)
		, scAjunctPlaceEnd(16)
		, scAjunctGoal(17)
		, scAjunctCause(18)
		, scAjunctMeasure(19)
		, scAjunctManner(20)
		, scDeterminer(21)
		, scChain(22)
		, scObjectOfPreposition(23)
		, scMainEntity(24)
		, scAdditionalEntity(25)
		, scPredicate(26)
		, scWhoDefinition(27)
		, scWhatDefinition(28)
		, scNameDefinition(29)
		, scVerbModifier(30)
		, scTitle(31)
	{
	}

	~SyntaxCategoriesType(void){};

	unsigned int GetValueCount(void) const {return 32;};

	const char* GetTypeName() const {return "SyntaxCategories";};

	const char* GetTypeDescription() const {return "�������������� ��������� (��� �����)";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "scSubjectFin";
		case 2: return "scSubjectInfin";
		case 3: return "scMain";
		case 4: return "scObject";
		case 5: return "scPrepositionObject";
		case 6: return "scAttribute";
		case 7: return "scSubjectComplement";
		case 8: return "scObjectComplement";
		case 9: return "scAjunct";
		case 10: return "scAjunctTimeSource";
		case 11: return "scAjunctTimeFixedPoint";
		case 12: return "scAjunctTimeEnd";
		case 13: return "scAjunctTimeDuration";
		case 14: return "scAjunctPlaceSource";
		case 15: return "scAjunctPlaceFixedPoint";
		case 16: return "scAjunctPlaceEnd";
		case 17: return "scAjunctGoal";
		case 18: return "scAjunctCause";
		case 19: return "scAjunctMeasure";
		case 20: return "scAjunctManner";
		case 21: return "scDeterminer";
		case 22: return "scChain";
		case 23: return "scObjectOfPreposition";
		case 24: return "scMainEntity";
		case 25: return "scAdditionalEntity";
		case 26: return "scPredicate";
		case 27: return "scWhoDefinition";
		case 28: return "scWhatDefinition";
		case 29: return "scNameDefinition";
		case 30: return "scVerbModifier";
		case 31: return "scTitle";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "������������";
		case 1: return "����������";
		case 2: return "��������� ����������";
		case 3: return "���������";
		case 4: return "����������";
		case 5: return "���������� � ���������";
		case 6: return "�����������";
		case 7: return "���������� � �����������";
		case 8: return "���������� � ������� ����������";
		case 9: return "��������������";
		case 10: return "�������������� ������� - ��������� �����";
		case 11: return "�������������� ������� - ������������� �����";
		case 12: return "�������������� ������� - �������� �����";
		case 13: return "�������������� ������� - �������������";
		case 14: return "�������������� ����� - ��������� �����";
		case 15: return "�������������� ����� - ������������� �����";
		case 16: return "�������������� ����� - �������� �����";
		case 17: return "�������������� ����";
		case 18: return "�������������� �������";
		case 19: return "�������������� ����";
		case 20: return "�������������� ������ ��������";
		case 21: return "������������";
		case 22: return "����� ������ �������� ����������";
		case 23: return "���������� � ��������";
		case 24: return "������� ��������";
		case 25: return "�������������� ��������";
		case 26: return "��������";
		case 27: return "����������� � ������������� ��������";
		case 28: return "����������� � ��������������� ��������";
		case 29: return "����������� � �����";
		case 30: return "����������� �������";
		case 31: return "�������� ������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class HeadDependentTypeType;
typedef CMapFeature<8, 3, HeadDependentTypeType> HeadDependentType;
class HeadDependentTypeType
	: public CBaseType
{
public:
	HeadDependentType Undefined;
	HeadDependentType hdtHead;
	HeadDependentType hdtDependent;
	HeadDependentTypeType(void)
		: Undefined(0)
		, hdtHead(1)
		, hdtDependent(2)
	{
	}

	~HeadDependentTypeType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "HeadDependentType";};

	const char* GetTypeDescription() const {return "����������� �����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "hdtHead";
		case 2: return "hdtDependent";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "������������";
		case 1: return "������";
		case 2: return "��������� ���� �����������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class DependencyPowerType;
typedef CPercentFeature<DependencyPowerType> DependencyPower;
class DependencyPowerType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CPercentFeature";};

	const char* GetTypeDescription() const {return "�������� �����������";};

	const char* GetValueName(unsigned int n) const {return "DependencyPower";};

	const char* GetValueDescription(unsigned int n) const {return "���� �����";};

};


class SyntaxCategoryPowerType;
typedef CPercentFeature<SyntaxCategoryPowerType> SyntaxCategoryPower;
class SyntaxCategoryPowerType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CPercentFeature";};

	const char* GetTypeDescription() const {return "�������� �����������";};

	const char* GetValueName(unsigned int n) const {return "SyntaxCategoryPower";};

	const char* GetValueDescription(unsigned int n) const {return "�������� ����������� �������������� ���������";};

};


class SentenceTypeType;
typedef CMapFeature<8, 4, SentenceTypeType> SentenceType;
class SentenceTypeType
	: public CBaseType
{
public:
	SentenceType Undefined;
	SentenceType stStatement;
	SentenceType stImperative;
	SentenceType stInterrogative;
	SentenceTypeType(void)
		: Undefined(0)
		, stStatement(1)
		, stImperative(2)
		, stInterrogative(3)
	{
	}

	~SentenceTypeType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "SentenceType";};

	const char* GetTypeDescription() const {return "��� �����������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "stStatement";
		case 2: return "stImperative";
		case 3: return "stInterrogative";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "������������";
		case 1: return "�����������������";
		case 2: return "�������������";
		case 3: return "��������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class IdParentType;
typedef CIntegerFeature<IdParentType> IdParent;
class IdParentType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CIntegerFeature";};

	const char* GetTypeDescription() const {return "����� �������";};

	const char* GetValueName(unsigned int n) const {return "IdParent";};

	const char* GetValueDescription(unsigned int n) const {return "����� ��������";};

};


class ObjectsOrderType;
typedef CMapFeature<8, 3, ObjectsOrderType> ObjectsOrder;
class ObjectsOrderType
	: public CBaseType
{
public:
	ObjectsOrder ooDiscontinuous;
	ObjectsOrder ooContinuous;
	ObjectsOrder ooContinuousNotNeverAdverb;
	ObjectsOrderType(void)
		: ooDiscontinuous(0)
		, ooContinuous(1)
		, ooContinuousNotNeverAdverb(2)
	{
	}

	~ObjectsOrderType(void){};

	unsigned int GetValueCount(void) const {return 3;};

	const char* GetTypeName() const {return "ObjectsOrder";};

	const char* GetTypeDescription() const {return "������� ���������� ��������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "ooDiscontinuous";
		case 1: return "ooContinuous";
		case 2: return "ooContinuousNotNeverAdverb";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�����������";
		case 1: return "����������(������� ������ ���� �� ������)";
		case 2: return "����������(������� ������ ���� �� ������) �� �������� �������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class PositionToDetectedObjectType;
typedef CMapFeature<8, 4, PositionToDetectedObjectType> PositionToDetectedObject;
class PositionToDetectedObjectType
	: public CBaseType
{
public:
	PositionToDetectedObject Undefined;
	PositionToDetectedObject ptdoRight;
	PositionToDetectedObject ptdoLeft;
	PositionToDetectedObject ptdoLeftRight;
	PositionToDetectedObjectType(void)
		: Undefined(0)
		, ptdoRight(1)
		, ptdoLeft(2)
		, ptdoLeftRight(3)
	{
	}

	~PositionToDetectedObjectType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "PositionToDetectedObject";};

	const char* GetTypeDescription() const {return "��������� �� ��������� � ������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "ptdoRight";
		case 2: return "ptdoLeft";
		case 3: return "ptdoLeftRight";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "����� �� �������� �����������";
		case 1: return "������";
		case 2: return "�����";
		case 3: return "����� � ������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class ObjectObligationType;
typedef CMapFeature<8, 2, ObjectObligationType> ObjectObligation;
class ObjectObligationType
	: public CBaseType
{
public:
	ObjectObligation ecoNotObligatory;
	ObjectObligation ecoObligatory;
	ObjectObligationType(void)
		: ecoNotObligatory(0)
		, ecoObligatory(1)
	{
	}

	~ObjectObligationType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "ObjectObligation";};

	const char* GetTypeDescription() const {return "�������������� �����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "ecoNotObligatory";
		case 1: return "ecoObligatory";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ������������";
		case 1: return "������������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class AgreementTypeType;
typedef CMapFeature<8, 7, AgreementTypeType> AgreementType;
class AgreementTypeType
	: public CBaseType
{
public:
	AgreementType Undefined;
	AgreementType atGNC;
	AgreementType atNP;
	AgreementType atC;
	AgreementType atGN;
	AgreementType atGPN;
	AgreementType atN;
	AgreementTypeType(void)
		: Undefined(0)
		, atGNC(1)
		, atNP(2)
		, atC(3)
		, atGN(4)
		, atGPN(5)
		, atN(6)
	{
	}

	~AgreementTypeType(void){};

	unsigned int GetValueCount(void) const {return 7;};

	const char* GetTypeName() const {return "AgreementType";};

	const char* GetTypeDescription() const {return "��� ������������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "atGNC";
		case 2: return "atNP";
		case 3: return "atC";
		case 4: return "atGN";
		case 5: return "atGPN";
		case 6: return "atN";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ����������";
		case 1: return "��� ����� � �����";
		case 2: return "����� � ����";
		case 3: return "�����";
		case 4: return "��� � �����";
		case 5: return "��� ���� � �����";
		case 6: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class ScopeOfTheRuleType;
typedef CMapFeature<8, 5, ScopeOfTheRuleType> ScopeOfTheRule;
class ScopeOfTheRuleType
	: public CBaseType
{
public:
	ScopeOfTheRule Undefined;
	ScopeOfTheRule scpBlockBoundary;
	ScopeOfTheRule scpSentenceBoundary;
	ScopeOfTheRule scpParagraphBoundary;
	ScopeOfTheRule scpCommaBoundary;
	ScopeOfTheRuleType(void)
		: Undefined(0)
		, scpBlockBoundary(1)
		, scpSentenceBoundary(2)
		, scpParagraphBoundary(3)
		, scpCommaBoundary(4)
	{
	}

	~ScopeOfTheRuleType(void){};

	unsigned int GetValueCount(void) const {return 5;};

	const char* GetTypeName() const {return "ScopeOfTheRule";};

	const char* GetTypeDescription() const {return "������� �������� �������";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "scpBlockBoundary";
		case 2: return "scpSentenceBoundary";
		case 3: return "scpParagraphBoundary";
		case 4: return "scpCommaBoundary";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ����������";
		case 1: return "�� ����� �����";
		case 2: return "�� ����� �����������";
		case 3: return "� �������� ���������";
		case 4: return "�� �������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class PositionInBlockType;
typedef CMapFeature<8, 4, PositionInBlockType> PositionInBlock;
class PositionInBlockType
	: public CBaseType
{
public:
	PositionInBlock Undefined;
	PositionInBlock pibBegin;
	PositionInBlock pibMiddle;
	PositionInBlock pibEnd;
	PositionInBlockType(void)
		: Undefined(0)
		, pibBegin(1)
		, pibMiddle(2)
		, pibEnd(3)
	{
	}

	~PositionInBlockType(void){};

	unsigned int GetValueCount(void) const {return 4;};

	const char* GetTypeName() const {return "PositionInBlock";};

	const char* GetTypeDescription() const {return "";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "pibBegin";
		case 2: return "pibMiddle";
		case 3: return "pibEnd";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ����������";
		case 1: return "������";
		case 2: return "��������";
		case 3: return "�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class SameTypeObjectsNumberType;
typedef CIntegerFeature<SameTypeObjectsNumberType> SameTypeObjectsNumber;
class SameTypeObjectsNumberType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CIntegerFeature";};

	const char* GetTypeDescription() const {return "����� �������";};

	const char* GetValueName(unsigned int n) const {return "SameTypeObjectsNumber";};

	const char* GetValueDescription(unsigned int n) const {return "����������� �������� ������ ����";};

};


class ChildrenAnalysisDepthType;
typedef CMapFeature<8, 6, ChildrenAnalysisDepthType> ChildrenAnalysisDepth;
class ChildrenAnalysisDepthType
	: public CBaseType
{
public:
	ChildrenAnalysisDepth Undefined;
	ChildrenAnalysisDepth cadHeadsOnly;
	ChildrenAnalysisDepth cadHeadsAndCurrentGroupChildren;
	ChildrenAnalysisDepth cadFull;
	ChildrenAnalysisDepth cadChildren;
	ChildrenAnalysisDepth cadHeadsOnlyNextDetectElement;
	ChildrenAnalysisDepthType(void)
		: Undefined(0)
		, cadHeadsOnly(1)
		, cadHeadsAndCurrentGroupChildren(2)
		, cadFull(3)
		, cadChildren(4)
		, cadHeadsOnlyNextDetectElement(5)
	{
	}

	~ChildrenAnalysisDepthType(void){};

	unsigned int GetValueCount(void) const {return 6;};

	const char* GetTypeName() const {return "ChildrenAnalysisDepth";};

	const char* GetTypeDescription() const {return "������� ������� �����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "cadHeadsOnly";
		case 2: return "cadHeadsAndCurrentGroupChildren";
		case 3: return "cadFull";
		case 4: return "cadChildren";
		case 5: return "cadHeadsOnlyNextDetectElement";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ����������";
		case 1: return "������ ������, ��� ��������� ������ ��������";
		case 2: return "������ � ����, ��������� ������� ������� ���������";
		case 3: return "������ ������";
		case 4: return "������ ����";
		case 5: return "������ ������, � ���������� ������ ��������";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class SentenceNumberType;
typedef CIntegerFeature<SentenceNumberType> SentenceNumber;
class SentenceNumberType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CIntegerFeature";};

	const char* GetTypeDescription() const {return "";};

	const char* GetValueName(unsigned int n) const {return "SentenceNumber";};

	const char* GetValueDescription(unsigned int n) const {return "����� �����������";};

};


class SyntaxParamsInheritanceModeType;
typedef CMapFeature<8, 2, SyntaxParamsInheritanceModeType> SyntaxParamsInheritanceMode;
class SyntaxParamsInheritanceModeType
	: public CBaseType
{
public:
	SyntaxParamsInheritanceMode Undefined;
	SyntaxParamsInheritanceMode spimInherit;
	SyntaxParamsInheritanceModeType(void)
		: Undefined(0)
		, spimInherit(1)
	{
	}

	~SyntaxParamsInheritanceModeType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "SyntaxParamsInheritanceMode";};

	const char* GetTypeDescription() const {return "Syntax params inheritance mode";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "Undefined";
		case 1: return "spimInherit";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "Value is not defined";
		case 1: return "Inherit";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class BlockPositionType;
typedef CIntegerFeature<BlockPositionType> BlockPosition;
class BlockPositionType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CIntegerFeature";};

	const char* GetTypeDescription() const {return "";};

	const char* GetValueName(unsigned int n) const {return "BlockPosition";};

	const char* GetValueDescription(unsigned int n) const {return "���������� ����� ����� � �����������";};

};


class BlockSearchScopeType;
typedef CIntegerFeature<BlockSearchScopeType> BlockSearchScope;
class BlockSearchScopeType
	: public CBaseType
{
public:
	const char* GetTypeName() const {return "CIntegerFeature";};

	const char* GetTypeDescription() const {return "";};

	const char* GetValueName(unsigned int n) const {return "BlockSearchScope";};

	const char* GetValueDescription(unsigned int n) const {return "���������� ������ ��� ������ �� ������-�����";};

};


class CreateUnitType;
typedef CMapFeature<8, 2, CreateUnitType> CreateUnit;
class CreateUnitType
	: public CBaseType
{
public:
	CreateUnit cuDetect;
	CreateUnit cuCreate;
	CreateUnitType(void)
		: cuDetect(0)
		, cuCreate(1)
	{
	}

	~CreateUnitType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "CreateUnit";};

	const char* GetTypeDescription() const {return "������� ����� ����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "cuDetect";
		case 1: return "cuCreate";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ��������� ����";
		case 1: return "������� ����� ����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


class MoveTypeType;
typedef CMapFeature<8, 2, MoveTypeType> MoveType;
class MoveTypeType
	: public CBaseType
{
public:
	MoveType mtDoNotMove;
	MoveType mtMoveChild;
	MoveTypeType(void)
		: mtDoNotMove(0)
		, mtMoveChild(1)
	{
	}

	~MoveTypeType(void){};

	unsigned int GetValueCount(void) const {return 2;};

	const char* GetTypeName() const {return "MoveType";};

	const char* GetTypeDescription() const {return "��� ����������� �����";};

	const char* GetValueName(unsigned int n) const {
		switch(n){
		case 0: return "mtDoNotMove";
		case 1: return "mtMoveChild";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};

	const char* GetValueDescription(unsigned int n) const {
		switch(n){
		case 0: return "�� ����������";
		case 1: return "�����������  child-�����";
		default: SS_THROW(L"������������ ����� ��������");
		}
		return "������������ ����� ��������"; 
	};
};


			}
		}
	}
}
