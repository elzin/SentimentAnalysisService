/*

=================== ������ ���������� ���������� NdxProcessor.dll =======================
-	�������� ��� ������� ��������� ������ 
virtual HRESULT	INdxSearchEngineFind::Find(
	const wchar_t* wszIndexStorageName,
	SS::Interface::Core::CommonContainers::IQueryResult* pQueryResult, 
	SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
	CNdxSearchSettings* pSearchSettings) = 0;
�� "SS::Interface::Core::NdxSE::IParametrizedQuery*	pPrmQueryResult"



���� NdxProcessor\search_factory.h, .cpp
-	�������� ����������� ������ CSearchFactory: �������� �������� 
"SS::Interface::Core::CommonContainers::IQueryResult* pQueryResult"
�� 
"SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult"


���� NdxProcessor\es_filler.h
-	����� �� ������ ������ es_filler.h\CESFillerEx, �� �������� ����������� CESFillerFromQuery


���� NdxProcessor\es_filler_query.h, .cpp
-	�������� ����������� ������ CESFillerFromQuery, ����� � �������� 
������ �� ���������� �� �������� IParametrizedQuery, 
������ ���:
CESFillerFromQuery(CEvalFactory* pEvalFactory, 
	SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult,
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* pIndexStorage, bool bFillOnlyObligatory);


r_logic.h, .cpp
-	�������� �������� ������ virtual void SetQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQueryResult);


���� hdr_logic.h, .cpp
-	�������� ��� ��������� ������ SetQuery � IQueryResult �� IParametrizedQuery,
�� ����� � ���� ������ ������ ����� �������� �� NULL �� ����������


=================== ������ �������� NdxStub.dll =======================

������ ������ CNdxStub::Find �������� �������������� ������� �� IQueryResult � IParametrizedQuery,
� ������� ������ NDxQuery.dll
*/