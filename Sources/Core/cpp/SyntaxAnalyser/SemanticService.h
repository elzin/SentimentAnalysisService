//SemanticService.h
#pragma once
#include "../ASSInterface/Construction.h"
#include "../ASSInterface/IAMConverter.h"
#include "../ASSInterface/IBlackBox.h"
#include "Container.h"

namespace SS
{
namespace Syntax
{
namespace BoardElements
{
	///����� ��������� ������� �� ������ � ���������� ��������
	class CSemanticService
	{
	private:
		///������� �������������� ������� ��� IText
		enum EMark
		{
			///������ �� ������
			mUndefined,
			///��������
			mAdd,
			///�������
			mDelete
		};
		///������ � ��� ���������
		struct SSemanticData
		{
			SS::Interface::Core::BlackBox::IIndex* pIndex;
			SS::Core::Features::CSemanticFeature	oSemanticFeature;
			EMark oMark;
			SSemanticData() : pIndex(NULL), oMark(mUndefined){ oSemanticFeature.Undefine(); };
		};
		///����������� ���������� ���������
		enum { SIZESEMANTIC = 10 };
		///��������� ���������
		CContainer<SSemanticData, SIZESEMANTIC> m_oSemanticContainer;
		///���������� ��������� ��������
		SS::Core::Features::CSemanticFeature m_oSemanticFeature;
		///���� �������� ����������� ������ ���������
		SS::Interface::Core::BlackBox::IUnit* m_pUnit;
		///������������� ���������
		SS::Interface::Core::AMConverter::IAMConverterSemantic* m_pAMConverterSemantic;
		///��� �������� �������������� ������������� ��������
		SS::Interface::Core::BlackBox::IBlackBoxTextStorage* m_pBlackBoxTextStorage;
		///���� �� ���������� ���������
		bool m_IsModified;

	private:
		///����������� �����������
		CSemanticService(const CSemanticService & v);
		///�������
		void Remove(SS::SyntaxConstructions::Types::CConstructionObject* pObject);
		///�������
		void Select(SS::SyntaxConstructions::Types::CConstructionObject* pObject);
		///���������
		void Appoint(SS::SyntaxConstructions::Types::CConstructionObject* pObject);
		///��������
		void Add(SS::SyntaxConstructions::Types::CConstructionObject* pObject);
		///������������ ��������� �� ��������� ��������
		void Inherit(const CSemanticService* pSemanticServiceBase);
		///�������� ����������
		bool BadPtr();
		///������������� ����� ���������
		void GenerateSemantic();
		///����������� undefine ��� 0
		void UndefineSemantic();
		///�������� ����
		void ZeroSemantic();
		///���������� ��������� ��� ��������� �� ��������
		unsigned int Size();

	public:
		///�����������
		CSemanticService();
		///��������=
		void operator=(const CSemanticService & v);
		///����������
		~CSemanticService(){};
		///��������� ������� ����������� � ������� �����
		void ApplyConstructionObject( SS::SyntaxConstructions::Types::CConstructionObject* pObject,
									  const CSemanticService* pSemanticServiceBase = NULL );
		///��������� ��������� ��������� � BlackBox
		void UpdateBlackBox();
		///�������� ������������� ����
		SS::Core::Features::CSemanticFeature & GetSemanticFeature();
		///���������� ����
		void SetUnit(SS::Interface::Core::BlackBox::IUnit* pUnit);
		///���������� ������������� ���������
		void SetSemanticConverter(SS::Interface::Core::AMConverter::IAMConverterSemantic* pAMConverterSemantic);
		///���������� BlackBox �������
		void SetTextStorage(SS::Interface::Core::BlackBox::IBlackBoxTextStorage* pBlackBoxTextStorage);
		///�������� ���������
		void AddSemantic( SS::Interface::Core::BlackBox::IIndex* pIndex,
						  SS::Core::Features::CSemanticFeature*  pSemanticFeature,
						  EMark oMark = mUndefined );
		///�������� ������ � ������
		void Clear();
	};

}
}
}