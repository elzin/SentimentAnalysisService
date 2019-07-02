#pragma once

#include "BoardElement.h"
#include "Block.h"
#include "BoardCommonTypes.h"
#include "../ASSInterface/IBlackBoxItems.h"
#include "../FeatureLibrary/define.h"
#include "../ASCInterface/IInterface.h"
#include "../ASSInterface/ICommon.h"
#include <vector>
#include <list>
#include <set>

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///�����. ������ ���������� �������������� �������������� �����������.
			class CBoard
			{
			private:
				///��� �������� �����
				std::vector<CBoardElement*>				m_elements;
				///����� �������� ����������� ��������� ��� ������� �����������
				std::vector<CBoardElement*>::iterator	m_MarkerLastElem;
				///��������� ��� ������
				CContainer<CBlock, 10>					m_Blocks;
				///�������������� ����
				SS::Core::Features::CSyntaxFeatureAposteriori m_oSyntaxFeatureAposteriori;
				///���� ����� 
				SS::Core::Types::EAnalyseLanguage m_eLang;
				///��������� �������
				SS::Interface::Core::MainAnalyse::IAnalyseParams* m_pAnalyseParams;
			
			private:
				///������� ��� ������ � ������ ������� ����� � ������������� SyntaxFlag
				void Init(SS::Interface::Core::BlackBox::IUnit* begin, unsigned int & uiLastPosition);
				///�������� Unit-�, ��� �� �� �� ��� 256-�
				bool IsGood(SS::Interface::Core::BlackBox::IUnit* pUnit) const;
                /// �������� �� ����������� �����
                bool IsCycle(CBoardElement* pElement, CBoardElement* pBorder = 0) const;
				
			public:
				///�����������
				CBoard();
				///����������
				~CBoard();
				///��������� ���������� ����� ����������
				void FillBoard(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
				///������������� ����� ������������ �� IText - � (���������� true, ���� ������������ ������ �������)
				bool Initialize(SS::Interface::Core::BlackBox::ISentence* pSentence);
				/// �������� ����
				PBLOCK AddBlock();
				///���������� ��������� �� ������ ����
				PBLOCK GetFirstBlock() const
				{
					return m_Blocks.GetFirst();
				}
				///���������� ��������� �� ��������� ����
				PBLOCK GetNextBlock() const
				{
					return m_Blocks.GetNext();
				}
				///�������� ���������� ���� �� �������� � �������� ��������
				PBLOCK GetPrevBlock() const;
				///�������� ������ �� ���������, ����������� �����������
				void DeleteBlocks();
				///������� ���� �������
				PBLOCK SetCurrentBlock(PBLOCK pBlock) const;
				///���������� ��������, ����������� �� ������� ������� �������� �����
				BoardElementsIterator ElementsBegin()
				{
					return m_elements.begin();
				}
				///���������� ��������, ����������� �� ������� ����� ���������� �������� �����
				BoardElementsIterator ElementsEnd()
				{
					return m_MarkerLastElem;
				}
				///��������� ���������� ����� ����������, �������� ������ ��������
				static int HeadDistance(BoardElementsIterator first, BoardElementsIterator last);
				///������� �������� ��� ���� ��������� �����
				void CreateVersions();
				///����������� �������������� ��������� ������ � ������ �������������� ������
				void AssignSyntaxInfoToBlackBoxMultilayer();
				///���������� ������
				unsigned int CountBlock() const;
				///��������� ���������� �������
				void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);
				///������� ������� ����
				void DeleteCurrentBlock();
				///�������� ���� ������
				SS::Core::Types::EAnalyseLanguage GetLang() { return m_eLang; };
				///�������� �������� ������� ��������
				CBoardElement* GetParent(CBoardElement* pElem);
			};
		}
	}
}