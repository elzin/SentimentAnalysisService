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

///��������� ����������� ������������� ����������, 
///� �������� ���� �������� ������� ���������� � ������
///�� ������� ������� ��������� ����� ���������� ���� � ��������� ������� ������ �������������� �� �������
class CDocNormStorage
{
public:
	CDocNormStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxDocNormStorage);

	///���������� ����� ��������� �� �������������� ���������
	unsigned int GetDocNorm(unsigned int uiDocId);
	///��������� ����� ���������
	void AddDocNorm(unsigned int uiDocNorm);

	///���������� ����� ���������� ���� � ���������
	unsigned int GetTotalWordsCount(void);

protected:
	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* m_pNdxDocNormStorage;
	///����� ���������� ����
	unsigned int m_uiTotalWordsCount;
};

//--------------------------------------------------------------------//

}
}
}
}
}