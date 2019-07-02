//Semanticbitfieldsstructures.h

#define FirstLevelSemanticType_BIT_SIZE 	4
#define SecondLevelSemanticType_BIT_SIZE 	5
#define ThirdLevelSemanticType_BIT_SIZE 	4
#define FourthLevelSemanticType_BIT_SIZE 	4
#define FifthLevelSemanticType_BIT_SIZE 	3
#define SixthLevelSemanticType_BIT_SIZE 	4


namespace SS
{
namespace Core
{
namespace Features
{
namespace bitfieldsstructures
{
/*! \struct SbfSemanticType
*  \brief     �������� ���� ��� ���������� ������� ������������� ��������
*/
struct  SbfSemanticType
{
	unsigned int
		m_STLevelFirts		:FirstLevelSemanticType_BIT_SIZE,	// 1-� �������
		m_STLevelSecond		:SecondLevelSemanticType_BIT_SIZE,	// 2-� �������
		m_STLevelThird		:ThirdLevelSemanticType_BIT_SIZE,	// 3-� �������
		m_STLevelFourth		:FourthLevelSemanticType_BIT_SIZE,	// 4-� �������
		m_STLevelFifth		:FifthLevelSemanticType_BIT_SIZE,	// 5-� �������
		m_STLevelSixth		:SixthLevelSemanticType_BIT_SIZE,	// 6-� �������
		m_Empty				:8;
		
	SbfSemanticType() 
		: m_STLevelFirts(0)
		, m_STLevelSecond(0)
		, m_STLevelThird(0)
		, m_STLevelFourth(0)
		, m_STLevelFifth(0)
		, m_STLevelSixth(0)
		, m_Empty(0)
	{}
	SbfSemanticType& operator = (const int value)
	{
		memcpy(this, &value, 4);
		return *this;
	}
	
} ;


}
}
}
}