#pragma once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{

//--------------------------------------------------------------------//

///������ ������� ��� �������� ��������
template <class TFactory>
class CFactoryClient
{
public:
	CFactoryClient(TFactory* pFactory):m_pFactory(pFactory){};

	///���������� ������� 
	TFactory* GetFactory(void){return m_pFactory;};

private:
	///����������� ������� �������
	TFactory* m_pFactory;
};

//--------------------------------------------------------------------//

}
}
}
}