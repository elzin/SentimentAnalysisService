#pragma once

#include "..\ASSInterface\IBlackBoxDictionaryIndex.h"
using namespace SS::Interface::Core::BlackBox;
using namespace SS::Dictionary::Types;

#include <vector>


namespace SS
{
namespace Core
{
namespace BlackBox
{

class CDictionaryIndex : public IDictionaryIndex
{
public:
	CDictionaryIndex();
	virtual ~CDictionaryIndex();

public:
	///���������� ��������� ���������/��� ������
	void SetIsComposite(bool blValue);
	///���������/��� ������
	bool IsComposite();
	///���������� ������� � ��������
	void AppendIndex(TDictionaryIndex oIndex);
	///������� �������� ��������
	void Clear();
	///������� ������� ������
	void RemoveIndex();

	///��������� �������(��������) ������� ��������
	bool GetFirst(TDictionaryIndex* pIndex);
	///��������� ���������� ������� ��������
	bool GetNext(TDictionaryIndex* pIndex);
	///��������� �������(��������) ������� ��������
	TDictionaryIndex GetFirst();

private:
	TDictionaryIndex m_oIndex;
};

}
}
}
