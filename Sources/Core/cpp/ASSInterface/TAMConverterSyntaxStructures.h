/// TAMConverterSyntaxStructures.h

#pragma once


namespace SS
{
	namespace Syntax
	{
		namespace DataTypes
		{



			/*	��� ���������� �������	*/
			struct S_bf_ui_TypeOfEndingObjectForVerb {
				unsigned int					
					Object			: 1,		/*	���������������	*/
					Relatives		: 1,		/*	������������� ����������� � ������� + !!!!(whether � if)	*/
					Adv				: 1,		/*	�������	*/				
					Preposition		: 1,		/*	��������	*/
					Inf				: 1,		/*	��������� ��� to	*/
					ToInf			: 1,		/*	��������� � to	*/
					Ing				: 1,		/*	��������� ���������� �������	*/
					That			: 1,		/*	���� That, �������� �������� �����������	*/
					Adjective		: 1,		/*	��������������	*/ 
					PastPart		: 1,		/*	��������� ���������� �������	*/ 

					/* ����� ���� ��� �������� ���������� */
					CaseDat			: 1,		/*		*/ 
					CaseGen			: 1,		/*		*/ 
					CaseInstr		: 1,		/*		*/ 

					Relatives1		: 1,		/*		*/ 
					Relatives2		: 1,		/*		*/ 
					Relatives3		: 1,		/*		*/ 
					Relatives4		: 1,		/*		*/ 
					Relatives5		: 1,		/*		*/ 
					Relatives6		: 1,		/*		*/ 
					Relatives7		: 1,		/*		*/ 
					Relatives8		: 1,		/*		*/ 
					Relatives9		: 1,		/*		*/ 
					Relatives10		: 1,		/*		*/ 

					/*	������ ����	*/
					EmptyBits		: 9;

					S_bf_ui_TypeOfEndingObjectForVerb() : Object(0), Relatives(0), Adv(0), 
																	  Preposition(0), Inf(0), ToInf(0),
																	  Ing(0), That(0),
																	  Adjective(0), PastPart(0),
																	  CaseDat(0), CaseGen(0), CaseInstr(0),
																	  Relatives1(0), Relatives2(0), Relatives3(0), Relatives4(0), Relatives5(0),
																	  Relatives6(0), Relatives7(0), Relatives8(0), Relatives9(0), Relatives10(0),
																	  EmptyBits(0)
					{}

					void SetObject()				{Object = 1;	}
					int  GetObject()				{return Object; }
					void SetRelatives()			{Relatives = 1;}
					int  GetRelatives()			{return Relatives;}
					void SetAdv()					{Adv = 1;}
					int  GetAdv()					{return Adv;}
					void SetPreposition()		{Preposition = 1;}
					int  GetPreposition()		{return Preposition;}
					void SetInf()					{Inf = 1;}
					int  GetInf()					{return Inf;}
					void SetToInf()				{ToInf = 1; }
					int  GetToInf()				{return ToInf;}
					void SetIng()					{Ing = 1;}
					int  GetIng()					{return Ing;}
					void SetThat()					{That = 1;}
					int  GetThat()					{return That;}
					void SetAdjective()			{Adjective = 1;}		
					int  GetAdjective()			{return Adjective;}	
					void SetPastPart()			{PastPart = 1;}		 
					int  GetPastPart()			{return PastPart;}	 

					/* ����� ���� ��� �������� ���������� */
					void SetCaseDat()				{CaseDat = 1;}
					int  GetCaseDat()				{return CaseDat;}
					void SetCaseGen()				{CaseGen = 1;}
					int  GetCaseGen()				{return CaseGen;}

					void SetRelatives1()			{Relatives1 = 1;}
					int  GetRelatives1()			{return Relatives1;}
					void SetRelatives2()			{Relatives2 = 1;}
					int  GetRelatives2()			{return Relatives2;}
					void SetRelatives3()			{Relatives3 = 1;}
					int  GetRelatives3()			{return Relatives3;}
					void SetRelatives4()			{Relatives4 = 1;}
					int  GetRelatives4()			{return Relatives4;}
					void SetRelatives5()			{Relatives5 = 1;}
					int  GetRelatives5()			{return Relatives5;}
					void SetRelatives6()			{Relatives6 = 1;}
					int  GetRelatives6()			{return Relatives6;}
					void SetRelatives7()			{Relatives7 = 1;}
					int  GetRelatives7()			{return Relatives7;}
					void SetRelatives8()			{Relatives8 = 1;}
					int  GetRelatives8()			{return Relatives8;}
					void SetRelatives9()			{Relatives9 = 1;}
					int  GetRelatives9()			{return Relatives9;}
					void SetRelatives10()		{Relatives10 = 1;}
					int  GetRelatives10()		{return Relatives10;}

					S_bf_ui_TypeOfEndingObjectForVerb& operator= (const S_bf_ui_TypeOfEndingObjectForVerb& value)
					{
						Object		= value.Object;
						Relatives	= value.Relatives;
						Adv			= value.Adv;
						Preposition	= value.Preposition;
						Inf			= value.Inf;
						ToInf		= value.ToInf;
						Ing			= value.Ing;
						That		= value.That;						
						Adjective	= value.Adjective;
						PastPart	= value.PastPart;

						/* ����� ���� ��� �������� ���������� */
						CaseDat		= value.CaseDat;
						CaseGen		= value.CaseGen;
						CaseInstr	= value.CaseInstr;
										 
						Relatives1	= value.Relatives1;
						Relatives2	= value.Relatives2;
						Relatives3	= value.Relatives3;
						Relatives4	= value.Relatives4;
						Relatives5	= value.Relatives5;
						Relatives6	= value.Relatives6;
						Relatives7	= value.Relatives7;
						Relatives8	= value.Relatives8;
						Relatives9	= value.Relatives9;
						Relatives10	= value.Relatives10;

						return *this;
					};
					
				};		

			/*	������� ���������, ������� ������ ����������� �������������� ��������������	*/
			struct  S_bf_ui_SyntaxInfoVerb{
					 unsigned int
					ConstructionType		: 5,
					Object					: 1,
					Relatives				: 1,
					Adv						: 1,
					Preposition				: 1,
					Inf						: 1,
					ToInf					: 1,
					Ing						: 1,
					That					: 1,
					Adjective				: 1,  
					PastPart				: 1,  

					/* ����� ���� ��� �������� ���������� */
					CaseDat					: 1,		/*		*/ 
					CaseGen					: 1,		/*		*/ 
					CaseInstr				: 1,		/*		*/ 

					Relatives1				: 1,		/*		*/ 
					Relatives2				: 1,		/*		*/ 
					Relatives3				: 1,		/*		*/ 
					Relatives4				: 1,		/*		*/ 
					Relatives5				: 1,		/*		*/ 
					Relatives6				: 1,		/*		*/ 
					Relatives7				: 1,		/*		*/ 
					Relatives8				: 1,		/*		*/ 
					Relatives9				: 1,		/*		*/ 
					Relatives10				: 1,		/*		*/ 

					/*	������ ����	*/
					EmptyBits				: 4; 

					S_bf_ui_SyntaxInfoVerb() 
						: ConstructionType(0),
						Object(0), Relatives(0), Adv(0),
						Preposition(0), Inf(0), ToInf(0),
						Ing(0), That(0),
						Adjective(0), PastPart(0),
						CaseDat(0), CaseGen(0), CaseInstr(0),
						Relatives1(0), Relatives2(0), Relatives3(0), Relatives4(0), Relatives5(0),
						Relatives6(0), Relatives7(0), Relatives8(0), Relatives9(0), Relatives10(0),
						EmptyBits(0)
					{}

					S_bf_ui_SyntaxInfoVerb& operator= (const unsigned int value)
					{
						memcpy(this, &value, 4);
						return *this;
					};
				};


			/*	������� ���������, ������� ������ ����� �����������  �������������,
			��� �������� ������ ����� ������� �� ����� ��������������� ������� � ����� ����� � �����������*/
			struct  S_bf_i_SyntaxRelationInfo{
					 int
					ObjectsCount			: 4,	// ����� ��������� �������� ������ ����
					ObjectsOrder			: 1,	// ������� ��������
					PositionToHead			: 1,	// ��������� �� ��������� � ������
					Probability				: 7,	// ���� �����
					ConnectionsObligation	: 1,	// �������������� �����
					
					/*	������ ����	*/
					EmptyBits				: 18; 
				};

		};
	};
};