#pragma once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

const unsigned int arrMasks[]={0x0000007f, 0x00003f80, 0x001fc000, 0x0fe00000, 0xf0000000};
const unsigned char arrOffsets[]={0, 7, 14, 21, 28};

//--------------------------------------------------------------------//

///���������������� ��� ������ � �������� ������� ByteAlign
//� ������ ����� ������� ��� �������� ������ ���� 
//��� ��� ������� ����� ��������� ��� ���� ���� (��������� 7 ��� ��������), � �.�.
//����� ������� ��� ������ 32 ��� �������� ����� 36 ���, � ������� 8 ���.
class CByteAlignCompress
{
public:
	typedef vector<unsigned char> TBytesBuffer;

	///������� 4 ����� � ������ �����
	void EncodeToBuffer(unsigned int uiValue, TBytesBuffer* pBytesBuffer) const;
	///������� 4 ����� � ������ ����� � �������� �������
	void ReverseEncodeToBuffer(unsigned int uiValue, TBytesBuffer* pBytesBuffer) const;

	///��������� � 4 ����� �� ������, ������� � ������������� �����, ���������� ������� ���� �����������
	unsigned int Decode(unsigned char* pBytesBuffer, unsigned int uiBytesBufferSize, unsigned int uiStartByte, unsigned int* puiWorkedBytesNumber) const;
	///��������� � 4 ����� �� ������ ������ ��� ������ ReverseEncodeToBuffer, 
	//������� � ������������� �����, ���������� ������� ���� �����������, �������� ���������� � �������� ����������� �� uiStartByte
	//� ������
	unsigned int ReverseDecode(unsigned char* pBytesBuffer, unsigned int uiBytesBufferSize, unsigned int uiStartByte, unsigned int* puiWorkedBytesNumber) const;

	///������� 4 ����� � ������ ������ ������ �� ��������� ���������� ���������� �������� ����, 
	///���� puiEncodedValue=NULL , ������ ������ ���������� ���� �� �������������� ��������
	unsigned int Encode(unsigned int uiValue, unsigned int* puiEncodedValue) const;
	///��������� 4 ����� 
	void StartDecode(void){m_ucCurrentDecodedByte=0;};
	bool Decode(unsigned char ucValue, unsigned int* puiDecodedValue);
	
	///����� ��� ��������� 7 ���
	static const unsigned int m_cuiMask=0x0000007f;
	///����� ��� ������������ ��������� 8-�� ����
	static const unsigned char m_cucSignBit=0x80;
	///����� ��� ������ ��������� 8-�� ����
	static const unsigned char m_cucUnsignBit=0x7f;

	///���������� ���������� ������ ������ ��� ��������� ������� ��������
	unsigned char GetNeededBytesNumber(unsigned int uiValue) const
	{
		unsigned char i=5;
		unsigned char ucBytesNumber=0;
		if(!uiValue){
			//���� �� ����� ���� ��� ����� 1�� 7-�� �����
			ucBytesNumber=1;
		}else{
			//��� ���������� ���������� ���������� 7-�� �����
			do{
				--i;
				if(uiValue&arrMasks[i]){
					ucBytesNumber=i+1;
					break;
				}
			}while(i!=0);
		}	
		return ucBytesNumber;
	};

protected:

	///������� ������������ ����
	unsigned char m_ucCurrentDecodedByte;
};

//--------------------------------------------------------------------//

}
}
}
}
}