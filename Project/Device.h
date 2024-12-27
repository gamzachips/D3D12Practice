#pragma once

class Device
{
public:
	//DX
	bool DXSetup(HWND hWnd);
	void DXRelease();
	HRESULT CreateDeviceSwapChain(HWND hWnd);
	HRESULT CreateRenderTarget();
	void SetViewPort();

	//Commands
	
	bool CommandsCreate(); //커맨드 객체를 생성합니다. 
	bool CommandsReset();
	bool CommandsExcute();
	void CommandsRelease();

	//GPUSync
	bool GPUSyncObjsCreate(); //동기화 객체를 생성합니다. 
	void GPUSyncObjsRelease();
	bool GPUSync();

	//Double -buffering
	bool ClearBackBuffer(COLOR col);
	bool Flip();

	//Time
	float GetEngineTime();

	//void GetDeviceInfo();
	//void GetFeatureLevel();

private:
	IDXGIAdapter4* mAdapter = nullptr;
	ID3D12Device* mDevice = nullptr;
	IDXGISwapChain4* mSwapChain = nullptr;
	ID3D12CommandQueue* mCommandQueue = nullptr;
	ID3D12CommandAllocator* mCommandAllocator = nullptr;
	ID3D12GraphicsCommandList* mCommandList = nullptr;

	DXGI_MODE_DESC mMode = {960, 600, 0, 1, DXGI_FORMAT_R8G8B8A8_UNORM};
	HWND hWnd;
	BOOL mShowFrame;

	BOOL mWindowMode; //전체화면 사용 여부 
	BOOL mVSync; //수직 동기화 사용 여부 

	//double buffering
	static constexpr UINT mRTCount = 2;
	UINT mRTDescSize = 0;
	UINT mRTIndex = 0;
	ID3D12DescriptorHeap* mRTDescHeap = nullptr;
	ID3D12Resource* mRT[mRTCount]{};

	//rendering sync
	ID3D12Fence* mFence = nullptr;
	UINT64 mFenceValue = 0;
	HANDLE mFenceEvent = nullptr;

	//viewport
	D3D12_VIEWPORT mViewport;

	// AA & AF option
	DWORD		mAA = 1;
	DWORD		mAF = 1;
	BOOL		mMipMap = true;
};
