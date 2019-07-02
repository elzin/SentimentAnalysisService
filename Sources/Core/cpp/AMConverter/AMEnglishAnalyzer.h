#pragma once

#include "stl.h"

#include ".\TAMConverterBitStructures.h"

using namespace SS::MorphoFeaturesCoding;
using namespace SS::MorphoFeaturesCoding::English;

namespace SS
{
namespace Core
{
namespace Features
{
	/// ��������� ����������� ��������������� ������������� ��� �����������			
	class CAMEnglishAnalyzer
	{
	public:
		/// �����������
		CAMEnglishAnalyzer(void)
		{
		}
		/// ����������
		virtual ~CAMEnglishAnalyzer(void)
		{
		}
	public:
		/// ��������� ����������� ������ ��������������� ������������� � ������������������ �����
		/** 
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\param *piMorphoInfo - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\return void
		*/
		void Code(/*in*/const CMorphoFeature *pMorphoFeature, /*out*/int *MorphoInfo, /*out*/int *PartOfSpeech);

		/// ��������� ������������� ������������������ ����� � ����� ��������������� ������������� 
		/** 
			\param iMorphoInfo - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/	
		void EnCode(/*in*/int iMorphoInfo, /*in*/int iPartOfSpeech, /*out*/CMorphoFeature *pMorphoFeature);
	private:

		/// ��������� ����������� ��� �����������
		/** 
			\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param ppMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/				
		void CodePronouns(int* piPartOfSpeech, const CMorphoFeature *pMorphoFeature);
		/// ��������� ����������� ��� �������
		/** 
			\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param ppMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/				
		void CodeAdverbs(int* piPartOfSpeech, const CMorphoFeature *pMorphoFeature);
		/// ��������� ����������� ��� ������������
		/** 
			\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param ppMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/				
		void CodeNumbers(int* piPartOfSpeech, const CMorphoFeature *pMorphoFeature);
		/// ��������� ����������� ��� ��������������
		/** 
			\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param ppMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/				
		void CodeAdjectives(int* piPartOfSpeech, const CMorphoFeature *pMorphoFeature);
		/// ��������� ����������� ��� ��������
		/** 
			\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param ppMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/				
		void CodeVerbs(int* piPartOfSpeech, const CMorphoFeature *pMorphoFeature);
		/// ��������� ����������� ��� ���������������
		/** 
			\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param ppMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/				
		void CodeNouns(int* piPartOfSpeech, const CMorphoFeature *pMorphoFeature);


		/// ��������� ������������� ����� � ����� ��������������� ������������� ��� �����������
		/** 
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/
		void EnCodePronouns(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);
		/// ��������� ������������� ����� � ����� ��������������� ������������� ��� �������
		/** 
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/
		void EnCodeAdverbs(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);
		/// ��������� ������������� ����� � ����� ��������������� ������������� ��� ������������
		/** 
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/
		void EnCodeNumbers(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);
		/// ��������� ������������� ����� � ����� ��������������� ������������� ��� ��������������
		/** 
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/
		void EnCodeAdjectives(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);
		/// ��������� ������������� ����� � ����� ��������������� ������������� ��� ��������
		/** 
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/
		void EnCodeVerbs(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);

		/// ��������� ������������� ����� � ����� ��������������� ������������� ��� ���������������
		/** 
			\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
			\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
			\return void
		*/
		void EnCodeNouns(int iPartOfSpeech, CMorphoFeature *ppMorphoFeature);
		///// ������������� ��������������� �������������
		///** 
		//	\param *pmorpho_feature - ��������� �� ���������, ���������� ��������������� ��������������
		//*/
		//void Initialization(CMorphoFeature *pmorpho_feature);
		/// ������������� ��������������� �������� ������
		void BackInit();

		/// ��������� ����������� ��������������� �������������
		/** 
			\param *pMorphoFeature- c������� ����� ��������������� �������������, ������� ���������� ������������.
			\param *piMorphoInfo	- �������� ����� �������������� ����������
			\param *piPartOfSpeech	- �������� ����� �������������� ����������
		*/
		void MorphoInfoBackAnalyzer(const CMorphoFeature *ppMorphoFeature, int *piMorphoInfo, int *piPartOfSpeech);

		/// ��������� ������������� ��������������� �������������
		/** 
			\param iMorphoInfo		- �������� ����� �������������� ����������
			\param iPartOfSpeech	- �������� ����� �������������� ����������
			\param *pMorphoFeature	- c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/
		void MorphoInfoAnalyzer(int iMorphoInfo, int iPartOfSpeech, CMorphoFeature *pMorphoFeature);

	private:
		/// ��������� �������������� ������ �����
		/** 
			\param pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/
		void PostAnalyseNumberType(CMorphoFeature *pMorphoFeature);

		/// ��������� �������������� ������ ����
		/** 
			\param pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/
		void PostAnalyseGenderType(CMorphoFeature *pMorphoFeature);

		/// ��������� �������������� ������ ������
		/** 
			\param pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		*/
		void PostAnalyseCaseType(CMorphoFeature *pMorphoFeature);

	private:
		/*! \var m_bMI
		*  \brief   �������� ������� ����� ���������������
		*/
		BASE_MORPHO_INFO m_mi_Base;

		/*! \var m_verbMI
		*  \brief     �������� ����� ��������������� ��� ��������
		*/
		VERBS_MORPHO_INFO m_mi_Verb;
		/*! \var m_nounMI
		*  \brief     �������� ����� ��������������� ��� ���������������
		*/
		NOUNS_MORPHO_INFO m_mi_Noun;
		/*! \var m_numMI
		*  \brief     �������� ����� ��������������� ��� ������������
		*/
		NUMERALS_MORPHO_INFO m_mi_Numerals;
		/*! \var m_adjMI
		*  \brief     �������� ����� ��������������� ��� ��������������
		*/
		ADJECTIVES_MORPHO_INFO m_mi_Adjective;
		/*! \var m_advMI
		*  \brief     �������� ����� ��������������� ��� �������
		*/
		ADVERBS_MORPHO_INFO m_mi_Adverb;
		/*! \var m_prnMI
		*  \brief     �������� ����� ��������������� ��� �����������
		*/
		PRONOUNS_MORPHO_INFO m_mi_Pronoun;
		/*! \var m_offMI
		*  \brief     �������� ����� ��������������� ��� ��������� ������ ����
		*/
		OFFICIAL_MORPHO_INFO m_mi_Official;


		/*! \var m_verbPOS
		*  \brief     �������� ����� ��������������� ��� ��������
		*/
		VERBS_PART_OF_SPEECH		m_pos_Verb;
		/*! \var m_nounPOS
		*  \brief     �������� ����� ��������������� ��� ���������������
		*/
		NOUNS_PART_OF_SPEECH		m_pos_Noun;
		/*! \var m_numPOS
		*  \brief     �������� ����� ��������������� ��� ������������
		*/
		NUMERALS_PART_OF_SPEECH		m_pos_Numeral;
		/*! \var m_adjPOS
		*  \brief     �������� ����� ��������������� ��� ��������������
		*/
		ADJECTIVES_PART_OF_SPEECH	m_pos_Adjective;
		/*! \var m_advPOS
		*  \brief     �������� ����� ��������������� ��� �������
		*/
		ADVERBS_PART_OF_SPEECH		m_pos_Adverb;
		/*! \var m_prnPOS
		*  \brief     �������� ����� ��������������� ��� �����������
		*/
		PRONOUNS_PART_OF_SPEECH		m_pos_Pronoun;


	};
};
};
};
