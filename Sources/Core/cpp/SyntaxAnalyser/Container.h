//Container.h
#pragma once

#include <vector>

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///��������� ����� ����������� �������� � ������� ������ ������������ ������
			/**
			   ���� � �����, �� �� ������ ����� ����������� ��� ����������.
			   ����� ����� �������� 10 ��������� (10 ��� ������� Add()) �.� ����� ���������� �������� 
			   �� �����������������.
			*/
			template<typename T, unsigned int MAX_COUNT = 10>
			class CContainer
			{
			private:
				struct SPair 
				{
					T oT;
					bool bInUse;
					SPair() : bInUse(false)/*, oT()*/ {};
				};
				///��������� ���������
				mutable std::vector<SPair> m_vElements;
				///������� �������
				mutable typename std::vector<SPair>::iterator m_itCurr;
				///��������� ��� ������������� ����������
				mutable std::vector<SPair> m_NullCollection;
				///������� �� ���������
				typename std::vector<SPair>::iterator m_itEnd;

			private:
				///����� ������� ������������� ��������
				bool SetUseElement() const;

			public:
				///�����������
				CContainer();
				///����������� �����������
				CContainer(const CContainer<T, MAX_COUNT> & c);
				///����������
				~CContainer(){};
				///��������=
				void operator=(const CContainer<T, MAX_COUNT> & c);
				///����������� ���������� ��������
				T* Add();
				///�������� ��������� �� ������ �������
				T* GetFirst() const;
				///�������� ��������� �������
				T* GetNext() const;
				///�������� ��������� ������� �� ��������
				T* GetNextForAddress(const T* pT) const;
				///���������� ������� ������� �������
				T* SetCurrent(const T* pT) const;
				///��������� ����������� �������� �� ��������(��� ��������� ����������)
				T* GetPrev() const;
				///����������� �������� �������� �������� �� ����������
				void DeleteCurrent();
				///������� ����������
				void Clear();
				///�������������� �� ������
				void RestoreForAddress(const T* pT);
				///���������� ������� ������ ����������
				unsigned int Size() const;
				///���������� true ���� ��������� ����
				bool Empty() const;
			};

			///�����������
			template<typename T, unsigned int MAX_COUNT>
			CContainer<T, MAX_COUNT>::CContainer()
			{
				m_itCurr =  m_vElements.end();
				m_vElements.reserve(MAX_COUNT);
				for (unsigned int i = 0; i < MAX_COUNT; ++i)
				{
					SPair oPair;
					m_vElements.push_back(oPair);
				}
				m_itEnd = m_vElements.begin();
			}

			///����������� �����������
			template<typename T, unsigned int MAX_COUNT>
			CContainer<T, MAX_COUNT>::CContainer(const CContainer<T, MAX_COUNT> & c) 
			{
				m_itCurr = m_vElements.end();
				unsigned int iIndexEnd  = (unsigned int)distance(c.m_vElements.begin(), c.m_itEnd);
				m_vElements = c.m_vElements;
				m_itEnd = m_vElements.begin() + iIndexEnd;
			}

			///��������=
			template<typename T, unsigned int MAX_COUNT>
			void CContainer<T, MAX_COUNT>::operator=(const CContainer<T, MAX_COUNT> & c)
			{
				m_itCurr = m_vElements.end();
				unsigned int iIndexEnd  = (unsigned int)distance(c.m_vElements.begin(), c.m_itEnd);
				m_vElements = c.m_vElements;
				m_itEnd = m_vElements.begin() + iIndexEnd;
			}

			///����� ������� ������������� ��������
			template<typename T, unsigned int MAX_COUNT>
			bool CContainer<T, MAX_COUNT>::SetUseElement() const
			{
				for (m_itCurr; m_itCurr != m_itEnd; ++m_itCurr)
				{
					if (m_itCurr->bInUse) 
					{ return true; }
				}
				return false;
			}

			///����������� ���������� ��������
			template<typename T, unsigned int MAX_COUNT>
			T* CContainer<T, MAX_COUNT>::Add()
			{
				//���� ������ ��������� ������
				if (m_itEnd == m_vElements.end())
				{ return NULL; }
				
				m_itEnd->bInUse = true;
				T* pT = &(m_itEnd->oT);
				++m_itEnd;

				return pT;
			}

			///�������� ��������� �� ������ ������������ �������
			template<typename T, unsigned int MAX_COUNT>
			T* CContainer<T, MAX_COUNT>::GetFirst() const
			{
				m_itCurr = m_vElements.begin();
				
				if (SetUseElement())
				{ return &(m_itCurr->oT); }
				
				return NULL;
			}

			///�������� ��������� �������
			template<typename T, unsigned int MAX_COUNT>
			T* CContainer<T, MAX_COUNT>::GetNext() const
			{
				if (m_itCurr ==  m_vElements.end())
				{ return NULL; }

				++m_itCurr;
				if (SetUseElement())
				{ return &(m_itCurr->oT); }

				m_itCurr =  m_vElements.end();
				return NULL;
			}

			///����������� �������� �������� �������� �� ����������
			template<typename T, unsigned int MAX_COUNT>
			void CContainer<T, MAX_COUNT>::DeleteCurrent()
			{
				if (m_itCurr !=  m_vElements.end())
				{ m_itCurr->bInUse = false;	}
			}

			///������� ����������
			template<typename T, unsigned int MAX_COUNT>
			void CContainer<T, MAX_COUNT>::Clear()
			{
				typename std::vector<SPair>::iterator it;
				for (it = m_vElements.begin(); it != m_itEnd; ++it)
				{ it->bInUse = false; }
				m_itEnd = m_vElements.begin();
				m_itCurr =  m_vElements.end();
			}

			///�������������� �� ������
			template<typename T, unsigned int MAX_COUNT>
			void CContainer<T, MAX_COUNT>::RestoreForAddress(const T* pT)
			{
				typename std::vector<SPair>::iterator it;
				for (it = m_vElements.begin(); it != m_itEnd; ++it)
				{ 
					if ( &(it->oT) == pT )
					{ it->bInUse = true; return; }
				}
			}

			///���������� ������� ������ ����������
			template<typename T, unsigned int MAX_COUNT>
			unsigned int CContainer<T, MAX_COUNT>::Size() const
			{
				typename std::vector<SPair>::const_iterator it;
				unsigned int iSize = 0;
				for (it = m_vElements.begin(); it != m_itEnd; ++it)
				{ 
					if (it->bInUse)
					{ ++iSize; }
				}
				return iSize;
			}

			///���������� true ���� ��������� ����
			template<typename T, unsigned int MAX_COUNT>
			bool CContainer<T, MAX_COUNT>::Empty() const
			{
				return (Size() == 0);
			}

			///�������� ��������� ������� �� ��������
			template<typename T, unsigned int MAX_COUNT>
			T* CContainer<T, MAX_COUNT>::GetNextForAddress(const T* pT) const
			{
				for (m_itCurr = m_vElements.begin(); m_itCurr != m_itEnd; ++m_itCurr)
				{ 
					if ( &(m_itCurr->oT) == pT )
					{ break; }
				}
				
				if (m_itCurr == m_itEnd)
				{ return NULL; }

				return GetNext();
			}

			///���������� ������� ������� �������
			template<typename T, unsigned int MAX_COUNT>
			T* CContainer<T, MAX_COUNT>::SetCurrent(const T* pT) const
			{
				for (m_itCurr = m_vElements.begin(); m_itCurr != m_itEnd; ++m_itCurr)
				{ 
					if ( &(m_itCurr->oT) == pT )
					{ break; }
				}
				if (m_itCurr == m_itEnd)
				{ SS_THROW(L"�������� �� ����������."); }
				return &(m_itCurr->oT);
			}

			///��������� ����������� �������� �� ��������(��� ��������� ����������)
			template<typename T, unsigned int MAX_COUNT>
			T* CContainer<T, MAX_COUNT>::GetPrev() const
			{
				typename std::vector<SPair>::iterator it = m_itCurr;
				while (it != m_vElements.begin()) 
				{ 
					--it;
					if (it->bInUse) return &(it->oT); 
				}
				return NULL;
			}
			
		}
	}
}
















