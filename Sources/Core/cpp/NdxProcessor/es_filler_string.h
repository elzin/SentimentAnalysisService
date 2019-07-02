#pragma once

#include ".\es_filler.h"
#include ".\index_storage.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{

//--------------------------------------------------------------------//

///����������� - �������� �� ���������� ������ � �������������� ����������� ������ ���������� ��� ��� ���������� �������
class CESFillerFromString : public CESFillerEx<wstring>
{
public:
	CESFillerFromString(Containers::CContainersFactory* pCntFactory, wstring* pExpression);
	virtual ~CESFillerFromString(void);

	///���������� ������� � ������������� ����������� � ����������� ��������	
	void Fill(CCalcEquation* pEquation, CSubster* pSubster);
	///���������� ��������� LBaseSearchWords
	void ViewFillingSource(void);

protected:
	///����������� ����� �� ���������� ��������� ������� � �������� �������
	unsigned int GetToken(wstring* pszExpression, unsigned int uiCurrPos, wstring* pszToken);
};

//--------------------------------------------------------------------//

}
}
}
}
}