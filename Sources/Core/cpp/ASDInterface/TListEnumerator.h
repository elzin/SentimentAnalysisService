#pragma once

#include "IEnumerator.h"
#include <list>
#include <algorithm>

namespace SS
{
namespace Core
{
namespace Types
{

	/// ��������� ������� �������� � ����������� �� ������ ������
	template <class T> class TListEnumerator : public SS::Interface::Core::Common::IEnumerator
	{
		/*! \typedef TCollection
		*  \brief    ���������� ��������� ��������� �� ������ ������ � ����-��������� T ������� ���������� ������
		*/
		typedef std::list<T> TCollection;

		/// ��������� ��������� �� ������ ������ � ����-��������� T ������� ���������� ������
		TCollection m_lstCollection;

		/// ��������� �������� �������� ���������
		TListEnumerator<T>::TCollection::iterator it_currElement;

		/// ������������� ��������� �������� �������� �� ������ ���������)
		void Init()
		{
			it_currElement = m_lstCollection.begin();	
		};

	public:

		/// �������������� ������ ������ (������������� ��������� �������� �������� �� ������ ���������)
		TListEnumerator()
		{
			Init();
		};

		///���������� true, ���� ��������� ������
		unsigned int Empty()
		{
			return m_lstCollection.empty();	
		};

		///���������� ����� ��������� ���������
		unsigned int Count()
		{
		
			return (unsigned int)m_lstCollection.size();
		};

		///������� ���������
		void Clear()
		{
			m_lstCollection.clear();
		};

		///������������� ��������� �� ������ ��������� 
		unsigned int Reset()
		{
			Init();
			return (m_lstCollection.empty()) ? false : true;
		};

		///������������� ��������� �� ��������� ������� ���������
		unsigned int MoveNext()
		{
		
			if ((m_lstCollection.empty()) ||
				(it_currElement == --m_lstCollection.end())) 
				return false;
			else
			{
				it_currElement ++;
				return true;
			};
		};

		///��������� ������� � ���������
		void Add(T Element)
		{
			m_lstCollection.push_back(Element);
			it_currElement = --m_lstCollection.end();
		};

		///���������� ������� ������� ��������� (NULL, ���� ��� ������)
		T* GetCurrent()
		{
			return ((m_lstCollection.empty()) ||
				(it_currElement == m_lstCollection.end())) ?
				NULL : &(*it_currElement);
		};

		void Find(T value)
		{
			it_currElement = std::find(m_lstCollection.begin(), m_lstCollection.end(), value);	
		};
	};
}
}
}
