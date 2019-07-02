#pragma once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{

//--------------------------------------------------------------------//

///��������� ����������� ���������� � ��������
class CCoordinateConvertor
{
public:
	///��������� �������� � ����� � ������ ����� �� �����
	static void InsertToCoordinate(unsigned int* puiCoordinate, unsigned int uiValue, unsigned char ucStartBit, unsigned char ucBitPerLevel);
	///������� �������� �� ����� �� ������� ����� �� �����
	static unsigned int SplitCoordinate(unsigned int uiCoordinate, unsigned char ucStartBit, unsigned char ucBitPerLevel);
};

//--------------------------------------------------------------------//

}
}
}
}
