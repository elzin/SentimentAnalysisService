//ServiceIndex.h

#pragma once

#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASSInterface\IBlackBoxUnit.h"
#include "..\ASSInterface\IBlackBox.h"
#include "..\ASCInterface\TCoommonTypes.h"
#include "..\ASSInterface\TDictionaryManager.h"
#include <list>

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{

			///����� ��������� ���������������� �������������� ������ � ����� � �������
			///�����������: ������ �� ����� ���� �������, ������������������ ������� ������ ����������
			class CBufferServiceIndex
			{
			private:
				char* m_pBuff;
				unsigned int m_iSize;
				unsigned int m_iPos;
			
			public:
				CBufferServiceIndex() : m_pBuff(NULL), m_iSize(0), m_iPos(0) {};
				//����������
				~CBufferServiceIndex() 
				{
					if (m_pBuff) 
					{ delete [] m_pBuff; }
				};
				//��������� ������ ��� ����� �����(��� ���� ������ ������������) 
				void Allocate(unsigned int iSize)
				{
					m_iSize = iSize;
					m_iPos = 0;
					if (m_pBuff)
					{ delete [] m_pBuff; }
					m_pBuff = new char[m_iSize];
				}
				//���������� � ����� ������
				void PutToBuffer(void* pData, unsigned int iSizeData)
				{
					if ( (!pData) || (iSizeData == 0) || ((m_iPos + iSizeData) > m_iSize) )
					{ SS_THROW(L"������������ ���������� � �����."); }
					
					memcpy(m_pBuff + m_iPos, pData, iSizeData);
					m_iPos += iSizeData;
				}
				//������ ������ �� ������
				void GetFromBuffer(void* pData, unsigned int iSizeData)
				{
					if ( (!pData) || (iSizeData == 0) || ((m_iPos + iSizeData) > m_iSize) )
					{ SS_THROW(L"������������ ���������� �� ������."); }
					
					memcpy(pData, m_pBuff + m_iPos, iSizeData);
					m_iPos += iSizeData;
				}
				//���������� ����� ��� ������ �� ����
				void SetBuffer(char* pBuff, unsigned int iSize)
				{
					if (m_pBuff)
					{ delete [] m_pBuff; }
					m_pBuff = pBuff;
					m_iSize = iSize;
					m_iPos = 0;
				}
				//�������� �����
				char* GetBuffer()
				{
					return m_pBuff;
				}
				//����� ��������
				void Reset()
				{
					m_pBuff = NULL;
					m_iSize = 0;
					m_iPos = 0;
				}
				//��������==
				bool operator==(const char* pBuff)
				{
					return (m_pBuff == pBuff);
				}
			};
			
			///"����������� ������" ������������� ������, �����������/����������� � ��������� ����
			/**
			������ ������ � ������ IIndexAndPosition (�.�. �� ����� �������-���� ����� ������)
			����������� �������� � ���� ������ ��� �����������, � ����� ����� �������� ����� �������������� ����������� ����������
			*/
			
			using SS::Core::Types::IndexationSearch::TViewIndex;
			using SS::Interface::Core::BlackBox::IUnit;
			using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;
			using SS::Core::Types::IndexationSearch::TLinguisticProcessorMode;			

			class CServiceIndex : public SS::Interface::Core::CommonContainers::IServiceIndex
			{
			private:
				CBufferServiceIndex			m_oBuffer;
				IUnit*						m_pUnit;
				IBlackBoxTextStorage*		m_pBlackBoxTextStorage;
				TViewIndex					m_oViewIndex;
				TLinguisticProcessorMode*	m_pLinguisticProcessorMode;
			
			private:
				///������� ��� �������
				void Clear();
				///��������� � ����� �������� �� Unit
				void GetIndexesFromUnit(std::list<TViewIndex> & lstViewIndex, bool bOnlyFirst = false);
			
			public:
				//������������
				CServiceIndex(IUnit* pUnit, TLinguisticProcessorMode* pLinguisticProcessorMode, IBlackBoxTextStorage* pBlackBoxTextStorage);
				virtual ~CServiceIndex();
				///������ IServiceIndex
				///������ ������ ��� ����������� (����� ���������� ���������)
				virtual SS::Core::Types::IndexationSearch::TViewIndex* GetViewIndex();							
				///������ ����� �������������� ���������� 
				virtual void GetInfoBuff(char **ppBuff, unsigned int* pSize);	
				///������� ���� ����� �������������� ���������� 
				virtual void SetInfoBuff(char *pBuff, unsigned int Size);
			};


		}
	}
}