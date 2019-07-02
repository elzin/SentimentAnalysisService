//IndexationIndex.h

#pragma once

#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASCInterface\TCoommonTypes.h"
#include "..\ASSInterface\IBlackBoxUnit.h"
#include "..\ASSInterface\TDictionaryManager.h"
#include "..\ASSInterface\IBlackBox.h"
#include <vector>

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			using SS::Interface::Core::BlackBox::IUnit;
			using SS::Interface::Core::BlackBox::IIndex;
			using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;
			using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;
			
			///�������� ���������� "������������� ��������"
			class CIndexationIndex : public SS::Interface::Core::CommonContainers::IIndexationIndex
			{
			private:
				IUnit*						m_pUnit;
				IIndex*						m_pCurrIndex;
				TLinguisticProcessorMode*	m_pLinguisticProcessorMode;
				IBlackBoxTextStorage*		m_pBlackBoxTextStorage;

			private:
				///������� ������������ ���� ������� � ��������� ������
				bool ApplyLinguisticProcessorMode(SS::Dictionary::Types::TDictionaryIndex & oIndex);
				///�������� ��������� ������
				unsigned int GetIndex();

			public:
				///������������
				CIndexationIndex(IUnit* pUnit, TLinguisticProcessorMode* pLinguisticProcessorMode, IBlackBoxTextStorage* pBlackBoxTextStorage);
				virtual ~CIndexationIndex();
				///������ IIndexationIndex
				///��������� ������� ������� ��������� (0 - ���� ���)
				virtual unsigned int GetFirstIndex();				
				///��������� ���������� ������� ��������� (0 - ���� �����������)
				virtual unsigned int GetNextIndex();				
				///������� ��������� (������ ��� �������)
				virtual void Clear();								
				///���������� ������� � ���������
				virtual void AddIndex(unsigned int uiIndex);
			};


		}
	}
}