#pragma once

#include "BaseExpert.h"
#include "../ASSInterface/ISyntaxConstructions.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///������ ���������. ������ ��������� ������������ ��������� �� CExpertManager.
			class CExpertGroup
			{
			private:
				///��������� ���������
				std::vector<CBaseExpert*> m_vExperts;
				///�������� ������
				int m_iIdGroup;
				///�������������� � ������� ���������� ��������
				bool m_bIsAmbiguity;
				///�������������� � ������� ����������� ������
				bool m_bIsUnionBlocks;

			public:
				///��� ��������� �� ���������
				typedef std::vector<CBaseExpert*>::iterator TExpertPtrItr;
				///�����������
				CExpertGroup(int iIdGroup) : m_iIdGroup(iIdGroup), m_bIsAmbiguity(false), m_bIsUnionBlocks(false){};
				///����������
				~CExpertGroup()
				{
					for (TExpertPtrItr it = m_vExperts.begin(); it != m_vExperts.end(); ++it)
					{ delete (*it); }
				}
				///�������� �� ������� ��������
				TExpertPtrItr begin()
				{
					return m_vExperts.begin();
				}
				///�������� ����� ���������� ��������
				TExpertPtrItr end()
				{
					return m_vExperts.end();
				}
				///���������� �������� � ������
				void AddExpert(CBaseExpert* pBaseExpert)
				{
					m_vExperts.push_back(pBaseExpert);
				}
				///�������� ������ ���������
				int GetIdGroup() const
				{
					return m_iIdGroup;
				}
				///���������� ������� ���������� ��������
				void SetAsAmbiguity()
				{
					m_bIsAmbiguity = true;
					for (TExpertPtrItr it = m_vExperts.begin(); it != m_vExperts.end(); ++it)
					{ (*it)->SetAsAmbiguity(); }
				}
				///�������� �� ������� ���������� ��������
				bool IsAmbiguity() const
				{
					return m_bIsAmbiguity;
				}
				///���������� ������� ����������� ������
				void SetAsUnionBlocks()
				{
					m_bIsUnionBlocks = true;
				}
				///�������� �� ������� ����������� ������
				bool IsUnionBlocks() const
				{
					return m_bIsUnionBlocks;
				}
			};

		}
	}
}





