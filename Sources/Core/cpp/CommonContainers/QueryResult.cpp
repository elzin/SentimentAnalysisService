// QueryResult.cpp
#include "StdAfx.h"
#include "queryresult.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			///�����������
			CQueryResult::CQueryResult() : m_pContainersFactory(NULL)
			{
				SS_TRY
				{
					m_Iter = m_lpQueryIndex.end();
				}
				SS_CATCH(L"")
			}

			///����������
			CQueryResult::~CQueryResult()
			{
				Clear(); 
			}

			//������ IBase
			ULONG CQueryResult::Release()
			{
				delete this;
				return 0;
			}

			HRESULT CQueryResult::QueryInterface(REFIID pIID, void** pBase)	//���������� � ���������� � �������� REFIID. 
				//pBase ����� NULL, ���� ������ ��������� �� ��������������
			{
				if (pIID==IID_QueryResult)
				{
					*pBase = (IQueryResult*)this;
				}
				else if( pIID == IID_Base )
				{
					*pBase=static_cast< SS::Interface::IBase* >( this );
				}
				else 
					*pBase = NULL;
				return S_OK;
			}
			
			//������ ������
			void CQueryResult::Clear()						// ������� ��������� (������� ��� �������)
			{
				SS_TRY

					m_oAbsentWords.clear();

					for (m_Iter = m_lpQueryIndex.begin(); m_Iter != m_lpQueryIndex.end(); m_Iter++)
					{
						if ((*m_Iter)) 
						{
							delete (*m_Iter);
						}						
					}

					m_lpQueryIndex.clear();
				SS_CATCH(L"")
			}
			
			IQueryIndex* CQueryResult::AddQueryIndex()		// ���������� ������� � ��������� (������� ���� ������ � ������ ��������� �� ����)
			{
				SS_TRY
				{
					IQueryIndex* pQueryIndex = m_pContainersFactory->CreateQueryIndex();
					m_lpQueryIndex.push_back(pQueryIndex);
					return pQueryIndex;
				}
				SS_CATCH(L"")
				return NULL;
			}
			
			IQueryIndex* CQueryResult::GetFirstQueryIndex()	// ��������� ������� ������� ��������� (0 - ���� ���)
			{
				SS_TRY
				{
					if (m_lpQueryIndex.empty())
					{ return NULL; }
					m_Iter = m_lpQueryIndex.begin();
                    return (*m_Iter);
				}
				SS_CATCH(L"")
				return NULL;
			}
			
			IQueryIndex* CQueryResult::GetNextQueryIndex()	// ��������� ���������� ������� ��������� (�� �������� ��������� ������� �������) (0 - ���� �����������)
			{
				SS_TRY
					if (m_Iter == m_lpQueryIndex.end())
					{
						//SS_THROW(L" �� ������ ����� GetFirstQueryIndex() ")
						SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L" �� ������ ����� GetFirstQueryIndex() ");
						return NULL;
					}
					m_Iter++;
					if (m_Iter == m_lpQueryIndex.end())
					{
						return NULL;
					}
					return (*m_Iter);
				SS_CATCH(L"")
				return NULL;
			}

			/// ������ ������ ������������� ����
			SS::Core::Types::IndexationSearch::TAbsentWords* CQueryResult::GetAbsentWords()
			{
				SS_TRY
					return &m_oAbsentWords;
				SS_CATCH(L"")
			}

		}
	}
}