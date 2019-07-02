#pragma once

#include <vector>
#include <set>
using namespace std;

#include "..\ASCInterface\services.h"
using namespace SS::Core::CommonServices;

#include "..\ASCInterface\IInterface.h"
using namespace SS::Interface::Core::ResourceManagers;

#include "..\ASSInterface\IRev.h"
using namespace SS::Interface::Core::Rev;

#include "..\ASSInterface\IAMConverter.h"
#include "..\ASSInterface\IBlackBox.h"

using namespace SS::Interface::Core::BlackBox;
using namespace SS::Interface::Core::BlackBox::Query;
using namespace SS::Interface::Core::MainAnalyse;
using namespace SS::Interface::Core;
using namespace SS::Core::Types;
using namespace SS::Core;

#include "..\ASSInterface\ICoSeDi.h"
using namespace SS::Interface::Core::CoSeDi;

#include "..\ASSInterface\TCoSeDiDataTypes.h"
using namespace SS::CoSeDi::DataTypes;

#include "WeightTable.h"
#include "TypeChecker.h"


namespace SS
{
namespace TransformGenerator
{

class CTransformModule : public IRelevanceEvaluation
{
public:
	CTransformModule();

public:
	HRESULT QueryInterface(REFIID refIID, void** pBase);
	ULONG Release();
	
	virtual void SetLoadManager(ILoadManager* pLoadManager);
	virtual void SetAnalyseParams(IAnalyseParams* pParams);

public:
	HRESULT EvaluateQuery(IText* pText, IQuery* pQuery);

private:
	/// ������ ������������� ��� ����������� � ����������� �� �����
	/**
		\param pSentence - ����������� ������� ����� ����������������
		\param pQuery [out] - ���������
		\param Lang - ���� �������
	*/
	bool DoTransform(ISentence* pSentence, IQuery* pQuery);
	/// ��������� ��������� ���������� �������������� ���������
	static void InitAcceptibleCategoriesList();
	/// �����������, �������� �� ������ �������� ���� "Who is?"
	bool IsWhoIsQuestion(ISentence* pSent);
	bool IsNameDefinition(ISentence* pSent);

	/// ��������� ������� �������������� ��������� ����� � ���������
	bool IsUnitInSet(set<unsigned int>* pst, IUnit* pUnit);

private:
	/// ������ ������������� ��� ����������� �����
	static int s_Trans_Eng1[];
	static int s_Trans_Eng2[];
	/// ������ ������������� ��� �������� �����
	static int s_Trans_Rus[];
	static int s_Trans_Undefined[];

	/// ��������� ���������� �������� �������������� ���������
	static set<unsigned int> s_sSC;
	/// �������������� ���������, �� ������� ������������ ������ ���� "Who is?"
	static set<unsigned int> s_sWhoIsSC;

	/// ������� ������� ���� �����
	SS::Interface::Core::BlackBox::IBlackBoxQueryStorage* m_pBlackBoxQueryStorage;
	SS::Interface::Core::BlackBox::IBlackBoxTextStorage* m_pBlackBoxTextStorage;

	ISemanticAnalysis* m_pSemanticAnalysis;
	ICombinatory* m_pCombinatory;

	CWeightTable m_oWeightTable;
	CTypeChecker m_oTypeChecker;

	bool m_bLite;
};

}
}
