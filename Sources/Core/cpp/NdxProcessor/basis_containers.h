#pragma once

#include ".\console.h"
#include ".\consoleclient.h"
#include "..\ASDInterface\INdxDataStorage.h"
#include ".\byte_align.h"

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

//--------------------------------------------------------------------//

///�������� - ������ ����� ���������� �������� � ������� ���������� 
class CValue : public CConsoleClient
{
public:
	CValue(void);
	virtual ~CValue(void);

	///��������� �������� AND
	virtual void MakeAnd(CValue* pValue);
	///��������� �������� AND �� ������������
	virtual void MakeSmoothAnd(CValue* pValue, unsigned int uiAdjacentSize);
	///��������� �������� OR
	virtual void MakeOr(CValue* pValue);
	///��������� �������� NOT
	virtual void MakeNot(CValue* pValue){TO_CONSOLE(L"Not ovveriden");};
	///��������� �� �������
	virtual bool IsEmpty(void){TO_CONSOLE(L"Not ovveriden"); return true;};
	///���������� �������� �� ������
	virtual void Reset(void){TO_CONSOLE(L"Not ovveriden");};

	///���������� ��� ��������
	float GetValueWeight(void){return m_fValueWeight;};
	///������������� ��� ��������
	void SetValueWeight(float fValue){m_fValueWeight=fValue;};
	///��������� � ���� ��������
	void AddToValueWeight(float fValue){m_fValueWeight+=fValue;};

protected:
	///��� ��������
	float m_fValueWeight;
};

//--------------------------------------------------------------------//

///�������� - ��������� �� ���������� ������������
class CCompositeValue : public CValue
{
public:
	//����� ������������ ������������
	///��������������� �� ������ ������������
	virtual bool MoveFirstOrt(void){TO_CONSOLE(L"Not ovveriden"); return false;};
	///��������������� �� �������� ������������
	virtual bool MoveNextOrt(void){TO_CONSOLE(L"Not ovveriden"); return false;};
	///��������������� �� ��������� ������������
	virtual bool MoveLastOrt(void){TO_CONSOLE(L"Not ovveriden"); return false;};
	///���������� ������� ������������
	virtual unsigned int GetCurrentOrt(void){TO_CONSOLE(L"Not ovveriden"); return 0;};

	///���������� ���������� ������������ ��������
	virtual unsigned int GetOrtsNumber(void){TO_CONSOLE(L"Not ovveriden"); return 0;};
	///���������� ����������� ��������� ���������� ������������ ��������
	virtual unsigned int GetOrtsMaxNumber(void){TO_CONSOLE(L"Not ovveriden"); return 0;};
	///������������� ������������
	virtual bool SetOrt(unsigned int uiValue){TO_CONSOLE(L"Not ovveriden"); return false;};
	///���������� ������������
	virtual bool UnsetOrt(unsigned int uiValue){TO_CONSOLE(L"Not ovveriden"); return false;};
	///��������� �� ������� ������������
	virtual bool HasOrt(unsigned int uiValue){TO_CONSOLE(L"Not ovveriden"); return false;};
};

//--------------------------------------------------------------------//

///����� ���������� ���������� �� ��������
typedef std::vector<CValue*> TValuePtrsBuffer;
///��������� - ����������
class CValuesContainer : public CConsoleClient
{
public:
	using CConsoleClient::ToString;

	CValuesContainer(unsigned int uiEntryPoint);
	virtual ~CValuesContainer(void);
	
	///���������� �������� ��������� ���������� �� ���������� �������������� ��������
	virtual void SetFreshValues(CValue* pPrevValue, TValuePtrsBuffer* pValuePtrsBuffer){TO_CONSOLE(L"Not ovveriden");};
	///����������� �������� �� ���������� ����������� ��������
	virtual void FreeValues(CValue* pGenerativeValue){TO_CONSOLE(L"Not ovveriden");};

	///������������ � ������
	void ToString(wstring& szValue);

protected:
	///����� ����� ��� ���������� ��������� ��������
	unsigned int m_uiEntryPoint;
};

//--------------------------------------------------------------------//

///������������ ����� ��������� ����������
class CBinaryContainer
{
public:
	virtual ~CBinaryContainer(void){};
	///���������� �������� �����
	virtual unsigned char* GetBinaryBuffer(void){TO_CONSOLE(L"Not ovveriden"); return NULL;};
	///���������� ������ ��������� ������
	virtual unsigned int GetBinaryBufferSize(void){TO_CONSOLE(L"Not ovveriden"); return 0;};
	///������������� ����� ������ ��������� ������, ����� �������
	virtual void InitBinaryBuffer(unsigned int uiNewSize){TO_CONSOLE(L"Not ovveriden");};
	///��������� �������� �����, �� ��������� ������
	virtual void FillBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize){TO_CONSOLE(L"Not ovveriden");};
	///������������ ���������� ��������� ������, ����� �� ������ �������� ����� ������ �������
	virtual void PreserveBinaryBuffer(void){TO_CONSOLE(L"Not ovveriden");};

	///����� ���������� ���������� � ����
	virtual unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
	///������ ���������� ���������� �� �����
	virtual void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	///����������� �� ������, ��������� ������ ����������
	virtual unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize){TO_CONSOLE(L"Not ovveriden");return 0;};
	///������� � �����
	virtual void ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBuffer){TO_CONSOLE(L"Not ovveriden");};

	///��������� ByteAlign
	static CByteAlignCompress* m_pByteAlignCompress;

protected:
	///������� 4 ����� � ����� � ����
	unsigned int WriteCompressed(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage, unsigned int uiValue);
	///������ � ��������� � 4 ����� �� ����
	unsigned int ReadCompressed(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
};

//--------------------------------------------------------------------//

///��������� ��������� ������
class CBinaryBufferContainer : public CBinaryContainer 
{
public:
	CBinaryBufferContainer(void);
	virtual ~CBinaryBufferContainer(void);

	///���������� �������� �����
	unsigned char* GetBinaryBuffer(void){return m_pucBuffer;};
	///���������� ������ ��������� ������
	unsigned int GetBinaryBufferSize(void){return m_uiBufferSize;};
	///������������� ����� ������ ��������� ������, ����� �������
	void InitBinaryBuffer(unsigned int uiNewSize);
	///��������� �������� �����, �� ��������� ������
	void FillBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize);
	///���������� �����
	void ResetBinaryBuffer(void);
	///������� ����� � �����
	void ReduceBackBinaryBuffer(unsigned int uiReducedSize);

protected:
	///����� � ��������������� �������� ������� � ���������
	unsigned char* m_pucBuffer;
	///������ ������������ ������ � ������
	unsigned int m_uiBufferSize;
};

//--------------------------------------------------------------------//

}
}
}
}
}