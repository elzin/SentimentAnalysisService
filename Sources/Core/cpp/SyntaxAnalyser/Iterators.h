//Iterators.h
#pragma once
#include ".\BoardElement.h"
#include "FeatureController.h"
#include "UnitSearchPolicys.h"

namespace SS
{
namespace Syntax
{
namespace ModifiedConstruction
{
	using namespace SS::Syntax::BoardElements;
	using namespace SS::Syntax::Policys;
	
	///��������� �����-�������� ��� ������ ���������� ��������
	template<typename TRange, typename TBreak, typename TCheck>
	class CObjectIterator
	{
	private:
		///������ ���������
		TRange oRange;
		///������ ���������
		TBreak oBreak;
		///������ ��������
		TCheck oCheck;

	protected:
		///����������� �� ���������
		CObjectIterator(){};
		///����������� ��� HeadAndCurrentGroupChildren
		CObjectIterator(unsigned int IdGroup) : oCheck(IdGroup){};
		///����������� ��� Child
		CObjectIterator(BoardElementsIterator & itBeginBoard) : oCheck(itBeginBoard){};
	
	protected:
		///���������� IdParent
		void SetIdParent(unsigned int IdParent)
		{
			oCheck.SetIdParent(IdParent);
		}
		///������������� ���������
		void InitRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt)
		{
			oRange.Init(pFirstIt, pLastIt);
		}
		///������ �������
		CBoardElement* First() const
		{
			for (CBoardElement* pElem = oRange.First(); pElem; pElem = oRange.Next())
			{
				if (oBreak.Break(pElem))
				{ return NULL; }
				if (oCheck.Check(pElem))
				{ return pElem; }
			}
			return NULL;
		}
		///��������� �������
		CBoardElement* Next() const
		{
			CBoardElement* pElem;
			while (pElem = oRange.Next())
			{
				if (oBreak.Break(pElem))
				{ return NULL; }
				if (oCheck.Check(pElem))
				{ return pElem; }
			}
			return NULL;
		}
	};
		
	///��������� ��� ��� "���������� �����������"
	class IObjectAnalyser
	{
	public:
		///����������
		virtual ~IObjectAnalyser(){};
		///��������� ������ ��������
		virtual bool Run() = 0;
		///���������� ���������� ������������
		virtual void SetFeatureController(IFeatureController* pFeatureController) = 0;
		///�������� ����������� �������
		virtual CBoardElement* GetWorkedElement() = 0;
		///������� ������ �����������
		virtual CConstructionObject* GetConstructionObject() = 0;
		///������������� ���������
		virtual void InitRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt) = 0;
		///������������� ����� ���������
		virtual void InitAllRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt) = 0;
		///���������� IdParent
		virtual void SetIdParent(unsigned int IdParent) = 0;
		///�������� ������ ��
		virtual void AddATObject(IBaseAT* pAT, IObjectAnalyser* pObject) = 0;
	};
	
	///��������� ����� �������� ������� ��� ������ ������� �����������
	template<typename TRange, typename TBreak, typename TCheck, typename TContinuance, bool Existence, bool Obligation>
	class CObjectAnalyser : public IObjectAnalyser, private CObjectIterator<TRange, TBreak, TCheck>
	{
	private:
		///��������� ���������� �� � ������ ������� � ������� ����������
		struct SATObject
		{
			///��������� ������� ��
			IBaseAT* pBaseAT;
			///������ �������
			IObjectAnalyser* pObjectAnalyser;
			///�����������
			SATObject() : pObjectAnalyser(NULL), pBaseAT(NULL){};
		};

	private:
		///������� �������� �������
		bool m_AnswerMatrix[2][2][2];
		///���������� ������������ �� ���������� ��������� � ����������
		IFeatureController* m_pFeatureController;
		///������������ �� ���������� ��������� � ����������
		bool m_Appropriate;
		///����������� �������
		CBoardElement* m_pBoardElement;
		///��������� �������� ������� � �������� ��������� �� ��
		std::vector<SATObject> m_vATObjectCollection;

	private:
		///���������� �������
		void FillData()
		{
			m_AnswerMatrix[0][0][0] = true;  m_AnswerMatrix[0][0][1] = true; m_AnswerMatrix[0][1][0] = true;
			m_AnswerMatrix[0][1][1] = false; m_AnswerMatrix[1][0][0] = true; m_AnswerMatrix[1][0][1] = false;
			m_AnswerMatrix[1][1][0] = true;  m_AnswerMatrix[1][1][1] = true;
			m_Appropriate = false;
			m_pFeatureController = NULL;
			m_pBoardElement = NULL;
		}
		///���������� �� ��
		bool IsAppropriateAT(CBoardElement* pElem)
		{
			//���� ��������� �� �����
			if (m_vATObjectCollection.empty()) 
			{ return true; }
			//������� �� ������
			CBoardElement* pElemBegin = NULL;

			pElem->GetMorphoContainerAT().clear();
			bool IsIntersect = false;
			for (std::vector<SATObject>::iterator it = m_vATObjectCollection.begin(); it != m_vATObjectCollection.end(); ++it)
			{
				//���� ����������� ������ �� �������� �����
				pElemBegin = it->pObjectAnalyser->GetWorkedElement();
				if (!pElemBegin)
				{ continue; }
				
				//���� ��������� ��� �� ����, ���������� �� ����� ������ ���������� ������� ��������
				if (pElemBegin->GetMorphoContainerAT().empty())
				{
					for ( PMORPHO pMorphoElemBegin = pElemBegin->GetFirstMorpho(); pMorphoElemBegin; 
						  pMorphoElemBegin = pElemBegin->GetNextMorpho() )
					{
						for ( PMORPHO pMorphoElem = pElem->GetFirstMorpho(); pMorphoElem;
							  pMorphoElem = pElem->GetNextMorpho() )
						{
							if ( it->pBaseAT->IsIntersect(pMorphoElemBegin->GetMorphoFeature(), pMorphoElem->GetMorphoFeature()) )
							{
								pElemBegin->AddMorphoAT(pMorphoElemBegin);
								pElem->AddMorphoAT(pMorphoElem);
								IsIntersect = true;
							}
						}	
					}	
				}
				else
				{
					std::list<PMORPHO>::iterator itMorphoElemBegin;
					for ( itMorphoElemBegin = pElemBegin->GetMorphoContainerAT().begin(); 
						  itMorphoElemBegin != pElemBegin->GetMorphoContainerAT().end(); 
						  ++itMorphoElemBegin )
					{
						for ( PMORPHO pMorphoElem = pElem->GetFirstMorpho(); pMorphoElem;
							  pMorphoElem = pElem->GetNextMorpho() )
						{
							if ( it->pBaseAT->IsIntersect((*itMorphoElemBegin)->GetMorphoFeature(), pMorphoElem->GetMorphoFeature()) )
							{
								pElem->AddMorphoAT(pMorphoElem);
								IsIntersect = true;
							}
						}	
					}
				}
				//���� �� ������� �� ��
				if (!IsIntersect)
				{ return false; }
			}
			return true;
		}

	public:
		///����������� �� ���������
		CObjectAnalyser() { FillData(); };
		///����������� ��� HeadAndCurrentGroupChildren
		CObjectAnalyser(unsigned int IdGroup) : CObjectIterator<TRange, TBreak, TCheck>(IdGroup) { FillData(); };
		///����������� ��� Child
		CObjectAnalyser(BoardElementsIterator & itBeginBoard) : CObjectIterator<TRange, TBreak, TCheck>(itBeginBoard) { FillData(); };
	
	public:		
		///������������� ���������
		void InitRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt)
		{
			CObjectIterator<TRange, TBreak, TCheck>::InitRange(pFirstIt, pLastIt);
		}
		///������������� ����� ��������� (����� �����)
		void InitAllRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt)
		{
			m_pFeatureController->InitRange(pFirstIt, pLastIt);
		}
		///��������� ������
		bool Run()
		{
			SS_TRY
			{
				m_Appropriate = false;
				//����� ����������� ��������
				CBoardElement* pElem;
				for (pElem = First(); pElem; pElem = Next())
				{
					m_Appropriate = (m_pFeatureController->IsAppropriate(pElem) && IsAppropriateAT(pElem));
					if (m_Appropriate)
					{ break; }
					if (!TContinuance::Continue(pElem))
					{ break; }
				}
				//���� ������� ��������
				if (m_AnswerMatrix[m_Appropriate][Existence][Obligation])
				{ 
					if (m_Appropriate && Existence)
					{ m_pBoardElement = pElem; }
					else
					{ m_pBoardElement = NULL; }
					return true; 
				}
				//���� �� ��������
				m_pBoardElement = NULL;
			}
			SS_CATCH(L"")
			return false;
		}
		///���������� ���������� ������������
		void SetFeatureController(IFeatureController* pFeatureController)
		{
			m_pFeatureController = pFeatureController;
		}
		///�������� ����������� �������
		CBoardElement* GetWorkedElement()
		{
			return m_pBoardElement;
		}
		///������� ������ �����������
		CConstructionObject* GetConstructionObject()
		{ 
			return  m_pFeatureController->GetConstructionObject();
		}
		///���������� IdParent
		void SetIdParent(unsigned int IdParent)
		{
			CObjectIterator<TRange, TBreak, TCheck>::SetIdParent(IdParent);
		}
		///�������� ������ ��
		void AddATObject(IBaseAT* pAT, IObjectAnalyser* pObject)
		{
			SATObject oATObject;
			oATObject.pBaseAT = pAT;
			oATObject.pObjectAnalyser = pObject;
			m_vATObjectCollection.push_back(oATObject);
		}
	};	

}
}
}