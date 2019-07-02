#pragma once
#include <list>
#include <string>

namespace SS
{
	namespace Core
	{
		namespace Types
		{
			namespace IndexationSearch
			{

#pragma pack(push,1)  // Fix packing size 
				/// ���������, ����������� ������ ��� �����������
				struct TViewIndex
				{
					int				m_DictionaryIndex;
					unsigned char	m_IDForm;
					TViewIndex() : m_IDForm(0), m_DictionaryIndex(0)
					{}
				};
#pragma pack(pop)

				///��� ���� ����
				enum ETextCutType
				{
					/// �����
					tctText,
					/// ���������
                    tctHeader,
					/// �������
                    tctTable,
					/// url-�����
					tctHttp
				};

				///��� ������� (������������ ��������)
				enum EIndexesType
				{
					///�������
					itNormal,
					///��������������
                    itAdjustment
				};

				typedef std::list<std::wstring> TAbsentWords;

				/// ��� ��������� �������
				enum EHighlightType{
					/// ������� ������
					hltNone,
					/// ����� �� �������
					hltQueryWord,
					/// ����� ������
					hltAnswerWord
				};

				///��� ���������� ����������
				enum EIndexProcessor
				{
					///���������
					ipLocal,
					///����������
					ipGlobal
				};

				/// ����� (������������ ��� ������ ������ �������, ����� ������ ������� ����������� ��� ������ ����������)
				class TNativeText
				{
				public:
					TNativeText() : m_wcText(0)	{};
					/// ������ �����
					const wchar_t* GetText()
					{
						return m_wcText;
					}
					/// ������ �����
					void SetText(const wchar_t* wc)
					{
						m_wcText = wc;
					}
				protected:
					const wchar_t* m_wcText;
				};

				/// ����������� ��������� ������ ��� ����������
				class TNativeTextForIndexation : public TNativeText
				{
				public:
					TNativeTextForIndexation() : m_wcStructure(0), m_wcMeta(0){}

					/// ������ ���������� � ��������� ������
					const wchar_t* GetTextStructure()
					{
						return m_wcStructure;
					}
					/// ������ ���������� � ��������� ������
					void SetTextStructure(const wchar_t* wc)
					{
						m_wcStructure = wc;
					}

					/// ������ ����-���������� �����-���������
					const wchar_t* GetTextInfo()
					{
						return m_wcMeta;
					}
					/// ������ ����-���������� �����-���������
					void SetTextInfo(const wchar_t* wc)
					{
						m_wcMeta = wc;
					}
				protected:
					const wchar_t* m_wcStructure;
					const wchar_t* m_wcMeta;
				};

				/// ��������� ������� �������
				class AnalyseDepthParams
				{
				protected:
					bool m_bIsMorpho;
					bool m_bIsSemantic;
					bool m_bIsSyntax;
					bool m_bIsSynonims;
				public:
					AnalyseDepthParams() : m_bIsMorpho(false), m_bIsSemantic(false), m_bIsSyntax(false), m_bIsSynonims(false) {}
				public:
					/// ������ �������/���������� ���������������� �������
					bool IsMorpho()	{return m_bIsMorpho;}
					/// ������ �������/���������� �������������� �������
					bool IsSemantic() {return m_bIsSemantic;}
					/// ������ �������/���������� ��������������� �������
					bool IsSyntax()	{return m_bIsSyntax;}
					/// ������ �������/���������� ������� �� ��������
					bool IsSynonims() {return m_bIsSynonims;}

					/// ��������� �������/���������� ���������������� �������
					void SetIsMorpho(bool bIsMorpho){m_bIsMorpho = bIsMorpho;}
					/// ��������� �������/���������� �������������� �������
					void SetIsSemantic(bool IsSemantic) {m_bIsSemantic = IsSemantic;}
					/// ��������� �������/���������� ��������������� �������
					void SetIsSyntax(bool bIsSyntax) {m_bIsSyntax = bIsSyntax;}
					/// ��������� �������/���������� ������� �� ��������
					void SetIsSynonims(bool IsSynonims) {m_bIsSynonims = IsSynonims;}
				};


				/// ���������, ������������ ���������������� ���������� ��� ����������
				class TIndexationParams
				{
				};

				
				///	��������� ��� ������ ��������������� ������� (NdxQuery.dll)
				struct TQueryParametrizerSettings
				{
				public:
					///	ctr
					TQueryParametrizerSettings():
						ndxq_EnableObligatoryFlag(1)	//	�� ��������� ��������
						,ndxq_EnableUnionsWords(1)		//	�� ��������� ��������
					{}

					unsigned int
						///	�������� ���� �������������� ��� ���
						///	(������������� ���� ���� � ������ ������ � �������������������)
						ndxq_EnableObligatoryFlag	: 1,
						///	��������� union-����� (��������� ���������� � ��� � ������������������)
						///	��� ���
						ndxq_EnableUnionsWords		: 1;
				};

				/// ��������� ������, ������������ � ���������� ������
				class TSearchParams
				{
				public:
					/// ��� ������� ������
					enum ESearchArea
					{
						/// ������� �����
						saNormal,
						/// ����� � ������������
						saEncyclopedia
					};

					/// ��� ������� ������
					ESearchArea m_SearchArea;

					/// ��� ����� ������� (������������ ��� Glo)
					enum ESearchLanguage
					{
						/// �������
						slRus,
						/// ����������
						slEng,
						slChinese,
						slSpanish,
						slPushtu,
						slEsperanto
					};

					/// ���� �������
					ESearchLanguage m_SearchLanguage;

					///������ ������ � ���������
					enum ESearchInObtainedMode
					{
						esiomNone,
						///�� � ����� ��������� �������
						esiomText
					};
					///��� ������ � ���������
					ESearchInObtainedMode m_SearchInObtainedMode;

					TSearchParams(int uiMaxSearchResultsCount=0)
						: m_uiMaxSearchResultsCount(uiMaxSearchResultsCount)
						, m_SearchArea(saNormal)
						, m_bForceOrSearch(false)
						, m_SearchInObtainedMode(esiomNone)
						, m_SearchLanguage(slRus)
					{};

					///����������� �� ���������� ��������� �����������
					unsigned int m_uiMaxSearchResultsCount;

					bool m_bForceOrSearch;

					///	��������� ��� ������ NdxQuery (�������������� ��������)
					TQueryParametrizerSettings	m_QPSettings;
				};

				/// ������ ����������/������� ������� ������
				enum ESearchDepth
				{
					/// ����������� ����� - ��� ����������
					sdNormal,
					/// ����� ������ �� ��������� (���� ��������������)
					sdStrict,
					/// ����� � ������ ��������� ���� (���� ��������������)
					sdSynonyms,
					/// ����� � ������������� ������������ ����
					sdRejectUnimportant
				};

				/// ����� ������
				enum EAnswerMode
				{
					/// �������������� - ������������ ��������������� ����������� �� ���� �������
					amAuto,
					/// �������������� ����� �� �������� ������
					amOnlyKeywords
				};

				/// ����� ��������� �������
				enum EGenerateQueryMode
				{
					/// ������������ �������� �������
					gqmIndex,
					/// ������������ ������
                    gqmString					
				};

				/// ��������� ������� ������� ������������
				class TQueryParams
				{
				public:
					TQueryParams()
						: m_SearchDepth(sdNormal)
						, m_AnswerMode(amAuto)
						, m_bIgnoreAbsentWords(false)
						, m_wcQuery(L"")
						, m_GenerateQueryMode(gqmIndex)
					{
					}

					/// ���� � ���, �� ������� ������������� ���� ������������
					bool m_bIgnoreAbsentWords;

					/// ������ ����������/������� ������� ������
					ESearchDepth m_SearchDepth;
					/// ����� ������
					EAnswerMode m_AnswerMode;
					/// ����� ��������� �������
					EGenerateQueryMode m_GenerateQueryMode;

					const wchar_t* GetQuery()
					{
						return m_wcQuery;
					}
					/// ������ �����
					void SetQuery(const wchar_t* wc)
					{
						m_wcQuery = wc;
					}
				protected:
					const wchar_t* m_wcQuery;
				};

				/// ���������, ������������ ���������������� ���������� ��� ���������� ����������� ������ � �����������
				struct TPrepareForViewParams
				{
					/// ����� ������� ITextBlock, ����������� ���������
					unsigned int m_uiFirstProcessedTextBlockNumber;
					/// ���������� ITextBlock, ���������� ���������
					unsigned int m_uiProcessedTextBlockCount;
				};

				/// ���������, ������������ ���������������� ���������� ��� �������� ��������������� �������������
				class TUpdateRelevanceParams
				{
				};

				/// ����� ������ ���������������� ����������
				class TLinguisticProcessorMode
				{
					AnalyseDepthParams m_AnalyseDepthParams;
				public:
					TLinguisticProcessorMode() : m_bIsLiteMode(false)
					{
					}

					bool m_bIsLiteMode;
					/// ��������� ������� �������
					AnalyseDepthParams* GetAnalyseDepthParams()
					{
						return &m_AnalyseDepthParams;
					}

					void Init()
					{
						m_bIsLiteMode = false;
					}
				};
			}
		}
	}
}