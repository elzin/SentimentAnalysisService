#pragma once

#include "baseconnectionsmanager.h"
#include "..\ASSInterface\ILingvoBaseManager.h"
#include "types.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

	/// ��������� ���������������� ����������, ������������ ������������ � SQL-�����
	class CSQLManager :
		public CBaseConnectionsManager<SS::Interface::Core::ResourceManagers::IConnection>,
		public SS::Core::CommonServices::CBaseCoreClass
	{

		///�������� � SQL-���� (��������� ��� + ��� �������)
		SS::Core::ResourceManagers::Types::THMConnections m_hmConnections;

		///�������, ��������� �� �����������
		SS::Core::ResourceManagers::Types::THMSubConnections m_hmSubConnections;

	protected:

		/// ��������� ���������� � ����� ���������� ���� � ������� ��������� 
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ���������� � SQL - �����
			\return bool - ���� ���������� ���������, true
		*/
		bool Open(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection);

		/// ��������� ���������� (� ����� ��� ��� �������������), �� ������� ��������� �������� 
		/** 
			\param it_Connection - ��������, ����������� �� ����������
		*/
		void Close(SS::Core::ResourceManagers::Types::THMConnections::iterator it_Connection);

		/// ��������� ���������� (� ����� ��� ��� �������������), �� ������� ��������� �������� 
		/** 
			\param it_Connection - ��������, ����������� �� ����������
		*/
		bool Open(SS::Core::ResourceManagers::Types::THMConnections::iterator it_Connection);

	public:
		CSQLManager();

		/// ��� �������� ����������� ��� ���������� � �� ������������� 
		~CSQLManager();

		/// ����������� ��� ���������� � �� ������������� 
		void Close();

		/// ��������� ������������ ��� ��� �� SQL - ������
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
		*/
		void Close(const wchar_t* BaseType);

		/// ��������� ������������, �� �������� ���������� � �������������
		/** 
			\return bool - ���� true, �� �������� ������ �������
		*/
		bool Open();

		/// ��������� ������������ ��� ���
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\return bool - ���� true, �� ���� �������
		*/
		bool Open(const wchar_t* BaseType);

		/// ������ ��� ��������� ���������
		/** 
			\param StorageName ��� ��������� ��������� (����� ���� Ind70ZMDF045DF...)
			\return bool - true, ���� �������� ��������� ������� ������
		*/
		bool OpenStorage(const wchar_t* StorageName);

		/// ���������� SubConnection 
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param pSubConnection - �������������, \see ISubConnection
			
		��������� � ���������� ������������� � ����� ������������������ 
		(��� �������������) �������� ������� ������
		*/
		void Register(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::ISubConnection* pSubConnection);

		/// �������� SubConnection
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param pSubConnection - �������������, \see ISubConnection
			
		������� ����� ������������������ ������������� 
		*/
		void UnRegister(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::ISubConnection* pSubConnection);

		/// �������� ��������, �������������� ����� ���������� ������������� ���� � ������� ������� ���������� � ������������
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� ��� ������ � ����������� � SQL-�����
			
		������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
		��������������� ����� ���������� ������������� ���� SQL-������ � ���������� ��������� �� ���� � ���������� ��������� 
		*/
		void CreateOpenAndRegister(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection);

		/// ������������� ������ �� ���������� SQL-������ \see SS::MANAGER::Constants
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� �� ������ � ����� SQL
			
		���� ����� ������ ����� ����, ���������� ����������� � ������������ ��������, ���������� � ��� 
		*/
		void UnRegisterDeleteAndClose(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection);
	};
}
}
}