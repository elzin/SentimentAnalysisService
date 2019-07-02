#pragma once

#include ".\table_storage.h"
#include ".\coordinate_counter.h"
#include ".\res_containers.h"
#include "..\ASCInterface\TCoommonTypes.h"

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

///��������� ����� �������
class CTextsFieldsStorage : public CTableStorage
{
public:
	CTextsFieldsStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* pNdxTableStorage);
	virtual ~CTextsFieldsStorage(void); 

	///������������ ���������� ��������� ����������
	void PrepareIndexing(void);
	///��������� �������� ��������� �� ��������� ����������
	void CompleteIndexing(void){};
	///��������� �������� ��������� �� ��������� ���������� ���������
	void CompleteDocumentIndexing(void){};

	///��������� ���������� �� ������
	void AddTextInfo(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pNdxMetaFieldCollection);
	///���������� ���������� � ������, ��� ���������� ����������� � CNdxMetaField
	void GetTextInfo(unsigned int uiTextIndex, SS::Interface::Core::NdxSE::CNdxMetaField* pNdxMetaField);
	///���������� ���������� � ������, ��� ���������� ����������� � CNdxMetaField
	void GetTextInfo(unsigned int uiTextIndex, SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pNdxMetaFieldCollection);
	///���������� ���������� �������
	unsigned int GetTextsNumber(void);
	///������� �����
	void DeleteText(unsigned int uiTextIndex);
	///��������� ����� ������� �� �������
	void GetTexts(SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pNdxMetaFieldCollection, 
		SS::Core::NdxSE::NdxProcessor::Containers::CFindResultCollection* pFindResults, 
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams);

protected:
	///������� ���������
	SS::Core::NdxSE::NdxProcessor::Indexing::CCoordinateCounter m_CoordinateCounter;
};

//--------------------------------------------------------------------//

}
}
}
}
}
