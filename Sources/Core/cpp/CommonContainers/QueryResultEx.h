#pragma once

#include "./QueryResult.h"
#include "..\ASSInterface\IQueryResultEx.h"
#include "../ASSInterface/IBlackBoxQuery.h"
#include "../ASSInterface/IDictionaryManager.h"

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			using SS::Interface::Core::CommonContainers::IQueryResultEx;

			using SS::Interface::Core::BlackBox::Query::IQuery;
			using SS::Interface::Core::BlackBox::Query::ITransformation;
			using SS::Interface::Core::BlackBox::Query::IGroup;
			using SS::Interface::Core::BlackBox::Query::IQueryUnit;
			using SS::Interface::Core::BlackBox::Query::IQueryUnitIndexCollection;
			using SS::Interface::Core::BlackBox::Query::IQueryUnitIndex;

			using SS::Core::Types::IndexationSearch::TQueryParams;
			using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;

			/// ��������� ���������������� IQueryResult + ��� ���������� �� IQuery
			class CQueryResultEx : public IQueryResultEx, public CQueryResult
			{
			private:
				IQuery*			m_pQuery;
				unsigned int	m_uiQueryUnitID;
				bool			m_IsSynonimCollection;
				bool			m_IsMorphoCollection;
				///���������� ���  �������� ������ ������ ���� ����
				bool			m_bOneUnit;
				//��������� ��� ������ � SequenceID
				struct SDataID
				{
					unsigned int uiRealSequenceID;
					unsigned int uiVirtualSequenceID;
					unsigned int uiTransformationID;
					bool		 bChangeRealSequenceID; 
					bool		 bChangeTransformID;
					//�������� ���������� �� IQueryUnit-�
					bool		 IsObligatory;
					//���������� ����� ��� ������ �������������
					unsigned int uiGroupCount;
					//��� ����� �������
					float fUnitWeight;
					//��������� ��������� ID
					void DataIdToZero();
					//������ SequenceID
					unsigned int GetSequenceID();

					void Init() 
					{
						uiRealSequenceID = 0;
						uiVirtualSequenceID = 0;
						uiTransformationID = 0;
						bChangeRealSequenceID = false;
						bChangeTransformID = false;
						IsObligatory = false;
						uiGroupCount = 0;
						fUnitWeight = 0.0;		
					};
				} m_oDataID;
				///�������(��� ��������� ������)
				SS::Interface::Core::Dictionary::IDictionary* m_pDictionary;
				///����� ������� �� QueryUnit-�
				std::wstring m_strWord;
				
				//����������� ������
				void ApplyCollections(IQueryUnitIndexCollection* pQueryUnitIndexCollection, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast);
				void ApplyUnits(IQueryUnit* pQueryUnit, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast);
				void ApplyGroups(IGroup* pGroup, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast);
				void ApplyTransform(ITransformation* pTransformation, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast);
				//���������
				TQueryParams				m_QueryParams;
				TLinguisticProcessorMode	m_LinguisticProcessorMode;
				//����������� ������
				bool ApplyLinguisticProcessorMode(IQueryUnitIndexCollection* pCollection);
				///���������� ������� ��������� �������-�������� � Unit - �
				void SearchSynonimCollection(IQueryUnit* pQueryUnit);
				///���������� ������� �����-��������� � Unit-�
				void SearchMorphoCollection(IQueryUnit* pQueryUnit);
				///����� ������(�������� �����)
				void Show();
				///����� ���� �������(�������� �����)
				void ShowWords();
				///����������� ����� �������
				void FindQueryWord(IQueryUnit* pQueryUnit);
				///������� ���������� Unit-�� � ����� ������
				void ControlCountUnitInGroup(IGroup* pGroup);
				
			public:
				//������������
				CQueryResultEx();
				virtual ~CQueryResultEx();
				//������ IQueryResultEx
				///����������� ������ (IQuery) � ������ CQueryIndex - ��
				virtual void SetIQuery(IQuery* pQuery);
				///������� IQuery �������������� � ������� SetIQuery
				virtual IQuery* GetIQuery();
				///������������ ���������� �������
				virtual void SetQueryParams(TQueryParams* pQueryParams);
				///������������ ������ ���������������� ����������
				virtual void SetLinguisticProcessorMode(TLinguisticProcessorMode* pLinguisticProcessorMode);
				//������������� ����� IBase
				virtual HRESULT QueryInterface(REFIID pIID, void** pBase);	//���������� � ���������� � �������� REFIID. 
																			//pBase ����� NULL, ���� ������ ��������� �� ��������������
				///������������� ����� �� CBaseCoreClass
				virtual void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
			};

		}
	}
}