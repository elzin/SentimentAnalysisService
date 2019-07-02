#pragma once

#include "ControlDynamicLibrary.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

		/// ������� ����� ��� ������ � ��������
		/** ������ ���������� �� �������� ���������, ��������� ������� ���������������� ��������
		������� ������ ������� ������ � ����������� ��������������� ����������*/
		class CBaseLoadManager
		{
		protected:
			///����� ��� �������� ������� (dll)
			CControlDynamicLibrary m_oControlDynamicLibrary;

			SS::Interface::Core::ResourceManagers::ILoadManager* m_pLoadManager;
		public:
			CBaseLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

			/// �������� �������� � ������� ������� ���������� ��� �����������
			/** 
				\param CoreLibrary - ������������� ������ 
				\param guidEntity - ������������� ��������(������)
				\param iidInterface - ������������� ����������
				\param ptssBase - ������ �� ����������, ��� ����� �������� ��������� �� ���������� ���������
				
			������� ��������� �� ������ ��������� ������� ������ ������� ������ �
			���������� ��������� �� ���� � ���������� ��������� 
			*/
			void Create(TCoreLibrary CoreLibrary, const GUID& guidEntity, const GUID& iidInterface, void** ptssBase, const wchar_t* wszPath);
			///�������� �������� � ������� ������� ���������� ��� ����������� �� ����� dll
			void Create(const wchar_t* wszDllName, const GUID& guidEntity, const GUID& iidInterface, void** ptssBase, const wchar_t* wszPath);
		};

}
}
}