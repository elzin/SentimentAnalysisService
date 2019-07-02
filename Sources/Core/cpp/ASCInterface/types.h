#pragma once

///������������, ������������ ��������� ������ �������	(����������� ��������� ����������)
typedef enum TCoreLibrary{
	///�������
	dllDictionary,
	///��������� ���������
	dllSynonims,
	///����������� ����������
	dllLexicaLib,
	///���������� � �����
	dllNdx,
	///��������� �������������
	dllAMConverter,
	///���
	dllCoSeDi,
	///�������������� ����������
	dllSyntaxConstructions,
	///�������������� ����������
	dllSyntaxAnalyzer,
	///��������� ����������
	dllBlackBox,
	///������� ������
	dllAISBroker,
	///�������� �������
	dllMainAnalyse,
	///������ ������ �������������
	dllRev,
	///������� �������������
	dllFeatureFactory,
	///������ ������ �������������
	dllTransformGenerator,
	///������ �������� ������ ��������� ����
	dllNdxDataStorage,
	///������ ���������� ������
	dllBasesManager,
	///������ ���������� ��������� �������
	dllLoadManager,
	///������ ����� ��������
	dllCommonServices,
	///������ �������� ������ ��������� ���� Ndx
	dllNdxBaseManager,
	///������ ���������� � ������ � ��������� ���� Ndx
	dllNdxProcessor,
	///������ ����� ����������� 
	dllCommonContainers,
	///������ ����� ������������� ��������
	dllUMCommonServices,
	///������ ���������� ���������������� ������
	dllLingvoBaseManager,
	///����� ������ ������������ �������
	dllLexicalAnalyzer,
	///������ �������������� �������
	dllSemanticAnalyzer,
	///������ ������ ��������������� �������������
	dllLinguisticRev,
	//�������� ������ �1
	dllTest1,
	//�������� ������ �2
	dllTest2,
	//������ ��������
	dllGSServer,
	//������ �������������� ���
	dllDataBaseTransformer,
	// ������ ��������������� �������
	dllStatisticsCollector,
	// ������ ��������������� ������� ������
	dllTextStatisticsProcessor,
	// ������ ���������� ����	
	dllServerLog,
	// ������ ����� ��������� �������
	dllCommonService,
	// ������ ����������� ����������-������
	dllISContainer,
	// ������ ������������ ��������
	dllNdxQuery,
	///���� ������
	dllDBMS,
	/// html parser
	dllHtmlParser,
	///����� ������ ���������
	dllQPCounter,
	///������ ���������� ����������� ���������
	dllGSPluginManager
};
