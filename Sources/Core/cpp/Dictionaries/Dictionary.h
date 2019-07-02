#pragma once

#include ".\AbbreviationSource.h"

namespace SS{ 
namespace Dictionary{

//�������� ��� ILoad
class CLoadStub: public ILoad
{
public: 
   /// ��������� � �������� ��� ��������� ������ 
   bool ToBinary() { return true; }
   
   /// ������������� �������
   bool ReLoad() { return true; }
   
   /// ��������� �������
   bool Load() { return true; }
   
   /// ����������� ������
   bool Clear() { return true; }
};
                                                           
class CDictionary:
   public IDictionary, 
   private SS::Interface::Core::Common::IConnection //�������� ���������� � ����� ����� ����
{
	CDBMSPtrsManager m_DBMSPtrsManager;
	CDBMSPtrsManager m_NewWordsDBMSPtrsManager;

	Edit::CSourceAdapter m_SourceAdapter;
	Edit::CAbbreviationSourceAdatper m_AbbreviationSourceAdatper;
	Edit::COneRootAdapter m_OneRootAdapter;
	Edit::CMorphoTypesCollectionAdapter m_MorphoTypesCollectionAdapter;

	CNewWordsList  m_NewWordsList;
	CMALanguagesManager m_MALanguagesManager;

	DBMS::IDataBase *m_pMorphoEngDB;
	DBMS::IDataBase *m_pMorphoRusDB;
	DBMS::IDataBase *m_pAbbreviationEngDB;
	DBMS::IDataBase *m_pAbbreviationRusDB;
	DBMS::IDataBase *m_pNdxDB;


private:
   //��������������� ��� ���������� ������� (������������ ������� ������� ���������� �������� ��� 
   //��������� ���������� ��������)
   void InitObjects( SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager );


private:
   ///////////////////////////////////////////////////////////////////////////////
   // IConnection
   bool Open();
   bool Close();

public:
	CDictionary();

	/// ���������� ��������� ������ � ������������� �������
	ILoad* GetLoader();

	/// ���������� ��������� ������ � ������������� �������
	IOneRoot* GetOneRoot();

	/// ���������� ��������� ������ � ������ ����������������
	IMorphoTypesCollection* GetMorphoTypesCollection();

	/// ���������� ��������� ������ � ��������
	ISource* GetSource();

   /// ���������� ��������� ��������� � �������������� ���������� �� ������� ����
   /// �������� �����������.
   /// ����� ����� ��������� ��� ����� � ��� �� ��������������� ��� � ������� ������� 
   /// ��� � � ������� �����������, ������� ��� �������� ���������� ������������
   /// ��� ����������.
   ISourceEx* GetAbbreviationSource();

	/// ���������� ��������� ���������������� �������
	IMorphologyAnalyser* GetMorphologyAnalyser();

   /// ���������� ��������� ��� ��������� ������� ���� ������������� ����,
   /// ��� eDictionariesNumber - ����� �������, ��� �������� ���������� ������� ������ ����
   IWordsList* GetWordList();

   void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

   void SetAnalyseParams( SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams );

public:
   RELEASE_IMPL()

	BEGIN_QI_MAP()
		QI_MAP_INHERIT_ENTRY( IID_Base, IBase )
		QI_MAP_INHERIT_ENTRY( IID_IDictionary, IDictionary )
	END_QI_MAP()
};

} //namespace Dictionary
} //namespace SS
