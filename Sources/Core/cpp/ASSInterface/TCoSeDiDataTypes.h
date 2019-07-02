#pragma once


#include <map>
#include <set>
#include <unordered_set>
#include <list>
#include <string>

#include <iterator>
#include <algorithm>
#include <functional>

namespace SS
{
	namespace CoSeDi
	{
		namespace DataTypes
		{			

			/*! \enum EWorkRegion
			*  \brief     ������� ������
			*/
			enum EWorkRegion
			{
				/// ���������
				wrSemantic		= 1,
				/// �������������
				wrCombinatory	= 2,
				/// ���������
				wrSyntax			= 3
			} ;			

			/*! \struct S_bf_ui_WorkRegions
			*  \brief     ���������� �����, ��� ��������� ������ ������
			*/
			struct  S_bf_ui_WorkRegions{
				unsigned short
					m_wrSemantic		:1,
					m_wrCombinatory		:1,
					m_wrSyntax			:1,
					EmptyBits			:13;	//������ ����

					S_bf_ui_WorkRegions() : m_wrSemantic(0), m_wrCombinatory(0), m_wrSyntax(0), EmptyBits(0)
					{
					}
					bool IsSyntax()
					{
						return (m_wrSyntax == 1 ) ? true : false;
					}
					bool IsSemantic()
					{
						return (m_wrSemantic == 1 ) ? true : false;
					}
					bool IsCombinatory()
					{
						return (m_wrCombinatory == 1 ) ? true : false;
					}
					void SetSyntax()
					{	
						m_wrSyntax = 1;
					}
					void SetSemantic()
					{	
						m_wrSemantic = 1;
					}
					void SetCombinatory()
					{					
						m_wrCombinatory = 1;
					}
					void UnSetSyntax()
					{	
						m_wrSyntax = 0;
					}
					void UnSetSemantic()
					{	
						m_wrSemantic = 0;
					}
					void UnSetCombinatory()
					{					
						m_wrCombinatory = 0;
					}
					
					S_bf_ui_WorkRegions& operator= (const unsigned short value)
					{
						memcpy(this, &value, 2);
						return *this;
					}
				};


			/*! \struct SExistence
			*  \brief     ������� ������������� ������ � ���
			*/
			struct SExistence
			{
				INT32	IDSource;
				INT32	IDExistence;
			};

			/*! \struct SCombinatoryAccess
			*  \brief    ��������� ��� ������ � ����� ������� Combinatory
			*/
			struct SCombinatoryAccess
			{
				INT32	ID;
				INT32	IDType;
				INT32	IDForm; // CHAR
				INT32	DictionaryNumber; // CHAR
				INT32	IDSource;
				INT32	Level;
				INT32	CombiType;	
				bool operator < (const SCombinatoryAccess& value) const
				{
					return (Level	< value.Level)?true:
						false;
				}
			};

			/*! \struct SSemanticIDSourceTree
			*  \brief     ��������� ��� ������� � ������� SemanticIDSourceTree
			*/
			struct SSemanticIDSourceTree
			{
				INT32	DictionaryNumberParent;
				INT32	IDSourceParent;
				INT32	DictionaryNumberChild;
				INT32	IDSourceChild;								
			};

			/*! \struct SSemanticsAccess
			*  \brief     ��������� ��� ������� � ������� Semantics
			*/
			struct SSemanticsAccess
			{
				INT32	IDSource;
				INT32	DictionaryNumber;
				INT32	IDClass;				
			};		

			/*! \struct SCombiSynonymsAccess
			*  \brief     ��������� ��� ������� � ������� CombiSynonyms
			*/
			struct SCombiSynonymsAccess
			{
				UINT32	IDSource;
				UINT32	DictionaryNumber;
				UINT32	SynonymClass;				
			};


			/*! \struct SSemanticsClassesTreeAccess
			*  \brief     ��������� ��� ������� � ������� SemanticsClassesTree
			*/
			struct SSemanticsClassesTreeAccess
			{
				INT32	IDClass;
				INT32	IDParent;
				std::wstring	Name;
			};
			/*! \struct SSemanticsAccess
			*  \brief     ��������� ��� ������� � ������� Semantics
			*/
			struct SSyntaxAccess
			{
				CHAR	DictionaryNumber;	
				INT32	IDSource;
				INT32	SyntaxInfo;
			};
			
			struct  TIDSource{
				int
					ushIDRoot		:24,	// ������ ������
					uchIDSuffics	:8;		// ������ ��������

					TIDSource() : ushIDRoot(0), uchIDSuffics(0)
					{
					}
					bool operator == (const TIDSource& value) const
					{
						return ((ushIDRoot== value.ushIDRoot)&&
							(uchIDSuffics	== value.uchIDSuffics))
							?true:
						false;
					}
					TIDSource& operator= (const TIDSource& value)
					{
						ushIDRoot		= value.ushIDRoot;
						uchIDSuffics	= value.uchIDSuffics;
						return *this;
					}
					
					TIDSource& operator= (const int& value)
					{
						memcpy(this, &value, 4);
						return *this;
					}
				};


			struct  SFullIDSource
			{
				SFullIDSource() : m_uchDictionaryNumber(0)
				{}
				SFullIDSource& operator= (const SFullIDSource& value)
				{
					m_ouiIDSource = value.m_ouiIDSource;
					m_uchDictionaryNumber = value.m_uchDictionaryNumber;
					
					return *this;
				}

				bool operator == (const SFullIDSource & value) const	
				{
					return ((m_ouiIDSource	==	value.m_ouiIDSource)&&
							(m_uchDictionaryNumber		==	value.m_uchDictionaryNumber)
							) ? true : false;
				}


				TIDSource		m_ouiIDSource;
				unsigned char	m_uchDictionaryNumber;
				
			};

			struct TFormInfo  {
				TIDSource m_stIDSource;
				unsigned char m_uchDictionaryNumber;
				short       m_shIDForm;
				TFormInfo() : m_shIDForm(0), m_uchDictionaryNumber(0)
				{}
				bool operator == (const TFormInfo & value) const	
				{
					return ((m_stIDSource	==	value.m_stIDSource)&&
						     (m_shIDForm		==	value.m_shIDForm))? true : false;
				}

				bool operator == (const TIDSource & value) const	
				{
					return (m_stIDSource	==	value)? true : false;
				}

				TFormInfo & operator= (const TFormInfo & value)	{
					m_stIDSource = value.m_stIDSource;
					m_shIDForm	 = value.m_shIDForm;
					return (*this);
				}
			};

			//typedef SFormInfo TFormInfo;
			
			typedef std::list<TFormInfo> T_list_FormInfo;

			typedef unsigned int	TSyntaxInfo;	
			typedef long			TSemanticType;

			/* ���� ���������� */
			enum ECombiType   {
				ctNewLexicalUnit		=  0,
				ctVerbWithParticle		= -1,
				ctVerbOrAdjWithPrep		= -2,
				ctVerbWithPrepPart		= -3,
				ctPhrasalVerbWithPrep	= -4,
				ctNounWithPrep			= -5,
				ctComplexWord			= -6

			};


			// ------------------------------------------------------------------
			// ������������� (ICombinatory) 
			// ------------------------------------------------------------------

			/// ����. ����� ������ ���������� 
			#define MAX_NUM_OF_COMBINATION_MEMBERS   5  

			/// ���������� � ����� ����������
			struct SWordIndex 
			{
				UINT32 IDSource; // ����� ������� � IDSource
				INT32  IDForm;   // IDForm 
			};

			/// ���������� � ���������� 
			struct SCombinationNewInfo 
			{
				UINT32     ID;            // ID ����������
				UINT32     HashKey;       // HASH-���� ����������
				UINT32     HashKey_2;     // HASH-���� ���������� � ������ 2
				 INT32     CombiType;     // CombiType ����������
				UINT32     IDType;        // IDType ����������

				UINT32     NumOfMembers; // ����� ������ ���������� 
				UINT32     PosInClause;  // ������� (� ����) � �������� �����������/�����_����������� 
				UINT32     PosOccupied;  // ����� �������/����/������, ������� ��������� � ���������� (������� ������)
				SWordIndex WordIndexes[MAX_NUM_OF_COMBINATION_MEMBERS]; // ���������� � ������ ����������

				UINT32     uiMorphoInfo;   //
				UINT32     uiPartOfSpeech; //
			};

			/// ���������� � ���������� ( ��� �������� ����� ���������� � DBMS-�������. ��. <CreateCombination()> ) 
			struct SCombinationNewInfoForAdd 
			{
				UINT32     ID;           // ID ���������� (�� �����������. ������������ � ������ <CreateCombination()>)
				 INT32     CombiType;    // CombiType ����������
				UINT32     IDType;       // IDType ����������

				UINT32     NumOfMembers; // ����� ������ ���������� 
				SWordIndex WordIndexes[MAX_NUM_OF_COMBINATION_MEMBERS]; // ���������� � ������ ����������

			};


			// ------------------------------------------------------------------


			struct SCombinationInfo
			{
				short				shIDType;
				ECombiType			eCombiType;
				T_list_FormInfo	m_T_list_FormInfo;

				SCombinationInfo() : shIDType(0), eCombiType(ctNewLexicalUnit)
				{}
				
				bool operator == (const SCombinationInfo& value) const
				{
					return (
						(shIDType				== value.shIDType)&&
						(eCombiType				== value.eCombiType)&&
						(m_T_list_FormInfo	== value.m_T_list_FormInfo)
						)
						?true:
					false;
				}
			};

			typedef SCombinationInfo TCombinationInfo;

			typedef std::list<int> TlistOfCombination;

			struct SSourceInCombination
			{
				TIDSource				m_IDSource;
				TlistOfCombination	m_listOfCombination;
			};

		};
	};
};