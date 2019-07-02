#pragma once

#include <string>
#include <list>

// {9A9F00C8-D506-4f5f-BE15-34731A93D5D4}
static const GUID IID_UsersManager = 
{ 0x9a9f00c8, 0xd506, 0x4f5f, { 0xbe, 0x15, 0x34, 0x73, 0x1a, 0x93, 0xd5, 0xd4 } };

// {859A4AC9-EA7D-4db5-81EA-E40536BF6A4C}
static const GUID CLSID_UsersManager = 
{ 0x859a4ac9, 0xea7d, 0x4db5, { 0x81, 0xea, 0xe4, 0x5, 0x36, 0xbf, 0x6a, 0x4c } };

namespace SS
{
namespace Autorization
{
namespace Types
{  
   typedef unsigned int TUserID;
 
   /// ������������ ������ � ������������
   /// UserID - �������� ���������� ���������������, ������� ���������� �������������� ������������
   class TPublicUserInfo
   {
      TUserID m_UserID;              //������������� ������������
      std::wstring m_wName;          //��� ������������

   public:
      /// ������������� ������������ read only
      TUserID GetUserID() const { return m_UserID; }

      /// ��� ������������
      void SetUserName( const std::wstring &Val ){ m_wName = Val; }
      std::wstring GetUserName() const { return m_wName; }

   public: //���������� ������ ����������, �� ��������!
      void SetUserID( TUserID Val ){ m_UserID = Val; }
   };
   
   /// ���������� ������ � ������������, ��� ������� � ������� ���������� ������ ������
   class TPrivateUserInfo: public TPublicUserInfo
   {
      std::wstring m_wPassword;    //������ ������������
      std::wstring m_wDescription;   //������������ �������� ������������
      std::wstring m_UserCatalog;    //������� �����������

   public:
      /// ������������ �������� ������������
      void SetDescription( const std::wstring &Val ){ m_wDescription = Val; }
      std::wstring GetDescription() const { return m_wDescription; }

      /// ������ ������������
      void SetPassword( const std::wstring &Val ){ m_wPassword = Val; }
      std::wstring GetPassword() const { return m_wPassword; }
      
      /// ������ ������� ������������
      std::wstring GetUserCatalog() const { return m_UserCatalog; }

   public: //���������� ������ ����������, �� ��������!
      void SetUserCatalog( const std::wstring &Val ){ m_UserCatalog = Val; }

   };

   typedef std::list<TUserID> TUserIDList;
}
}

namespace Interface
{
namespace Autorization
{
   /// ���������� ��������������
   /// ������ ���� ������������
	class IUsersManager : public virtual SS::Interface::IBase
	{
	public:   
		virtual ~IUsersManager() {};

      /// ���������������� ��-���������
      /// ���������� �������� ����� �������������� ����������
      /// DataCatalogPath - ������� � ������� ������ (���� ������, �� ������������ ��-���������
      virtual void Init( const std::wstring &DataCatalogPath = L"" ) = 0;

      /// �������������
      /// IniFilePath- ���� � INI-����� DBMS
      /// DataCatalogPath - ������� � ������� ������
      /// virtual void Init( const std::wstring &IniFilePath, const std::wstring &DataCatalogPath ) = 0;

      /// ���� � �������� � ������ ������ 
      virtual std::wstring GetDataCatalogPath() const = 0;

      /// ��������� ������������ � �������
		/// ������������� ������������� UserID � ����������� ��� read only ���� oUserName
		virtual void AddUser( /*inout*/SS::Autorization::Types::TPrivateUserInfo &UserInfo ) = 0;

		/// ������� ������������ �� �������
		virtual void DeleteUser( /*in*/SS::Autorization::Types::TUserID UserID ) = 0;

		/// �������� ���������� � ������������
		virtual void ChangeUserInfo( /*in*/const SS::Autorization::Types::TPrivateUserInfo &UserInfo ) = 0;

		/// ���������� ������ ��������������� �������������
		virtual void GetUsersIDList( /*out*/SS::Autorization::Types::TUserIDList& UserIDList) const = 0;

		/// ���������� ������ ���������� � ������������
		/// ���� ���� Password ������������
		virtual void GetPrivateUsersInfo( 
			/*in*/SS::Autorization::Types::TUserID UserID, 
			/*in*/const std::wstring &Password, 
			/*out*/SS::Autorization::Types::TPrivateUserInfo &UserInfo ) const = 0;

      /// ���������� ���������� � ������������ ��������� ��� �������� ��������� (��� ������ ������)
		/// ���� ���� Password ������������
		virtual void GetPublicUsersInfo( 
			/*in*/SS::Autorization::Types::TUserID UserID, 
			/*out*/SS::Autorization::Types::TPublicUserInfo &UserInfo ) const = 0;

		/// ����� UserID �� ����� ������������
		virtual bool FindUserIDByName( 
		/*in*/const std::wstring &Name, 
		/*out*/SS::Autorization::Types::TUserIDList &UserIDList ) const = 0;
	}; 
}
}
}