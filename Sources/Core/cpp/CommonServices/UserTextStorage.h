#pragma once

namespace SS {
namespace CommonServices {
namespace UserTextStorage {


///////////////////////////////////////////////////////////////////////////////
// ���������� ���������� IUsersManager
///////////////////////////////////////////////////////////////////////////////
class TUsersManager: public IUsersManager
{
   Detail::TUserTextStorage m_UserTextStorage;

public:     
   /// �������������
   /// IniFilePath- ���� � INI-����� DBMS
   /// DataCatalogPath - ������� � ������� ������
   void Init( const std::wstring &IniFilePath, const std::wstring &DataCatalogPath );

   /// ������������� ��-���������
   /// ���������� �������� ����� �������������� ����������
   /// DataCatalogPath - ������� � ������� ������ (���� ������, �� ������������ ��-���������
   void Init( const std::wstring &DataCatalogPath = L"" );

   /// ���� � �������� � ������ ������ 
   std::wstring GetDataCatalogPath() const;

   /// ��������� ������������ � �������
   /// ������������� ������������� UserID � ����������� ��� read only ���� oUserName
   void AddUser( TPrivateUserInfo &UserInfo );

   /// ������� ������������ �� �������
   void DeleteUser( TUserID UserID );

   /// �������� ���������� � ������������
   void ChangeUserInfo( const TPrivateUserInfo &UserInfo );

   /// ���������� ������ ��������������� �������������
   void GetUsersIDList(TUserIDList& UserIDList) const;

   /// ���������� ������ ���������� � ������������
   /// ���� ���� Password ������������
   void GetPrivateUsersInfo( TUserID UserID, const std::wstring &Password, TPrivateUserInfo &UserInfo ) const;

   /// ���������� ���������� � ������������ ��������� ��� �������� ��������� (��� ������ ������)
   /// ���� ���� Password ������������
   void GetPublicUsersInfo( TUserID UserID, TPublicUserInfo &UserInfo ) const;

   /// ����� UserID �� ����� ������������
   bool FindUserIDByName( const std::wstring &Name, TUserIDList &UserIDList ) const;

public:
   RELEASE_IMPL()

   BEGIN_QI_MAP()
      QI_MAP_INHERIT_ENTRY( IID_UsersManager, IUsersManager )
      QI_MAP_INHERIT_ENTRY( IID_Base, IBase )
   END_QI_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// ���������� ���������� IText
///////////////////////////////////////////////////////////////////////////////
class TText: public IText
{
   Detail::TText m_Text;

public:
   /// ��������� ����� ������ � ������ PartName � Content
   /// ������ ����� ������������ �������������
   bool GetTextPart( const std::wstring &PartName,  std::wstring &Content ) const;

   /// �������� ��������� ����� ������ � ������ PartName � Content ��������� ������ ����� FileFormat
   void SetTextPart( const std::wstring &PartName,  const std::wstring &Content, EFileFormat FileFormat = FFUNICODE );

   /// ������� ��������� ����� ������ � ������ PartName
   bool DeleteTextPart( const std::wstring &PartName );

   /// �������� �������� ���� ������
   void GetTextPartNames( TStringsList &PartNameList );

public: //�������� �� ����������� � ���������� IText
   void OpenDir( const std::wstring &DirName );

public:
   RELEASE_IMPL()

   BEGIN_QI_MAP()
      QI_MAP_INHERIT_ENTRY( IID_Text, IText )
      QI_MAP_INHERIT_ENTRY( IID_Base, IBase )
   END_QI_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// ���������� ���������� ITextsManager
///////////////////////////////////////////////////////////////////////////////
class TTextsManager: public ITextsManager
{
   Detail::TTextsManager m_TextsManager;

public:   
   /// ������� ������ ������������. �������������.
   void Open( TUserID UserID, const std::wstring &Password, IUsersManager *pUsersManager );

   /// �������� � ������� ������������ ����� � ������ TextName
   bool AddText( const std::wstring &TextName, IText *pText );

   /// ���������� ����� � ������ TextName
   bool GetText( const std::wstring &TextName, IText *pText ) const;

   /// ������� �� ������� ������������ ����� � ������ TextName
   bool DeleteText( const std::wstring &TextName );

   /// �������� �������� ���� ������� ������������
   void GetUserTextNames( TStringsList &TextNameList ) const;

public:
   RELEASE_IMPL()

   BEGIN_QI_MAP()
      QI_MAP_INHERIT_ENTRY( IID_TextsManager, ITextsManager )
      QI_MAP_INHERIT_ENTRY( IID_Base, IBase )
   END_QI_MAP()
};

} //namespace UserTextStorage
} //namespace CommonServices
} //namespace SS
