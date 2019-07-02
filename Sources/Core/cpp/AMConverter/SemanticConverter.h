#pragma once

#include ".\Semanticbitfieldsstructures.h"

#include "..\ASSInterface\TCoSeDiDataTypes.h"


//using namespace SS::Core::SMISL;

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			using namespace bitfieldsstructures;
			/// �������� �� �����������/ ������������� ������������� �������������
			class CSemanticConverter
			{
			public:
				/// �����������
				CSemanticConverter(void);
				/// ����������
				~CSemanticConverter(void);

				/// �������� ����� ������������� ������������� � �����
				/** 
					\param *pSemanticFeature - ����� ������������� �������������
					\param piSymanticType - �����, ������� �������� �������������� ������������� ��������������
					\return void
				*/
				bool Code(/*in*/CSemanticFeature *pSemanticFeature, /*out*/SS::Dictionary::Types::TDictionaryIndex* pDictionaryIndex);
								/// ���������� ����� � ����� ������������� �������������
				/** 
					\param iSymanticType - �����, ������� �������� �������������� ������������� ��������������
					\param *pSemanticFeature - ����� ������������� �������������
					\return void
				*/
				bool EnCode(/*in*/SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex, /*out*/CSemanticFeature *pSemanticFeature);
			private:
				/// ����������� ������������� �������������� ��������
				/** 
					\param SS::AMConverter::Semantic::bitfieldsstructures::SbfSemanticTypeoSemanticType -  ���������, ���������� ����� ������������� ��� ����������� ������������� ��������
					\param *pSemanticFeature - ��������� �� ���������, ���������� ����� ������������� �������������
				*/
				void EnCodeVerbSemantics(bitfieldsstructures::SbfSemanticType	oSemanticType, /*out*/CSemanticFeature *pSemanticFeature);
				/// -brief- 
				/** 
					\param SS::AMConverter::Semantic::bitfieldsstructures::SbfSemanticType&oSemanticType -  ���������, ���������� ����� ������������� ��� ����������� ������������� ��������
					\param *pSemanticFeature - ��������� �� ���������, ���������� ����� ������������� �������������
				*/
				void CodeVerbSemantics(bitfieldsstructures::SbfSemanticType&	oSemanticType, /*out*/CSemanticFeature *pSemanticFeature);

				/// �������� ������������� �������������� Food
				void CodeMaterial(bitfieldsstructures::SbfSemanticType&	oSemanticType, /*out*/CSemanticFeature *pSemanticFeature);
				/// ����������� ������������� �������������� Food
				void EnCodeMaterial(bitfieldsstructures::SbfSemanticType	oSemanticType, /*out*/CSemanticFeature *pSemanticFeature);

			};
		}
	}
}

