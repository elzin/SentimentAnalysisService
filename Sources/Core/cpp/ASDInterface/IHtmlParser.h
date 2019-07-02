#pragma once
#include "..\ASCInterface\iinterface.h"
//--------------------------------------------------------------------//
/// guid ��� ������, ��������������� IHtmlData
static const GUID CLSID_HtmlData =  { 0x28ad6bc1, 0x8431, 0x49e6, { 0x9e, 0xe4, 0x27, 0xfe, 0xba, 0x02, 0x1e, 0x12 } };
/// guid ��� ���������� IHtmlData
static const GUID IID_HtmlData =  { 0xf11090b5, 0x3307, 0x4f27, { 0x95, 0x5d, 0xdc, 0xbe, 0x8c, 0x18, 0xea, 0x43 } };
/// guid ��� ������, ��������������� IHtmlParser
static const GUID CLSID_HtmlParser =  { 0xf2371f7f, 0xee13, 0x42a0, { 0x96, 0x1d, 0xf3, 0xfa, 0xc6, 0xe2, 0x96, 0x72 } };
/// guid ��� ���������� IHtmlParser
static const GUID IID_HtmlParser =  { 0x6f7dde8b, 0x7638, 0x4af1, { 0x83, 0x60, 0xdd, 0x4b, 0x94, 0x25, 0xb5, 0x6b } };
//--------------------------------------------------------------------//
namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace  PluginsUtils
			{
				//--------------------------------------------------------------------//
				// ��������� ��� ������ � �������� HTML ����������
				class IHtmlData : public SS::Interface::IBase
				{
					public:
						virtual void Init() = 0;
						virtual void AddConstraints(int iKey, int iValue) = 0;
						virtual bool GetStringValue(int iKey, const wchar_t** pValue) = 0;
						virtual bool GetIntValue(int iKey, unsigned int* iValue) = 0;
						virtual bool SetCurrentTable(unsigned int iTableNum) = 0;
						virtual bool SetCurrentCell(unsigned int iCellNum) = 0;
				};
				//--------------------------------------------------------------------//
				///��������� �������� HTML ����������.
				class IHtmlParser : public SS::Interface::IBase
				{
					public:
						virtual bool ParseHtml(	const unsigned char* pHtmlContent,
												unsigned int iContentLen,
												SS::Interface::Core::PluginsUtils::IHtmlData* pData) = 0;
				};
				//--------------------------------------------------------------------//
			}
		}
	}
}

//--------------------------------------------------------------------//

// ���������������� ���� ����������
// ��� ����������
#define MarkNone		0
// ��������� 1-�� ������
#define MarkH1			1
// ��������� 2-�� ������
#define MarkH2			2
// ��������� 3-�� ������
#define MarkH3			3
// ��������� 4-�� ������
#define MarkH4			4
// ��������� 5-�� ������
#define MarkH5			5
// ��������� 6-�� ������
#define MarkH6			6
// ������ �������
#define MarkCell		7
// �����������
#define MarkDefinition	8
// ������������ ������
#define MarkDefTerm		9

// �������������� �����
// ����� �� HTML
#define StrText			1
// ���������
#define StrTitle		2
// ��������
#define StrDescription	3
// �������� �����
#define StrKeyword		4
// �����
#define StrAuthor		5
// ���������
#define StrCharset		6
// �������� ������� �������
#define StrTableName	7
// ��������� ������� �������
#define StrTableHeader	8
// ����� ������� ������
#define StrCellText		9


// �������������� �����
/// ����� ������
#define IntNumOfTables		10
/// ����� ����� � �������
#define IntNumOfCells		11
/// ������ ������ �������
#define IntTableStart		12
/// ����� ������ �������
#define IntTableEnd			13
/// ������ ������ �������
#define IntTableMaxRow		14
/// ����� ������ �������
#define IntTableMaxCol		15
/// ������
#define IntRow				51
/// �������
#define IntCol				52
/// ���������� ������
#define IntRowSpan			53
/// ���������� �������
#define IntColSpan			54
/// ������ ������ ������
#define IntCellStart		55
/// ����� ������ ������
#define IntCellLength		56
/// ������ - ��������� 
#define IntCellHeader		57
/// ������ � ������ �������
#define IntCellEmptyText	58





// �����������
/// ���� ���������� �����
#define  CtrMaxRows				1
/// ���� ���������� ��������
#define  CtrMaxCols				2
/// ����������� ���������� �����
#define  CtrMinRows				3
/// ����������� ���������� ��������
#define  CtrMinCols				4
/// ����� � ������� 1 � ���������
#define  CtrDisableLinks		5
/// ������� � ������� 1 � ���������
#define  CtrDisableScripts		6
/// ����������� true � ���������
#define  CtrDisableImg			7
/// ���������� ����� ������ ����� (0-100 %)
#define  CtrEmptyRows			8
/// ���������� ����� ������ �������� (0-100 %)
#define  CtrEmptyCols			9
/// ���������� ����� �������� ����� (��)
#define  CtrNonEmptyRows		10
/// ���������� ����� �������� �������� (��)
#define  CtrNonEmptyCols		11
/// ������ ������ ����������� ��������� 1=��
#define  CtrFullFirstRow		12
/// ������������ ������ ������ � ������
#define  CtrMaxCellTextSize		13
/// 1=����� ������� - � ������� ������������ ������� ���������� �������
#define  CtrDebugMode			14

//--------------------------------------------------------------------//