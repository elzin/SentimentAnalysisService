#pragma once

#include ".\settings_operator.h"
#include ".\settings_editor.h"

namespace SS
{
namespace CommonServices
{

//----------------------------------------------------------------//

///������ ��������
class CSettingsService :
	public CSettingsOperator, public CSettingsEditor
{
public:
	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������
	ULONG Release(void);
	//-----------Eof-IBase
protected:
	///���������� ���������
	SS::Interface::Core::ResourceManagers::ILoadManager* GetLoader(void){return GetLoadManager();};

};

//----------------------------------------------------------------//

}
}
