#pragma once

#include ".\TAMConverterBitStructures.h"

using namespace SS::MorphoFeaturesCoding;
using namespace SS::MorphoFeaturesCoding::Russian;

namespace SS
{
namespace Core
{
namespace Features
{
/// ��������� ����������� ��������������� ������������� ��� ��������
class CAMRussianAnalyzer
{
public:
	/// �����������
	CAMRussianAnalyzer(void);
	/// ����������
	~CAMRussianAnalyzer(void);
public:
	/// ��������� ����������� ������ ��������������� ������������� � ������������������ �����
	/** 
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\param *piMorphoInfo - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
	*/
	bool Code(/*in*/const CMorphoFeature *pMorphoFeature, /*out*/int *MorphoInfo, /*out*/int *PartOfSpeech);
	/// ��������� ������������� ������������������ ����� � ����� ��������������� ������������� 
	/** 
		\param iMorphoInfo - ������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
	*/
	bool EnCode(/*in*/int iMorphoInfo, /*in*/int iPartOfSpeech, /*out*/CMorphoFeature *pMorphoFeature);

private:
	/// ������������� ��������������� �������� ������
	void BackInit();
	///// ������������� ��������������� �������������
	///** 
	//	\param *morpho_feature - ��������� �� ���������, ���������� ��������������� ��������������
	//*/
	//void Initialization(CMorphoFeature *morpho_feature);

	/// ��������� ����������� ��� �����������
	/** 
		\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
	*/
	void CodePronouns(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);
	/// ��������� ����������� ��� �������
	/** 
		\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/
	void CodeAdverbs(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);
	/// ��������� ����������� ��� ������������
	/** 
		\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/
	void CodeNumbers(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);
	/// ��������� ����������� ��� ��������������
	/** 
		\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/
	void CodeAdjectives(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);
	/// ��������� ����������� ��� ��������
	/** 
		\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/
	void CodeVerbs(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);
	/// ��������� ����������� ��� ���������������
	/** 
		\param piPartOfSpeech - �������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/
	void CodeNouns(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);
	/// ��������� ������������� ������ � ����� ��������������� ������������� ��� ��������� ������ ���� 
	/** 
		\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/
	void CodeOfficial(int* iPartOfSpeech, const CMorphoFeature *pMorphoFeature);


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
	void EnCodeNouns(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);
	/// ��������� ������������� ����� � ����� ��������������� ������������� ��� ��������� ������ ����
	/** 
		\param iPartOfSpeech - ������� ��������, ���������� ����� �������������� ��������������� ����������.
		\param *pMorphoFeature - c������� ����� ��������������� �������������, ������� ���������� ������������.
		\return void
	*/				
	void EnCodeOfficial(int iPartOfSpeech, CMorphoFeature *pMorphoFeature);

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
	/*! \var m_mi_BASE
	*  \brief   �������� ������� ����� ���������������
	*/
	BASE_MORPHO_INFO				m_mi_BASE;

	/*! \var m_mi_OFFICIAL
	*  \brief     �������� ����� ��������������� ��� ��������� ������ ����
	*/
	MORPHO_INFO_OFFICIAL			m_mi_OFFICIAL;
	/*! \var m_mi_NOUNS
	*  \brief     �������� ����� ��������������� ��� ��������������� 
	*/
	MORPHO_INFO_NOUNS				m_mi_NOUNS;
	/*! \var m_mi_NUMERALS
	*  \brief     �������� ����� ��������������� ��� ������������
	*/
	MORPHO_INFO_NUMERALS			m_mi_NUMERALS;

	/*! \var m_mi_ADJECTIVES
	*  \brief     �������� ����� ��������������� ��� ��������������
	*/
	MORPHO_INFO_ADJECTIVES		m_mi_ADJECTIVES;

	/*! \var m_mi_PRONOUNS
	*  \brief     �������� ����� ��������������� ��� �����������
	*/
	MORPHO_INFO_PRONOUNS			m_mi_PRONOUNS;

	/*! \var m_mi_ADVERB
	*  \brief     �������� ����� ��������������� ��� �������
	*/
	MORPHO_INFO_ADVERB				m_mi_ADVERB;
	/*! \var m_mi_VERB
	*  \brief     �������� ����� ��������������� ��� ��������
	*/
	MORPHO_INFO_VERB				m_mi_VERB;
	/*! \var m_pos_PRETEXT
	*  \brief     �������� ����� ��������������� ��� ���������
	*/
	PART_OF_SPEECH_PRETEXT			m_pos_PRETEXT;
	/*! \var m_pos_NOUNS
	*  \brief     �������� ����� ��������������� ��� ���������������
	*/
	PART_OF_SPEECH_NOUNS			m_pos_NOUNS;
	/*! \var m_pos_NUMERALS
	*  \brief     �������� ����� ��������������� ��� ������������
	*/
	PART_OF_SPEECH_NUMERALS			m_pos_NUMERALS;
	/*! \var m_pos_ADJECTIVE
	*  \brief     �������� ����� ��������������� ��� ��������������
	*/
	PART_OF_SPEECH_ADJECTIVE		m_pos_ADJECTIVE;
	/*! \var m_pos_PRONOUNS
	*  \brief     �������� ����� ��������������� ��� �����������
	*/
	PART_OF_SPEECH_PRONOUNS			m_pos_PRONOUNS;
	/*! \var m_pos_ADVERB
	*  \brief     �������� ����� ��������������� ��� �������
	*/
	PART_OF_SPEECH_ADVERB_R			m_pos_ADVERB;
	/*! \var m_pos_VERB
	*  \brief     �������� ����� ��������������� ��� ��������
	*/
	PART_OF_SPEECH_VERB_R			m_pos_VERB;

};
};
};
};
