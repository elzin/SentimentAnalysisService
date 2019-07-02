#pragma once

namespace SS{ 
namespace Dictionary{
namespace Edit
{

/*
   ��������� �������������� ������� ProperSourceForm (NominalSourceForm)
   � ������� � ���� IDSource ������� ����� TDictionaryIndex::GetId()
*/
class CSource
{
private:
   typedef ClassLevelLockable<CSource> TMutex; //������������ ������� ��� ����������

private:
   DBMS::IDataBase *m_pDataBase;
   wchar_t m_wzSourceFormTableName[50];
   wchar_t m_wzSourceToMorphoTableName[50];
   wchar_t m_wzMorphoTypeToMorphoInfoTable[50];
private:
	mutable CTablePtr m_pSourceForm;
	mutable CTablePtr m_pSourceToMorpho;
	mutable CTablePtr m_pMorphoTypeToMorphoInfo;
	TDictNumber m_CurInitDictNumber; //����� ������� ��� �������� ���������������� �������
	TMutex m_Mutex;                  //������ ������ ������. ��������� ��� ����������� ����������, ��� ������� ��� ��������� �������� ���������� ���� �������

public:
   typedef unsigned int TIDSource;
public:
	CSource(): m_CurInitDictNumber(DATA_TYPE::NAMES::ednUnknown), m_pDataBase(NULL) 
	{
		memset(m_wzSourceFormTableName, 0, sizeof(wchar_t) * 50);
		memset(m_wzSourceToMorphoTableName, 0, sizeof(wchar_t) * 50);
		memset(m_wzMorphoTypeToMorphoInfoTable, 0, sizeof(wchar_t) * 50);
	}
	
	//�������������� �������, �������� ����������� ����� ���������� ��������
   /*
      CurInitDictNumber - ����� ������� (�������� ����� ����������� � �������� ������)
      SourceFormTableName, SourceToMorphoTableName - ����� ����� ������
   */
	void Init( 
      DBMS::IDataBase *pDataBase, 
      TDictNumber CurInitDictNumber, 
      const wchar_t *SourceFormTableName, 
      const wchar_t *SourceToMorphoTableName 
   );

	/// ���������� ��� ��������� ���������� �� ������
	/**
		��������:
			�� IDSource ������� � �������� ProperSourceForm (NominalSourceForm), 
			ProperSourceToMorpho (NominalSourceToMorphoTable), MorphoTypeToMorphoInfo ������ � ������.
	*/
	bool Get( TIDSource IDSource, SSource &Source ) const;

	/// ��������� ��� ��������� ���������� ��� ������
	/**
		��������:
			������� � ������� ProperSourceForm (NominalSourceForm) ���������� ����� � 
			���������� � IDSource. ��������� � ��� ������� ������ - ���� PartOfWord � ������ ���
			��������� ������(IDSource) � �������������� ���������� ����� � �������.  ����� ��������� � ������� 
         ProperSourceToMorpho (NominalSourceToMorpho) ����� ������ IDSource � pSource->m_MorphoTypeInfo.IDType
	*/
	void Add( const SSource &Source, TIDSource &IDSource );

	/// ������� ��� ���������� �� ������
	/**
		��������:
			������� �� ������� ProperSourceForm (NominalSourceForm), ������ � IDSource . ����� �� ������� 
			ProperSourceToMorpho (NominalSourceToMorpho) ��� ������ � IDSource 
	*/
	void Delete( TIDSource IDSource );

private:
	void Open() const;
	void Close() const;

};


///////////////////////////////////////////////////////////////////////////////
// ���������� CSource ��� ��������� ISource
// �������� ������������� ���������� �������� CSource
///////////////////////////////////////////////////////////////////////////////
class CSourceAdapter: public ISource
{
public:
   //��������� ������ ����������������� ������ ��� ��������������� ��������� �������� CSource
   struct SInitStruct
   {
      //������ ��� ������ CSource::Init
      DBMS::IDataBase *pDataBase; 
      TDictNumber CurInitDictNumber; 
      std::wstring SourceFormTableName; 
      std::wstring SourceToMorphoTableName; 
   };

private:
   typedef CObjectsSelector<TDictNumber, CSource> TSources;

private:
   TSources m_Sources;
   CSource *m_pCurSource;
   CSource::TIDSource m_CurIDSource;

public:
   CSourceAdapter(): m_pCurSource(0), m_CurIDSource(0) {}
   
   //������ � �������������� ���������� ������� CSource ��� ������ ���������� [First, Last) ����������� �� ��������� SInitStruct
   //���������� ������� ���������
   template<class InputIterator>
   void Init( InputIterator First, InputIterator Last )
   {
      TSources::TAutoPtr AutoPtr;

      m_Sources.Clear();
      m_pCurSource = 0;

      for( ; First != Last; ++First )
      {
         AutoPtr.reset( new CSource() );

         AutoPtr->Init(
            First->pDataBase,
            First->CurInitDictNumber, 
            First->SourceFormTableName.c_str(), 
            First->SourceToMorphoTableName.c_str() 
         );

         if( !m_Sources.Add(First->CurInitDictNumber, AutoPtr) )
         {
            m_Sources.Clear();
            SS_THROW( L"������ CSourceAdapter::Init" );
         }
      }
   }
   
   ///////////////////////////////////////////////////////////////////////////////
   // ISource
   /// ������������� ������ �����
   unsigned int SetDictionaryIndex(SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex);
   
   /// ���������� ��� ��������� ���������� �� ������
   unsigned int Get(SS::Dictionary::Types::SSource* pSource);
   
   /// �������� ��� ��������� ���������� ��� ������
   void Add(SS::Dictionary::Types::SSource* pSource);
   
   /// ������� ��� ���������� �� ������
   void Delete();
};

}
} //namespace Dictionary
} //namespace SS
