#include "stdafx.h"
#include "BaseExpert.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			//�����������
			CBaseExpert::CBaseExpert() : m_isCheckedApplication(false), m_bIsAmbiguity(false), m_isApplicable(false)
			{
			}
			
			//�������� ���������
			void CBaseExpert::ClearApplicableState()
			{
				m_isCheckedApplication = false;
			}

			///���������� �������������� � ���������� ��������
			void CBaseExpert::SetAsAmbiguity()
			{
				m_bIsAmbiguity = true;
			}
		}
	}
}