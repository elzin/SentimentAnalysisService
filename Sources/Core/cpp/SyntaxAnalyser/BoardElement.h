#pragma once

#include "BoardCommonTypes.h"
#include "MorphoListElement.h"
#include "BlockVersion.h"
#include "MorphoFormsFilter.h"
#include "../ASSInterface/Construction.h"
#include "../ASSInterface/IAMConverter.h"
#include "../ASSInterface/IBlackBoxUnit.h"
#include "../ASSInterface/TMainAnalyseTypes.h"
#include <list>
#include "Container.h"

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///������� �����. ������ ��� �������� ���������� �� �������������� �����
			class CBoardElement
			{
				///��������� ��� �������� �� � ��� ������
				struct SLayer
				{
					///���������� ����� ������������� ����������� � ��
					unsigned int iNumber;
					///��� ������������
					SS::Core::Features::Types::AgreementType oAgreementType;
					///�����������
					SLayer() : iNumber(0) { oAgreementType.Undefine(); };
				};
			
			private:
				///������ ���������, ������� ����� ������� �������
				CContainer<MORPHO, SIZEMORPHO> m_oMorphoContainer;
				///������ ������� ��������, ������� ��������� �� AgrimentType
				std::list<PMORPHO> m_oMorphoContainerAT;
				///����, ���������������, ���� ������� ������ � �����������, ������� ������� ����������� �� �����.
				bool m_beatsBlocks;
				///����, �����������, ����� �� ������� � ������ �� ������� ������.
				bool m_isHead, m_isHeadDynamic;				
				///����, ���������������, ���� ���� ������������ ������� �������� ������ �������� �����
				bool m_useVersion;
				///��� �������� �������������� IFeature (��� �������� �����)
				SS::Interface::Core::BlackBox::IBlackBoxTextStorage *m_pBlackBoxTextStorage;
				///��������������� ���������
				SS::Interface::Core::AMConverter::IAMConverterMorpho *m_pAMConverterMorpho;
				///������������� ���������
				SS::Interface::Core::AMConverter::IAMConverterSemantic *m_pAMConverterSemantic; 
				///������������� �������������� ����������.
				SS::Core::Features::CSyntaxFeatureAposteriori m_syntaxFeatureAposteriori;
				///��������� �������������� ����������.
				SS::Core::Features::CSyntaxFeatureApriori m_syntaxFeatureApriori;
				///������ ��� ��������� ���������
				CSemanticService m_oSemanticService;
				///����, �������� ������������� ������� �����
				SS::Interface::Core::BlackBox::IUnit *m_pUnit;
				///�����
				std::wstring m_word;
				///������������� ������ ���������, ������� ������� ��������� ����� �������������� ���������� ��������.
				int m_iIdGroup, m_iIdGroupDynamic;
				///��������� �� ������� ��������, ��������������� ������� ��������
				PVERELEMENT m_pVersionElement;
				///���� �����������
				SS::Core::Types::EAnalyseLanguage m_eLang;
				///������� �� ���������
				unsigned int m_uiDefPosition;
				///������ � ���������������� ����������������
				CMorphoFormsFilter m_oMorphoFormsFilter;
				///��������� ����� ����������� ����������� � ��
				std::vector<SLayer> m_vATLayers;
                /// ����, ����������� �� ���������� ��������� �������� �����
                bool m_IsDone;
				
			private:
				///������������� m_word, ������������ ���������� ��� � ������ �������
				void SetWord(const std::wstring &wsWord);
				///������� ���������� ���������� � ������ ������
				void ClearData();
				///����������� ���������� (��� �������� �����)
				void DivisionMorpho();
				///������� ���������� �� ����������� �� ��
				void RemoveMorphoButAT();
			
			public:
				///���������� � ������ ����� ����������� ( ������� ���� ������� �� �� ������������� �������������� )
				std::list<BoardElements::BoardElementsIterator> m_childUniformMembers;
			
			public:
				///�����������
				CBoardElement(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
				//����������
				~CBoardElement();
				//����� ��� ������������� ������ ��������� ������
				bool Init( SS::Interface::Core::BlackBox::IUnit* unit,
						   SS::Core::Types::EAnalyseLanguage eLang,
						   unsigned int uiPosition );
				///���������� ������� �������� ������� �������� (��� ��������)
				const PVERELEMENT GetVerElem() const { return m_pVersionElement; };
				///���������� ���� �������� (��� ��������)
				SS::Core::Types::EAnalyseLanguage GetLang() const;
				///���������� ��������� �� ������ ������� ���������� ����������
				CMorphoListElement* GetFirstMorpho()
				{
					if (!m_useVersion)
					{ return m_oMorphoContainer.GetFirst();	}
					else
					{ return m_pVersionElement->m_pMorpho; }
				}
				///���������� ��������� �� ��������� ������� � ���������� ����������
				CMorphoListElement* GetNextMorpho()
				{
					if (!m_useVersion)
					{ return m_oMorphoContainer.GetNext(); }
					else
					{ return NULL; }
				}
				///���������� ��������� �� ������ ������� ���������� ����������(��� ������������� �������� �������)
				PMORPHO GetFirstMorphoDynamic();
				///���������� ��������� �� ��������� ������� � ���������� ����������(��� ������������� �������� �������)
				PMORPHO GetNextMorphoDynamic();
				///���������� ��������� �� ��������� ����� ���������� ������� � ���������� ����������
				PMORPHO GetNextMorphoForAddress(PMORPHO pMorpho);
				///���������� �����, ��������������� ������� ��������.
				std::wstring & GetWord() { return m_word; };
				///���������� ������ ������������� ��������
				int GetParentIndex() const
				{
					if (m_useVersion)
					{ return m_pVersionElement->m_syntaxFeatureAposteriori.m_IdParent.GetValue(); }
					else
					{ return m_syntaxFeatureAposteriori.m_IdParent.GetValue(); }
				}
				///������������� �������� ����� ������������� �������������� ������� �����������
				void ApplyConstruction( SS::SyntaxConstructions::Types::CConstructionObject* pObject, 
									    int parentIndex, int ownIndex, int iIdGroup, unsigned int iCountApplyedExpertAT, 
										CBoardElement* pElemBaseSemantic );
				///����������� ����� �������������� ���������
				void SetFeatureToUnit();
				///���������� ����, ������������, �������� �� ������ ������� �������� �����
				bool BeatsBlocks() const { return m_beatsBlocks; };
				///������ ����, ������������, �������� �� ������ ������� �������� �����
				void SetBeatsBlocks() {	m_beatsBlocks = true; };
				///���������� ������������� �������������� ���������� ��������
				SS::Core::Features::CSyntaxFeatureAposteriori & GetSyntaxFeature()
				{
					if (m_useVersion)
					{ return m_pVersionElement->m_syntaxFeatureAposteriori;	}
					else
					{ return m_syntaxFeatureAposteriori; }
				}
				SS::Core::Features::CSyntaxFeatureAposteriori & GetSyntaxFeature1()
				{
					//if (m_useVersion)
					//{ return m_pVersionElement->m_syntaxFeatureAposteriori;	}
					//else
					{ return m_syntaxFeatureAposteriori; }
				}
				///���������� ������������� �������������� ���������� �������� (��� ������������� �������� �������)
				SS::Core::Features::CSyntaxFeatureAposteriori & GetSyntaxFeatureDynamic() { return m_syntaxFeatureAposteriori; }
				///���������� ����, ������������, �������� �� ������� ��������
				bool IsHead() const	{ return m_isHead; };
				///��������� �������� ��������
				void SetHead(bool bHead) { m_isHead = bHead; };
                ///���������� ����, ����������� �� ���������� ��������� �������� �����
                bool IsDone() { return m_IsDone; }
                /// ��������� ���������� ��������� �������� �����
                void SetDone(bool bDone) { m_IsDone = bDone; }
				///���������� ����, ������������, �������� �� ������� �������� ( ������������ ��� ������������ �������� ������� )
				bool IsHeadDynamic() const { return m_isHeadDynamic; };
				///���������� �������� ������, ������������ �������� �������������� ��������������
				int GetGroup() { return m_iIdGroup;	};
				///���������� �������� ������, ������������ �������� �������������� �������������� ( ������������ ��� ������������ �������� ������� )
				int GetGroupDynamic() { return m_iIdGroupDynamic; };
				///������������� ������� ������
				void SetVersion(PVERELEMENT pVersion)
				{
					m_pVersionElement = pVersion;
					m_iIdGroup = pVersion->m_iIdGroup;
					m_isHead = pVersion->m_isHead;
					m_useVersion = true;
				}
				///���������, ��������� �� ��������� �� �������� ��� ���
				bool UseVersions() const { return m_useVersion;	};
				///���������, �������� �� ������� ������ �������������� �����������
				bool IsUnusedForm() const
				{ return ( m_useVersion && (m_pVersionElement->m_morphoFeatureApriori.m_PartOfSpeechTypes.IsUndefined()) );	};
				///���������� ��������� �������������� ����������
				SS::Core::Features::CSyntaxFeatureApriori & GetSyntaxFeatureApriori()
				{
					if (m_useVersion)
					{ return m_pVersionElement->m_syntaxFeatureApriori;	}
					else
					{ return m_syntaxFeatureApriori; }
				}
				///���������� ��������� �������������� ���������� (��� ������������� �������� �������)
				SS::Core::Features::CSyntaxFeatureApriori & GetSyntaxFeatureAprioriDynamic()	{ return m_syntaxFeatureApriori; };
				///���������� ������������� ���
				SS::Core::Features::Types::TSemanticType & GetSemanticType() { return GetSemanticFeature().m_SemanticType; };
				///���������� ������������� ��������������
				SS::Core::Features::CSemanticFeature & GetSemanticFeature();
				///���������� ��������� �� ����, ��������������� �������� �����
				SS::Interface::Core::BlackBox::IUnit* GetUnit() const { return m_pUnit; };
				///����� ���� �������� ��������
				void Reset();
				///������� ��� ���������� ����� ��� ������� � �������� (������������ ������ ����� �������)
				void RemoveUselessMorpho();
				///�������� ����������� �������
				unsigned int GetPosition() const { return m_uiDefPosition; };
				///���������� �����-���� ����������� �� AgrimentType-�
				void AddMorphoAT(CMorphoListElement* pMorpho);
				///�������� ��������� ���������� ����������� �� ��
				std::list<PMORPHO> & GetMorphoContainerAT() { return m_oMorphoContainerAT; };
				///���� �� �� �� ������� ������
				bool IsAT(unsigned int iNumber) const;
				///�������� �� �� ������ ����������� �����������
				SS::Core::Features::Types::AgreementType GetAT(unsigned int iNumber) const;
				///��������� ������������� ���� � IText
				void RemoveUselessSemantic();
				///�������� ������������� ������
				const CSemanticService & GetSemanticService(){ return m_oSemanticService; };

				bool IsSemantic(SS::Interface::Core::BlackBox::IUnit* pUnit, SS::Core::Features::Types::TSemanticType semType);

				bool IsPersonApostrof(SS::Interface::Core::BlackBox::IUnit* pUnit);				
				
			};

		}
	}
}
