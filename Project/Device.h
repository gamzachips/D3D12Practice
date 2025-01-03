#pragma once

struct VertexBuffer
{
	ID3D12Resource* pBuff = nullptr;
	D3D12_VERTEX_BUFFER_VIEW view = {};
};

struct IndexBuffer
{
	ID3D12Resource* pBuff = nullptr;
	D3D12_INDEX_BUFFER_VIEW	view = {};
};

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
	bool CommandsCreate();
	bool CommandsReset();
	bool CommandsExcute();
	void CommandsRelease();

	//GPUSync
	bool GPUSyncObjsCreate(); 
	void GPUSyncObjsRelease();
	bool GPUSync();

	//Double -buffering
	bool ClearBackBuffer(COLOR col);
	bool Flip();

	//Time
	float GetEngineTime();

	//void GetDeviceInfo();
	//void GetFeatureLevel();

	//Buffer
	bool CreateBuffer(UINT size, OUT ID3D12Resource** ppBuff);
	bool UpdateBuffer(ID3D12Resource* pBuff, LPVOID pData, UINT size);
	bool CreateVertexBuffer(void* pData, UINT size, UINT stride, OUT ID3D12Resource** ppVB, D3D12_VERTEX_BUFFER_VIEW** ppVBV);
	bool CreateConstantBuffer(void* pData, UINT size, OUT ID3D12Resource** ppCB);

	ID3D12Device* GetDevice() { return mDevice; }
	ID3D12GraphicsCommandList* GetCommandList() { return mCommandList; }
	DXGI_MODE_DESC GetMode() { return mMode; }
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
	D3D12_VIEWPORT mViewports[3];

	// AA & AF option
	DWORD		mAA = 1;
	DWORD		mAF = 1;
	BOOL		mMipMap = true;
};
