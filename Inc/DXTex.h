//
// DirectXTex.h : DirectX Texture Library 헤더
//
// DirectX Texture Library : DX11 ( Dec.13, 2017) 
// 제공 Present : Chuck Walbourn @ Microsoft / MSFT (http://blogs.msdn.com/b/chuckw/)
// 편집 Edit    : Kihong Kim / onlysonim@gmail.com 
// 갱신 Update  : 2017.12.03
//
#pragma once
#pragma warning(disable:4996)

// Platform Header 및 Library
//
#include "Windows.h"
#include "stdio.h"

/*
///////////////////////////////////////////////////////////////////////////////
//
// DirectX 표준 라이브러리 
//
///////////////////////////////////////////////////////////////////////////////
// < DirectX 버전별 개발 라이브러리 >
// DX9         : DirectX SDK 2002 Nov.
// DX10.x/DX11 : DirectX SDK 2010 June (DX 독립 배포 마지막 버전)
// DX11.X/DX12 : Windows SDK 8.x  (DX 가 포함되어 배포됨)

// DX 표준 헤더
#include "D3D11.h"					//DX 표준 헤더. (DX 11.0)
//#include "D3D11_1.h"				//DX 표준 헤더. (DX 11.1)
#pragma comment(lib, "D3D11")		//DX 라이브러리 로딩.  D3D11.dll 필요.

//DirectX Math : Dx 수학 라이브러리
//#include "XNAMath.h"				//XNA Math 라이브러리.(ver.2.0) DirectX SDK 2010 June. 대응.
#include "DirectXMath.h"			//XNA Math 라이브러리.(ver.3.0) VS2012 (Windows SDK 8) 이상.
using namespace DirectX;

//DXGI : DirectX Graphics Infrastructure
//DX 의 버전에 독립적인 하드웨어 저수준 접근 방식을 제공합니다.
//#include "DXGI.h"					//DXGI 헤더. (d3d11.h 에 포함됨)
#pragma comment(lib, "dxgi")		//DXGI 라이브러리. DXGI.dll 필요.

//DX 셰이더 운용 라이브러리.
#include "D3DCompiler.h"				//DX 셰이더 컴파일러 헤더.
#pragma comment(lib, "d3dcompiler")		//DX 셰이더 컴파일러 라이브러리.  D3DCompiler.dll 필요.
*/


///////////////////////////////////////////////////////////////////////////////
//
// DirectX 텍스처 라이브러리 
//
///////////////////////////////////////////////////////////////////////////////
//
// DX 텍스처 유틸리티 및 일반화 라이브러리 모음집. 
// DX 텍스처 사용시 필요한 여러 기능 클래스 및 서비스를 제공합니다.
// 일반적인 이미지 포멧(JPG, BMP, PNG 등..) 및 특수 포맷 (TGA, DDS) 을 함께 지원하며 
// 포맷변환, 컬러키(Color-Key), 압축포멧(BCX) 등의 추가 기능도 제공합니다.
//
// DDS 포멧 : 전용 함수 지원  ex) Create-DDS-Texture
// WIC 포멧 : bmp, jpg, png 등의 일반 포멧 지원.  ex) Create-WIC-Texture
// TGA 포멧 : 전용 함수 사용. ex) LoadFrom-TGA-File
//
// 기본적인 기능은 DirectXTK 에도 포함되어 배포 중입니다. 자세한 내용을 아래를 참조하세요.
// 라이브러리 설명 :  DXTK/ReadMe.txt
// 참조 : http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx
// 
// <버전>  DirecXTex, December 13, 2017 (DX11)
// <대상 플렛폼>
// Windows Desk Top Apps(Windows 7/8/10), XBox One, Windows Mobile (Windows Phone 8.1), Windows Store Apps 지원.
// <제공 기능>
//  DirectXTex, TexConv (+ColorKey), DDSViwer, DDSTextureLoader,  WICTextureLoader, ScreenGrab  
// <권장 개발환경>
//  Windows 8.x SDK, Visual Studio 2013/2015/2017 
//
//
// DirectXTex 를 보다 편하게 사용하기 위해서 Project 속성 추가가 필요합니다.
// 다음 순서대로 Project 속성을 변경/추가 하십시오.
 //
// 1. C/C++>입력>일반>추가 포함 디렉터리 : "../Yena/DXTex/Inc" 추가
// 2. 링커>일반>추가 라이브러리 디렉터리 : "../Yena/DXTex/Lib " 추가
// 3. 링커>입력>추가 종속성 : DirectXTex.lib 추가 (또는 아래와 같이 직접 명시할 것)
// 4. DirectXTex 클래스별 헤더 선언 :  여러분의 프로젝트에 필요한 헤더를 추가. (아래 참조)
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG 
	#ifdef _WIN64
		#pragma comment(lib, "DirectXTex64d")	//디버그 버전.(64bit)
	#elif _WIN32
		#pragma comment(lib, "DirectXTexd")		//디버그 버전.
	#endif
#else
	#ifdef _WIN64 
		#pragma comment(lib, "DirectXTex64")	//릴리즈 버전 (64bit)
	#elif _WIN32 
		#pragma comment(lib, "DirectXTex")		//릴리즈 버전.
	#endif
#endif


//-----------------------------------------------------------------------------
// DirectXTex 헤더 선언 : 우리 프로젝트에 필요한 것만 추가하겠습니다.
//-----------------------------------------------------------------------------
// DirectXTex 의 텍스처 API 
//
#include "DirectXTex.h"			//DirectXTK 통합 헤더.			
//#include "../../Yena/DXTex/Inc/DirectXTex.h"		//구형 배포버전과의 프로젝트 호환성을 위해 상대경로 지정.


/**************** end of "DirectXTex.h" ***********************************/