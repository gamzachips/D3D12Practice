// 
//! \file   Yena.h
//! \brief  예나 / 엔진 / 기반 프레임워크 헤더.
//! 
//! \author	김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//
#pragma once
#pragma warning(disable:4996)

/////////////////////////////////////////////////////////////////////////////
//
// 기본 필수 헤더 정의
//
/////////////////////////////////////////////////////////////////////////////
#include "windows.h"		//Windows 기본 헤더.
#include "tchar.h"

#include "ynError.h"		//엔진\예외처리 프레임워크. 
#include "ynWindow.h"		//엔진\윈도 프레임워크.
#include "ynGraphics.h"		//엔진\DX 표준 헤더 및 헬퍼 클래스.
//#include "ynTimer.h"		//엔진\타이머 클래스.

 


///////////////////////////////////////////////////////////////////////////////
//
// 엔진 프레임워크 설명
//
///////////////////////////////////////////////////////////////////////////////
//! \defgroup	Yena 엔진 프레임워크
//!	\brief		공통 기반 프레임워크와 확장 라이브러리. \n
//!	\details	3D 애플리케이션 제작용 공통 기반 프레임워크와 확장 라이브러리를 제공합니다.
//! \n \copydetails YENA
//! \n\n \copydetails Yena
//! \par		소스 파일
//! \ref		Yena.h, Yena.cpp, ynWindow.h, ynDXAfx.h, ynError.h, ynTimer.h 
//
//! \namespace	YENA
//! \brief		예나 / 엔진 / 최상위 네임스페이스
//! \details	네임스페이스 YENA 에는 엔진 및 예제 전체에서 사용될 전역 데이터, 상수, 매크로, 함수, 헬퍼 클래스 등을 정의합니다.
//! \note		D3D 인터페이스들은 직관적인 표현, 호환성 향상 및 일반화를 위해 재정의하였습니다. 
//! 
//!	2020.08.22 김기홍 Kihong.Kim / onlysonim@gmail.com 
//! \ingroup	Yena 
namespace YENA
{

	// 전역(공유) 데이터, 함수 및 인터페이스의 추가는 여기에...
	//...

	//GLOBALCONST TCHAR* yn_strProjVer	= _T("v.0.9");
	//GLOBALCONST TCHAR* yn_strEngVer	= _T("v.1.0.0@1");
	//GLOBALCONST TCHAR* yn_strBuildVer	= _T("Build.20.0822");

}


using namespace YENA;




/****************** The end of file "Yena.h" ***********************************/