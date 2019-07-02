#include "StdAfx.h"

#include ".\AMEnglishAnalyzer.h"

#include "assert.h"
#include "crtdbg.h"


namespace SS
{
namespace Core
{
namespace Features
{
//void CAMEnglishAnalyzer::Initialization(CMorphoFeature *morpho_feature)
//{
//	SS_TRY
//	{
//		morpho_feature->Undefine();
//
//		//morpho_feature->m_PartOfSpeechTypes.Undefine(); // ����� ����
//		//morpho_feature->m_AnimInAnimType.Undefine();    // ��������������
//		//morpho_feature->m_AspectType.Undefine();        // ��� ��������
//		//morpho_feature->m_AdverbType.Undefine();        // ��� �������
//		//morpho_feature->m_CaseType.Undefine();          // �����
//
//		//morpho_feature->m_CountType.Undefine();         // �������������
//		//morpho_feature->m_CommonType.Undefine();        // ��������������� 
//		//morpho_feature->m_DegreeType.Undefine();        // ������� ���������
//		//morpho_feature->m_GenderType.Undefine();        // ���
//		//morpho_feature->m_NumberType.Undefine();        // �����
//
//		//morpho_feature->m_NumericType.Undefine();       // ��� �������������
//		//morpho_feature->m_NegativeType.Undefine();      // �������������� ���������
//		//morpho_feature->m_OfficialType.Undefine();      // ��� ��������� ����� ����
//		//morpho_feature->m_PhaseVerbType.Undefine();     // ����������
//		//morpho_feature->m_PersonType.Undefine();        // ����
//
//		//morpho_feature->m_PronounGroup.Undefine();      // ������ �����������
//		//morpho_feature->m_PronounClass.Undefine();      // ����� �����������
//		//morpho_feature->m_ShortType.Undefine();         // ���������
//		//morpho_feature->m_AdverbClass.Undefine();       // ����� �������
//		//morpho_feature->m_ConjunctionType.Undefine();   // ��� �����
//
//
//		//morpho_feature->m_DeterminerType.Undefine();    // ��� ������������
//		//morpho_feature->m_TimeType.Undefine();          // �����
//		//morpho_feature->m_TransitionalType.Undefine();  // ������������
//		//morpho_feature->m_VoiceType.Undefine();         // �����
//		//morpho_feature->m_VerbForm.Undefine();          // ����� �������
//
//		//morpho_feature->m_VerbType.Undefine();          // ��� �������
//		//morpho_feature->m_MoodType.Undefine();          // ���������� �������
//	}
//	SS_CATCH(L"")
//}


//////////////////////////////////////////////////////////////////////////////////
/////////////////*		������ ��������������		*/////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void CAMEnglishAnalyzer::BackInit()
{

	SS_TRY
	{
		m_mi_Verb.Empty			= 0;
		m_mi_Noun.Empty			= 0 ;
		m_mi_Numerals.Empty		= 0;
		m_mi_Adjective.Empty	= 0;
		m_mi_Adverb.Empty		= 0;
		m_mi_Pronoun.Empty		= 0;
		m_mi_Official.Empty		= 0;
		
		m_pos_Noun.Empty		= 0;
		m_pos_Verb.Empty		= 0;
		m_pos_Numeral.Empty		= 0;
		m_pos_Adjective.Empty	= 0;
		m_pos_Adverb.Empty		= 0;
		m_pos_Pronoun.Empty		= 0;
		m_mi_Base.Empty			= 0;
	}
	SS_CATCH(L"")
}

void CAMEnglishAnalyzer::MorphoInfoBackAnalyzer(const CMorphoFeature *pMorphoFeature, int *MorphoInfo, int *PartOfSpeech)
{

	SS_TRY
	{
		unsigned char uchBaseMI = 0;
		unsigned char uchAddMI  = 0;

		///*	�������� ������ MorphoInfo	*/
		m_mi_Base.NegativeType		= pMorphoFeature->m_NegativeType.GetSingleValue();
		m_mi_Base.PartOfSpeechTypes	= pMorphoFeature->m_PartOfSpeechTypes.GetSingleValue();
		m_mi_Base.SemanticsTypes	= 0;

		memcpy(&uchBaseMI, &m_mi_Base, 1);
		*MorphoInfo =  uchBaseMI<<8;

	// �������� ��������
		// �������� ��������� ������ �� �����
		memcpy(&uchBaseMI, &m_mi_Base, 1);	

		if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postOfficial)){	// ��������� ����� ����		
			m_mi_Official.OfficialType = pMorphoFeature->m_OfficialType.GetSingleValue();
			m_mi_Official.ConjunctionType = pMorphoFeature->m_ConjunctionType.GetSingleValue();
			m_mi_Official.DeterminerType = pMorphoFeature->m_DeterminerType.GetSingleValue();
				
			memcpy(&uchAddMI, &m_mi_Official, 1);
			*MorphoInfo += uchAddMI;
	//		BackAnalyzerOfficial(PartOfSpeech, SpecialMorpho,pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postVerb)){		// ������� � �����
			m_mi_Verb.Transitivity = pMorphoFeature->m_TransitionalType.GetSingleValue();
			m_mi_Verb.VerbType = pMorphoFeature->m_VerbType.GetSingleValue();
			memcpy(&uchAddMI, &m_mi_Verb, 1);
			*MorphoInfo += uchAddMI;
			CodeVerbs(PartOfSpeech, pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun)){		// ���������������
			m_mi_Noun.AnimInAnimType	= pMorphoFeature->m_AnimInAnimType.GetSingleValue();
			m_mi_Noun.CountType		= pMorphoFeature->m_CountType.GetSingleValue();
			m_mi_Noun.GenderType		= pMorphoFeature->m_GenderType.GetSingleValue();

			memcpy(&uchAddMI, &m_mi_Noun, 1);
			*MorphoInfo += uchAddMI;
			CodeNouns(PartOfSpeech, pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postAdjective)){	// ��������������
			CodeAdjectives(PartOfSpeech, pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNumeric)){	// ������������	
			CodeNumbers(PartOfSpeech, pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postAdverb)){	// �������
			m_mi_Adverb.AdverbType	= pMorphoFeature->m_AdverbType.GetSingleValue();
			m_mi_Adverb.AdverbClass = pMorphoFeature->m_AdverbClass.GetSingleValue();
			memcpy(&uchAddMI, &m_mi_Adverb, 1);
			*MorphoInfo += uchAddMI;
			CodeAdverbs(PartOfSpeech, pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postPronoun)){	// �����������
			m_mi_Pronoun.GenderType	= pMorphoFeature->m_GenderType.GetSingleValue();
			m_mi_Pronoun.PersonType	= pMorphoFeature->m_PersonType.GetSingleValue();
			m_pos_Pronoun.PronounGroup= pMorphoFeature->m_PronounGroup.GetSingleValue();
			
			memcpy(&uchAddMI, &m_mi_Pronoun, 1);
			*MorphoInfo += uchAddMI;
			CodePronouns(PartOfSpeech, pMorphoFeature);
		}
		else{
			*MorphoInfo = 0;
			*PartOfSpeech = 0;
		}
	}
	SS_CATCH(L"")


}


void CAMEnglishAnalyzer::Code(/*in*/const CMorphoFeature *pMorphoFeature, /*out*/int *piMorphoInfo, /*out*/int *piPartOfSpeech)
{
	SS_TRY
	{
		BackInit();
		MorphoInfoBackAnalyzer(pMorphoFeature, piMorphoInfo, piPartOfSpeech);
	}
	SS_CATCH(L"")


}

void CAMEnglishAnalyzer::EnCodePronouns( int iPartOfSpeech, CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{		
		memcpy( &m_pos_Pronoun, &iPartOfSpeech, 2);
		pMorphoFeature->m_CaseType			= m_pos_Pronoun.CaseType;
		pMorphoFeature->m_NumberType		= m_pos_Pronoun.NumberType;
		pMorphoFeature->m_PronounClass		= m_pos_Pronoun.PronounClass;
		pMorphoFeature->m_PronounGroup		= m_pos_Pronoun.PronounGroup;
		pMorphoFeature->m_AnimInAnimType	= m_pos_Pronoun.AnimInAnimType;
	}
	SS_CATCH(L"")


}
void CAMEnglishAnalyzer::EnCodeAdverbs(int iPartOfSpeech, CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		memcpy( &m_pos_Adverb, &iPartOfSpeech, 2);
		pMorphoFeature->m_DegreeType = m_pos_Adverb.DegreeType;
	}
	SS_CATCH(L"")

}
void CAMEnglishAnalyzer::EnCodeNumbers(int iPartOfSpeech, CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		memcpy( &m_pos_Numeral, &iPartOfSpeech, 2);
		pMorphoFeature->m_NumericType = m_pos_Numeral.NumericType;

	}
	SS_CATCH(L"")

}
void CAMEnglishAnalyzer::EnCodeAdjectives(int iPartOfSpeech, CMorphoFeature *pMorphoFeature)

{
	SS_TRY
	{
		memcpy( &m_pos_Adjective, &iPartOfSpeech, 2);
		pMorphoFeature->m_DegreeType = m_pos_Adjective.DegreeType;

	}
	SS_CATCH(L"")

}
void CAMEnglishAnalyzer::EnCodeVerbs(int iPartOfSpeech, CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		memcpy( &m_pos_Verb, &iPartOfSpeech, 2);
		pMorphoFeature->m_NumberType = m_pos_Verb.NumberType;
		pMorphoFeature->m_PersonType = m_pos_Verb.PersonType;
		pMorphoFeature->m_TimeType = m_pos_Verb.TimeType;
		pMorphoFeature->m_VerbForm = m_pos_Verb.VerbForm;	
		pMorphoFeature->m_VoiceType= m_pos_Verb.VoiceType;	
	}
	SS_CATCH(L"")


}

void CAMEnglishAnalyzer::EnCodeNouns(int iPartOfSpeech, CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		memcpy( &m_pos_Noun, &iPartOfSpeech, 2);
		pMorphoFeature->m_NumberType= m_pos_Noun.NumberType;
		pMorphoFeature->m_CaseType	= m_pos_Noun.CaseType;
	}
	SS_CATCH(L"")

}



void CAMEnglishAnalyzer::CodePronouns(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		if(
			(pMorphoFeature->m_NumberType.IsIntersectsWith(&SS::Core::Features::Values::NumberType.ntSingle))&&
			(pMorphoFeature->m_NumberType.IsIntersectsWith(&SS::Core::Features::Values::NumberType.ntPlural))
			)
		{
			m_pos_Pronoun.NumberType = 0;
		}else
		{
			m_pos_Pronoun.NumberType = pMorphoFeature->m_NumberType.GetSingleValue();
		}		

		m_pos_Pronoun.CaseType		= pMorphoFeature->m_CaseType.GetSingleValue();
		m_pos_Pronoun.PronounClass	= pMorphoFeature->m_PronounClass.GetSingleValue();
		m_pos_Pronoun.AnimInAnimType	= pMorphoFeature->m_AnimInAnimType.GetSingleValue();
		memcpy( iPartOfSpeech, &m_pos_Pronoun, 2);
	}
	SS_CATCH(L"")


}
void CAMEnglishAnalyzer::CodeAdverbs(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		m_pos_Adverb.DegreeType = pMorphoFeature->m_DegreeType.GetSingleValue();		
		memcpy( &iPartOfSpeech, &m_pos_Adverb, 2);
	}
	SS_CATCH(L"")


}
void CAMEnglishAnalyzer::CodeNumbers(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		m_pos_Numeral.NumericType = pMorphoFeature->m_NumericType.GetSingleValue();		
		memcpy( &iPartOfSpeech, &m_pos_Numeral, 2);
	}
	SS_CATCH(L"")

}
void CAMEnglishAnalyzer::CodeAdjectives(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		m_pos_Adjective.DegreeType = pMorphoFeature->m_DegreeType.GetSingleValue();
		memcpy( &iPartOfSpeech, &m_pos_Adjective, 2);
	}
	SS_CATCH(L"")

}
void CAMEnglishAnalyzer::CodeVerbs(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		if(
			(pMorphoFeature->m_NumberType.IsIntersectsWith(&SS::Core::Features::Values::NumberType.ntSingle))&&
			(pMorphoFeature->m_NumberType.IsIntersectsWith(&SS::Core::Features::Values::NumberType.ntPlural)))
		{
			m_pos_Verb.NumberType = 0;
		}else
		{
			m_pos_Verb.NumberType = pMorphoFeature->m_NumberType.GetSingleValue();
		}
		
		m_pos_Verb.PersonType	= pMorphoFeature->m_PersonType.GetSingleValue();
		m_pos_Verb.TimeType		= pMorphoFeature->m_TimeType.GetSingleValue();
		m_pos_Verb.VerbForm		= pMorphoFeature->m_VerbForm.GetSingleValue();
		m_pos_Verb.VoiceType	= pMorphoFeature->m_VoiceType.GetSingleValue();
		memcpy( &iPartOfSpeech, &m_pos_Verb, 2);
	}
	SS_CATCH(L"")

}

void CAMEnglishAnalyzer::CodeNouns(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		assert(_CrtCheckMemory());

		if(
			(pMorphoFeature->m_NumberType.IsIntersectsWith(&SS::Core::Features::Values::NumberType.ntSingle))&&
			(pMorphoFeature->m_NumberType.IsIntersectsWith(&SS::Core::Features::Values::NumberType.ntPlural))
			)
		{
			m_pos_Noun.NumberType = 0;
		}else
		{
			m_pos_Noun.NumberType = pMorphoFeature->m_NumberType.GetSingleValue();
		}		
		m_pos_Noun.CaseType		= pMorphoFeature->m_CaseType.GetSingleValue();

		memcpy( &iPartOfSpeech, &m_pos_Noun, 2);
	}
	SS_CATCH(L"")

}

void CAMEnglishAnalyzer::EnCode(/*in*/int iMorphoInfo, /*in*/int iPartOfSpeech, /*out*/CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		pMorphoFeature->Undefine();
		//Initialization(pMorphoFeature);
		MorphoInfoAnalyzer(iMorphoInfo, iPartOfSpeech, pMorphoFeature);
	}
	SS_CATCH(L"")

}

void CAMEnglishAnalyzer::MorphoInfoAnalyzer(int iMorphoInfo, int iPartOfSpeech, CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		unsigned char uchBaseMI = iMorphoInfo>>8;
		unsigned char uchAddMI = (iMorphoInfo<<24)>>24;
		memcpy(&m_mi_Base, &uchBaseMI, 1);		
		
		pMorphoFeature->m_NegativeType = m_mi_Base.NegativeType;
		pMorphoFeature->m_PartOfSpeechTypes = m_mi_Base.PartOfSpeechTypes;

		if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postOfficial)){	// ��������� ����� ����
			memcpy(&m_mi_Official, &uchAddMI, 1);	
			pMorphoFeature->m_OfficialType = m_mi_Official.OfficialType;
			pMorphoFeature->m_ConjunctionType = m_mi_Official.ConjunctionType;
			pMorphoFeature->m_DeterminerType = m_mi_Official.DeterminerType;
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postVerb)){		// ������� � �����
			memcpy(&m_mi_Verb, &uchAddMI, 1);	
			pMorphoFeature->m_TransitionalType = m_mi_Verb.Transitivity;
			pMorphoFeature->m_VerbType = m_mi_Verb.VerbType;
			EnCodeVerbs(iPartOfSpeech, pMorphoFeature);

			PostAnalyseNumberType(pMorphoFeature);

		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun)){		// ���������������
			memcpy(&m_mi_Noun, &uchAddMI, 1);	
			pMorphoFeature->m_AnimInAnimType = m_mi_Noun.AnimInAnimType;
			pMorphoFeature->m_CountType = m_mi_Noun.CountType;
			pMorphoFeature->m_GenderType = m_mi_Noun.GenderType;
			EnCodeNouns(iPartOfSpeech, pMorphoFeature);

			PostAnalyseNumberType(pMorphoFeature);
			PostAnalyseCaseType(pMorphoFeature);

		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postAdjective)){ // ��������������
			// � MorphoInfo  ������ ������ �� ��������
			EnCodeAdjectives(iPartOfSpeech, pMorphoFeature);

			PostAnalyseNumberType(pMorphoFeature);

		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNumeric)){	// ������������
			EnCodeNumbers(iPartOfSpeech, pMorphoFeature);

		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postAdverb)){	// �������
			memcpy(&m_mi_Adverb, &uchAddMI, 1);
			pMorphoFeature->m_AdverbType = m_mi_Adverb.AdverbType;
			pMorphoFeature->m_AdverbClass = m_mi_Adverb.AdverbClass;
			EnCodeAdverbs(iPartOfSpeech, pMorphoFeature);
		}
		else if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postPronoun)){	// �����������
			memcpy(&m_mi_Pronoun, &uchAddMI, 1);

			pMorphoFeature->m_GenderType = m_mi_Pronoun.GenderType;
			pMorphoFeature->m_PersonType = m_mi_Pronoun.PersonType;
			EnCodePronouns(iPartOfSpeech, pMorphoFeature);
                                          
			PostAnalyseNumberType(pMorphoFeature);

		}
		else{
			pMorphoFeature->m_PartOfSpeechTypes.Undefine();


			PostAnalyseCaseType(pMorphoFeature);
		
		}
	}
	SS_CATCH(L"")
}

void CAMEnglishAnalyzer::PostAnalyseCaseType(CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		/*	��� ��������������� ���������� ������ ����� ���	*/
		if(pMorphoFeature->m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun))
		{
			if(pMorphoFeature->m_CaseType.Equal(Values::CaseType.Undefined))
			{
				pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctCommon);
			}
		
		}
		else
			/*	��� ���� ��������� ������ ���� ���������� ����� �����	*/
            if(pMorphoFeature->m_CaseType.Equal(Values::CaseType.Undefined))
		{
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctNominative);
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctGenitive);
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctDative);
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctAccusative);
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctInstrumental);
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctLocative);
			pMorphoFeature->m_CaseType.AssignOR(&Values::CaseType.ctCommon);
		}
	}
	SS_CATCH(L"")
}


void CAMEnglishAnalyzer::PostAnalyseNumberType(CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		if(pMorphoFeature->m_NumberType.Equal(Values::NumberType.Undefined))
		{
			pMorphoFeature->m_NumberType.AssignOR(&Values::NumberType.ntSingle);
			pMorphoFeature->m_NumberType.AssignOR(&Values::NumberType.ntPlural);
		}
	}
	SS_CATCH(L"")
}

void CAMEnglishAnalyzer::PostAnalyseGenderType(CMorphoFeature *pMorphoFeature)
{
	SS_TRY
	{
		/*	���� ��� �����, �� ��� ������������� � ������� � �������	*/
		if(pMorphoFeature->m_GenderType.Equal(Values::GenderType.gtGeneral))
		{
			pMorphoFeature->m_GenderType.AssignOR(&Values::GenderType.gtFemale);
			pMorphoFeature->m_GenderType.AssignOR(&Values::GenderType.gtMasculine);
		}
		else
			/*	���� ��� �����������	*/
			if(pMorphoFeature->m_GenderType.Equal(Values::GenderType.Undefined))
		{
			pMorphoFeature->m_GenderType.AssignOR(&Values::GenderType.gtFemale);
			pMorphoFeature->m_GenderType.AssignOR(&Values::GenderType.gtMasculine);
			pMorphoFeature->m_GenderType.AssignOR(&Values::GenderType.gtNeutral);
		}
	}
	SS_CATCH(L"")
}

}
}
}