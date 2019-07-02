#pragma once

#include "../FeatureLibrary/define.h"
#include "../FeatureLibrary/MorphoFeatureApriori.h"
#include "../FeatureLibrary/MorphoFeatureAposteriori.h"
#include "../FeatureLibrary/SemanticFeatureApriori.h"
#include "../FeatureLibrary/SemanticFeatureAposteriori.h"
#include "./TSyntaxConstructions.h"

#include <vector>
#include <list>
#include <string>

namespace SS
{
	namespace SyntaxConstructions
	{
		namespace Types
		{
			
			///����� ����������� ������ �����������
			class CConstructionObject
			{
			public:
				CConstructionObject() : m_wsDetectWordGroupName(L"")
				{
				}

				CConstructionObject(const CConstructionObject & value) //ADDED
				{
					SS_TRY

					m_MorphoFeatureApriori.Assign(&value.m_MorphoFeatureApriori);
					m_SyntaxFeatureApriori.Assign(&value.m_SyntaxFeatureApriori);
               m_SemanticFeatureApriori.Assign(&value.m_SemanticFeatureApriori);
               m_ObjectFeature.Assign(&value.m_ObjectFeature);
					m_MorphoFeatureAposteriori.Assign(&value.m_MorphoFeatureAposteriori);
					m_SyntaxFeatureAposteriori.Assign(&value.m_SyntaxFeatureAposteriori);
               m_SemanticFeatureAposteriori.Assign(&value.m_SemanticFeatureAposteriori);
					m_wsDetectWordGroupName = value.m_wsDetectWordGroupName;
					m_DetectWordsGroup		= value.m_DetectWordsGroup;

					SS_CATCH(L"")										
				};
			/*	���� ����������	*/
			public:

				CConstructionObject & operator=(const CConstructionObject & value)
				{
					SS_TRY
					{
						m_MorphoFeatureApriori.Assign(&value.m_MorphoFeatureApriori);
						m_SyntaxFeatureApriori.Assign(&value.m_SyntaxFeatureApriori);
                  m_SemanticFeatureApriori.Assign(&value.m_SemanticFeatureApriori);
						m_ObjectFeature.Assign(&value.m_ObjectFeature);
						m_MorphoFeatureAposteriori.Assign(&value.m_MorphoFeatureAposteriori);
						m_SyntaxFeatureAposteriori.Assign(&value.m_SyntaxFeatureAposteriori);
                  m_SemanticFeatureAposteriori.Assign(&value.m_SemanticFeatureAposteriori);
						m_wsDetectWordGroupName = value.m_wsDetectWordGroupName;
						m_DetectWordsGroup = value.m_DetectWordsGroup;
					}
					SS_CATCH(L"")										

					return *this;					
					
				};

				//�������� ==
				bool operator==(const CConstructionObject & value) const
				{
					SS_TRY
					{
						if( (m_MorphoFeatureApriori.Equal(&value.m_MorphoFeatureApriori))&&
							(m_SyntaxFeatureApriori.Equal(&value.m_SyntaxFeatureApriori))&&
							(m_SemanticFeatureApriori.Equal(&value.m_SemanticFeatureApriori))&&
  							(m_ObjectFeature.Equal(&value.m_ObjectFeature))&&
							(m_MorphoFeatureAposteriori.Equal(&value.m_MorphoFeatureAposteriori))&&
							(m_SyntaxFeatureAposteriori.Equal(&value.m_SyntaxFeatureAposteriori))&&
                     (m_SemanticFeatureAposteriori.Equal(&value.m_SemanticFeatureAposteriori))&&
							(m_wsDetectWordGroupName == value.m_wsDetectWordGroupName)&&
							(m_DetectWordsGroup	== value.m_DetectWordsGroup) )
						{ return true; }
					}
					SS_CATCH(L"")										

					return false;
				};

				//�������� !=
				bool operator != (const CConstructionObject & value) const
				{
					if ( (*this) == (value) )
					{ return false;	}
					
					return true;
				};
		
			public:
				TDetectWordsGroup & GetDetectWords()
				{
					return m_DetectWordsGroup;
				}
				void SetDetectWords(TDetectWordsGroup & DetectWordsGroup)
				{
					m_DetectWordsGroup = DetectWordsGroup;
				}

				std::wstring & GetDetectWordGroupName()
				{
					return m_wsDetectWordGroupName;
				}
				void SetDetectWordGroupName(std::wstring wsDetectWordGroupName)
				{
					m_wsDetectWordGroupName = wsDetectWordGroupName;
				}
				void GetValue(std::vector<unsigned char> & vecOfByte)
				{
					SS_TRY
					{
						m_MorphoFeatureApriori.GetValue(vecOfByte);
						m_SyntaxFeatureApriori.GetValue(vecOfByte);
						m_SemanticFeatureApriori.GetValue(vecOfByte);
						m_ObjectFeature.GetValue(vecOfByte);
						//��������������� ���
						//unsigned char ch = 0;
						//for (int i = 0; i < 8; ++i)
						//{ vecOfByte.push_back(ch); }
						//����� ���������������� ����
						m_MorphoFeatureAposteriori.GetValue(vecOfByte);
						m_SyntaxFeatureAposteriori.GetValue(vecOfByte);
						m_SemanticFeatureAposteriori.GetValue(vecOfByte);
					}
					SS_CATCH(L"")
				}
				// ���������� ������������������ ����, ������� ��������� ��������� ������ ���������				
				void SetValue(std::vector<unsigned char> & vecOfByte)
				{	
					SS_TRY
					{	
						unsigned int uiPosition = 0;

						m_MorphoFeatureApriori.SetValue(vecOfByte, uiPosition);		
						m_SyntaxFeatureApriori.SetValue(vecOfByte, uiPosition);
						m_SemanticFeatureApriori.SetValue(vecOfByte, uiPosition);
						m_ObjectFeature.SetValue(vecOfByte, uiPosition);
						m_MorphoFeatureAposteriori.SetValue(vecOfByte, uiPosition);
						m_SyntaxFeatureAposteriori.SetValue(vecOfByte, uiPosition);
						m_SemanticFeatureAposteriori.SetValue(vecOfByte, uiPosition);
					}
					SS_CATCH(L"")
				}

            //�������� ������ 
            void Clear()
            {
               SS_TRY
               {
                  m_MorphoFeatureApriori.Undefine();
                  m_SyntaxFeatureApriori.Undefine();
                  m_SemanticFeatureApriori.Undefine();
                  m_ObjectFeature.Undefine();
                  m_MorphoFeatureAposteriori.Undefine();
                  m_SyntaxFeatureAposteriori.Undefine();
                  m_SemanticFeatureAposteriori.Undefine();
               }
               SS_CATCH(L"")
            }


			public:
				///��������������� �������������� ��� ��������������
				SS::Core::Features::CMorphoFeatureApriori		m_MorphoFeatureApriori;
				///�������������� �������������� ��� ��������������
				SS::Core::Features::CSyntaxFeatureApriori		m_SyntaxFeatureApriori;
				///������������� �������������� ��� ��������������
				SS::Core::Features::CSemanticFeatureApriori				m_SemanticFeatureApriori;
            SS::Core::Features::CSemanticFeatureAposteriori		   m_SemanticFeatureAposteriori;
				///��������� ����
				SS::Core::Features::CObjectFeature				m_ObjectFeature;
				//��������������� ���������� ��� ���������
				SS::Core::Features::CMorphoFeatureAposteriori	m_MorphoFeatureAposteriori;
				//�������������� �������������� ��� ���������
				SS::Core::Features::CSyntaxFeatureAposteriori	m_SyntaxFeatureAposteriori;				

			protected:
				//����������� ������������ ����� ��� ��������������
				std::wstring m_wsDetectWordGroupName;	
				TDetectWordsGroup m_DetectWordsGroup;
			};

			///������� ��� �����������
			class CConstruction
			{
			public:
				typedef std::list<CConstructionObject*> TListOfConstructionObject;
				typedef TListOfConstructionObject::const_iterator iterator; 
			public:
				CConstruction() 
				{
				}
				CConstruction(const CConstruction & oConstruction) 
				{
					SS_TRY
					{
						clear();
						
						TListOfConstructionObject::const_iterator iter;

						for(iter = oConstruction.m_Objects.begin(); iter != oConstruction.m_Objects.end(); iter++)
						{ push_back(*(*iter)); }
					}
					SS_CATCH(L"")

				}
				virtual~ CConstruction() 
				{
					clear();
				}
				/*	������������ �������	*/
			public:
				iterator begin() const
				{
					return m_Objects.begin();
				}
				iterator end() const
				{
					return m_Objects.end();
				}

				void push_back(const CConstructionObject & oConstructionObject)
				{
					SS_TRY

						CConstructionObject* pConstructionObject = new CConstructionObject( oConstructionObject );//ADDED
						m_Objects.push_back(pConstructionObject);

					SS_CATCH(L"")
				}

				void clear()
				{
					SS_TRY

						TListOfConstructionObject::iterator iter;
						for(iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
						{ delete (*iter); }

						m_Objects.clear();
					
					SS_CATCH(L"")
				}


				unsigned int GetObjectCount() const
				{
					return (unsigned int)m_Objects.size();
				}
				
			public:	
				//�������� ==
				bool operator==(const CConstruction & value) const
				{
					SS_TRY

						if ( m_Objects.size() != value.m_Objects.size() )
						{ return false; }

						TListOfConstructionObject::const_iterator iterOwn;
						TListOfConstructionObject::const_iterator iterOther;

						for ( iterOwn = m_Objects.begin(), iterOther = value.m_Objects.begin();
							  iterOwn != m_Objects.end(), iterOther != value.m_Objects.end();
							  iterOwn++, iterOther++ )
						{
							if ( (*(*iterOwn)) != (*(*iterOther)) )
							{ return false; }
						}				

					SS_CATCH(L"")

					return true;
				};

				//�������� !=
				bool operator!=(const CConstruction & value) const
				{
					if ( (*this) == (value) )
					{ return false;	}
					
					return true;
				};

				//�������� ������������
				CConstruction & operator=(const CConstruction & value)
				{
					SS_TRY
					{
						/*	������� �� ��� ����	*/
						clear();
						/*	������ ��, ��� ������	*/
						TListOfConstructionObject::const_iterator iter;
							
						for(iter = value.m_Objects.begin(); iter != value.m_Objects.end(); iter++)
						{ push_back(*(*iter)); }
					}
					SS_CATCH(L"")

					return *this;
				};
				
			protected:
				//������ �������� �����������
				TListOfConstructionObject m_Objects;				
			};

			///����� ����������� �����������
			class CConstructionEx : public CConstruction
			{				
			public:
				CConstructionEx() : m_lID(0) {}

				CConstructionEx(const CConstructionEx & oConstructionEx) 
					: 
					m_lID(oConstructionEx.m_lID), 
					m_wsName(oConstructionEx.m_wsName),
					CConstruction((CConstruction)oConstructionEx) {}

				virtual~ CConstructionEx() {}
			
			public:
				unsigned long GetID()
				{
					return m_lID;
				}
				void SetID(unsigned long lID)
				{
					m_lID = lID;
				}
				std::wstring GetName() const
				{
					return m_wsName;
				}
				void SetName(const std::wstring & wsName)
				{
					m_wsName = wsName;
				}
			
			public:	
				//�������� ==
				bool operator==(const CConstructionEx & value) const
				{
					SS_TRY
					{
						if (CConstruction::operator!=((CConstruction)value))
						{ return false; }

						if (m_lID != value.m_lID)
						{ return false; }

						if (m_wsName != value.m_wsName)
						{ return false; }

						if ( !m_ConstructionFeature.Equal( &(value.m_ConstructionFeature) ) )
						{ return false; }
					}
					SS_CATCH(L"")

					return true;
				};

				//�������� !=
				bool operator != (const CConstructionEx& value)
				{
					if ( (*this) == (value) )
					{ return false;	}

					return true;
				};	

				CConstructionEx & operator=(const CConstructionEx & value)
				{
					SS_TRY
					{
						CConstruction::operator=((CConstruction)value);
						
						m_lID = value.m_lID;
						m_wsName = value.m_wsName;
						
						m_ConstructionFeature = value.m_ConstructionFeature;
					}						
					SS_CATCH(L"")
					
					return *this;
				};

			protected:
				//����� �����������
				unsigned long m_lID;
				//�������� �����������
				std::wstring m_wsName;
				//��� �����������
				SS::Core::Features::CConstructionFeature m_ConstructionFeature;
			};
		
		}
	}
}
