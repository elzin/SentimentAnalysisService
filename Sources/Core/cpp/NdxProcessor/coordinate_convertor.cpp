#include "StdAfx.h"
#include ".\coordinate_convertor.h"
#include ".\console.h"

//--------------------------------------------------------------------//

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{

void CCoordinateConvertor::InsertToCoordinate(unsigned int* puiCoordinate, unsigned int uiValue, unsigned char ucStartBit, unsigned char ucBitPerLevel)
{
	if(ISNULL(puiCoordinate)) return;

	//���������� ����� ������
	unsigned int uiLevelMask=0xffffffff>>(32-ucBitPerLevel);
	
	//�������� ����� � ������ �����
	uiLevelMask=uiLevelMask<<((ucStartBit+1)-ucBitPerLevel);
	uiLevelMask=~uiLevelMask;

	//�������� �������� � ������ �����
	uiValue=uiValue<<((ucStartBit+1)-ucBitPerLevel);

	//������� �� � � ������
	(*puiCoordinate)&=uiLevelMask; 
	//������� �� ��� �� ���������
	(*puiCoordinate)|=uiValue; 
}

unsigned int CCoordinateConvertor::SplitCoordinate(unsigned int uiCoordinate, 
														unsigned char ucStartBit, 
														unsigned char ucBitPerLevel) 
{
	//���������� ����� ������
	unsigned int uiLevelMask=0xffffffff>>(32-ucBitPerLevel);
	
	//�������� ����� � ������ �����
	uiLevelMask=uiLevelMask<<((ucStartBit+1)-ucBitPerLevel);
	//������� �� � � �����������
	uiCoordinate&=uiLevelMask; 
	//�������� �������
	uiCoordinate=uiCoordinate>>((ucStartBit+1)-ucBitPerLevel);

	//���������� ���������� �������� 
	return uiCoordinate;
}

//--------------------------------------------------------------------//

}
}
}
}


