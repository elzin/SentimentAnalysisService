#pragma once

#pragma warning( disable : 4290 )
#include <stdexcept> 

#include ".\basefeaturecollection.h"
#include "define.h"
#include <vector>
#include "../ASSInterface/TMainAnalyseTypes.h"
#include "../ASCInterface/TDictionaryIndex.h"


namespace SS
{
	namespace Core
	{
		namespace Features
		{
			class CMorphoFeatureApriori;
			class CMorphoFeatureAposteriori;

			/// ����� ��������������� �������������
			class CMorphoFeature :
				public SS::Core::Features::Base::CBaseFeatureCollection
			{
				friend class SS::Core::Features::CMorphoFeatureApriori;
				friend class SS::Core::Features::CMorphoFeatureAposteriori;
			public:
				CMorphoFeature(void);
				virtual ~CMorphoFeature(void);

				CMorphoFeature& operator = (const CMorphoFeature& value)
				{
					Assign(&value);
					return *this;
				}
				CMorphoFeature(const CMorphoFeature& value){
					Init();
					*this = value;
				};
				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "MorphoFeature";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "��������������� ��������������";};

				///����������� � ������ ������� �� ���� ����� � ������
				bool IsIntersectsByCaseGenderNumber(const CMorphoFeature& value);							

                ///�������� ����������� � ������ ������� ��������������� �������������
				bool IsIntersectsWith(const CMorphoFeature& value) const;

				///�������� ����������� � ������ ������� ��������������� �������������
				bool IsIntersectsWith(const CMorphoFeature& value, SS::Core::Types::EAnalyseLanguage eLang) const;

				///�������� ��������� � ������ ������� ��������������� �������������
				bool IsEqualUniformMember( const CMorphoFeature& value ) const;

				///�������� ������������ ������ ��������������� �������������
				void AssignMorphoFeature(const CMorphoFeature* pValue)throw( std::invalid_argument);

				///�������� ����������� �� pValue �������������� ������� �� Undefind
				void AssignValidMorphoFeature(const CMorphoFeature* pValue);
				
				Types::PartOfSpeechTypes	m_PartOfSpeechTypes;// ����� ����
				Types::AnimInAnimType		m_AnimInAnimType; 	// ��������������
				Types::AspectType			m_AspectType;		// ��� ��������
				Types::AdverbType			m_AdverbType;		// ��� �������
				Types::CaseType				m_CaseType;			// �����

				Types::CountType			m_CountType;		// �������������
				Types::CommonType			m_CommonType;		// ��������������� 
				Types::DegreeType			m_DegreeType;		// ������� ���������
				Types::GenderType			m_GenderType;		// ���
				Types::NumberType			m_NumberType;		// �����


				Types::NumericType			m_NumericType;		// ��� �������������
				Types::NegativeType			m_NegativeType;		// �������������� ���������
				Types::OfficialType			m_OfficialType;		// ��� ��������� ����� ����
				Types::PhaseVerbType		m_PhaseVerbType;	// ����������
				Types::PersonType			m_PersonType;		// ����

				Types::PronounGroup			m_PronounGroup;		// ������ �����������
				Types::PronounClass			m_PronounClass;		// ����� �����������
				Types::ShortType			m_ShortType;		// ���������		
				Types::TAdverbClass			m_AdverbClass;		// ����� �������
				Types::TConjunctionType		m_ConjunctionType;	// ��� �����


				Types::TDeterminerType		m_DeterminerType;	// ��� ������������
				Types::TimeType				m_TimeType;			// �����
				Types::TransitionalType		m_TransitionalType;	// ������������
				Types::VoiceType			m_VoiceType;		// �����
				Types::VerbForm				m_VerbForm;			// ����� �������

				Types::VerbType				m_VerbType;			// ��� �������
				Types::MoodType				m_MoodType;			// ���������� �������				


				unsigned int m_iCountMorphoElement ;

			private:
				void Init();

				///// ��������� ����������� ������ ��������������� ������������� � ������������������ �����
				//void Code(
				//	///����� ������� ��� �������� ���������� ��������� ����������� ��������������� �������������
				//	const unsigned char uchDictionaryNumber,
				//	///�������� ��������, ���������� ����� �������������� ��������������� ����������.
				//	int* piMorphoInfo, 
				//	///�������� ��������, ���������� ����� �������������� ��������������� ����������.
				//	int* piPartOfSpeech
				//	) const;
				//
				///// ��������� ������������� ������������������ ����� � ����� ��������������� ������������� 
				//void EnCode(
				//	///����� ������� ��� �������� ���������� ��������� ����������� ��������������� �������������
				//	const unsigned char uchDictionaryNumber, 
				//	///������� ��������, ���������� ����� �������������� ��������������� ����������
				//	const int iMorphoInfo,
				//	///������� ��������, ���������� ����� �������������� ��������������� ����������
				//	const int iPartOfSpeech
				//	);
			};
		}
	}
}