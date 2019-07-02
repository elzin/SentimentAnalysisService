#pragma once

#include ".\basis_setting.h"

namespace SS
{
namespace CommonServices
{

//----------------------------------------------------------------//

///��������� ���������
template <class T>
class CSetting : public CBasisSetting
{
public:
	CSetting(const wchar_t* wszSettingName, SSettingType SettingType)
		:CBasisSetting(wszSettingName, SettingType){};

	///��������� ��������� � �������� ���
	virtual void ToBinary(std::vector<unsigned char>* pBuffer)
	{
		if(!pBuffer) return;
		
		//��������
		m_SettingName.ToBinary(pBuffer);

		//���������
		unsigned int uiOldSize=(unsigned int)pBuffer->size();
		pBuffer->resize(pBuffer->size() + sizeof(SSettingAttributes));
		unsigned char* pCurrPos=&(pBuffer->front())+uiOldSize;
		memcpy(pCurrPos, (unsigned char*)&m_SettingAttributes, sizeof(SSettingAttributes));
		
		//��������
		m_SettingValue.ToBinary(pBuffer);
	};

	///��������� ��������� �� ������
	virtual void FromBinary(unsigned char* pucBuffer, unsigned int uiBufferSize, unsigned int* puiReadedSize)
	{
		if(!pucBuffer) return;
		if(!uiBufferSize) return;
		if(!puiReadedSize) return;

		(*puiReadedSize)=0;

		//��������
		(*puiReadedSize)+=m_SettingName.FromBinary(pucBuffer, uiBufferSize);

		//���������
		memcpy((unsigned char*)&m_SettingAttributes, pucBuffer+(*puiReadedSize), sizeof(SSettingAttributes));
		(*puiReadedSize)+=sizeof(SSettingAttributes);
		
		//��������
		(*puiReadedSize)+=m_SettingValue.FromBinary(pucBuffer+(*puiReadedSize), uiBufferSize-(*puiReadedSize));
	};

	///���������� �������� ���������
	bool GetSettingValue(void* pOutValue, 
		SS::Interface::Core::CommonServices::EParameterType eSettingType, bool bIsArray)
	{
		//��������� ���
		if(!(eSettingType==m_SettingAttributes.m_SettingType.m_eSettingType && 
			bIsArray==m_SettingAttributes.m_SettingType.m_bIsArray))
			return false;

		//�������� �������� ���������
		m_SettingValue.CopyTo(pOutValue);
		return true;
	};

	///������������� �������� ���������
	bool SetSettingValue(void* pInValue, 
		SS::Interface::Core::CommonServices::EParameterType eSettingType, bool bIsArray)
	{
		//��������� ���
		if(eSettingType!=m_SettingAttributes.m_SettingType.m_eSettingType)
			return false;

		if(m_SettingAttributes.m_SettingType.m_bIsArray==bIsArray){
			//�������� �������� ���������
			m_SettingValue.CopyFrom(pInValue);
			return true;
		}else if(m_SettingAttributes.m_SettingType.m_bIsArray && !bIsArray){
			//���� ��������� ������, � ����������� ������� �������� 
			//��������� ��� � ������� ���������
			m_SettingValue.CopyFrom(pInValue, true);
			return true;
		}else{
			return false;
		}
	};
	
	///�������� �������� ���������
	void CopyValue(CBasisSetting* pSetting)
	{
		if(!pSetting) return;
		CSetting<T>* p=static_cast<CSetting<T>* >(pSetting);
		m_SettingValue=p->m_SettingValue;
	}

protected:
	///�������� ���������
	T m_SettingValue;
};

//----------------------------------------------------------------//

}
}
