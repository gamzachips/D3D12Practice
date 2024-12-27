#pragma once
#pragma warning(disable:4996)

#include "Windows.h"
#include "stdio.h"
#include "tchar.h"

#include <memory>
#include <chrono>
using namespace std::chrono;
#define TIME_MAX  9223372036854775807

// DX 표준 헤더 
#include <d3d12.h>				//DX 표준 헤더. (DX 12.0)
#pragma comment(lib, "D3D12")		//DX 라이브러리 로딩.  D3D12.dll 필요.


#include "DirectXHelpers.h"
#include "DirectXTex.h"
//DirectX Math : Dx 수학 라이브러리 
#include "DirectXMath.h"
using namespace DirectX;

#include "dxgi1_4.h"
#include "dxgi1_6.h"				//DXGIAdpater4 용.
#pragma comment(lib, "dxgi")		//DXGI 라이브러리. DXGI.dll 필요.



//In Project
#include "Types.h"
#include "Defines.h"

