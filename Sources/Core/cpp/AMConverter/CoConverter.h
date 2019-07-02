#pragma once

#include "..\ASSInterface\TDictionaryNames.h"


#include "..\ASSInterface\IAMConverter.h"

#include ".\syntaxanalyzer.h"

#include ".\AMRussianAnalyzer.h"
#include ".\AMEnglishAnalyzer.h"

#include ".\SemanticConverter.h"
#include ".\syntaxAposterioriAnalyzer.h"


namespace SS
{
	namespace Core
	{
		namespace Features
		{
			/////////////////////////////////////////////////////////////////////////////
			// CCoConverter
			class CCoConverter 
				: public SS::Interface::Core::AMConverter::IAMConverterMorpho
				, public SS::Interface::Core::AMConverter::IAMConverterSyntax
				, public SS::Interface::Core::AMConverter::IAMConverterSyntaxAposteriori
				, public SS::Interface::Core::AMConverter::IAMConverterSemantic
			{
			public:
				/// �����������
				CCoConverter()
				{		
				}
				/// ����������
				virtual ~CCoConverter()
				{
				}
			public: //from SS::Interface::IBase	
				HRESULT QueryInterface(REFIID refIID, void** pBase);
				ULONG Release();
			public: //from SS::Core::SMISL::IAMConverterMorpho	
				/// ��������� ����������� ������ ��������������� ������������� � ������������������ �����
				void Code(
					///����� ������� ��� �������� ���������� ��������� ����������� ��������������� �������������
					const unsigned char uchDictionaryNumber,
					///c������� ����� ��������������� �������������, ������� ���������� ������������.
					const CMorphoFeature* pMorphoFeature,
					///�������� ��������, ���������� ����� �������������� ��������������� ����������.
					int* piMorphoInfo, 
					///�������� ��������, ���������� ����� �������������� ��������������� ����������.
					int* piPartOfSpeech
					);
				
				/// ��������� ������������� ������������������ ����� � ����� ��������������� ������������� 
				void EnCode(
					///����� ������� ��� �������� ���������� ��������� ����������� ��������������� �������������
					const unsigned char uchDictionaryNumber, 
					///������� ��������, ���������� ����� �������������� ��������������� ����������
					const int iMorphoInfo,
					///������� ��������, ���������� ����� �������������� ��������������� ����������
					const int iPartOfSpeech,
					///c������� ����� ��������������� �������������, ������� ���������� ������������
					CMorphoFeature* pMorphoFeature
					);

				/// �������� ����� ��������� �������������� ������������ � �����
				/** 
					\param oPartOfSpeechTypes - ����� ���� �����, ��� �������� ���������� ��������� �����������
					\param *pSyntaxFeature	- ������ ��������� �������������� �������������
					\param piSyntaxInfo	- �����, ������� �������� �������������� ��������� �������������� ��������������
					\return void
				*/
				void Code(
					/*in*/SS::Core::Features::Types::PartOfSpeechTypes oPartOfSpeechTypes,
					/*in*/SS::Core::Features::CSyntaxFeatureApriori *pSyntaxFeature, 
					/*out*/unsigned int* piSyntaxInfo);

				/// ��������� ������������� ����� � ����� ��������� �������������� ������������� 
				/** 
					\param oPartOfSpeechTypes - ����� ���� �����, �������������� �������������� �������� ���������� ��������
					\param iSyntaxInfo - �������������� �������������� ��������������
					\param *pSyntaxFeature - ����� �������������� ��������� 
					\return void
				*/
				void EnCode(
				/*in*/SS::Core::Features::Types::PartOfSpeechTypes oPartOfSpeechTypes,
				/*in*/unsigned int iSyntaxInfo,	
				/*out*/SS::Core::Features::CSyntaxFeatureApriori *pSyntaxFeature);

			public: //from SS::Core::SMISL::IAMConverterSemantic	
				/// �������� ����� ������������� ������������� � �����
				/** 
					\param *pSemanticFeature - ����� ������������� �������������
					\param pSemanticType - �����, ������� �������� �������������� ������������� ��������������
					\return void
				*/
				void Code(/*in*/SS::Core::Features::CSemanticFeature *pSemanticFeature, /*out*/SS::Dictionary::Types::TDictionaryIndex* pDictionaryIndex);

				/// ���������� ����� � ����� ������������� �������������
				/** 
					\param SemanticType - �����, ������� �������� �������������� ������������� ��������������
					\param *pSemanticFeature - ����� ������������� �������������
					\return void
				*/
				void EnCode(/*in*/SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex, /*out*/SS::Core::Features::CSemanticFeature *pSemanticFeature);

			public: //from SS::Core::SMISL::IAMConverterSyntaxAposteriori
				/// �������� ����� ��������� �������������� ������������ � �����
				/** 
					\param *pSyntaxFeature	- ������ ��������� �������������� �������������
					\param piSyntaxInfo	- �����, ������� �������� �������������� ��������� �������������� ��������������
				*/
				void Code(
					/*in*/SS::Core::Features::CSyntaxFeatureAposteriori *pSyntaxFeatureAposteriori, 
					/*out*/unsigned int* piSyntaxInfo) ;
					/*	������������� ������������� �������������� ����������	*/
				/// ��������� ������������� ����� � ����� ��������� �������������� ������������� 
				/** 
					\param iSyntaxInfo - �������������� �������������� ��������������
					\param *pSyntaxFeature - ����� �������������� ��������� 
				*/
				void EnCode(
					/*in*/unsigned int iSyntaxInfo,	
					/*out*/SS::Core::Features::CSyntaxFeatureAposteriori *pSyntaxFeatureAposteriori);
			private:
//RRR				CMorphoAnalyzerRus		m_MorphoAnalyzerRus;
				CAMEnglishAnalyzer		m_oAMEnglishAnalyzer;

				CSyntaxAnalyzer			m_oSyntaxAnalyzer;

				CAMRussianAnalyzer		m_oAMRussianAnalyzer;
			};
		}
	}
}