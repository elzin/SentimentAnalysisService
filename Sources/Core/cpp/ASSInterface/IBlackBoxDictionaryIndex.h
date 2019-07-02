#pragma once

#include "./TDictionaryManager.h"


namespace SS
{
namespace Interface
{
namespace Core
{
namespace BlackBox
{

/// ������������ �������, ������� ������������ ��� ����������/������
	class IDictionaryIndex
	{
	public:
		///���������� ��������� ���������/��� ������
		virtual void SetIsComposite(bool blValue) = 0;
		///���������/��� ������
		virtual bool IsComposite() = 0;
		///���������� ������� � ��������
		virtual void AppendIndex(SS::Dictionary::Types::TDictionaryIndex oIndex) = 0;
		///������� �������� ��������
		virtual void Clear() = 0;
		///������� ������� ������
		virtual void RemoveIndex() = 0;

		///��������� �������(��������) ������� ��������
		virtual bool GetFirst(SS::Dictionary::Types::TDictionaryIndex* pIndex) = 0;
		///��������� ���������� ������� ��������
		virtual bool GetNext(SS::Dictionary::Types::TDictionaryIndex* pIndex) = 0;
		
		///��������� �������(��������) ������� ��������
		virtual SS::Dictionary::Types::TDictionaryIndex GetFirst() = 0;
	};

}
}
}
}
