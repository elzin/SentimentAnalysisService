#pragma once
#include "..\..\cpp\ASSInterface\IBlackBox.h"

#include "..\..\cpp\ASSInterface\ICoSeDi.h"
namespace LinguisticsKernel
{
	public ref class CStringService
	{
	public:
		CStringService(void);
		~CStringService(void);

		///������ ���������� �������� ���� �������
		System::String^ IndexTypeToString(SS::Interface::Core::BlackBox::EIndexType indexType);
		///������ ���������� �������� ���� �������������
		System::String^ TransformationTypeToString(SS::Interface::Core::BlackBox::Query::ETransformationType transformationType);

		///������ ���������� �������� ������ �������
		System::String^ DictionaryIndexToString(System::UInt32 index);
		///������ ������� ���������� �������� ������ �������
		System::String^ DictionaryIndexToShortString(System::UInt32 index);

		///������ ���������� �������� �������������� �������
		System::String^ SemanticIndexToString(System::UInt32 index);
		///������ ���������� �������� �������������� �������
		System::String^ SyntaxIndexToString(System::UInt32 index);
		///������ ���������� �������� ��������������� �������
		System::String^ SynonymIndexToString(System::UInt32 index);
		///������ ���������� �������� ���������������� �������
		System::String^ MorphoIndexToString(System::UInt32 index);
		///������ ������� ���������� �������� ���������������� �������
		System::String^ MorphoIndexToShortString(System::UInt32 index);

		System::String^ DictionaryIndexToString1(System::UInt32 index);

		System::String^ LanguageIndexToString(System::UInt32 index);

		//System::String^ GetMorphoString(SS::Core::Features::CMorphoFeature& oMorphoFeature);



//		void SetSemanticClassesTree(SS::Interface::Core::ISemanticClassesTree* pSemanticClassesTree);
	};
}