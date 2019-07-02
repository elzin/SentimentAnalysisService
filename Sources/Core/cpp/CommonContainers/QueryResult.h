//QueryResult.h
#pragma once
#include "..\ASCInterface\ICommonContainers.h"
#include <list>
#include "ContainersFactory.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			using SS::Interface::Core::CommonContainers::IQueryResult;
			using SS::Interface::Core::CommonContainers::IQueryIndex;
			
			///��������� ������ ������������ ��� ������ ������������ ������� � ������������ �������� ��� ������
			class CQueryResult : virtual public IQueryResult
			{
			private:
				std::list<IQueryIndex*> m_lpQueryIndex;
				std::list<IQueryIndex*>::iterator m_Iter;
				SS::Core::Types::IndexationSearch::TAbsentWords m_oAbsentWords;
				///������� �����������
				CContainersFactory* m_pContainersFactory;

			public:
				//������������
				CQueryResult();
				virtual ~CQueryResult();
				//������ ������
				///������� ��������� (������� ��� �������)
				virtual void Clear();						
				///���������� ������� � ��������� (������� ���� ������ � ������ ��������� �� ����)
				virtual IQueryIndex* AddQueryIndex();		
				///��������� ������� ������� ��������� (0 - ���� ���)
				virtual IQueryIndex* GetFirstQueryIndex();	
				///��������� ���������� ������� ��������� (�� �������� ������� ��������� ������� �������) (0 - ���� �����������)
				virtual IQueryIndex* GetNextQueryIndex();
				/// ������ ������ ������������� ����
				virtual SS::Core::Types::IndexationSearch::TAbsentWords* GetAbsentWords();
				//������ IBase
				virtual ULONG Release();
				virtual HRESULT QueryInterface(REFIID pIID, void** pBase);	
				///���������� ������� �����������
				void SetContainersFactory(CContainersFactory* pContainersFactory){ m_pContainersFactory = pContainersFactory; };
			};

		}
	}
}