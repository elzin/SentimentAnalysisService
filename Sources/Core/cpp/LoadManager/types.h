#pragma once

#include <map>
#include <list>
#include <algorithm>

namespace SS
{
namespace Core
{
namespace ResourceManagers
{
namespace Types
{

			/// ����������� ���� ��� GUID (��������� �������� ���������)
			/** ������ ����� ��������� �������� ��������� ��� GUID, � ����� �������������� � ��������� ��������� */
			class CGuidShell
			{

				/// GUID, ������ �������� ������� ������ �����
				GUID m_guid;

				/// ����������� GUID � ��������� �������������
				/** 
					\return std::wstring - ��������� ������������� GUID
				*/
				std::wstring inToString();
			public:

				/// ������������� ������ ������ 
				/** 
					\param guid - GUID
				*/
				CGuidShell(GUID guid);

				/// �������� ��������� ��� ������������ �������
				/** 
					\param value  - �����, � ������� ���������� ���������
					\return bool - ���� ������, �� true
				*/
				bool operator<(const CGuidShell& value) const;

				/// �������� ���������� ���� � GUID
				operator GUID();

				/// �������� ���������� ���� � GUID ��� ������������ �������
				operator GUID() const;

				/// ����������� GUID � ��������� ��������� 
				/** 
					\return std::wstring ��������� ������������� GUID
				*/
				std::wstring ToString();

				/// ����������� GUID � ��������� ��������� (��� ������������ �������)
				/** 
					\return std::wstring ��������� ������������� GUID
				*/
				std::wstring ToString() const;
			};



			/*! \typedef TLInterfaces
			*  \brief    ��������� ���������
			*/
			typedef int TInterface;

			/*! \typedef TMWorkInterfaces
			*  \brief    ��������� ����� ������������ ����� GUID ���������� � ������� ������ �� ��������� �� ����
			*/
			typedef std::map<CGuidShell,TInterface> TMWorkInterfaces;
			/*! \typedef TPWorkInterfaces
			*  \brief    ��������� ���� - ��������� �� ������� ��������� � ����� ����������� ����� GUID ���������� � ������� ������ �� ��������� �� ����
			*/
			typedef std::pair<SS::Interface::IBase*, TMWorkInterfaces> TPWorkInterfaces;

			/*! \typedef TMWorkEntities
			*  \brief    ��������� ����� ������������ ����� GUID ������ � ����� TMWorkInterfaces (���������� �������)
			*/
			typedef std::map<CGuidShell,TPWorkInterfaces> TMWorkEntities;
			/*! \typedef TMWorkLibraries;			
			*  \brief    ��������� ����� ������������ ����� ��������������� ������ � ����������� �������
			*/
			typedef std::map<TCoreLibrary, TMWorkEntities> TMWorkLibraries;			
}
}
}
}