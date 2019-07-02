//#pragma once
//
//#include "TListEnumerator.h"
//#include <string>
//
//namespace SS
//{
//namespace Core
//{
//namespace Types
//{
//namespace Search
//{
//
//	/// ������������ �������� ����� � ��� ������� ������
//	class TWord
//	{
//
//	protected:
//		/// �����
//		std::string m_sWord;
//		/// ������ ������ �����
//		unsigned int m_uiSourceIndexOfWord;
//	public:
//
//		TWord() :
//		  m_uiSourceIndexOfWord(NULL)
//		{
//
//		};
//
//		TWord(unsigned int uiSourceIndexOfWord) :
//		  m_uiSourceIndexOfWord(uiSourceIndexOfWord)
//		{
//
//		};
//
//		///������������� ����� TWord::m_sWord
//		void SetWord(const char* pszWord)
//		{
//			m_sWord = pszWord;
//		};
//
//		///���������� ����� TWord::m_sWord
//		const char* GetWord()
//		{
//			return m_sWord.c_str();
//		};
//
//		///������������� ������ ������ ����� TWord::m_uiSourceIndexOfWord
//		void SetSourceIndexOfWord(unsigned int uiSourceIndexOfWord)
//		{
//			m_uiSourceIndexOfWord = uiSourceIndexOfWord;
//		};
//
//		///���������� ������ ������ ����� TWord::m_uiSourceIndexOfWord
//		unsigned int GetSourceIndexOfWord()
//		{
//			return m_uiSourceIndexOfWord;
//		};
//	};
//
//
//	/// ������ ���������
//	/** ������ � ���������� ��������� �������� ������� ����� ������ ��������� 
//	(���� �� �������� ��������� �����, ��� �������� � ���� �������� ��������),
//	��� ������ � ��������, ������������, ����-�� ������� ������ ������*/
//	class TGroupSynonyms : public SS::Core::Types::TListEnumerator<TWord>,
//		public TWord
//	{
//		/// ���������� ����������, ��������� �� ������ ������ � ������
//		bool m_blIsChecked;
//
//	public:
//
//		TGroupSynonyms(unsigned int uiSourceIndexOfWord) : TWord(uiSourceIndexOfWord)
//		{
//		};
//
//		TGroupSynonyms() : m_blIsChecked(false)
//		{
//
//		}
//		/// ������������� ���������� TGroupSynonyms::m_blIsChecked
//		void SetIsChecked(bool blIsChecked)
//		{
//			m_blIsChecked = blIsChecked;	
//		};
//
//		/// ���������� ���������� TGroupSynonyms::m_blIsChecked
//		bool GetIsChecked()
//		{
//			return m_blIsChecked;
//		};
//
//		bool operator == (const TGroupSynonyms& value)
//		{
//			return (value.m_uiSourceIndexOfWord == m_uiSourceIndexOfWord) ? true : false;
//		};
//	};
//
//	/// �������� ��������� ����� ��������� TGroupSynonyms,
//	/** � ����� �������� �����, ��� �������� ���� �������� ��� �������� */
//	class TSynonymsSplit : public SS::Core::Types::TListEnumerator<TGroupSynonyms>,
//		public TWord
//	{
//	public:
//		
//	};
//
//	typedef SS::Core::Types::TListEnumerator<TSynonymsSplit> TSynonymsSplits;
//}
//}
//}
//}
