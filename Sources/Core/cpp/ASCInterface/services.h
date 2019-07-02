#pragma once

#include <windows.h>
#include <string>
#include <vector>

namespace SS
{
namespace Interface
{
namespace Core
{
namespace ResourceManagers
{
	class ILoadManager;
}
}
}
}

namespace SS
{
namespace Core
{
namespace CommonServices
{

	class CManagerLifeTimeForEvent
	{
		HANDLE m_hEvent;
	public:

		CManagerLifeTimeForEvent()
		{
			m_hEvent = CreateEvent(NULL,FALSE,TRUE,NULL);
		};

		~CManagerLifeTimeForEvent()
		{
			::CloseHandle(m_hEvent);
		};

		operator HANDLE()
		{
			return m_hEvent;
		};
	};


	class CWaitForSingleObject
	{
		CManagerLifeTimeForEvent* m_pManagerLifeTimeForEvent;
	public:

		CWaitForSingleObject(CManagerLifeTimeForEvent* pManagerLifeTimeForEvent) 
			: m_pManagerLifeTimeForEvent(pManagerLifeTimeForEvent)
		{
			::WaitForSingleObject(*m_pManagerLifeTimeForEvent, INFINITE);
		};
		
		~CWaitForSingleObject()
		{
			SetEvent(*m_pManagerLifeTimeForEvent);
		};
	};
	/// ��������� �������� ����� ����������� ������
	class CManagerLifeTimeForCriticalSection
	{
		/// ����������� ������
		CRITICAL_SECTION m_pcs;
	public:

		/// ������������� ����������� ������
		CManagerLifeTimeForCriticalSection()
		{
			::InitializeCriticalSection(&m_pcs);
		};

		/// �������� ����������� ������
		~CManagerLifeTimeForCriticalSection()
		{
			::DeleteCriticalSection(&m_pcs);
		};		

		operator LPCRITICAL_SECTION ()
		{
			return &m_pcs;
		};
	};

	/// ��������� �������������� ����/����� ��/� ����������� ������
	class CCriticalSection
	{
		/// ����������� ������
		CManagerLifeTimeForCriticalSection *m_pcs;
	public:

		/// ������������� ������ ������
		/** 
			\param lpCriticalSection - ����������� ������
		*/
		CCriticalSection(CManagerLifeTimeForCriticalSection* lpCriticalSection) : m_pcs(lpCriticalSection) 
		{
			::EnterCriticalSection(*m_pcs);
		};
	
		///�������������� ����� �� ����������� ������
		~CCriticalSection()
		{
			LeaveCriticalSection();
		};
	
	private:
		/// ����� �� ����������� ������
		void LeaveCriticalSection()
		{
			::LeaveCriticalSection(*m_pcs);
		};
	};

	/// ���������
	template <class T>
		class CSingle
		{
		public:
			static T& Instance()
			{
				static T oT;
				return oT;
			};
		};


		/// ����� ��������� ��� ����������� �� IBase
	template <class T>
		class TSmartPointerOfIBase
		{
			T* m_pT;
		public:
			TSmartPointerOfIBase() : m_pT(NULL) {};
			~TSmartPointerOfIBase()
			{
				if(m_pT)
					m_pT->Release();
			};

			T* operator = (T* pT)
			{
				if(m_pT)
				{
					m_pT->Release();
					m_pT = NULL;
				};
				m_pT = pT;
				return m_pT;
			};

			bool operator ! ()
			{
				return (!m_pT) ? true : false;
			};
			T* operator-> ()
			{
				return m_pT;
			};
		};

	class CBaseCoreClass
	{
	public:
		CBaseCoreClass() : m_pLoadManager(NULL)
		{
		}
		/*virtual ~CBaseCoreClass()
		{
		}*/
	public:
			/// ������������� ��������� �� ���� ��������
			virtual void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
			{
				m_pLoadManager = pLoadManager;
			};
			/// ������������� ��������� �� ���� ��������
			virtual SS::Interface::Core::ResourceManagers::ILoadManager* GetLoadManager()
			{
				return m_pLoadManager;
			};
		private:
			SS::Interface::Core::ResourceManagers::ILoadManager* m_pLoadManager;
	};

	class CSaveDbgView
	{
	public:
		static void SaveDbgView(wchar_t* wszFirst...) 
		{ 
			try{ 
				va_list args; 
				va_start(args,wszFirst); 
				
				std::wstring wsArgs=L";"; 
				wsArgs.reserve(512); 
				wsArgs+=wszFirst; 
				for(;;) 
				{ 
				
				
					wchar_t* wszArg=va_arg(args, wchar_t*); 
					if(wszArg==NULL) break; 
				
					wsArgs+=L";"; 
				
					wsArgs+=wszArg; 
				};
				
				if(!wsArgs.empty()) 
					wsArgs+=L"#"; 
				
				va_end(args); 
				
				::OutputDebugStringW(wsArgs.c_str()); 
			}
			catch(...){ 
			
				::OutputDebugStringW(L"Error in SaveDbgView"); 
				throw;
			}
		};
	};
}
}
}