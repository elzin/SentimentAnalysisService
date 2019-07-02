// bitfieldsstructures
#pragma once

namespace SS
{
namespace MorphoFeaturesCoding
{

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*! \struct BASE_MORPHO_INFO
*  \brief     �������� ������� ����� ��������������� ������������� ��� �����������
*/
struct  BASE_MORPHO_INFO{
unsigned char
	SemanticsTypes		:3, // ������������� ��������������
	NegativeType		:NEGATIVETYPE_BIT_SIZE,	// ���������				
	PartOfSpeechTypes	:PARTOFSPEECHTYPES_BIT_SIZE,// ����� ����				
	Empty				:1; 
BASE_MORPHO_INFO() : SemanticsTypes(0),  NegativeType(0), PartOfSpeechTypes(0), Empty(0)
{}
} ;


namespace English
{
//////////////////////////////////////////////////////////////////////////

/*! \struct VERBS_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
*/
struct  VERBS_MORPHO_INFO{
	unsigned char
		Transitivity		:TRANSITIONALTYPE_BIT_SIZE, // ������������� ��������������
		VerbType			:VERBTYPE_BIT_SIZE,	// ��� �������				
		Empty				:4;	// ������ ����				
	VERBS_MORPHO_INFO() : Transitivity(0), VerbType(0), Empty(0)
	{}
} ;

/*! \struct VERBS_PART_OF_SPEECH
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
*/
struct  VERBS_PART_OF_SPEECH{
	unsigned short
		VerbForm				:VERBFORM_BIT_SIZE,	// ����� �������
		TimeType 				:TIMETYPE_BIT_SIZE,	// ����� �������
		PersonType				:PERSONTYPE_BIT_SIZE,	// ����			
		NumberType				:NUMBERTYPE_BIT_SIZE,	// �����
		VoiceType				:VOICETYPE_BIT_SIZE,	// �����
		Empty					:5;	// ������ ����		
	VERBS_PART_OF_SPEECH() : VerbForm(0), TimeType(0), PersonType(0), NumberType(0), Empty(0), VoiceType(0)
	{}
} ;


//////////////////////////////////////////////////////////////////////////


/*! \struct NOUNS_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������������
*/			
struct  NOUNS_MORPHO_INFO{
	unsigned char
		AnimInAnimType		:ANIMINANIMTYPE_BIT_SIZE, // ��������������
		GenderType			:GENDERTYPE_BIT_SIZE,	// ���				
		CountType			:COUNTTYPE_BIT_SIZE,	// �������������			
		Empty				:1;	// ������ ����				
	NOUNS_MORPHO_INFO() : Empty(0), CountType(0), GenderType(0), AnimInAnimType(0)
	{
	}
} ;

/*! \struct NOUNS_PART_OF_SPEECH
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������������
*/			
struct  NOUNS_PART_OF_SPEECH{
	unsigned short
		NumberType			:NUMBERTYPE_BIT_SIZE,	// �����
		CaseType			:CASETYPE_BIT_SIZE,		// �����
		Empty				:11;					// ������ ����				
	NOUNS_PART_OF_SPEECH() : Empty(0), CaseType(0), NumberType(0)
	{}
} ;

//////////////////////////////////////////////////////////////////////////


/*! \struct NUMERALS_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
*/			
struct  NUMERALS_MORPHO_INFO{
	unsigned char
		Empty				:8;	// ������ ����				
	NUMERALS_MORPHO_INFO() : Empty(0)
	{
	}
} ;

/*! \struct NUMERALS_PART_OF_SPEECH
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
*/			
struct  NUMERALS_PART_OF_SPEECH{
	unsigned short
		NumericType			:NUMERICTYPE_BIT_SIZE, // ��� �������������
		Empty				:14;// ������ ����				
	NUMERALS_PART_OF_SPEECH() : NumericType(0), Empty(0)
	{}
} ;
//////////////////////////////////////////////////////////////////////////

/*! \struct ADJECTIVES_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������������
*/			
struct  ADJECTIVES_MORPHO_INFO{
	unsigned char
		Empty				:8;	// ������ ����				
	ADJECTIVES_MORPHO_INFO() : Empty(0)
	{}
} ;

/*! \struct ADJECTIVES_PART_OF_SPEECH
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������������
*/			
struct  ADJECTIVES_PART_OF_SPEECH{
	unsigned short
		DegreeType			:DEGREETYPE_BIT_SIZE,	// ������� ���������
		Empty				:14;// ������ ����				
	ADJECTIVES_PART_OF_SPEECH() : DegreeType(0), Empty(0)
	{}
} ;

//////////////////////////////////////////////////////////////////////////


/*! \struct ADVERBS_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
*/			
struct  ADVERBS_MORPHO_INFO{
	unsigned char
		AdverbType			:ADVERBTYPE_BIT_SIZE, // ��� �������
		AdverbClass			:ADVERBCLASS_BIT_SIZE, // ����� �������
		Empty				:2;	// ������ ����							
	ADVERBS_MORPHO_INFO() : AdverbType(0), AdverbClass(0), Empty(0)
	{}
} ;

/*! \struct ADVERBS_PART_OF_SPEECH
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
*/			
struct  ADVERBS_PART_OF_SPEECH{
	unsigned short
		DegreeType			:DEGREETYPE_BIT_SIZE,	// ������� ���������
		Empty				:14;// ������ ����				
	ADVERBS_PART_OF_SPEECH(): DegreeType(0),  Empty(0)
	{}
} ;
//////////////////////////////////////////////////////////////////////////


/*! \struct PRONOUNS_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
*/			
struct  PRONOUNS_MORPHO_INFO{
	unsigned char
		GenderType			:GENDERTYPE_BIT_SIZE,	// ���				
		PersonType			:PERSONTYPE_BIT_SIZE,	// ����				
		Empty				:sizeof(unsigned char) * CHAR_BIT - 
                    GENDERTYPE_BIT_SIZE - PERSONTYPE_BIT_SIZE;	// ������ ����
	PRONOUNS_MORPHO_INFO() : Empty(0), PersonType(0), GenderType(0)
	{}
} ;	

/*! \struct PRONOUNS_PART_OF_SPEECH
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
*/			
struct  PRONOUNS_PART_OF_SPEECH{
	unsigned short
		PronounGroup		:PRONOUNGROUP_BIT_SIZE, // ������ ����������� 
		PronounClass		:PRONOUNCLASS_BIT_SIZE,	// ����� �����������
		CaseType			:CASETYPE_BIT_SIZE,	// �����	
		NumberType			:NUMBERTYPE_BIT_SIZE,	// �����
		AnimInAnimType		:ANIMINANIMTYPE_BIT_SIZE,
		Empty				:sizeof(unsigned short) * CHAR_BIT - 
                    PRONOUNGROUP_BIT_SIZE - PRONOUNCLASS_BIT_SIZE - 
                    CASETYPE_BIT_SIZE - NUMBERTYPE_BIT_SIZE - ANIMINANIMTYPE_BIT_SIZE;// ������ ����				
	PRONOUNS_PART_OF_SPEECH() : PronounClass(0), CaseType(0), NumberType(0), AnimInAnimType(0), PronounGroup(0), Empty(0)
	{}
} ;
//////////////////////////////////////////////////////////////////////////


/*! \struct OFFICIAL_MORPHO_INFO
*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������� ������ ����
*/			
struct  OFFICIAL_MORPHO_INFO{
	unsigned short
		OfficialType	:OFFICIALTYPE_BIT_SIZE,	// ��������� ����� ����
		ConjunctionType :CONJUNCTIONTYPE_BIT_SIZE,	// ��� �����
		DeterminerType	:DETERMINERTYPE_BIT_SIZE, // ��� ������������
		Empty			:1;	// ������ ����
	OFFICIAL_MORPHO_INFO() : OfficialType(0), ConjunctionType(0), DeterminerType(0), Empty(0)
	{}
} ;

};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//	namespace RUSSIAN
//	{
//		////////////////////////////////////////////////////////////////////////////////////
//		////////////////////////////////////////////////////////////////////////////////////
//		///*! \struct MORPHO_INFO
//		//*  \brief     �������� ������� ����� ��������������� ������������� ��� ����������� 
//		//*/			
//		//		struct  MORPHO_INFO {
//		//			unsigned short
//		//				PartOfSpeechTypes	:PARTOFSPEECHTYPES_BIT_SIZE,	// ����� ����
//		//				SemanticsTypes		:3, 	// ������������� ��������������
//		//				NegativeType		:NEGATIVETYPE_BIT_SIZE,	// ���������
//		//				EmptyBits			:9;	// ������ ����
//		//		} ;

//		///*! \struct PART_OF_SPEECH_OFFICIAL
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������� ������ ����
//		//*/			
//		//		struct  PART_OF_SPEECH_OFFICIAL{
//		//			unsigned short
//		//				OfficialType	:OFFICIALTYPE_BIT_SIZE,	// ��������� ����� ����
//		//				EmptyBits		:12;	// ������ ����
//		//		} ;

//		///*! \struct SPECIAL_MORPHO_PRETEXT
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������
//		//*/			
//		//		struct  SPECIAL_MORPHO_PRETEXT{
//		//			unsigned short
//		//				CaseType		:CASETYPE_BIT_SIZE,	// �����
//		//				EmptyBits		:13;	// ������ ����
//		//		};

//		///*! \struct PART_OF_SPEECH_ADJECTIVE_NOUN_OTHER
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������������, �������������� � �� ������ ����
//		//*/			
//		//		struct  PART_OF_SPEECH_ADJECTIVE_NOUN_OTHER{
//		//			unsigned short
//		//				CaseType		:CASETYPE_BIT_SIZE,	//�����
//		//				GenderType		:GENDERTYPE_BIT_SIZE,	//���				
//		//				NumberType		:NUMBERTYPE_BIT_SIZE,	//����� 
//		//				AnimInAnimType	:ANIMINANIMTYPE_BIT_SIZE,	//��������������	
//		//				EmptyBits		:6;	//������ ����
//		//		} ;


//		///*! \struct SPECIAL_MORPHO_ADJECTIVE
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������������
//		//*/			
//		//		struct  SPECIAL_MORPHO_ADJECTIVE{
//		//			unsigned short
//		//			ShortType	:SHORTTYPE_BIT_SIZE,	//���������
//		//			DegreeType	:DEGREETYPE_BIT_SIZE,	//������� ���������
//		//			PhaseVerbType	:PHASEVERBTYPE_BIT_SIZE,	//����������
//		//			// NegativeType	:NEGATIVETYPE_BIT_SIZE,	//���������
//		//			EmptyBits		:11;	// ������ ����
//		//		} ;

//		///*! \struct SPECIAL_MORPHO_PRONOUN
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
//		//*/				
//		//		struct  SPECIAL_MORPHO_PRONOUN{
//		//			unsigned short
//		//				PronounGroup	:PRONOUNGROUP_BIT_SIZE,	//������ �����������
//		//				PronounClass	:PRONOUNCLASS_BIT_SIZE,	//������ �����������
//		//				PersonType	:PERSONTYPE_BIT_SIZE,	//����
//		//				EmptyBits		:8;	// ������ ����
//		//			SPECIAL_MORPHO_PRONOUN() : PronounGroup(0), PronounClass(0), PersonType(0), EmptyBits(0) {}
//		//		} ;

//		///*! \struct SPECIAL_MORPHO_NUMERAL
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
//		//*/				
//		//		struct  SPECIAL_MORPHO_NUMERAL{
//		//			unsigned short
//		//				NumericType		:NUMERICTYPE_BIT_SIZE,	//��� �������������
//		//				EmptyBits			:14;	// ������ ����
//		//		} ;

//		///*! \struct PART_OF_SPEECH_ADVERB
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
//		//*/				
//		//		struct  PART_OF_SPEECH_ADVERB{
//		//			unsigned short
//		//				AdverbType	:ADVERBTYPE_BIT_SIZE,	//��� ������� 
//		//				EmptyBits		:12;	//������ ����
//		//		} ;

//		///*! \struct PART_OF_SPEECH_VERB
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
//		//*/				
//		//		struct  PART_OF_SPEECH_VERB{
//		//			unsigned short
//		//				VerbForm			:VERBFORM_BIT_SIZE,	// ����� �������
//		//				AspectType			:ASPECTTYPE_BIT_SIZE,	// ��� �������
//		//				TransitionalType	:1,	// ������������					 
//		//				VoiceType			:VOICETYPE_BIT_SIZE,	//�����	
//		//				VerbType			:VERBTYPE_BIT_SIZE,	// ����� �������
//		//				EmptyBits			:6;	//������ ����					 
//		//		} ;

//		///*! \struct SPECIAL_MORPHO_VERB_PERSONAL
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������ ��������
//		//*/		
//		//		struct  SPECIAL_MORPHO_VERB_PERSONAL{
//		//			unsigned short
//		//				TimeType		:TIMETYPE_BIT_SIZE,	// ����� �������
//		//				NumberType	:NUMBERTYPE_BIT_SIZE,	//����� 
//		//				GenderType	:GENDERTYPE_BIT_SIZE,	//���				
//		//				PhaseVerbType	:PHASEVERBTYPE_BIT_SIZE,	//����������
//		//				PersonType	:PERSONTYPE_BIT_SIZE,	//����			
//		//				EmptyBits		:5;	//������ ����					 
//		//		} ;

//		///*! \struct SPECIAL_MORPHO_VERB_IMPERSONAL
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������� ��������
//		//*/		
//		//		struct  SPECIAL_MORPHO_VERB_IMPERSONAL{
//		//			unsigned short
//		//				TimeType		:TIMETYPE_BIT_SIZE,	//����� �������
//		//				NumberType	:NUMBERTYPE_BIT_SIZE,	//����� 
//		//				GenderType	:GENDERTYPE_BIT_SIZE,	//���				
//		//				EmptyBits		:9;	//������ ����					 
//		//		} ;

//		///*! \struct SPECIAL_MORPHO_PARTICIPLE
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ����������
//		//*/		
//		//		struct  SPECIAL_MORPHO_PARTICIPLE{
//		//			unsigned short
//		//				TimeType		:TIMETYPE_BIT_SIZE,	//����� �������
//		//				NumberType		:NUMBERTYPE_BIT_SIZE,	//����� 
//		//				GenderType		:GENDERTYPE_BIT_SIZE,	//���	
//		//				CaseType		:CASETYPE_BIT_SIZE,	//�����
//		//				AnimInAnimType	:ANIMINANIMTYPE_BIT_SIZE,	//��������������
//		//				ShortType		:SHORTTYPE_BIT_SIZE,	//���������
//		//				//NegativeType	:NEGATIVETYPE_BIT_SIZE,	//���������
//		//				EmptyBits		:3;	//������ ����					 
//		//		} ;
//		//

//		///*! \struct SPECIAL_MORPHO_IMPERATIVE
//		//*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � �������� � ����������
//		//*/	
//		//		struct  SPECIAL_MORPHO_IMPERATIVE{
//		//			unsigned short
//		//				NumberType	:NUMBERTYPE_BIT_SIZE,	//����� 
//		//				PersonType	:PERSONTYPE_BIT_SIZE,	//����
//		//				EmptyBits		:12;	//������ ����					 
//		//		} ;

//	};


//namespace NEW
//{
namespace Russian
{

	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	/*! \struct MORPHO_INFO_OFFICIAL
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������� ������ ����
	*/	

			struct  MORPHO_INFO_OFFICIAL{
				unsigned char
					OfficialType		:OFFICIALTYPE_BIT_SIZE,	// ��������� ����� ����
					Empty				:4;	// ������ ����
				MORPHO_INFO_OFFICIAL() : OfficialType(0), Empty(0)
				{}
			} ;

	
	/*! \struct PART_OF_SPEECH_PRETEXT
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������
	*/			
			struct  PART_OF_SPEECH_PRETEXT{
				unsigned int
					CaseType		:CASETYPE_BIT_SIZE,	// �����
					Empty			:29;	// ������ ����
				PART_OF_SPEECH_PRETEXT() : CaseType(0), Empty(0)
				{}
			};

	/*! \struct MORPHO_INFO_NOUNS
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������������
	*/			
			struct  MORPHO_INFO_NOUNS{
				unsigned char
					AnimInAnimType		:ANIMINANIMTYPE_BIT_SIZE, // ��������������
					GenderType			:GENDERTYPE_BIT_SIZE,	// ���				
					Empty				:3;	// ������ ����				
				MORPHO_INFO_NOUNS() : AnimInAnimType(0), GenderType(0), Empty(0)
				{}
			} ;

	/*! \struct PART_OF_SPEECH_NOUNS
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ���������������
	*/			
			struct  PART_OF_SPEECH_NOUNS{
				unsigned int
					CaseType			:CASETYPE_BIT_SIZE,		//�����
					NumberType		:NUMBERTYPE_BIT_SIZE,	//����� 
					Empty				:27;	//������ ����
				PART_OF_SPEECH_NOUNS() : CaseType(0), NumberType(0), Empty(0)
				{}
			} ;

	/*! \struct MORPHO_INFO_NUMERALS
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
	*/			
		struct  MORPHO_INFO_NUMERALS{
				unsigned char
					NumericType		:NUMERICTYPE_BIT_SIZE,	//��� �������������
					Empty			:6;	// ������ ����				
				MORPHO_INFO_NUMERALS() : NumericType(0), Empty(0)
				{}
			} ;

	/*! \struct PART_OF_SPEECH_NUMERALS
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
	*/			
			struct  PART_OF_SPEECH_NUMERALS{
				unsigned int
					CaseType		:CASETYPE_BIT_SIZE,	//�����
					GenderType		:GENDERTYPE_BIT_SIZE,	//���				
					NumberType		:NUMBERTYPE_BIT_SIZE,	//����� 
					AnimInAnimType	:ANIMINANIMTYPE_BIT_SIZE,	//��������������	
					Empty			:22;	//������ ����
				PART_OF_SPEECH_NUMERALS() : CaseType(0), GenderType(0), NumberType(0), 
					AnimInAnimType(0), Empty(0)
				{}
			} ;

	/*! \struct MORPHO_INFO_ADJECTIVES
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������������
	*/			
		struct  MORPHO_INFO_ADJECTIVES{
				unsigned char
					Empty			:8;	// ������ ����		
				MORPHO_INFO_ADJECTIVES() : Empty(0)
				{}
			} ;

	/*! \struct MORPHO_INFO_PRONOUNS
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
	*/			
		struct  MORPHO_INFO_PRONOUNS{
				unsigned char
					Empty			:8;	// ������ ����		
				MORPHO_INFO_PRONOUNS() : Empty(0)
				{}
			} ;

	/*! \struct PART_OF_SPEECH_ADJECTIVE
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������������
	*/			
		struct  PART_OF_SPEECH_ADJECTIVE{
				unsigned int
					CaseType		:CASETYPE_BIT_SIZE,	//�����
					GenderType		:GENDERTYPE_BIT_SIZE,	//���				
					NumberType		:NUMBERTYPE_BIT_SIZE,	//����� 
					AnimInAnimType	:ANIMINANIMTYPE_BIT_SIZE,	//��������������	
					ShortType		:SHORTTYPE_BIT_SIZE,	//���������
					DegreeType		:DEGREETYPE_BIT_SIZE,	//������� ���������
					Empty			:19;	//������ ����
				PART_OF_SPEECH_ADJECTIVE() : CaseType(0), GenderType(0), NumberType(0), 
					AnimInAnimType(0), ShortType(0), DegreeType(0), Empty(0)
				{}
			} ;

	/*! \struct PART_OF_SPEECH_PRONOUNS
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ������������
	*/			
			struct  PART_OF_SPEECH_PRONOUNS{
				unsigned int
					CaseType		:CASETYPE_BIT_SIZE,	//�����
					GenderType		:GENDERTYPE_BIT_SIZE,	//���				
					NumberType		:NUMBERTYPE_BIT_SIZE,	//����� 
					AnimInAnimType	:ANIMINANIMTYPE_BIT_SIZE,	//��������������	
					PronounGroup	:PRONOUNGROUP_BIT_SIZE,	//������ �����������
					PronounClass	:PRONOUNCLASS_BIT_SIZE,	//������ �����������
					PersonType		:PERSONTYPE_BIT_SIZE,	//����
					Empty			:14;	//������ ����
				PART_OF_SPEECH_PRONOUNS() : CaseType(0), GenderType(0), NumberType(0),AnimInAnimType(0),
					PronounGroup(0), PronounClass(0), PersonType(0), Empty(0)
				{}
			} ;

	/*! \struct MORPHO_INFO_ADVERB
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
	*/			
			struct  MORPHO_INFO_ADVERB{
			unsigned char
				AdverbType		:ADVERBTYPE_BIT_SIZE,	//��� ������� 
				Empty			:4;	//������ ����
			MORPHO_INFO_ADVERB() : AdverbType(0), Empty(0)
			{}
		} ;

	/*! \struct PART_OF_SPEECH_ADVERB_R
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
	*/			
			struct  PART_OF_SPEECH_ADVERB_R{
				unsigned int
					DegreeType	:DEGREETYPE_BIT_SIZE,	//������� ���������
					Empty		:30;	//������ ����
				PART_OF_SPEECH_ADVERB_R() : DegreeType(0), Empty(0)
				{}
			} ;


	/*! \struct MORPHO_INFO_VERB
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
	*/			
			struct  MORPHO_INFO_VERB{
				unsigned char
					AspectType			:ASPECTTYPE_BIT_SIZE,	// ��� �������
					Empty				:4;	//������ ����					 
				MORPHO_INFO_VERB() : AspectType(0), Empty(0)
				{}
			} ;

	/*! \struct PART_OF_SPEECH_VERB_R
	*  \brief     �������� ����� ��������������� ������������� ��� ����������� ���������� � ��������
	*/			
			struct  PART_OF_SPEECH_VERB_R{
				unsigned int
					TransitionalType	:TRANSITIONALTYPE_BIT_SIZE,	// ������������					 
					VerbForm			:VERBFORM_BIT_SIZE,	// ����� �������
					TimeType			:TIMETYPE_BIT_SIZE,	// ����� �������
					NumberType			:NUMBERTYPE_BIT_SIZE,	//����� 
					GenderType			:GENDERTYPE_BIT_SIZE,	//���				
					VoiceType			:VOICETYPE_BIT_SIZE,	//�����	
					PersonType			:PERSONTYPE_BIT_SIZE,	//����			
					CaseType			:CASETYPE_BIT_SIZE,	//�����
					AnimInAnimType		:ANIMINANIMTYPE_BIT_SIZE,	//��������������
					ShortType			:SHORTTYPE_BIT_SIZE,	//���������
					PhaseVerbType		:PHASEVERBTYPE_BIT_SIZE,	//����������
					Empty				:8;	//������ ����					 
				PART_OF_SPEECH_VERB_R() : VerbForm(0), TimeType(0), NumberType(0), GenderType(0), 
					VoiceType(0), PersonType(0), CaseType(0),  AnimInAnimType(0), ShortType(0), 
					TransitionalType(0), PhaseVerbType(0), Empty(0)
				{}
			} ;

};
//};

};
};
