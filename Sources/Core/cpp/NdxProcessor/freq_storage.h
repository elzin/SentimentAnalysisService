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

#pragma pack(push,1)  // Fix packing size 
///���������� �� ������� ��������� ������� � ��������
struct SIndexTF
{
	///�������� �������
	unsigned int m_uiIndex;
	///������� ��������� ������� � ��������
	unsigned int m_IndexFrequencyInText;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///��������� ������ �������� � ����������
class CIndexFrequencyStorage
{
public:
	CIndexFrequencyStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* pNdxVectorStorage);
	virtual ~CIndexFrequencyStorage(void);

	///��������� ��������� ������� �����
	void WriteIndexFreqs(vector<SIndexTF>& v_tf);
	///������������� ��� ����� ����������
	void SetTextComplete(void);
	///������ ���������� �� ������
	void ReadIndexFreqsForText(unsigned int uiTextNumber, map<unsigned int,unsigned int>& mm_tf);

protected:
	///������ ��������� ����� � ��������� ��� �������� ������
	unsigned int ReadIndexFreqsBuffer(vector<SIndexTF>& IndexFreqsBuffer);
	
	///���������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* m_pNdxVectorStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}