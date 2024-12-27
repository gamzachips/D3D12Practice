/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3/YENA : 2D/3D 렌더링 엔진.						                       // 
//                                                                         //
//  제 작 : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Interactive  http://www.zero-g.kr					   //	
//  초기개발 : 2003.12 - 2004.03.                                           //
//  개발환경 : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008       //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 9.0c(2007, November)                           //
//                  OpenGL 1.x / 2.x                                       //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  테스트 환경 : CPU - AMD Athlon										   //	 
//                      AMD Athlonx64 w/q4                                 // 
//                      Intel Pentium III/IV & Celeron                     //
//                      Core2 w/Quad                                       //
//                VGA - ATI Radeon 9xxx Series                             //
//                          Radeon 1xxx Series                             //
//                          Radeon HD 3/4/5/6 Series                       //
//                      nVidia GeForce 2 MX/Ti Series.                     //  
//                             GeForce 3 Ti Series.                        //
//                             GeForce 4 MX/Ti Series.                     //
//                             GeForce FX Series.                          //
//                             GeForce 5/6/7/8/9xxx Series.                //
//                             GeForce 2/4xx GTS Series.                   //
//                             GeForce 7xx GTX Series.                     //
//                             GeForce 2Way-SLI / 3Way-SLI		   	       //
//                OS - Windows 98 / 2K / XP / VISTA / Win7 x32:x64         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
// DirectX.h: DirectX SDK 필수 헤더.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04. Update.
// 2017.01. Update. B3Yena / DX11.1 (Windows SDK 8.1)
// 2020.08. Update. B3Yena / DX12.x (Windows 10 SDK 10.18362)
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma warning(disable:4996)


///////////////////////////////////////////////////////////////////////////////
//
// 윈도우즈 표준 플랫폼 헤더 및 라이브러리
//
///////////////////////////////////////////////////////////////////////////////

#include "windows.h" 
//#include "tchar.h"  
//#include "stdio.h"

//Window Runtime C++ Template Library.
//참조: https://docs.microsoft.com/en-us/cpp/cppcx/wrl/windows-runtime-cpp-template-library-wrl?view=vs-2019
#include "wrl.h"
using namespace Microsoft::WRL;
//GUID 정의 헤더 : IID_xxx 정의 사용시 DX 헤더 전에 추가해야 함.
#include "initguid.h"   





///////////////////////////////////////////////////////////////////////////////
//
// DirectX 표준 라이브러리
//
///////////////////////////////////////////////////////////////////////////////
// < DirectX 버전별 개발 라이브러리 >
// DX9         : DirectX SDK 2002 Nov.
// DX10.x/DX11 : DirectX SDK 2010 June (DX 독립 배포 마지막 버전)
// DX11.X/DX12 : Windows SDK 8.x / 10.x (DX 가 포함되어 배포됨)
// DX12.X      : Windows SDK 10.x       (DX 가 포함되어 배포됨)

// DX 표준 헤더
//#include "D3D11.h"				//DX 표준 헤더. (DX 11.0)
//#include "D3D11_1.h"				//DX 표준 헤더. (DX 11.1)
#include "D3D12.h"					//DX 표준 헤더. (DX 12.0)
//#include "D3D12_1.h"				//DX 표준 헤더. (DX 12.1)
#pragma comment(lib, "D3D12")		//DX 라이브러리 로딩.  D3D12.dll 필요.

//DirectX Math : Dx 수학 라이브러리
//#include "XNAMath.h"				//XNA Math 라이브러리.(ver.2.0) DirectX SDK 2010 June. 대응.
#include "DirectXMath.h"			//XNA Math 라이브러리.(ver.3.0) VS2012 (Windows SDK 8) 이상.
using namespace DirectX;

//DXGI : DirectX Graphics Infrastructure
//DX 의 버전에 독립적인 하드웨어 저수준 접근 방식을 제공합니다.
//#include "DXGI.h"					//DXGI 헤더. (d3d12.h 에 포함됨)
//#include "DXGI1_4.h"
#include "DXGI1_6.h"				//DXGIAdpater4 용.
#pragma comment(lib, "dxgi")		//DXGI 라이브러리. DXGI.dll 필요.

//DX 셰이더 운용 라이브러리.
#include "D3DCompiler.h"				//DX 셰이더 컴파일러 헤더.
#pragma comment(lib, "d3dcompiler")		//DX 셰이더 컴파일러 라이브러리.  D3DCompiler.dll 필요.



///////////////////////////////////////////////////////////////////////////////
//
// DirectX 확장 라이브러리 : DirectX Extensions
//
// DX 확장 라이브러리 및 유틸리티 모음집.
// 사용시 프로젝트/속성에 추가설정이 필요합니다.
// 각 확장 라이브러리 사용법을 참조. 
//
///////////////////////////////////////////////////////////////////////////////

// ■ DirectXTK  (ver. Aug.15, 2020)
// DX 유틸리티 및 일반화 라이브러리 모음집. 
// DX 사용시 필요한 여러 기능 클래스 및 서비스를 제공합니다.
// 설명1 :  DXTK/ReadMe.txt
// 설명2 :  Yena/DXTK/DirecrtXTK 사용법.txt
// 참조 : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
//
#include "DXTK.h"



// ■ DirectXTex  (ver. February 9, 2018)
// DX 텍스처 유틸리티 및 확장 라이브러리 모음집.  
// DX 텍스처 운용시 필요한 여러 기능 클래스 및 서비스를 제공합니다.
// 설명1 :  DXTex/ReadMe.txt
// 설명2 :  Yena/DXTex/DirecrtXTex 사용법.txt
// 참조 : https://blogs.msdn.microsoft.com/chuckw/2011/10/27/directxtex/
// 
//#include "DXTex.h"								//프로젝트 속성설정 필요. DirectXTex 사용법.txt 참조.

/*// 프로젝트 속성설정없이 수동접근, 사용하는 경우 
#include "../../Yena/DXTex/Inc/DirectXTex.h"		//구형 배포버전과의 프로젝트 호환성을 위해 상대경로 지정.
#ifdef _DEBUG
#pragma comment(lib, "../Yena/DXTex/Lib/DirectXTexd.lib")
#else
#pragma comment(lib, "../Yena/DXTex/Lib/DirectXTex.lib")
#endif
*/


// ■ DXErr  (ver. Nov, 2015)
// DirectX 에러 메제지 처리 라이브러리
// HRESULT 값을 문자열로 출력합니다.
// 참조 : https://blogs.msdn.microsoft.com/chuckw/2012/04/24/wheres-dxerr-lib/
//
#include "DXErr.h"


// ■ D3DX Helper  (ver. Aug.13, 2020)
// D3D 자원관련 운용 일반화 인터페이스들.
// D3DX12 Helper 등을 함께 사용함.
// 참조 : https://docs.microsoft.com/en-us/windows/win32/direct3d12/helper-structures-and-functions-for-d3d12#in-this-section
// 참조2: https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12
//
#include "D3DX12.h"			// DXHelper\D3DX12.h
//#include "D3DX12_1.h"		// DXHelper\D3DX12_1.h for DX12.1 --> Windows 10 SDK 10.0.19041 사용시 불필요.


 
/****************** end of file "DirectX.h" *******************************/