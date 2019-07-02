#pragma once

#include "..\ASDInterface\INdxDataStorage.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Indexing
{

//--------------------------------------------------------------------//

///������� ���������
class CCoordinateCounter
{
public:
	CCoordinateCounter(void);

	///���������� �������
	void Reset(void);
	///�������������� ���������� ������������ ����
	void Increment(SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::EIndexCoordinateType CoordinateType, unsigned int uiStep = 1);
	///���������� ���������� ������������ ����
	unsigned int GetCoordinate(SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::EIndexCoordinateType CoordinateType);
	///��������� �������� ���������� ������������ ����, ���������� ������� �� ������ ���������
	int Update(SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::EIndexCoordinateType CoordinateType, unsigned int uiValue);

protected:
	///���������� ���������� ������������ ����
	void ResetCoordinate(SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::EIndexCoordinateType CoordinateType);
	///���������� ����������� ���������� ��� ������������ ����
	void ResetSubCoordinates(SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo::EIndexCoordinateType CoordinateType);

	///���������� ����� ��������� � �������� �������� �������
	static const unsigned int m_uiCoordinatesTypesNumber=7;
	///������ �������� ���������� ���� �����
	unsigned int m_arCoordinates[m_uiCoordinatesTypesNumber];
	
};

//--------------------------------------------------------------------//

}
}
}
}
}