#pragma once

#include ".\CashCoSeDi.h"

namespace SS
{
	namespace CoSeDi
	{

		const int ciMaxIDSource = 200000;

		/// ����� ��������� ������� ���������������� �����, ����� ��� DBMS- � SQL-�����
		class CBaseCashCoSeDi
		{
		public:
			/// �����������
			CBaseCashCoSeDi(void){};
			/// ����������
			virtual ~CBaseCashCoSeDi(void){}
			
			/// ��������� ���������� �� ������ ����� � ������� ��� ���
			/** 
				\param uiIDSource - ������ ������ �����
				\param ewr - ���������� � ����� ������� ������ ����������� �����
				\return bool - ��������� ��������
			*/
			bool IsExistIDSource(unsigned int uiIDSource, SS::CoSeDi::DataTypes::EWorkRegion ewr)
			{
			
				SS_TRY
				{
 					SS::CoSeDi::DataTypes::S_bf_ui_WorkRegions oS_bf_ui_WorkRegions;	
					oS_bf_ui_WorkRegions = m_ucExistence[uiIDSource];

					switch(ewr)
					{
					case SS::CoSeDi::DataTypes::wrSemantic:
						return oS_bf_ui_WorkRegions.IsSemantic();
						break;
					case SS::CoSeDi::DataTypes::wrCombinatory:
						return oS_bf_ui_WorkRegions.IsCombinatory();
						break;
					case SS::CoSeDi::DataTypes::wrSyntax:
						return oS_bf_ui_WorkRegions.IsSyntax();
						break;
					default:
						return false;
						break;
					}					
				}		
				SS_CATCH(L"");

				return true;


			}

			/// ��������� ������ � ���
			/** 
				\param uiIDSource - ������ ������ �����
				\param ewr - �������� �������, � ������� ����������� �����
				\return void
			*/
			void AddIDSource(unsigned int uiIDSource, SS::CoSeDi::DataTypes::EWorkRegion ewr)
			{
				SS_TRY;
				///////////////////////////////////////////////////////////////////////
				/*	���������� ���������� � ������ ��� �������� �������	*/

				SS::CoSeDi::DataTypes::S_bf_ui_WorkRegions oS_bf_ui_WorkRegions;	
				oS_bf_ui_WorkRegions = m_ucExistence[uiIDSource];				
				switch(ewr)
				{
				case SS::CoSeDi::DataTypes::wrSemantic:
					oS_bf_ui_WorkRegions.SetSemantic();
					break;
				case SS::CoSeDi::DataTypes::wrCombinatory:
					oS_bf_ui_WorkRegions.SetCombinatory();
					break;
				case SS::CoSeDi::DataTypes::wrSyntax:
					oS_bf_ui_WorkRegions.SetSyntax();
					break;
				}				
				m_ucExistence[uiIDSource] = *((unsigned short*)&oS_bf_ui_WorkRegions);

		
				SS_CATCH(L"");
				
			}
		protected:
			/*! \var unsigned short m_ucExistence[ciMaxIDSource];
			*  \brief     ������ ������������� ������ � �������
			*/
			unsigned short m_ucExistence[ciMaxIDSource];							
		};
	};
};