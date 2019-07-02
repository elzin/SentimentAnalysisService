#pragma once

#include ".\console.h"
#include ".\const.h"
#include ".\basisfile.h"
#include ".\file_cash_members.h"


namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{
namespace FileCash
{

class SS::Core::NdxSE::NdxDataStorage::CBasisFile;

//--------------------------------------------------------------------//

///�������� ���
class CFileCash
{
public:
	typedef CCircularBuffer<CBuffer> TFileCashBuffers;

	CFileCash(unsigned int uiBufferSize, unsigned int uiBuffersMaxNumber);
	virtual ~CFileCash(void){Clear();};

	///������������� ����
	void Init(SS::Core::NdxSE::NdxDataStorage::CBasisFile* pCashedFile){if(!m_pCashedFile) m_pCashedFile=pCashedFile;};

	///��������� ������ � �����
	virtual void AddData(unsigned char* pucData, unsigned int uiSize);
	///������ ������ �� ������� �������
	virtual void Read(unsigned char* pucData, unsigned int uiSize);
	///������ ������ �� ������� �������, ��� ������ �������
	virtual void Look(unsigned char* pucData, unsigned int uiSize);
	///����� ������ �� ������� �������
	virtual void Write(unsigned char* pucData, unsigned int uiSize);

	///����������� ������� ������� � ����
	void SeekPos(unsigned int uiOffset, unsigned int uiOrigin);
	///��������� ������� �������
	unsigned int TellPos(void);

	///������������� �������� � �����
	void	SetFileOffset(unsigned int uiValue){m_uiFileOffset=uiValue;};
	///���������� �������� � �����
	unsigned int	GetFileOffset(void){return m_uiFileOffset;};
	///���������� ������ ������ � ����
	unsigned int	GetFilledSize(void);

	///���������� ������ � ����
	void FlushToFile(void);
	///���������� ������ �� ����������� ������� ���� ����� � ����
	void FlushFilledBuffersToFile(void);

	///������� ��� ����������� ������
	void Clear(void);
	
	///���������� ���������� �������
	void View(void);

protected:
	///��������� �����
	CBuffer* AddBuffer(void);

	///������� ������� � ����
	CCashPosition m_CurrentCashPosition;
	///�������� ������� ����
	TFileCashBuffers m_FileCashBuffers;
	///����, ������� ������������� �����
	CBasisFile* m_pCashedFile;
	///������ ������ ���������
	const unsigned int m_uiBufferSize;
	///������� �������� � ����� ������ ���������� ���
	unsigned int m_uiFileOffset;
};

//--------------------------------------------------------------------//

///�������� ��� ������
class CReadFileCash : public CFileCash
{
public:
	CReadFileCash(unsigned int uiBufferSize);
	virtual ~CReadFileCash(void);

	///������ ���� � �����
	void	FillFromFile(void);

protected:
	///��������� ������ � �����
	void AddData(unsigned char* pucData, unsigned int uiSize){TO_CONSOLE(L"Proxed");};
	///����� ������ �� ������� �������
	void Write(unsigned char* pucData, unsigned int uiSize){TO_CONSOLE(L"Proxed");};
	///���������� ������ � ����
	void	FlushToFile(CBasisFile* pFile){TO_CONSOLE(L"Proxed");};
	///���������� ������ �� ����������� ������� ���� ����� � ����
	void	FlushFilledBuffersToFile(CBasisFile* pFile){TO_CONSOLE(L"Proxed");};
};

//--------------------------------------------------------------------//

}
}
}
}
}