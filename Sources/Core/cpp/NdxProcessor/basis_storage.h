#pragma once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Storages
{

//--------------------------------------------------------------------//

///������� ���������
class CBasisStorage
{
public:
	CBasisStorage(void):m_WorkingMode(ewmExtracting){};
	virtual ~CBasisStorage(void){};

	///������ ������ ��������
	enum EWorkingMode
	{
		///����� ����������-����������
		ewmIndexing,
		///����� ����������-������
		ewmExtracting,
	};

	///���������� ����� ������ ���������
	EWorkingMode GetWorkingMode(void){return m_WorkingMode;};
	///������������� ����� ������ ���������
	void SetWorkingMode(EWorkingMode WorkingMode){m_WorkingMode=WorkingMode;};
	///������������ ���������� ��������� ����������
	virtual void PrepareIndexing(void) = 0;
	///��������� �������� ��������� �� ��������� ����������
	virtual void CompleteIndexing(void) = 0;
	///��������� �������� ��������� �� ��������� ���������� ���������
	virtual void CompleteDocumentIndexing(void) = 0;

protected:
	///����� ������ ���������
	EWorkingMode m_WorkingMode;
};

//--------------------------------------------------------------------//

}
}
}
}
}