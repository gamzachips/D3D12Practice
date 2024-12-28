#include "pch.h"
#include "Device.h"

bool Device::DXSetup(HWND hWnd)
{
	CreateDeviceSwapChain(hWnd);
	CreateRenderTarget();
	SetViewPort();

	return true;
}

void Device::DXRelease()
{
	GPUSyncObjsRelease();
	CommandsRelease();

	for (UINT i = 0; i < mRTCount; i++)
	{
		SAFE_RELEASE(mRT[i]);
	}

	SAFE_RELEASE(mRTDescHeap);
	SAFE_RELEASE(mSwapChain);
	SAFE_RELEASE(mDevice);
}

HRESULT Device::CreateDeviceSwapChain(HWND hWnd)
{
	//DXGI 인터페이스 생성 
	IDXGIFactory4* pFactory = nullptr;
	::CreateDXGIFactory2(0, IID_PPV_ARGS(&pFactory));

	//DX 렌더링 장치 구성 
	HRESULT hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&mDevice));
	CHECK(hr);

	CommandsCreate(); 
	GPUSyncObjsCreate();

	
	//double buffering
	DXGI_SWAP_CHAIN_DESC1 scDesc{};
	scDesc.Width = mMode.Width;
	scDesc.Height = mMode.Height;
	scDesc.Format = mMode.Format;
	scDesc.SampleDesc.Count = mAA;
	scDesc.SampleDesc.Quality = 0;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = mRTCount;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	IDXGISwapChain1* pSwapChain = nullptr;
	hr = pFactory->CreateSwapChainForHwnd(mCommandQueue, hWnd, &scDesc, nullptr, nullptr, &pSwapChain);
	CHECK(hr);

	hr = pSwapChain->QueryInterface(IID_PPV_ARGS(&mSwapChain));
	CHECK(hr);

	mRTIndex = mSwapChain->GetCurrentBackBufferIndex();

	pFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER); //전체화면 방지 

	//임시 인터페이스 제거 
	SAFE_RELEASE(pFactory); 
	SAFE_RELEASE(pSwapChain);

	return hr;
}

HRESULT Device::CreateRenderTarget()
{
	D3D12_DESCRIPTOR_HEAP_DESC hDesc{};
	hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	hDesc.NumDescriptors = mRTCount;
	HRESULT hr = mDevice->CreateDescriptorHeap(&hDesc, IID_PPV_ARGS(&mRTDescHeap));
	CHECK(hr);

	mRTDescSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_CPU_DESCRIPTOR_HANDLE dh = mRTDescHeap->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i < mRTCount; i++)
	{
		hr = mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mRT[i]));
		mDevice->CreateRenderTargetView(mRT[i], nullptr, dh);
		dh.ptr += mRTDescSize;
	}
	CHECK(hr);
	return hr;
}

void Device::SetViewPort()
{
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (FLOAT)mMode.Width;
	vp.Height = (FLOAT)mMode.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	mViewport = vp;
}

bool Device::CommandsCreate()
{
	D3D12_COMMAND_QUEUE_DESC cqDesc{};

	cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	cqDesc.NodeMask = 0;
	HRESULT hr = mDevice->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&mCommandQueue));
	hr = mDevice->CreateCommandAllocator(cqDesc.Type, IID_PPV_ARGS(&mCommandAllocator));
	hr = mDevice->CreateCommandList(0, cqDesc.Type, mCommandAllocator, nullptr, IID_PPV_ARGS(&mCommandList));
	mCommandList->Close();

	CHECK(hr);

	return true;
}

bool Device::CommandsReset()
{
	mCommandAllocator->Reset();
	mCommandList->Reset(mCommandAllocator, nullptr);

	return true;
}

bool Device::CommandsExcute()
{
	ID3D12CommandList* cmdLists[] = { mCommandList, };

	mCommandList->Close();
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	return true;
}

void Device::CommandsRelease()
{
	SAFE_RELEASE(mCommandQueue);
	SAFE_RELEASE(mCommandAllocator);
	SAFE_RELEASE(mCommandList);
}

bool Device::GPUSyncObjsCreate()
{
	HRESULT hr = mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
	mFenceValue = 1;

	mFenceEvent = CreateEvent(nullptr, false, false, nullptr);
	
	CHECK(hr);
	if (!mFenceEvent) return false;
	return true;
}

void Device::GPUSyncObjsRelease()
{
	SAFE_RELEASE(mFence);
	::CloseHandle(mFenceEvent);
}

bool Device::GPUSync()
{
	const UINT64 fence = mFenceValue;
	mCommandQueue->Signal(mFence, fence);
	mFenceValue++;

	if (mFence->GetCompletedValue() < fence)
	{
		mFence->SetEventOnCompletion(fence, mFenceEvent);
		::WaitForSingleObject(mFenceEvent, INFINITE);
	}
	return true;
}

bool Device::ClearBackBuffer(COLOR col)
{
	D3D12_RECT rc = { 0, 0, (LONG)mMode.Width, (LONG)mMode.Height };

	CommandsReset();
	
	mCommandList->RSSetViewports(1, &mViewport);
	mCommandList->RSSetScissorRects(1, &rc);

	D3D12_RESOURCE_BARRIER br = {};
	br.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	br.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	br.Transition.pResource = mRT[mRTIndex];
	br.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	br.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	br.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	mCommandList->ResourceBarrier(1, &br);

	D3D12_CPU_DESCRIPTOR_HANDLE rtv;
	rtv = mRTDescHeap->GetCPUDescriptorHandleForHeapStart();
	rtv.ptr += (SIZE_T)mRTIndex * (SIZE_T)mRTDescSize;

	mCommandList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
	mCommandList->ClearRenderTargetView(rtv, (float*)&col, 0, NULL);

	return true;
}

bool Device::Flip()
{
	ID3D12CommandList* cmdLists[] = { mCommandList, };

	D3D12_RESOURCE_BARRIER br = {};
	br.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	br.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	br.Transition.pResource = mRT[mRTIndex];
	br.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	br.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	br.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	mCommandList->ResourceBarrier(1, &br);

	mCommandList->Close();
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	mSwapChain->Present(mVSync, 0);

	GPUSync();

	mRTIndex = mSwapChain->GetCurrentBackBufferIndex();

	return true;
}

float Device::GetEngineTime()
{
	static ULONGLONG oldtime = GetTickCount64();
	ULONGLONG 		 nowtime = GetTickCount64();
	float dTime = (nowtime - oldtime) * 0.001f;
	oldtime = nowtime;

	return dTime;
}

bool Device::CreateBuffer(UINT size, OUT ID3D12Resource** ppBuff)
{
	D3D12_HEAP_PROPERTIES hp{};
	hp.Type = D3D12_HEAP_TYPE_UPLOAD;
	hp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	hp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	hp.CreationNodeMask = 0;
	hp.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC rDesc{};
	rDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	rDesc.Alignment = 0;
	rDesc.Width = size;
	rDesc.Height = 1;
	rDesc.DepthOrArraySize = 1;
	rDesc.MipLevels = 1;
	rDesc.Format = DXGI_FORMAT_UNKNOWN;
	rDesc.SampleDesc.Count = 1;
	rDesc.SampleDesc.Quality = 0;
	rDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	rDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	ID3D12Resource* pBuff = nullptr;
	HRESULT hr = mDevice->CreateCommittedResource(
		&hp, D3D12_HEAP_FLAG_NONE, &rDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&pBuff));

	CHECK(hr);

	*ppBuff = pBuff;

	return true;
}

bool Device::UpdateBuffer(ID3D12Resource* pBuff, LPVOID pData, UINT size)
{
	if (pData == nullptr) return false;

	UINT8* buff = nullptr;
	HRESULT hr = pBuff->Map(0, nullptr, (void**)&buff);
	CHECK(hr);

	memcpy(buff, pData, size);
	pBuff->Unmap(0, nullptr);

	return true;
}

bool Device::CreateVertexBuffer(void* pData, UINT size, UINT stride, OUT ID3D12Resource** ppVB, D3D12_VERTEX_BUFFER_VIEW** ppVBV)
{
	ID3D12Resource* pVB = nullptr;
	CreateBuffer(size, &pVB);
	UpdateBuffer(pVB, pData, size);

	D3D12_VERTEX_BUFFER_VIEW* pVBV = new D3D12_VERTEX_BUFFER_VIEW;
	pVBV->BufferLocation = pVB->GetGPUVirtualAddress();
	pVBV->SizeInBytes = size;
	pVBV->StrideInBytes = stride;

	*ppVB = pVB;
	*ppVBV = pVBV;

	return true;
}
