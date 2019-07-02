///////////////////////////////////////////////////////////////////////////////
// ����������� ���������� Loki:
// ���������� �����������, ���������� MultiAssocVector � ���������� 
////////////////////////////////////////////////////////////////////////////////

#ifndef AssocVector_H
#define AssocVector_H

#include <algorithm>
#include <functional>
#include <vector>
#include <utility>

namespace SS { namespace Lib {

////////////////////////////////////////////////////////////////////////////////
// class template AssocVectorCompare
// Used by AssocVector
////////////////////////////////////////////////////////////////////////////////

   namespace Private
   {
      template <class Value, class C>
      class AssocVectorCompare : public C
      {
         typedef std::pair<typename C::first_argument_type, Value>
            Data;
         typedef typename C::first_argument_type first_argument_type;

      public:
         AssocVectorCompare()
         {}

         AssocVectorCompare(const C& src) : C(src)
         {}

         bool operator()(const first_argument_type& lhs, 
            const first_argument_type& rhs) const
         { return C::operator()(lhs, rhs); }

         bool operator()(const Data& lhs, const Data& rhs) const
         { return operator()(lhs.first, rhs.first); }

         bool operator()(const Data& lhs, 
            const first_argument_type& rhs) const
         { return operator()(lhs.first, rhs); }

         bool operator()(const first_argument_type& lhs,
            const Data& rhs) const
         { return operator()(lhs, rhs.first); }
      };
   } //namespace Private

   ////////////////////////////////////////////////////////////////////////////////
   // class template AssocVector
   // An associative vector built as a syntactic drop-in replacement for std::map
   // BEWARE: AssocVector doesn't respect all map's guarantees, the most important
   //     being:
   // * iterators are invalidated by insert and erase operations
   // * the complexity of insert/erase is O(N) not O(log N)
   // * value_type is std::pair<K, V> not std::pair<const K, V>
   // * iterators are random
   ////////////////////////////////////////////////////////////////////////////////
   template
      <
         class K,
         class V,
         class C = std::less<K>,
         class A = std::allocator< std::pair<K, V> >
      >
      class AssocVector 
         : private std::vector< std::pair<K, V>, A >
         , private Private::AssocVectorCompare<V, C>
      {
         typedef std::vector<std::pair<K, V>, A> Base;
         typedef Private::AssocVectorCompare<V, C> MyCompare;

      public:
         typedef K key_type;
         typedef V mapped_type;
         typedef typename Base::value_type value_type;

         typedef C key_compare;
         typedef A allocator_type;
         typedef typename A::reference reference;
         typedef typename A::const_reference const_reference;
         typedef typename Base::iterator iterator;
         typedef typename Base::const_iterator const_iterator;
         typedef typename Base::size_type size_type;
         typedef typename Base::difference_type difference_type;
         typedef typename A::pointer pointer;
         typedef typename A::const_pointer const_pointer;
         typedef typename Base::reverse_iterator reverse_iterator;
         typedef typename Base::const_reverse_iterator const_reverse_iterator;

         class value_compare
            : public std::binary_function<value_type, value_type, bool>
            , private key_compare
         {
            friend class AssocVector;

         protected:
            value_compare(key_compare pred) : key_compare(pred)
            {}

         public:
            bool operator()(const value_type& lhs, const value_type& rhs) const
            { return key_compare::operator()(lhs.first, rhs.first); }
         };

         // 23.3.1.1 construct/copy/destroy

         explicit AssocVector(const key_compare& comp = key_compare(), 
            const A& alloc = A())
            : Base(alloc), MyCompare(comp)
         {}

         template <class InputIterator>
            AssocVector(InputIterator first, InputIterator last, 
            const key_compare& comp = key_compare(), 
            const A& alloc = A())
            : Base(first, last, alloc), MyCompare(comp)
         {
            MyCompare& me = *this;
            std::sort(begin(), end(), me);
         }

         AssocVector& operator=(const AssocVector& rhs)
         { 
            AssocVector(rhs).swap(*this); 
            return *this;
         }

         // iterators:
         // The following are here because MWCW gets 'using' wrong
         iterator begin() { return Base::begin(); }
         const_iterator begin() const { return Base::begin(); }
         iterator end() { return Base::end(); }
         const_iterator end() const { return Base::end(); }
         reverse_iterator rbegin() { return Base::rbegin(); }
         const_reverse_iterator rbegin() const { return Base::rbegin(); }
         reverse_iterator rend() { return Base::rend(); }
         const_reverse_iterator rend() const { return Base::rend(); }

         // capacity:
         bool empty() const { return Base::empty(); }
         size_type size() const { return Base::size(); }
         size_type max_size() { return Base::max_size(); }

         // 23.3.1.2 element access:
         mapped_type& operator[](const key_type& key)
         { return insert(value_type(key, mapped_type())).first->second; }

         // modifiers:
         std::pair<iterator, bool> insert(const value_type& val)
         {
            bool found(true);
            iterator i(lower_bound(val.first));

            if (i == end() || this->operator()(val.first, i->first))
            {
               i = Base::insert(i, val);
               found = false;
            }
            return std::make_pair(i, !found);
         }

         iterator insert(iterator pos, const value_type& val)
         {
            //NW 205-05-08 
            //����� Alexandrescu ��� �� ����, ���������� � ���� ����������� 
            //�������  val > *pos � val > *(pos + 1) � val >= *(pos + 1)
            //if (pos != end() && this->operator()(*pos, val) && 
            //    (pos == end() - 1 ||
            //        !this->operator()(val, pos[1]) &&
            //            this->operator()(pos[1], val)))
            //�.�. �������� ��������� ����: 
            //AssocVector<int, char> test;
            //test.insert( make_pair(0, 'a') );
            //test.insert( make_pair(5, 'b') );
            //test.insert( make_pair(10, 'c') );
            //test.insert( test.begin() + 1, make_pair(15, 'y') );
            //�� ����� ���� ������� ������ ���� *(pos - 1) < val < *pos 
            if(
               ( pos == end() || this->operator()(val, *pos) ) &&
               ( pos == begin() || this->operator()(*(pos - 1), val) ) 
               )
            {
               return Base::insert(pos, val);
            }

            return insert(val).first;
         }

         //��������� �������� ���� �������� ��� ���� �� ������, 
         //� ����� �������� ������� � ������ ������
         //�������� ����������� ��� �������� � ����������� ������� 
         //����������: first: �������� �������� � ������ key 
         //            second: true - ������� �������� ����, false - ���� key ��� ���� � ����������.
         std::pair<iterator, bool> ChangeKey( iterator pos, const key_type& key )
         {
            //���� ������� ��������� �� ��������� �� �� ����� ��������� ����� ����� �����������
            if(
               ( /*pos == end() ||*/ pos == end() - 1 || this->operator()(key, (pos + 1)->first) ) &&
               ( pos == begin() || this->operator()((pos - 1)->first, key) ) 
               )
            {
               pos->first = key;     
               return std::make_pair(pos, true);
            }

            //������� ������� ������ ��������
            iterator i(lower_bound(key));
            bool IsChanged(false);

            if (i == end() || this->operator()(key, i->first))
            {
               //���������� ��������
               mapped_type Tmp(pos->second);

               if( i > pos )
               {
                  copy( pos + 1, i, pos );
                  --i;
               }
               else
                  copy_backward( i, pos, pos + 1 );

               i->first = key;
               i->second = Tmp;

               IsChanged = true;
            }
            //else - ����� ������� ��� ����, ������ ������ �� �����

            return std::make_pair(i, IsChanged);
         }

         template <class InputIterator>
            void insert(InputIterator first, InputIterator last)
         { for (; first != last; ++first) insert(*first); }

         void erase(iterator pos)
         { Base::erase(pos); }

         size_type erase(const key_type& k)
         {
            iterator i(find(k));
            if (i == end()) return 0;
            erase(i);
            return 1;
         }

         void erase(iterator first, iterator last)
         { Base::erase(first, last); }

         void swap(AssocVector& other)
         {
            using std::swap;
            Base::swap(other);
            MyCompare& me = *this;
            MyCompare& rhs = other;
            swap(me, rhs);
         }

         void clear()
         { Base::clear(); }

         // observers:
         key_compare key_comp() const
         { return *this; }

         value_compare value_comp() const
         {
            const key_compare& comp = *this;
            return value_compare(comp);
         }

         // 23.3.1.3 map operations:
         iterator find(const key_type& k)
         {
            iterator i(lower_bound(k));
            if (i != end() && this->operator()(k, i->first))
            {
               i = end();
            }
            return i;
         }

         const_iterator find(const key_type& k) const
         {       
            const_iterator i(lower_bound(k));
            if (i != end() && this->operator()(k, i->first))
            {
               i = end();
            }
            return i;
         }

         size_type count(const key_type& k) const
         { return find(k) != end(); }

         iterator lower_bound(const key_type& k)
         {
            MyCompare& me = *this;
            return std::lower_bound(begin(), end(), k, me);
         }

         const_iterator lower_bound(const key_type& k) const
         {
            const MyCompare& me = *this;
            return std::lower_bound(begin(), end(), k, me);
         }

         iterator upper_bound(const key_type& k)
         {
            MyCompare& me = *this;
            return std::upper_bound(begin(), end(), k, me);
         }

         const_iterator upper_bound(const key_type& k) const
         {
            const MyCompare& me = *this;
            return std::upper_bound(begin(), end(), k, me);
         }

         std::pair<iterator, iterator> equal_range(const key_type& k)
         {
            MyCompare& me = *this;
            return std::equal_range(begin(), end(), k, me);
         }

         std::pair<const_iterator, const_iterator> equal_range(
            const key_type& k) const
         {
            const MyCompare& me = *this;
            return std::equal_range(begin(), end(), k, me);
         }

         friend bool operator==(const AssocVector& lhs, const AssocVector& rhs)
         {
            const Base& me = lhs;
            return me == rhs;
         } 

         bool operator<(const AssocVector& rhs) const
         {
            const Base& me = *this;
            const Base& yo = rhs;
            return me < yo;
         } 

         friend bool operator!=(const AssocVector& lhs, const AssocVector& rhs)
         { return !(lhs == rhs); } 

         friend bool operator>(const AssocVector& lhs, const AssocVector& rhs)
         { return rhs < lhs; }

         friend bool operator>=(const AssocVector& lhs, const AssocVector& rhs)
         { return !(lhs < rhs); } 

         friend bool operator<=(const AssocVector& lhs, const AssocVector& rhs)
         { return !(rhs < lhs); }
      };

      // specialized algorithms:
      template <class K, class V, class C, class A>
         void swap(AssocVector<K, V, C, A>& lhs, AssocVector<K, V, C, A>& rhs)
      { lhs.swap(rhs); }
    
      ////////////////////////////////////////////////////////////////////////////
      // ����� �������� �������� AssocVector, �� � ������� �� ���� ��������� 
      // ������� �� ���������� �����, ��� �� ��� � multimap
      ////////////////////////////////////////////////////////////////////////////
      template
         <
            class K,
            class V,
            class C = std::less<K>,
            class A = std::allocator< std::pair<K, V> >
         >
         class MultiAssocVector 
            : private std::vector< std::pair<K, V>, A >
            , private Private::AssocVectorCompare<V, C>
         {
            typedef std::vector<std::pair<K, V>, A> Base;
            typedef Private::AssocVectorCompare<V, C> MyCompare;

         public:
            typedef K key_type;
            typedef V mapped_type;
            typedef typename Base::value_type value_type;

            typedef C key_compare;
            typedef A allocator_type;
            typedef typename A::reference reference;
            typedef typename A::const_reference const_reference;
            typedef typename Base::iterator iterator;
            typedef typename Base::const_iterator const_iterator;
            typedef typename Base::size_type size_type;
            typedef typename Base::difference_type difference_type;
            typedef typename A::pointer pointer;
            typedef typename A::const_pointer const_pointer;
            typedef typename Base::reverse_iterator reverse_iterator;
            typedef typename Base::const_reverse_iterator const_reverse_iterator;

            class value_compare
               : public std::binary_function<value_type, value_type, bool>
               , private key_compare
            {
               friend class MultiAssocVector;

            protected:
               value_compare(key_compare pred) : key_compare(pred)
               {}

            public:
               bool operator()(const value_type& lhs, const value_type& rhs) const
               { return key_compare::operator()(lhs.first, rhs.first); }
            };

            // 23.3.1.1 construct/copy/destroy

            explicit MultiAssocVector(const key_compare& comp = key_compare(), 
               const A& alloc = A())
               : Base(alloc), MyCompare(comp)
            {}

            template <class InputIterator>
               MultiAssocVector(InputIterator first, InputIterator last, 
               const key_compare& comp = key_compare(), 
               const A& alloc = A())
               : Base(first, last, alloc), MyCompare(comp)
            {
               MyCompare& me = *this;
               std::sort(begin(), end(), me);
            }

            MultiAssocVector& operator=(const MultiAssocVector& rhs)
            { 
               MultiAssocVector(rhs).swap(*this); 
               return *this;
            }

            // iterators:
            // The following are here because MWCW gets 'using' wrong
            iterator begin() { return Base::begin(); }
            const_iterator begin() const { return Base::begin(); }
            iterator end() { return Base::end(); }
            const_iterator end() const { return Base::end(); }
            reverse_iterator rbegin() { return Base::rbegin(); }
            const_reverse_iterator rbegin() const { return Base::rbegin(); }
            reverse_iterator rend() { return Base::rend(); }
            const_reverse_iterator rend() const { return Base::rend(); }

            // capacity:
            bool empty() const { return Base::empty(); }
            size_type size() const { return Base::size(); }
            size_type max_size() { return Base::max_size(); }

            // modifiers:
            iterator insert(const value_type& val)
            {
               return Base::insert(upper_bound(val.first), val);
            }

            iterator insert(iterator pos, const value_type& val)
            {
               if(
                  ( pos == end() || !this->operator()(*pos, val) ) &&
                  ( pos == begin() || !this->operator()(val, *(pos - 1)) ) 
                  )
               {
                  return Base::insert(pos, val);
               }

               return insert(val);
            }

            //��������� �������� ���� �������� ��� ���� �� ������ 
            //(� ����� ��������) ������� � ����� ������
            //��� ���� �� ������������� ��� ������� � ����� ������ ����� 
            //����� ��������� �� ��������� � ����������� ������� (�.�. 
            //������� �������� ����������� ����� ��������� ���� �������)
            //�������� ����������� ��� �������� � ����������� ������� 
            //����������: �������� �������� � ������ key 
            iterator ChangeKey( iterator pos, const key_type& key )
            {
               //���� ������� ��������� �� ��������� �� �� ����� ��������� ����� ����� �����������
               if(
                  ( /*pos == end() ||*/ pos == end() - 1 || !this->operator()((pos + 1)->first, key) ) &&
                  ( pos == begin() || !this->operator()( key, (pos - 1)->first) ) 
                  )
               {
                  pos->first = key;     
                  return pos;
               }

               //������� ������� ������ ��������
               iterator i(upper_bound(key));

               //���������� ��������
               mapped_type Tmp(pos->second);

               if( i > pos )
               {
                  copy( pos + 1, i, pos );
                  --i;
               }
               else
                  copy_backward( i, pos, pos + 1 );

               i->first = key;
               i->second = Tmp;

               return i;
            }

            template <class InputIterator>
               void insert(InputIterator first, InputIterator last)
            { for (; first != last; ++first) insert(*first); }

            void erase(iterator pos)
            { Base::erase(pos); }

            size_type erase(const key_type& k)
            {
               std::pair<iterator, iterator> IterPair(equal_range(k));
      
               size_type RetVal( std::distance(IterPair.first, IterPair.second) );
               
               erase(IterPair.first, IterPair.second);
               return RetVal;
            }

            void erase(iterator first, iterator last)
            { Base::erase(first, last); }

            void swap(MultiAssocVector& other)
            {
               using std::swap;
               Base::swap(other);
               MyCompare& me = *this;
               MyCompare& rhs = other;
               swap(me, rhs);
            }

            void clear()
            { Base::clear(); }

            // observers:
            key_compare key_comp() const
            { return *this; }

            value_compare value_comp() const
            {
               const key_compare& comp = *this;
               return value_compare(comp);
            }

            // 23.3.1.3 map operations:
            iterator find(const key_type& k)
            {
               iterator i(lower_bound(k));
               if (i != end() && this->operator()(k, i->first))
               {
                  i = end();
               }
               return i;
            }

            const_iterator find(const key_type& k) const
            {       
               const_iterator i(lower_bound(k));
               if (i != end() && this->operator()(k, i->first))
               {
                  i = end();
               }
               return i;
            }

            size_type count(const key_type& k) const
            { 
               std::pair<const_iterator, const_iterator> IterPair(equal_range(k));

               return std::distance(IterPair.first, IterPair.second);
            }

            iterator lower_bound(const key_type& k)
            {
               MyCompare& me = *this;
               return std::lower_bound(begin(), end(), k, me);
            }

            const_iterator lower_bound(const key_type& k) const
            {
               const MyCompare& me = *this;
               return std::lower_bound(begin(), end(), k, me);
            }

            iterator upper_bound(const key_type& k)
            {
               MyCompare& me = *this;
               return std::upper_bound(begin(), end(), k, me);
            }

            const_iterator upper_bound(const key_type& k) const
            {
               const MyCompare& me = *this;
               return std::upper_bound(begin(), end(), k, me);
            }

            std::pair<iterator, iterator> equal_range(const key_type& k)
            {
               MyCompare& me = *this;
               return std::equal_range(begin(), end(), k, me);
            }

            std::pair<const_iterator, const_iterator> equal_range(
               const key_type& k) const
            {
               const MyCompare& me = *this;
               return std::equal_range(begin(), end(), k, me);
            }

            friend bool operator==(const MultiAssocVector& lhs, const MultiAssocVector& rhs)
            {
               const Base& me = lhs;
               return me == rhs;
            } 

            bool operator<(const MultiAssocVector& rhs) const
            {
               const Base& me = *this;
               const Base& yo = rhs;
               return me < yo;
            } 

            friend bool operator!=(const MultiAssocVector& lhs, const MultiAssocVector& rhs)
            { return !(lhs == rhs); } 

            friend bool operator>(const MultiAssocVector& lhs, const MultiAssocVector& rhs)
            { return rhs < lhs; }

            friend bool operator>=(const MultiAssocVector& lhs, const MultiAssocVector& rhs)
            { return !(lhs < rhs); } 

            friend bool operator<=(const MultiAssocVector& lhs, const MultiAssocVector& rhs)
            { return !(rhs < lhs); }
        };
         // specialized algorithms:
         template <class K, class V, class C, class A>
            void swap(MultiAssocVector<K, V, C, A>& lhs, MultiAssocVector<K, V, C, A>& rhs)
         { lhs.swap(rhs); }

}} //namespace SS::Lib 


////////////////////////////////////////////////////////////////////////////////
// Change log:
// May 20, 2001: change operator= - credit due to Cristoph Koegl
// June 11, 2001: remove paren in equal_range - credit due to Cristoph Koegl
// June 20, 2001: ported by Nick Thurn to gcc 2.95.3. Kudos, Nick!!!
// January 22, 2002: fixed operator= - credit due to Tom Hyer
// June 25, 2002: fixed template insert() - credit due to Robert Minsk
// June 27, 2002: fixed member swap() - credit due to David Brookman
////////////////////////////////////////////////////////////////////////////////

#endif // AssocVector_H
