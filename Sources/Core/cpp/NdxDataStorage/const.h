#pragma		once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

//---------------------------------------------
//��������������� ���������
const unsigned int EMPTY_OFFSET=0xffffffff;
const unsigned int EMPTY_VALUE=0xffffffff;
const unsigned int EMPTY_SOURCE=0xffffffff;
const unsigned int EMPTY_NODE=0xff;
const unsigned int UC_EMPTY=0xff;
const unsigned int INT_SIZE=4;

//---------------------------------------------
//��������� ������
const unsigned int cuiChunkSize=64;

//---------------------------------------------
//��������� ��� ������ � ���������� ������

///������������ ������ ������ � ���������
const unsigned int cuiMaxFileSize=1500000000;
///������������ ���������� ������ � ���������
const unsigned int cuiMaxFilesNumber=0xff; 
///������ ����� ��� �������� �� �������� ������������� ������
const unsigned int cuiRootFileIndex=254; 

//---------------------------------------------
//��������� ��� �����������

///������ ��������� �������� ������
const unsigned int cuiPageSize=4096;
///������ ������ � �������� ���� �������� �����
const unsigned int cuiCommonFileBufferSize=(cuiPageSize*16);
///������ ������ ������ � �������� ���� �������� �����
const unsigned int cuiReadFileBufferSize=cuiPageSize;
///������������ ���������� ������� � �������� ����
const unsigned int cuiMaxBufferNumber=0xff;
///������ ������ � �������� ���� ����� �������� � ��������� �����
const unsigned int cuiOffsetsFileBufferSize=3000000;
///������ ������ � �������� ���� ����� ������ � ��������� �����
const unsigned int cuiDataFileBufferSize=3000000;
///������������ ������ ������������� ����������� � ��������� ���� ������
const unsigned int cuiMaxWorkedBoundDataSize=0xffffffff;
///����������� ������ ��������� ���� ������� ����� �������� �� ����
const unsigned int cuiCashMinSizeToFlush=0;//10000000;
///����������� ���������� ������� ������� ��������� ����
const double cdbBufferSizeReductionKoef=1.5;

//---------------------------------------------

}
}
}
}
