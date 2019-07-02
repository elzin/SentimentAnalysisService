#pragma once

#include "..\ASSInterface\ISyntaxConstructions.h"

#include "..\ASSInterface\ICoSeDi.h"


namespace SS
{
	namespace SyntaxConstructions
	{
		namespace SQL
		{
			class CSyntaxConstructionGroupsNames : public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionGroupsNames
			{
			public:
				///�����������
				CSyntaxConstructionGroupsNames(void);
				///����������
				~CSyntaxConstructionGroupsNames(void);
			
				/// ���������� ������ ���� ������� ����������� � �� �����
				void Get(/*out*/std::list<SS::SyntaxConstructions::Types::SSyntaxConstructionGroupName> * p_list_SyntaxConstructionGroup)
				{
					/*SS::SyntaxConstructions::DataTypes::SSyntaxConstructionGroupName oSyntaxConstructionGroupName;
					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgIndefinable;
					oSyntaxConstructionGroupName.m_sName	= "����� �����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbObjecrBinder;
					oSyntaxConstructionGroupName.m_sName	= "����� ������ ����������� ����� �������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ������������ �������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModalVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� �������� ������� ��������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModalVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ������� ��������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgPrepositionPhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ���������� �����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounPostModifierBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����������������� ����������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� �������� ������� ��������������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ������������ �������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounPhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ����������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ��������� �����������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinderIndexation;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ��������� �����������(����������)";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinderQuery;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ��������� �����������(������)";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ������� ��������������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectMainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ��������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUtility;
					oSyntaxConstructionGroupName.m_sName	= "������ ��������������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgQuestionWordDetector;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������������� ����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ������� ���������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);
					
					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbAdverbBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� �������� �� ���������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);
					
					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgQuestionVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ���������� ������� � �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgMorphologyAmbiguityResolveCommon;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ��� ���� ����� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgMorphologyAmbiguityResolveIndexation;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ��� ����������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgMorphologyAmbiguityResolveQuery;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ��� ������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModAuxQuestVerbBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ���������������� ������� � �������� � �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAdjectivePhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ��������������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveParticiplePhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ���������� � ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgIntransitiveRemover;
					oSyntaxConstructionGroupName.m_sName	= "������, ��������� �������� � ������������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbComplementBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� �������� � ���������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgBeNounParticipleBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������, ����������� be + Noun + Participle";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgTimePlacePrepBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ����������� ������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgTimePlacePrepPostBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ����������� ������� ��������� � ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUniformMembersBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ���������� ������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);*/
				}
			public:
				/// ��������� � �������� ��� ��������� ������ 
				bool ToBinary(){};
				/// ������� ������� �����������
				void Delete()
				{}
				/// �������� ������� �����������
				void Add()
				{}
				/// ��������� ������� �����������
				void Update()
				{}
			};
		};

		namespace DBMS
		{
			class CSyntaxConstructionGroupsNames : public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionGroupsNames
			{
			public:
				/// �����������
				CSyntaxConstructionGroupsNames(void);
				/// ����������
				~CSyntaxConstructionGroupsNames(void);
			
				/// ���������� ������ ���� ������� ����������� � �� �����
				void Get(/*out*/std::list<SS::SyntaxConstructions::Types::SSyntaxConstructionGroupName> * p_list_SyntaxConstructionGroup)
				{
					/*SS::SyntaxConstructions::Types::SSyntaxConstructionGroupName oSyntaxConstructionGroupName;

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUtilityQuery;
					oSyntaxConstructionGroupName.m_sName	= "������ ��������������� ��������� ��� ������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					//oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUniformMembersBuilder;
					//oSyntaxConstructionGroupName.m_sName	= "������ ����� ���������� ������";
					//p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgIndefinable;
					oSyntaxConstructionGroupName.m_sName	= "����� �����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);
					
					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgMorphologyAmbiguityResolveCommon;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ��� ���� ����� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgMorphologyAmbiguityResolveIndexation;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ��� ����������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgMorphologyAmbiguityResolveQuery;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ��� ������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ������������ �������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModalVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� �������� ������� ��������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUtility;
					oSyntaxConstructionGroupName.m_sName	= "������ ��������������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� �������� ������� ��������������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ������� ���������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounPhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ����������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgBeNounParticipleBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������, ����������� be + Noun + Participle";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����������� ������� � ��������� �� ��� ������ //07.09";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinderIndexation;
					oSyntaxConstructionGroupName.m_sName	= "";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinderQuery;
					oSyntaxConstructionGroupName.m_sName	= "";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModalVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ������� ��������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ������� ��������������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgQuestionWordDetector;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������������� ����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbAdverbBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� �������� �� ���������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAdjectivePhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ��������������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgTimePlacePrepBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ����������� ������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgPrepositionPhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ���������� �����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgTimePlacePrepPostBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ����������� ������� ��������� � ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgIntransitiveRemover;
					oSyntaxConstructionGroupName.m_sName	= "������, ��������� �������� � ������������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveParticiplePhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ���������� � ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ������������ �������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounPostModifierBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����������������� ����������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectMainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ��������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModAuxQuestVerbBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ���������������� ������� � �������� � �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgQuestionVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ���������� ������� � �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbComplementBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� �������� � ���������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbObjecrBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� �������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAllBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ��� ������������ ���� �� ��������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);
					//��������
					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUniformMembersBinderPostHyp;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ���������� ������ ����� ��������� �� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);
					//
					//oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainBuilderIndexation;
					//oSyntaxConstructionGroupName.m_sName	= "������ ����������� ���������� ������� ��������������� ��������";
					//p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);
					//
					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUniformMembersBinderFinal;
					oSyntaxConstructionGroupName.m_sName	= "������ ����� ���������� ������ ����� ��������� �� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);


					/*oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgIndefinable;
					oSyntaxConstructionGroupName.m_sName	= "����� �����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgVerbObjecrBinder;
					oSyntaxConstructionGroupName.m_sName	= "����� ������ ����������� ����� �������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� ������������ �������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModalVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� �������� ������� ��������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgModalVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ������� ��������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgPrepositionPhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ���������� �����";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounPostModifierBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����������������� ����������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainMorphoResolve;
					oSyntaxConstructionGroupName.m_sName	= "������ ���������� ��������������� �������� �������� ������� ��������������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgInfinitiveVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ������������ �������� �������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgNounPhraseBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ����������������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectVerbBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ��������� �����������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAuxVerbChainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� �������� ������� ��������������� ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgSubjectMainBuilder;
					oSyntaxConstructionGroupName.m_sName	= "������ ����������� ����� ��������� � ��������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgUtility;
					oSyntaxConstructionGroupName.m_sName	= "������ ��������������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);

					oSyntaxConstructionGroupName.m_ID		= SS::Syntax::Types::tcgAllBinder;
					oSyntaxConstructionGroupName.m_sName	= "������ ��� ������������ ���� �� ��������� ���������";
					p_list_SyntaxConstructionGroup->push_back(oSyntaxConstructionGroupName);*/
				}
			public:
				/// ������� ������� �����������
				void Delete()
				{}
				/// �������� ������� �����������
				void Add()
				{}
				/// ��������� ������� �����������
				void Update()
				{}
			};
		};
	};
};
