#pragma once

#include "..\..\cpp\ASSInterface\IBlackBox.h"
#include "StringService.h"

namespace LinguisticsKernel
{
	public ref class CWord
	{
	public:
		enum class EIndexType
		{
			eitMorpho=0,	
			eitSyntax=1,	
			eitSemantic=2,	
			eitSynonim=3,	
		};

		CWord(SS::Interface::Core::BlackBox::IUnit* pUnit, CStringService^ pStringService);
		CWord(SS::Interface::Core::BlackBox::Query::IQueryUnit* pQueryUnit, bool bQuestion, CStringService^ pStringService);
		~CWord(void);

		///��������� ����� ������ �������
		void Compare(CWord^ pWord, System::Windows::Forms::TreeNode^ pTNWord, System::Windows::Forms::TreeNode^ pCommonTNWord);
		///��������� �������� �������� � �����
		void ExtractIndexes(CWord^ pWord);
		///���������� ������ �������� �� ����
		System::Collections::ArrayList^ GetIndexesByType(CWord::EIndexType IndexType) {
				return safe_cast<System::Collections::ArrayList^>(m_parrIndexes[ (int) IndexType ]);
		};
		///��������� ������� ����� � ���� ������
		void AddToNodeIndexes(System::Windows::Forms::TreeNode^ pTN);
		///��������� ����� � ���� ������
		System::Windows::Forms::TreeNode^ AddWordToNode(System::Windows::Forms::TreeNode^ pTN);

		///���������� ��������� �������������
		property System::String^ Word {
			System::String^ get() {
				 return m_psWord;
			};
		};
		///���������� ���� ��������������� �����
		///������������� ���� ��������������� �����
		property bool IsQuestion {
			bool get() {
				 return m_bQuestion;
			};
			void set(bool value) {
				m_bQuestion = value;
			};
		};		
		///���������� ��������� ���� ��������� � ������
		property System::Collections::ArrayList^ SameWords{
			System::Collections::ArrayList^ get() {
				 return m_parrSameWords;
			};
		};

	protected:
		///��������� ��������� ��������
		void Compare(System::Collections::ArrayList^ pLeftIndexes, System::Collections::ArrayList^ pRightIndexes, System::Collections::ArrayList^ pSameIndexes, System::Collections::ArrayList^ pDifIndexes);
		///��������� �������� �������� ����� � ���� ������
		void AddToNode(System::Collections::ArrayList^ pSameIndexes, System::Collections::ArrayList^ pDifIndexes, System::Windows::Forms::TreeNode^ pTN, CWord::EIndexType IndexType);
		///��������� ������ � ���� ������
		void AddIndexToNode(System::UInt32 Index, CWord::EIndexType IndexType, System::Drawing::Color ForeColor, System::Windows::Forms::TreeNode^ pTN);

		///��������� �������������
		System::String^ m_psWord;
		///��������� ��������
		System::Collections::ArrayList^ m_parrIndexes;
		///���� ��������������� �����
		bool m_bQuestion;
		///��������� ���� ��������� � ������
		System::Collections::ArrayList^ m_parrSameWords;
		///��������������� �������� � ������
		CStringService^ m_pStringService;
		///���� ����� ��� �����������
		System::Drawing::Color m_WordColor;
	};


	public ref class CTreeComparator
	{
	public:
		CTreeComparator(void);
		~CTreeComparator(void);
		
		///������������ ������ � ������� ����
		void SetLeftWords(SS::Interface::Core::BlackBox::IText* pLeftText){if(pLeftText) Convert(pLeftText, m_pLeftWords);};
		///������������ ������ � ������� ����
		void SetRightWords(SS::Interface::Core::BlackBox::IText* pRightText){if(pRightText) Convert(pRightText, m_pRightWords);};
		///������������ ������ � ������� ����
		void SetLeftWords(SS::Interface::Core::BlackBox::Query::IQuery* pLeftQuery){if(pLeftQuery) Convert(pLeftQuery, m_pLeftWords);};
		///������������ ������ � ������� ����
		void SetRightWords(SS::Interface::Core::BlackBox::Query::IQuery* pRightQuery){if(pRightQuery) Convert(pRightQuery, m_pRightWords);};
		///��������� ����������� �������� ���� ��������
		void Compare(System::String^ pQuery, System::Windows::Forms::TreeView^ pComparationTree, System::Windows::Forms::TreeView^ pCoincidenceTree);
		
	protected:
		///������������ IText � ������ CWord
		void Convert(SS::Interface::Core::BlackBox::IText* pText, System::Collections::ArrayList^ pWords);
		///������������ IQuery � ������ CWord
		void Convert(SS::Interface::Core::BlackBox::Query::IQuery* pQuery, System::Collections::ArrayList^ pWords);
		
		///��������� ��������� ���� � ����� ������
		System::Collections::ArrayList^ m_pLeftWords;
		///��������� ��������� ���� � ������ ������
		System::Collections::ArrayList^ m_pRightWords;
		///��������������� �������� � ������
		CStringService^ m_pStringService;
	};

}