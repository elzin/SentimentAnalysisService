#ifndef _SYNC_OBJ_H
#define _SYNC_OBJ_H

//#include "__Def.h"
//#include "OtxType.h"

#define EXEPTION_NO_SYNC_OBJECT                 "Synchronization::NoSyncObject"
#define EXEPTION_NULL_OBJECT_OPERATION          "Synchronization::NotNullObjectExpected"
#define EXEPTION_NOT_NULL_OBJECT_CREATION       "Synchronization::TheObjectIsBusy"

#pragma pack(push,8)  // Fix packing

#ifndef DRIVER


	/*! \class CritSectC
	*  \brief ����� ��������� ����������� ������ CRITICAL_SECTION
	*/
	class CritSectC   {

		/// ������������ ����� "��������� ����������� ������"
		friend class VisitCritSectC;

		private: // Data

			/// ������� ���������
			LONG                EnterCnt;

			/// ���� "������� ������"
			BOOL                DeleteFl;

			/// ��������� ����������� ������
			CRITICAL_SECTION    CritSect;

		public: // Constructor/Destructor

			/// �����������
			CritSectC(void)   {   DeleteFl=FALSE; EnterCnt=0; memset(&CritSect,0,sizeof(CRITICAL_SECTION)); InitializeCriticalSection(&CritSect);   }

			/// ����������
			~CritSectC(void)   {  DeleteCriticalSection(&CritSect); }

		public: // Functions

			/// ����� � ��
			void Enter(void)   { EnterCriticalSection(&CritSect);    InterlockedIncrement(&EnterCnt); }

			/// �������� ��
			void Leave(void)   { LeaveCriticalSection(&CritSect); if(InterlockedDecrement(&EnterCnt)==0 && DeleteFl) delete(this); }

			/// ������� ��
			void Destroy(void) { DeleteFl=TRUE; }

	};

	/*! \class VisitCritSectC
	*  \brief ����� ��������� ����������� ������ CritSectC
	*/
	class VisitCritSectC   {


		/// ������������ ����� "����������� ������"
		friend class CritSectC;

		private: // Data

			/// ��������� �� ��
			CritSectC * CritSectPtr;

		public: // Constructor/Destructor

			/// ����������� - ����� � ��
			VisitCritSectC(CritSectC & rCritSect)   { CritSectPtr=&rCritSect; if(CritSectPtr)   CritSectPtr->Enter(); }

			/// ����������� - ����� � ��
			VisitCritSectC(CritSectC * pCritSect)   { CritSectPtr= pCritSect; if(CritSectPtr)   CritSectPtr->Enter(); }

			/// ����������  - �������� ��
			~VisitCritSectC(void)                    { if(CritSectPtr)   CritSectPtr->Leave(); }

			/// �������� ��������� � ��
			void AbortVisitCritSect(void)           { if(CritSectPtr)   CritSectPtr->Leave();  CritSectPtr=NULL; }

	};

	/// ����� - ������� ����������� ������
	#define NEW_CRIT_SECT(pCritSect)          if(pCritSect==NULL) { pCritSect = new CritSectC; }

	/// ����� - ������� ����������� ������
	#define DEL_CRIT_SECT(pCritSect)          if(pCritSect!=NULL) { pCritSect->Destroy(); pCritSect=NULL; }

	/// ����� - �������� ����������� ������
	#define VISIT_CRIT_SECT(CRIT_SECT)        VisitCritSectC Visit##CRIT_SECT(CRIT_SECT)

	/// ����� - �������� ��������� ����������� ������
	#define ABORT_VISIT_CRIT_SECT(CRIT_SECT)  Visit##CRIT_SECT.AbortVisitCritSect()


	// // // // // // // // // // // // // // // // // // // // // // // //


	/*! \class SyncObjC
	*  \brief ������� ����� ��� �������� �������������
	*/
	class SyncObjC   {

		public:

			HANDLE Hnd;

		public:

			SyncObjC(void);
			~SyncObjC(void);

	};


	/*! \class AMEventC
	*  \brief ������� ����� ��� �������� Event
	*/
	class AMEventC : public SyncObjC  {

		public:

			AMEventC(bool bManual);
			~AMEventC(void);

			void Set(void);
			void Reset(void);
			void Pulse(void);

	};


	/*! \class ManualEventC
	*  \brief ����� ��� �������� NonAutoEvent
	*/
	class ManualEventC : public AMEventC   {

		public:

			ManualEventC(void) : AMEventC(TRUE) {};
			~ManualEventC(void)                  {};

	};


	/*! \class AutoEventC
	*  \brief ����� ��� �������� AutoEvent
	*/
	class AutoEventC : public AMEventC   {

		public:

			AutoEventC(void) : AMEventC(FALSE) {};
			~AutoEventC(void)                   {};

	};


	/*! \class SemaphoreC
	*  \brief ����� ��� �������� Semaphore
	*/
	class SemaphoreC : public SyncObjC  {

		private: // Data

			long MaxCount;

		public:

			SemaphoreC(void);
			~SemaphoreC(void);

			void Make(long nMaxCount, long nInitCount = 0L);
			long Release(long lReleaseCount, long * lpPreviousCount = NULL);
			long GetCount(void);
			void Restore(void);
	};

#else // DRIVER

	#define NEW_CRIT_SECT(pCritSect)
	#define DEL_CRIT_SECT(pCritSect)
	#define VISIT_CRIT_SECT(CRIT_SECT)
	#define ABORT_VISIT_CRIT_SECT(CRIT_SECT)

#endif

#pragma pack(pop)

#endif // _SYNC_OBJ_H


