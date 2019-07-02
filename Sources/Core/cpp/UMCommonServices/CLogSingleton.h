#pragma once

#include "..\ASCInterface\ICommonServices.h"
#include "Log.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{

	class CLogSingleton : public SS::Interface::Core::CommonServices::ILog,
		SS::Core::CommonServices::CSingle<CLog>
	{
	protected:

		std::wstring m_wsPathToLog;
		void Init();
	public:

		CLogSingleton();

		~CLogSingleton();

		///������ ������ ���-��������� szMessage �� ����
		void SaveLog(wchar_t* wszFirst...);		

		///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** pBase); 
		///������������
		ULONG Release();
	};
}
}
}