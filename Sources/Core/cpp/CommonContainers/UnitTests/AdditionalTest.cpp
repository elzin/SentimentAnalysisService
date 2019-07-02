//AdditionalTest.cpp

#include "StdAfx.h"
#include ".\additionaltest.h"

//���� ������������
#ifdef _SS_UNITTESTS

namespace SS
{
namespace UnitTests
{

	///���������� �������� (���������������� m_pDictionary)
	void CAdditionalTest::SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
	{
		//�������� �������
		m_pDictionary = (SS::Interface::Core::Dictionary::IDictionary*)
		pLoadManager->GetInterface(L"./core/linguistics/Dictionaries.dll", CLSID_IDictionary, IID_IDictionary);
		if (!m_pDictionary)
		{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�� ������� �������� IDictionary*"); }
		//�������� ��������������
		m_pAMConverterMorpho = (SS::Interface::Core::AMConverter::IAMConverterMorpho*)
		pLoadManager->GetInterface(L"./core/linguistics/AMConverter.dll", CLSID_AMConverterMorpho, IID_AMConverterMorpho);
		if (!m_pAMConverterMorpho)
		{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�� ������� �������� IAMConverterMorpho*"); }
	}

	///������ ������ �����, ���� ����� ������ ����
	void CAdditionalTest::UnitCollectionFilter()
	{
		if (!m_bOneWord) 
		{ return; }
			
		//������� �����
		std::wstring wsWord;

		TIterator it(m_UnitCollection.begin());
		while (it != m_UnitCollection.end())
		{ 
			wsWord = GetWordFromUnit(*it);     
			//������� ������
			if (wsWord != m_wsWord)
			{ it = m_UnitCollection.erase(it); continue; }
			++it;
		}
		if (m_UnitCollection.empty())
		{ SAVE_LOG(L"����� ���, ���� ��� ������������ �������������.");	exit(0); }
	}

	///��������� ��������� ������
	void CAdditionalTest::GetUnitCollection(IText* pText)
	{
		//������� ���������� ������
		m_UnitCollection.clear();

		IParagraph* pPar = NULL;
		ISentence* pSent = NULL;
		IUnit* pCurrUnit = NULL;
		IUnit* pRightUnit = NULL;
		IUnit* pChildUnit = NULL;

		pPar = pText->GetFirstParagraph();
		if (!pPar)
		{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"IText �� �������� �� ������ IParagraph."); return; }
		pSent = pPar->GetFirstSentence();
		if (!pSent)
		{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"IParagraph �� �������� �� ������ ISentence."); return; }

		//������� Unit-��
		pCurrUnit = pSent->GetFirstUnit();
		while (pCurrUnit)
		{
			pChildUnit = pCurrUnit->GetLeftChildUnit();
			if (pChildUnit)
			{
				pCurrUnit = pChildUnit;
				continue;
			}
			//��������� ����
			m_UnitCollection.push_back(pCurrUnit);

			pRightUnit = pCurrUnit->GetRightUnit();
			while (pRightUnit == NULL)
			{
				pCurrUnit = pCurrUnit->GetParentUnit();
				if (pCurrUnit == NULL)
				{ break; }
				//��������� ����
				m_UnitCollection.push_back(pCurrUnit);

				pRightUnit = pCurrUnit->GetRightUnit();
			}
			pCurrUnit = pRightUnit;
		}
		//������� Unit-��(�����)
		if (m_UnitCollection.empty()) 
		{ SAVE_LOG(L"������ � ������ ���."); exit(0); }
	}

	///��������� �������� ������
	void CAdditionalTest::AnalyseText(IText* pText)
	{
		//������ ��� �����
		GetUnitCollection(pText);
		//�������������
		UnitCollectionFilter();
		//��������� �����
		SAVE_LOG(L"Sentence::::::::::");
		TIterator itUnit(m_UnitCollection.begin());
		for (itUnit; itUnit != m_UnitCollection.end(); ++itUnit)
		{ ShowInfoFromTextUnit(*itUnit); }
	}

	///����� ���������� �������� unit-�
	void CAdditionalTest::ShowInfoFromTextUnit(IUnit* pUnit) const
	{
		//����� �����
		std::wstring wsWord = GetWordFromUnit(pUnit); SAVE_LOG((wchar_t*)wsWord.c_str());
		//����� ��������������� �����
		//ShowSyntaxFlag(pUnit);
		//����� �������������� ���������
		//ShowSyntaxCategory(pUnit);
		
		IIndex*				pIndex = NULL;
		IDictionaryIndex*	pDictionaryIndex = NULL;
		TDictionaryIndex	oTDictionaryIndex;

		//������� ��������
		for (pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			//��������� IDictionaryIndex
			pDictionaryIndex = pIndex->GetDictionaryIndex();
			if (!pDictionaryIndex) continue;
			//��������� TDictionaryIndex
			if ( !(pDictionaryIndex->GetFirst(&oTDictionaryIndex)) ) continue;
				
			//����� �� ����� ������
			if (oTDictionaryIndex.GetIndexType() != eitMorphoIndex) continue;
			
			//����� �������
			//ShowIndex(oTDictionaryIndex);
			//����� ������ �� ��������������� ��� �����
			ShowMorphoFeature(pIndex);
			//����� ���������� � Features
			//ShowFeaturesInfo(pIndex);
		}
	}

	///����� ���������� � IFeatures ��� ������� IIndex
	void CAdditionalTest::ShowFeaturesInfo(IIndex* pIndex) const
	{
		SAVE_LOG(L"��������� IIndex: ");
		
		unsigned int iMorphoIndex = 0; 
		unsigned int iMorphoInfo = 0;
		unsigned int iPartOfSpeech = 0;

		wchar_t BuffMorphoIndex[30];
		wchar_t BuffMorphoInfo[30];
		wchar_t BuffPartOfSpeech[30];
		
		for (IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
		{
			iMorphoIndex = pFeature->GetMorphoIndex();
			_itow(iMorphoIndex, BuffMorphoIndex, 10);
			iMorphoInfo = pFeature->GetMorphoInfo();
			_itow(iMorphoInfo, BuffMorphoInfo, 10);
			iPartOfSpeech = pFeature->GetPartOfSpeech();
			_itow(iPartOfSpeech, BuffPartOfSpeech, 10);
			//����� � ���
			SAVE_LOG(L"IFeature: " AND BuffMorphoIndex AND L"  " AND BuffMorphoInfo AND L"  " AND BuffPartOfSpeech);
		}
	}

	///����� ��������������� �����
	void CAdditionalTest::ShowSyntaxFlag(IUnit* pUnit) const
	{
		wchar_t Buff[30];
		_itow((int)pUnit->GetSyntaxFlag(), Buff, 10);
		SAVE_LOG(L"�������������� ����: " AND Buff);
	}
	
	///����� �������������� ��������� �����
	void CAdditionalTest::ShowSyntaxCategory(IUnit* pUnit) const
	{
		std::string sCategories = pUnit->GetSyntaxFeature()->GetSyntaxFeatureAposteriori()->m_SyntaxCategories.ToString();
		wchar_t Buff[30];
		MultiByteToWideChar(0, 0, sCategories.c_str(), 30, Buff, 30);
		SAVE_LOG(L"�������������� ���������: " AND Buff);
	}

	///����� ������ �� ��������������� ��� �����
	void CAdditionalTest::ShowMorphoFeature(IIndex* pIndex) const
	{
		if (!m_pAMConverterMorpho)
		{ SS_THROW(L"����������_LoadManager."); }
		//��������������� ����
		SS::Core::Features::CMorphoFeature oMorphoFeature;
		TDictionaryIndex oTDictionaryIndex;
		try
		{
			pIndex->GetDictionaryIndex()->GetFirst(&oTDictionaryIndex);
		}
		catch (...) 
		{
			SAVE_LOG(L"�� ���� �������� TDictionaryIndex.");
			throw;
		}
		
		//������� ��-���
		for (IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
		{
			//��������� �����-����
			m_pAMConverterMorpho->EnCode( oTDictionaryIndex.GetDictionaryNumber(), pFeature->GetMorphoInfo(),
										  pFeature->GetPartOfSpeech(), &(oMorphoFeature) );
			//�������� ����� ����
			//std::string sPartOfSpeach = oMorphoFeature.m_PartOfSpeechTypes.ToString();
			//wchar_t Buff[30];
			//MultiByteToWideChar(0, 0, sPartOfSpeach.c_str(), 30, Buff, 30);
			//SAVE_LOG(L"����� ����: " AND Buff);

			std::string sXML; 
			oMorphoFeature.GetXMLValue(sXML);
			SAVE_LOG(L"XML: " AND (wchar_t*)sXML.c_str());
		}
	}

	/*************************������ ��� IQuery*************************/

	///��������� �������� �������
	void CAdditionalTest::AnalyseQuery(IQuery* pQuery)
	{
		ITransformation*			pTransformation = NULL;
		IGroup*						pGroup = NULL;
		IQueryUnit*					pQueryUnit = NULL;
	
		//������� �������
		for (pTransformation = pQuery->GetFirstTransformation(); pTransformation; pTransformation = pTransformation->GetNextTransformation())
		{
			SAVE_LOG(L"Transformation::::::::::");
			for (pGroup = pTransformation->GetFirstGroup(); pGroup; pGroup = pGroup->GetNextGroup())
			{
				for (pQueryUnit = pGroup->GetFirstQueryUnit(); pQueryUnit; pQueryUnit = pQueryUnit->GetNextQueryUnit())
				{ ShowInfoFromQueryUnit(pQueryUnit); }
			}
		}
	}

	///����� ���������� �������� �����-�����
	void CAdditionalTest::ShowInfoFromQueryUnit(IQueryUnit* pQueryUnit) const
	{
		//����� �����
		std::wstring wsWord = GetWordFromQueryUnit(pQueryUnit); SAVE_LOG((wchar_t*)wsWord.c_str());
				
		IQueryUnitIndexCollection*	pCollection = NULL;
		IQueryUnitIndex*			pIndex = NULL;
		
		//������� ��������
		for (pCollection = pQueryUnit->GetFirstQueryUnitIndexCollection(); pCollection; pCollection = pCollection->GetNextQueryUnitIndexCollection())
		{
			//����� �� ����� ���������
			//if (pCollection->GetIndexCollectionType() != eitMorphoIndex) continue;
			//����� ��������
			for (pIndex = pCollection->GetFirstQueryUnitIndex(); pIndex; pIndex = pIndex->GetNextQueryUnitIndex())
			{ ShowIndex(pIndex->GetIndex()); }
		}
	}

	/************************������ ��� ��������� ������������ ������������*****************************/

	///��������� ������������ ������������� �� �����-�������
	std::wstring CAdditionalTest::GetWordFromMorphoIndex(TDictionaryIndex oTDictionaryIndex) const
	{
		wchar_t Word[50];
		SS::Dictionary::Types::SWordIndex oWordIndex;
		oWordIndex.m_DictIndex.SetDictionaryIndex(oTDictionaryIndex.GetDictionaryIndex());
		SS::Interface::Core::Dictionary::IMorphologyAnalyser* pMorphologyAnalyser = NULL;
		if (!m_pDictionary)
		{ SS_THROW(L"����������_LoadManager."); }
		pMorphologyAnalyser = m_pDictionary->GetMorphologyAnalyser();
		pMorphologyAnalyser->GetWord(&oWordIndex, Word);
		return Word;
	}
	
	///�������� ����������� ������������� �� �����
	std::wstring CAdditionalTest::GetWordFromUnit(IUnit* pUnit) const
	{
		IIndex*				pIndex = NULL;
		IDictionaryIndex*	pDictionaryIndex = NULL;
		TDictionaryIndex	oTDictionaryIndex;
		std::wstring		wsWord;

		wsWord = pUnit->GetWord();
		if (!wsWord.empty()) return wsWord;

		//���� ��� �������� ������������ ������������ ��� �����
		for (pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			//��������� IDictionaryIndex
			pDictionaryIndex = pIndex->GetDictionaryIndex();
			if (!pDictionaryIndex) continue;
			//��������� TDictionaryIndex
			if ( !(pDictionaryIndex->GetFirst(&oTDictionaryIndex)) ) continue;
			//���� ������ ���������������, �������� ����������� �������������
			if (oTDictionaryIndex.GetIndexType() == eitMorphoIndex)
			{ 
				wsWord = GetWordFromMorphoIndex(oTDictionaryIndex);
				if (!wsWord.empty()) return wsWord;
			}
		}
		return L"���_������������_�������������";
	}

	///�������� ����������� ������������� �� �����-�����
	std::wstring CAdditionalTest::GetWordFromQueryUnit(IQueryUnit* pQueryUnit) const
	{
		IQueryUnitIndexCollection*	pCollection = NULL;
		IQueryUnitIndex*			pIndex = NULL;
		std::wstring				wsWord;

		wsWord = pQueryUnit->GetWord();
		if (!wsWord.empty()) return wsWord;

		//���� ��� �������� ������������ ������������ ��� �����-�����
		for (pCollection = pQueryUnit->GetFirstQueryUnitIndexCollection(); pCollection; pCollection = pCollection->GetNextQueryUnitIndexCollection())
		{
			//������ ���� ��������� �������������
			if (pCollection->GetIndexCollectionType() == eitMorphoIndex)
			{ 
				//������������
				for (pIndex = pCollection->GetFirstQueryUnitIndex(); pIndex; pIndex = pIndex->GetNextQueryUnitIndex())
				{
					wsWord = GetWordFromMorphoIndex(pIndex->GetIndex());
					if (!wsWord.empty()) return wsWord;
				}
			}
		}
		return L"���_������������_�������������";
	}

	/***************************����� ������**********************/

	///����� �������
	void CAdditionalTest::ShowIndex(TDictionaryIndex oTDictionaryIndex) const
	{
		//��� �������
		std::wstring wsName;
				
		if (oTDictionaryIndex.GetIndexType() == eitMorphoIndex)
		{
			wsName = L"��������������� ������: ";
		}
		else if (oTDictionaryIndex.GetIndexType() == eitSemanticIndex) 
		{
			wsName = L"������������� ������: ";
		}
		else if (oTDictionaryIndex.GetIndexType() == eitSyntaxIndex)
		{
			wsName = L"�������������� ������: ";
		}
		else if (oTDictionaryIndex.GetIndexType() == eitSynonymIndex)
		{
			wsName = L"�������������� ������: ";
		}
		else if (oTDictionaryIndex.GetIndexType() == eitCombinatoryIndex)
		{
			wsName = L"������������� ������: ";
		}
		else
		{
			wsName = L"�������������� ������: ";
		}

		wchar_t Buff[30];
		_itow(oTDictionaryIndex.GetDictionaryIndexWithoutFlags(), Buff, 10);
		SAVE_LOG((wchar_t*)wsName.c_str() AND Buff);
	}

}
}

#endif //_SS_UNITTESTS