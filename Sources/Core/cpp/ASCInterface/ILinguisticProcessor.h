#pragma once
#include "ICommonContainers.h"
#include "TCoommonTypes.h"

#include <string>
#include <vector>

// {B3D22326-7558-4144-8C39-B9952C02403F}
static const GUID CLSID_LinguisticProcessor = 
{ 0xb3d22326, 0x7558, 0x4144, { 0x8c, 0x39, 0xb9, 0x95, 0x2c, 0x2, 0x40, 0x3f } };

// {41C0E09E-9E89-4286-BD80-54A4174E2FB4}
static const GUID IID_LinguisticProcessor = 
{ 0x41c0e09e, 0x9e89, 0x4286, { 0xbd, 0x80, 0x54, 0xa4, 0x17, 0x4e, 0x2f, 0xb4 } };


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			///��������� ������ ������
			class ILexemeBoard
			{
			public:
				ILexemeBoard() {}
				virtual ~ILexemeBoard() {}
			public:
				/// ������ ������� ��������� (���������� � ������������ ���������� ������������� ����������� ������ ������)
				virtual unsigned int GetCapacity() = 0;
				/// ������ ���������� ����������� ������ ������
				virtual unsigned int GetCount() = 0;
				/// ������� �� ������ �������, ������ 0, ���� ������ ���
				virtual unsigned int MoveFirst() = 0;
				/// ������� �� ��������� �������, ������ 0, ���� ��������� �� ��������� �������
				virtual unsigned int MoveNext() = 0;
				///	��������� �������
				virtual const wchar_t* GetLexeme() = 0;
				virtual const char* GetLexemeA() = 0;
				/// ��������� ����������� ������ ������� ������� � ������ (��������� ���������� � 0)
				virtual unsigned int GetAbsoluteIndex() = 0;
				/// ��������� ����������� ������ ������� ������� ������� �������
				virtual unsigned int GetAbsoluteSymbolIndex() = 0;
			};

			///��������� ���������� ��������� ������ ������������ �����������
			class ILexicaPrimary : virtual public SS::Interface::IBase
			{
			public:
				ILexicaPrimary() {}
				virtual ~ILexicaPrimary() {}
			public:
				///����������� ����������� � ������
				virtual void SetText(SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText, unsigned int uiStartPosition = 0) = 0;
				///�������� ��������� (� �.�. � ������) ����� ������ � ����������, ������ 0, ���� ������ �� ��������� (��� ���� ��� ����� ��� ���� �� ����� ���������)
				virtual unsigned int LoadNext(
					/// ���� ������c� � true, �� �������� ������ ���������� ��� ����� ������� �� ���������
					bool bIgnoreParagraphs = false
					) = 0;
				///������ ��������� ���������� ���������� ������ ������� ����������� ����� ������
				/**
					����������: ������������ ������ �� ��������� ILexemeBoard ���������
					�� ���� ����� ����� ������� ���������� ILexicaPrimary
				*/
				virtual ILexemeBoard* GetLexemeBoard() = 0;
			};

			/// �������� ����� �������, ��������� �� ���������������� ���������� ��� �������� ����������
			class ILinguisticIndexation
			{
			public:
				ILinguisticIndexation(){}
				virtual ~ILinguisticIndexation(){}
			public:

				///������ �������� ���������� ���������
				virtual HRESULT StartDocumentIndexation() = 0;

				/// ���������� ������� ���������� ���������� ������� ������
				virtual void Init(
					/// ��������� � ������������� �������
					SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText
					/// ��������� ���������� ������
					, SS::Core::Types::IndexationSearch::TIndexationParams* pIndexationParams
					) = 0;

				/// ���������� ������� ���������� ��������� �������
				virtual void Init(
					/// ��������� � ������������� �������
					std::list< std::list<SS::Core::Types::IndexationSearch::TNativeTextForIndexation*> > * p_l_l_NativeText
					/// ��������� ���������� ������
					, SS::Core::Types::IndexationSearch::TIndexationParams* pIndexationParams
					) = 0;

				/// ���������� ��������� ������ �������
				/**
				������:
					0 - ���� ���� ��� ����� ��� �������
					1 - ���� ������ ���
					2 - ���� ���� ������
				*/
				virtual unsigned int GenerateNext(
					/// ��������� �� ���������, ������� ���������� ���������
					SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult
					) = 0;

				///������� �������� ���������� ���������
				virtual HRESULT EndDocumentIndexation() = 0;
			};

			/// �������� ����� �������, ��������� �� ���������������� ���������� ��� �������� ������� �������
			class ILinguisticQuery
			{
			public:
				ILinguisticQuery(){}
				virtual ~ILinguisticQuery(){}
			public:
				/// ������ ������� ������������ ��� ������ ��� ��������� ������� � ���������� ���������� �� ������������ ������� 
				/**
					������������ ��� ������ ������� � ��������� �����������, ����������� �� ���� ����������� ��������� ������� SS
				*/
				virtual void GenerateQuery(
					/// ��������� ������
					SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
					/// ��������� ������� �������
					, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
					/// ���������, ������� ���������� ���������
					, SS::Interface::Core::CommonContainers::IQueryResult* pQureResult
					/// �������� ���������� ���������� ������� �������� �������
					, bool bIsRememberQuery
					) = 0;

				/// ��������� ������ �������� ����� ���� �������
				virtual void GetQuerySourceIndices(std::vector<unsigned int>* pvIndices) = 0;

				virtual void GetQueryKeywords(LPCWSTR szQuery, std::vector<std::wstring>* pKeywords, 
						std::vector<std::vector<std::wstring> >* pMorphoForms) = 0;
			};

			/// �������� ����� �������, ��������� �� ���������������� ���������� ��� �������� ������ � ������ �������������
			class ILinguisticSearch
			{
			public:
				ILinguisticSearch(){}
				virtual ~ILinguisticSearch(){}
			public:
				/// ������ ��������� ������� �������, ������� 
//				virtual void SetQueryForFurtherUpdate(SS::Interface::Core::CommonContainers::IQueryResult* pQureResult);
				/// ������������ ��������������� ������������� ����������� ������
				virtual void UpdateRelevance(
					/// ��������� � ������������ ������
					SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult
					/// ��������� � �������� ������������ (� ������ ���������, �������������� ��� ������ ILinguisticQuery)
					,SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
					/// ��������� ������� ������� (� ������ ���������, �������������� ��� ������ ILinguisticQuery)
					, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
					/// ��������� �������� �������������
					, SS::Core::Types::IndexationSearch::TUpdateRelevanceParams* pUpdateRelevanceParams
					) = 0;
				/// ������������� ���� ����, ���������� ���������
				virtual void SetTitles(SS::Interface::Core::CommonContainers::ITextBlock * pTextBlock) = 0;
			};

			/// �������� ����� �������, ��������� �� ���������������� ���������� ��� �������� ������ ���������
			class ILinguisticShowResults
			{
			public:
				ILinguisticShowResults(){}
				virtual ~ILinguisticShowResults(){}
			public:
				virtual ILexicaPrimary* GetLexicaPrimary() = 0;

				/// ��������� ������� ����� � �������
				/** 
					\param psWord - ��������� �� �����
					\return unsigned int ������ 0, ���� ����� ��� � ���� � 1 ���� ����
				*/				
				virtual unsigned int IsExistWord(
					const wchar_t* psWord
					) = 0;

				/// ���������� ���������� IIndexAndPosition ��������� �����
//				virtual void FillSourceIndices(SS::Interface::Core::CommonContainers::IIndexAndPosition* pIAP);

				/// ������ ������� ������������, ���� ��������� ������ �������� ������� ���� ��� ���������� ��������� ��������� ����
				virtual void PrepareForView(
					/// ��������� � ������������ ������
					SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult
					/// ��������� ���������� � ������ (���-�� ���������������� ����������� � �.�.)
					, SS::Core::Types::IndexationSearch::TPrepareForViewParams* pPrepareForViewParams
					) = 0;

				/// ��������� ������ �������� ����� ��� �����
				virtual void GetSourceIndices(const wchar_t* wszWord, std::vector<unsigned int>* pvIndices) = 0;
			};

			/// ������� ��������� ���������������� ����������
			/**
				�������� ��� �������� �� CLSID = CLSID_LinguisticProcessor
				��� ���������� IID = IID_LinguisticProcessor 
			*/
			class ILinguisticProcessor : public SS::Interface::IBase
			{
			public:
				ILinguisticProcessor(){}
				virtual ~ILinguisticProcessor(){}
			public:
				/// ���������� ��������� ��� ���������� ��������������� ����������
				virtual ILinguisticIndexation* GetLinguisticIndexation() = 0;
				/// ���������� ��������� ��� ���������� ���������������� ������� ������� ������������
				virtual ILinguisticQuery* GetLinguisticQuery() = 0;
				/// ���������� ��������� ��� ���������� ���������������� ������
				virtual ILinguisticSearch* GetLinguisticSearch() = 0;
				/// ���������� ��������� ��� ����������� ����������� ������
				virtual ILinguisticShowResults* GetLinguisticShowResults() = 0;
				/// ������ ��� ����������� ������ ������ ���������������� ����������
				virtual void SetMode(SS::Core::Types::IndexationSearch::TLinguisticProcessorMode* pMode) = 0;
			};
		}
	}
}