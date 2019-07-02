//UnitSearchPolicys.h
#pragma once
#include ".\BoardElement.h"

namespace SS
{
namespace Syntax
{
namespace Policys
{
	using namespace SS::Syntax::BoardElements;
	///������� ����� ��� ��������� ������ � �����
	class CBaseSide
	{
	protected:
		///������ ������� ���������
		BoardElementsIterator* m_pFirstIt;
		///������� �� ���������
		BoardElementsIterator* m_pLastIt;
		///������� �������
		mutable BoardElementsIterator m_itCurrent;
		///��������� ��� ������������� ����������
		mutable BoardCollection m_NullCollection;

		mutable bool isNull;

	protected:
		///�����������
		CBaseSide() : m_pFirstIt(NULL), m_pLastIt(NULL)
		{
			//m_itCurrent = m_NullCollection.end();
			isNull = true;
		}

	public:
		///������������� ���������
		void Init(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt)
		{
			m_pFirstIt = pFirstIt;
			m_pLastIt = pLastIt;
			//isNull = true;
		}
	};
	
	//*************************************��������� �������� ���������****************************************//
	
	///�����-��������� ������ ��������� ����� �������
	class CRightPolicy : public CBaseSide
	{
	public:
		///���������� ������ ������� ���������
		CBoardElement* First() const
		{			
			CBoardElement* pReturn = NULL;
			if ( (*m_pFirstIt) == (*m_pLastIt) )
			{ return NULL; }
			try
			{
				m_itCurrent = (*m_pFirstIt);
				pReturn = (*m_itCurrent);
				isNull = false;
			}
			catch (...)
			{
				SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�� ��������� ������������� ���������.");
				return NULL;
			}			
			return pReturn;
		}
		///���������� ��������� ������� ���������
		CBoardElement* Next() const
		{
			if (/*m_itCurrent == m_NullCollection.end()*/isNull) 
			{
				SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�� ������ first()."); 
				return NULL;
			}
			if (++m_itCurrent == (*m_pLastIt))
			{ 
				//m_itCurrent = m_NullCollection.end();	
				isNull=true;
				return NULL;
			}
			return (*m_itCurrent);
		}
	};

	///�����-��������� ������ ��������� ������ ������
	class CLeftPolicy : public CBaseSide
	{
	public:
		///���������� ������ ������� ���������
		CBoardElement* First() const
		{
			CBoardElement* pReturn = NULL;
			try
			{
				m_itCurrent = (*m_pLastIt);
				pReturn = (*m_itCurrent);
				isNull = false;
			}
			catch (...)
			{
				SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�� ��������� ������������� ���������."); 
				return NULL;
			}
			if ( (*m_pFirstIt) == (*m_pLastIt) )
			{ return NULL; }
			--m_itCurrent;
			pReturn = (*m_itCurrent);
			return pReturn;
		}
		///���������� ��������� ������� ���������
		CBoardElement* Next() const
		{
			if (isNull) 
			{
				SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�� ������ first()."); 
				return NULL;
			}	
			if (m_itCurrent == (*m_pFirstIt))
			{
				//m_itCurrent = m_NullCollection.end();	
				isNull = true;
				return NULL;
			}
			--m_itCurrent;
			return (*m_itCurrent);
		}
	};

	//*************************************��������� ���������� ������*****************************************//
	
	///�����-��������� ���� ����� �������� ����� ��������
	class CBreakPolicy
	{
	private:
		///�������
		std::wstring m_sComma;

	public:
		///�����������
		CBreakPolicy() : m_sComma(L","){};
		///�������� �� ����������
		bool Break(CBoardElement* pElem) const
		{
			if ( pElem->GetWord() == m_sComma )
			{ return true; }
			return false;
		}
	};

	///�����-��������� ���� �� ����� ��������� ����� ��������
	class CNotBreakPolicy
	{
	public:
		///�������� �� ����������
		bool Break(CBoardElement* pElem) const
		{
			return false;
		}
	};

	//*************************************��������� �������� ���������*******************************************//
	
	///�����-��������� �� ������� ������ �������� ���������
	class COnlyHeadPolicy
	{
	public:
		///��� ��������� Child (������ �����)
		void SetIdParent(unsigned int IdParent){};
		///��������� �������
		bool Check(CBoardElement* pElem) const
		{
			if ( pElem->IsHead() ) 
			{ return true; }
			return false;
		}
	};

	///�����-��������� �� ������� ����� ���������
	class CFullPolicy
	{
	public:
		///��� ��������� Child (������ �����)
		void SetIdParent(unsigned int IdParent){};
		///��������� �������
		bool Check(CBoardElement* pElem) const
		{
			return true;
		}
	};

	///�����-��������� �� ������� �������� ��� �������� ������� �������
	class CHeadAndCurrentGroupChildrenPolicy
	{
	private:
		///������������� ������
		unsigned int m_IdGroup;

	public:
		///�����������
		CHeadAndCurrentGroupChildrenPolicy(unsigned int IdGroup) : m_IdGroup(IdGroup){};
		///��� ��������� Child (������ �����)
		void SetIdParent(unsigned int IdParent){};
		///��������� �������
		bool Check(CBoardElement* pElem) const
		{
			if ( (pElem->IsHead() || pElem->GetGroup() == m_IdGroup) && (!pElem->IsUnusedForm()) )
			{ return true; }
			return false;
		}
	};

	///�����-��������� �� ������� child-��������� ���������� ������������
	class CChildPolicy
	{
	private:
		///������ ��������
		int m_IdParent;
		///������ ������� �����������
		BoardElementsIterator & m_itBeginBoard;		
	
	public:
		///�����������
		CChildPolicy(BoardElementsIterator & itBeginBoard) : m_itBeginBoard(itBeginBoard), m_IdParent(-1){};
		///��������� IdParent ����������� ������������
		void SetIdParent(unsigned int IdParent)
		{
			m_IdParent = IdParent;
		}
		///��������� �������
		bool Check(CBoardElement* pElem) const
		{
			SS_TRY
			{
				if (pElem->IsHead() || m_IdParent < 0)
				{ return false; }

				int iMaxTreeDepth = 10, iTreeDepth = 0;
				
				for(BoardElementsIterator itParent = m_itBeginBoard + pElem->GetParentIndex(); ((*itParent) != pElem); 
					itParent = m_itBeginBoard + pElem->GetParentIndex())
				{
					if ( pElem->GetParentIndex() == m_IdParent )
					{ return true; }
					pElem = (*itParent);
					
					if(iMaxTreeDepth < ++iTreeDepth)
					{ return false;	}					
				}
			}
			SS_CATCH(L"")
			return false;
			
		}
	};

	//*************************************��������� Cont/Discont*******************************************//

	///�����-��������� ��� �������� ������ ������� �������� ���������
	class CContinuousPolicy
	{
	public:
		///��������� �������
		static bool Continue(CBoardElement* pElem)
		{
			return false;
		}
	};
	
	///�����-��������� ��� �������� ���� ��������� ���������
	class CDiscontinuousPolicy
	{
	public:
		///��������� �������
		static bool Continue(CBoardElement* pElem)
		{
			return true;
		}
	};

	///�����-��������� ��� �������� ������ ������� �������� ���������, �� ������ �������
	class CContinuousNotNeverAdverbPolicy
	{
	public:
		///��������� �������
		static bool Continue(CBoardElement* pElem)
		{
			SS_TRY
			{
				for (PMORPHO pMorpho = pElem->GetFirstMorpho(); pMorpho; pMorpho = pElem->GetNextMorpho())
				{
					if ( pMorpho->GetMorphoFeature().m_PartOfSpeechTypes.Equal(SS::Core::Features::Values::PartOfSpeechTypes.postAdverb) )
					{ return true; }
				}
			}
			SS_CATCH(L"")
			return false;
		}
	};

	
	//*************************************��������� ��� ������ CFeatureController*******************************************//

	///�����-��������� ��� �������� mfamAllForms
	class CAllFormsPolicy
	{
	private:
		///������� ��� AllForms
		std::set<unsigned int> m_DictionaryIndexes;
		///������ ����������� ������-����
		std::set<std::wstring> m_DetectWords;

	public:
		///���������������� ������
		void InitData( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
					   SS::Interface::Core::Dictionary::IDictionary* pDictionary )
		{
			SS_TRY
			{
				typedef std::list<SS::Dictionary::Types::TWordInfo>::iterator TWordInfoIt;
				std::list<SS::Dictionary::Types::TWordInfo> lWordInfo;
				std::list<SS::Dictionary::Types::TWordInfo> lWordInfoDetect;

				//������� ������-���� �������
				for ( SS::SyntaxConstructions::Types::TDetectWordsGroup::iterator itWord = pConObj->GetDetectWords().begin();
					  itWord != pConObj->GetDetectWords().end(); ++itWord )
				{
					pDictionary->GetMorphologyAnalyser()->GetWordInfo( itWord->c_str(), &(lWordInfo),
																	   SS::Dictionary::Types::efzOnlySearch );
					for (TWordInfoIt itWordInfo = lWordInfo.begin(); itWordInfo != lWordInfo.end(); ++itWordInfo)
					{
						lWordInfoDetect.clear();
						pDictionary->GetMorphologyAnalyser()->GetWordFormsByIDSource( &(itWordInfo->front().m_WordIndex.m_DictIndex), 
																					  &(lWordInfoDetect) );
						for (TWordInfoIt itWordInfoDet = lWordInfoDetect.begin(); itWordInfoDet != lWordInfoDetect.end(); ++itWordInfoDet)
						{ m_DetectWords.insert(itWordInfoDet->front().m_wWord); }

						//���������� ���������
						m_DictionaryIndexes.insert(itWordInfo->front().m_WordIndex.m_DictIndex.GetDictionaryIndexWithoutFlags());
					}
					lWordInfo.clear();
				}
			}
			SS_CATCH(L"")
		}

		///�������� ������-�����
		bool IsEqualWord(CBoardElement* pElem)
		{
			for (PMORPHO pMorpho = pElem->GetFirstMorpho(); pMorpho; pMorpho = pElem->GetNextMorpho())
			{
				if ( m_DictionaryIndexes.find(pMorpho->GetIDSource()) != m_DictionaryIndexes.end() )
				{ return true; }
			}
			return false;
		}
	};

	///�����-��������� ��� �������� mfamLetForm
	class CLetFormPolicy
	{
	private:
		///������ ����������� ������-����
		std::set<std::wstring> m_DetectWords;

	public:
		///���������������� ������
		void InitData( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
					   SS::Interface::Core::Dictionary::IDictionary* pDictionary )
		{
			SS_TRY
			{
				for ( SS::SyntaxConstructions::Types::TDetectWordsGroup::iterator itWord = pConObj->GetDetectWords().begin();
					  itWord != pConObj->GetDetectWords().end(); ++itWord )
				{
					m_DetectWords.insert(*itWord);
				}
			}
			SS_CATCH(L"")
		}
		
		///�������� ������-�����
		bool IsEqualWord(CBoardElement* pElem)
		{
			if ( m_DetectWords.find(pElem->GetWord()) != m_DetectWords.end() ) 
			{ return true;	}
			return false;
		}
	};

	///�����-��������� ��� �������� mfamUndefined
	class CUndefinedFormPolicy
	{
	public:
		///���������������� ������
		void InitData( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
					   SS::Interface::Core::Dictionary::IDictionary* pDictionary )
		{
		//����� ������ �� ������
		}

		///�������� ������-�����
		bool IsEqualWord(CBoardElement* pElem)
		{
			return true;
		}

	};

	//***********************************position************************************
		
	///�����-��������� ��� �������� pibBegin
	class CBeginPositionPolicy
	{
	public:
		///�������� �� ������� �������� � �����
		static bool IsAppropriatePosition(CBoardElement* pElem, BoardElementsIterator itF, BoardElementsIterator itL)
		{
			SS_TRY
			{
				BoardElementsIterator it = itF;
				for (it; (*it) != pElem; ++it)
				{
					if ( (*it)->IsHead() && (!(*it)->BeatsBlocks()) )
					{ return false; }
				}
			}
			SS_CATCH(L"")
			return true;
		}
	};

	///�����-��������� ��� �������� pibEnd
	class CEndPositionPolicy
	{
	public:
		///�������� �� ������� �������� � �����
		static bool IsAppropriatePosition(CBoardElement* pElem, BoardElementsIterator itF, BoardElementsIterator itL)
		{
			SS_TRY
			{
				BoardElementsIterator it = itL;
				--it;
				for (it; (*it) != pElem; --it)
				{
					if ( (*it)->IsHead() )
					{ return false; }
				}
			}
			SS_CATCH(L"")
			return true;
		}
	};

	///�����-��������� ��� �������� pibMiddle � ������� ���������
	class CMiddlePositionPolicy
	{
	public:
		///�������� �� ������� �������� � �����
		static bool IsAppropriatePosition(CBoardElement* pElem, BoardElementsIterator itF, BoardElementsIterator itL)
		{
			return ( !CBeginPositionPolicy::IsAppropriatePosition(pElem, itF, itL) &&
					 !CEndPositionPolicy::IsAppropriatePosition(pElem, itF, itL)		);
		}
	};

	///�����-��������� ��� �������� pibUndefined
	class CUndefinedPositionPolicy
	{
	public:
		///�������� �� ������� �������� � �����
		static bool IsAppropriatePosition(CBoardElement* pElem, BoardElementsIterator itF, BoardElementsIterator itL)
		{
			return true;
		}
	};

	//*************************************��������� ��� AgreementType*******************************************//

	///��������� ��� ������� ��������� ��
	class IBaseAT
	{
	public:
		///�������� ������������
		virtual bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
								  SS::Core::Features::CMorphoFeature & oMorphoTwo ) = 0;
	};
	
	///�����-��������� ��� �������� atC
	class CPolicyC : public IBaseAT
	{
	public:
		///�������� ������������
		bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
						  SS::Core::Features::CMorphoFeature & oMorphoTwo )
		{
			return ( oMorphoOne.m_CaseType.IsIntersectsWith(&(oMorphoTwo.m_CaseType)) );
		}
	};

	///�����-��������� ��� �������� atGN
	class CPolicyGN : public IBaseAT
	{
	public:
		///�������� ������������
		bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
						  SS::Core::Features::CMorphoFeature & oMorphoTwo )
		{
			return ( oMorphoOne.m_GenderType.IsIntersectsWith(&(oMorphoTwo.m_GenderType)) &&
					 oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) );
		}
	};

	///�����-��������� ��� �������� atGNC
	class CPolicyGNC : public IBaseAT
	{
	public:
		///�������� ������������
		bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
						  SS::Core::Features::CMorphoFeature & oMorphoTwo )
		{
			return ( oMorphoOne.m_GenderType.IsIntersectsWith(&(oMorphoTwo.m_GenderType)) &&
					 oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) &&
					 oMorphoOne.m_CaseType.IsIntersectsWith(&(oMorphoTwo.m_CaseType)) );
		}
	};

	///�����-��������� ��� �������� atGPN
	class CPolicyGPN : public IBaseAT
	{
	public:
		///�������� ������������
		bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
						  SS::Core::Features::CMorphoFeature & oMorphoTwo )
		{
			return ( oMorphoOne.m_GenderType.IsIntersectsWith(&(oMorphoTwo.m_GenderType)) &&
					 oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) &&
					 oMorphoOne.m_PersonType.IsIntersectsWith(&(oMorphoTwo.m_PersonType)) );
		}
	};

	///�����-��������� ��� �������� atNP
	class CPolicyNP : public IBaseAT
	{
	public:
		///�������� ������������
		 bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
						   SS::Core::Features::CMorphoFeature & oMorphoTwo )
		{
			return ( oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) &&
					 oMorphoOne.m_PersonType.IsIntersectsWith(&(oMorphoTwo.m_PersonType)) );
		}
	};

	///�����-��������� ��� �������� atN
	class CPolicyN : public IBaseAT
	{
	public:
		///�������� ������������
		bool IsIntersect( SS::Core::Features::CMorphoFeature & oMorphoOne,
					 	  SS::Core::Features::CMorphoFeature & oMorphoTwo )
		{
			return oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType));
		}
	};

}
}
}