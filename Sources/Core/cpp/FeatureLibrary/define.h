#pragma once

namespace SS{
	namespace Core{
		namespace Features{
			///����� ��������������� �������������
			class CMorphoFeature;
		}
	}
}

#include "BaseType.h"
//#include "MapDefinitionMorpho.h"
//#include "MapDefinitionSemantic.h"
//#include "MapDefinitionSyntax.h"
#include "AutoFeatures.h"

#include "morphofeature.h"
#include "ObjectFeature.h"
//#include "MorphoFeatureApriori.h"
//#include "MorphoFeatureAposteriori.h"
#include "SyntaxFeatureApriori.h"
#include "SyntaxFeatureAposteriori.h"
#include "ConstructionFeature.h"
#include "SemanticFeature.h"

namespace SS{
	namespace Core{
		namespace Features{
			namespace Types{
#pragma warning (disable : 4091)
				///��� �������� ����� ����
				typedef PartOfSpeechTypes;
				///��� �������� ����� ����
				typedef PartOfSpeechTypes;
				/// ��� �������� ��������������
				typedef AnimInAnimType;
				/// ��� �������� ������������ ��������������
				typedef Uniqueness;
				///	��� �������� ����������� ��������
				typedef TDetectWordAnalyzeMode;
				///	��� �������� ����������� ��������
				typedef OperationMod;
				///	��� �������� ����� �����������
				typedef ExistenceMod;
				///	��� �������� ��� ��������
				typedef AspectType;
				///	��� �������� ��� �������
				typedef AdverbType;
				///	��� �������� �����
				typedef CaseType;
				///	��� �������� �������������
				typedef CountType;
				///	��� �������� ���������������
				typedef CommonType;
				///	��� �������� ������� ���������
				typedef DegreeType;
				///	��� �������� ���
				typedef GenderType;
				///	��� �������� �����
				typedef NumberType;
				///	��� �������� ��� �������������
				typedef NumericType;
				///	��� �������� �������������� ���������
				typedef NegativeType;
				///	��� �������� ����������
				typedef PhaseVerbType;
				///	��� �������� ����
				typedef PersonType;
				///	��� �������� ������ �����������
				typedef PronounGroup;
				///	��� �������� ����� �����������
				typedef PronounClass;
				///	��� �������� ���������
				typedef ShortType;
				///	��� �������� ����� �������
				typedef TAdverbClass;
				///	��� �������� ��� �����
				typedef TConjunctionType;
				///	��� �������� ��� ������������
				typedef TDeterminerType;
				///	��� �������� �����
				typedef TimeType;
				///	��� �������� ������������
				typedef TransitionalType;
				///	��� �������� �����
				typedef VoiceType;
				///	��� �������� ����� �������
				typedef VerbForm;
				///	��� �������� ��� �������
				typedef VerbType;
				///	��� �������� ����������
				typedef MoodType;

			//���� ���������
				/// ������������� ����
				typedef TSemanticType;
				/// ������������� ��� �������
				typedef TSTimeIntervalType;
				/// ��� �����
				typedef TSPlaceType;
				/// ��� ������
				typedef TCityType;//		TCityType;
				/// ��� ������
				typedef TAreaType;//		TAreaType;
				/// ��� ������
				typedef TDistrictType;//	TDistrictType;
				/// ��� �����
				typedef TMetroType;//		TMetroType;


				typedef TSMaterial;
				typedef TSTransport;
				typedef TSBuilding;
				typedef TSMFood;
				typedef TSMForFreeTime;

				/// ��� ���������� ����������
				typedef TSInfo;

				/// ���� ���
				typedef TSMeasureType;
				/// ������������� ����, ���������� � �����
				typedef TSPersonType;
				/// ���� �����������
				typedef TSOrganizationType;
				/// ������������� ���� ��������
				typedef TSVerbType;
				///
				typedef TSVBeType;
				///
				typedef TSVAcquirePossessType;
				///
				typedef TSVAcquireType;
				///
				typedef TSVEndType;
				///
				//typedef TSVMoveType;
				///
				//typedef TSVEmotionType;
				///
				//typedef TSVExperiencedType;
				///
				//typedef TSVSearchType;
				///
				//typedef TSServiceTypes;

			// ������ ����������
				/// ���������� �����������
				typedef VerbConstruction;
				/// ����������� ����������������
				typedef NounConstruction;
				/// ����������� ���������������
				typedef AdjectiveConstruction;
				/// ��� ���������� �������
				typedef TypeOfEndingObject;
				///
				typedef CombiType;
				/// �������������� ��������� (��� �����
				typedef SyntaxCategories;
				/// ����������� �����������
				typedef HeadDependentType;
				/// ��� �����������
				typedef SentenceType;
				/// ������� ���������� ��������
				typedef ObjectsOrder;
				/// ��������� �� ��������� � ������
				typedef PositionToDetectedObject;
				/// �������������� �����
				typedef ObjectObligation;
				/// ��� ������������
				typedef AgreementType;
				/// ������� �������� �������
				typedef ScopeOfTheRule;
				///
				typedef PositionInBlock;

				/// ���� �����
				typedef DependencyPower;
				/// �������� ����������� �������������� ���������
				typedef SyntaxCategoryPower;
				/// ����� ��������
				typedef IdParent;
				/// ����������� �������� ������ ����
				typedef SameTypeObjectsNumber;
				/// ������� ������� �����
				typedef ChildrenAnalysisDepth;       
            /// ����� �����������
            typedef SentenceNumber;
            /// ������������ �������������� ������������� ������������� ��������
				typedef SyntaxParamsInheritanceMode;

#pragma warning (default : 4091)
			}
		}
	}
}

//static 
namespace SS{
	namespace Core{
		namespace Features{
			namespace Values{
				///����� �������� ����� ����
				static const SS::Core::Features::Types::PartOfSpeechTypesType PartOfSpeechTypes;
				// ����� �������� ��������� ����� ����
				static const SS::Core::Features::Types::OfficialTypeType OfficialType;
				/// ����� �������� ��������������
				static const SS::Core::Features::Types::AnimInAnimTypeType AnimInAnimType;
				/// ����� �������� ������������ ��������������
				static const SS::Core::Features::Types::UniquenessType Uniqueness;
				///	����� �������� ����������� ��������
				static const SS::Core::Features::Types::TDetectWordAnalyzeModeType TDetectWordAnalyzeMode;
				///	����� �������� ����������� ��������
				static const SS::Core::Features::Types::OperationModType OperationMod;
				///	����� �������� ����� �����������
				static const SS::Core::Features::Types::ExistenceModType ExistenceMod;
				///	����� �������� ��� ��������
				static const SS::Core::Features::Types::AspectTypeType AspectType;
				///	����� �������� ��� �������
				static const SS::Core::Features::Types::AdverbTypeType AdverbType;
				///	����� �������� �����
				static const SS::Core::Features::Types::CaseTypeType CaseType;
				///	����� �������� �������������
				static const SS::Core::Features::Types::CountTypeType CountType;
				///	����� �������� ���������������
				static const SS::Core::Features::Types::CommonTypeType CommonType;
				///	����� �������� ������� ���������
				static const SS::Core::Features::Types::DegreeTypeType DegreeType;
				///	����� �������� ���
				static const SS::Core::Features::Types::GenderTypeType GenderType;
				///	����� �������� �����
				static const SS::Core::Features::Types::NumberTypeType NumberType;
				///	����� �������� ��� �������������
				static const SS::Core::Features::Types::NumericTypeType NumericType;
				///	����� �������� �������������� ���������
				static const SS::Core::Features::Types::NegativeTypeType NegativeType;
				///	����� �������� ����������
				static const SS::Core::Features::Types::PhaseVerbTypeType PhaseVerbType;
				///	����� �������� ����
				static const SS::Core::Features::Types::PersonTypeType PersonType;
				///	����� �������� ������ �����������
				static const SS::Core::Features::Types::PronounGroupType PronounGroup;
				///	����� �������� ����� �����������
				static const SS::Core::Features::Types::PronounClassType PronounClass;
				///	����� �������� ���������
				static const SS::Core::Features::Types::ShortTypeType ShortType;
				///	����� �������� ����� �������
				static const SS::Core::Features::Types::TAdverbClassType TAdverbClass;
				///	����� �������� ��� �����
				static const SS::Core::Features::Types::TConjunctionTypeType TConjunctionType;
				///	����� �������� ��� ������������
				static const SS::Core::Features::Types::TDeterminerTypeType TDeterminerType;
				///	����� �������� �����
				static const SS::Core::Features::Types::TimeTypeType TimeType;
				///	����� �������� ������������
				static const SS::Core::Features::Types::TransitionalTypeType TransitionalType;
				///	����� �������� �����
				static const SS::Core::Features::Types::VoiceTypeType VoiceType;
				///	����� �������� ����� �������
				static const SS::Core::Features::Types::VerbFormType VerbForm;
				///	����� �������� ��� �������
				static const SS::Core::Features::Types::VerbTypeType VerbType;
				///	����� �������� ����������
				static const SS::Core::Features::Types::MoodTypeType MoodType;

			//������ ���������
				/// ������������� ����
				static const SS::Core::Features::Types::TSemanticTypeType TSemanticType;
				/// ������������� ��� �������
				static const SS::Core::Features::Types::TSTimeIntervalTypeType TSTimeIntervalType;
				/// ��� �����
				static const SS::Core::Features::Types::TSPlaceTypeType TSPlaceType;
				/// ��� ������
				static const SS::Core::Features::Types::TCityType		TCityType;
				/// ��� ������
				static const SS::Core::Features::Types::TAreaType		TAreaType;
				/// ��� ������
				static const SS::Core::Features::Types::TDistrictType	TDistrictType;
				/// ��� �����
				static const SS::Core::Features::Types::TMetroType		TMetroType;
				/// ��� �����/�������
				static const SS::Core::Features::Types::TGenericType		TGenericType;
				/// ��� ���������� ����������
				static const SS::Core::Features::Types::TSInfoType		TSInfoType;

				static const SS::Core::Features::Types::TSMaterialType		TSMaterialType;
				static const SS::Core::Features::Types::TSTransportType		TSTransportType;
				static const SS::Core::Features::Types::TSBuildingType		TSBuildingType;
				static const SS::Core::Features::Types::TSMFoodType			TSMFoodType;
				static const SS::Core::Features::Types::TSMForFreeTimeType	TSMForFreeTimeType;

				
				/// ���� ���
				static const SS::Core::Features::Types::TSMeasureTypeType TSMeasureType;
				/// ������������� ����, ���������� � �����
				static const SS::Core::Features::Types::TSPersonTypeType TSPersonType;
				/// ���� �����������
				static const SS::Core::Features::Types::TSOrganizationTypeType TSOrganizationType;
				/// ������������� ���� ��������
				static const SS::Core::Features::Types::TSVerbTypeType TSVerbType;
				///
				static const SS::Core::Features::Types::TSVBeTypeType TSVBeType;
				///
				static const SS::Core::Features::Types::TSVAcquirePossessTypeType TSVAcquirePossessType;
				///
				static const SS::Core::Features::Types::TSVAcquireTypeType TSVAcquireType;
				///
				static const SS::Core::Features::Types::TSVEndTypeType TSVEndType;
				///
				static const SS::Core::Features::Types::TSServiceTypesType TSServiceTypes;
			// ������ ����������
				/// ���������� �����������
				static const SS::Core::Features::Types::VerbConstructionType VerbConstruction;
				/// ����������� ����������������
				static const SS::Core::Features::Types::NounConstructionType NounConstruction;
				/// ����������� ���������������
				static const SS::Core::Features::Types::AdjectiveConstructionType AdjectiveConstruction;
				/// ��� ���������� �������
				static const SS::Core::Features::Types::TypeOfEndingObjectType TypeOfEndingObject;
				///
				static const SS::Core::Features::Types::CombiTypeType CombiType;
				/// �������������� ��������� (��� �����
				static const SS::Core::Features::Types::SyntaxCategoriesType SyntaxCategories;
				/// ����������� �����������
				static const SS::Core::Features::Types::HeadDependentTypeType HeadDependentType;
				/// ��� �����������
				static const SS::Core::Features::Types::SentenceTypeType SentenceType;
				/// ������� ���������� ��������
				static const SS::Core::Features::Types::ObjectsOrderType ObjectsOrder;
				/// ��������� �� ��������� � ������
				static const SS::Core::Features::Types::PositionToDetectedObjectType PositionToDetectedObject;
				/// �������������� �����
				static const SS::Core::Features::Types::ObjectObligationType ObjectObligation;
				/// ��� ������������
				static const SS::Core::Features::Types::AgreementTypeType AgreementType;
				/// ������� �������� �������
				static const SS::Core::Features::Types::ScopeOfTheRuleType ScopeOfTheRule;
				/// ������� � �����
				static const SS::Core::Features::Types::PositionInBlockType PositionInBlock;
				/// ������� ������� �����
				static const SS::Core::Features::Types::ChildrenAnalysisDepthType ChildrenAnalysisDepth;
				/// ������������ �������������� ������������� ������������� ��������
				static const SS::Core::Features::Types::SyntaxParamsInheritanceModeType SyntaxParamsInheritanceMode;
				/// ������� ����� ����
				static const SS::Core::Features::Types::CreateUnitType CreateUnit;
				/// ��� ����������� �����
				static const SS::Core::Features::Types::MoveTypeType MoveType;
			}
		}
	}
}