
%option c++
%option noyywrap
%option nostdinit
%option prefix="Walker"

  /*������*/
%s QUOTATIONS
  /*����*/
%s DATES			
  /*�����*/
%s NAMES
  /*�����������*/
%s ORGANIZATIONS
  /*�����*/
%s PLACES
  /*�������� ������������� �������*/
%s REPARSEDITEMS
  /**/
%s LSEQUENCES
  /*������*/
%s QUERY
  /**/
%s MULTINAMES
  /*���������������������*/
%s INSEQUENCES
  /* �������� */
%s TELEPHONES

/*�����*/
Word				\x11	
/*�����*/
Number				\x12	
/*����� + ����� ����*/
Month				\x13	
/**/
LWord				\x14	
/*������� (Last Name)*/
LName         		\x15	
/*���(First Name)*/
FName         		\x16	
/*�������� (Middle Name)*/
MName         		\x17	
/*��������*/
Initial       		\x18	
/**/
Genitive      		\x19	
/*����� - ����*/
NumberDay     		\x1A	
/*����� -���*/
NumberYear    		\x1B	
/*������� ,*/
Comma         		\x1C	
/*��������*/
Apostroph			\x1D	
/**/
SmallWord			\x1E	
/*����� - ���*/
WordCentury   		\x1F	
/*����� - ���, ���������*/
WordYear      		\x20	
/*�����*/
Defis         		\x21	
/*����� - ����*/
WordDay       		\x22	
/**/
DMY           		\x23	
/**/
GenConj       		\x24	
/**/
Org           		\x25	
/**/
SpecificOrg   		\x26	
/**/
Quote				\x27	
/**/
RQuote				\x28	
/*�����*/
City          		\x29	
/*����/�����������*/
State         		\x2A	
/*������*/
Country       		\x2B	
/**/
Quotation     		\x2C	
/* ����� �����: "�" "���" "��" "���" "��" "��" "von" "di" "van" "da" "de" "d" */
NameParticle  		\x2D	
/* & */
Ampersand     		\x2E	
/*����*/
Tire          		\x2F	
/**/
ThreeDigits      		\x30	
/**/
MeasureDay			\x31	
/**/
MeasureMonth		\x32	
/*���*/
Name				\x33	
/**/
NonSyntax			\x34	
/* : */
Colon				\x35	
/* / */
Slash				\x36	
/*�����*/
Point				\x37	
/*���������� �����*/
EngWord				\x38	
/*����� S*/
LetterS				\x39	
/*����� URL*/
URLPart				\x3A	
/* @ */
At					\x3B	
/*����� �������*/
RomanNumber			\x3C	
/**/
STerminated			\x3D	
/*���������� ��������� (��, ��...)*/
OrdinalParticle 	\x3E	
/*����� T*/
LetterT         	\x3F	
/**/
Volume          	\x40	
/*������� �������*/
Quarter         	\x41	
/**/
To					\x42	
/**/
LSmallWord			\x43	
/**/
CityState			\x44	
/**/
QListWord			\x45	
/**/
QThe				\x46	
/**/
QNames				\x47	
/**/
QOf					\x48	
/**/
QWhat				\x49	
/**/
QAre				\x4A	
/*������*/
Verb				\x4B	
/*��� �����������*/
ProperWord			\x4C	
/*�������, ���������� �����*/
GeoSemantic			\x4D	
/*������� ����� �����*/
/*�/�/��/��/from/to/��/��*/
DatePreposition     \x4E	
/**/
ProperWordUnknown   \x4F	
/**/
OrgAbbr				\x50	
/**/
GeoConj				\x51	
/**/
GeoSemanticPre      \x52	
/**/
GenetiveAdj			\x53	
/**/
GenetiveNoun		\x54	
/**/
NounSeqRoot			\x55	
/**/
DativeAdj			\x56	
/**/
DativeNoun			\x57	
/**/
DativeAndGenAdj     \x58	
/**/
DativeAndGenNoun    \x59	
/**/
LQuote				\x5A
/**/
OrdinalNumber		\x5B	
/**/
YearQuarter			\x5C
/*2 �����*/
TwoDigits      		\x5D	
/*1 �����*/
OneDigit      		\x5E	
/*����� ��� - ����, �����*/
DayTime      		\x5F
/*�����������, ������ (semtitIndef)*/
WordDecade      	\x60	
/*4 �����*/
FourDigits      	\x61
/*5 ����*/
FiveDigits      	\x62
/*6 ����*/
SixDigits      		\x63
/*7 ����*/
SevenDigits      	\x64
/*8 ����*/
EightDigits      	\x65
/*9 ����*/
NineDigits      	\x66
/*10 ����*/
TenDigits      		\x67
/*11 ����*/
ElevenDigits		\x68
/*����� ������*/	
LeftBracket			\x69
/*������ ������*/
RightBracket		\x6A
/*����� - ����� ��������,�������, ����*/
TelephoneWord		\x6B
/*URL*/
URL					\x6C
/*���� "+"*/
PlusSign			\x6D
/* ����� - ���., ��� - ���������� ���������� ����� */
TelephoneAdditionWord \x6E


NotLastName [^\x4F\x15]

NotQuote    [^\x27\x28\x5A]
NotVerbAndQuote         [^\x4B\x27\x28\x5A]

NotApostroph  [^\x1D]
NotVerbAndApostroph [^\x4B\x1D]

SumProperWord  {ProperWord}|{ProperWordUnknown}


F       ({NameParticle}{Apostroph}?({LName}|{Name}|{FName}|{MName}))|{LName}|{Name}|{MName}
I       {Name}|{FName}
O       {MName}

Day       {NumberDay}
Year      {NumberYear}
Century     {NumberDay}|{NumberYear}|{RomanNumber}

  /* 15th of September | 15 of September | 15 �������� | September 15th */
Date      ({Day}{GenConj}?{Month})|({Month}{Day})

/*�������������� �����*/
Hyfen     {Defis}|{Tire} 

LNoun     {LWord}|{Genitive}
ComplNoun   {LNoun}(({Defis}|{Ampersand}){LNoun})?
ComplSequence {ComplNoun}{0,3}

OneToTenLengthNumber	{OneDigit}|{TwoDigits}|{ThreeDigits}|{FourDigits}|{FiveDigits}|{SixDigits}|{SevenDigits}|{EightDigits}|{NineDigits}|{TenDigits}
AnyNumber   			{Number}|{NumberDay}|{NumberYear}|{OneToTenLengthNumber}
LongNumber    			({Number}|{OneToTenLengthNumber}){OneToTenLengthNumber}*

					/* OLD VERSIONS */
	/* AnyNumber   			{Number}|{NumberDay}|{NumberYear} */
	/* LongNumber    			({Number}|{ThreeDigits}){ThreeDigits}* */


NumBreak    {Point}|{Comma}|{Apostroph}
DateBreak   {Defis}|{Point}|{Slash}
PhoneBreak   {Hyfen}

AnyEngWord    {EngWord}|{URLPart}|{LetterS}|{GenConj}|{STerminated}|{OrdinalParticle}|{LetterT}
InetPath    ({Slash}{AnyEngWord})*(({Point}{AnyEngWord})|{Slash})?
InetLocation  ({AnyEngWord}{Point})+{URLPart}
ProtoBreak    {Colon}{Slash}{2}

AnyWord     {Word}|{LWord}|{LSmallWord}
LSLWord     {LWord}|{LSmallWord}|{Initial}|{City}

RCity     {City}|{CityState}
RState      {State}|{CityState}

Decade {WordDecade}|{MeasureMonth}

TelephonePrefix			{TelephoneWord}{Point}?
CountryCode				{PlusSign}?({OneDigit}|{TwoDigits}|{ThreeDigits})
CityCode				{LeftBracket}?({OneDigit}|{TwoDigits}|{ThreeDigits}|{FourDigits}|{FiveDigits}){RightBracket}?
SevenDigitsNumber		({ThreeDigits}{PhoneBreak}?{TwoDigits}{PhoneBreak}?{TwoDigits})|({ThreeDigits}{PhoneBreak}?{FourDigits})|{SevenDigits}
 /* ({TwoDigits}{PhoneBreak}?{TwoDigits}{PhoneBreak}?{TwoDigits})| */
SixDigitsNumber			{SixDigits}
FiveDigitsNumber		({OneDigit}{PhoneBreak}?{TwoDigits}{PhoneBreak}?{TwoDigits})|({ThreeDigits}{PhoneBreak}?{TwoDigits})|{FiveDigits}
TenDigitsNumber			{OneDigit}?{TenDigits}
ElevenDigitsNumber		({PlusSign}?{ElevenDigits})|({CountryCode}{PhoneBreak}?{CityCode}{PhoneBreak}?{SevenDigitsNumber})
AdditionalNumber		({Comma}?{TelephoneAdditionWord}{Point}?({ThreeDigits}|{FourDigits}))

Time					({TwoDigits}|{NumberDay}){Colon}({TwoDigits}|{NumberDay})({Colon}({TwoDigits}|NumberDay))?

%%

  /* flex provides a mechanism for conditionally activating rules. */
  /* Any rule whose pattern is prefixed with `<sc>' will only be active when the scanner is in the start condition named sc. */
  /* ������� -> <QUOTATIONS> <REPARSEDITEMS> <DATES> <MULTINAMES> <NAMES> <ORGANIZATIONS> <LSEQUENCES> <QUERY>*/

<QUOTATIONS>
{
  /* �������� ������ */
  /* ��������-����� ������� */
{Quote}({ProperWord})({NotVerbAndQuote}{0,4}){Quote}          return lpQuotation; 
{LQuote}({ProperWord})({NotVerbAndQuote}{0,4}){RQuote}          return lpQuotation;
{Apostroph}({ProperWord})({NotVerbAndApostroph}{0,4}){Apostroph}      return lpQuotation;
{Quote}{NotVerbAndQuote}{Quote}									return lpQuotationSimple;

}

<REPARSEDITEMS>
{
  /* 1223.253,144'213 */
({Number}|{ThreeDigits})({NumBreak}?{ThreeDigits})+         return lpComplexNumber;

  /* � 15:50 �� 16:00 */
{DatePreposition}{Time}{DatePreposition}{Time}				return lpTimeInterval;

  /* 22:25[:14] */ /*+*/
{Time}               										return lpTime;

  /* 22-25 */ /*+*/
({TwoDigits}|{NumberDay}){Hyfen}({TwoDigits}|{NumberDay})	return lpTime1;

  /*8/11/1989*/
  /*8-11-1989*/
  /*8.11.1989*/ /*+*/
  ({TwoDigits}|{OneDigit}){DateBreak}({TwoDigits}|{OneDigit}){DateBreak}({FourDigits}|{ThreeDigits}|{TwoDigits})          return lpDMY6;

  /*1989/11/8*/
  /*1989-11-8*/
  /*1989.11.8*/ 
  {FourDigits}{DateBreak}({TwoDigits}|{OneDigit}){DateBreak}({TwoDigits}|{OneDigit}) return lpYMD;

  					/* OLD VERSIONS */
	/* {Number}{DateBreak}{Number}{DateBreak}{Number}          return lpDMY6; - OLD VERSION*/

  /*138��*/
({AnyNumber}{Hyfen}?{OrdinalParticle})|({OrdinalNumber})          return lpOrdinalNumber;
  
  					/* OLD VERSIONS */
	/*(({Number}|{ThreeDigits}){Hyfen}?{OrdinalParticle})|({OrdinalNumber})          return lpOrdinalNumber;*/
 
  /* 12/3 , 123/321 */
{AnyNumber}{Slash}{AnyNumber}       return lpSimpleFraction;
  
    					/* OLD VERSIONS */
	/*({Number}|{ThreeDigits}){Slash}({Number}|{ThreeDigits})       return lpSimpleFraction;*/

  /* it's , what's*/
{EngWord}{Apostroph}{LetterS}                 return lpGenitiveEng;
  /* Newtons' */
{STerminated}{Apostroph}                    return lpGenitiveEng;

  /* bozhko@mail.ru */
{AnyEngWord}{At}{InetLocation}                  return lpInetLocation;

  /* http://www.cs.man.ac.uk/~pjj/cs211/flexdoc.html */
{AnyEngWord}({ProtoBreak}|{Point}){InetLocation}{InetPath}    return lpInetLocation;

  /* google.com */
{InetLocation}                          return lpInetLocation;

  /* don't , aren't */
{AnyEngWord}{Apostroph}{LetterT}                return lpNegVerb;

}

<TELEPHONES>
{
{TelephonePrefix}?(({CountryCode}{CityCode})|({CityCode}))?{SevenDigitsNumber}{AdditionalNumber}?			return lpSevenDigitsPhoneNumber;
{TelephonePrefix}?(({CountryCode}{CityCode})|({CityCode}))?{SixDigitsNumber}{AdditionalNumber}?				return lpSixDigitsPhoneNumber;
({TelephonePrefix}|({CountryCode}?{CityCode}))({TwoDigits}{PhoneBreak}?{FourDigits}){AdditionalNumber}?		return lpSixDigitsPhoneNumber;
{TelephonePrefix}?(({CountryCode}{CityCode})|({CityCode}))?{FiveDigitsNumber}{AdditionalNumber}?			return lpFiveDigitsPhoneNumber;

{TelephonePrefix}?{TenDigitsNumber}{AdditionalNumber}?														return lpTenDigitsPhoneNumber;
{TelephonePrefix}?{ElevenDigitsNumber}{AdditionalNumber}?													return lpElevenDigitsPhoneNumber;
}

<DATES>
{ 
  /*����, ����, ����, �����, �������, �������*/ 
{DayTime} 						return lpDayTime; 
    
 /* � 13 �� 15 ���� 2000 ����*/ /*+*/ 
{DatePreposition}{AnyNumber}{DatePreposition}{Date}{Comma}?{Year}{WordYear}? 	return lpDYI;
 
  /* C 15 �� 20 ��������*/
{DatePreposition}{NumberDay}{DatePreposition}{Date}   return lpDI;

  /* 15th of September | 15 of September | 15 �������� | September 15th */ /*+*/ 
{Date}        return lpDMW2;

  /* 2001-2003th years, 2001-2003-� ���� */ 
{Year}{Hyfen}{Year}{WordYear}                 return lpYear;

  /* 21th century, 21-� ���, XXth century, XX-� ��� */
{Century}{Hyfen}?{SmallWord}?{WordCentury}                      return lpCentury;


  /* 2000-��    */
{Year}{Hyfen}{OrdinalParticle}                 return lpNumericYear;

  /* 1999 September 15th; 2009 ���, 13 �������� */
{Year}{WordYear}?{Comma}?{Date}                 return lpDMY4;

  /* 2001`s years */
{Year}{Apostroph}{LetterS}{WordYear}				return lpYear1;

  /* 2001th year, 2001-� ��� */ /*+*/ 
{Year}{WordYear}                        return lpYear2;

  /* 90`s */ /*+*/
{TwoDigits}{Apostroph}?({LetterS}|{OrdinalParticle})                return lpNumericYear;

  /* I ���������, II ���������*/
({AnyNumber}|{RomanNumber}){WordYear} 						return lpYearPart1; 
 
  /* ������ ���������, 1*� ���������, ������ ���������, 2*� ���������*/
{AnyNumber}(({Apostroph})|({Hyfen}))?{OrdinalParticle}			return lpYearPart2; 

  /* 1-2 ��� */ /*+*/
{Day}{Hyfen}{Day}{Month}                    return lpDM;

  /* 1-2 of May */ /*+*/
{Day}{Hyfen}{Day}{GenConj}{Month}               return lpDM1;

  /* Mon[,] [the] 15th of November[,] 1999 [year] */ /*+*/
{WordDay}{Comma}?{SmallWord}?{Date}{Comma}?{Year}{WordYear}?  return lpDMYW;

  /* mon[,] [the] 5th of May */ /*+*/
{WordDay}{Comma}?{SmallWord}?{Date}               return lpDMW;

  /* 15th of May, Mon */ /*+*/
{Date}{Comma}{WordDay}                      return lpDMW1;

  /* ����[,] 1999 [����] */ /*+*/
{Month}{Comma}?{Year}{WordYear}?                return lpYM;

  /* 15th of November[,] 1999 [year] */
{Date}{Comma}?{Year}{WordYear}?                 return lpDMY;

  /* 15th of November[,] 1999, Mon */ /*+-*/
{Date}{Comma}?{Year}{Comma}{WordDay}              return lpDMYW1;

  /* 1999-Jan-14 */ /*+*/
{Year}{Hyfen}{Month}{Hyfen}{Day}                return lpDMY1;

  /* 1999-Jan-14, Monday */ /*+*/
{Year}{Hyfen}{Month}{Hyfen}{Day}{Comma}{WordDay}    return lpDMYW3;


  /* 18-Jul-2005 [year] */ /*+*/
{Day}{Hyfen}{Month}{Hyfen}{Year}{WordYear}?           return lpDMY2;

  /* 18-Jul-2005 [year], Monday */ /*+*/
{Day}{Hyfen}{Month}{Hyfen}{Year}{WordYear}?{Comma}{WordDay}       return lpDMYW4;


  /* 15th of November' 1999 [year] */ /*+*/
{Date}{Apostroph}{Year}{WordYear}?                return lpDMY3;
  
  /* Tue[,] the 21-10-1997 [year] */ /*+*/
{WordDay}{Comma}?{SmallWord}?{DMY}{WordYear}?         return lpDMYW2;

  /* 29.03.2005 �. */ /*+*/
{DMY}{WordYear}                         return lpDMY5;

  /* quarter to seven */
  /*{Quarter}{To}{AnyNumber}                    return lpTime1; */

  /* ������� */
{YearQuarter}							return lpMI;

  /* 1 �������, IV ������� */
({AnyNumber}|{RomanNumber}){YearQuarter}			return lpMI1;

  /* ������� 1, ������� IV*/
{YearQuarter}({AnyNumber}|{RomanNumber})			return lpMI2;

  /* 2�� �������, 2-�� �������*/
{AnyNumber}({Apostroph}|{Hyfen})?{OrdinalParticle}{YearQuarter}  return lpMI3;
 
  /* ����� */
{Month} 							return lpM;

   /* ��� */
{Year}                             return lpYear2;

  /* 1�� ������ ����, I ����������� [20] ���� */
({AnyNumber}|{RomanNumber}){Decade}({AnyNumber}|{RomanNumber})?{WordCentury}		 return lpDecade;

  /* ������ [20] ����, �������� ����*/
{WordDecade}({AnyNumber}|{RomanNumber})?{WordCentury}								return lpDecade1;

  /* 1 �����������, II �����������*/
({AnyNumber}|{RomanNumber}){WordDecade}												return lpDecade2;

  /* ��������, �������� ���, weekend */
{WordDecade}{WordDay}?																return lpWeekEnd;

}

<MULTINAMES>
{
  /* Armin van Buuren , ����� ��� ����� */
  {ProperWord}{NameParticle}{ProperWord}         return lpFI;
  
  /* ������ ���� �������� */
  {FName}{FName}{FName}                    return lpFIO;
  
  /* ������ �������� */
  {FName}{FName}                     return lpFI;
}

<NAMES>
{


  /* de Marco */
{F}                               return lpF;

  /* �������� ������������ �����, ����� �������� �. */
{F}{I}({O}|{Initial})                 return lpFIO;


  /* ������ ������� ��������, George W. Bush */
{I}({I}|{O}|{Initial}){F}                   return lpFIO;

  /* George Bush */
{I}{F}                              return lpFI;

  /* ����� �������� */
{F}{I}                              return lpFI;

  /* ����� �. �. */
({F}|{ProperWord}|{ProperWordUnknown}){Initial}{2}        return lpFIO;

  /* �. �. ����� */
{Initial}{2}({F}|{ProperWord}|{ProperWordUnknown})        return lpFIO;

  /* ����� �. */
{F}{Initial}                          return lpFI;

  /* �. ����� */
{Initial}{F}                          return lpFI;

  /*{F}{I}{ProperWordUnknown}                   return lpFIO;*/

  /*{ProperWordUnknown}{F}{I}                   return lpFIO;*/



}

<ORGANIZATIONS>
{

  /* ���� "������� ������" */
{Org}{Quotation}                        return lpOrg;

  /* HSBC Holdings */
{Quotation}{Org}                        return lpOrg;

  /* Organization of United Nations */
{ComplSequence}{Org}{GenConj}{SmallWord}?{LWord}{1,3}     return lpOrg;

  /* ����������� ������������ ����� */
{ComplSequence}{Org}{Genitive}{1,3}               return lpOrg;

  /* World Trade Organization, �������� ����-���� */
{ComplSequence}{Org}{ComplSequence}               return lpOrg;

  /* Hangzhou MSD Pharmaceutical Co. */
{SpecificOrg}{Org}                        return lpOrg;

  /* �������� Hangzhou MSD Pharmaceutical */
{Org}{SpecificOrg}                        return lpOrg;

  /* */
{ProperWord}{OrgAbbr}{1,3}                    return lpOrg;

  /* ��� */
{OrgAbbr}{2,3}                          return lpOrg;


{OrgAbbr}{1,2}{GeoSemantic}                   return lpOrg;

}

<PLACES>
{

  /* Moscow, Russia */
{RCity}{Comma}{Country}                     return lpCityCountry;

  /* Dallas, Texas */
{RCity}{Comma}{RState}                      return lpCityState;

  /* Texas, USA */
{RState}{Comma}{Country}                    return lpStateCountry;

  /* ���������� ����� ���������*/
{GeoSemantic}{ProperWordUnknown}                return lpGeoSemantic;

  /* ���������� �������, ��������� ���������� �����,  */
{ProperWordUnknown}({GeoSemantic}{1,2})                 return lpGeoSemantic; 

({ProperWordUnknown}{Comma}){0,4}{ProperWordUnknown}({GeoConj}{ProperWordUnknown})?({GeoSemantic}{1,2})   return lpGeoSemantic; 

  /* ���� ��������, ������� ������ � ��������� */
{GeoSemanticPre}{ProperWord}({GeoConj}({ProperWord})){0,1} return lpGeoSemantic;  

{GeoSemanticPre}{ProperWordUnknown}({GeoConj}({ProperWordUnknown})){0,1} return lpGeoSemantic;  
}


<LSEQUENCES>
{

  /* R&B */
{LWord}{1,4}{Ampersand}{LWord}{1,3}               return lpSimpleSequence;

  /* any sequence of LWords */
{LSLWord}{2,}                         return lpLSequence;

{LSLWord}{1,2}{GeoSemantic}                   return lpLSequence;

{LSLWord}{GeoSemantic}{LSLWord}                 return lpLSequence;

  /* float numbers should be joined after dates */
{LongNumber}({Point}|{Comma}){LongNumber}           return lpFloat;
}

<INSEQUENCES>
{
   /*{NounSeqRoot}{GenetiveNoun} return lpNounSequence;*/
  
    /*{NounSeqRoot}({GenetiveAdj}?{GenetiveNoun}{Comma}){1,3} return lpNounSequence;*/
 
  /*{NounSeqRoot}({GenetiveAdj}?{GenetiveNoun}{Comma}){1,3}({GenetiveAdj}?{GenetiveNoun})({GenConj}({GenetiveAdj}?{GenetiveNoun}))? return lpNounSequence;*/
   
  /*{NounSeqRoot}{GenetiveAdj}?{GenetiveNoun}{GenConj}{GenetiveAdj}?{GenetiveNoun}  return lpNounSequence;*/
   
  /*{NounSeqRoot}({DativeAdj}?{DativeNoun}{Comma}){1,3}({DativeAdj}?{DativeNoun})({GenConj}({DativeAdj}?{DativeNoun}))? return lpNounSequence;*/
   
  /*{NounSeqRoot}{DativeAdj}?{DativeNoun}{GenConj}{DativeAdj}?{DativeNoun}  return lpNounSequence;*/

 /*{NounSeqRoot}{1,2}({DativeAndGenAdj}?{DativeAndGenNoun}{Comma}){1,3}({DativeAndGenAdj}?{DativeAndGenNoun})({GenConj}({DativeAndGenAdj}?{DativeAndGenNoun}))? return lpNounSequence;*/
   
 /*{NounSeqRoot}{DativeAndGenAdj}?{DativeAndGenNoun}{GenConj}{DativeAndGenAdj}?{DativeAndGenNoun} return lpNounSequence;*/


}

<QUERY>
{

  /* List the names of... */
{QListWord}{QThe}?{QNames}{QOf}                 return lpList;

  /* What are the names of... */
{QWhat}{QAre}{QThe}?{QNames}{QOf}               return lpList;

  /* List/Name... */
{QListWord}                           return lpList;

}

.                               return lpWord;


%%
