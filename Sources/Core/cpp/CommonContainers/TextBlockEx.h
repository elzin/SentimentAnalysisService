//TextBlockEx.h
#pragma once
#include "TextBlock.h"
#include "..\ASSInterface\ITextBlockEx.h"
#include "..\ASSInterface\IBlackBoxUnit.h"
#include "..\ASSInterface\IBlackBoxItems.h"
#include "..\ASSInterface\IBlackBox.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{

			using SS::Interface::Core::CommonContainers::ITextFeature;
			using SS::Interface::Core::CommonContainers::ITextBlockEx;
			using SS::Interface::Core::CommonContainers::IIndexAndPosition;
			using SS::Interface::Core::ResourceManagers::ILoadManager;
			using SS::Interface::Core::BlackBox::IText;
			using SS::Interface::Core::BlackBox::IUnit;
			using SS::Core::Types::IndexationSearch::TIndexationParams;
			using SS::Core::Types::IndexationSearch::TSearchParams;
			using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;
			using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;

			///��������� ���������������� ITextBlock + ��� ���������� �� IText + ������������ IText �� ������������ ITextBlock
			class CTextBlockEx : public ITextBlockEx, public CTextBlock
			{
			private:
				ILoadManager*				m_pLoadManager;
				IBlackBoxTextStorage*		m_pBlackBoxTextStorage;
				TLinguisticProcessorMode	m_LinguisticProcessorMode;
			
			private:
			    ///������������� ������� IndicsationIndex � ServiceIndex
				void SetIndexes(ITextBlockCut* pTextBlockCut, IUnit* pUnit);
				///�������� TextFeature
				void CopyTextFeature(ITextFeature* ptfTo, ITextFeature* ptfFrom);
				///��������� BlackBoxTextStorage
				void InitConnection();
				void ViewTextBlockCut(ITextBlockCut* pTextBlockCut);
				///����������� � ����-��� ���������� �� ��������
				inline void ParagraphToCut( SS::Interface::Core::BlackBox::IParagraph* pParagraph,
											SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut);
				///����������� � �������� ���������� �� ����-����
				inline void CutToParagraph( SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut,
											SS::Interface::Core::BlackBox::IParagraph* pParagraph);
			
			public:
			    ///�����������
				CTextBlockEx(ILoadManager* pLoadManager);
				///����������
				virtual ~CTextBlockEx();
			    ///������ ITextBlockEx
				///���������� ITextBlock �� ��������� IText
				virtual void SetIText(IText* pIText, bool bIsCopyTextFeature = true);
				///������������ IText �� ������� ITextBlock
				virtual IText* GenerateIText();
				///������������ ������ ���������������� ����������
				virtual void SetLinguisticProcessorMode(TLinguisticProcessorMode* pLinguisticProcessorMode);
				///��������� ���������� �������������
				virtual void UpdateRelevance();
				///������������� �� CTextBlock
				///�������� ��������� ����
				virtual ITextFeature* GetTextFeature();
				///������������� �� ITextBlock
				///������� ������� � ��������� (������� ���� � ������ ������)
				virtual ITextBlockCut* AddBlockCut();
			};

		}
	}
}