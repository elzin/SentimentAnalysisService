#pragma once

#include "../ASDInterface/INdxDataStorage.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Storages
{

//--------------------------------------------------------------------//

///������� �������� � ����� ����� � ��������� �������
class CIndexEntryPointTable
{
public:
   CIndexEntryPointTable(SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* pNdxTableStorage);
   virtual ~CIndexEntryPointTable(void); 

	///��������� �������� �� �������� ������
	unsigned int GetIndexEntryPoint(unsigned int uiIndex);
	///��������� �������� ������ � ���� ������, df - �� ��������� ���������� ������ 0.
	bool SetIndexEntryPoint(unsigned int uiIndex, unsigned int uiEntryPoint);
	///��������� �������� ������ � ���� ������ �  df 
	bool SetIndexEntryPoint(unsigned int uiIndex, unsigned int uiEntryPoint, unsigned int uiIndexDF);
	///��������� ���� �������� - �� ������������ 
	bool Open(string& szPath);
	///�������� ������ � ��, ������� �������� df. 
	bool ModifyIndexRecordDF(unsigned int uiIndex, unsigned int uiDF);
	///��������� ������ �� �������� ������. ������ ������ �� ��������.
	bool ModifyIndexDataRecord(unsigned int uiIndex, unsigned int uiEntryPoint, unsigned int uiDF);
	///���������� ������� ������ � ����������
	unsigned int GetIndexDF(unsigned int uiIndex);
	///���������� �� ������� ������ ����� ����� � ��������� ������� � ������� ������ � ����������
	bool GetIndexData(unsigned int uiIndex, unsigned int* puiOffset, unsigned int* puiDF);
	///������������� ������ �������
	bool InitScanOffsetDF();
	///������� � �������� ������
	bool MoveNext(unsigned int* puiSourceIndex, unsigned int* puiDF ) ; 

private:
	///������������� �������� ���������� ������� � ��
	bool InitAdd(void);
	///������������� ������ �� ������� ������
	bool InitFind(void* pvOffset, void* pvDF);
	///������������� ��������� ����� ������.
	bool InitModify(void* pvOffset, void* pvDF);

	///������ 
	unsigned int m_uiIndex;
	///����� ����� � ������������ ������
	unsigned int m_uiEntryPoint;
	///������ ���������� ��� ������ � DBMS. ����������.
	void* m_pToDataAdd[3];
	///������ ���������� ��� ��������� �����
	void* m_pToDataGet[3];
	///����� ���������, � ������� ����������� ������.
	unsigned int m_uiDF;
	///������ ���������� ��� ��������� ����� ������.
	void* m_pToDataModify[3];
	///������ ���������� ��� ������������ ����� ������.
	void* m_pToScanGet[3];
	
	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* m_pNdxTableStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}