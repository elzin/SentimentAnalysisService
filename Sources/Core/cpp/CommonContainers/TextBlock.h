//TextBlock.h
#pragma once
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASCInterface\ITextFeature.h"
#include ".\SearchResult.h"
#include "ContainersFactory.h"
#include <list>

namespace SS
{
namespace Core
{
namespace CommonContainers
{
	using SS::Interface::Core::CommonContainers::ITextBlock;		
	using SS::Interface::Core::CommonContainers::ITextFeature;
	using SS::Interface::Core::CommonContainers::ITextBlockCut;

	///��������� ���� ������� ������������ ��� ��� ����������, ��� � ��� ������
	class CTextBlock : virtual public ITextBlock
	{
	private:
		///��� XML
		std::wstring m_ws;								
		///�������������
		unsigned int m_uiRelevance;						
		//��������� �� ��������� ����
		ITextFeature* m_pTextFeature;					
		///��������� �� ���������� SearchResult
		SS::Core::CommonContainers::CSearchResult* m_pSearchResult;

	protected:
		///C����� ���������� �� ITextBlockCut
		std::list<ITextBlockCut*> m_lpTextBlockCut;		
		///�������� ������� ������
		std::list<ITextBlockCut*>::iterator m_Iter;
		///������� �����������
		CContainersFactory* m_pContainersFactory;

	protected:
		///�����������
		CTextBlock();
		///��������� � ��������� ������ �TextBlockCut
		void AddCut(ITextBlockCut* pTextBlockCut);

	public:
		///����������
		virtual ~CTextBlock();
		///��������� XML - ������ ����������� ����������
		virtual std::wstring* GetXML();
		///�������������� ������, �������� ����������� ��� ��������� ����
		virtual ITextFeature* GetTextFeature();			
		///������� ����� (������ ��� ������� �� ������)
		virtual void Clear();							
		///��������� ������ ������� ��������� (0 - ���� ���)
		virtual ITextBlockCut* GetFirstBlockCut();		
		///��������� ��������� ������� ��������� (0 - ���� �����������)
		virtual ITextBlockCut* GetNextBlockCut();		
		///��������� ������������� ������� ���������� �����
		virtual unsigned int GetRelevance()				
		{
			return m_uiRelevance;
		}
		///������������ ������������� ������� ���������� �����
		virtual void SetRelevance(unsigned int uiRelevance)	
		{
			m_uiRelevance = uiRelevance;
			if(m_pSearchResult)
			{ m_pSearchResult->ChangeSortedDataActuality(false); }
		}
		void UpdateRelevance();
		///������������� ��������� SearchResult
		void SetSearchResult(SS::Core::CommonContainers::CSearchResult* pSearchResult)
		{
			m_pSearchResult = pSearchResult;
		}
		void Sort();
		///���������� ������� �����������
		void SetContainersFactory(CContainersFactory* pContainersFactory){ m_pContainersFactory = pContainersFactory; };
	};
}
}
}