#pragma once
#include <stdio.h>

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxBaseManager
{

//--------------------------------------------------------------------//

///���� ��������� ������ ������
enum ErrorCode
{
	///������� �������� 
	erIsNull,
	///�������� �� �������
	erNotFind,
	///�������� �� ������������
	erNotEqual,
	///������ DBMS
	erDBMS,
	///������ ���������� �������� � ����
	erTryCatch,
	///���������� �����
	erBadHandle,
	///�������� ������
	erFileIO
};

///����������� ������ �� ���������
int st_free (void *mem);
///�������� ������ �� ���������
void* st_malloc		 (unsigned long n_bytes);

///������� �� �������
void ToConsole(const wchar_t* pszString);
///������� �� �������
void ToConsoleEx(const wchar_t* pszString, const wchar_t* pszDest, const wchar_t* pszFile, long Line);
///������� �� �������
void ToConsole(const wchar_t* pszString, double dbValue);
///������� �� �������
void ToConsole(const wchar_t* pszString, unsigned int uiValue);
///������� �� �������
void ToConsole(unsigned char* pBuffer, unsigned int uiSize);
///������� �� ������� ��������� ������
void ViewMemoryStatus(void);
///���������� �������������� ������
unsigned int GetMemoryStatus(void);
///������� ������ � ����� �� �������
void ErrorToConsole(ErrorCode EC, const wchar_t* pszString, const wchar_t* pszDest, const wchar_t* pszFile, long Line);

extern bool g_bStopLogging;

#define UT_STOP_LOGING \
		g_bStopLogging=true;
#define UT_START_LOGING \
		g_bStopLogging=false;

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)

#define __WFILE__ WIDEN(__FILE__)
#define __WFUNCTION__ WIDEN(__FUNCTION__)

///��������� �� ������� ��������
#define ISNULL(x) \
	x==NULL?ErrorToConsole(erIsNull, WIDEN(#x), __WFUNCTION__,  __WFILE__, __LINE__), true:false
///������� ������ �� �������
#define ERR_TO_CONSOLE(code, s) \
{ErrorToConsole(code, s, __WFUNCTION__, __WFILE__, __LINE__);}
///������� ��������� �� �������
#define TO_CONSOLE(s) \
	ToConsoleEx(s, __WFUNCTION__,  __WFILE__, __LINE__);

//--------------------------------------------------------------------//

///�������� ��������� ������������� ���������� ������� ����
class CTickMeasure
{
public:
	CTickMeasure():m_iStartTick(0), m_iStopTick(0), m_iSumTick(0), m_uiStartsCount(0){};
	virtual ~CTickMeasure(){};
	
	///���������� �������
	unsigned int m_uiStartsCount;
	///������� �����
	__int64 m_iStartTick;
	///������� �������
	__int64 m_iStopTick;
	///����� ����� ����������
	__int64 m_iSumTick;
};

//--------------------------------------------------------------------//

///���������� ��������� ������� ���������� ������� ����
class CTickManager  
{
public:
	
	#pragma warning( disable : 4996 )
	typedef std::unordered_map<wstring, CTickMeasure> TTickMeasures;
	#pragma warning( default : 4996 )

	CTickManager();
	virtual ~CTickManager();

	///������ �������� ������� ����������
	void	StartTick(const wchar_t* szID);
	///������� �������� ������� ����������
	void	StopTick(const wchar_t* szID);
	///������� ������� ����������
	double	GetTicks(const wchar_t* szID);
	///����������� ������� ����������
	void	ViewTicks(const wchar_t* szID);
	///����������� ���� ������� ������� ����������
	void	ViewTicks(void);

protected:
	///��������� ������� ������� ����������
	TTickMeasures m_TickMeasures;
};

//--------------------------------------------------------------------//

///������ ����������� ��������� ������� ����������
extern CTickManager TickManager;

///��������� ������� ������� �� ��������������
#define START_TICK(sID) \
	TickManager.StartTick(sID);

///������������� ������� ������� �� ��������������
#define STOP_TICK(sID) \
	TickManager.StopTick(sID);

///����������� ������� ���������� �� ��������������
#define VIEW_TICK(sID) \
	TickManager.ViewTicks(sID);

///����������� ���� ������� ������� ����������
#define VIEW_TICKS() \
	TickManager.ViewTicks();

//--------------------------------------------------------------------//

}
}
}
}
