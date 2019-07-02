#pragma once
#include "..\assinterface\iblackbox.h"
#include ".\smexpert.h"

namespace SS
{
	namespace Semantic
	{

using namespace SS::Interface::Core;

		class CSMExpertGroup : virtual public SS::Interface::Core::Common::CAnalyseParams
		{
		public:
			CSMExpertGroup(TCHAR * scDescription);
			virtual ~CSMExpertGroup(void);
			/// ������ ������ BlackBox
			/** 
			\param pIText - ����� ��� �������
			\return bool - ������ - ���� ������ ������ �������

			����� ������ ��������� � ��������� ���������
			*/
			bool Analize(BlackBox::IText * pIText);

			/// ���������� �������� � ������
			/** 
				\param pExpert - �������
			*/
			void AddExpert( CSMExpert * pExpert );
			/// ���������� �������� ������
			wstring GetGroupDescription(){ return m_szDescription; };
			/// ������������� �������� ������
			void SetGroupDescription(TCHAR * scDescription){ m_szDescription=scDescription; };
			void SetExpertsSMManager(CSMManager * pManager);

		protected:
			void DeleteExperts();

		private:
			list<CSMExpert*> m_Experts;
			list<CSMExpert*>::iterator m_CurrentExpert;
			
			wstring m_szDescription;
		};
	}
}