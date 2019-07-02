// ICommonContainers.h

#pragma once

#include "ITextFeature.h"
#include "tcoommontypes.h"
//������ �� �� ����� ��-����� �� �����������!


// {DC26B1F5-F463-4419-BC5D-0F3E5E704057}
static const GUID CLSID_IndexationResult = 
{ 0xdc26b1f5, 0xf463, 0x4419, { 0xbc, 0x5d, 0xf, 0x3e, 0x5e, 0x70, 0x40, 0x57 } };
// {DE2B93EE-1329-4020-9BE1-DC141EC2DCFA}
static const GUID IID_IndexationResult = 
{ 0xde2b93ee, 0x1329, 0x4020, { 0x9b, 0xe1, 0xdc, 0x14, 0x1e, 0xc2, 0xdc, 0xfa } };
// {1D50D5DD-DBC3-4793-95F2-C162F4F1CB3B}
static const GUID CLSID_QueryResult  = 
{ 0x1d50d5dd, 0xdbc3, 0x4793, { 0x95, 0xf2, 0xc1, 0x62, 0xf4, 0xf1, 0xcb, 0x3b } };
// {3BAB5827-C836-4284-9300-D46F666DE78F}
static const GUID IID_QueryResult  = 
{ 0x3bab5827, 0xc836, 0x4284, { 0x93, 0x0, 0xd4, 0x6f, 0x66, 0x6d, 0xe7, 0x8f } };
// {D9B2AED8-ACC6-45c0-A220-7268E2F2CCEB}
static const GUID CLSID_SearchResult  = 
{ 0xd9b2aed8, 0xacc6, 0x45c0, { 0xa2, 0x20, 0x72, 0x68, 0xe2, 0xf2, 0xcc, 0xeb } };
// {0B4797BB-95F1-47d9-A8A0-DEF9B6803F4A}
static const GUID IID_SearchResult  = 
{ 0xb4797bb, 0x95f1, 0x47d9, { 0xa8, 0xa0, 0xde, 0xf9, 0xb6, 0x80, 0x3f, 0x4a } };


namespace SS
{
  namespace Interface
  {
	namespace Core
	{
		namespace CommonContainers
		{
			class ITextBlock;
			class ITextBlockCut;
			class ITextFeature;
			class IIndexAndPosition;
			class IIndexationIndex;
			class IServiceIndex;

			/// �������� ������� �������
			struct SQueryIndexAttributes
			{
				unsigned int
				///������������� ������������� �������
				m_TransformationID : 8,
				///������������� ������������������ �������
				m_SequenceID : 8,
				///������� �������
				m_IndexPosition : 8,
				///������������� ����� ����, 
				//���� ����� ���������� � ����, � ���������� ���������� ������������ ���� �� N ���� �� �����
				m_WordsBlockID : 6,
				//� ������ ������ ���� ��������������
				m_Obligatory : 1,
				//���� �������� ������				
				m_bAnswerIndex : 1;
				
				SQueryIndexAttributes(void):
					m_TransformationID(0xff),
					m_SequenceID(0xff),
					m_WordsBlockID(0),
					m_IndexPosition(0xff),
					m_Obligatory(0),
					m_bAnswerIndex(0){};
			};

			/// "������ �������" ������������� ������ ������� � ���������� ����������
			class IQueryIndex // ��� ������� ������ ����� �������� *IItem
			{																						// ���������� �������� � *IQueryIndex
			public:
				virtual ~IQueryIndex(){};
				/// ��������� ����� ������� (���� ��� ������ � ����������� ������)
				virtual const wchar_t* GetQueryWord() = 0;
				/// ��������� ����� ������� (���� ��� ������ � ����������� ������)
				virtual void SetQueryWord(const wchar_t* wszWord) = 0;

				/// ��������� �������
				virtual unsigned int GetQueryIndex() = 0;
				/// ������������ �������
				virtual void SetQueryIndex(unsigned int uiIndex) = 0;

				///���������� ��� �������
				virtual float GetIndexWeight(void) = 0;
				///������������� ��� �������
				virtual void SetIndexWeight(float fWeight) = 0;
				///���������� ���������
				virtual SQueryIndexAttributes GetAttributes(void) = 0;
				///������������� ���������
				virtual void SetAttributes(SQueryIndexAttributes oAttributes) = 0;
				///���������� �������� �����
				virtual const char GetOperator() = 0;
				///������������� �������� �����
				virtual void SetOperator(char chOperator) = 0;
				/// ��������� ���-�� ������ �����
				virtual const unsigned int GetLeftBrackets() = 0;
				///	��������� ���-�� ������ ������
				virtual const unsigned int GetRightBrackets() = 0;
				/// ������������ ���-�� ������ �����
				virtual void SetLeftBrackets(unsigned int uiBracketCount) = 0;
				/// ������������ ���-�� ������ ������
				virtual void SetRightBrackets(unsigned int uiBracketCount) = 0;
			};

			/// "��������� ������" ��������� ������������ ��� ������ ������������ ������� � ������������ �������� ��� ������
			class IQueryResult : public SS::Interface::IBase
			{	
			public:
				virtual ~IQueryResult(){};
				/// ������� ��������� (������� ��� �������)
				virtual void Clear() = 0;
				/// ���������� ������� � ��������� (������� ���� ������ � ������ ��������� �� ����)
				virtual IQueryIndex* AddQueryIndex() = 0;

				/// ��������� ������� ������� ��������� (0 - ���� ���)
				virtual IQueryIndex* GetFirstQueryIndex() = 0;
				/// ��������� ���������� ������� ��������� (�� �������� ������� ��������� ������� �������) (0 - ���� �����������)
				virtual IQueryIndex* GetNextQueryIndex() = 0;
				/// ������ ������ ������������� ����
				virtual SS::Core::Types::IndexationSearch::TAbsentWords* GetAbsentWords() = 0;
			};
			
			/// "��������� ������" ��������� ������������ ��� ������ ������������ ������
			class ISearchResult : public SS::Interface::IBase
			{
			public:
				virtual ~ISearchResult(){};

				/// ������ ���������� ����������� ������
				virtual unsigned int Count() = 0;

				/// ��������� ����� ������ ����������� 
				/**
				���� �������� � true, �� ���������� ������������ ���������������� �� ������������� �� ���������
				� ��������� ������, ������� �������� �� �����
				*/
				virtual void SetSortedMode(bool bOn) = 0;

				/// ������� ��������� (������� ��� ��������� �����)
				virtual void Clear() = 0;
				/// ���������� ���������� ����� � ��������� (������� ���� ���� � ������ ��������� �� ����)
				virtual ITextBlock* AddTextBlock() = 0;

				/// ��������� ������� ���������� ����� ��������� (0 - ���� ���)
				virtual ITextBlock* GetFirstTextBlock() = 0;
				/// ��������� ���������� ���������� ����� ��������� (�� �������� ������� ��������� ������� ���������� �����) (0 - ���� �����������)
				virtual ITextBlock* GetNextTextBlock() = 0;
				/// ������ ��������� ������ ��� ������������ �������
				/**
					���� ����� ������������, ������ ����
					����� ������� ���������� �������� �� ��������������� ������� - ���, ��� �������� GetNextTextBlock() ����� �������� ��������� ���������
					��������� ����� ���������� 
					nPosition ���������� � 0
				*/
				virtual ITextBlock* GetTextBlock(unsigned int nPosition) = 0;

				virtual bool GetXML(std::wstring* pXML) = 0;
				virtual bool GetXML(std::wstring* pXML, int iFirst, int iCount) = 0;
				virtual void SetRequestID(unsigned int id) = 0;
				virtual unsigned int GetRequestID() = 0;
				//���������� ��������� �� xml (������ ����� ������� ����� TextBlock)
				virtual void SetGsXML(const wchar_t* wzXml) = 0;
			};

			// "��������� ���������" ��������� ������������ ��� ������ ������������ ������� � ������������ �������� ��� ����������
			/**
				�������� ����� �������� ������, ������� ���� ����������������
				������ ���� ������������� ������ ������ 
			*/
			class IIndexationResult : public SS::Interface::IBase
			{
			public:
				virtual ~IIndexationResult(){};
				// ������� ��������� (������� ��� ��������� �����)
				virtual void Clear() = 0;
				// ���������� ���������� ����� � ��������� (������� ���� ���� � ������ ��������� �� ����)
				virtual ITextBlock* AddTextBlock() = 0;

				// ��������� ������� ���������� ����� ��������� (0 - ���� ���)
				virtual ITextBlock* GetFirstTextBlock() = 0;
				// ��������� ���������� ���������� ����� ��������� (�� �������� ������� ��������� ������� ���������� �����) (0 - ���� �����������)
				virtual ITextBlock* GetNextTextBlock() = 0;
			};

			/// "��������� ����". ������������ ��� ��� ����������, ��� � ��� ������
			/**
				�������� ��������� ����� ������ � ���������� �� �������������� ������ � ����������� ����
				����������� ���������:
				= ��� ����������
					��� ���������� ������ ��������� ���� �������� �� ����� �������, � ������� ���� ������ ��� �������
				= ��� ������
					����� ������ �������� ���� ��� ����� �������, ���������� �������� (��� ���������) ���������� ������
					��� ������� ������������ ��� �����������, � ����� ��� ����-������� �������������
			*/
			class ITextBlock
			{
			public:
				virtual ~ITextBlock(){};
				// �������������� ������, �������� ����������� ��� ��������� ����
				/**
					��� ������ ������ ������� ������ ��������� �������������
					��� ���������� ������ ��������� �������������� ��������� �� ���� ����������� ��������� �������
				*/
				virtual ITextFeature* GetTextFeature() = 0;

				/// ������� ����� (������ ��� ������� �� ������)
				virtual void Clear() = 0;
				/// ������� ������� � ��������� (������� ���� � ������ ������)
				virtual ITextBlockCut* AddBlockCut() = 0;

				/// ��������� ������ ������� ��������� (0 - ���� ���)
				virtual ITextBlockCut* GetFirstBlockCut() = 0;
				/// ��������� ��������� ������� ��������� (0 - ���� �����������)
				virtual ITextBlockCut* GetNextBlockCut() = 0;

				/// ��������� ������������� ������� ���������� �����
				virtual unsigned int GetRelevance() = 0;
				/// ������������ ������������� ������� ���������� �����
				virtual void SetRelevance(unsigned int uiRelevance) = 0;
				/// ��������� XML-������ ����������� ����������
				virtual std::wstring* GetXML() = 0;

				SS::Core::Types::IndexationSearch::EIndexProcessor m_IndexProcessorMark;
			};

			/// "�������" �� ����������� �����, ���������� ��� ���������� ����������� ������. ��� ������ ����� ����� ���� ��������� �������
			/**
				�������� ������� �� �������, ������ ������ � ������
			*/
			class ITextBlockCut
			{
			public:
				virtual ~ITextBlockCut(){};
				/// ������� ������� (������ ��� �������)
				virtual void Clear() = 0;
				/// ���������� ������� � ��������� (������� � ���� � ������ ���������)
				virtual IIndexAndPosition* AddIndexAndPosition() = 0;

				/// ��������� ������� ������� ��������� (0 - ���� ���)
				virtual IIndexAndPosition* GetFirstIndexAndPosition() = 0;
				/// ��������� ���������� ������� ��������� (�� �������� ������� ��������� ������� �������) (0 - ���� �����������)
				virtual IIndexAndPosition* GetNextIndexAndPosition() = 0;

				/// ��������� ������������� ������ ��������� �����
				virtual unsigned int GetRelevance() = 0;
				/// ������������ ������������� ������ ��������� �����
				virtual void SetRelevance(unsigned int uiRelevance) = 0;

				/// ���������� ���������� ����� � ���� ������ (������������ ��������� GlobalSearch)
				virtual void SetTextCut(const wchar_t* wszText) = 0;
				/// ��������� ���������� ����� � ���� ������
				virtual const wchar_t* GetTextCut() = 0;

				///���������� "�����" ���� ������� ������ ��������� �����
				virtual void SetIndexTypeName(const wchar_t* wszName) = 0;
				///��������� "�����" ���� ������� ������ ��������� �����
				virtual const wchar_t* GetIndexTypeName() = 0;
				
				/// ������������ "�����" �������
				virtual void SetPluginName(const wchar_t* wsName) = 0;
				/// ��������� "�����" �������
				virtual const wchar_t* GetPluginName() const = 0;
				
				/// ���������� ��� ����� ���� 
				virtual SS::Core::Types::IndexationSearch::ETextCutType GetType() = 0;
				/// ������������� ��� ����� �����
				virtual void SetType(SS::Core::Types::IndexationSearch::ETextCutType eTextCutType) = 0;
				/// ���������� ������� ���������
				virtual unsigned int GetLevel() = 0;
				/// ������������� ������� ���������
				virtual void SetLevel(unsigned int uiLevel) = 0;
				/// ���������� ����� ������ ����� ���� �����
				virtual unsigned int GetNumber() = 0;
				/// ������������� ����� ������ ����� ���� �����
				virtual void SetNumber(unsigned int uiNumber) = 0;

				/// ��� ������������� ������� � ��������� �� ����� (����� ����� 100 ���������)
				unsigned int m_IndexesPercentage;
				/// ��� ������������� �������
				SS::Core::Types::IndexationSearch::EIndexesType m_IndexesType;
			};

			/// "������ �� �������" ������ �� ����� ������� � ������
			/**
				�������� � ���� ������������� � ����������� �������, ��������������� �� ����� ������� ���������� �����.
				������������ ��� ���������� � ��� ������
			*/
			class IIndexAndPosition
			{
			public:

				virtual ~IIndexAndPosition(){};
				/// ��������� ������� ������� � ��������� �����
				virtual unsigned int GetPosition() = 0;
				/// ������������ ������� ������� � ��������� �����
				virtual void SetPosition(unsigned int uiPosition) = 0;

				/// ��������� ����������� ������ � ������ ������� ������� �����
				virtual unsigned int GetFirstCharPosition() = 0;
				/// ������������ ����������� ������ � ������ ������� ������� �����
				virtual void SetFirstCharPosition(unsigned int uiPosition) = 0;

				/// ������ ����������� ������
				virtual IServiceIndex* GetServiceIndex() = 0;
				/// ������ ������������� ������
				virtual IIndexationIndex* GetIndexationIndex() = 0;

				/// ������������ �����
				virtual void SetWord(const wchar_t* szWord) = 0;
				///������ ���� ����� (��� ������ ������������)
				virtual const wchar_t* GetWord() = 0;

				/// ������ ��� ��������� �������
				virtual SS::Core::Types::IndexationSearch::EHighlightType GetHighlightType() = 0;
				/// ��������� ��� ��������� �������
				virtual void SetHighlightType(SS::Core::Types::IndexationSearch::EHighlightType hlt) = 0;

				/// ������ ��� ��������� �������
				virtual unsigned int GetIsInAnswerSentence() = 0;
				/// ��������� ��� ��������� �������
				virtual void SetIsInAnswerSentence(unsigned int uiIn) = 0;
			};

			/// "����������� ������" ������������� ������, �����������/����������� � ��������� ����
			/**
				������ ������ � ������ IIndexAndPosition (�.�. �� ����� �������-���� ����� ������)
				����������� �������� � ���� ������ ��� �����������, � ����� ����� �������� ����� �������������� ����������� ����������
			*/
			class IServiceIndex
			{
			public:
				virtual ~IServiceIndex(){};
				/// ������ ������ ��� �����������
				virtual SS::Core::Types::IndexationSearch::TViewIndex* GetViewIndex() = 0;
				/// ������ ����� �������������� ���������� 
				virtual void GetInfoBuff(char** ppBuff, unsigned int* pSize) = 0;
				/// ������� ���� ����� �������������� ���������� 
				virtual void SetInfoBuff(char* pBuff, unsigned int Size) = 0;
			};

			/// "������������� ������" ������������� ������, ������������� ��������� �����������
			/**
				������ ������ � ������ IIndexAndPosition (�.�. �� ����� �������-���� ����� ������)
				����� �������� � ���� ��������� �������� �������� - ������ �� ��� ���������������� �� ����� � ��� �� �������
			*/
			class IIndexationIndex
			{
			public:
				virtual ~IIndexationIndex(){};
				/// ��������� ������� ������� ��������� (0 - ���� ���)
				virtual unsigned int GetFirstIndex() = 0;
				/// ��������� ���������� ������� ��������� (0 - ���� �����������)
				virtual unsigned int GetNextIndex() = 0;

				/// ������� ��������� (������ ��� �������)
				virtual void Clear() = 0;
				/// ���������� ������� � ���������
				virtual void AddIndex(unsigned int uiIndex) = 0;
			};

	  }
	}
  }
}