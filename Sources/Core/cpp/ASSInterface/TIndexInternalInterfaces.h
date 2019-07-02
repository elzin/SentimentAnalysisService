//internal_interface.h 
namespace INDEX_INTERFACE
{


	//���������� � ����-��
	class IPrepared
	{
	public:
		//���������� � ���������� ����������
		virtual HRESULT Prepare()=0;

		virtual ~IPrepared() {};
	};

	//���������� ��� ��� ������ � ������
	class IReturnSBC
	{
	public:

		//�� ������� ���������� ���������� ���
		virtual HRESULT GetSBC(/*in*/ULONG ulNumLevel, /*in*/ULONG ulSourceIndex, /*in, out*/CSentenceLevel& oSentenceLevel) = 0; 

		virtual ~IReturnSBC() {};
	};

	//������ � ������� ��������
	class IWorkWithBase
	{
	public:

		//��������� (��������) ������ �� ������ � ���������� ����� ���������� �����������, � ������� ��� ������ �����������
		//(0, ���� ������ ���� ���������)
		virtual HRESULT GetDataOfSource(ULONG ulSourceIndex, ULONG ulCurrentAbsNumOfSentence, ULONG &ulLastAbsNumOfSentence) = 0;

		virtual ~IWorkWithBase() {};
	};

	//������ � ���������� ���������
	class IWorkWithIndex
	{
	public:

		//��������� ������� ������
		virtual HRESULT SetSourceIndex(ULONG ulSourceIndex) = 0;

		//��������� �������� ������
		virtual HRESULT SetNumLevel(ULONG ulNumLevel) = 0;

		//���������� ������� ������ �� �������
		virtual HRESULT IncLevel() = 0;

		//������� ���
		virtual HRESULT Insert(CSentenceLevel& oSentenceLevel, bool blIsInsert) = 0;

		virtual ~IWorkWithIndex() {};
	};

	//������ � ��������� ������������
	class IWorkWithAccordance
	{
	public:

		//������� ������
		virtual HRESULT Insert(ULONG ulAbsoluteNumSentence, ULONG ulNumText, ULONG ulNumParagraph, ULONG ulNumSentence) = 0;

		virtual ~IWorkWithAccordance() {};
	};

}
//internal_interface.h end




