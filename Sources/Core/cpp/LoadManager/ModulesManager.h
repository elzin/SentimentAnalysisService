#pragma once

#include "CBaseLoadManager.h"
#include "types.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

		/// ��������� ����������� ���������������� �� �������� �������
		/** ������������ � �������������� ��� ��������� ������ 
		(� ����� �������� ���������� ������ �������), ����������� ������*/
		class CModulesManager : public CBaseLoadManager
		{

		protected:
			///����������� ���� ���������, �������, �����������, ����������� ��� ������
			SS::Core::ResourceManagers::Types::TMWorkLibraries m_mWorkLibraries;

			///������� ���� ������� ������ ������
			/** 
				\param CoreLibrary - ������������� ������� ������
				\return SS::Core::ResourceManagers::Types::TMWorkLibraries::iterator - �������� �� ������ ������
			*/
			SS::Core::ResourceManagers::Types::TMWorkLibraries::iterator FindOrCreateLibrary(TCoreLibrary CoreLibrary);

			///������� ���� ������� ������ ����� � ������ ������
			/** 
				\param CoreLibrary - ������������� ������ 
				\param guidEntity - ������������� ��������(������)
				\param iidInterface - ������������� ����������
				\param ptssBase - ������ �� ����������, ��� �������� ��������� �� ���������
				\return SS::Core::ResourceManagers::Types::TMWorkEntities::iterator - �������� �� ������ ��������		 
			*/
			SS::Core::ResourceManagers::Types::TMWorkEntities::iterator FindOrCreateEntity(TCoreLibrary CoreLibrary, SS::Core::ResourceManagers::Types::TMWorkLibraries::iterator& it_Library, const GUID& guidEntity, void** ptssBase, const wchar_t* wszPath);

			///������� ���� ������� ������ ��������� � ������ ������
			/** 
				\param guidEntity - ������������� ��������(������)
				\param iidInterface - ������������� ����������
				\param ptssBase - ������ �� ����������, ��� �������� ��������� �� ���������
				\return SS::Core::ResourceManagers::Types::TMWorkInterfaces::iterator - �������� �� ������ ���������			 
			*/
			SS::Core::ResourceManagers::Types::TMWorkInterfaces::iterator FindOrCreateInterface(SS::Core::ResourceManagers::Types::TMWorkEntities::iterator it_Entity, const GUID& iidInterface, void** ptssBase);

			///������� ��� ��������
			/** 
				\param CoreLibrary - ������������� ������ 
				\param iidInterface - ������������� ����������
			*/
			void DeleteAll();

		public:
			CModulesManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

			~CModulesManager();			

			/// �������� �������� � ������� ������� ���������� � ������������
			/** 
				\param CoreLibrary - ������������� ������ 
				\param guidEntity - ������������� ��������(������)
				\param iidInterface - ������������� ����������
				\param ptssBase - ������ �� ����������, ��� ����� �������� ��������� �� ���������� ���������
				
			������� ��������� �� ������ ��������� ������� ������ ������� ������,
			(���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������)
			���������� ��������� �� ���� � ���������� ��������� �
			���������� ��������� �� ���������� ���������
			*/
			void CreateAndRegister(TCoreLibrary CoreLibrary, const GUID& guidEntity, const GUID& iidInterface, void** ptssBase, const wchar_t* wszPath);
			void CreateAndRegister(const wchar_t* wszLibraryPath, const GUID& guidEntity, const GUID& iidInterface, void** ptssBase, const wchar_t* wszPath);


		};
}
}
}