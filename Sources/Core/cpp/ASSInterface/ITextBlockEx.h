//ITextBlockEx.h

#pragma once

#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASCInterface\TCoommonTypes.h"
#include ".\IBlackBoxItems.h"


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace CommonContainers
			{
		
				using SS::Interface::Core::BlackBox::IText;
				using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;
				
				///��������� ���������������� ITextBlock + ��� ���������� �� IText + ������������ IText �� ������������ ITextBlock
				class ITextBlockEx : virtual public ITextBlock 
				{
				public:
					///�� �������� IText � SetIText() � GenerateIText(), ������ ���������� �� ����������
					///���������� ITextBlock �� ��������� IText
					virtual void SetIText(IText* pIText, bool bIsCopyTextFeature = true) = 0;
					///������������ IText �� ������� ITextBlock
					virtual IText* GenerateIText() = 0;
					///������������ ������ ���������������� ����������
					virtual void SetLinguisticProcessorMode(TLinguisticProcessorMode* pLinguisticProcessorMode) = 0;
					/// ��������� ���������� �������������
					virtual void UpdateRelevance() = 0;
				};			
			
			
			}
		}
	}
}