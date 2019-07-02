#pragma once

#include "IBlackBoxItems.h"
#include "IBlackBoxDictionaryIndex.h"
#include "../FeatureLibrary/define.h"
#include "./CObligatory.h"

#include "TDictionaryManager.h"


namespace SS
{
namespace Interface
{
namespace Core
{
namespace BlackBox
{
namespace Query
{

	class ITransformation;
	class IGroup;
	class IQueryUnit;
	class IQueryUnitIndex;
	class IQueryUnitIndexCollection;

	///���� �������������
	enum ETransformationType
	{
		///�����������
		ettUndefined,
		///�������
		ettSimple,
		///������������
		ettTransitive,
		///��������������
		ettIntransitive,
		///���������������
		ettDefinitive
	};

	///��������� ������������� (���� ��������� �������� �������)
	class IQuery
	{
	public:
		///���������� ������������� � �����
		virtual void AddTransformation(ITransformation* pTransformation) = 0;

		///��������� ��������� �� ������ �������������
		virtual ITransformation* GetFirstTransformation() = 0;
		///��������� ��������� �� ��������� �������������
		virtual ITransformation* GetLastTransformation() = 0;

		///�������� �� �������
		virtual bool IsEmpty() = 0;

		///������� ���������, ������� ��������� ���������� � �������� ���� �������������
		virtual void Clear() = 0;
		///�������� ������
		virtual void Release() = 0;
	};

	///��������� ����� �������� 
	/**��������� ����� �������� (�������� �������, ����������, ���������),  
	������� ������ �������������� � ������� ������������� (�������� ��������� ������)*/
	class ITransformation : public CObligation
	{
	public:
		///���������� ������ � �����
		virtual void AddGroup(IGroup* pGroup) = 0;

		///��������� ��������� �� ��������� �������������
		virtual ITransformation* GetNextTransformation() = 0;
		///��������� ��������� �� ����������� �������������
		virtual ITransformation* GetPrevTransformation() = 0;

		///��������� ��������� �� ������ ������
		virtual IGroup* GetFirstGroup() = 0;
		///��������� ��������� �� ��������� ������
		virtual IGroup* GetLastGroup() = 0;

		///������� �������������, ������� ��������� ���������� � �������� ���� �����
		virtual void Clear() = 0;
		///�������� ��������������, ������ ��������� �� ���������(������) �������������
		virtual ITransformation* Release() = 0;
		
		///�������� �� �������
		virtual bool IsEmpty() = 0;
	};

	///��������� ��������, �������� � ���� �� ����� �������� 
	/**��������� ��������, �������� � ���� �� ����� �������� (�������� �������, ����������, ���������),  
	������� ������ �������������� � ������� ������������� (�������� ��������� ������)*/
	class IGroup : public CObligation
	{
	public:
		///���������� ����� � �����
		virtual void AddQueryUnit(IQueryUnit* pQueryUnit) = 0;

		///��������� ��������� �� ��������� ������
		virtual IGroup* GetNextGroup() = 0;
		///��������� ��������� �� ����������� ������
		virtual IGroup* GetPrevGroup() = 0;

		///��������� ��������� �� ������ ����
		virtual IQueryUnit* GetFirstQueryUnit() = 0;
		///��������� ��������� �� ��������� ����
		virtual IQueryUnit* GetLastQueryUnit() = 0;

		///������� ������, ������� ��������� ���������� � �������� ���� ������
		virtual void Clear() = 0;
		///�������� ������, ������ ��������� �� ���������(������) ������
		virtual IGroup* Release() = 0;

		///���������� �������������� ��������������
		virtual ISyntaxFeature* GetSyntaxFeature() = 0;

		///�������� �� �������
		virtual bool IsEmpty() = 0;

		///������������� ������������� ������������������ � ������� ������ ����
		virtual void SetSequenceID(unsigned int uiSequenceID) = 0;
		///���������� ������������� ������������������ � ������� ������ ����
		virtual unsigned int GetSequenceID() = 0;
	};

	///������, �������� � ���� �� ����� �������� 
	/**������������ ������, �������� � ���� �� ����� �������� (�������� �������, ����������, ���������),  
	������� ������ �������������� � ������� ������������� (�������� ��������� ������)*/
	class IQueryUnit : public CObligation
	{
	public:
		///��������� ��������� �� ��������� ����
		virtual IQueryUnit* GetNextQueryUnit() = 0;
		///��������� ��������� �� ���������� ����
		virtual IQueryUnit* GetPrevQueryUnit() = 0;

		///������� �����, ������� ��������� ����������
		virtual void Clear() = 0;
		///�������� �����, ������ ��������� �� ���������(������) ����
		virtual IQueryUnit* ReleaseQueryUnit() = 0;

		///���������� ���������
		virtual void AddQueryUnitIndexCollection(IQueryUnitIndexCollection* pQueryUnitIndexCollection) = 0;
		///��������� ��������� �� ������ ���������
		virtual IQueryUnitIndexCollection* GetFirstQueryUnitIndexCollection() = 0;
		///��������� ��������� �� ��������� ���������
		virtual IQueryUnitIndexCollection* GetLastQueryUnitIndexCollection() = 0;

		///��������� ��������� �� ��������� ������������� ����
		virtual IQueryUnitIndexCollection* GetQueryUnitIndexCollection(SS::Interface::Core::BlackBox::EIndexType IndexCollectionType) = 0;

		///�������� �� �������
		virtual bool IsEmpty() = 0;
		
		///������������� ������������� ������������������ � ������� ������ ����
		virtual void SetSequenceID(unsigned int uiSequenceID) = 0;
		///���������� ������������� ������������������ � ������� ������ ����
		virtual unsigned int GetSequenceID() = 0;

		///��������� ����������� �������� �����
		virtual const wchar_t* GetWord() = 0;
		///������������ ����������� �������� �����
		virtual void SetWord(const wchar_t* szWord) = 0;

		///�������� ������� ������ ����� (��� ������ �������������)
		virtual bool IsNumber(int iNumber) = 0;
		///���������� ������ �����
		virtual void AddNumber(int iNumber) = 0;
		///������� ������ �������
		virtual void ClearNumbers() = 0;
	};

	///��������� �������� ����� �������
	class IQueryUnitIndexCollection : public CObligation
	{
	public:
		///��������� ��������� �� ��������� ������
		virtual IQueryUnitIndexCollection* GetNextQueryUnitIndexCollection() = 0;
		///��������� ��������� �� ���������� ������
		virtual IQueryUnitIndexCollection* GetPrevQueryUnitIndexCollection() = 0;

		///���������� ������� �����
		virtual void AddQueryUnitIndex(IQueryUnitIndex* pQueryUnitIndex) = 0;
		///��������� ��������� �� ������ ������ �����
		virtual IQueryUnitIndex* GetFirstQueryUnitIndex() = 0;
		///��������� ��������� �� ��������� ������ �����
		virtual IQueryUnitIndex* GetLastQueryUnitIndex() = 0;

		///�������� ������� ������� � ��������� (��� ����������� ������) - ������ �������
		virtual IQueryUnitIndex* ContainsIndexFull(SS::Dictionary::Types::TDictionaryIndex oIndex) = 0;
		///�������� ������� ������� � ��������� (��� ����������� ������) - ������� ��� �������� ����
		virtual IQueryUnitIndex* ContainsIndex(SS::Dictionary::Types::TDictionaryIndex oIndex) = 0;

		///������� ���������, ������� ��������� ���������� � �������� ������ ��������
		virtual void Clear() = 0;
		///�������� ���������, ������ ��������� �� ���������(������) ���������
		virtual IQueryUnitIndexCollection* Release() = 0;

		///������������� ��� ���������
		virtual void SetIndexCollectionType(SS::Interface::Core::BlackBox::EIndexType IndexType) = 0;
		///���������� ��� ���������
		virtual SS::Interface::Core::BlackBox::EIndexType GetIndexCollectionType() = 0;

		///�������� �� �������
		virtual bool IsEmpty() = 0;
	};

	///������ ����� �������, ����� ����� ���������� �������� ���
	class IQueryUnitIndex : public CObligation
	{
	public:
		///��������� ��������� �� ��������� ������
		virtual IQueryUnitIndex* GetNextQueryUnitIndex() = 0;
		///��������� ��������� �� ���������� ������
		virtual IQueryUnitIndex* GetPrevQueryUnitIndex() = 0;

		///������������� ��� �������
		virtual void SetIndex(SS::Dictionary::Types::TDictionaryIndex oIndex) = 0;
		///���������� ��� �������
		virtual SS::Dictionary::Types::TDictionaryIndex& GetIndex() = 0;

		///�������� �������, ������ ��������� �� ���������(������) ������
		virtual IQueryUnitIndex* Release() = 0;

		/// ���������� ���������� � ������
		virtual void AddIDForm(short shForm) = 0;
		/// ��������� ������ ����������
		virtual bool GetFirstIDForm(short* pshForm) = 0;
		///��������� ��������� ����������
		virtual bool GetNextIDForm(short* pshForm) = 0;

		///�������� ������� id form-� � ��������� (��� ����������� ������)
		virtual bool ContainsIDForm(short idForm) = 0;
	};

}
}
}
}
}
