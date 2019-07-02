#pragma once

#include "../ASSInterface/IMainAnalyse.h"

namespace SS
{
namespace MainAnalyse
{

	/// ������ � ��������� ������ ���������� �������� ������� ������, �� ��������
	class CAnalyseParams : public SS::Interface::Core::MainAnalyse::IAnalyseParams
	{
	public:
		CAnalyseParams();
		virtual ~CAnalyseParams(){};
	public:

		///�������� ������� ������� ������
		ULONG Release();

		///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** pBase); 

	};
}
}
