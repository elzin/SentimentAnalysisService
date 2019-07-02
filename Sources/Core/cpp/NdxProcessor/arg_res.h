#pragma once

#include ".\arg.h"
#include ".\node_containers.h"

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

	class CIndexStorage;
}
}
}
}
}

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

///�������� ������� - ���� �������, ������������ ����������� ������� ���������� �������� �������
class CResultArgument : public SS::Core::NdxSE::NdxProcessor::Containers::CTreeNode<CArgumentEx*>, public CConsoleClient
{
public:
	typedef vector<unsigned int> THistoryBuffer;

	CResultArgument(unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, float fKoeff = 1.0);
	virtual ~CResultArgument(void);

	///��������� ������� ������� ����
	CResultArgument* AddChild(CResultArgument* pChildArgument);
	///���������� ������������ ����
	CResultArgument* GetParent(void){return ((CResultArgument*)(SS::Core::NdxSE::NdxProcessor::Containers::CTreeNode<CArgumentEx*>::GetParent()));};
	///���������� �������� �������
	CResultArgument* GetCurrentChild(void){return ((CResultArgument*)(SS::Core::NdxSE::NdxProcessor::Containers::CTreeNode<CArgumentEx*>::GetCurrentChild()));};
	///���������� ������� �� ��������������
	CResultArgument* GetChild(unsigned int uiChildId);
	///���������� ����� ������� �������� ����������
	THistoryBuffer* GetHistoryBuffer(void){return &m_HistoryBuffer;};

	///��������� �������� � ��������
	void Calculate(CArgument* pArgument){TO_CONSOLE(L"Do nothing");};
	///�������� ����� �� ������ �������
	void CutByDepth(unsigned int uiDepth);
	///���������� ���� ������������� ����������
	bool IsProcessed(void){return m_bProcessed;};
	///������������� ���� ������������� ����������
	void SetProcessed(void){m_bProcessed=true;};
	///��������� ������� ������������� �� ������� ����������
	unsigned int CalculateBaseIDFromResultHistory(Storages::CIndexStorage* pIndexStorage);
	


	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);
	///���������� ���������� ������� ������
	void View(void);

protected:
	///��������� ������� ������� ����
	SS::Core::NdxSE::NdxProcessor::Containers::CTreeNode<CArgumentEx*>* 
		AddChild(unsigned int uiChildID, SS::Core::NdxSE::NdxProcessor::Containers::CTreeNode<CArgumentEx*>* pChildNode){TO_CONSOLE(L"Proxed"); return NULL;};
	///����� ������� �������� ����������
	THistoryBuffer m_HistoryBuffer;
	///���� ������������� ����������
	bool m_bProcessed;
};

//--------------------------------------------------------------------//

}
}
}
}
}