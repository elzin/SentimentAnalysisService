//QueryIndex.h

#pragma once

#include "..\ASCInterface\ICommonContainers.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{

			using SS::Interface::Core::CommonContainers::IQueryIndex;
			using SS::Interface::Core::CommonContainers::SQueryIndexAttributes;
			
			///"������ �������" ������������� ������ ������� � ���������� ����������
			class CQueryIndex : public IQueryIndex
			{
			private:
				unsigned int			m_QueryIndex;		// ������ �������
				float					m_IndexWeight;		// ��� �������
				SQueryIndexAttributes	m_oAttributes;		// ���������
				char					m_Operator;			// �������� �����
				unsigned int			m_LeftBrackets;		// ���-�� ������ �����
				unsigned int			m_RightBrackets;	// ���-�� ������ ������
				wchar_t*				m_wszWord;			// ����� �������
			public:
				//������������
				CQueryIndex();
				virtual ~CQueryIndex();
				//������ IQueryIndex
				///��������� ����� ������� (���� ��� ������ � ����������� ������)
				virtual const wchar_t* GetQueryWord();								
				///��������� ����� ������� (���� ��� ������ � ����������� ������)
				virtual void SetQueryWord(const wchar_t* wszWord);				
				///��������� �������
				virtual unsigned int GetQueryIndex()							
				{
					return m_QueryIndex;
				}
				///������������ �������
				virtual void SetQueryIndex(unsigned int uiIndex)				
				{
					m_QueryIndex = uiIndex;
				}
				///���������� ��� �������
				virtual float GetIndexWeight()									
				{
					return m_IndexWeight;
				}
				///������������� ��� �������
				virtual void SetIndexWeight(float fWeight)						
				{
					m_IndexWeight = fWeight;
				}
				///���������� ���������
				virtual SQueryIndexAttributes GetAttributes()					
				{
					return m_oAttributes;
				}
				///������������� ���������
				virtual void SetAttributes(SQueryIndexAttributes oAttributes)	
				{
					m_oAttributes = oAttributes;
				}
				///���������� �������� �����
				virtual const char GetOperator()								
				{
					return m_Operator;
				}
				///������������� �������� �����
				virtual void SetOperator(char chOperator)						
				{
					m_Operator = chOperator;
				}
				///��������� ���-�� ������ �����
				virtual const unsigned int GetLeftBrackets()					
				{
					return m_LeftBrackets;
				}
				///��������� ���-�� ������ ������
				virtual const unsigned int GetRightBrackets()					
				{
					return m_RightBrackets;
				}
				///������������ ���-�� ������ �����
				virtual void SetLeftBrackets(unsigned int uiBracketCount)		
				{
					m_LeftBrackets = uiBracketCount;
				}
				///������������ ���-�� ������ ������
				virtual void SetRightBrackets(unsigned int uiBracketCount)		
				{
					m_RightBrackets = uiBracketCount;
				}
			};


		}
	}
}