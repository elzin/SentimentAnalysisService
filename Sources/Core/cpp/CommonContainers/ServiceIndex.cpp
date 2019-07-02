//ServiceIndex.cpp

#include "StdAfx.h"
#include ".\serviceindex.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			
			//������������
			CServiceIndex::CServiceIndex(
				IUnit* pUnit
				, TLinguisticProcessorMode* pLinguisticProcessorMode
				, IBlackBoxTextStorage* pBlackBoxTextStorage) 
										 : m_pUnit(pUnit)
										 , m_pLinguisticProcessorMode(pLinguisticProcessorMode)
										 , m_pBlackBoxTextStorage(pBlackBoxTextStorage)

			{
			}
			
			CServiceIndex::~CServiceIndex()
			{
			}

			//������ ������ ��� �����������
			SS::Core::Types::IndexationSearch::TViewIndex* CServiceIndex::GetViewIndex() 							
			{
				SS_TRY
				{
					std::list<TViewIndex> lstNeedIndexes;
					bool bOnlyFirst = true;
					GetIndexesFromUnit(lstNeedIndexes, bOnlyFirst);
					if(!lstNeedIndexes.empty())
					{
						m_oViewIndex = (*lstNeedIndexes.begin());
					}
				}
				SS_CATCH(L"")
				
				return &(m_oViewIndex);
			};
			
			//������ ����� �������������� ����������
			void CServiceIndex::GetInfoBuff(char** ppBuff, unsigned int* pSize)
			{
				SS_TRY
				{
					std::list<TViewIndex> lstNeedIndexes;
					std::list<TViewIndex>::iterator itViewIndex;
					
					GetIndexesFromUnit(lstNeedIndexes);
					
					unsigned int iSizeViewIndex = sizeof(TViewIndex);
					unsigned int iSize = iSizeViewIndex * lstNeedIndexes.size();
					(*pSize) = iSize;
					if (iSize == 0) 
					{
						(*ppBuff) = NULL;
						return;
					}
					
					//�������� ������ ��� ������
					m_oBuffer.Allocate(iSize);
					
					//����������
					for ( itViewIndex = lstNeedIndexes.begin(); itViewIndex != lstNeedIndexes.end(); itViewIndex++)
					{ m_oBuffer.PutToBuffer(&(*itViewIndex), iSizeViewIndex); }
									
					//�������� �����
					(*ppBuff) = m_oBuffer.GetBuffer();
				}
				SS_CATCH(L"")
			}
			
			//������� ���� ����� �������������� ���������� 
			void CServiceIndex::SetInfoBuff(char* pBuff, unsigned int Size)
			{
				SS_TRY
				{
					if ( (!pBuff) || (Size == 0) ) 
					{ return; }

					if ( m_oBuffer == pBuff ) 
					{ 
						SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�������� ��������� ����� ��� ������ ��������.");
						return; 
					}
									
					unsigned int iSizeViewIndex = sizeof(TViewIndex);
					if (Size % iSizeViewIndex)
					{ SS_THROW(L"�� ����� ����� ������ ������."); }
					
					Clear();
					//���������� ������ ����������
					int iCount = Size/iSizeViewIndex;
					//��������� ������ ��� ������ � ���
					m_oBuffer.SetBuffer(pBuff, Size);
					
					//���������� ���������� � �����
					TViewIndex											oViewIndex;
					SS::Interface::Core::BlackBox::IIndex*	pIndex = NULL;
					SS::Interface::Core::BlackBox::IFeature*	pFeature = NULL;
					SS::Dictionary::Types::TDictionaryIndex	oInd;
					unsigned int										iPrevIndex = UINT_MAX;

					for (int i = 0; i < iCount; i++)
					{
						//��������� �� ������ ������ ������
						m_oBuffer.GetFromBuffer(&oViewIndex, iSizeViewIndex);
						if (oViewIndex.m_DictionaryIndex != iPrevIndex) 
						{
							oInd.SetDictionaryIndex(oViewIndex.m_DictionaryIndex);
							//���������� DictionaryIndex
							pIndex = m_pBlackBoxTextStorage->CreateIndex();
							pIndex->GetDictionaryIndex()->AppendIndex(oInd);
							m_pUnit->AddIndex(pIndex);
						}
						//���������� ����������� �������
						iPrevIndex = oViewIndex.m_DictionaryIndex;
						//���������� IDForm
						pFeature = m_pBlackBoxTextStorage->CreateFeature();
						pFeature->SetMorphoIndex(oViewIndex.m_IDForm);
						pIndex->AddFeature(pFeature);
					}
					//��� �� �� ��������� delete[] ��� ���������� ������
					m_oBuffer.Reset();
				}
				SS_CATCH(L"")
			}

			//������� ��� �������
			void CServiceIndex::Clear()
			{
				m_pUnit->ClearUnit();
			}

			//��������� � ����� �������� �� Unit
			void CServiceIndex::GetIndexesFromUnit(std::list<TViewIndex> & lstViewIndex, bool bOnlyFirst)
			{
				SS_TRY
				{

					if(m_pLinguisticProcessorMode->m_bIsLiteMode)
						bOnlyFirst = true;

					SS::Interface::Core::BlackBox::IIndex*			pIndex = NULL;
					SS::Interface::Core::BlackBox::IFeature*			pFeature = NULL;
					SS::Interface::Core::BlackBox::IDictionaryIndex* pDictionaryIndex = NULL;
					SS::Dictionary::Types::TDictionaryIndex			oInd;
					TViewIndex													oViewIndex;
					
					for (pIndex = m_pUnit->GetFirstIndex(); pIndex; pIndex = m_pUnit->GetNextIndex())
					{
						if ( !(pDictionaryIndex = pIndex->GetDictionaryIndex()) ) 
							SS_THROW(L"����������� IDictionaryIndex." AND m_pUnit->GetWord());

						if ( !(pDictionaryIndex->GetFirst(&oInd)) ) 
						{ 
							//SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"����������� ������ TDictionaryIndex, ���� IDictionaryIndex ����������!" AND pUnit->GetWord());
							continue;
						}

						if ( oInd.GetIndexType() == SS::Interface::Core::BlackBox::eitMorphoIndex )
						{ 
							oViewIndex.m_DictionaryIndex = oInd.GetDictionaryIndex();
							pFeature = pIndex->GetFirstFeature();
							if (pFeature)
							{ 
								oViewIndex.m_IDForm = pFeature->GetMorphoIndex();
								lstViewIndex.push_back(oViewIndex);
								if (bOnlyFirst) return;
							}
							else
							{ 
								SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"� ������������ ����������� ���������." AND m_pUnit->GetWord()); 
								continue;
							}

							while (pFeature = pIndex->GetNextFeature()) 
							{
								oViewIndex.m_IDForm = pFeature->GetMorphoIndex();
								lstViewIndex.push_back(oViewIndex);
							}
						}
					}
				}
				SS_CATCH(L"")
			}

		}
	}
}








