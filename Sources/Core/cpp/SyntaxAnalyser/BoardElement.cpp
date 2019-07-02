#include "stdafx.h"
#include "BoardElement.h"

#include "../ASSInterface/IAMConverter.h"
#include "../ASSInterface/TDictionaryNames.h"
#include "../ASSInterface/TDictionaryManager.h"

using namespace SS::Core::Features;

namespace SS
{
namespace Syntax
{
namespace BoardElements
{
using namespace SS::SyntaxConstructions::Types;
using namespace SS::Interface::Core::BlackBox;
using namespace std;

//�����������
CBoardElement::CBoardElement(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager) : 
	m_isHead(true), m_isHeadDynamic(true),
	m_beatsBlocks(false), m_useVersion(false),
	m_uiDefPosition(0), m_pUnit(NULL), m_IsDone(false),
	m_iIdGroup(-1), m_iIdGroupDynamic(-1), m_pVersionElement(NULL), 
	m_eLang(SS::Core::Types::EAnalyseLanguage::ealUndefined)
{
	SS_TRY
	{
		using SS::Interface::Core::AMConverter::IAMConverterSemantic;
		using SS::Interface::Core::AMConverter::IAMConverterMorpho;
		using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;
		
		//��������� ConverterMorpho
		m_pAMConverterMorpho = (IAMConverterMorpho*)
			pLoadManager->GetInterface(L"./core/linguistics/AMConverter.dll", CLSID_AMConverterMorpho, IID_AMConverterMorpho);
		//�������� ConverterSemantic
		m_pAMConverterSemantic = (IAMConverterSemantic*)
			pLoadManager->GetInterface(L"./core/linguistics/AMConverter.dll", CLSID_AMConverterSemantic, IID_AMConverterSemantic);
		//�������� TextStorage
		m_pBlackBoxTextStorage = (IBlackBoxTextStorage*)
			pLoadManager->GetInterface(L"./core/linguistics/BlackBox.dll", CLSID_BlackBoxTextStorage, IID_BlackBoxTextStorage);
		if ( (!m_pAMConverterMorpho) || (!m_pAMConverterSemantic) || (!m_pBlackBoxTextStorage) )
		{ SS_THROW(L"������ ��� �������� ���������� ��� ����� ��������."); }
		//������ ��� ������
		m_word.reserve(SS::Constants::MAX_CHARS_IN_WORD);
		//��������� � ������������� ������
		m_oSemanticService.SetSemanticConverter(m_pAMConverterSemantic);
		m_oSemanticService.SetTextStorage(m_pBlackBoxTextStorage);
	}
	SS_CATCH(L"")
}

//����������
CBoardElement::~CBoardElement()
{
	ClearData();
}

//������� ���������� ���������� � ������ ������
void CBoardElement::ClearData()
{
	SS_TRY
	{
		m_oMorphoContainer.Clear();
		m_oMorphoContainerAT.clear();
		m_iIdGroup = -1;
		m_childUniformMembers.clear();
		m_vATLayers.clear();
		
		m_syntaxFeatureAposteriori.Undefine();
		m_syntaxFeatureApriori.Undefine();
		m_oSemanticService.Clear();
		m_uiDefPosition = 0;
				
		m_isHead = true;
		m_isHeadDynamic = true;
		m_beatsBlocks = false;
		m_useVersion = false;
	}
	SS_CATCH(L"")
}

bool CBoardElement::IsSemantic(IUnit* pUnit, SS::Core::Features::Types::TSemanticType semType)
	{
		SS::Interface::Core::BlackBox::IIndex* pIndex;
		SS::Interface::Core::BlackBox::IDictionaryIndex* pDictionaryIndex;
		SS::Interface::Core::BlackBox::EIndexType oIndexType;
			
		for(pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			pDictionaryIndex = pIndex->GetDictionaryIndex();
			
			if(pDictionaryIndex)
			{
				SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex = pDictionaryIndex->GetFirst();
				oIndexType = oDictionaryIndex.GetIndexType();
				if (oIndexType==SS::Interface::Core::BlackBox::eitSemanticIndex)
				{							
					int index = oDictionaryIndex.GetDictionaryIndex();
					SS::Core::Features::CSemanticFeature oSemanticFeature;							
   					m_pAMConverterSemantic->EnCode(index, &oSemanticFeature);					
					if (oSemanticFeature.m_SemanticType.IsContain(semType))						
					{
						return true;
					}
				}
			}
		}

		return false;
	}	

bool CBoardElement::IsPersonApostrof(SS::Interface::Core::BlackBox::IUnit* pUnit)
{
	IUnit *pChild = pUnit->GetLeftChildUnit();
	if (pChild!=NULL)
	{
		SS::Dictionary::Types::TDictionaryIndex oIndexVal;	
		if (pChild->GetFirstIndex()==NULL) return false;
		pChild->GetFirstIndex()->GetDictionaryIndex()->GetFirst(&oIndexVal);
		if (!oIndexVal.GetFirstLetterUpperCase()) return false;
	}
	while (pChild!=NULL)
	{
		wstring str = pChild->GetWord();
		if (str.size()>0 && (str[0]=='\'' || str[0]=='`')) return true;
		pChild = pChild->GetRightUnit();		
	}
	return false;
}


//����� ��� ������������� ������ ��������� ������
bool CBoardElement::Init( SS::Interface::Core::BlackBox::IUnit* pUnit,
						  SS::Core::Types::EAnalyseLanguage eLang,
						  unsigned int uiPosition )
{
	SS_TRY
	{
		ClearData();
		SetWord(pUnit->GetWord());
		m_oSemanticService.SetUnit(pUnit);

		m_pUnit = pUnit;
		m_eLang = eLang;
		m_syntaxFeatureAposteriori.m_IdParent = uiPosition;
		m_uiDefPosition = uiPosition;
	
		CMorphoListElement* pMorphoListElement = NULL;
		IDictionaryIndex* pDictionaryIndex = NULL;
		
		SS::Dictionary::Types::TDictionaryIndex oIndexVal;

		wstring s = pUnit->GetWord();
		int len = s.size();

		IIndex *pIndex = pUnit->GetFirstIndex();
		bool isPerson = 
			(IsSemantic(pUnit,SS::Core::Features::Values::TSemanticType.smtService) ||
			 IsSemantic(pUnit,SS::Core::Features::Values::TSemanticType.smtPerson) || 
			 IsPersonApostrof(pUnit) /*Ahmadinejad's*/ || IsSemantic(pUnit,SS::Core::Features::Values::TSemanticType.smtPlace))
			 && len == 0 && !IsSemantic(pUnit,SS::Core::Features::Values::TSemanticType.smtTimeInterval);


		bool isNom = false;
		bool isProp = false;
		for (IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednRProperName ||
				pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednAbbreviationsRus) isProp = true;
			if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednRNominalName) isNom = true;

			if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednEProperName ||
				pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednAbbreviationsEng) isProp = true;
			if (pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryNumber()==SS::Dictionary::DATA_TYPE::NAMES::ednENominalName) isNom = true;
		}

		if (isNom && !isProp) 
		{
			pUnit->SetIsNominalOnly(true);
		}
		else 
		{
			pUnit->SetIsNominalOnly(false);
		}

		for (IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			//��������� IDictionaryIndex
			if ( !(pDictionaryIndex = pIndex->GetDictionaryIndex()) ) 
			{ 
				SS_THROW(L"����������� IDictionaryIndex.");
			}
			
			//��������� TDictionaryIndex
			if ( pDictionaryIndex->GetFirst(&oIndexVal) ) 
			{
				//������ ����������
				for (IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
				{
					if ( pMorphoListElement = m_oMorphoContainer.Add() ) 
					{ 
						pMorphoListElement->Init(m_pAMConverterMorpho, pFeature, pIndex, uiPosition, isPerson); 
					}
					else
					{ 
						SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"���������� ������� ���������� ������������������." AND m_word.c_str());
					}
				}
			}
			else
			{ 
				continue;
			}
					
			//������ ���������
			do 
			{
				if (oIndexVal.GetIndexType() == eitSemanticIndex)
				{
					SS::Core::Features::CSemanticFeature oSemanticFeature;
					m_pAMConverterSemantic->EnCode( oIndexVal, &(oSemanticFeature) );
					m_oSemanticService.AddSemantic(pIndex, &oSemanticFeature);
				}
			} 
			while ( pDictionaryIndex->GetNext(&oIndexVal) );
		}

		if ( pUnit->GetSyntaxFeature() && pUnit->GetSyntaxFeature()->GetSyntaxFeatureApriori() )
		{
			m_syntaxFeatureApriori = *(pUnit->GetSyntaxFeature()->GetSyntaxFeatureApriori());	
		}
		
		//�������� �������� �� ����������� ������� � �������
		if (m_oMorphoContainer.Empty())
		{ 
			SAVE_LOG( SS_WARNING AND __WFUNCTION__ AND (wchar_t*)m_word.c_str() AND L" - � ����. ������� �� ���������� �.� �� ����� ����������." );
			return false; 
		}
		
		//�������
		if (eLang == SS::Core::Types::ealRussian) 
		{ 
			m_oMorphoFormsFilter.FilterMorphoContainerRus(m_oMorphoContainer);
			DivisionMorpho();
		}
		else
		{ 
			m_oMorphoFormsFilter.FilterMorphoContainer(m_oMorphoContainer);
		}
	}
	SS_CATCH(L"")
	return true;
}

//������� ����� �����������
Core::Types::EAnalyseLanguage CBoardElement::GetLang() const
{
	return m_eLang;
}

void CBoardElement::ApplyConstruction( CConstructionObject* pObject, int parentIndex, int ownIndex, 
									   int iIdGroup, unsigned int iCountApplyedExpertAT, CBoardElement* pElemBaseSemantic )
{
	SS_TRY
	{
		//��������� ���������
		if ( (pElemBaseSemantic == NULL) || (pElemBaseSemantic == this) )
		{ 
			if (m_useVersion)
			{
				m_pVersionElement->m_oSemanticService.ApplyConstructionObject(pObject);
			}
			else
			{
				m_oSemanticService.ApplyConstructionObject(pObject);
			}	
		}
		else
		{
			if (m_useVersion) 
			{
				m_pVersionElement->m_oSemanticService.ApplyConstructionObject(pObject, &(pElemBaseSemantic->m_oSemanticService)); 
			}
			else
			{
				m_oSemanticService.ApplyConstructionObject(pObject, &(pElemBaseSemantic->m_oSemanticService)); 
			}
		}
		
		bool* pHead;
		SS::Core::Features::CSyntaxFeatureAposteriori* pSyntaxFeatureAposteriori;
		int* pIdGroup;
		SS::Core::Features::CSyntaxFeatureApriori* pSyntaxFeatureApriori;

		if (m_useVersion)
		{
			pHead						= &m_pVersionElement->m_isHead;
			pSyntaxFeatureAposteriori	= &m_pVersionElement->m_syntaxFeatureAposteriori;
			pIdGroup					= &m_pVersionElement->m_iIdGroup;
			pSyntaxFeatureApriori		= &m_pVersionElement->m_syntaxFeatureApriori;
		}
		else
		{
			pHead						= &m_isHead;
			pSyntaxFeatureAposteriori	= &m_syntaxFeatureAposteriori;
			pIdGroup					= &m_iIdGroup;
			pSyntaxFeatureApriori		= &m_syntaxFeatureApriori;
		}

		*pIdGroup = iIdGroup;
		if (!m_useVersion)
		{ m_iIdGroupDynamic = iIdGroup; }

		if ( ( !pObject->m_SyntaxFeatureAposteriori.m_SyntaxCategories.IsUndefined() ) &&
				( pObject->m_SyntaxFeatureAposteriori.m_SyntaxCategoryPower > pSyntaxFeatureAposteriori->m_SyntaxCategoryPower ) )
		{
			pSyntaxFeatureAposteriori->m_SyntaxCategories = pObject->m_SyntaxFeatureAposteriori.m_SyntaxCategories;
			pSyntaxFeatureAposteriori->m_SyntaxCategoryPower = pObject->m_SyntaxFeatureAposteriori.m_SyntaxCategoryPower;
			pSyntaxFeatureApriori->m_SyntaxCategories = pObject->m_SyntaxFeatureAposteriori.m_SyntaxCategories;
		}

		if ( pObject->m_SyntaxFeatureAposteriori.m_DependencyPower > pSyntaxFeatureAposteriori->m_DependencyPower )
		{
			if (parentIndex == ownIndex) 
			{
				pSyntaxFeatureAposteriori->m_IdParent = parentIndex;
				pSyntaxFeatureAposteriori->m_DependencyPower = pObject->m_SyntaxFeatureAposteriori.m_DependencyPower;
				*pHead = true;
			}
			
			//������������� ���������� �������� ������ ��������� �������� � ���� �����
			if ( (pObject->m_SyntaxFeatureAposteriori.m_IdParent != UINT_MAX) && (parentIndex != ownIndex) )
			{
				pSyntaxFeatureAposteriori->m_IdParent = parentIndex;
				pSyntaxFeatureAposteriori->m_DependencyPower = pObject->m_SyntaxFeatureAposteriori.m_DependencyPower;
				*pHead = false;
				if (!m_useVersion)
				{ m_isHeadDynamic = false; }
			}
		}
			
		//������������ ������ ��������������� ���������� ��� ���������� ��������
		
		const unsigned int MinCountMorpho = 1;	//���������� ��������� ���������� ����������

		if ( pObject->m_MorphoFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmRemove) )
		{
			if (m_useVersion)
			{ m_pVersionElement->m_morphoFeatureApriori.Undefine(); }
			else
			{
				for (PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho; pMorpho = m_oMorphoContainer.GetNext())
				{
					if ( pObject->m_MorphoFeatureAposteriori.IsIntersectsWith(pMorpho->GetMorphoFeature(), m_eLang) )	
					{
						//�������� ������ ���� ��� �� ��������� ����
						if (m_oMorphoContainer.Size() > MinCountMorpho) 
						{
							pMorpho->ReleaseFeature();
							m_oMorphoContainer.DeleteCurrent();
						}
					}
				}
			}
		}
		else if ( pObject->m_MorphoFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmSelect) )	
		{
			if (m_useVersion)
			{ SAVE_LOG(L"������� ������� ��������������� ���������� �� ��������. �������, ���������� � ����������, �� ������ ������ Remove � Select"); }
				
			//���� ��� ��
			if (pObject->m_ObjectFeature.m_AgreementType.IsUndefined())
			{
				for ( PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho && (m_oMorphoContainer.Size() > MinCountMorpho);
					  pMorpho = m_oMorphoContainer.GetNext() )
				{
					if ( !pObject->m_MorphoFeatureAposteriori.IsIntersectsWith(pMorpho->GetMorphoFeature(), m_eLang) )
					{
						pMorpho->ReleaseFeature();
						m_oMorphoContainer.DeleteCurrent();
					}
				}
			}
			else
			{
				std::list<PMORPHO>::iterator it(m_oMorphoContainerAT.begin());
				while ( it != m_oMorphoContainerAT.end() )
				{
					if ( !pObject->m_MorphoFeatureAposteriori.IsIntersectsWith((*it)->GetMorphoFeature(), m_eLang) )
					{
						it = m_oMorphoContainerAT.erase(it);
						continue;
					}
					++it;
				}
			}
		}
		else if ( pObject->m_MorphoFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmAppoint) )	
		{
			//���� �� ���������� ������� ���� ��������
			PMORPHO pMorphoNeed = NULL;
			//���� PartOfSpeech �� ������������ �� ���� �������� ���������� ���� ����� � ��������
			if ( !pObject->m_MorphoFeatureApriori.m_PartOfSpeechTypes.IsIntersectsWith(
																	&pObject->m_MorphoFeatureAposteriori.m_PartOfSpeechTypes ) ) 
			{ 
				for (pMorphoNeed = m_oMorphoContainer.GetFirst(); pMorphoNeed; pMorphoNeed = m_oMorphoContainer.GetNext())
				{
					if ( pObject->m_MorphoFeatureAposteriori.m_PartOfSpeechTypes.Equal(pMorphoNeed->GetMorphoFeature().m_PartOfSpeechTypes) )
					{ break; }
				}
			}
			//���� ����� ���� ���
			if (!pMorphoNeed) 
			{
				if (!m_useVersion)
				{
					//����� ��������� ����� ����, �� ������� ��������� �����������. ��� ������ �������������� 100%.
					for (PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho; pMorpho = m_oMorphoContainer.GetNext())
					{
						if ( pObject->m_MorphoFeatureApriori.IsIntersectsWith(pMorpho->GetMorphoFeature(), m_eLang) )
						{ 
							pMorpho->SetMorphoFeature( &pObject->m_MorphoFeatureAposteriori ); 
						}
						else
						{
							pMorpho->ReleaseFeature();
							m_oMorphoContainer.DeleteCurrent();
						}
					}
					if ( m_oMorphoContainer.Empty() ) 
					{ SS_THROW(L"������ ���� �� �����"); }
				}
				else
				{
					m_pVersionElement->m_morphoFeatureApriori.AssignMorphoFeature( &pObject->m_MorphoFeatureAposteriori );
					(m_pVersionElement->m_pMorpho)->SetMorphoFeature( &pObject->m_MorphoFeatureAposteriori );	
				}
			}
			else
			{
				if (!m_useVersion)
				{
					for (PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho; pMorpho = m_oMorphoContainer.GetNext())
					{
						if ( pMorpho != pMorphoNeed )
						{
							pMorpho->ReleaseFeature();
							m_oMorphoContainer.DeleteCurrent();						
						}
						else
						{
							pMorpho->SetMorphoFeature( &pObject->m_MorphoFeatureAposteriori );
						}					
					}
				}
				else
				{ pMorphoNeed->SetMorphoFeature( &pObject->m_MorphoFeatureAposteriori ); }
			}
		}
		else if ( pObject->m_MorphoFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmAdd) )
		{
			for (PMORPHO pM = GetFirstMorpho(); pM; pM = GetNextMorpho())
			{
				if ( pObject->m_MorphoFeatureApriori.IsIntersectsWith(pM->GetMorphoFeature(), m_eLang) )
				{ pM->AddMorphoFeature(&pObject->m_MorphoFeatureAposteriori); }
			}
		}

		//��������� AgreementType
		if ( !pObject->m_ObjectFeature.m_AgreementType.IsUndefined() )
		{
			if (m_useVersion)
			{
				//�������� ��������� ��
				m_oMorphoContainerAT.clear();
			}
			else
			{
				//��������� ����
				SLayer oLayer;
				oLayer.oAgreementType.Assign(pObject->m_ObjectFeature.m_AgreementType);
				oLayer.iNumber = iCountApplyedExpertAT;
				m_vATLayers.push_back(oLayer);
				//������� ������ ���������� � �������� ��������� ��
				RemoveMorphoButAT();
			}
		}
		
		//�������������
		if (m_useVersion)
		{
			m_isHead = m_pVersionElement->m_isHead;
			m_iIdGroup = m_pVersionElement->m_iIdGroup;
		}
		
		//������������ ��� �� ������������� �������� ���������� ������
		for (std::list<BoardElements::BoardElementsIterator>::iterator ii = m_childUniformMembers.begin(); ii != m_childUniformMembers.end(); ++ii)
		{ (**ii)->ApplyConstruction(pObject, parentIndex, ownIndex, iIdGroup, iCountApplyedExpertAT, pElemBaseSemantic); }
	}
	SS_CATCH((wchar_t*)m_pUnit->GetWord())
}

void CBoardElement::SetFeatureToUnit()
{
	SS_TRY
	{
		if (m_useVersion)
		{
			//���������
			m_pUnit->CreateSyntaxFeature()->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.Assign( 
						    			m_pVersionElement->m_syntaxFeatureAposteriori.m_SyntaxCategories );
			//���������
			m_pVersionElement->m_oSemanticService.UpdateBlackBox();
		}
		else
		{
			//���������
			m_pUnit->CreateSyntaxFeature()->SetSyntaxCategory(m_syntaxFeatureAposteriori.m_SyntaxCategories.GetValue());
			//���������
			m_oSemanticService.UpdateBlackBox();
		}
	}
	SS_CATCH(L"")
}

PMORPHO CBoardElement::GetFirstMorphoDynamic()
{
	return m_oMorphoContainer.GetFirst();
}

PMORPHO CBoardElement::GetNextMorphoDynamic()
{
	return m_oMorphoContainer.GetNext();
}

///���������� ��������� �� ��������� ����� ���������� ������� � ���������� ����������
PMORPHO CBoardElement::GetNextMorphoForAddress(PMORPHO pMorpho)
{
	return m_oMorphoContainer.GetNextForAddress(pMorpho);
}

void CBoardElement::SetWord(const std::wstring & wsWord)
{
	SS_TRY
	{
		m_word.erase(m_word.begin(), m_word.end());
		int iLen = (int)wsWord.size();
		for (int i = 0; i < iLen; i++)
		{
			if (L'A' <= wsWord[i] && wsWord[i] <= L'Z')
			{ 
				m_word.push_back(wsWord[i] - L'A' + L'a');
				continue;
			}
			if (L'�' <= wsWord[i] && wsWord[i] <= L'�') 
			{
				m_word.push_back(wsWord[i] - L'�' + L'�');				
				continue;
			}
			m_word.push_back(wsWord[i]);	
		}
	}
	SS_CATCH(L"")
}

SS::Core::Features::CSemanticFeature& CBoardElement::GetSemanticFeature()
{
	if (m_useVersion)
	{ return m_pVersionElement->m_oSemanticService.GetSemanticFeature(); }
	return m_oSemanticService.GetSemanticFeature();
}

///����� ���� �������� ��������
void CBoardElement::Reset()
{
	SS_TRY
		
		m_syntaxFeatureAposteriori.Undefine();
		m_syntaxFeatureAposteriori.m_IdParent = m_uiDefPosition;
		
		m_oMorphoContainerAT.clear();
		m_iIdGroup = -1;
		m_childUniformMembers.clear();
		m_vATLayers.clear();
		
		m_isHeadDynamic = true;
		m_isHead = true;
		m_beatsBlocks = false;
		m_useVersion = false;

	SS_CATCH(L"")
}

///������� ��� ���������� ����� ��� ������� � �������� (������������ ������ ����� ����� �������)
void CBoardElement::RemoveUselessMorpho()
{
	SS_TRY
	{
		if (!m_useVersion)
		{ return; }

		 if (m_pVersionElement->m_pMorpho==NULL) return;
		
		//����� ���� ���������� � ���������� �������
		SS::Core::Features::Types::PartOfSpeechTypes oPartOfSpeechResult = m_pVersionElement->m_pMorpho->GetPOST();

		//����
		/*if (m_word == L"born") 
		{
			wchar_t Buff[30];
			MultiByteToWideChar(0, 0, oPartOfSpeechResult.ToString().c_str(), 30, Buff, 30);
			SAVE_LOG(L"������ ����� ����: " AND Buff);
		}*/
		//����
		
		if ( oPartOfSpeechResult.Equal(SS::Core::Features::Values::PartOfSpeechTypes.postNoun) ) 
		{ 
			oPartOfSpeechResult.AssignOR(&SS::Core::Features::Values::PartOfSpeechTypes.postPronoun); 
		}
		else if ( oPartOfSpeechResult.Equal(SS::Core::Features::Values::PartOfSpeechTypes.postPronoun) ) 
		{
			oPartOfSpeechResult.AssignOR(&SS::Core::Features::Values::PartOfSpeechTypes.postNoun);
		}
			
		//�������������� ����������
		m_oMorphoFormsFilter.RestoreMorphoContainer(m_oMorphoContainer);
	
		//�������� ������ ���������� � ����������� �� �����
		if (m_eLang == SS::Core::Types::ealRussian)
		{
			//�������� ����� ���� � ������
			for (PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho; pMorpho = m_oMorphoContainer.GetNext())
			{
				if ( (pMorpho->GetPOST().IsIntersectsWith(&oPartOfSpeechResult)) && 
					 (pMorpho->GetMorphoFeature().m_VoiceType.IsIntersectsWith(&m_pVersionElement->m_pMorpho->GetMorphoFeature().m_VoiceType)) )
				{ 
					continue;
				}
				else
				{
					pMorpho->ReleaseFeature();
					m_oMorphoContainer.DeleteCurrent();
				}
			}	
		}
		else
		{
			//�������� ����� ����
			for (PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho; pMorpho = m_oMorphoContainer.GetNext())
			{
				if ( !pMorpho->GetPOST().IsIntersectsWith(&oPartOfSpeechResult) )
				{ 
					pMorpho->ReleaseFeature();
					m_oMorphoContainer.DeleteCurrent();
				}
			}	
		}
	
		//�������� ������ �������� IIndex
		SS::Dictionary::Types::TDictionaryIndex oIndexVal;
		IIndex* pIndex = m_pUnit->GetFirstIndex();
		while (pIndex)
		{
			if ( (pIndex->GetDictionaryIndex()->GetFirst(&oIndexVal)) && 
				 (oIndexVal.GetIndexType() == eitMorphoIndex) && (!pIndex->GetFirstFeature()) ) 
			{ 
				//����
				/*if (m_word == L"born") 
				{
					wchar_t Buff[30];
					_itow(oIndexVal.GetDictionaryIndexWithoutFlags() ,Buff, 10);
					SAVE_LOG(L"��������� ������: " AND Buff);
				}*/
				//����
				
				pIndex = pIndex->ReleaseIndex();
				continue;
			}
			pIndex = m_pUnit->GetNextIndex();
		}

		//////////////////////�������� ���///////////////////////////////
		//pIndex = m_pUnit->GetFirstIndex();
		//while (pIndex)
		//{
		//	for (PMORPHO pMorpho = m_oMorphoContainer.GetFirst(); pMorpho; pMorpho = m_oMorphoContainer.GetNext())
		//	{
		//		if (pIndex == pMorpho->GetIndex()) 
		//		{
		//			//������� ����
		//			std::string s = pMorpho->GetMorphoFeature().m_CommonType.ToString();
		//			char t = 0;
		//		}
		//	}
		//	for (IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
		//	{
		//		unsigned int iMorphoIndex = pFeature->GetMorphoIndex();
		//		unsigned int iMorphoInfo = pFeature->GetMorphoInfo();
		//		unsigned int iPartOfSpeech = pFeature->GetPartOfSpeech();
		//		int iii = 0;
		//	}
		//	//�������
		//	for (bool b = pIndex->GetDictionaryIndex()->GetFirst(&oIndexVal); b; b = pIndex->GetDictionaryIndex()->GetNext(&oIndexVal))
		//	{
		//		if (oIndexVal.GetIndexType() == eitMorphoIndex) 
		//		{
		//			int ii = 0;
		//		}
		//		unsigned int iValue = oIndexVal.GetDictionaryIndexWithoutFlags();
		//		int iiii = 0;
		//	}
		//	pIndex = m_pUnit->GetNextIndex();
		//}
		////////////////////����� ��������� ����///////////////////////////
	}
	SS_CATCH(L"")
}

///����������� ���������� (��� �������� �����)
void CBoardElement::DivisionMorpho()
{
	SS_TRY
	{
		const unsigned __int8 RightCount = 1;
		unsigned __int8 iCount = 0;
		bool IsAccusative, IsCommon, IsDative, IsGenitive, IsInstrumental, IsLocative, IsNominative;
		unsigned int iSize = m_oMorphoContainer.Size();
		
		CMorphoFeature*	pMorphoFeature;
		IFeature*		pFeature = NULL;
		IIndex*			pIndex = NULL;
		PMORPHO			pMorphoNew = NULL;
		PMORPHO pMorpho = m_oMorphoContainer.GetFirst();
		for (unsigned int i = 0; i < iSize; ++i)
		{
			//��������������� ���� �� �������� �������������
			pMorphoFeature = &(pMorpho->GetMorphoFeature());

			IsAccusative = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctAccusative);
			iCount += IsAccusative;
			IsCommon = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctCommon);
			iCount += IsCommon;
			IsDative = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctDative);
			iCount += IsDative;
			IsGenitive = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctGenitive);
			iCount += IsGenitive;
			IsInstrumental = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctInstrumental);
			iCount += IsInstrumental;
			IsLocative = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctLocative);
			iCount += IsLocative;
			IsNominative = pMorphoFeature->m_CaseType.IsIntersectsWith(&SS::Core::Features::Values::CaseType.ctNominative);
			iCount += IsNominative;

			//���� ������ ��������� ������� �����������
			if (iCount > RightCount)
			{ 
				//��������� ��������������� ����
				for (unsigned int j = 0; j < iCount; ++j)
				{
					if ( j != (iCount-1) ) 
					{
						pMorphoNew = m_oMorphoContainer.Add();
						if (pMorphoNew) 
						{
							pFeature = m_pBlackBoxTextStorage->CreateFeature();
							pIndex = pMorpho->GetIndex();
							pIndex->AddFeature(pFeature);
							pMorphoNew->Init(m_pAMConverterMorpho, pFeature, pIndex); 
						}
						else
						{ 
							SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"���������� ������� ���������� ������������������." AND m_word.c_str()); 
							return;
						}
					}
					else
					{ pMorphoNew = pMorpho; }
				
					//��������
					if (IsAccusative)
					{
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctAccusative);
						IsAccusative = false;
					}
					else if (IsCommon) 
					{	
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctCommon);
                        IsCommon = false;
					}
					else if (IsDative) 
					{
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctDative);
						IsDative = false;
					}
					else if (IsGenitive) 
					{					
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctGenitive);
						IsGenitive = false;
					}
					else if (IsInstrumental) 
					{	
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctInstrumental);
						IsInstrumental = false;
					}
					else if (IsLocative) 
					{
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctLocative);
						IsLocative = false;
					}
					else if (IsNominative)
					{
						pMorphoFeature->m_CaseType.Assign(SS::Core::Features::Values::CaseType.ctNominative);
						IsNominative = false;
					}
					//���������� ��� ������ �������������
					pMorphoNew->SetMorphoFeature(pMorphoFeature);
				}
			}
			//��������� ��������
			iCount = 0;			
			//��������� ���������
			pMorpho = m_oMorphoContainer.GetNext();
		}
	}
	SS_CATCH(L"")
}

///���������� �����-���� ����������� �� AgrimentType-�
void CBoardElement::AddMorphoAT(CMorphoListElement* pMorpho)
{
	//�������� ���������� ���� �� ��� ��� ���
	std::list<PMORPHO>::iterator it;
	it = find(m_oMorphoContainerAT.begin(), m_oMorphoContainerAT.end(), pMorpho);
	if (it == m_oMorphoContainerAT.end())
	{ m_oMorphoContainerAT.push_back(pMorpho); }
}

///������� ���������� �� ����������� �� ��
void CBoardElement::RemoveMorphoButAT()
{
	if (m_useVersion || m_oMorphoContainerAT.empty()) return;
	std::list<PMORPHO>::iterator it;
	for (PMORPHO pM = m_oMorphoContainer.GetFirst(); pM; pM = m_oMorphoContainer.GetNext())
	{
		it = find(m_oMorphoContainerAT.begin(), m_oMorphoContainerAT.end(), pM);
		if (it == m_oMorphoContainerAT.end())
		{ 
			pM->ReleaseFeature();
			m_oMorphoContainer.DeleteCurrent(); 
		}
	}
	//�������� ���������
	m_oMorphoContainerAT.clear();
}

///���� �� �� �� ������� ������
bool CBoardElement::IsAT(unsigned int iNumber) const
{
	for (std::vector<SLayer>::const_iterator it = m_vATLayers.begin(); it != m_vATLayers.end(); ++it)
	{ 
		if (it->iNumber == iNumber) 
		{ return true; }
	}
	return false;
}

///�������� �� �� ������ ����������� �����������
SS::Core::Features::Types::AgreementType CBoardElement::GetAT(unsigned int iNumber) const
{
	for (std::vector<SLayer>::const_iterator it = m_vATLayers.begin(); it != m_vATLayers.end(); ++it)
	{ 
		if (it->iNumber == iNumber) 
		{ return it->oAgreementType; }
	}
	SS::Core::Features::Types::AgreementType oAT;
	oAT.Undefine();
	return oAT;
}

///��������� ������������� ���� � IText
void CBoardElement::RemoveUselessSemantic()
{
	SS_TRY
	{
		IDictionaryIndex* pDictionaryIndex = NULL;
		SS::Dictionary::Types::TDictionaryIndex	oIndexVal;
		SS::Core::Features::CSemanticFeature		oSemanticFeature;
		//�� Generic �� ����������
		GetSemanticFeature().m_SGeneric.Undefine();
		if (GetSemanticFeature().IsUndefined())
		{ return; }
	
		//������� ��������
		IIndex* pIndex = m_pUnit->GetFirstIndex();
		while (pIndex)
		{
			//��������� IDictionaryIndex
			if ( !(pDictionaryIndex = pIndex->GetDictionaryIndex()) )
			{ SS_THROW(L"����������� IDictionaryIndex."); }

			//��������� TDictionaryIndex
			if (!pDictionaryIndex->GetFirst(&oIndexVal))
			{ continue; }

			//�������� ��� �������������
			if (oIndexVal.GetIndexType() == eitSemanticIndex) 
			{
				oSemanticFeature.Undefine();
				m_pAMConverterSemantic->EnCode(oIndexVal, &(oSemanticFeature));
				//�� Generic �� ����������
				oSemanticFeature.m_SGeneric.Undefine();			
				
				//���� �� ������������ � ����� �� �������
				if ( !oSemanticFeature.IsIntersectsWith(&GetSemanticFeature()) ) 
				{
					pIndex = pIndex->ReleaseIndex();
					continue;
				}
			}
			pIndex = m_pUnit->GetNextIndex();		
		}	
	}
	SS_CATCH(L"")
}


}
}
}






















