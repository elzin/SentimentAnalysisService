#pragma once

#include "..\ASCInterface\ITextFeature.h"
using namespace SS::Interface::Core::CommonContainers;

#include <string>

#include <assert.h>


namespace CommonContainers
{
namespace Define
{
		
//������ � ������ ������������ ������ � ������ ������

#define SIZEUI							sizeof (unsigned int)
#define SIZEI							sizeof (int)

#define SIZEPath						256
#define SIZETextName					256
#define SIZEAccessRights				256
#define SIZEBaseName					256

#define SIZEFirstSentenceAbsNumber		SIZEUI
#define SIZETextNumber					SIZEUI
#define SIZETextSize					SIZEUI
#define SIZETextFileSize				SIZEUI
#define SIZEPluginID					SIZEUI

#define SIZETextFileTime				sizeof (FILETIME)	
	
#define SIZEWithoutTitle (SIZEPath + SIZETextName + SIZEAccessRights + SIZEBaseName + SIZETextFileTime + (SIZEUI * 5))
	
}
}

namespace SS
{
namespace Core
{
namespace BlackBox
{

template <bool bAllocate>
class CTextFeatureBuff
{
private:
	int m_iPos;
	int m_iSize;
	BYTE* m_pBuff;
public:
	CTextFeatureBuff() :
			m_iPos(0),
			m_iSize(0),
			m_pBuff(NULL)
	{
	}

	~CTextFeatureBuff()
	{
		if(bAllocate && m_pBuff)
			delete m_pBuff;
	}

public:
	void Allocate(int iSize)
	{
		assert(bAllocate);
		if(m_pBuff) 
			delete m_pBuff;
		
		m_pBuff = new BYTE[iSize];
		m_iSize = iSize;
		m_iPos = 0;
	}

	void SetBuff(BYTE* pBuff, int iSize)
	{
		assert(!bAllocate);
		m_pBuff = pBuff;
		m_iSize = iSize;
		m_iPos = 0;
	}

	void Concatenate(void* pSource, int iSize)
	{
		assert(m_iPos + iSize <= m_iSize);
		if(pSource)
			memcpy(m_pBuff + m_iPos, pSource, iSize);
		m_iPos += iSize;
	}

	void Copy(void* pDest, int iSize)
	{
		assert(m_iPos + iSize <= m_iSize);
		memcpy(pDest, m_pBuff + m_iPos, iSize);
		m_iPos += iSize;
	}

	int GetSize()
	{
		return m_iPos;
	}

	int GetCapacity()
	{
		return m_iSize;
	}

	BYTE* GetBuff()
	{
		return m_pBuff;
	}

};

///������������ ������������� ������
/**��������� ���������������� ���������� SS::Interface::Core::CommonContainers::ITextFeature*/

class CTextFeature : public SS::Interface::Core::CommonContainers::ITextFeature
{
	CTextFeatureBuff<true> m_oOutputBuff;
	CTextFeatureBuff<false> m_oInputBuff;
protected:
	wchar_t			m_szPath[SIZEPath];							// ���� � ������
	wchar_t			m_szTextName[SIZETextName];					// ��� ������
	char			m_szAccessRights[SIZEAccessRights];			// ����� �������
	char			m_szBaseName[SIZEBaseName];					// ��� ����
	unsigned int	m_FirstSentenceAbsNumber;					//���������� ����� ������� ����������� ������
	unsigned int	m_TextNumber;								// ����� ������
	unsigned int	m_TextSize;									// ������ ������
	FILETIME		m_TextFileTime;								// ����� ���������� ��������� ����� � �������
	unsigned int	m_TextFileSize;								// ������ ����� ������
	unsigned int	m_PluginID;									// ID �������

private:
	//����������� ������
	void Init();
	void Del();

public:
	CTextFeature(void);
	virtual ~CTextFeature(void);

	//������ IBase
	virtual ULONG Release();
	virtual HRESULT QueryInterface(REFIID pIID, void** pBase);	//���������� � ���������� � �������� REFIID. 
	//pBase ����� NULL, ���� ������ ��������� �� ��������������

	///������ ������, ���������� ������ � ������
	unsigned int GetMemorySize();

	//������ ITextFeature
	virtual void GetTextFeatureBuff(char** ppBuff, unsigned int* pSize);
	virtual void SetTextFeatureBuff(char* pBuff, unsigned int Size);
	///�������� ���� � ������
	virtual const wchar_t* GetTextPath();
	///�������� ���� � ������
	virtual void SetTextPath(const wchar_t* szPath);
	///�������� ��� ������
	virtual const wchar_t* GetTextName();
	///�������� ��� ������
	virtual void SetTextName(const wchar_t* szName);
	///�������� ����� �������
	virtual const char* GetAccessRights();
	///�������� ����� �������
	virtual void SetAccessRights(const char* szAccessRights);
	///�������� ��� ����
	virtual const char* GetBaseName();
	///�������� ��� ����
	virtual void SetBaseName(const char* szName);
	///������� �������� ��������������
	virtual void Clear();
	///������������ ����������� ������ ������� ����������� ������
	virtual void SetFirstSentenceAbsNumber(unsigned int uiValue)
	{
		m_FirstSentenceAbsNumber = uiValue;
	};
	///��������� ����������� ������ ������� ����������� ������
	virtual unsigned int GetFirstSentenceAbsNumber()
	{
		return m_FirstSentenceAbsNumber;
	};
	///������������ ������ ������
	virtual void SetTextNumber(unsigned int uiValue)
	{
		m_TextNumber = uiValue;
	}
	///��������� ������ ������
	virtual unsigned int GetTextNumber()
	{
		return m_TextNumber;
	}
	///������������ ������� ������
	virtual void SetTextSize(unsigned int uiValue)
	{
		m_TextSize = uiValue;
	}
	///��������� ������� ������
	virtual unsigned int GetTextSize()
	{
		return m_TextSize;				
	}
	///������ ����� ���������� ��������� ����� � �������
	virtual const FILETIME GetTextFileTime() const
	{
		return (m_TextFileTime);
	}
	///������������� ����� ���������� ��������� ����� � �������
	virtual void SetTextFileTime(const FILETIME* pFileTime)
	{
		m_TextFileTime = (*pFileTime);
	}
	///������������� ������ ����� ������
	virtual void SetTextFileSize(const unsigned int ulFileSize)
	{
		m_TextFileSize = ulFileSize;
	}
	///���������� ������ ����� ������
	virtual const unsigned int GetTextFileSize() const
	{
		return m_TextFileSize;
	}
	///������������� ID �������
	virtual void SetPluginID(const unsigned int uiPluginID)
	{
		m_PluginID = uiPluginID;
	}
	///���������� ID �������
	virtual const unsigned int GetPluginID() const
	{
		return m_PluginID;
	}

	virtual ITitle* GetFirstTitle()
	{
		return NULL;
	}

	virtual void AddTitle(int nBegin, int nEnd, int iType)
	{
		SS_THROW(L"��������� ������������ ���� �����");
	}
};

}
}
}
