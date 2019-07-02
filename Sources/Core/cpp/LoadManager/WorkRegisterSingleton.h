#pragma	once

#include "..\ASCInterface\ICommonServices.h"
#include "..\ASCInterface\services.h"
#include "WorkRegister.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{


	/// ������������� ������� ������������ ���������� ������ � �����������
	class CWorkRegisterSingleton : public SS::Interface::Core::CommonServices::IWorkRegister,
		SS::Core::CommonServices::CSingle<CWorkRegister>
	{

	public:

		CWorkRegisterSingleton();
		~CWorkRegisterSingleton();

		///���������� �������� ��������� �� ��� ����� (������ ������)
		std::wstring GetParameter(std::wstring wParametrName);

		///��������� ������� ����������
		void SetWorkDir(std::wstring wPathToDir);

		///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** ppBase); 

		///������������
		ULONG Release();

	private:

		void CreateSSDirectories();
		
		bool CreateSSDirectory(LPCWSTR szPath, LPCWSTR szDir);

	};

}
}
}



