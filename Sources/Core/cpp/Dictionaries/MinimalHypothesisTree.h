#pragma once

namespace SS{ 
namespace Dictionary{
namespace MinimalHypothesisTree{

using namespace SS::Dictionary;


/**
   ������ ��������� ���������� "������������ ������ ������ �������". ��� ������ �� �������� ����� ���������� 
   � ������� ����� ����������� ��������������� ���������� �� ������ ����� (��������). ��� ���� ��� ���� ���� �� 
   ������� ��������� ������ ����� ������ ���������� ������ ��������������� �����������. �.�. ����
   �������� ����� ���� � ��������������� ���������� �� ���, ������� ��������  
   ����������� ����������� ��������� �������� ���������������� � �� ������ ����������� ������ ������ ��� ���� 
   ����. �� ����� ������, ��������, ����� ���������� ��������������� ���������� � ����� �����.

   ������ �������� ��������� �������, ������ ���� ������ ��� ��������� ����� � �����, � ������ ����� ������ (� ������ ������ ���� ���� �� ������).
   ������ ������ ������ ����� �� ������� ����� ������������ ����� � �������, � ������ ������� ��� ����� � ����� ��������� 
   ����� �������. �.�. �� ������ ����� � �������� ������� � ������ � ������� ��� ������� ������ ���� �������� ����� ����������
   ������� ������� ����� ��������� ����� ����� ����� ������������� �� �������� ���� � ���� ��� ���������:
      ���� � ������� 3 ����� "���", "���", "���" �� ������ ����� ���������:
                                 �     �
                                 |     |
                                 �     �
                                / \    |
                               �   �   �
   
   � ������ ����� ������ �������� � ������ � ���������� ���� �������� ��������������� ���������� � �����.
   ���� � ���� ���� ��������������� �� ����� �� ����� �� ����� ���� ����� ������� ������������ � �������.
   �.�. ��� ����������� �������� ���������� ����� ����� ������� ����������� � ����� ����� � ������, ��� ��������������� ���������� 
   � ����� ���������.

   ����� ���� ��� ������ ���� ���������, ������������ ����������� �� ����-�� ���������:
      ��� ������� ���� ������� � ����� �������� �� ����� � ���������� ���������� � �����:
         ���� ���� �������� ������ �� ��������� � ���������� ����

         ���� � ���� ��� ��������������� ���-�� (��), �� �������� �� �� �������� �� ������� ����������� �������� �����
         � ����������� � �������� ����

         ��� ����� ��������� �������� ���� � ������� �� ��������� � ������� ����� �������� ����-�� ��������:
         ���� ��� ���� �� ������� ���, ���� �� ���� �������� ��.
*/

///////////////////////////////////////////////////////////////////////////////
// ���������� ���������� ������� ������ ������ �� ���������� ������ � ��������� 
// � ������� ���� �������� ��������� ���������
// K - ���� ������, �������������� ���������� � ���� �������� ����
// V - �������������� ���������� �� ����
///////////////////////////////////////////////////////////////////////////////
template<class K, class V>   
class CTree
{   
public:
   typedef K TKey;     //���� �� �������� �������� ������
   typedef V TValue;   //�������� ������� ������������� ������� �����
   class CNode;

private:
   typedef std::map<TKey, CNode> TChildrenStorage;

public:
   typedef  typename TChildrenStorage::iterator TNodeIterator;               //�������� �����, ������ �� ��������� �������� std::pair<TKey, CNode>
   typedef  typename TChildrenStorage::const_iterator TConstNodeIterator;    //����������� �������� �����

public:
   //���� ������
   class CNode
   { 
      TChildrenStorage m_ChildrenStorage;
      TValue m_Value;

   public:
      explicit CNode( TValue Value = TValue() ): m_Value(Value) {};
       
      //�������� ����
      const TValue &GetValue() const{ return m_Value; }
      void SetValue( const TValue &Value ){ m_Value = Value; }

      //�������� �� ������ (��� ��������)
      bool IsLeaf() const { return m_ChildrenStorage.empty(); }

      //������ � ����� ��������� �������� �����
      TNodeIterator Begin(){ return m_ChildrenStorage.begin(); }
      TNodeIterator End()  { return m_ChildrenStorage.end(); }
      TConstNodeIterator Begin() const { return m_ChildrenStorage.begin(); }
      TConstNodeIterator End() const   { return m_ChildrenStorage.end(); }

      //�������� �������� ���� ������ � ��� ������ ���� ��� ��� �������� ����� � ������ Key.
      //���������� � ������ ���������� ���� �������� ��������� ���� � ������ Key (���� ������ ���
      //������������, ���� ��������������� �� �������). ������ ���������� ���������� ���� �� �������.
      std::pair<TNodeIterator, bool> Insert( const TKey &Key, const CNode &Node = CNode() )
      { return m_ChildrenStorage.insert( TChildrenStorage::value_type(Key, Node) ); }

      //������� �������� ���� � ���� ��� ��������
      void Erase( TNodeIterator Pos ){ m_ChildrenStorage.erase(Pos); }
      void Erase( TNodeIterator Begin ,TNodeIterator End ){ m_ChildrenStorage.erase(Begin, End); }

      //����� ������� � ������ Key. ����� End � ������ ���������� ������
      TConstNodeIterator Find( const TKey &Key ) const { return m_ChildrenStorage.find(Key); }
      TNodeIterator Find( const TKey &Key ) { return m_ChildrenStorage.find(Key); }

      //������� ��� �������
      void Clear(){ m_ChildrenStorage.clear(); }
   };

private:
   CNode m_RootNode;

public:
   //�������� ����������� � ������������ ��������������� ������������ ������ ��������
   
   //����������� ������ ������ (���������� ���� � ������ ������)
   const CNode &Root() const { return m_RootNode; }
   CNode &Root() { return m_RootNode; }
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ����� ������� ��������� ���������� ������������ ������ ������
///////////////////////////////////////////////////////////////////////////////
class CMinimalHypothesisTree
{
public:   
   
   //��������� ��������� ������� ��� ��������������� � �����
   struct SMorhpo//: public CObjectCount<SMorhpo>
   {
      typedef std::set<TIDType> TIDTypeStotage;

      TIDTypeStotage m_IDTypes;

      friend bool operator ==( const SMorhpo& M1, const SMorhpo& M2 )
      { return M1.m_IDTypes == M2.m_IDTypes; } 
      
      friend bool operator !=( const SMorhpo& M1, const SMorhpo& M2 )
      { return M1.m_IDTypes != M2.m_IDTypes; } 
      
      
      friend bool operator<( const SMorhpo& M1, const SMorhpo& M2 )
      { return M1.m_IDTypes < M2.m_IDTypes; } 
   };

   typedef CAutoRefCount<SMorhpo> TMorphoCreator;
   typedef wchar_t TChar;

private:
   struct SMorphoLess: public std::binary_function<TMorphoCreator::SmartPtr, TMorphoCreator::SmartPtr, bool>
   {
      bool operator()( TMorphoCreator::SmartPtr P1, TMorphoCreator::SmartPtr P2 ) const
      {
         APL_ASSERT( P1 != 0 && P2 != 0 );           
         return *P1 < *P2;
      }
   };
 
   
   //����� ��������� ����� �����������, �� ���������������. 
   //��������� ����������� ��������������� ��������� �����������, �������� ����� ����������� ��� 
   //��������� � �������� ��������������� � ������������ �������������.
   class CMorphoStatistic                                 
   {
      typedef std::multimap<size_t, TMorphoCreator::SmartPtr> TPriorityStorage; //����������� ������ ���������������      
      typedef std::map<TMorphoCreator::SmartPtr, TPriorityStorage::iterator, SMorphoLess> TMorphoStorage; //�������� ���������������
   
   private:
      TPriorityStorage m_PriorityStorage;
      TMorphoStorage m_MorphoStorage;

   public:
      bool Empty() const { return m_PriorityStorage.empty(); }
      void Clear() { m_PriorityStorage.clear(); m_MorphoStorage.clear(); }

      //�������� ����������� ��������������� �� D. (���� ����� ��� �� ����������� ����� � ���������� ���������� D)
      void Change( TMorphoCreator::SmartPtr Ptr, size_t D )
      {
         APL_ASSERT( Ptr != 0 );

         TMorphoStorage::iterator I = m_MorphoStorage.find(Ptr);

         if( I == m_MorphoStorage.end() )
         {
            APL_ASSERT( std::find_if(m_PriorityStorage.begin(), m_PriorityStorage.end(),
               std::bind2nd(
                  binary_compose_1arg( 
                     std::equal_to<SMorhpo>(), 
                     unary_compose_1arg( pointer_deref_t<TMorphoCreator::SmartPtr, SMorhpo>(), select_second_t<TPriorityStorage::value_type>() ),
                     pointer_deref_t<TMorphoCreator::SmartPtr, SMorhpo>() 
                  ),
                  Ptr
               ) ) == m_PriorityStorage.end()
            );

            TPriorityStorage::iterator J = m_PriorityStorage.insert( TPriorityStorage::value_type(D, Ptr) );
            APL_CHECK( m_MorphoStorage.insert(TMorphoStorage::value_type(Ptr, J)).second );
         }
         else
         {            
            std::pair<size_t, TMorphoCreator::SmartPtr> VT(*I->second);
            VT.first += D;
            m_PriorityStorage.erase(I->second);
            
            //std::pair<TPriorityStorage::iterator, bool> Rez( m_PriorityStorage.insert(VT) );  
            //APL_ASSERT( Rez.second );
            I->second = m_PriorityStorage.insert(VT);
         }
      }

      //��������������� � ������������ �����-��.
      TMorphoCreator::SmartPtr GetMax() const { APL_ASSERT(!Empty()); return m_PriorityStorage.rbegin()->second; }

      //�������� ���������� �� ������� ���������� ����������
      void AddStatistic( const CMorphoStatistic &MS )
      {
         for( TPriorityStorage::const_iterator I = MS.m_PriorityStorage.begin(); I != MS.m_PriorityStorage.end(); ++I )
            Change( I->second, I->first );
      }
   };

   //���� ��� � CMorphoStatistic, �� ��������� ������ ���������������� �������� �� 1
   class CMorphoStatisticLite                                 
   {
      typedef std::map<TMorphoCreator::SmartPtr, size_t, SMorphoLess> TMorphoStorage; //�������� ���������������

   private:
      TMorphoStorage m_MorphoStorage;
      TMorphoStorage::iterator m_CurMaxIter;

   public:
      CMorphoStatisticLite(): m_CurMaxIter(m_MorphoStorage.end()) {}
      bool Empty() const { return m_MorphoStorage.empty(); }
      void Clear() {  m_MorphoStorage.clear(); m_CurMaxIter = m_MorphoStorage.end(); }

      //�������� ����������� ��������������� �� 1. (���� ����� ��� �� ����������� ����� � ���������� ���������� 1)
      void Increment( TMorphoCreator::SmartPtr Ptr )
      {
         APL_ASSERT( Ptr != 0 );

         TMorphoStorage::iterator I = m_MorphoStorage.find(Ptr);

         if( I == m_MorphoStorage.end() )
         {          
            std::pair<TMorphoStorage::iterator, bool> Rez( m_MorphoStorage.insert(TMorphoStorage::value_type(Ptr, 1)) );
            
            APL_ASSERT( Rez.second );
            I = Rez.first;
         }
         else
         {    
            ++I->second;
         }

         if( m_CurMaxIter == m_MorphoStorage.end() || I->second > m_CurMaxIter->second )
            m_CurMaxIter = I;   
      }

      //��������������� � ������������ �����-��.
      TMorphoCreator::SmartPtr GetMax() const { APL_ASSERT(!Empty()); return m_CurMaxIter->first; }
   };
   
   typedef CTree<TChar, TMorphoCreator::SmartPtr>  TTree;

public:

   //������ ����������� ������ �� ���� ������ �� ������
   class SCursor
   {
   public:    
      typedef std::basic_string<TChar> TWord;

   private:
      friend CMinimalHypothesisTree;
      typedef std::deque<std::pair<TTree::TConstNodeIterator, TTree::TConstNodeIterator> > TIterStack; 
   
   private:
      TIterStack IterStack;                        //���� � ����������� �������� ��������� � ������
      TWord Word;                                  //���� �����
      TMorphoCreator::ConstSmartPtr Ptr;           //��������� �� ���������������

   public:
      //������� �����
      const TWord &GetWord() const { return Word; }
      const TMorphoCreator::ConstSmartPtr &GetPtr() const { return Ptr; }

      //���������� �� �����
      bool End() const { return IterStack.empty(); }
   };

   //�������������� ������ �� ������
   struct SStatistic
   {
      typedef size_t UnsignedT;
      UnsignedT WordsCount;        //���������� ���� � ������
      UnsignedT CharCount;         //���������� ���� �� ���� ������ � ������
      UnsignedT NodeCount;         //���������� ����� � ������
      UnsignedT TypesCount;        //��������� ���������� ����� ������� ����� ������� �� ���� (����� SMorhpo.m_IDTypes)

      void Clear()
      {
         WordsCount = 0;
         CharCount = 0; 
         NodeCount = 0; 
         TypesCount = 0;
      }
   };


private:
   TTree m_Tree;

private:
   //��������� ��� ����� ����������� ���������� � �������� 1
   //�������� � ������ ���������� �� ������������� ������� ������� ��� 
   //std::distance(I1, I2) == 1
   template< class InputIterator >
   static bool DistanceEqual1( InputIterator I1, InputIterator I2 )
   {
      return I1 != I2 && ++InputIterator(I2) == I2;
   }
   
   //���������� ����������� ������. ���������� ����������.
   //Node - ������� ����
   //MS - ������������ ���������� �� ��������������� � ���� ����� ������ �� Node  
   void OptimizeTreeImpl( TTree::CNode &Node );
   //TMorphoCreator::SmartPtr OptimizeTreeImpl( TTree::CNode &Node );

   //����������: ������� �������������� ������ �� ������, ���������� ����������
   //Depth - �������  �������� ���� ������ (���������� � 1)
   void CalcStatisticDataImpl( const TTree::CNode &Node, SStatistic &Statistic, size_t Depth ) const;

public:  
   
   //�������� ������ [Begin, End) ��������������� �� ��� � ������.
   //[Begin, End) - ��� ������
   //Ptr - ��������������� �� ���.
   //�����: ������� �� �������� ����� (���� ����� ����� ��� ���� ������� �� ����������)
   template<class InputIterator>
   bool AddString( InputIterator Begin, InputIterator End, TMorphoCreator::SmartPtr Ptr )
   {
      TTree::CNode *pNode = &m_Tree.Root();
      
      std::pair<TTree::TNodeIterator, bool> ResultPair;

      for( ; Begin != End; ++Begin )
      {
         ResultPair = pNode->Insert( *Begin  );

         pNode = &ResultPair.first->second;
      }

      if( pNode->GetValue() != 0 )
         return false;

      pNode->SetValue(Ptr);

      return true;
   }
   
   //���������� ��������������� �� ����� [Begin, End)��� ���� ������� ��� ������-�� 0
   template<class InputIterator>
   TMorphoCreator::ConstSmartPtr GetMorpho( InputIterator Begin, InputIterator End ) const
   {
      TMorphoCreator::ConstSmartPtr RetValue;
      const TTree::CNode *pNode = &m_Tree.Root();
      TTree::TConstNodeIterator I;

      for( ; Begin != End; ++Begin )
      {
         I = pNode->Find( *Begin  );

         if( I == pNode->End() )
            break;

         pNode = &I->second;

         if( pNode->GetValue() != 0 )
            RetValue = pNode->GetValue();
      }

      return RetValue;
   }

   //������������� ������������ �����
   //� ����� ������� ����� ���� ����. ���� � ������ ��� �� ������ ����� �� Cursor.End() == true
   void ScanInit( SCursor &Cursor ) const;

   //����� ��������� �����, ����� ��������� ����� ����������� ���� ��� ������� ScanInit, � ����� ����
   //�� Cursor.End() == false �������� ScanNext
   void ScanNext( SCursor &Cursor ) const;

   //�������������� ������, �.�. ������� ����������� ������ ������, �� �������� ��������� ����.
   void OptimizeTree()
   { 
      for( TTree::TNodeIterator I = m_Tree.Root().Begin(); I != m_Tree.Root().End(); ++I )
         OptimizeTreeImpl(I->second); 
   }

   //������� �������������� ������ �� ������
   void CalcStatisticData( SStatistic &Statistic ) const
   { 
      Statistic.Clear();

      for( TTree::TConstNodeIterator I = m_Tree.Root().Begin(); I != m_Tree.Root().End(); ++I )
         CalcStatisticDataImpl(I->second, Statistic, 1); 
   }

   //������ �������
   void Clear(){ m_Tree.Root().Clear(); }
};


///////////////////////////////////////////////////////////////////////////////
// ������� �����.
// ��������������� �������� ��� ���������� ������������ ������ ������
///////////////////////////////////////////////////////////////////////////////
class CFacade
{
   typedef CMorphoTypesSearchCreateManager::TPointer TMorphoTypesSearchPtr;

private:
   CMinimalHypothesisTree m_MinimalHypothesisTree;

   IAMConverterMorpho  *m_pAMConverter;
   TMorphoTypesSearchPtr m_pMorphoTypesSearch;
   TDictNumber m_DictNumber;

private:
   //����� �� �������� ����� IDType
   bool CanAddIDType( TIDType IDType );

public:
   CFacade(): m_pAMConverter(0), m_DictNumber(DATA_TYPE::NAMES::ednUnknown) { }
   
   //���������������� ������
   void Init( IAMConverterMorpho *pAMConverter, DBMS::IDataBase *pDataBase, TDictNumber DictNumber );

   //��������� ������ �� ����� ��������������� �� ���� ������������������ ��������������� ����� ����. �������: 
   //    <����� � ������� ������� ����><���������� ������(�)><IDType>
   void LoadFromFile( const char *pFileName );

   //�������� � ������ ����� � ������� ��������������� (������ IDType).
   //���������� ������� ��� ������� ����������� ����� ������� � ��������������� �� ����.
   //    Str - ����������� �����. ������������ � ��������������� ���� (������ "����" ���������� �������� "����")
   //    TypesList - ����� IDType ������� ����� ���� �������� �� ����� Str
   //    ���������: ������� �� �������� ����� (���� ����� ����� ��� ���� � ������ ��� ���� ��� IDType 
   //               � TypesList �� �������� �������������, ���������� �� ����������)
   bool AddStringReverse( const std::wstring &Str, const TTypesList &TypesList );

   //�������������� ��� �� �������� ������ ��������� ����� �� ���� ��� � �� �����
   bool TestTree( const char *pFileName ) const;

   //��������� ������ � ���� �������� ������� � LoadFromFile
   void SaveToFileOriginal( const char *pFileName ) const;

   //��������� ������ � ���� � ������� ��� IDType ���� � ���� ������
   //TotalWordCount - ���������� ����
   //TotalCharCount - ���������� �������� �� ���� ������
   void SaveToFileStrict( const char *pFileName, size_t &TotalWordCount, size_t &TotalCharCount ) const;

   //��������� ������ � ������� �� ����������:
   //       #DATA_FIELD_INFO = "ID"        : INT32              // IDType
   //       #DATA_FIELD_INFO = "Word"      : WSTRING - NO_FIND  // ����������� ������������� ���������
   //��� ���� ����� ������������ � �������� ������� ���������� ���� (�.�. � ������� �������� ����������� �����)
   void SaveToTable( DBMS::IDataTable *pTable ) const ;

   //�������������� ������
   void Optimize() { m_MinimalHypothesisTree.OptimizeTree(); }

   typedef CMinimalHypothesisTree::SStatistic TStatistic;
   
   void CalcStatisticData( TStatistic &Statistic ) const { m_MinimalHypothesisTree.CalcStatisticData(Statistic); }

   void Clear() { m_MinimalHypothesisTree.Clear(); }
};


class CMinimalHypothesisTreeBuilder: public IMinimalHypothesisTreeBuilder
{
   CDBMSPtrsManager m_DBMSPtrsManager;
   DBMS::IDataBase *m_pMorphoDB;
   CFacade m_Facade;

public:
   CMinimalHypothesisTreeBuilder(): m_pMorphoDB(0) {}

   bool Init( TDictNumber DictNumber );
   bool AddReverseWord( const std::wstring* pwReverseWord, const TTypesList* pTypesList );
   void Build();

public:
   RELEASE_IMPL()

   BEGIN_QI_MAP()
      QI_MAP_INHERIT_ENTRY( IID_Base, IBase )
      QI_MAP_INHERIT_ENTRY( IID_IMinimalHypothesisTreeBuilder, IMinimalHypothesisTreeBuilder )
   END_QI_MAP()
};

} //namespace MinimalHypothesisTree
} //namespace Dictionary
} //namespace SS
