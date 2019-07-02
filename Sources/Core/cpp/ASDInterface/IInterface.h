#pragma once

#include <vector>
#include <string>
#include "../ASCInterface/IInterface.h"

namespace SS
{
	namespace Interface
	{
		namespace Core
		{

			///������� ��� ���-������
			class IServiceDatabase : public virtual IBase
			{
			public:

				///������������ ��������� �����������
				virtual HRESULT RunBackUp(	std::vector< std::pair<std::string, std::string> >* vPathes,
											const char* szBaseName	)=0;

				///������������ �������� ����
				virtual HRESULT RunShrink()=0;

				///������������ �������������� ����
				virtual HRESULT RunDefrag(char* szTableName, char* szIndexNumber)=0;

			};

			///�������� ����-������
			class IOpenFiles : public virtual IBase
			{
			public:

				///��������� ��������� ������
				virtual HRESULT OpenStorage(const char* szBaseName)=0;
				///3a������� ��������� ������
				virtual void CloseStorage()=0;

				///������� ��������� ������
				virtual HRESULT ClearStorage(const char* szBaseName)=0;
				///������������� ���� � ����(���� ����� ��������� ����������)
				virtual void SetDatabasePath(char* szPath)=0;

				IOpenFiles(){};
				virtual ~IOpenFiles(){};
			};
		}

	}
}
