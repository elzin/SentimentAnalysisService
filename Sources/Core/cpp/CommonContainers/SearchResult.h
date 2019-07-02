// SearchResult.h
#pragma once
#include "..\ASSInterface\ICommonContainersEx.h"
#include <list>
#include "SearchResultFile.h"
#include "ContainersFactory.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{

			using SS::Interface::Core::CommonContainers::ISearchResultEx;
			using SS::Interface::Core::CommonContainers::ITextBlock;
						
			///��������� ������ ������������ ��� ������ ������������ ������
			class CSearchResult : public ISearchResultEx
			{
			private:
				std::list<ITextBlock*> m_lpTextBlock;
				std::list<ITextBlock*>::iterator m_lIter;
				bool m_bSorted;
				bool m_bIsSortedDataActuality;
				std::list<ITextBlock*> m_lpTextBlockSort;
				std::list<ITextBlock*>::iterator m_lIterSort;
				XML::CSearchResultFile m_oXML;
				unsigned int m_uiRequestID;
				///���������� ���������� ������
				bool m_bGlobal;
				///������� �����������
				CContainersFactory* m_pContainersFactory;
				
			private:
				void Sort();

			public:
				virtual ULONG Release();
				virtual HRESULT QueryInterface(REFIID pIID, void** pBase);
				virtual void AddTextBlock(ITextBlock * pTextBlock);
				CSearchResult();
				virtual ~CSearchResult();
				///������� ��������� (������� ��� ��������� �����)
				virtual void Clear();						
				///���������� ���������� ����� � ��������� (������� ���� ���� � ������ ��������� �� ����)
				virtual ITextBlock *AddTextBlock();			
				///��������� ������� ���������� ����� ��������� (0 - ���� ���)
				virtual ITextBlock *GetFirstTextBlock();	
				///��������� ���������� ���������� ����� ��������� (�� �������� ������� ��������� ������� ���������� �����) (0 - ���� �����������)
				virtual ITextBlock *GetNextTextBlock();		
				///������ ��������� ������ ��� ������������ �������
				virtual ITextBlock* GetTextBlock(unsigned int nPosition);
				///������ ���������� ����������� ������
				virtual unsigned int Count();				
				///��������� ����� ������ ����������� 
				virtual void SetSortedMode(bool bOn);
				virtual bool GetXML(std::wstring* pXML);
				virtual bool GetXML(std::wstring* pXML, int iFirst, int iCount);
				virtual void SetRequestID(unsigned int id);
				virtual unsigned int GetRequestID();
				//���������� ��������� �� xml (������ ����� ������� ����� TextBlock)
				virtual void SetGsXML(const wchar_t* wzXml);
				void ChangeSortedDataActuality(bool bSortedDataActuality)
				{
					m_bSorted = bSortedDataActuality;
				}
				///���������� ������� �����������
				void SetContainersFactory(CContainersFactory* pContainersFactory){ m_pContainersFactory = pContainersFactory; };
			};
		}
	}
}