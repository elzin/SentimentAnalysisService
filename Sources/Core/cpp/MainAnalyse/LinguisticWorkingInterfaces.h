#pragma once

#include "../ASSInterface/ILexicaLib.h"
#include "../ASSInterface/ISemanticAnalyze.h"
#include "../ASSInterface/ISyntaxAnalyzer.h"
#include "../ASSInterface/IRev.h"
#include "../ASSInterface/IDictionaryManager.h"
#include "../ASSInterface/ICoSeDi.h"
#include "../ASSInterface/IQueryDeformer.h"

namespace SS
{
namespace LinguisticProcessor
{

class CLinguisticWorkingInterfaces
	: public SS::Core::CommonServices::CBaseCoreClass
    , public SS::Interface::Core::Common::CAnalyseParams
{
protected: // AnalyseInterface
	SS::Interface::Core::CoSeDi::ICoSeDiManager*					m_pCoSeDiManager;
	/// ������ ���������������� �������
	SS::Interface::Core::Dictionary::IDictionary*				m_pDictionary;
	/// ����������� ������
	SS::Interface::Core::LexicalAnalyze::ILexica*				m_pLexica;
	/// �������������� ������
	SS::Interface::Core::ISyntaxAnalyzer*						m_pSyntaxAnalyzer;
	/// ������������� ������
	SS::Interface::Core::ISemanticAnalyze*						m_pSemanticAnalyze;
	/// ������ ������ �������������
	SS::Interface::Core::Rev::IRelevanceEvaluation*				m_pRelevanceEvaluation;
	/// ������ �������������� �������� (��� ������������������ �������� ����: ������ ���� ��������. ��� �� �������?)
	SS::Interface::QueryDeformer::IQueryDeformer*				m_pQueryDeformer;
protected: // TextStorages
	// IText
	SS::Interface::Core::BlackBox::IBlackBoxTextStorage*			m_pBlackBoxTextStorage;
	SS::Interface::Core::BlackBox::IText*						m_pText;
	SS::Interface::Core::BlackBox::IText*						m_pTextFeatureText;
	// IQuery
	SS::Interface::Core::BlackBox::Query::IQuery*				m_pQuery;
	SS::Interface::Core::BlackBox::IBlackBoxQueryStorage*		m_pBlackBoxQueryStorage;
	SS::Interface::Core::Rev::ILinguisticRelevance*				m_pLinguisticRelevance;
protected: // params
	SS::Core::Types::IndexationSearch::TLinguisticProcessorMode m_oMode;		
public:
	CLinguisticWorkingInterfaces(void);
	~CLinguisticWorkingInterfaces(void);
public:
	void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
public:
	void SetMode(SS::Core::Types::IndexationSearch::TLinguisticProcessorMode* pMode)
	{
		m_oMode.GetAnalyseDepthParams()->SetIsMorpho	(pMode->GetAnalyseDepthParams()->IsMorpho());
		m_oMode.GetAnalyseDepthParams()->SetIsSemantic	(pMode->GetAnalyseDepthParams()->IsSemantic());
		m_oMode.GetAnalyseDepthParams()->SetIsSyntax	(pMode->GetAnalyseDepthParams()->IsSyntax());
		m_oMode.GetAnalyseDepthParams()->SetIsSynonims	(pMode->GetAnalyseDepthParams()->IsSynonims());
	}
};

}
}
