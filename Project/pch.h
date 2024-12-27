#pragma once
#pragma warning(disable:4996)

#include "Windows.h"
#include "stdio.h"
#include "tchar.h"

#include <memory>
#include <chrono>
using namespace std::chrono;
#define TIME_MAX  9223372036854775807

// DX ǥ�� ��� 
#include <d3d12.h>				//DX ǥ�� ���. (DX 12.0)
#pragma comment(lib, "D3D12")		//DX ���̺귯�� �ε�.  D3D12.dll �ʿ�.


#include "DirectXHelpers.h"
#include "DirectXTex.h"
//DirectX Math : Dx ���� ���̺귯�� 
#include "DirectXMath.h"
using namespace DirectX;

#include "dxgi1_4.h"
#include "dxgi1_6.h"				//DXGIAdpater4 ��.
#pragma comment(lib, "dxgi")		//DXGI ���̺귯��. DXGI.dll �ʿ�.



//In Project
#include "Types.h"
#include "Defines.h"

