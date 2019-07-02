#pragma once

#include ".\settings_manager.h"
#include "..\ASCInterface\ICommonServices.h"

namespace SS
{
namespace CommonServices
{

//----------------------------------------------------------------//

///�������� ��������, ��������� ���������, �������, ��������, �������� ���������
class  CSettingsEditor :
			public virtual CSettingsManager,
			public SS::Interface::Core::CommonServices::ISettingsServerEdit
{
public:

	//------------ISettingsServerEdit 
	//ISettingsServerEdit implementation
	///���������� ������ ����������. ��������� - null
	void GetParameterList (std::vector<std::wstring>* pOutSettingsNames, bool bShowPrivate);
	///�������� ��������
	bool			AddParameter		(const wchar_t*		wszName, 
											SS::Interface::Core::CommonServices::EParameterType	eType, 
											bool			bIsArray		= false, 
											bool			bIsPublic		= true,
											bool			bIsReadOnly		= false);
	///�������� ��� ��������� �� ��� �����
	SS::Interface::Core::CommonServices::EParameterType GetParameterType		
										(const wchar_t*		wszName, 
										bool*			pbIsArray = NULL);
	///�������� �� �������� ���������
	unsigned int GetPublicity				(const wchar_t* wszName);
	///�������� �� ��������� ���������������
	unsigned int GetAccessibility			(const wchar_t* wszName);
	///������� ��������
	void			DeleteParameter		(const wchar_t* wszName);
	///������������� ��� ������������� ���������
	void SetParameterName			(const wchar_t* wszName, const wchar_t* wszNewName);
	///������������� ����������� ������������� ���������
	void SetParameterPublicity		(const wchar_t* wszName, bool bIsPublic);
	///������������� ��� ������� � ������������� ���������
	void SetParameterAccessibility	(const wchar_t* wszName, bool bIsReadOnly);
	///������������� ��� ������������� ��������� (���� ����� ��� �� ��������� �� ������, ��� �������� ����������)
	void SetParameterType			(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType eType);
	///�������� �������� � ������ �������� ���������
	void AddParameterValue(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType eType, void* pValue);
	//-----------Eof-ISettingsServerEdit 

};

//----------------------------------------------------------------//

}
}