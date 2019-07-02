#pragma once

#include "ICommonServices.h"
#include "types.h"
#include "services.h"
#include "conversion.h"
#include <exception>
#include <atlconv.h>

#ifdef MDEFINES
	#include <string>
	#include <vcclr.h>
#endif

namespace SS
{
namespace Core
{
namespace CommonServices
{

	#define USES_INTTOCHAR \
		char __SS_Buffer[40]
	#define INTTOCHAR(x) _ltoa(x,__SS_Buffer,10)

	#define USES_INTTOWCHAR \
		wchar_t __SS_WBuffer[40]
	#define INTTOWCHAR(x) _ltow(x,__SS_WBuffer,10)

	#define SS_WARNING L"warning"
	#define SS_EVENT L"event"
	#define SS_ERROR L"error"
	#define SS_MESSAGE L"message"

#ifdef _DEBUG
	#ifndef USES_IBASE
		#define SAVE_LOG(x) \
			if(!(!spLoadManager)) \
			{\
			SS::Core::CommonServices::CSaveDbgView::SaveDbgView(x, NULL); \
				((SS::Interface::Core::CommonServices::ILog*) \
				spLoadManager->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_Log, IID_Log))->SaveLog(x, NULL); \
			}
	#else
		#define SAVE_LOG(x) \
			((SS::Interface::Core::CommonServices::ILog*) \
			GetLoadManager()->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_Log, IID_Log))->SaveLog(x, NULL);
	#endif
#else
	#define SAVE_LOG(x)
#endif
	
	#define WIDEN2(x) L##x
	#define WIDEN(x) WIDEN2(x)
	#define __WFUNCTION__ WIDEN(__FUNCTION__)
	#define __WFILE__ WIDEN(__FILE__)

	
	#define SL_OUT_DEBUG_STR(x) ::OutputDebugStringW(x)

	#define SS_FILL_EXCEPTION(typeError) \
		pException->Add(); \
		pException->GetCurrent()->SetFunction(__WFUNCTION__); \
		pException->GetCurrent()->SetFile(__WFILE__); \
		pException->GetCurrent()->SetLine(__LINE__); \
		pException->GetCurrent()->SetTypeError(typeError); 

	/// �������� �������� ����������
#ifndef USES_IBASE
	#define SS_THROW(z) { \
		if(!(!spLoadManager)) \
		{ \
			SS::Interface::Core::CommonServices::IException* pException = NULL;\
			spLoadManager->Create(L"./CommonServices/UMCommonServices.dll", CLSID_Exception, IID_Exception, (void**)&pException); \
			SS_FILL_EXCEPTION(SS::Core::CommonServices::eteCritical); \
			pException->GetCurrent()->SetMessage(z, NULL); \
			SAVE_LOG(SS_ERROR AND pException->ToString().c_str()) \
			throw pException; \
		} \
	}
#else
	#define SS_THROW(z) { \
		SS::Interface::Core::CommonServices::IException* pException = \
		(SS::Interface::Core::CommonServices::IException*) \
		GetLoadManager()->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_Exception, IID_Exception); \
		pException->Clear(); \
		SS_FILL_EXCEPTION(SS::Core::CommonServices::eteCritical); \
		pException->GetCurrent()->SetMessage(z, NULL); \
		SAVE_LOG(SS_ERROR AND pException->ToString().c_str()) \
		throw pException;}
#endif
	/// ������������ ��� ���������� �����, �������� SS_THROW(L"HELLO" AND L"HI");
	#define AND ,


	/// ������������ ��� ������������ ���������� ����������� �������
	#define SS_TRY try{

	/// ������������ ��� ������������ ���������� ����������� �������
	#define SS_CATCH(x) } \
		catch(SS::Interface::Core::CommonServices::IException* pException) {  \
			SS_FILL_EXCEPTION(pException->GetCurrent()->GetTypeError()); \
			SL_OUT_DEBUG_STR(pException->ToString().c_str()); \
			SAVE_LOG(SS_ERROR AND x AND pException->ToString().c_str()); \
			switch(pException->GetCurrent()->GetTypeError()) \
			{ \
			case SS::Core::CommonServices::eteCritical: \
					throw pException; \
				break; \
			case SS::Core::CommonServices::eteNormal: \
				break; \
			}; \
		}  catch (std::exception& e) { \
			SS::Core::CommonServices::CConvertMultiByteAndWideChar oConvertMultiByteAndWideChar; \
			SS::Core::CommonServices::CSaveDbgView::SaveDbgView(L"Catch in:" AND __WFUNCTION__ AND oConvertMultiByteAndWideChar.MultiByteToWideChar(e.what()) AND NULL); \
			SAVE_LOG(SS_ERROR AND L"catch (...)" AND x AND __WFUNCTION__ AND oConvertMultiByteAndWideChar.MultiByteToWideChar(e.what())) \
			SS_THROW(x AND oConvertMultiByteAndWideChar.MultiByteToWideChar(e.what())); \
		}  catch (...) { \
			SS::Core::CommonServices::CSaveDbgView::SaveDbgView(L"Catch in:" AND __WFUNCTION__ AND NULL); \
			SAVE_LOG(SS_ERROR AND L"catch (...)" AND x AND __WFUNCTION__) \
			SS_THROW(x); \
		}


	/// ���������� ������� ��� ������������� ���������� ��������� �������, ������ ���� ��������� � ����� ����� � �������� CreateInstance
#ifndef MDEFINES
	#define SET_LOAD_MANAGER_DEFINE \
		extern "C" \
		void __declspec(dllexport) SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager*); \
		extern "C" \
		bool __declspec(dllexport) IsLoadManagerExist()
#else
	#define SET_LOAD_MANAGER_DEFINE
#endif


	/// ��������� ������� ��� ������������� ���������� ��������� �������, ������ ���� ��������� � ����� ����� � ����������� ������� CreateInstance
#ifndef MDEFINES
	#define SET_LOAD_MANAGER_IMPLEMENTATION \
		SS::Core::CommonServices::TSmartPointerOfIBase<SS::Interface::Core::ResourceManagers::ILoadManager> spLoadManager; \
		SS::Core::CommonServices::CManagerLifeTimeForCriticalSection omltCriticalSection; \
		\
		void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager) \
		{ \
			SS::Core::CommonServices::CCriticalSection oCriticalSection(&omltCriticalSection); \
			if(!IsLoadManagerExist()) \
				spLoadManager = pLoadManager; \
		}; \
		bool IsLoadManagerExist() \
		{ \
			return (!spLoadManager) ? false : true; \
		}
#else
	#define SET_LOAD_MANAGER_IMPLEMENTATION 
#endif

	/// ������ ���� ��������� � �����, ��� ����������� ������������� ����
	#define USES_LOAD_MANAGER \
		extern SS::Core::CommonServices::TSmartPointerOfIBase<SS::Interface::Core::ResourceManagers::ILoadManager> spLoadManager; 

	///��������� ������� ������� �� ��������������
	#define SS_START_TICK(sID) \
		if(!(!spLoadManager)) \
			((SS::Interface::Core::CommonServices::IPerformanceMeasure*) \
			spLoadManager->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_PerformanceMeasure, IID_PerformanceMeasure))->StartCalculation(sID);

	///������������� ������� ������� �� ��������������
	#define SS_STOP_TICK(sID) \
		if(!(!spLoadManager)) \
			((SS::Interface::Core::CommonServices::IPerformanceMeasure*) \
			spLoadManager->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_PerformanceMeasure, IID_PerformanceMeasure))->StopCalculation(sID);

	///����������� ������� ���������� �� ��������������
	#define SS_VIEW_TICK(sID) \
		if(!(!spLoadManager)) \
			((SS::Interface::Core::CommonServices::IPerformanceMeasure*) \
			spLoadManager->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_PerformanceMeasure, IID_PerformanceMeasure))->ViewCalculation(sID);

	///������� ������
	#define SS_CLEAR_TICKS() \
		if(!(!spLoadManager)) \
			((SS::Interface::Core::CommonServices::IPerformanceMeasure*) \
			spLoadManager->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_PerformanceMeasure, IID_PerformanceMeasure))->ClearCalculations();

	///����������� ���� ������� ������� ����������
	#define SS_VIEW_TICKS() \
		if(!(!spLoadManager)) \
			((SS::Interface::Core::CommonServices::IPerformanceMeasure*) \
			spLoadManager->GetInterface(L"./CommonServices/UMCommonServices.dll", CLSID_PerformanceMeasure, IID_PerformanceMeasure))->ViewCalculations();

}
}
}