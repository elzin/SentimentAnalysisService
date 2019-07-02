#pragma once

namespace SS{ 
namespace Dictionary{
namespace Edit{

/**
	����� ��������� ������������� ������� MorphoTypeToMorphoInfo � 
	MorphoTypes
*/
class CMorphoTypesCollection
{
private:
   typedef ClassLevelLockable<CMorphoTypesCollection> TMutex; //������������ ������� ��� ����������
private:
	DBMS::IDataBase *m_pDataBase;
	CTablePtr m_pMorphoTypes;
	CTablePtr m_pMorphoTypeToMorphoInfo;
	TMutex m_Mutex;                  //������ ������ ������. ��������� ��� ����������� ����������, ��� ������� ��� ��������� �������� ���������� ���� �������

private:
	static const wchar_t *szMorphoTypesTable;
	static const wchar_t *szMorphoTypeToMorphoInfoTable;

private:
	void Open();
	void Close();
   //� ����� � ��� ��� � ������ IDType ����� ����������� ������ ���������� � ���� � ���� �� �������, ������
   //��������� "���" � ���������� ������� IDType
   //������� �������������� ���������� ������� ���������� IDForm � ���������� IDType
   //IDType - ��� � �������� ���������� �������������� �����
   void RestoreCorrectIDFormOrder( const TIDType &IDType  );

   //�������� � ������ RecordID ������� m_pMorphoTypes �������� IDForm �� NewIDForm
   void ReplaceIDForm( UINT32 RecordID, TIDForm NewIDForm );

public:
	CMorphoTypesCollection() : m_pDataBase(NULL) {}

	///������������ ������, ���������� �������� ����� ������� ������� ������
	void Init( DBMS::IDataBase *pDataBase );


	/// ������� ������� ��� ����������������
	/**
		��������:
			������� ��� ������ � ������� MorphoTypes � ������� IDType ����� ��������	
	*/
	void DeleteType(const TIDType &IDType);

	/// ���������� ������ ��������� �������� ���� ����������������
	/**
		��������:
			������� ��� ������ � ������� MorphoTypes � ������� IDType ����� �������� � ������������ � ���
			�������	MorphoTypeToMorphoInfo ���������� ������� �� SQL���� INNER JOIN
	*/
	void GetElements(const TIDType &IDType, std::list<SMorphoType>* p_l_MorphoTypes);

	/// ��������� ������ ���������
	/// ����������:
	///	  S_OK - �������� ���������� ���� �������. 
	///     E_INVALIDARG - ��������� ������ �������� �� �������
	/**
		��������:
			��� ������� p_l_MorphoTypes 
				���� ��� ������� � MorphoTypes � �������� IDType � IDForm
					��������� � MorphoTypes � MorphoTypeToMorphoInfo �� ����� ������
				����� ���� ��� ������ � ������� MorphoTypeToMorphoInfo � MorphoInfo ������ ��������
					��������� ���� ������ � MorphoTypeToMorphoInfo
				�����
					���������� E_INVALIDARG, �� �� ��������� ���������� ��������� �������
	*/
	HRESULT AddElements(std::list<SMorphoType>* p_l_MorphoTypes);

   ///������ ����� ��� ��� ������ ���������
   /// ����������:
   ///	  S_OK - �������� ���������� ���� �������. 
   ///     E_INVALIDARG - ��������� ������ �������� �� �������
   /**
      ��������:
         ������� � ������� MorphoTypes (GetUserValue, SetUserValue) ���������� IDType � ���������� ��� �
         ������ ������� ������ p_l_MorphoTypes ����� �������� AddElements � ���������� �� ��� ������ 
         AddElements
   */
   HRESULT CreateCollection(std::list<SMorphoType>* p_l_MorphoTypes);

	/// ������� ������ ���������
	/// ����������:
	///		S_OK - �������� �������� ���� �������. 
	///     E_INVALIDARG - ��������� ������ ������� �� �������
	/**
		��������:
			������� �� ������� MorphoTypes ��� ������ � �������� IDType � IDForm ��� ������� ��� ��� �������� IDType ����� 
			�������� ��� ��������� ������ � ��������� �� �������� IDForm. ���� ����� ������� ��� �� ���������� E_INVALIDARG, 
			�� ��������� ��������� ������� �� ����������������
	*/
	HRESULT DeleteElements(std::list<SMorphoType>* p_l_MorphoTypes);
};



///////////////////////////////////////////////////////////////////////////////
// ���������� CMorphoTypesCollection ��� ��������� IMorphoTypesCollection
// �������� ������������� ���������� �������� CMorphoTypesCollection
///////////////////////////////////////////////////////////////////////////////
class CMorphoTypesCollectionAdapter: public IMorphoTypesCollection
{
public:
   //��������� ������ ����������������� ������ ��� ��������������� ��������� �������� CMorphoTypesCollection
   struct SInitStruct
   {
      //������ ��� ������ CMorphoTypesCollection::Init
      DBMS::IDataBase *pDataBase;

      //����� ����� ������� ����� ����������� ������ ����
      typedef std::vector<TDictNumber> TKeys;
      TKeys Keys;
   };

private:
   typedef CObjectsSelectorMultiKey<TDictNumber, CMorphoTypesCollection> TMorphoTypesCollections;

private:
   TMorphoTypesCollections m_MorphoTypesCollections;
   CMorphoTypesCollection *m_pCurMorphoTypesCollection;

public:
   CMorphoTypesCollectionAdapter(): m_pCurMorphoTypesCollection(0) {}

   //������ � �������������� ���������� ������� CMorphoTypesCollection ��� ������ ���������� [First, Last) ����������� �� ��������� SInitStruct
   //���������� ������� ���������
   template<class InputIterator>
      void Init( InputIterator First, InputIterator Last )
   {
      TMorphoTypesCollections::TAutoPtr AutoPtr;

      m_MorphoTypesCollections.Clear();
      m_pCurMorphoTypesCollection = 0;

      for( ; First != Last; ++First )
      {
         AutoPtr.reset( new CMorphoTypesCollection() );

         AutoPtr->Init(
            First->pDataBase
         );

         APL_ASSERT( !First->Keys.empty() );

         if( !m_MorphoTypesCollections.Add(First->Keys.begin(), First->Keys.end(), AutoPtr) )
         {
            m_MorphoTypesCollections.Clear();
            SS_THROW( L"������ CMorphoTypesCollectionAdapter::Init" );
         }
      }
   }

   ///////////////////////////////////////////////////////////////////////////////
   // IMorphoTypesCollection
   
   void SetDictionaryNumber(TDictNumber eDictionariesNumber);

   /// ������� ��� ����������������
   void DeleteType( const SS::Dictionary::Types::TIDType &IDType );

   /// ���������� ������ ���������  ���� ����������������
   void GetElements(
      const SS::Dictionary::Types::TIDType &IDType,
      std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes
   );

   /// ��������� ������ ��������� 
   /// ����������:
   ///	  S_OK - �������� ���������� ���� �������. 
   ///     E_INVALIDARG - ��������� ������ �������� �� �������
   HRESULT AddElements(std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes);

   ///������ ����� ��� ��� ������ ���������
   /// ����������:
   ///	  S_OK - �������� ���������� ���� �������. 
   ///     E_INVALIDARG - ��������� ������ �������� �� �������
   HRESULT CreateCollection(std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes);

   /// ������� ������ ���������
   /// ����������:
   ///	  S_OK - �������� �������� ���� �������. 
   ///     E_INVALIDARG - ��������� ������ ������� �� �������
   HRESULT DeleteElements(std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes);
};

} //namespace Edit
} //namespace Dictionary
} //namespace SS
