#pragma		once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{

//---------------------------------------------
//��������������� ���������
const unsigned int EMPTY_OFFSET=0xffffffff;
const unsigned int EMPTY_VALUE=0xffffffff;
const unsigned int EMPTY_SOURCE=0xffffffff;
const unsigned int EMPTY_NODE=0xff;
const unsigned int UC_EMPTY=0xff;
const unsigned int INT_SIZE=4;

namespace Containers
{

	//---------------------------------------------
	//������ ��� �������� ���������� �������� ������
	const unsigned int carrBmSizes[]={
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 
	0x00000010, 0x00000020, 0x00000040, 0x00000080, 
	0x00000100, 0x00000200, 0x00000400, 0x00000800, 
	0x00001000, 0x00002000, 0x00004000, 0x00008000, 
	0x00010000, 0x00020000, 0x00040000, 0x00080000, 
	0x00100000, 0x00200000, 0x00400000, 0x00800000, 
	0x01000000, 0x02000000, 0x04000000, 0x08000000, 
	0x10000000, 0x20000000, 0x40000000, 0x80000000};

	//---------------------------------------------
	///����������� �� ���������� ��� � ������� �����
	const unsigned int cuiBitsLimitNumber=4096;
	///������ ������� ��������� ������ ��
	const unsigned int cuiBoundBmBlocksArraySize=10;
	///������ ������� ���������� ����������� � �������
	const unsigned int cuiSentencesCountSize=16/*100*/;
	///������ ������� ����� ��� �������� ������� ����
	const unsigned int cuiPosBitMapSize=0xff;
	
	///������ ����� ������ ���������� CB�CoordinateNode_4i 
	const unsigned char cucBaCoordinateNode_BlockBufferSize=32;
	///������ ����� ������ ���������� CBmCoordinateNode_4i 
	const unsigned char cucBmCoordinateNode_BlockBufferSize=64;
	///������ ����� ������� ���������� CBaCoordinateNode_4i_Blocked 
	const unsigned int cuiPositionBlockSize=255;

	///���������� ����������� ������� ���������� 
	const unsigned int cuiHeaderLevelsNumber=2;

	//---------------------------------------------
}

}
}
}
}
