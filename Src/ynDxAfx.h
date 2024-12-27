//
//! \file   dxAfx.h
//! \brief	예나 / 엔진 / 그래픽스(DX) 헤더 및 헬퍼
//!	\details DirectX 사용 버전 : DX12
//! 
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date  2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \date  2003.11.4. 김 기홍 Kihong Kim / onlysonim@gmail.com
//! \date  2010.12.01. Update. (DX11.Jun.2010)
//! \date  2016.12.27. Update. (DX11/12 Windows SDK 8.1/10.0.x)
//! \date  2018.01.18. Update. (DX12)
//! \date  2020.08.22. Update. (DX12.x Windows 10 SDK 10.0.x)
//!
#pragma once
#pragma warning(disable:4996)

///////////////////////////////////////////////////////////////////////////////
//
// Platform Header 및 기본 Library
//
///////////////////////////////////////////////////////////////////////////////
/*
#include "windows.h"
#include "tchar.h"
#include "stdio.h"

#include "map"
#include "chrono"
using namespace std::chrono;
#define TIME_MAX  9223372036854775807
*/


///////////////////////////////////////////////////////////////////////////////
//
// 그래픽스 API 별 표준 헤더 및 확장라이브러리 운용 헤더. 
//
///////////////////////////////////////////////////////////////////////////////
#include "DirectX.h"			// DX 용 표준 헤더 및 확장 라이브러리 
//#include "Vulkan.h"			// VK 용 표준 헤더 및 확장 라이브러리 
//#include "OpenGL.h"			// GL 용 표준 헤더 및 확장 라이브러리 
//#include "Metal.h"			// Mac용 표준 헤더 및 확장 라이브러리 



namespace YENA
{
 
///////////////////////////////////////////////////////////////////////////////
//
// 그래픽스 인터페이스 및 자료형 재정의
// API 일반화를 통환 엔진의 호환성 및 이식성 증대
// 
///////////////////////////////////////////////////////////////////////////////
typedef ID3D12Device*				LPDEVICE;
//typedef ID3D11DeviceContext*		LPDXDC;
//typedef IDXGISwapChain*			LPSWAPCHAIN;
//typedef ID3D12RenderTargetView*	LPRTVIEW;
typedef ID3D12Resource*				LPRESOURCE; 
typedef LPRESOURCE					LPXBUFFER; 
typedef LPRESOURCE					LPVERTEXBUFFER; 
typedef LPRESOURCE					LPINDEXBUFFER; 
typedef LPRESOURCE					LPCONSTBUFFER;
typedef LPRESOURCE					LPTEXTURE;
typedef LPRESOURCE					LPTEXTUREBUFFER;
typedef LPVERTEXBUFFER				LPVB; 
typedef LPINDEXBUFFER				LPIB; 
typedef LPCONSTBUFFER				LPCB;
typedef LPTEXTUREBUFFER				LPTB;
typedef LPTEXTURE					LPTEX;
typedef D3D12_RESOURCE_DESC			RESOURCE_DESC;
typedef D3D12_SUBRESOURCE_DATA		SUBRESOURCE_DATA;

typedef ID3D12DescriptorHeap*		LPDESCHEAP;
typedef ID3D12DescriptorHeap*		LPDESCRIPTORHEAP;
typedef D3D12_DESCRIPTOR_HEAP_DESC	DESCRIPTOR_HEAP_DESC;
typedef D3D12_CPU_DESCRIPTOR_HANDLE	CPU_DESCHANDLE;
typedef D3D12_CPU_DESCRIPTOR_HANDLE	CPU_DESCRIPTOR_HANDLE;
typedef D3D12_GPU_DESCRIPTOR_HANDLE	GPU_DESCHANDLE;
typedef D3D12_GPU_DESCRIPTOR_HANDLE	GPU_DESCRIPTOR_HANDLE;

typedef D3D12_VERTEX_BUFFER_VIEW	VERTEXBUFFERVIEW;
typedef VERTEXBUFFERVIEW			VBVIEW;
typedef VERTEXBUFFERVIEW			VBV;
typedef D3D12_VERTEX_BUFFER_VIEW*	LPVERTEXBUFFERVIEW;
typedef LPVERTEXBUFFERVIEW			LPVBVIEW;
typedef LPVERTEXBUFFERVIEW			LPVBV;
typedef D3D12_INDEX_BUFFER_VIEW		INDEXBUFFERVIEW;
typedef INDEXBUFFERVIEW				IBVIEW;
typedef INDEXBUFFERVIEW				IBV;
typedef D3D12_INDEX_BUFFER_VIEW*	LPINDEXBUFFERVIEW;
typedef LPINDEXBUFFERVIEW			LPIBVIEW;
typedef LPINDEXBUFFERVIEW			LPIBV;

typedef D3D12_INPUT_LAYOUT_DESC		INPUTLAYOUT;
typedef D3D12_INPUT_LAYOUT_DESC*	LPINPUTLAYOUT;
//typedef LPINPUTLAYOUT				LPLAYOUT;
typedef D3D12_INPUT_ELEMENT_DESC	INPUTELEMENT;
typedef D3D12_INPUT_ELEMENT_DESC*	LPINPUTELEMENT;
//typedef LPINPUTELEMENT			LPELEMENT;

typedef ID3D12CommandAllocator*		LPCOMMANDALLOCATOR;
typedef LPCOMMANDALLOCATOR			LPCOMMANDALLOC;
typedef LPCOMMANDALLOC				LPCMDALLOC;
typedef ID3D12CommandQueue*			LPCOMMANDQUEUE;
typedef LPCOMMANDQUEUE				LPCMDQUEUE;
typedef ID3D12GraphicsCommandList*	LPGRAPHICSCOMMANDLIST;
typedef LPGRAPHICSCOMMANDLIST		LPGRAPHCMDLIST;
typedef LPGRAPHICSCOMMANDLIST		LPGRPCMDLIST;
typedef LPGRAPHICSCOMMANDLIST		LPCMDLIST;

typedef D3D12_VIEWPORT				VIEWPORT;
typedef D3D12_CLEAR_FLAGS			CLEAR_FLAGS;

// 장치 설정 정보 구조체. (DX9/10/11 구형 호환성 유지용)
//using ADAPTER_DESC = DXGI_ADAPTER_DESC1;
typedef DXGI_ADAPTER_DESC1			ADAPTER_DESC;
typedef DXGI_MODE_DESC				MODE_DESC;		//DXGI 1.0 대응
//typedef DXGI_MODE_DESC1			MODE_DESC;		//DXGI 1.1 대응
//typedef D3DDISPLAYMODE			DISPLAYMODE;	//DX9 용.

// 셰이더 관련 재정의  (DX9/10/11 구형 호환성 유지용)
//typedef ID3DBlob*  LPFXCODE;				//셰이더 코드 버퍼(컴파일욈, 이진데이터, 임시)
typedef ID3DBlob*  LPXDATA;					//셰이더 코드 버퍼(컴파일욈, 이진데이터)
typedef ID3DBlob*  LPSHADER;				//셰이더 코드 버퍼(컴파일됨, 이진데이터)
typedef LPSHADER   LPVERTEXSHADER;
typedef LPSHADER   LPPIXELSHADER;
typedef LPSHADER   LPGEOMETRYSHADER;

typedef ID3D12PipelineState*				LPPIPELINESTATE;
typedef ID3D12PipelineState*				LPPSO;
typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC	GRAPHICS_PIPELINE_STATE_DESC;
typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC	GPSO_DESC;
typedef D3D12_COMPUTE_PIPELINE_STATE_DESC	COMPUTE_PIPELINE_STATE_DESC;
typedef D3D12_COMPUTE_PIPELINE_STATE_DESC	CPSO_DESC;

typedef D3D12_GPU_VIRTUAL_ADDRESS			GPU_VIRTUAL_ADDR;
typedef D3D12_GPU_VIRTUAL_ADDRESS			GPU_VADDR;
typedef D3D12_CPU_DESCRIPTOR_HANDLE			CPU_DESCRIPTOR_HANDLE;
typedef D3D12_CPU_DESCRIPTOR_HANDLE			CPU_DESCH;

/*
// DirectX Math 타입 재정의 : 호환성 향상
// DX9/DX10 : DirectX SDK June.2010 이하
typedef D3DXMATRIXA16	MATRIXA; 
typedef D3DXMATRIX		MATRIX;	
typedef D3DXVECTOR4		VECTOR4;
typedef D3DXVECTOR3		VECTOR3;
typedef D3DXVECTOR2		VECTOR2;
*/
// DirectX Math 타입 재정의 : 구형 소스와의 호환성 향상이 목적.
typedef XMMATRIX		MATRIXA; 
typedef XMFLOAT4X4		MATRIX; 
typedef XMVECTOR		VECTOR; 
typedef XMFLOAT4		VECTOR4; 
typedef XMFLOAT3		VECTOR3;
typedef XMFLOAT2		VECTOR2;

//색상 타입: 2가지.
//typedef XMCOLOR		Color;		// r, g, b, a.  [정수형 0~255]
//typedef XMFLOAT4		Color;		// r, g, b, a.  [실수형 0~1.0]





///////////////////////////////////////////////////////////////////////////////
//
//! \brief	예나 / 엔진 / 헬퍼 네임스페이스
//!	\details 생산성 향상을 위한 다양한 상수, 함수, 보조 클래스(Helper) 및 
//!			서드파티 라이브러리가 준비되어 있습니다.
//! 
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com 
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
//
///////////////////////////////////////////////////////////////////////////////
namespace Helpers
{

//////////////////////////////////////////////////////////////////////////////////
//
//! \class	Color
//! \brief	예나 / 엔진 / 색상 클래스
//! \details 4가지 색상 성분(R,G,B,A)을 가지는 벡터 데이터입니다.
//!			직관적인 사용과 표현식을 위해 특별히 클래스화 하였으며
//!			기존 DirectX 자료형과의 호환성도 지원하고 있습니다.
//!			DirectXTK 가 제공하는 \b Color 클래스도 함께 살펴보길 바랍니다.
//! \see	DirectX::SimpleMath::Color 
//! \note	이 클래스의 산술 연산자들은 SIMD 버전으로 제작하였습니다. 
//!			SISD 와 SIMD 방식의 장단점을 연구해 봅시다.
//! 
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
//
////////////////////////////////////////////////////////////////////////////////
struct ynColor
{
	union
	{
		struct { float r, g, b, a; };
		struct { float x, y, z, w; };
		float    c[4];
		XMFLOAT4 v;
	};

#if defined( __cplusplus )
	ynColor() noexcept :r(1), g(1), b(1), a(1) {}
	explicit ynColor(float _r, float _g, float _b, float _a = 1.0f) noexcept :r(_r), g(_g), b(_b), a(_a) {}
	explicit ynColor(float _c[4]) noexcept :r(_c[0]), g(_c[1]), b(_c[2]), a(_c[3]) {}
	explicit ynColor(const XMFLOAT4& _v) noexcept :v(_v) {}
	//explicit Color(const XMFLOAT4& _v) noexcept: r(_v.x), g(_v.y), b(_v.z), a(_v.w) {}
	ynColor(const XMVECTOR& _v) noexcept { XMStoreFloat4(&v, _v); }

	//virtual ~Color() = default;
	ynColor(ynColor&) = default;
	ynColor& operator = (const ynColor&) = default;
	ynColor(ynColor&&) = default;
	ynColor& operator = (ynColor&&) = default;

	//operator XMFLOAT4 () const noexcept { return XMFLOAT4(r, g, b, a); }
	operator XMFLOAT4 () const noexcept { return v; }
	operator XMVECTOR () const noexcept { return XMLoadFloat4(&v); }
	operator const float* () const noexcept { return c; }
	//operator	   float* () noexcept { return c; }

	//operator XMFLOAT4 () { return XMFLOAT4(a, b, g, r); }
	//Color operator = (XMFLOAT4)
	
	//---------------------------------------------------------------------
	// 다음의 인터페이스들은 SISD 및 SIMD 버전으로 제작하였습니다.
	// 두 버전을 비교하고 장단점을 연구해 봅시다. (연구 과제)
	//---------------------------------------------------------------------
	//! 색상과 스칼라 곱셈 연산자. \n
	//! SIMD 타입1 : SSE/AVX 명령어 사용 (정렬형)
	//! \n\n 
	//! \b 예문 
	//! \code  
	//! Color col;  
	//! col = col * 0.5f; 
	//! \endcode
	ynColor operator * (float s)
	{
		float col[4];
		__m128 v0, v1, v2;
		__declspec(align(16)) float a1[] = { r, g, b, a };
		__declspec(align(16)) float a2[] = { s, s, s, s };
		v1 = _mm_load_ps(a1);
		v2 = _mm_load_ps(a2);
		v0 = _mm_mul_ps(v1, v2);
		_mm_storeu_ps(col, v0);
		return ynColor(col);
	}

	/*// SIMD 타입2 : SSE/AVX 명령어 사용 (비정렬형)
	Color operator * (float s)
	{
		Color col;
		__m128 v0, v1, v2;

		//...(연구과제)...

		return col;
	}

	// 색상 * 스칼라 곱  (ex)  col = col * 0.5f
	// SISD 타입 : 일반 명령어 사용.
	/*Color operator * (float s)
	{
		Color col;
		col.r = r * s;
		col.g = g * s;
		col.b = b * s;
		col.a = a * s;
		return col;
	}*/

#endif	//__cplusplus
};	//end of ynColor

using Color = YENA::Helpers::ynColor;


//! \namespace	gp3::Helpers::colors
//! \brief		예나 / 엔진 / 색상 네임스페이스
//! \details	Color 색상 객체들이 미리 정의되어 있으며 엔진 전체에서 공유됩니다.
//! \ingroup Yena
namespace colors {

	GLOBALCONST Color black		(0, 0, 0, 1);
	GLOBALCONST Color white		(1, 1, 1, 1);				//100% white
	GLOBALCONST Color silverlt	(0.9f, 0.9f, 0.9f, 1);		//90% white : Light Silver
	GLOBALCONST Color silver	(0.7f, 0.7f, 0.7f, 1);		//70% white : 
	GLOBALCONST Color gray		(0.5f, 0.5f, 0.5f, 1);		//50% white : gray
	GLOBALCONST Color graydk	(0.3f, 0.3f, 0.3f, 1);		//30% white : Dark-gray
	GLOBALCONST Color graydp	(0.15f, 0.15f, 0.15f, 1);	//15% white : Deep-gray 

	GLOBALCONST Color red		(1.0f, 0.0f, 0.0f, 1);
	GLOBALCONST Color reddk		(0.5f, 0.0f, 0.0f, 1);		//Dark-red
	GLOBALCONST Color green		(0.0f, 1.0f, 0.0f, 1);
	GLOBALCONST Color greendk	(0.0f, 0.5f, 0.0f, 1);		//Dark-pink
	GLOBALCONST Color blue		(0.0f, 0.0f, 1.0f, 1);
	GLOBALCONST Color bluedk	(0.0f, 0.0f, 0.5f, 1);		//Dark-blue
	GLOBALCONST Color bluedp	(0.0f, 0.125f, 0.3f, 1);	//Deep-blue 

	GLOBALCONST Color yellow	(1, 1, 0, 1);
	GLOBALCONST Color yellowdk	(0.5f, 0.5f, 0, 1);			//Dark-yellow.
	GLOBALCONST Color pink		(1.0f, 0.5f, 1.0f, 1);
	GLOBALCONST Color pinkdk	(0.5f, 0.2f, 0.5f, 1);		//Dark-pink
	GLOBALCONST Color cyan		(0.0f, 1.0f, 1.0f, 1);
	GLOBALCONST Color cyandk	(0.0f, 0.5f, 0.5f, 1);		//Dark-cyan
	GLOBALCONST Color orange	(1.0f, 0.6f, 0.0f, 1);
	GLOBALCONST Color orangedk	(0.5f, 0.3f, 0.0f, 1);		//Dark-orange

	//기본 배경색.
	GLOBALCONST Color& bgBlue = bluedp;		//Deep-blue
	GLOBALCONST Color& bgGray = graydp;		//Deep-gray

	//색상 추가는 여기에...
	//...

};
using namespace colors;

#define ynColorTest(_x, _y, _col) \
	ynTextDraw(_x, _y, _col, _T("%s = {%.2f, %.2f, %.2f, %.2f}"), ynToString(_col), _col.x, _col.y, _col.z, _col.w)		
	//ynTextDraw(_x, _y, _col, _T("%s = {%.2f, %.2f, %.2f, %.2f}"), toString(_col), _col.r, _col.g, _col.b, _col.a)




///////////////////////////////////////////////////////////////////////////////
//
// DX 및 장치 관련 전역 데이터  
//
///////////////////////////////////////////////////////////////////////////////

//...



///////////////////////////////////////////////////////////////////////////////
//
// DX Helper 클래스 추가 재정의 
//
// d3dx12.h 에 기술되지 않은 헬퍼의 추가 및 개선
// DX Helper 스타일을 최대한 준수.
// 김기홍 Kihong Kim / Update. 2018.08.22
//
///////////////////////////////////////////////////////////////////////////////
#if defined( __cplusplus )

#ifndef CDXGI_SWAP_CHAIN_DESC1
	struct CDXGI_SWAP_CHAIN_DESC1 : DXGI_SWAP_CHAIN_DESC1
	{
		CDXGI_SWAP_CHAIN_DESC1() = default;
		explicit CDXGI_SWAP_CHAIN_DESC1(const DXGI_SWAP_CHAIN_DESC1& o) noexcept :
			DXGI_SWAP_CHAIN_DESC1(o) 
		{}
		CDXGI_SWAP_CHAIN_DESC1(
			UINT width,
			UINT height,
			DXGI_FORMAT format,
			BOOL stereo = FALSE,
			DXGI_SAMPLE_DESC sampleDesc = { 1, 0 },
			DXGI_USAGE bufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
			UINT bufferCount = 2,
			DXGI_SCALING scaling = DXGI_SCALING_STRETCH,
			DXGI_SWAP_EFFECT swapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
			DXGI_ALPHA_MODE alphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
			UINT flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
		) noexcept
		{
			Width = width;
			Height = height;
			Format = format;
			Stereo = stereo;
			SampleDesc = sampleDesc;
			BufferUsage = bufferUsage;
			BufferCount = bufferCount;
			Scaling = scaling;
			AlphaMode = alphaMode;
			Flags = flags;
		}
		CDXGI_SWAP_CHAIN_DESC1(
			UINT width, UINT height, DXGI_FORMAT format, 
			DXGI_SWAP_EFFECT swapEffect, UINT bufferCount = 2, UINT samplerCount = 1
		) noexcept
		{
			Width = width;  Height = height;  Format = format;
			Stereo = FALSE;
			SampleDesc = { samplerCount, 0 };
			BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			BufferCount = bufferCount;
			Scaling = DXGI_SCALING_STRETCH;
			SwapEffect = swapEffect;
			AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		}
		CDXGI_SWAP_CHAIN_DESC1(
			const DXGI_MODE_DESC& m,
			DXGI_SWAP_EFFECT swapEffect, UINT bufferCount = 2, UINT samplerCount = 1
		) noexcept
		{
			Width = m.Width;  Height = m.Height;  Format = m.Format;
			Stereo = FALSE;
			SampleDesc = { samplerCount, 0 };
			BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			BufferCount = bufferCount;
			Scaling = DXGI_SCALING_STRETCH;
			SwapEffect = swapEffect;
			AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		}
		/*CDXGI_SWAP_CHAIN_DESC1( const DXGI_MODE_DESC& md ) noexcept : 		 
		{
			//CDXGI_SWAP_CHAIN_DESC1(md.Width, md.Height, md.Format);
		}*/
		static inline CDXGI_SWAP_CHAIN_DESC1 FlipModel(UINT width, UINT height, DXGI_FORMAT format, UINT buffCount = 2, UINT samplerCount = 1)
		{
			return CDXGI_SWAP_CHAIN_DESC1(width, height, format, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, buffCount, samplerCount);
		}
		static inline CDXGI_SWAP_CHAIN_DESC1 FlipModel(const DXGI_MODE_DESC& mode, UINT buffCount = 2, UINT samplerCount = 1)
		{
			return CDXGI_SWAP_CHAIN_DESC1(mode, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, buffCount, samplerCount);
		}
		static inline CDXGI_SWAP_CHAIN_DESC1 DiscardModel(const DXGI_MODE_DESC& mode, UINT buffCount = 2, UINT samplerCount = 1)
		{
			return CDXGI_SWAP_CHAIN_DESC1(mode, DXGI_SWAP_EFFECT_FLIP_DISCARD, buffCount, samplerCount);
		}

	};
#endif


#ifndef CD3DX12_DESCRIPTOR_HEAP_DESC
	struct CD3DX12_DESCRIPTOR_HEAP_DESC : D3D12_DESCRIPTOR_HEAP_DESC
	{
		CD3DX12_DESCRIPTOR_HEAP_DESC() = default;
		explicit CD3DX12_DESCRIPTOR_HEAP_DESC(const D3D12_DESCRIPTOR_HEAP_DESC& o) noexcept :
			D3D12_DESCRIPTOR_HEAP_DESC(o)
		{}
		CD3DX12_DESCRIPTOR_HEAP_DESC(
			D3D12_DESCRIPTOR_HEAP_TYPE type,
			UINT numDescriptors,
			D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			UINT nodeMask = 0
		) noexcept
		{
			Type = type;
			NumDescriptors = numDescriptors;
			Flags = flags;
			NodeMask = nodeMask;
		}
	};
#endif


	// 리소스 뷰 
	// D3D12 에는 정의되어 있지 않지만 VB/IB/Texture 운용의 통일성을 위해 정의함.
	//
#ifndef CD3DX12_RESOURCE_VIEW
	struct CD3DX12_RESOURCE_VIEW
	{
		//...
	};

	//typedef D3D12_RESOURCE_VIEW RESOURCEVIEW;
	//typedef void* LPRESOURCEVIEW;
#endif


#ifndef CD3DX12_CONSTANT_BUFFER_VIEW
	// 상수버퍼 뷰 
	// D3D12 에는 정의되어 있지 않지만 VB/IB/Texture 운용의 통일성을 위해 정의함.
	// 참고 : D3D12_CONSTANT_BUFFER_VIEW_DESC https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_constant_buffer_view_desc
	struct CD3DX12_CONSTANT_BUFFER_VIEW
	{
		D3D12_GPU_VIRTUAL_ADDRESS BufferLocation = 0;		//버퍼 위치.
		UINT SizeInBytes = 0;								//버퍼 크기 (+정렬)
		UINT StrideInBytes = 0;								//요소 크기 (배열구성시 요소1개의 크기)(+정렬)
	};

	typedef CD3DX12_CONSTANT_BUFFER_VIEW		CONSTANTBUFFERVIEW;
	typedef CONSTANTBUFFERVIEW					CBVIEW;
	typedef CONSTANTBUFFERVIEW					CBV;
	typedef CD3DX12_CONSTANT_BUFFER_VIEW*		LPCONSTANTBUFFERVIEW;
	typedef LPCONSTANTBUFFERVIEW				LPCBVIEW;
	typedef LPCONSTANTBUFFERVIEW				LPCBV;
	typedef D3D12_CONSTANT_BUFFER_VIEW_DESC		CONSTANT_BUFFER_VIEW_DESC;
#endif



	// 추가 헬퍼는 여기에...
	// ...



#endif // defined( __cplusplus )







///////////////////////////////////////////////////////////////////////////////
//
// 수학 헬퍼 클래스.
//
///////////////////////////////////////////////////////////////////////////////
// 다음의 인터페이스들은 SISD 및 SIMD 버전으로 제작하였습니다.
// 일반 버전과 의 SIMD 타입 헬퍼와 비교해 봅시다. (연구 과제)
// Color operator *  (Color& lhs, float s);
// Color operator +  (Color& lhs, float s);
// Color operator -  (Color& lhs, float s);
// Color operator *= (Color& lhs, float s);
// Color operator += (Color& lhs, float s);
// Color operator -= (Color& lhs, float s);
// ... 




}//end of namespace Helpers.
using namespace Helpers;






//////////////////////////////////////////////////////////////////////////////// 
//
//! \brief		예나 / 엔진 / 리소스 네임스페이스
//! \details	렌더링 자원 및 버퍼 운용을 위한 매크로, 함수 및 클래스가 정의되어 있습니다.
//! \remark	그래픽스 API 의 일반화(Generic)를 통해 직관적이고 단순한 구조를 유지하며
//!				복잡한 (자동화) 클래스 설계는 지양하였습니다. \n
//!	\note		여러분이 만든 자원은 여러분이 제거해야 합니다. \n 
//!				안전한 자원관리는 개발자의 중요 덕목이며 본 교재의 교육목표 중의 하나이다.
//! 
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
// 
////////////////////////////////////////////////////////////////////////////////
namespace Resources
{
	static int ynUpdateBuffer(LPXBUFFER pBuff, LPVOID pData, UINT size);

	//! 새 버퍼를 생성합니다.
	//! \param pDev		D3D 장치
	//! \param size		생성할 버퍼 크기
	//! \param ppBuff	생성된 버퍼를 돌려받을 (리소스) 포인터
	//! \return 성공시 OK, 실패시 FAIL.
	//!
	static int ynCreateBuffer( LPDEVICE pDev, UINT size, out LPXBUFFER* ppBuff )
	{
		try 
		{
			ID3D12Resource* buff = nullptr;
			ynChkFailed(pDev->CreateCommittedResource( 
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
						D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(size),
						D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&buff))); 
			*ppBuff = buff;
		}
		catch (ynError& e)
		{
			ynError(e, _T("버퍼 생성 실패"));
			return e.hr();
		}

		return YN_OK;
	}


	//! 새 버퍼를 생성합니다.
	//! \param pDev		D3D 장치
	//! \param pCmdList 커맨드 리스트
	//! \param rd		리소스 디스크립터 
	//! \param srd		서브 리소스 데이터 
	//! \param ppBuff	생성된 버퍼를 돌려받을 (리소스) 포인터
	//! \return 성공시 OK, 실패시 FAIL.
	//! 
	static int ynCreateBuffer( LPDEVICE pDev, LPGRPCMDLIST pCmdList, 
							 RESOURCE_DESC& rd, SUBRESOURCE_DATA& srd, out LPXBUFFER* ppBuff )
	{
		try 
		{
			ID3D12Resource* pHB = nullptr;
			ynChkFailed(pDev->CreateCommittedResource(
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
						D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_COMMON, 
						nullptr, IID_PPV_ARGS(&pHB)));
			ID3D12Resource* pUB = nullptr;
			ynChkFailed(pDev->CreateCommittedResource(
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
						D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr, IID_PPV_ARGS(&pUB)));
			pCmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pHB,
						D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			UpdateSubresources<1>(pCmdList, pHB, pUB, 0, 0, 1, &srd);
			pCmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pHB,
						D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

			//작업대기 & 임시 버퍼 제거
			//...

			*ppBuff = pHB;
		}
		catch (ynError& e)
		{
			ynError(e, _T("버퍼 생성 실패"));
			return e.hr();
		}

		return YN_OK;
	}


	//! 새 버퍼를 생성하고 지정된 데이터로 버퍼를 채운다.
	//! \param pDev		D3D 장치
	//! \param pData	버퍼에 저장할 데이터.
	//! \param size		생성할 버퍼 크기
	//! \param ppBuff	생성된 버퍼를 돌려받을 (리소스) 포인터
	//! \return 성공시 OK, 실패시 FAIL.
	//! 
	static int ynCreateBuffer( LPDEVICE pDev, LPVOID pData, UINT size, out LPXBUFFER* ppBuff )
	{
		try
		{
			LPXBUFFER pUB = nullptr;
			ynChkFailed(ynCreateBuffer(pDev, size, &pUB));
			ynChkFailed(ynUpdateBuffer(pUB, pData, size));

			*ppBuff = pUB;
		}
		catch (ynError& e)
		{
			ynError(e, _T("버퍼 생성 실패"));
			return e.hr();
		}

		return YN_OK;
	}


	//! 지정된 데이터로 버퍼를 갱신합니다.
	//! \param pBuff	갱신할 버퍼 포인터
	//! \param pData	버퍼에 저장할 데이터.
	//! \param size		저장할 데이터의 크기
	//! \return 성공시 OK, 실패시 FAIL.
	//! 
	static int ynUpdateBuffer(LPXBUFFER pBuff, LPVOID pData, UINT size)
	{
		HRESULT hr = S_YN_OK;
		if (pData == nullptr) return hr;

		UINT8* buff = nullptr;
		hr = pBuff->Map(0, nullptr, (void**)&buff);
		if (FAILED(hr) || buff == nullptr)
		{
			ynError(hr, _T("버퍼 갱신 실패. \npBuff=0x%x Size=%d"), buff, size);
			return hr;
		}
		memcpy(buff, pData, size);	 
		pBuff->Unmap(0, nullptr);

		return hr;
	}

	//! 버퍼를 제거합니다. 
	//! \param rpBuff  제거할 버퍼
	//! 
	static void ynReleaseBuffer(LPXBUFFER& rpBuff)
	{
		safeRelease(rpBuff);
	}


	//! 입력된 \a size 를  \a align 만큼 정렬합니다.  
	//! \param	size	정렬할 값.  
	//! \param	align	졍렬 기준값. 
	//! \return UINT 정렬된 값
	//! \remark 이 함수는 버퍼(크기) 정렬에 사용됩니다.
	//!			메모리 운용의 효율성을 위해 256 바이트 정렬을 권장합니다.
	//! 
	static UINT ynSizeAligned(UINT size, UINT align)
	{
		align -= 1;
		return (size + align) & ~align;
	}

	//! 입력된 \a size 를 256(바이트)으로 정렬합니다.  
	//! \param size 정렬할 값.  
	//! \return UINT 정렬된 값
	//! \remark 이 함수는 버퍼(크기) 정렬에 사용됩니다.
	//!			메모리 운용의 효율성을 위해 256 바이트 정렬을 권장합니다.
	//! 
	static UINT ynSizeAligned(UINT size)
	{
		return (size + 255) & ~255;
	}


	//////////////////////////////////////////////////////////////////////////////// 
	//
	// 버퍼류 자원 공통 인터페이스.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	/*struct ynIBuffer
	{
		LPRESOURCE			pRes = nullptr;
		LPVOID				pView = nullptr;
		//LPRESOURCEVIEW		pView = nullptr;
		//LPRESOURCEVIEW		pView = {};
		//UINT				uSize = 0;
		
		//...
	};*/


	//////////////////////////////////////////////////////////////////////////////// 
	//
	// 정점 버퍼 운용 인터페이스.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	ynVertexBuffer
	//! \brief	예나 / 엔진 / 정점 버퍼 구조체 
	//! \details VB 및 VBV 운용 정보 구조체.
	//! \sample def_VB
	//! \remark 자료형의 이름은 관례적인 '정점 버퍼'를 따르지만 구조체 내에는
	//!			D3D12 렌더링시 필요한 VB 및 VBV 를 모두 포함하고 있습니다.
 	//!			또 간단하고 직관적인 표현식을 위해 내부 인터페이스는 추가하지 않았습니다.\n
	//!			ynConstantBuffer 클래스를 참고하여 여러분이 직접 추가해보기 바랍니다.
	//! \see ynIndexBuffer, ynConstantBuffer
	//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena 
	struct ynVertexBuffer
	{
		LPXBUFFER			pBuff = nullptr;		//!< 정점 버퍼
		LPVERTEXBUFFERVIEW	pView = nullptr;		//!< 정점 버퍼-뷰
	};
	

	//////////////////////////////////////////////////////////////////////////////// 
	//
	// 색인 버퍼 운용 인터페이스.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	ynIndexBuffer
	//! \brief	예나 / 엔진 / 색인 버퍼 구조체 
	//! \details IB 및 IBV 운용 정보 구조체.
	//! \sample def_IB
	//! \remark 자료형의 이름은 관례적인 '색인 버퍼'를 따르지만 구조체 내에는
	//!			D3D12 렌더링시 필요한 IB 및 IBV 를 모두 포함하고 있습니다.
 	//!			또 간단하고 직관적인 표현식을 위해 내부 인터페이스는 추가하지 않았습니다. \n
	//!			ynConstantBuffer 클래스를 참고하여 여러분이 직접 추가해보기 바랍니다.
	//! \see ynVertexBuffer, ynConstantBuffer
	//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena
	struct ynIndexBuffer 
	{
		LPXBUFFER			pBuff = nullptr;		//!< 색인 버퍼
		LPINDEXBUFFERVIEW	pView = nullptr;		//!< 색인 버퍼-뷰
	};

	//////////////////////////////////////////////////////////////////////////////// 
	//
	// 상수 버퍼 운용 인터페이스.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	/*struct ynConstantBuffer
	{ 
		LPRESOURCE			pRes = nullptr;
		CONSTANTBUFFERVIEW	view = {};
	};*/

	//////////////////////////////////////////////////////////////////////////////// 
	//
	// 상수 버퍼 운용 인터페이스.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	_mdata
	//! \brief	예나 / 엔진 / 메타 데이터 템플릿
	//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena
	template<typename T>
	struct _mdata : T
	{
		_mdata() noexcept = default;
		virtual ~_mdata() = default;		
		operator T() {	return *(T*)this;	}
		virtual void set	(T& data)	{ *(T*)this = data;	}	
		virtual T*   data	()			{ return this;		} 
		virtual UINT size	()			{ return sizeof(T);	}
		virtual UINT alignOf()			{ return alignof(T);}
	};
	
	
	//-------------------------------------------------------------------
	// 상수 버퍼 클래스 템플릿
	//-------------------------------------------------------------------
	//! \class	ynConstantBuffer
	//! \brief	예나 / 엔진 / 상수 버퍼 클래스 템플릿
	//! \details CB 및 CBV 를 운용하며 템플릿 상수 데이터 T 를 포함하고 있습니다.
	//! \tparam	 T	상수 메타 데이터 YENA::Resources::_mdata<T>
	//!
	//! \sample     def_CB
	//! 
	//! \note 모든 예제는 가능한 간단하고 직관적인 표현식 사용을 지향하고 있습니다. \n
	//!		하지만,	상수 버퍼는 셰이더 문법 및 표현식과의 일체감을 위해서 특별히 템플릿화 하였습니다. \n
	//!		실용성보다는 예제를 위한 디자인임을 눈치 채주면 고맙겠습니다. \emoji sunglasses \n 
	//!		2020.08.22 김기홍 Kihong.Kim
	//! 
	//! \b 사용예 : 애플리케이션 (demo.cpp)
	//! \sample     sample_CB1
	//! 
	//! \b 사용예 : 셰이더 (demo.fx)  
	//! \sample     sample_CB2
	//!
	//! \see		YENA::Resources::_mdata,  ynVertexBuffer, ynIndexBuffer
	//!
	//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena
	//!   
	template<typename T>
	struct ynConstantBuffer : _mdata<T>
	{
		LPXBUFFER pBuff = nullptr;
		CONSTANT_BUFFER_VIEW_DESC  viewDesc = {};

		ynConstantBuffer() = default;
		virtual ~ynConstantBuffer() { safeRelease(pBuff);		}
		virtual void			 set	(LPXBUFFER _buff)	{ pBuff = _buff;	}	
		virtual LPXBUFFER&		 get	()					{ return pBuff;		}		 
		virtual GPU_VIRTUAL_ADDR addr	()					{ return pBuff->GetGPUVirtualAddress();	}
		virtual GPU_VIRTUAL_ADDR view	()					{ return addr();	}		
		virtual GPU_VIRTUAL_ADDR getGPUVirtualAddress	()	{ return addr();	}
 	};

	//template<typename T> int  createConstantBuffer	(out ConstantBuffer<T>** ppCB);
	//template<typename T> int  updateConstantBuffer	(ConstantBuffer<T>* pCB);
	//template<typename T> void releaseConstantBuffer	(ConstantBuffer<T>*& rpCB);


	//-------------------------------------------------------------------
	// 상수 버퍼 운용 함수 템플릿
	//-------------------------------------------------------------------
	//! 상수버퍼를 생성합니다.
	//! \tparam T		데이터 타입.
	//! \param	pDev	D3D 장치.
	//! \param	ppCB	생성된 상수버퍼를 돌려받을 객체의 포인터.
	//! \return 성공시 OK, 실패시 FAIL.
	//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	template<typename T>
	int ynCreateConstantBuffer(LPDEVICE pDev, out ynConstantBuffer<T>** ppCB)
	{
		try
		{
			UINT size = sizeof(T);
			UINT sizeA = ynSizeAligned(size); 
			ID3D12Resource* pBuff = nullptr;
			ynChkFailed(ynCreateBuffer(pDev, sizeA, &pBuff));
			ynChkFailed(ynUpdateBuffer(pBuff, &T{}, sizeA));
			//ynChkFailed(createBuffer(pDev, sizeof(T), &pBuff));
			//ynChkFailed(updateBuffer(pBuff, &T{}, sizeof(T)));		
			ynConstantBuffer<T>* pCB = new ynConstantBuffer<T>; 	
			assert(pCB != NULL);
			pCB->set(pBuff);		 

			*ppCB = pCB;
		}
		catch (ynError& e)
		{
			ynError(e, _T("ConstantBuffer<%s> 생성 실패"), toString(T));
			return e.hr();
		}

		return YN_OK;
	}

	//! 상수버퍼를 생성합니다.
	//! \tparam T		데이터 타입.
	//! \param pDev		D3D 장치.
	//! \param pData	저장할 상버 데이터.
	//! \param size		생성할 버퍼 크기.
	//! \param cnt		버퍼에 저장될 요소의 크기.
	//! \param ppCB		생성된 상수버퍼를 돌려받을 포인터.
	//! \param pSizeAligned	버퍼의 정렬된 크기를 돌려받을 변수 포인터.
	//! \return 성공시 OK, 실패시 FAIL.
	//! 
	template<typename T>
	int ynCreateConstantBuffer(LPDEVICE pDev, LPVOID pData, UINT size, UINT cnt, 
								out LPXBUFFER* ppCB, out UINT* pSizeAligned)
	{
		UINT sizeA = ynSizeAligned(size); 
		UINT totSizeA = sizeA * cnt;
		try
		{
			LPXBUFFER pCB = nullptr;
			ynChkFailed(ynCreateBuffer(pDev, totSizeA, &pCB));
			ynChkFailed(ynUpdateBuffer(pCB, pData, totSizeA));
			//ynChkFailed(Error::test(1, 2, _T("createCB-Array 실패!")));
			*ppCB = pCB;
			*pSizeAligned = sizeA;
		}Z
		catch (ynError& e)
		{
			ynError(e, _T("ConstantBuffer<%s> 생성 실패 : \n" 
						"Element[%d] : Size=%d Aligned=%d Total=%dBytes"), 
						ynToString(T), cnt, size, sizeA, totSizeA);
			return e.hr();
		}

		return YN_OK;
	}

	//! 상수버퍼 객체를 갱신합니다. 객체 내부 상수 데이터로 버퍼를 갱신합니다.
	//! \tparam T		데이터 타입.
	//! \param pCB		갱신할 상수버퍼 객체.
	//! \return 성공시 OK, 실패시 FAIL.
	//! 
	template<typename T>
	int ynUpdateConstantBuffer(ynConstantBuffer<T>* pCB)
	{
		return ynUpdateBuffer(pCB->get(), pCB->data(), pCB->size());
	}

	//! 상수버퍼 객체를 제거합니다. 내부 데이터 및 버퍼도 함께 제거됩니다.
	//! \tparam T		데이터 타입.
	//! \param	rpCB	제거할 상수버퍼 객체.
	//! \return 없음.
	//! 
	template<typename T>
	void ynReleaseConstantBuffer(ynConstantBuffer<T>*& rpCB)
	{
		safeDelete(rpCB);
	}

	//! 상수버퍼 객체를 제거합니다. 내부 데이터 및 버퍼도 함께 제거된다
	//! \tparam T		데이터 타입
	//! \param	rCB		제거할 상수버퍼 객체.
	//! \return 없음.
	//! 
	template<typename T>
	void ynReleaseConstantBuffer(ynConstantBuffer<T>& rCB)
	{
		safeRelease(rCB.pBuff);
	}


	//////////////////////////////////////////////////////////////////////////////// 
	//
	// 텍스처 운용 인터페이스.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	ynTexture
	//! \brief	예나 / 엔진 / 텍스처 클래스
	//! \details
	//! \ingroup Yena
	//! 
	struct ynTexture //: public IBuffer
	{
		//...
	};

	//! 텍스처를 로드합니다.
	//! 
	static int ynCreateTexture  () 
	{ 
		//...
		return YN_OK;
	}
	
	//! 텍스처를 제거합니다.
	//! 
	static int ynReleaseTexture () 
	{
		//...
		return YN_OK;
	}


};//end of namespace Resources

using namespace Resources;





///////////////////////////////////////////////////////////////////////////////
//
// 에러 / 예외처리 클래스.
//
///////////////////////////////////////////////////////////////////////////////

//... ynError.h 참조.
 




///////////////////////////////////////////////////////////////////////////////
//
// 폰트 인터페이스.
//
///////////////////////////////////////////////////////////////////////////////

//... ynFont.h 참조.




}// end of namespace YENA


using namespace YENA;


/**************** The end of file : "dxAfx.h" *********************************/