#pragma once

namespace SS {
namespace CommonServices {
namespace UserTextStorage {
namespace Detail {

///////////////////////////////////////////////////////////////////////////////
// ������������ ��������������
// ��� ������� ������������ ������� �������
///////////////////////////////////////////////////////////////////////////////   
class TUserTextStorage: public NonCopyable
{
   struct TRecord
   {
      INT32 UserID;
      std::wstring Name;
      std::wstring Description;
      std::wstring DirectoryName;

      void *rgRecMap[4];

      TRecord(): UserID(0) 
      {
         rgRecMap[0] = &UserID;
         rgRecMap[1] = &Name;
         rgRecMap[2] = &Description;
         rgRecMap[3] = &DirectoryName;
      }
   };
   
   typedef ClassLevelLockable<TUserTextStorage> TMutex;  //������������ ������� ��� ����������

private:
   IDataBase *m_pDataBase;
   mutable CTablePtr m_pTable;
   TString m_DataCatalogPath;
   TMutex m_Mutex;


private:
   // ������ �� ���� UserName � UserID ��� �������� ������������
   void MakeUserCatalogName( const TString &UserName, INT32 UserID, TString &CatalogName )
   {
      std::basic_stringstream<TCHAR> Stream; 
      Stream << UserName << _T("  ") << UserID;

      CatalogName = Stream.str();
   }

public:
   TUserTextStorage():  m_pDataBase(0) {}
   ~TUserTextStorage() { Close(); }

   void Close();
   void Open( ILoadManager *pLoadManager, const TString &IniFilePath, const TString &DataCatalogPath );

   const TString &GetDataCatalogPath() const { return m_DataCatalogPath; }

   /// ��������� ������������ � �������
   /// ������������� ������������� UserID � ����������� ��� read only ���� oUserName
   void AddUser( TPrivateUserInfo &oUserName );

   /// ������� ������������ �� �������
   void DeleteUser( TUserID UserID );

   /// �������� ���������� � ������������
   void ChangeUserInfo( const TPrivateUserInfo &oUserName );

   /// ���������� ������ ��������������� �������������
   void GetUsersIDList( TUserIDList& oUserIDList) const;

   /// ���������� ������ ���������� � ������������
	/// ���� ���� Password ������������
	void GetPrivateUsersInfo( TUserID UserID, const std::wstring &Password, TPrivateUserInfo &oUserInfo ) const;

   /// ���������� ���������� � ������������ ��������� ��� �������� ��������� (��� ������ ������)
	/// ���� ���� Password ������������
	void GetPublicUsersInfo( TUserID UserID, TPublicUserInfo &oUserInfo ) const;

	/// ����� UserID �� ����� ������������
	bool FindUserIDByName( const std::wstring &Name, TUserIDList &oUserIDList ) const;
};

///////////////////////////////////////////////////////////////////////////////
// ����� ��������� ��������� � ������� � ������ ��������� ����� � ��������� 
// ��������
///////////////////////////////////////////////////////////////////////////////
class TText
{
  std::wstring m_DirName;

public:
   /// ������� ������� � �������
   void OpenDir( const std::wstring &DirName ) { APL_ASSERT(!DirName.empty()); m_DirName = DirName; m_DirName += _T('\\'); } 
   
   /// ��������� ����� �� �����
   /// �����: ���� �� ����� ����
   bool GetFileText( const std::wstring &FileName,  std::wstring &Content ) const;

   /// �������� ����� � ����
   void SetFileTextAnsi( const std::wstring &FileName, const std::wstring &Content );
   void SetFileTextUnicode( const std::wstring &FileName, const std::wstring &Content );

   /// ������� ����
   /// �����: ���� ������ � ��� �����
   bool DeleteFileText( const std::wstring &FileName );

   /// ������ ������ � ��������
   void GetFileNames( TStringsList &FileNameList ) const;
};

///////////////////////////////////////////////////////////////////////////////
// ������ ��������� ��������� ����������  ������� ��� ���������� ������������
///////////////////////////////////////////////////////////////////////////////
class TTextsManager
{
   std::wstring m_DirName;

public:
   /// ������� ������� � �������
   void OpenDir( const std::wstring &DirName ); 

   //������� �������
   const std::wstring &GetCurDir() const { return m_DirName; }

   /// �������� �������
   /// �����: false - ������� ��� ��� ������
   bool AddSubDir( const std::wstring &DirName );

   /// ���� �� ����������
   bool IsExistSubDir( const std::wstring &DirName ) const;

   /// ������� ����������
   /// �����: ������� ��� ������� �����
   bool DeleteSubDir( const std::wstring &DirName );

   /// ������ ������������
   void GetSubDirNames( TStringsList &DirNameList ) const;
};

} //namespace Detail 
} //namespace UserTextStorage
} //namespace CommonServices
} //namespace SS
