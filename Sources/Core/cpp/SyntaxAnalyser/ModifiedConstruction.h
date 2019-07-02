//ModifiedConstruction.h
#pragma once

#include "Iterators.h"

namespace SS
{
namespace Syntax
{
namespace ModifiedConstruction
{
	using namespace SS::Core::Features;
	
	///��������� ��� ���������������� �����������
	class IModifiedConstruction
	{
	public:
		///����������� ����������
		virtual ~IModifiedConstruction(){};
		///������������ ���������������� �����������
		virtual void Create( SS::SyntaxConstructions::Types::CConstructionEx & oConstruction,
							 SS::Interface::Core::Dictionary::IDictionary* pDictionary ) = 0;
		///��� ������������� ��������
		typedef std::vector<IObjectAnalyser*>::iterator iterator;
		///������ ������� �����������
		virtual iterator begin() = 0;
		///����������� ������� �����������
		virtual iterator end() = 0;
		///�������� ����������� � �� �����������
		virtual void ClearContainersAT() = 0;
		///�������� ��� ����������� � ��
		virtual bool IsAT() = 0;
	};
	
	///���������������� ����������� ���������� ��������� �����������
	class CModifiedConstruction : public IModifiedConstruction
	{
	private:
		///��������� ���������������� ��������
		std::vector<IObjectAnalyser*> m_oCollection;
		///��������� �������� �������� ������������
		std::vector<IFeatureController*> m_oControllerCollection;
		///������ ������� ������������ �����������
		BoardElementsIterator & m_itBeginBoard;
		///������������� ������
		int m_IdGroup;
		///���� ����������� ������ ���� NotObligatory
		bool m_MustNotObligatory;
		///��������������� ��������� ������� ��
		static CPolicyC		m_oPolicyC;
		static CPolicyGN	m_oPolicyGN;
		static CPolicyGNC	m_oPolicyGNC;
		static CPolicyGPN	m_oPolicyGPN;
		static CPolicyNP	m_oPolicyNP;
		static CPolicyN		m_oPolicyN;
		///���������� ����������� � ��
		bool m_isAT;
		///���� �����������
		ExpertModel::ESyntaxBase m_eBase;

	private:
		///������������ ����������������� ������� �����������
		void CreateModifiedObject(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///�������� ������-���������
		void CreateDetectModifiedObject(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///�������� ������� Same
		void CreateSameModifiedObject( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
									   SS::Interface::Core::Dictionary::IDictionary* pDictionary,
									   unsigned int iSameCount );
		///���������� ��� ���������
		template<typename TRange> 
			void SetBreakType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///���������� ��� �����������������
		template<typename TRange, typename TBreak>
			void SetContinuanceType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///���������� ��� �������������
		template<typename TRange, typename TBreak, typename TContinuance> 
			void SetExistenceType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///���������� ��� ��������������
		template<typename TRange, typename TBreak, typename TContinuance, bool Existence> 
			void SetObligationType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///���������� ��� ��������
		template<typename TRange, typename TBreak, typename TContinuance, bool Existence, bool Obligation>
			void SetCheckType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj);
		///������������ ������� �������� ������������
		void CreateControllerObject( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
									 SS::Interface::Core::Dictionary::IDictionary* pDictionary );
		///���������� ��� �������
		template<typename TForm>
			void SetPositionType( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
								  SS::Interface::Core::Dictionary::IDictionary* pDictionary );
		///�������� ���� ��������
		void Delete();
		///������������ ������
		void SetLinks();
		///���������� ������ ��� ��������� �� ��
		void SetDataAT(SS::SyntaxConstructions::Types::CConstructionEx & oConstruction);

	public:
		///�����������
		CModifiedConstruction(BoardElementsIterator & itBeginBoard, int IdGroup, ExpertModel::ESyntaxBase eBase) 
			: m_itBeginBoard(itBeginBoard),
			  m_IdGroup(IdGroup),
			  m_MustNotObligatory(false),
			  m_isAT(false),
			  m_eBase(eBase)
		{};
		///����������
		virtual ~CModifiedConstruction(){ Delete(); };
		///������������ ���������������� �����������
		void Create( SS::SyntaxConstructions::Types::CConstructionEx & oConstruction,
					 SS::Interface::Core::Dictionary::IDictionary* pDictionary );
		///������ ������� �����������
		iterator begin() { return m_oCollection.begin(); };
		///����������� ������� �����������
		iterator end() { return m_oCollection.end(); };
		///�������� ����������� � �� �����������
		void ClearContainersAT();
		///�������� ��� ����������� � ��
		bool IsAT() { return m_isAT; };
	};
	
	//========================================= Private =============================================//
	
	///���������� ��� ���������
	template<typename TRange>
	void CModifiedConstruction::SetBreakType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		if (pConObj->m_ObjectFeature.m_ScopeOfTheRule.Equal(Values::ScopeOfTheRule.scpCommaBoundary)) 
		{ 
			SetContinuanceType<TRange, CBreakPolicy>(pConObj);
		}
		else
		{ 
			SetContinuanceType<TRange, CNotBreakPolicy>(pConObj);
		}
	}
	
	///���������� ��� �����������������
	template<typename TRange, typename TBreak>
	void CModifiedConstruction::SetContinuanceType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		if ( pConObj->m_ObjectFeature.m_ObjectsOrder.Equal(Values::ObjectsOrder.ooContinuous) ) 
		{
			SetExistenceType<TRange, TBreak, CContinuousPolicy>(pConObj);
		}
		else if ( pConObj->m_ObjectFeature.m_ObjectsOrder.Equal(Values::ObjectsOrder.ooDiscontinuous) ) 
		{
			SetExistenceType<TRange, TBreak, CDiscontinuousPolicy>(pConObj);
		}
		else if ( pConObj->m_ObjectFeature.m_ObjectsOrder.Equal(Values::ObjectsOrder.ooContinuousNotNeverAdverb) ) 
		{
			SetExistenceType<TRange, TBreak, CContinuousNotNeverAdverbPolicy>(pConObj);
		}
		else
		{ SS_THROW(L"�� ���������� Continuance."); }
	}

	///���������� ��� �������������
	template<typename TRange, typename TBreak, typename TContinuance> 
	void CModifiedConstruction::SetExistenceType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		if ( pConObj->m_MorphoFeatureApriori.m_ExistenceMod.Equal(Values::ExistenceMod.excmExist) )
		{
			SetObligationType<TRange, TBreak, TContinuance, true>(pConObj);
		}
		else if ( pConObj->m_MorphoFeatureApriori.m_ExistenceMod.Equal(Values::ExistenceMod.excmAbsent) )
		{
			SetObligationType<TRange, TBreak, TContinuance, false>(pConObj);
		}
		else
		{ SS_THROW(L"�� ���������� ExistenceMod."); }
	}

	///���������� ��� ��������������
	template<typename TRange, typename TBreak, typename TContinuance, bool Existence> 
	void CModifiedConstruction::SetObligationType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		//�������������� ������ ��� SameType
		if (m_MustNotObligatory) 
		{
			SetCheckType<TRange, TBreak, TContinuance, Existence, false>(pConObj);
			return;
		}

		if ( pConObj->m_ObjectFeature.m_ObjectObligation.Equal(Values::ObjectObligation.ecoObligatory) )
		{ 
			SetCheckType<TRange, TBreak, TContinuance, Existence, true>(pConObj);
		}
		else if ( pConObj->m_ObjectFeature.m_ObjectObligation.Equal(Values::ObjectObligation.ecoNotObligatory) )
		{
			SetCheckType<TRange, TBreak, TContinuance, Existence, false>(pConObj);
		}
		else
		{ SS_THROW(L"�� ���������� Obligation."); }
	}

	///���������� ��� ��������
	template<typename TRange, typename TBreak, typename TContinuance, bool Existence, bool Obligation>
	void CModifiedConstruction::SetCheckType(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		//������ ���������������� �����������
		IObjectAnalyser* pObjectAnalyser = NULL;

		if ( pConObj->m_ObjectFeature.m_ChildrenAnalysisDepth.IsUndefined() ||
			 pConObj->m_ObjectFeature.m_ChildrenAnalysisDepth.Equal(Values::ChildrenAnalysisDepth.cadHeadsAndCurrentGroupChildren) )
		{ 
			pObjectAnalyser = new CObjectAnalyser< TRange, TBreak, CHeadAndCurrentGroupChildrenPolicy,
												   TContinuance, Existence, Obligation >(m_IdGroup);
		}
		else if ( pConObj->m_ObjectFeature.m_ChildrenAnalysisDepth.Equal(Values::ChildrenAnalysisDepth.cadChildren) )
		{
			pObjectAnalyser = new CObjectAnalyser< TRange, TBreak, CChildPolicy,
												   TContinuance, Existence, Obligation >(m_itBeginBoard);
		}
		else if ( pConObj->m_ObjectFeature.m_ChildrenAnalysisDepth.Equal(Values::ChildrenAnalysisDepth.cadHeadsOnly) )
		{
			pObjectAnalyser = new CObjectAnalyser< TRange, TBreak, COnlyHeadPolicy,
												   TContinuance, Existence, Obligation >;
		}
		else if ( pConObj->m_ObjectFeature.m_ChildrenAnalysisDepth.Equal(Values::ChildrenAnalysisDepth.cadFull) )
		{
			pObjectAnalyser = new CObjectAnalyser< TRange, TBreak, CFullPolicy,
												   TContinuance, Existence, Obligation >;
		}
		//��������� � ���������
		m_oCollection.push_back(pObjectAnalyser);
	}

	///������������ ����������������� ������� �����������
	inline void CModifiedConstruction::CreateModifiedObject(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		SS_TRY
		{
			if ( pConObj->m_ObjectFeature.m_PositionToDetectedObject.Equal(Values::PositionToDetectedObject.ptdoRight) ||
				 pConObj->m_ObjectFeature.m_PositionToDetectedObject.IsUndefined() )
			{ 
				SetBreakType<CRightPolicy>(pConObj);
			}
			else if ( pConObj->m_ObjectFeature.m_PositionToDetectedObject.Equal(Values::PositionToDetectedObject.ptdoLeft) )
			{
				SetBreakType<CLeftPolicy>(pConObj);
			}
			else
			{ SS_THROW(L"�� ������ PositionToDetectedObject."); }
		}
		SS_CATCH(L"")
	}
	
	///���������� ��� �������
	template<typename TForm>
	void CModifiedConstruction::SetPositionType( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
												 SS::Interface::Core::Dictionary::IDictionary* pDictionary )
	{
		IFeatureController* pFeatureController = NULL;
		if ( pConObj->m_ObjectFeature.m_PositionInBlock.Equal(Values::PositionInBlock.pibBegin) )
		{
			pFeatureController = new CFeatureController<TForm, CBeginPositionPolicy>(pConObj, pDictionary, m_eBase);
		}
		else if ( pConObj->m_ObjectFeature.m_PositionInBlock.Equal(Values::PositionInBlock.pibEnd) )
		{
			pFeatureController = new CFeatureController<TForm, CEndPositionPolicy>(pConObj, pDictionary, m_eBase);
		}
		else if ( pConObj->m_ObjectFeature.m_PositionInBlock.Equal(Values::PositionInBlock.pibMiddle) )
		{
			pFeatureController = new CFeatureController<TForm, CMiddlePositionPolicy>(pConObj, pDictionary, m_eBase);
		}
		else
		{
			pFeatureController = new CFeatureController<TForm, CUndefinedPositionPolicy>(pConObj, pDictionary, m_eBase);
		}
		m_oControllerCollection.push_back(pFeatureController);
	}
	
	///������������ ������� �������� ������������
	inline void CModifiedConstruction::CreateControllerObject( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
															   SS::Interface::Core::Dictionary::IDictionary* pDictionary )
	{
		SS_TRY
		{
			if ( pConObj->m_MorphoFeatureApriori.m_DetectWordAnalyzeMode.Equal(Values::TDetectWordAnalyzeMode.mfamAllForms) )
			{
				SetPositionType<CAllFormsPolicy>(pConObj, pDictionary);
			}
			else if ( pConObj->m_MorphoFeatureApriori.m_DetectWordAnalyzeMode.Equal(Values::TDetectWordAnalyzeMode.mfamLetForm) )
			{
				SetPositionType<CLetFormPolicy>(pConObj, pDictionary);
			}
			else
			{
				SetPositionType<CUndefinedFormPolicy>(pConObj, pDictionary);
			}
		}
		SS_CATCH(L"")
	}
	
	///�������� ������-���������
	inline void CModifiedConstruction::CreateDetectModifiedObject(SS::SyntaxConstructions::Types::CConstructionObject* pConObj)
	{
		SS_TRY
		{
			IObjectAnalyser* pObjectAnalyser = NULL;
			if (pConObj->m_ObjectFeature.m_ScopeOfTheRule.Equal(Values::ScopeOfTheRule.scpCommaBoundary)) 
			{ 
				pObjectAnalyser = new CObjectAnalyser< CRightPolicy, CBreakPolicy, CHeadAndCurrentGroupChildrenPolicy,
													   CDiscontinuousPolicy, true, true >(m_IdGroup);
			}
			else
			{ 
				pObjectAnalyser = new CObjectAnalyser< CRightPolicy, CNotBreakPolicy, CHeadAndCurrentGroupChildrenPolicy,
													   CDiscontinuousPolicy, true, true >(m_IdGroup);
			}
			//��������� � ���������
			m_oCollection.push_back(pObjectAnalyser);
		}
		SS_CATCH(L"")
	}

	///�������� ������� Same
	inline void CModifiedConstruction::CreateSameModifiedObject( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
																 SS::Interface::Core::Dictionary::IDictionary* pDictionary,
																 unsigned int iSameCount)
	{
		SS_TRY
		{
			m_MustNotObligatory = false;
			if ( pConObj->m_ObjectFeature.m_ObjectObligation.Equal(Values::ObjectObligation.ecoObligatory) )
			{ 
				CreateControllerObject(pConObj, pDictionary);
				CreateModifiedObject(pConObj);
				--iSameCount;
				m_MustNotObligatory = true;
			}
			for (unsigned int i = 0; i < iSameCount; ++i)
			{
				CreateControllerObject(pConObj, pDictionary);
				CreateModifiedObject(pConObj);
			}
			m_MustNotObligatory = false;
		}
		SS_CATCH(L"")
	}
	
	///������������ ������
	inline void CModifiedConstruction::SetLinks()
	{
		SS_TRY
		{
			if (m_oCollection.size() != m_oControllerCollection.size())
			{ SS_THROW(L"�������������� ��� ������������ ������."); }
			if (m_oCollection.empty()) 
			{ SS_THROW(L"������ �����������."); }

			std::vector<IObjectAnalyser*>::iterator itAnalyser(m_oCollection.begin());
			std::vector<IFeatureController*>::iterator itController(m_oControllerCollection.begin());
			for (itAnalyser; itAnalyser != m_oCollection.end(); ++itAnalyser, ++itController)
			{ (*itAnalyser)->SetFeatureController(*itController); }
		}
		SS_CATCH(L"")
	}

	///�������� ���������������� �����������
	inline void CModifiedConstruction::Delete()
	{
		SS_TRY
		{
			//�������� ���������������� ��������
			std::vector<IObjectAnalyser*>::iterator it(m_oCollection.begin());
			for (it; it != m_oCollection.end(); ++it)
			{ delete (*it);	}
			//�������� �������� �������� ������������
			std::vector<IFeatureController*>::iterator itr(m_oControllerCollection.begin());
			for (itr; itr != m_oControllerCollection.end(); ++itr)
			{ delete (*itr); }
			//������ �������
			m_oCollection.clear();
			m_oControllerCollection.clear();
		}
		SS_CATCH(L"");
	}

	///���������� ������ ��� ��������� �� ��
	inline void CModifiedConstruction::SetDataAT(SS::SyntaxConstructions::Types::CConstructionEx & oConstruction)
	{
		SS_TRY
		{
			//��������� �������� � ���������� ��
			std::vector<IObjectAnalyser*> vAgreementCollection;
			//��� ��
			SS::Core::Features::Types::AgreementType oAT;
			//���������� �������� ��
			const unsigned int CountValueAT = SS::Core::Features::Values::AgreementType.GetValueCount();
			//������� �� ��
			for (unsigned int iAT = 0; iAT < CountValueAT; ++iAT)
			{
				//������� ����������
				vAgreementCollection.clear();
				//���������� ��
				oAT.SetSingleValue(iAT);
				if (oAT.IsUndefined()) { continue; }
				//���������� �� ���������
				for (CModifiedConstruction::iterator itObj = m_oCollection.begin(); itObj != m_oCollection.end(); ++itObj)
				{
					if ( (*itObj)->GetConstructionObject()->m_ObjectFeature.m_AgreementType.IsIntersectsWith(&oAT) )
					{ vAgreementCollection.push_back(*itObj); }
				}
				//�������� (���� �� ������� �� ��� ���������)
				if (vAgreementCollection.empty())
				{
					continue;
				}
				//�������� (����� ��������� � �� ���� ������ ������)
				if (vAgreementCollection.size() == 1)
				{
					SAVE_LOG( SS_WARNING AND __WFUNCTION__ AND (wchar_t*)oConstruction.GetName().c_str() AND
							  L"����������� �������� ���� !! ������� � AgreementType." );
					vAgreementCollection.clear();
					continue;
				}
				//��������� ��� ����������� �������� ��
				m_isAT = true;
				//������������� ����������� ��������
				CModifiedConstruction::iterator itAgObjBegin(vAgreementCollection.begin());
				CModifiedConstruction::iterator itAgObj = itAgObjBegin + 1;
				for (itAgObj; itAgObj != vAgreementCollection.end(); ++itAgObj)
				{
					if ( oAT.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atC) )
					{ 
						(*itAgObj)->AddATObject(&m_oPolicyC, (*itAgObjBegin)); 
					}
					else if ( oAT.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atGN) )
					{ 
						(*itAgObj)->AddATObject(&m_oPolicyGN, (*itAgObjBegin)); 
					}
					else if ( oAT.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atGNC) )
					{ 
						(*itAgObj)->AddATObject(&m_oPolicyGNC, (*itAgObjBegin)); 
					}
					else if ( oAT.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atGPN) )
					{ 
						(*itAgObj)->AddATObject(&m_oPolicyGPN, (*itAgObjBegin));
					}
					else if ( oAT.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atNP) )
					{ 
						(*itAgObj)->AddATObject(&m_oPolicyNP, (*itAgObjBegin));
					}
					else if ( oAT.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atN) )
					{ 
						(*itAgObj)->AddATObject(&m_oPolicyN, (*itAgObjBegin));
					}
					else
					{ SS_THROW(L"���������������� AgreementType."); }
				}
			}
		}
		SS_CATCH(L"")
	}
	
	//================================================ Public =============================================//

	///������������ ���������������� �����������
	inline void CModifiedConstruction::Create( SS::SyntaxConstructions::Types::CConstructionEx & oConstruction,
											   SS::Interface::Core::Dictionary::IDictionary* pDictionary )
	{
		SS_TRY
		{
			//������� �����������
			Delete();
			//�������� �� �����������
			if (oConstruction.GetObjectCount() == 0) 
			{ SS_THROW(L"������ ����������� �� ����."); }
			//�������� ������-��������
			SS::SyntaxConstructions::Types::CConstruction::iterator itConObj(oConstruction.begin());
			CreateControllerObject((*itConObj), pDictionary);
			CreateDetectModifiedObject(*itConObj);
			++itConObj;
			//������� �����������
			for (itConObj; itConObj != oConstruction.end(); ++itConObj)
			{ 
				unsigned int iSameCount = (*itConObj)->m_ObjectFeature.m_SameTypeObjectsNumber.GetValue();
				//��� �������, ������������ ������
				if (iSameCount == 0) { iSameCount = 1; }
				//��� Obligatory
				if (iSameCount > 1)
				{
					CreateSameModifiedObject(*itConObj, pDictionary, iSameCount);
				}
				else
				{
					CreateControllerObject((*itConObj), pDictionary);
					CreateModifiedObject(*itConObj);
				}
			}
			//���������� �����
			SetLinks();
			//���������� ������ ��� ��������� �� ��
			SetDataAT(oConstruction);
		}
		SS_CATCH(L"")
	}
	
	///�������� ����������� � �� �����������
	inline void CModifiedConstruction::ClearContainersAT()
	{
		if (m_isAT)
		{
			CBoardElement* pElem = NULL;
			for (CModifiedConstruction::iterator it = m_oCollection.begin(); it != m_oCollection.end(); ++it)
			{
				pElem = (*it)->GetWorkedElement();
				if (!pElem) { continue;	}
				pElem->GetMorphoContainerAT().clear();
			}		
		}
	}
	
}
}
}