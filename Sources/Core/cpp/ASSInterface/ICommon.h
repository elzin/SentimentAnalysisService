#pragma once

#include "./IMainAnalyse.h"


// {99A8AC3A-896C-4cb2-9D68-67ED73C9B222}
static const GUID CLSID_Connection = 
{ 0x99a8ac3a, 0x896c, 0x4cb2, { 0x9d, 0x68, 0x67, 0xed, 0x73, 0xc9, 0xb2, 0x22 } };

// {3C8ECA65-B2A1-4143-AE0B-189BBFF2B2B9}
static const GUID IID_Connection = 
{ 0x3c8eca65, 0xb2a1, 0x4143, { 0xae, 0xb, 0x18, 0x9b, 0xbf, 0xf2, 0xb2, 0xb9 } };


namespace SS
{
namespace Interface
{
namespace Core
{
namespace Common
{
	/// ���������� �������� �������� � �����������
	/// ���������, ��������������� ����� ������� �� ������ � ��������� � ��������� ��������
	class IConnection/* : public virtual IBase*/
	{
	public:
		/// ��������� ���������� 
		virtual bool Open()	= 0;
		/// ��������� ���������� 
		virtual bool Close() = 0;
	};     


	/// ���������� �������� �������� � �����������
	/// ���������, ��������������� ����� ������� �� ������ � ��������� � ��������� ��������
	class ILoad	
	{
	public:
		/// �����������
		ILoad(void){};
		/// ����������
		virtual ~ILoad(){};
	public:
		/// ��������� � �������� ��� ��������� ������ 
		virtual bool ToBinary()	= 0;
		/// ������������� �������
		virtual bool ReLoad()	= 0;
		/// ��������� �������
		virtual bool Load()	= 0;
		/// ����������� ������
		virtual bool Clear()	= 0;
	};     

	class CAnalyseParams
	{
	public:
		CAnalyseParams() : m_pAnalyseParams(NULL)
		{}
		virtual ~CAnalyseParams() {}
		/// ������������� ������� ��������� �������
		/** 
			\param pAnalyseParams - ��������� ������
			\return void
		*/
		virtual void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams)
		{
			m_pAnalyseParams = pAnalyseParams;
		}

		/// ������������� ������� ��������� �������
		/** 
			\param pAnalyseParams - ��������� ������
			\return void
		*/
		virtual SS::Interface::Core::MainAnalyse::IAnalyseParams* GetAnalyseParams()
		{
			return m_pAnalyseParams;
		}

	private:
		SS::Interface::Core::MainAnalyse::IAnalyseParams* m_pAnalyseParams;
	};

}
}
}
}
