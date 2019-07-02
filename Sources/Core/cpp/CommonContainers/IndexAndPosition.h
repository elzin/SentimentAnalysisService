// IndexAndPosition.h
#pragma once
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASSInterface\Constants.h"
#include "..\ASSInterface\IBlackBoxUnit.h"
#include "..\ASSInterface\IBlackBox.h"
#include "ContainersFactory.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			using SS::Interface::Core::BlackBox::IUnit;
			using SS::Interface::Core::CommonContainers::IServiceIndex;
			using SS::Interface::Core::CommonContainers::IIndexationIndex;
			using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;
			using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;
			
			/// "������ �� �������" ������ �� ����� ������� � ������
			/**
			�������� � ���� ������������� � ����������� �������, ��������������� �� ����� ������� ���������� �����.
			������������ ��� ���������� � ��� ������
			*/ 
			class CIndexAndPosition : public SS::Interface::Core::CommonContainers::IIndexAndPosition
			{
			private:
				std::wstring			  m_ws;
				IServiceIndex*			  m_pServiceIndex;
				IIndexationIndex*		  m_pIndexationIndex;
				IUnit*					  m_pUnit;
				IBlackBoxTextStorage*	  m_pBlackBoxTextStorage;
				TLinguisticProcessorMode* m_pLinguisticProcessorMode;
				///���� ������������, ���� ���������� ������� Unit � ����������� 
				bool m_bDelUnit;
				///������� �����������
				CContainersFactory* m_pContainersFactory;

			private:
				///�������� �����
				void CreateUnit();
				
			public:
				//������������
				CIndexAndPosition(IBlackBoxTextStorage* pBlackBoxTextStorage, TLinguisticProcessorMode* pLinguisticProcessorMode);
				virtual	~CIndexAndPosition();
				///������ ������
				///����� ������� ������� � ����� �����
				virtual unsigned int GetPosition();	 				
				///������� ������� ������� � ����� �����
				virtual void SetPosition(unsigned int uiPosition);	
				///������ ����������� ������
				virtual IServiceIndex* GetServiceIndex();			
				///������ ������������� ������
				virtual IIndexationIndex* GetIndexationIndex();		
				///������������ �����
				virtual void SetWord(const wchar_t* szWord);					
				///������ ���� ����� (��� ������ ������������)
				virtual const wchar_t* GetWord();
				///������ ��� ��������� �������
				virtual SS::Core::Types::IndexationSearch::EHighlightType GetHighlightType();
				///��������� ��� ��������� �������
				virtual void SetHighlightType(SS::Core::Types::IndexationSearch::EHighlightType hlt);
				///��������� ����������� ������ � ������ ������� ������� �����
				virtual unsigned int GetFirstCharPosition();
				///������������ ����������� ������ � ������ ������� ������� �����
				virtual void SetFirstCharPosition(unsigned int uiPosition);
				///������ ��� ��������� �������
				virtual unsigned int GetIsInAnswerSentence();
				///��������� ��� ��������� �������
				virtual void SetIsInAnswerSentence(unsigned int bIn);
			
				///������
				///��������� XML - ������ ����������� ����������
				std::wstring* GetXML();
				///��������� ���������������� �����
				void SetUnit(IUnit* pUnit);
				///�������� ��������� �� ����
				IUnit* GetUnit();
				///�������� �� ����� ����-�� ���� ������ (����� - �� ������������)
				bool IsValid();
				///����������� �� ������� �������� Unit
				void NotDeleteUnit();
				///���������� ������� �����������
				void SetContainersFactory(CContainersFactory* pContainersFactory){ m_pContainersFactory = pContainersFactory; };
			};


		}
	}
}