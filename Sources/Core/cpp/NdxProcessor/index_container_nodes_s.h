#pragma once

#include "..\ASDInterface\INdxDataStorage.h"
#include ".\box_containers_s.h"
#include ".\pos_ba_containers_s.h"
#include ".\node_containers.h"
#include ".\cnt_factory.h"

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

///��������� - ������� ������������ ����, ����� ������ ���� �� ��������� 
///�������� �������� �� ����������� ����
class CCoordinateNode_4s : 
	public CTreeNode<CCoordinateNode_4s*> , public CBinaryContainer, 
	public CConsoleClient, public CFactoryClient<CContainersFactory>
	
{
public:
	CCoordinateNode_4s(CContainersFactory* pContainersFactory)
		:CFactoryClient<CContainersFactory>(pContainersFactory){};
	~CCoordinateNode_4s(void){ResetNode();};
	
	using CConsoleClient::ToString;

	///���������� �������� �� ����������� ���� �� �������� ����
	virtual void GetChildOffset(unsigned int uiValue, SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset){};	
	///��������� ���� �� �������� � ��������� �����
	virtual void AddChildNode(unsigned int uiValue, CCoordinateNode_4s* pChild);	
	///���������� ����
	virtual void ResetNode(void);	
	///�������� ����������� ����, ��������� ���� � �����������
	virtual CCoordinateNode_4s* MoveUpChildNode(unsigned int uiValue);
	///������ ���� �� ���������
	void ReadNode(CCoordinateNode_4s* pCoordinateNode, SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset);

	///������������ � ������
	void ToString(wstring& szValue, wstring szOffset);

protected:
	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* GetCoordinatesStorage(void){return GetFactory()->GetIndexStorage()->GetCoordinateStorage();};
};

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ � ������� �����
///�������� �������� �� ����������� ���� � ������������� ��������� �� ��������� ��� � �����
///�������� ������������ ������ �� ���������
class CBmCoordinateNode_4s : 
	public CBitMap_4s,
	public CCoordinateNode_4s
{
public:
	typedef map<unsigned int, SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset> TChildsOffsets;

	CBmCoordinateNode_4s(unsigned int uiBitMapSize, CContainersFactory* pContainersFactory)
		:CBitMap_4s(uiBitMapSize), CCoordinateNode_4s(pContainersFactory){};
	~CBmCoordinateNode_4s(void){ResetNode();};

	///���������� �������� �� ����������� ���� �� �������� ����
	void GetChildOffset(unsigned int uiValue, SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pCompositeOffset);	
	///���������� ����
	void ResetNode(void);	

	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);

	///������������ � ������
	void ToString(wstring& szValue);
	///���������� ���������� ������� ������
	void View(void);
protected:
	///��������� �������� ����������� ����� �� ���������
	TChildsOffsets m_ChildsOffsets;
};

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ � ������� �����
///�������� �������� �� ����������� ���� � ������������� ��������� �� ��������� ��� � �����
///�������� ������������ ������ �� ���������
class CBmCoordinateNode_4s_Heavy : 
	public CBmCoordinateNode_4s 
{
public:
	CBmCoordinateNode_4s_Heavy(unsigned int uiBitMapSize, CContainersFactory* pContainersFactory)
		:CBmCoordinateNode_4s(uiBitMapSize, pContainersFactory){};

	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage);
};

//--------------------------------------------------------------------//

///��������� - ������������ ���� 
///�������� ������ ������� ByteAlign
///�������� ������������ ������ �� ���������
template <class TBasisContainer>
class CBaCoordinateNode_4s : 
	public TBasisContainer,
	public CCoordinateNode_4s
{
public:
	CBaCoordinateNode_4s(CContainersFactory* pContainersFactory)
		:CCoordinateNode_4s(pContainersFactory){};

	///������ ���������� ���������� �� ���������
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage)
	{
		if(ISNULL(pNdxStorage)) return;

		START_TICK(L"CBaCoordinateNode_4s::Read");

		//������ ��������� ���������
		TBasisContainer::Read(pNdxStorage);

		STOP_TICK(L"CBaCoordinateNode_4s::Read");
	};

	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize)
	{
		if(ISNULL(pBuffer)) return 0;
		if(ISNULL(uiBufferSize)) return 0;

		//������ ��������� ���������
		return TBasisContainer::FromBinaryBuffer(pBuffer, uiBufferSize);
	};

	///���������� ����
	void ResetNode(void)
	{
		TBasisContainer::Reset();
		CCoordinateNode_4s::ResetNode();
	};


	///������������ � ������
	void ToString(wstring& szValue)
	{
		TBasisContainer::ToString(szValue);
	};

	///���������� ���������� ������� ������
	void View(void)
	{
		wstring szValue;
		szValue.append(L"\n//-------CBaCoordinateNode_4s\n");
		ToString(szValue);
		szValue.append(L"\n//-------Eof-CBaCoordinateNode_4s\n");
		ToConsole(szValue.c_str());
	};
};

//--------------------------------------------------------------------//

}
}
}
}
}