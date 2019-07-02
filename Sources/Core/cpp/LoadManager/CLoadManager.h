#pragma once

#include "ModulesManager.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{
	/// ������������� ������� ������������ ���������� �������� ��������� �������
	class CLoadManager : public SS::Interface::Core::ResourceManagers::ILoadManager
	{

		CModulesManager m_oModulesManager;
		const wchar_t* m_wszPath;
	public:

		CLoadManager();
		~CLoadManager();

		///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** ppBase); 
		///������������
		ULONG Release();

		/// ��������� ������� ����� ��� ������������� �������
		void SetWorkPath(const wchar_t* wszPath);
		const wchar_t* GetWorkPath();
		/// ������ ��������� �� ������ ���������
		/** 
			\param CoreLibrary - ������������� ������ 
			\param guidEntity - ������������� ��������(������)
			\param iidInterface - ������������� ����������
			\param ptssBase - ������ �� ����������, ��� ����� �������� ��������� �� ���������� ���������
			
		������� ��������� �� ������ ��������� ������� ������ ������� ������,
		(���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������)
		���������� ��������� �� ���� � ���������� ���������.
		�����������: ��������� ������ � guidEntity � �������� ���� ������ ����
		*/
		void* GetInterface(TCoreLibrary CoreLibrary, const GUID& guidEntity, const GUID& iidInterface);

		/// �������� ��������� �������� � ������� ������� ���������� (������ ������� ����� �����������)
		/** 
			\param CoreLibrary - ������������� ������ 
			\param guidEntity - ������������� ��������(������)
			\param iidInterface - ������������� ����������
			\param ptssBase - ������ �� ����������, ��� ����� �������� ��������� �� ���������� ���������
			
		������� ��������� �� ������ ��������� ������� ������ ������� ������ �
		���������� ��������� �� ���� � ���������� ��������� 
		��������! ������������ ������ ������� ��� ���������� ������� �����������
		��� ������������� ������ ��� ���������� ��������� ����
		*/
		void Create(TCoreLibrary CoreLibrary, const GUID& guidEntity, const GUID& iidInterface, void** ptssBase);
		
		void* GetInterface(const wchar_t* wszPath, const GUID& guidEntity, const GUID& iidInterface);
		void Create(const wchar_t* wszPath, const GUID& guidEntity, const GUID& iidInterface, void** ptssBase);
	};
}
}
}