//BaseExpertConstruction.h
#pragma once

#include "BaseExpert.h"
#include "ModifiedConstruction.h"

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	using namespace SS::Syntax::ModifiedConstruction;
	
	///������� ������� ��� ��������� ����������� �� ����
	class CBaseExpertConstruction : public CBaseExpert
	{
	private:
		///����������� �� ����
		SS::SyntaxConstructions::Types::CConstructionEx m_oConstruction;
		///������������� ������
		int m_IdGroup;
		///������-�����
		std::list< std::set<std::wstring> > m_DetectWords;
		
	protected:
		///���������������� �����������
		IModifiedConstruction* m_pModifiedConstruction;
		///������ ������� ������������ �����������
		BoardElementsIterator m_itBeginBoard;
		///������ ������� �����
		BoardElementsIterator m_itBlockBegin;
		///����������� ������� �����
		BoardElementsIterator m_itBlockEnd;
		///������ ������� ����� ��������� ������
		BoardElementsIterator m_itFirst;
		///��������� ������� ����� ��������� ������
		BoardElementsIterator m_itLast;
		///������ ������� �������(�� ������-��������) ���������
		BoardElementsIterator m_itFirstR;
		///��������� ������� ������(�� ������-��������) ���������
		BoardElementsIterator m_itLastL;
		///��������� ��� ������������� ����������
		BoardCollection m_NullCollection;

	private:
		///���������� ��������� ��������
		void SetRange();
		///���������� ������-�����
		void SetDetectWords(SS::Interface::Core::Dictionary::IDictionary* pDictionary);
		///��������� IdParent � ������ SameObject
		inline unsigned int GetIdParentReal(unsigned int idParent);
		///���������� ������
		inline void Delete();
		
	protected:
		///��������� �����������
		void ApplyConstruction(unsigned int iCountApplyedExpertAT = 0);
		///�������� ������������ �������� � �����������
		bool IsApplicable();

	public:
		///�����������
		CBaseExpertConstruction( SS::SyntaxConstructions::Types::CConstructionEx & oConstruction,
								 SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager,
								 SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams,
								 int IdGroup, ESyntaxBase eBase );
		///����������
		virtual ~CBaseExpertConstruction();
		///���������� ��������� �������� ��������
		virtual std::wstring GetName() const;
	};

}
}
}