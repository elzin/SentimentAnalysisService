#pragma once

#include "../ASDInterface/INdxDataStorage.h"
#include "../ASCInterface/ICommonContainers.h"
#include ".\basis_storage.h"

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

///�������� � ����������� �� �������
class CTextsInfoStorage : public CBasisStorage
{
public:
	CTextsInfoStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* pNdxVectorStorage);
	virtual ~CTextsInfoStorage(void);
	
	///������������ ���������� ��������� ����������
	void PrepareIndexing(void){};
	///��������� �������� ��������� �� ��������� ����������
	void CompleteIndexing(void){};
	///��������� �������� ��������� �� ��������� ���������� ���������
	void CompleteDocumentIndexing(void){};

	///��������� ���������� �� ������
	unsigned int AddTextInfo(SS::Interface::Core::CommonContainers::ITextFeature* pTextFeature);
	///���������� ���������� �� ������
	void GetTextInfo(unsigned int uiTextIndex, SS::Interface::Core::CommonContainers::ITextFeature* pTextFeature);
	///������� �����
	void DeleteText(unsigned int uiTextIndex);
	///��������� ������ �� �����
	bool IsTextDeleted(unsigned int uiTextIndex);
	///���������� ���������� �������
	unsigned int GetTextsNumber(void){return m_pNdxVectorStorage->GetIndexesNumber();};

protected:
	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* m_pNdxVectorStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}