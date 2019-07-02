#pragma once

//#include <VARARGS.H>
#include <STDARG.H>
#include <string>

#include "ExceptionParams.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{

	///������� ����� ��� ���� ������ ������� ��
	class CException : public SS::Interface::Core::CommonServices::IException,
		public SS::Core::Types::Enumerators::TListEnumerator<SS::Core::CommonServices::CExceptionParams>
	{
		
		std::wstring m_wsExceptions;
	public:

		///���������� ��������� ������ � ������
		SS::Interface::Core::CommonServices::IExceptionParams* Add();
		
		///������������ ������� ������
		SS::Interface::Core::CommonServices::IExceptionParams* GetCurrent();

		///���������� � ���� ������ ����������� ������
		std::wstring& ToString();

		///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** pBase); 
		///������������
		ULONG Release();
	};
}
}
}

