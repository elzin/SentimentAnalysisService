#pragma once

#include "BlockVersion.h"
#include "BoardElement.h"
#include "ParsingType.h"
#include "DynamicVersionGenerator.h"

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///���� ��������� �����. ���������� ������� ����� �������� �����������. 
			class CBlock
			{
			private:
				///������ ��� ����������� ��������� �������
				///������ ���� ������� ������� ������� �����
				std::list<CBlockVersion> m_Versions;
				///������� ������
				std::list<CBlockVersion>::iterator m_itCurrentVersionStatic;
				///�������� ���������� ������
				std::list<CBlockVersion>::iterator m_itBestVersionStatic;
				///��������� ��� ������������� ����������
				std::list<CBlockVersion> m_NullCollection;
				
				///������ ��� ������������ ��������� �������
				///������ �� ������ ������ ��������
				CBlockVersion m_oBestVersionDynamic;
				///������� ��������
				CBlockVersion m_oCurrentVersionDynamic;
				
				///����� ������
				///������� ���������� ��������������� �������
				unsigned int m_iVersionCount;
				///����������� ����
				CBlock* m_pAddBlock;
				///������� �����
				BoardElementsIterator m_first, m_last;
				///������� �������� ����������� ������
				CBlockVersion m_oCurrVerBothBlock;
				///������ �������� ������� ����������� ������
				CBlockVersion m_oBestVerBothBlock;
				///������ ������������ ��������� �������
				CDynamicVersionGenerator m_oDynamicVersionGenerator;
				///���������� ��������� � �������� �� ����������� � ������� �����
				unsigned int m_CountATExpert;
				
			private:
				///����������� ���� ��������� ����� ����� ��������
				void SetVersion(CBlockVersion* pVersion);
				///�������� ���������� ����� (�������� ��������� � AddBlock())
				bool UnionBlocks();
				///���������� �������� � �������� ����� ������, ������� ������������
				void SaveVerBoth(CBlockVersion & oVersion);
				///�������� ������ �����
				void ClearData();
											
			public:
				///�����������
				CBlock(){};
				///����������
				~CBlock(){};
								
				///������ ��� ������ �� ������������ ����������
				///��������� �� ��������
				void CreateVersions();
				///������������ ����������� �������
				bool SwitchVersion();
				///���������� � ������������� �������� ���������� �������� �������
				void SetBestVersion();
				///���������� ������� ����������� ��������
				void SetCurrentVersion();
				///���������� �� ������ �� ���������
				bool VersionsFinish() {	return m_itCurrentVersionStatic == m_Versions.end(); };
				///��������� �������� �� ������
				void SetHypothesis(unsigned int iNumber);
				///���������� ���������� �������
				int VersionNumber() { return (int)m_Versions.size(); }
				///���������� ������ ������� ��������
				int BestVersionIndex()
				{
					if (m_Versions.empty())
					{ return 0;	}
					else
					{
						if (m_itBestVersionStatic != m_Versions.end()) 
						{ return (int)( std::distance(m_Versions.begin(), m_itBestVersionStatic) + 1 );	}
						return 0;
					}
				}
				
				///������ ��� ������ � ������������� ����������
				///������������ �������� �������
				bool SwitchVersionDynamic(ExpertModel::ParsingType type);
				///��������� ������ ������������ ��������
				void SetBestVersionDynamic();
				///������������� ����������� (������������)������ ��������
				void SetVersionFinal();
			
				///����� ������
				///������������� ����� ������ �������
				void Init(BoardElementsIterator first, BoardElementsIterator last);
				///���������� ��������, ����������� �� ������ ������� �����
				BoardElementsIterator GetFirst() { return m_first; };
				///���������� ��������, ����������� �� ������� ����� ���������� �������� �����
				BoardElementsIterator GetLast()	{ return m_last; };
				///� ����� � ������ ����������� �������� ������� �����. ����������� ���� ������ ���� ��������� ��������.
				void AddBlock(CBlock* pBlockToAdd);
				///���������� ������ �������� ����� �� ������ ������
				CBlockVersion & GetBestVersion();
				///�������� ����� �� �����������
				bool Empty() const;
				///�������� �������������� �������� ������� �����
				bool Contain(BoardElementsIterator itElem) const;
				///���������� �� 1 ���������� ������������� ��������� � ��
				void IncCountATExpert() { ++m_CountATExpert; };
				///������� ���������� ������������� ��������� � ��
				unsigned int GetCountATExpert() { return m_CountATExpert; };
			};
		}
	}
}