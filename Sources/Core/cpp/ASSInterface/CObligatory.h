#pragma once

///���������������� ��������������
class CObligation
{
public:
	CObligation():m_bIsObligatory(true), m_fWeight(0.0){};
	virtual ~CObligation(void){};

	virtual void SetObligatory(BOOL bObligatroy){m_bIsObligatory = bObligatroy; };
	///������� ���� ��������������
	virtual void SetUnObligatory(void){m_bIsObligatory=false;};
	///���������� ���� ��������������
	virtual void SetObligatory(void){m_bIsObligatory=true;};
	///���������� ���� ��������������
	virtual BOOL IsObligatory(void){return m_bIsObligatory;};
	///������������� ��� �������
	virtual void SetWeight(float fValue){m_fWeight=fValue;};
	///���������� ��� �������
	virtual float GetWeight(void){return m_fWeight;};

protected:
	///���� ��������������
	BOOL m_bIsObligatory;
	///���
	float m_fWeight;
};
	
