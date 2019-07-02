#pragma once

#include "..\assinterface\iblackbox.h"
#include ".\StringService.h"
#include "..\assinterface\IDictionaryManager.h"


namespace SS
{
	namespace Semantic
	{

		typedef TCHAR * TCharType;
		/// ����������� ���� ������
		class CLexemType
		{
		public:
			CLexemType(void);
			~CLexemType(void);
			/// ������������� ��������� �� ��������� �������� ����� 
			void Init(SS::Interface::Core::BlackBox::IUnit ** ppUnit) { m_ppCurentUnit=ppUnit; };
			
			/// ������ ���� ����� ����� ��������� ������
			/** 
				\param pcWord - ������
				\param  pUnit - �����
				\return 			bool - ����� - ���� �����
			*/
			bool WordEqualsTo(const TCharType pcWord,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL );
			/// ������, ���� ���� - ����� , � ��� ����� �� ����� uiLessOrEqual
			/** 
				\param uiLessOrEqual=0 - ����� �����, ���� =0 - �� ����� ����� ���� ������������
				\param pUnit=NULL
				\return 			bool
			 
			-detailed description- 
			*/
			bool IsWord(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������, ���� ������ ����� ����� � ������� ��������
			bool IsUpperCase(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool IsEng(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool Iseng(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool IsENG(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool IsEnG(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool IsRus(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool Isrus(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			//bool IsRUS(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ����� ������, ���� ����� - �����
			bool IsSymbol(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			
			/// ����� ������, ���� ����� ����� ������� ������� �������
			/** 
				\param pcSymbol - ������
				\param pUnit=NULL  - ����� 
			*/
			bool SymbolEqualsTo(TCharType  pcSymbol,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ���������� ����� �����
			/** 
				\param pUnit=NULL - �����
				\return 			UINT - �����
			*/
			UINT GetLexemLength(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);

			/// ������, ���� ����� ���� �����
			/** 
				\param uiLessOrEqual=0 - ����� ����� �� ������ ���, ���� 0 - �� �����
				\param pUnit=NULL - ����� 
				\return 			bool -
			*/
			bool IsDigits(UINT uiLessOrEqual=0,SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������ ���� ����� - �������
			bool IsSQuotes(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������ ���� ����� - ����
			bool IsSTire(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������, ���� ����� - �����
			bool IsSDefis(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������, ���� ����� - �������
			bool IsSComma(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������ ���� ����� - �����
			bool IsSDot(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������, ���� ����� �������
			bool IsSApostrophe(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
			/// ������ - ���� ������ �����
			bool IsEmpty(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL){ return false; };
		private:
			/// ��������� �� ������� ���� ��������
			SS::Interface::Core::BlackBox::IUnit ** m_ppCurentUnit;
			/// ����������� �� ��������
			CStringService m_StringService;
		};
	}
}