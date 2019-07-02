#pragma once

#include "..\ASCInterface\ICommonServices.h"
#include "..\ASCInterface\TListEnumerator.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{

	class CExceptionParams : public SS::Interface::Core::CommonServices::IExceptionParams
	{
		///��������� �� ������
		std::wstring m_wsMessage;
		///��� ������
		SS::Core::CommonServices::ETypeError m_eteTypeError;
		///��� �������
		std::wstring m_wsFunction;
		///��� �����
		std::wstring m_wsFile;
		///����� ������ � �����
		long m_lLine;

	public:

		CExceptionParams();
		CExceptionParams(
			///��� ������
			SS::Core::CommonServices::ETypeError eteTypeError,
			///��� �������
			std::wstring wsFunction,
			///��� �����
			std::wstring wsFile,
			///����� ������ � �����
			long lLine);

		///��������� ��������� �� ������
		void SetMessage(wchar_t* wszMessage...);
		///������ ��������� �� ������
		const std::wstring& GetMessage();		

		///��������� ��� �������, ��������� ������
		void SetFunction(const std::wstring wsFunction);
		///������ ��� �������, ��������� ������
		const std::wstring& GetFunction();

		///��������� ��� ����� � �����
		void SetFile(const std::wstring wsFile);
		///������ ��� ����� � �����
		const std::wstring& GetFile();

		///��������� ����� ������ � ����� � ����� 
		void SetLine(const long lLine);
		///������ ����� ������ � ����� � ����� 
		const long GetLine();

		///��������� ��� ������
		void SetTypeError(const SS::Core::CommonServices::ETypeError eteTypeError);
		///������ ��� ������
		const SS::Core::CommonServices::ETypeError GetTypeError();
	};
}
}
}
