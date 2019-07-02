//AdditionalTest.h
/*���� �������� �������������� ����������
������� � ������ ��� ������������ ������*/
#pragma once

//���� ������������
#ifdef _SS_UNITTESTS

#include "../../ASSInterface/IBlackBoxItems.h"
#include "../../ASSInterface/IDictionaryManager.h"
#include "../../ASSInterface/IBlackBoxQuery.h"
#include "../../ASSInterface/IAMConverter.h"

namespace SS
{
namespace UnitTests
{

	///������������ ���� ��� BlackBox
	using namespace SS::Interface::Core::BlackBox;
	using namespace SS::Interface::Core::BlackBox::Query;
	using SS::Dictionary::Types::TDictionaryIndex;

	///�������� IText-�
	class CAdditionalTest
	{
	private:
		///��������� ������
		std::vector<IUnit*> m_UnitCollection;
		///��� �������� ���������
		typedef std::vector<IUnit*>::iterator TIterator;
		///�������
		SS::Interface::Core::Dictionary::IDictionary*			m_pDictionary;
		///����� ���������
		SS::Interface::Core::AMConverter::IAMConverterMorpho*	m_pAMConverterMorpho;
		///��������� ������������� �����
		std::wstring m_wsWord;
		///������������� ���� �����
		bool m_bOneWord;

	private:
		///��� IText
		///��������� ��������� ������
		void GetUnitCollection(IText* pText);
		///������ ������ �����, ���� ����� ������ ����
		void UnitCollectionFilter();
		///����� ���������� �������� �����
		void ShowInfoFromTextUnit(IUnit* pUnit) const;
		///����� ���������� � IFeatures ��� ������� IIndex
		void ShowFeaturesInfo(IIndex* pIndex) const;
		///����� ��������������� ����� �����
		void ShowSyntaxFlag(IUnit* pUnit) const;
		///����� �������������� ��������� �����
		void ShowSyntaxCategory(IUnit* pUnit) const;
		///����� ������ �� ��������������� ��� �����
		void ShowMorphoFeature(IIndex* pIndex) const;
		
		///��� IQuery
		///����� ���������� �� �����-�����
		void ShowInfoFromQueryUnit(IQueryUnit* pQueryUnit) const;
		
		///��� ��������� ������������ �������������
		///��������� ������������ ������������� �� �������
		std::wstring GetWordFromMorphoIndex(TDictionaryIndex oTDictionaryIndex) const;
		///�������� ����������� ������������� �� �����
		std::wstring GetWordFromUnit(IUnit* pUnit) const;
		///�������� ����������� ������������� �� �����-�����
		std::wstring GetWordFromQueryUnit(IQueryUnit* pQueryUnit) const;

		///����� �������
		void ShowIndex(TDictionaryIndex oTDictionaryIndex) const;
	
	public:
		///�����������
		CAdditionalTest() : m_pDictionary(NULL), m_pAMConverterMorpho(NULL), m_bOneWord(false){};
		///��������� �������� ������
		void AnalyseText(IText* pText);
		///��������� �������� �������
		void AnalyseQuery(IQuery* pQuery);
		///���������� �������� (���������������� m_pDictionary)
		void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
		///���������� ����� ��� �������
		void SetOneWordAnalyse(std::wstring s) { m_wsWord = s; m_bOneWord = true; };
		///����� ������������ �������(��������� � �������� �������)
		void ResetOneWordAnalyse() { m_bOneWord = false; };
	};

}//UnitTests
}//SS

#endif //_SS_UNITTESTS