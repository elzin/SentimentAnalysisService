//IndexationResult.h
#pragma once
#include "..\ASCInterface\ICommonContainers.h"
#include "ContainersFactory.h"
#include <list>

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{

			using SS::Interface::Core::CommonContainers::ITextBlock;
			using SS::Interface::Core::CommonContainers::IIndexationResult;
			
			///�������� ���������� ��������� ������ CTextBlockEx
			class CIndexationResult : public IIndexationResult
			{
			private:
				std::list<ITextBlock*> m_lpTextBlock;
				std::list<ITextBlock*>::iterator m_listIter;
				///������� �����������
				CContainersFactory* m_pContainersFactory;
				
			public:
				//������������
				CIndexationResult();
				virtual ~CIndexationResult();
				///������� ��������� (������� ��� ��������� �����)
				virtual void Clear();						
				///���������� ���������� ����� � ��������� (������� ���� ���� � ������ ��������� �� ����)
				virtual ITextBlock *AddTextBlock();			
				///��������� ������� ���������� ����� ��������� (0 - ���� ���)
				virtual ITextBlock *GetFirstTextBlock();	
				///��������� ���������� ���������� ����� ��������� (�� �������� ������� ��������� ������� ���������� �����) (0 - ���� �����������)
				virtual ITextBlock *GetNextTextBlock();		
				//������ IBase
				virtual ULONG Release();
				virtual HRESULT QueryInterface(REFIID pIID, void** pBase);	
				///���������� ������� �����������
				void SetContainersFactory(CContainersFactory* pContainersFactory){ m_pContainersFactory = pContainersFactory; };
			};

		}
	}
}