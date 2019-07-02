#pragma once

#include "..\ASSInterface\ILingvoBaseManager.h"
#include "..\ASCInterface\idbms.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{
namespace Types
{

	/*! \typedef TLSubConnections
	*  \brief   ��������� ������ �������������
	*/
	typedef std::list<SS::Interface::Core::ResourceManagers::ISubConnection*> TLSubConnections;
	/*! \typedef THMSubConnections
	*  \brief    ��������� ����� ������������ ����� ������ ���� ���� � ������� �������������
	*/
	typedef std::unordered_map<std::wstring, TLSubConnections> THMSubConnections;
	/*! \typedef TLConnections
	*  \brief    ��������� ������ ���������� SQL - ������
	*/
	typedef std::list<SS::Interface::Core::ResourceManagers::IConnection**> TLConnections;
	/*! \typedef THMConnections
	*  \brief    ��������� ����� ������������ ����� ������ ���� ���� � ������� ������ �� ��������� �� ���������� SQL-������
	*/
	typedef std::unordered_map<std::wstring, TLConnections> THMConnections;

	/*! \typedef TLDBMSConnections
	*  \brief    ��������� ������ ���������� DBMS - ������
	*/
	typedef std::list<SS::Interface::Core::DBMS::IDataBase**> TLDBMSConnections;
	/*! \typedef THMDBMSConnections
	*  \brief    ��������� ����� ������������ ����� ������ ���� ���� � ������� ������ �� ��������� �� ���������� DBMS-������
	*/
	typedef std::unordered_map<std::wstring, TLDBMSConnections> THMDBMSConnections;
}
}
}
}