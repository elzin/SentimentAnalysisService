#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{


			class CSMComplexName :
				public CSMSentenceExpert
			{
			public:
				CSMComplexName(void);
				~CSMComplexName(void);
				bool AnalizeSentence();
				//bool Init(IText * pIText);
			private:
				//struct 
				/// �������� ��������� �����
				struct SSmanticDescription{
					/// ��������� �����
					SS::Core::Features::CSemanticFeature _oSemanticFeature;
					/// ����� - ���� ��� �����������
					bool _bProper;
					SSmanticDescription(){  _bProper=false; };
				};
			//typedefs
				/// ������ �������� ����
				typedef list<CSMComplexName::SSmanticDescription> TLSmanticDescription;
			//attributes
				/// ��������� - ������
				long m_lSemanticCitation;
				///
				SS::Core::Features::CMorphoFeature m_MorphoFeature;

			//methods
				/// ���������� �� ������������ ������� �����
				bool IsValidWord();
				/// �������� ��������� ��� �����������
				/** 
					\param oDesc - �������� ������ ����
					\param l_units - ��������������� ������ �����
				*/
				void DetectProper(CSMComplexName::TLSmanticDescription& oDesc, TBoxUnits& l_units);
				/// ��������� ������������� ���������� ��� ������������� ���������� ������ ����
				/** 
					\param l_units - ������ ����
					\param oDesc - ������ ��������������� �������� � ����������
				*/
				void ProcessUnits(TBoxUnits & l_units, CSMComplexName::TLSmanticDescription& oDesc);
				/// ������������� ��������� ��������� ��� ������ ���� � �������������� � � ������������� �������
				/** 
					\param oSemanticFeature - ��������� ������
					\param oPersonType - ��������� ������ ����������� � ���� Person
					\param uiNonProperCount - ����� ���������� � ������ ���� �� ��� �����������
					\param l_SemGeo - ��������� ����������� � �����
					\param l_Sem - ��� ������ ���������
					\param bPerson - ������ - ���� � ���������� ��������� ��� ������ - ��� 
					\return bool - ������ - ���� �� ��� �� ���� � ����������
				*/
				bool ConvertFeatureToType(SS::Core::Features::CSemanticFeature & oSemanticFeature,SS::Core::Features::Types::TSPersonType&  oPersonType,  UINT uiNonProperCount , list<long> & l_SemGeo, list<long> & l_Sem, bool & bPerson);
				/// ������� ��������� ������ 
				/** 
					\param oDesc - ������ ����
					\param tsemFeature - �������� ��������� �� And
					\param oPersonType - �������� ��������� �� Or 
					\return UINT - ���-�� ���� ��� ��������� � ������
				*/
				UINT MergeSemantic(CSMComplexName::TLSmanticDescription& oDesc,SS::Core::Features::CSemanticFeature & tsemFeature, SS::Core::Features::Types::TSPersonType & oPersonType);
				/// �������� ������ �� ������������
				/** 
					\param l_units - ������ ����
					\param l_SemGeo  - ��������� ����������� � �����
					\param l_Sem - ��������� ���������
					\return bool - ���� ������������ ������
				 
				-detailed description- 
				*/
				IUnit * CheckSemantic(TBoxUnits & l_units , list<long> & l_SemGeo, list<long> & l_Sem );

			};

		}
	}
}