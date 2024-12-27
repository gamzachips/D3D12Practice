//
// DirectXTK.h : DirectX Toolkit 헤더
//
// DirectXTK for DX12 (Aug.15, 2020) 
// 제공 Present : Chuck Walbourn @ Microsoft / MSFT (https://walbourn.github.io/)
// 편집 Edit    : Kihong Kim / onlysonim@gmail.com 
// 갱신 Update  : 2020.08.26
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
// DirectX Took Kit  라이브러리 
//
///////////////////////////////////////////////////////////////////////////////
//
// DX 유틸리티 및 일반화 라이브러리 모음집. 
// DX 사용시 필요한 여러 기능 클래스 및 서비스를 제공합니다.
// 자세한 내용을 아래를 참조하세요.
// 라이브러리 설명 :  DXTK/ReadMe.txt
// 참조 : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
// 
// <버전> DirectXTK, December 5, 2016 (DX11)
// <대상 플렛폼>
// Windows Desk Top Apps(Windows 7/8/10), XBox One, Windows Mobile (Windows Phone 8.1), Windows Store Apps 지원.
// <제공 기능>
// Math, State Objects, Texture, EffectSystem, Model(XFile) Animation, Font, Audio (XAudio 및 Wave), 등..
// <권장 개발환경>
// Windows 8.x SDK
// Visual Studio 2013 (update 5), Visual Studio 2015 (update 3), Windows 7 (sp1) 이상.
//
//
// DirectXTK 를 보다 편하게 사용하기 위해서 Project 속성 추가가 필요합니다.
// 다음 순서대로 Project 속성을 변경/추가 하십시오.
 //
// 1. C/C++>입력>일반>추가 포함 디렉터리 : "../Yena/DXTK/Inc" 추가
// 2. 링커>일반>추가 라이브러리 디렉터리 : "../Yena/DXTK/Lib " 추가
// 3. 링커>입력>추가 종속성 : DirectXTK.lib 추가 (또는 아래와 같이 직접 명시할 것)
// 4. DirectXTK 클래스별 헤더 선언 :  여러분의 프로젝트에 필요한 헤더를 추가. (아래 참조)
//
///////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG 
	#ifdef _WIN64
		#pragma comment(lib, "DirectXTK12_64d")		//64bit + 디버그 버전.
	#elif _WIN32
		#pragma comment(lib, "DirectXTK12d")		//32bit + 디버그 버전.
	#endif
#else
	#ifdef _WIN64 
		#pragma comment(lib, "DirectXTK12_64")		//64bit 버전 
	#elif _WIN32 
		#pragma comment(lib, "DirectXTK12")			//32bit 버전.
	#endif
#endif

//-----------------------------------------------------------------------------
// DirectXTK 헤더 선언 : 우리 프로젝트에 필요한 것만 추가하겠습니다.
//-----------------------------------------------------------------------------
// DirectXTK : SimpleMath 
// SIMD 가속 지원 자료형(XMVECTOR 및 XMMATRIX)의 사용시 복잡성을 최소화한 수학 라이브러리. 
// 간편하고 직관적인 사용법으로 다소의 성능저하를 상쇄합니다.
// 참조 : https://github.com/Microsoft/DirectXTK/wiki/SimpleMath
// 
#include "SimpleMath.h"	
using namespace DirectX::SimpleMath;

// DirectXTK : SpriteFont
// 2D Texture / Sprite 기반의 폰트 출력 라이브러리.
// 빠르고 경쾌하지만, CJK 계열의 폰트의 경우 완성형만 지원됩니다.
// 참조 : Yena/DXTK/MakeSpriteFont/SpriteFont 사용법.txt
// 참조 : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
//
#include "SpriteFont.h"	
  

// DirectXTK 의 텍스처 API 
// DirectXTex 로 개발된 것이지만 기본적인 기능은 DirectXTK 에도 포함시켜 배포 중.
// DDS : dds 전용 함수 사용.
// WIC : bmp, jpg, png 등의 일반 포멧 지원.
// TGA : tga 전용 함수 사용.
// 참조1 : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
// 참좀2 : http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx
//
#include "DDSTextureLoader.h"	//DDS 전용 함수들.
#include "WICTextureLoader.h"	//WIC 전용 함수들.


// DirectXTK : DescritprHeap 
// 디스크립터-힙 운용 클래스.
//
#include "DescriptorHeap.h"



// DirectXTK : ResourceUploadBatch 
// 리소스 업로드 운용 클래스.
//
#include "ResourceUploadBatch.h"




/**************** end of "DirectXTK.h" ***********************************/