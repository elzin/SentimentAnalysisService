//TextBlockCut.h
#pragma once
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASSInterface\IBlackBox.h"
#include "ContainersFactory.h"
#include <list>

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{
			using SS::Interface::Core::CommonContainers::IIndexAndPosition;
			using SS::Interface::Core::CommonContainers::ITextBlockCut;
			using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;
			using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;

			///"�������" �� ����������� �����, ���������� ��� ���������� ����������� ������. ��� ������ ����� ����� ���� ��������� �������
			/**
			�������� ������� �� �������, ������ ������ � ������
			*/
			class CTextBlockCut : public ITextBlockCut
			{
			private:
				std::wstring m_wsIndexTypeName;
				std::wstring m_ws;
				wchar_t* m_wszTextCut;
				wchar_t* m_wszPluginName;
				std::list<IIndexAndPosition*> m_list_pIndexAndPosition;	
				std::list<IIndexAndPosition*>::iterator m_listIter;
				unsigned int m_uiRelevance;
				IBlackBoxTextStorage*		m_pBlackBoxTextStorage;
				TLinguisticProcessorMode*	m_pLinguisticProcessorMode;

				///��������������� ������
				struct SBlockCutData
				{
					unsigned int
					TextCutType : 8,
					Level : 8,
					Number : 8;
				} m_oBlockCutData;
				///������� �����������
				CContainersFactory* m_pContainersFactory;

			public:
				//������������
				CTextBlockCut(IBlackBoxTextStorage* pBlackBoxTextStorage, TLinguisticProcessorMode*	pLinguisticProcessorMode);
				virtual ~CTextBlockCut();
				//������ ITextBlockCut
				///������� ������� (������ ��� �������)
				virtual void Clear();									
				///���������� ������� � ��������� (������� � ���� � ������ ���������)
				virtual IIndexAndPosition* AddIndexAndPosition();		
				///��������� ������� ������� ��������� (0 - ���� ���)
				virtual IIndexAndPosition* GetFirstIndexAndPosition();	
				///��������� ���������� ������� ��������� (�� �������� ������� ��������� ������� �������) (0 - ���� �����������)
				virtual IIndexAndPosition* GetNextIndexAndPosition();
				/// ���������� ���������� ����� � ���� ������ (������������ ��������� GlobalSearch)
				virtual void SetTextCut(const wchar_t* wszText);
				///���������� "�����" ���� ������� ������ ��������� �����
				void SetIndexTypeName(const wchar_t* wszName);
				///��������� "�����" ���� ������� ������ ��������� �����
				const wchar_t* GetIndexTypeName();
				/// ��������� ������������� ������ ��������� �����
				virtual unsigned int GetRelevance()
				{
					return m_uiRelevance;
				}
				/// ������������ ������������� ������ ��������� �����
				virtual void SetRelevance(unsigned int uiRelevance)
				{
					m_uiRelevance = uiRelevance;
				}
				/// ��������� ���������� ����� � ���� ������
				virtual const wchar_t* GetTextCut();
				/// ������������ "�����" �������
				virtual void SetPluginName(const wchar_t* wsName);
				/// ��������� "�����" �������
				virtual const wchar_t* GetPluginName() const;
				/// ���������� ��� ����� ���� 
				virtual SS::Core::Types::IndexationSearch::ETextCutType GetType();
				/// ������������� ��� ����� �����
				virtual void SetType(SS::Core::Types::IndexationSearch::ETextCutType eTextCutType);
				/// ���������� ������� ���������
				virtual unsigned int GetLevel();
				/// ������������� ������� ���������
				virtual void SetLevel(unsigned int uiLevel);
				/// ���������� ����� ������ ����� ���� �����
				virtual unsigned int GetNumber();
				/// ������������� ����� ������ ����� ���� �����
				virtual void SetNumber(unsigned int uiNumber);
				//������
				/// ��������� XML - ������ ����������� ����������
				std::wstring* GetXML();
				///���������� ������� �����������
				void SetContainersFactory(CContainersFactory* pContainersFactory){ m_pContainersFactory = pContainersFactory; };
			};


		}
	}
}