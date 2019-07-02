//DynamicVersionGenerator.cpp

#include "StdAfx.h"
#include ".\dynamicversiongenerator.h"

namespace SS
{
namespace Syntax
{
namespace BoardElements
{
	///���������� ��������
	void CDynamicVersionGenerator::SetBlockRange(BoardElementsIterator itF, BoardElementsIterator itL)
	{ 
		SS_TRY
		{
			m_itF = itF; 
			m_itL = itL;
			isNull = false;
			SNode oNode;
			m_NodeCollection.clear();
			for (BoardElementsIterator it = m_itF; it != m_itL; ++it)
			{ 
				oNode.pElem = (*it);
				m_NodeCollection.push_back(oNode);
			}
		}
		SS_CATCH(L"")
	}

	///�������� ������ ��������
	bool CDynamicVersionGenerator::GetFirstVersion()
	{
		SS_TRY
		{

			//�������� �� �������������
			if ( /*(m_itF == m_NullCollection.end()) ||
				 (m_itL == m_NullCollection.end()) ||*/isNull || !m_pVersion )
			{ SS_THROW(L"�� ��������� �������������."); }

			//��������� ��������
			m_pVersion->ClearAll();

			for (BoardElementsIterator it = m_itF; it != m_itL; ++it)
			{ m_pVersion->AddElement(); }

			//���������� ����� ������ ��������
			for (IteratorNC itNode = m_NodeCollection.begin(); itNode != m_NodeCollection.end(); ++itNode)
			{ itNode->pMorpho = itNode->pElem->GetFirstMorphoDynamic();	}

			//��������� ������� � ��� ������������� ����� ���������� ��������
			if (!FindNormalVersion()) 
			{ return false; }

			//�������� ��������
			WriteVersion();

		}
		SS_CATCH(L"")	
		return true;
	}

	///�������� ��������� ��������
	bool CDynamicVersionGenerator::GetNextVersion()
	{
		SS_TRY
		{
			//������������� ��������� ��������
			if (!GenerateVersion())
			{ 
				return false;
			}
			//��������� ������� � ��� ������������� ����� ���������� ��������
			if (!FindNormalVersion()) 
			{ 
				return false; 
			}
			//�������� ��������
			WriteVersion();
		}
		SS_CATCH(L"")
		return true;
	}
	
	///===============================================Private=================================================///

	///����� ���������� ��������
	bool CDynamicVersionGenerator::FindNormalVersion()
	{
		SS_TRY
		{

			/// ������ �� ������
			for (int i = 0; i < 100; i++)
			{
				if(CheckVersion())
				{ return true; }
				if (!GenerateVersion())
				{ return false; }
			}

		}
		SS_CATCH(L"")
		return true;
	}

	///�������� ��������
	void CDynamicVersionGenerator::WriteVersion() const
	{
		SS_TRY
		{
			ConstIteratorNC itNode(m_NodeCollection.begin());
			for (PVERELEMENT pVE = m_pVersion->GetFirst(); pVE; pVE = m_pVersion->GetNext())
			{ 
				pVE->Init(itNode->pElem, itNode->pMorpho);
				++itNode;
			}
		}
		SS_CATCH(L"")
	}
	
	///������������� ��������� ��������
	bool CDynamicVersionGenerator::GenerateVersion()
	{
		SS_TRY
		{
			bool bChanged = false;
			for (IteratorNC itNode = m_NodeCollection.begin(); itNode != m_NodeCollection.end(); ++itNode)
			{
				itNode->pMorpho = itNode->pElem->GetNextMorphoForAddress(itNode->pMorpho);
				if (itNode->pMorpho)
				{
					bChanged = true;
					break;
				}
				else
				{ 
					itNode->pMorpho = itNode->pElem->GetFirstMorphoDynamic();
				}
			}
			if (bChanged) 
			{ 
				return true; 
			}
		}
		SS_CATCH(L"")
		return false;
	}
	
	///��������� �������� �� ���������� �� ��
	bool CDynamicVersionGenerator::CheckVersion() const
	{
		int numOfIter = 0;
		SS_TRY
		{
			//���� ���������� ��
			std::list<SNode> l_NodesAT;
			//���������� ����� �����������
			unsigned int iNumber = 0;
			//����� ��������� �� ������� ����������� �����������
			do
			{
				l_NodesAT.clear();
				//����� ��������� �����������
				++iNumber;
				//����� ����� � �� ������ ����������� �����������
				for (ConstIteratorNC itNode = m_NodeCollection.begin(); itNode != m_NodeCollection.end(); ++itNode)
				{ 
					if ( itNode->pElem->IsAT(iNumber) )
					{ 
						l_NodesAT.push_back(*itNode);
					}
				}
				//�������� ����������� �����
				if (l_NodesAT.empty())
				{ 
					return true;
				}
						
				//��� ��
				SS::Core::Features::Types::AgreementType oAT;
				//���������� �������� ��
				const unsigned int CountValueAT = SS::Core::Features::Values::AgreementType.GetValueCount();
				//������� ����� �� ����������� ��
				std::list<SNode> l_NodesOneAT;
				//�������� �������
				std::list<SNode>::iterator itN;
				std::list<SNode>::iterator itNBegin;
				//������� �� ��
				for (unsigned int iAT = 0; iAT < CountValueAT; ++iAT)
				{
					//������� ����������
					l_NodesOneAT.clear();
					//���������� ��
					oAT.SetSingleValue(iAT);
					if (oAT.IsUndefined()) { continue; }
					//���������� ���������� �� ���������
					for (itN = l_NodesAT.begin(); itN != l_NodesAT.end(); ++itN)
					{
						if ( itN->pElem->GetAT(iNumber).IsIntersectsWith(&oAT) )
						{ 
							l_NodesOneAT.push_back(*itN);
						}
					}
					//��������
					itNBegin = l_NodesOneAT.begin();
					if ( l_NodesOneAT.size()>0)
					{
						itN = itNBegin; ++itN;
						//��������� �� ���������� �� ���������� ��
						for (itN; itN != l_NodesOneAT.end(); ++itN)
						{
							if (itN->pMorpho == NULL || itNBegin->pMorpho == NULL) 
							{
								return false;
							}
							if (!IsIntersectByAT(itNBegin->pMorpho->GetMorphoFeature(), itN->pMorpho->GetMorphoFeature(), oAT) )
							{ 
								return false; 
							}
						}	
					}
				}
				numOfIter++;
				if (numOfIter > 100000) 
				{
					return false;
				}
			} 
			while (!l_NodesAT.empty());
		}
		SS_CATCH(L"")
		return true;
	}

	///�������� ����������� �� AgreementType
	bool CDynamicVersionGenerator::IsIntersectByAT( SS::Core::Features::CMorphoFeature & oMorphoOne,
													SS::Core::Features::CMorphoFeature & oMorphoTwo,
													SS::Core::Features::Types::AgreementType & oAt ) const
	{
		SS_TRY
		{
			if ( oAt.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atC) )
			{ 
				return oMorphoOne.m_CaseType.IsIntersectsWith(&(oMorphoTwo.m_CaseType));
			}
			else if ( oAt.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atGN) )
			{ 
				return ( oMorphoOne.m_GenderType.IsIntersectsWith(&(oMorphoTwo.m_GenderType)) &&
					     oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) );
			}
			else if ( oAt.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atGNC) )
			{ 
				return ( oMorphoOne.m_GenderType.IsIntersectsWith(&(oMorphoTwo.m_GenderType)) &&
						 oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) &&
						 oMorphoOne.m_CaseType.IsIntersectsWith(&(oMorphoTwo.m_CaseType)) );
			}
			else if ( oAt.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atGPN) )
			{ 
				return ( oMorphoOne.m_GenderType.IsIntersectsWith(&(oMorphoTwo.m_GenderType)) &&
						 oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) &&
						 oMorphoOne.m_PersonType.IsIntersectsWith(&(oMorphoTwo.m_PersonType)) );
			}
			else if ( oAt.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atNP) )
			{ 
				return ( oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType)) &&
						 oMorphoOne.m_PersonType.IsIntersectsWith(&(oMorphoTwo.m_PersonType)) );
			}
			else if ( oAt.IsIntersectsWith(&SS::Core::Features::Values::AgreementType.atN) )
			{ 
				return oMorphoOne.m_NumberType.IsIntersectsWith(&(oMorphoTwo.m_NumberType));
			}
			else
			{ SS_THROW(L"���������������� AgreementType."); }

		}
		SS_CATCH(L"")
		return false;
	}

}
}
}



