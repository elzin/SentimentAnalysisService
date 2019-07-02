#pragma	 once

#include "IExpertController.h"
#include "GroupManager.h"
#include "BoardCommonTypes.h"
#include "Board.h"
#include "Block.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///��������� ������������������� ���������� ���������.
			class CExpertController : public SS::Interface::Syntax::IExpertController
			{
			private:
				///�������� �����
				static CGroupManager				m_oGroupManager;
				///�������� �� ������� ������ ���������
				CGroupManager::TCollectionItr		m_itCurrentGroupPtr;
				///�������� �� �������� ��������
				CExpertGroup::TExpertPtrItr			m_itCurrentExpertPtr;
				///�������������� �����
				BoardElements::CBoard				m_oBoard;
				///���������, ��������� �� ��������� �� ��������
				bool m_isVersioned;
				///���� ��� ����������� ������� �� ����� �������� ��� �� ����
				bool m_bOneHyp;
				///����� ��������
				int m_iNumHyp;
				///���������� �������� ������������� �����
				bool m_bInitBoard;
					
			public:
				///�����������
				CExpertController(ESyntaxBase eBase);
				///���������� ����������� ��� ������ � ��������� ���������
				SS::Interface::Core::Common::ILoad* GetLoader();
				///������������� �� IBase
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
				///��������� ����������
				void SetParams(bool bOneHyp, int iNumHyp);
				///������������� ������������� �����������
				virtual void SetSentence(SS::Interface::Core::BlackBox::ISentence* pSentence);
				///������������� ������������� ����������� ��� �������� �����
				virtual void SetSentenceTest( SS::Interface::Core::BlackBox::ISentence* pSentence,  
											  SS::Syntax::ExpertModel::ParsingType type );
				///��������� �������������� ������ ����������� � ������������ ��������� �������
				virtual void ParseSentenceDynamic(ParsingType pType);
				///��������� ���������� ��������
				virtual void PerformStep();
				///��������� �� ����� ������� ������ ���������
				virtual void PerformGroup();
				///������������ ��������� ��������
				virtual void PerformVersion();
				///���������� �������������� �����
				virtual BoardElements::CBoard & GetBoard()
				{
					return m_oBoard;
				}
				///���������� ������, ����������� �������� ��������
				virtual std::wstring GetCurrentExpertString()
				{
                    std::wstring result = L"";
                    if((m_itCurrentGroupPtr != m_oGroupManager.GetEndGroup()) && 
                       (m_itCurrentExpertPtr != (*m_itCurrentGroupPtr)->end()))
                        result = (*m_itCurrentExpertPtr)->GetName();
					return result;
				}
				///��������� �� ��������� �� ��������
				virtual bool IsVersioned()
				{
					return !((*m_itCurrentGroupPtr)->IsAmbiguity());
				}

				///��������
				virtual ULONG Release()
				{
					delete this;
					return 0;
				}
				///������ ����������
				virtual HRESULT QueryInterface(REFIID pIID, void** pBase)
				{
					if (pIID == IID_ExpertController)
					{
						*pBase = static_cast< SS::Interface::Syntax::IExpertController* >( this );
					}
					else if (pIID == IID_Base)
					{
						*pBase = static_cast< SS::Interface::IBase* >( this );
					}
					else
					{
						*pBase = NULL;
					}
					return S_OK;
				}
				///���������� AnalyseParams
				void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);
			};
		}
	}
}