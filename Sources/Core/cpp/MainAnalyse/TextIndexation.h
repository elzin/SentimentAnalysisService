#pragma once

#include "../ASSInterface/ITextBlockEx.h"
#include "./LinguisticWorkingInterfaces.h"
//#include "./LinguisticIndexation.h"

namespace SS
{
namespace LinguisticProcessor
{
namespace Indexation
{

class CTextIndexation : virtual public SS::LinguisticProcessor::CLinguisticWorkingInterfaces

{
public:
	CTextIndexation(void);
	~CTextIndexation(void);
public:
	/// ���������� ������� ���������� ���������� ���������� ����� ���������� ������ 
	void Init(
		/// ��������� � ������������� �������
		SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText
		/// ��������� ���������� ������
		, SS::Core::Types::IndexationSearch::TIndexationParams* pIndexationParams
		/// ��������� ������� ������� ������
		, unsigned int uiFistCharPosition 
		);

	unsigned int GenerateNext(unsigned int& uiFistCharPosition, unsigned int& uiPosition, SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult);

	void Clear();
private:
	void Init();

};


}
}
}