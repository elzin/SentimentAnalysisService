//DynamicVersionGenerator.h

#pragma once
#include "BlockVersion.h"
#include "BoardElement.h"

namespace SS
{
namespace Syntax
{
namespace BoardElements
{

	///����� ��� ��������� ������������ �������
	class CDynamicVersionGenerator
	{
		///���� (������� � ������� ����������)
		struct SNode
		{
			///����
			CBoardElement* pElem;
			///������� ����������
			PMORPHO pMorpho;
			///�����������
			SNode() : pElem(NULL), pMorpho(NULL) {};
		};

	private:
		///��������� ��� ������������� ����������
		BoardCollection m_NullCollection;
		bool isNull;
		///������ ������� �����
		BoardElementsIterator m_itF;
		///����������� ������� �����
		BoardElementsIterator m_itL;
		///�������� ��� ������������� ���������
		CBlockVersion* m_pVersion;
		///��������� �����
		std::vector<SNode> m_NodeCollection;
		///�������� ���������
		typedef std::vector<SNode>::iterator IteratorNC;
		typedef std::vector<SNode>::const_iterator ConstIteratorNC;

	private:
		///�������� ����������� �� AgreementType
		bool IsIntersectByAT( SS::Core::Features::CMorphoFeature & oMorphoOne,
							  SS::Core::Features::CMorphoFeature & oMorphoTwo,
							  SS::Core::Features::Types::AgreementType & oAt ) const;
		///�������� ��������
		void WriteVersion() const;
		///����� ���������� ��������
		bool FindNormalVersion();
		///������������� ��������� ��������
		bool GenerateVersion();
		///��������� �������� �� ���������� �� ��
		bool CheckVersion() const;

	public:
		///�����������
		CDynamicVersionGenerator() : m_pVersion(NULL)
		{
			//m_itF = m_NullCollection.end();
			//m_itL = m_NullCollection.end();
			isNull = true;
		}
		///���������� ��������
		void SetBlockRange(BoardElementsIterator itF, BoardElementsIterator itL);
		///���������� �������� 
		void SetVersion(CBlockVersion* pV) { m_pVersion = pV; };
		///�������� ������ ��������
		bool GetFirstVersion();
		///�������� ��������� ��������
		bool GetNextVersion();
	};

}
}
}