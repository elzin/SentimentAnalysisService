#pragma once

#include "../ASSInterface/TDictionaryNames.h"

#include ".\consts.h"
#include "..\ASSInterface\TBaseNames.h"
using namespace SS::MANAGER::Constants;

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

	/// ��������� ������ � ����������� (��������, �����������, ������������� � ��������)
	template <class TConnection> class CBaseConnectionsManager 
	{
		std::wstring m_wsNameActiveStorage;
	public:

		void SetActiveStorage(const wchar_t* wszNameActiveStorage)
		{
			m_wsNameActiveStorage = wszNameActiveStorage;
		};

		std::wstring& GetActiveStorage()
		{
			return m_wsNameActiveStorage;
		};
	protected:

		/// ��������� �������� ���������� ������������� ���� ���
		/** 
			\param BaseType \see SS::MANAGER::Constants
			\return bool - ���� true, �� ���� �������

			����� ����������� �������, ����������� � ������� �����������, ���������� �� ����� ������
		*/
		virtual bool Open(const wchar_t* BaseType, TConnection** ptssConnection) = 0;

		/// ������������� ������ �� ����������
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� �� ������ � �����
			
		���� ����� ������ ����� ����, ���������� ����������� � ������������ ��������, ���������� � ��� 
		*/
		template<class TConnections> void UnRegisterDeleteAndClose(const wchar_t* BaseType, TConnection** ptssConnection, TConnections& oConnections)
		{

			SS_TRY
			{
				TConnections::iterator it_Connection=oConnections.find(BaseType);

				if(!ptssConnection)
				{

					SAVE_LOG(SS_ERROR AND L"!ppConnection" AND BaseType AND __WFUNCTION__);
					return;
				};

				if(it_Connection!=oConnections.end())
				{

					if(it_Connection->second.empty())
					{

						SAVE_LOG(SS_ERROR AND L"it_Connections->second.empty()" AND BaseType AND __WFUNCTION__);
						return;
					};
					

					//������� � ������� ������
					TConnections::value_type::second_type::iterator it_CurrentConnection=find(it_Connection->second.begin(), it_Connection->second.end(), ptssConnection);

					if(it_CurrentConnection!=it_Connection->second.end())
						it_Connection->second.erase(it_CurrentConnection);


					if(it_Connection->second.empty())
					{
						//SAVE_LOG(SS_MESSAGE,"������� ������� ����",BaseType,NULL);
						(*ptssConnection)->Close();
						//(*ptssConnection)->Release();
						
						*ptssConnection=NULL;
						oConnections.erase(it_Connection);
					};
				};
			}
			SS_CATCH(L"")
		};

		/// �������� ��������, �������������� ����� ���� ������������� ���� � ������� ������� ���������� � ������������
		/** 
			\param BaseType - ��� ����, (���������������, ���������, ��������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� �� ������ � ����� 
			
		������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
		��������������� ����� ���� ������������� ���� � ���������� ��������� �� ���� � ���������� ��������� 
		*/
		template<class TConnections> void CreateOpenAndRegister(const wchar_t* BaseType, TConnection** ptssConnection, TConnections& oConnections)
		{
			SS_TRY
			{
				TConnections::iterator it_Connection=oConnections.find(BaseType);

				if(!ptssConnection)
				{

					SAVE_LOG(SS_ERROR AND L"!ppConnection" AND BaseType AND __WFUNCTION__);
					return;
				};

				if(it_Connection!=oConnections.end())
				{

					if(it_Connection->second.empty())
					{

						SAVE_LOG(SS_ERROR AND L"������� ����, � ���������� ��� ���� ���" AND BaseType AND __WFUNCTION__);
						return;
					};
				

					//���������� ��������� �� ������� ���������� � ����� ������������ ������� ����������		
					TConnections::value_type::second_type::iterator it_CurrentConnection=find(it_Connection->second.begin(), it_Connection->second.end(), ptssConnection);

					if(it_CurrentConnection==it_Connection->second.end())
					{
						it_Connection->second.push_back(ptssConnection);
						*ptssConnection=*it_Connection->second.front();
					};


					if(!(*it_Connection->second.front())->IsOpen())
					{
						if(!Open(BaseType,it_Connection->second.front()))
						{
							SAVE_LOG(SS_ERROR AND L"������������ ���������� �� �����������" AND BaseType AND __WFUNCTION__);

							//������� ������
							it_CurrentConnection=find(it_Connection->second.begin(), it_Connection->second.end(), ptssConnection);
							if(it_CurrentConnection!=it_Connection->second.end())
								it_Connection->second.erase(it_CurrentConnection);
						};
					};
				}
				else
				{

					*ptssConnection=NULL;
					if(Open(BaseType,ptssConnection))
						oConnections.insert(TConnections::value_type(BaseType,TConnections::value_type::second_type(1,ptssConnection)));
					else
					{

						SAVE_LOG(SS_ERROR AND L"���������� �� �����������, ����-" AND BaseType AND __WFUNCTION__);
					};

				};
			}
			SS_CATCH(L"")
		}
	public:
	};
}
}
}