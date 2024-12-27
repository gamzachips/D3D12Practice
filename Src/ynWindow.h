// 
//! \file   ynWindow.h
//! \brief  엔진 / 윈도 프레임워크 헤더. 
//! 
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date  2003.11.04
//! \date  2010.08.20. Updated. VS08, VS10, Yena 1.01 통합 
//! \date  2012.12.10. Updated. C++11 / GCC5 / VS12
//! \date  2015.10.20. Updated. C++11/14 / GCC6.1 / VS15 
//! \date  2016.12.27. Updated. Windows SDK 8.1/10.0.x (DX11/12)
//! \date  2018.03.05. Updated. C++17  / GCC11 / VS17
//! \date  2020.08.22. Updated. Windows 10 SDK 10.0.x (DX12.x)
//
#pragma once
#pragma warning(disable:4996)

///////////////////////////////////////////////////////////////////////////////
//
// 플랫폼 헤더 및 라이브러리 정의.
//
///////////////////////////////////////////////////////////////////////////////
#include "windows.h"
#include "tchar.h"

#include "wrl.h"
using namespace Microsoft::WRL;

#include "map"
#include "chrono"
using namespace std::chrono;
#define TIME_MAX  milliseconds::max()
//#define TIME_MAX  9223372036854775807



//! \namespace	YENA::Window
//! \brief		엔진 / 윈도 네임스페이스
//! \details	윈도 생성, 메세지 처리 등 일반적인 윈도 운영을 위한 함수와 매크로가 정의됩니다.\n
//! \note		예제의 간결함을 위해 클래스화 하지는 않았습니다. \n
//!				다중 모니터 또는 다중 윈도 환경의 경우 윈도 객체용 클래스가 필요하며
//!				엔진 클래스(e.g., Yena)에서 윈도 객체 컨테이너(e.g., 배열)로 운용할 것을 추천합니다.
//! \ingroup	Engine
namespace YENA::Window
{

///////////////////////////////////////////////////////////////////////////////
//
// 윈도 프레임워크 : 예제의 간결함을 위해 비 클래스화.
//
///////////////////////////////////////////////////////////////////////////////

int  ynCreateWindow		(HWND& rhWnd, UINT width, UINT height, BOOL resize = TRUE);
void ynResizeWindow		(HWND hWnd, UINT NewWidth, UINT NewHeight);
int  ynMessagePump		();
void ynSetWindowTitle	(HWND hWnd, TCHAR* title);

LRESULT CALLBACK ynMsgProc(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (CALLBACK *LPAFXMSGPROC)(HWND, UINT, WPARAM, LPARAM);
//extern LRESULT (CALLBACK * yn_MsgProcExt)(HWND, UINT, WPARAM, LPARAM);
extern TCHAR*		yn_ClassName;
extern TCHAR*		yn_WindowName;
extern LPAFXMSGPROC yn_MsgProcExt;

//!응용 프로그램 상태
enum AFX_STATE {
	AFX_QUIT,			//!< 종료/나가기
	AFX_RUNNING,		//!< 동작중
	AFX_SUSPEND,		//!< 대기중
	AFX_RESUME,			//!< 이어 진행
	AFX_HIDE,			//!< 숨김 (Iconic)
	AFX_RESTORE,		//!< 복구중
	AFX_LOSTDEVICE,		//!< 장치 소실

	AFX_MAX,
};

#define ynChkState(st)  ( (st) == AFX_QUIT )
#define ynChkBreak(st)  if(ynChkState(st)) break;




///////////////////////////////////////////////////////////////////////////////
//
// 기타 시스템 관련 함수 및 매크로.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef KEY_UP
//! 키 눌림 테스트. 
#define KEY_UP(key)	    ((GetAsyncKeyState(key)&0x8001) == 0x8001)
#define KEY_DOWN(key)	((GetAsyncKeyState(key)&0x8000) == 0x8000)
#define ynKeyUp			KEY_UP
#define ynKeyDn			KEY_DOWN
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = nullptr; }
#define SAFE_DELETE(pBuff)	if((pBuff)){ delete (pBuff); (pBuff) = nullptr;	 }
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff); (pBuff) = nullptr;  }
#define ynSafeRelease			SAFE_RELEASE
#define ynSafeDelete			SAFE_DELETE
#define ynSafeDelArry			SAFE_DELARRY

#define SAFE_CLEAR(Buff)	if(Buff){ ZeroMemory(&Buff, sizeof(Buff)); }
#define SAFE_ZEROMEM		SAFE_CLEAR
#define ynSafeClear			SAFE_CLEAR
#define ynSafeZeroMem		SAFE_ZEROMEM
#endif	//SAFE_RELEASE

#ifndef YES_
#define YES_	TRUE
#define NO_		FALSE
#endif

#ifndef ON
#define ON		TRUE
#define OFF		FALSE
#define ENABLE  TRUE
#define DISABLE	FALSE
#endif

#ifndef YN_OK
#define YN_OK	   0					//에러 없음. 특별한 문제 없음.
#define YN_FAIL   -1					//에러 발생.
#define YN_FAILED(v)   ((v) != YN_OK)	//에러 체크 매크로.
#endif

/*
#ifndef OK
#define OK    0							//작업 종료. 문제 없음.
#define FAIL -1							//작업 오류. 기타 오류 있음..
#define CHK_FAILED(v)  ((v) != OK)
#endif*/

#ifndef pure
#define pure	PURE 
//#define pure	=0 
#endif
 
#ifndef in
#define in			
#define out
#define inout
#endif

#define DEFAULT  0
//#define ynToStr(v)   #v
//#define ynPutValule(v)  printf(#v" = %d \n"), v)


#ifndef toKB
//메가바이트 환산
//2진수 기준 : 1 MB = 1,048,576 bytes (1024^2 = 2^20) 
//            1 GB = 1024^3 bytes (1 GiB)
#define toKB(a)  ((a)/1024)
#define toMB(a)  ((a)/1024/1024)		
#define toMBf(a) ((a)/1024/1024.0f)		
//#define toGB(a)  (toMB((a))/1024)		
//#define toGBf(a) (toMBf((a))/1024.0f)		
#define toGB(a)  (toMB((a))/1000)		//GB 표현의 간결함을 위해 10진수로 처리.
#define toGBf(a) (toMBf((a))/1000.0f)		
#endif


} //end of namespace YENA::Window;


using namespace YENA::Window;



/*************** end of file : "ynWindow.h" ********************************/