// IQPCounter.h
#pragma once

#include "..\ASCInterface\IInterface.h"
//#include "..\ASCInterface\ILinguisticProcessor.h"
//#include "..\ASCInterface\TCoommonTypes.h"
#include <list>

// {0C6B8616-1AE0-4e73-A7E5-1FFD1675C537}
static const GUID CLSID_ICounterSessions = 
{ 0xc6b8616, 0x1ae0, 0x4e73, { 0xa7, 0xe5, 0x1f, 0xfd, 0x16, 0x75, 0xc5, 0x37 } };

// {912506EE-F73C-494f-A91D-CBBDFB39E5D1}
static const GUID IID_ICounterSessions = 
{ 0x912506ee, 0xf73c, 0x494f, { 0xa9, 0x1d, 0xcb, 0xbd, 0xfb, 0x39, 0xe5, 0xd1 } };

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace CommonServices
			{
				class ICounterSession;

				class ICounterSessions : public virtual SS::Interface::IBase
				{
				public:
					///������ ������ � �������� ������. ���� �� ����������, ������� � ������.
					virtual ICounterSession* GetSession(wchar_t* wszName) = 0;
					///������������ ��� ������ (�� ���� ���� ������� ���� ������� �������� ���������� �� ���� � ������ ����� �� ������).
					virtual void DropAll() = 0;
					///������������ ��� ������ (�� ���� ���� ������� ���� ������� �������� ���������� �� ����).
					virtual void DropStatistics() = 0;
					/// ������ ������ � ����������� �� ��� ��������� �� ������ ������ ������.
					virtual std::list<ICounterSession*>* GetSessionList() = 0;
				};

				///������ ���������.
				class ICounterSession // : public virtual SS::Interface::IBase
				{
				public:
					/// ������ ����� ���������� �� ������.
					virtual void StartSession() = 0;
					/// ��������� ����� ���������� �� ������.
					virtual void StopSession() = 0;
					///��������� �������.
					virtual void StartCounter(wchar_t* wszName) = 0;
					///���������� �������.
					virtual void StopCounter(wchar_t* wszName) = 0;
					///������ ����� ���������� �� �����.
					virtual void StartPart() = 0;
					///��������� ����� ���������� �� �����.
					virtual void StopPart() = 0;
					///������ ����� ���������� �� �����. ���������� �������������� ������ ����������, ������� ����� �������� � ������, ���������� ���������� �� ������� ������ �����.
					virtual void StartPart(wchar_t* wszInfo) = 0;
					///���������� �������������� ������ ����������, ������� ����� �������� � ������, ���������� ���������� �� ������� ������ ����� (�������� ����� ������, ���������� � StartPart, ���� ����).
					virtual void StopPart(wchar_t* wszInfo) = 0;
					///������ ����� ���������� �� �����. ���������� �������������� ������ ����������, ������� ����� �������� � ������, ���������� ���������� �� ������� ������ �����. ������������� ���������� ������ � ������ �������������� ����������.
					virtual void StartPart(wchar_t* wszInfo, unsigned int uiValue) = 0;
					///���������� �������������� ������ ����������, ������� ����� �������� � ������, ���������� ���������� �� ������� ������ ����� (�������� ����� ������, ���������� � StartPart, ���� ����). ������������� ���������� ������ � ������ �������������� ���������� (��� �������� �������� ����� ��������, ���������� � StartPart, ���� ����).
					virtual void StopPart(wchar_t* wszInfo, unsigned int uiValue) = 0;
					///����� ���������� �� ���� � �� ���������, ������� ������
					virtual void DropAll() = 0;
					///����� ���������� �� ���� ��� ���������, ������� ������
					virtual void DropStatistics() = 0;
				};
			}
		}
	}
}
