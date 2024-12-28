#include "pch.h"
#include "App.h"
#include "Device.h"
#include "Shader.h"

COLOR g_ClearColor(0, 0.125f, 0.3f, 1);

const TCHAR* g_WindowName = _T("Jiwon's first D3D Project");
extern HWND g_hWnd;

App::App()
{
	mDevice = new Device;
	mShader = new Shader;
}

App::~App()
{
	SAFE_DELETE(mDevice);
	SAFE_DELETE(mShader);
}

void App::Init(HWND hWnd)
{
	mDevice->DXSetup(hWnd);
	mShader->CreateShader(mDevice->GetDevice());
	CreateCBs();

	mDevice->CommandsReset();
	DataLoading();
	mDevice->CommandsExcute();
	mDevice->GPUSync();
}

void App::Update(float deltaTime)
{
	mShader->UpdateShader();
}

void App::Render()
{
}

void App::Release()
{
	mDevice->DXRelease();
	mShader->ReleaseShader();
	DataRelease();
	ReleasePipelineState();
}

void App::RenderBegin()
{
	mDevice->ClearBackBuffer(g_ClearColor);

}

void App::RenderEnd()
{
	mDevice->Flip();
}



bool App::CreatePipelineState()
{
	D3D12_RASTERIZER_DESC rDesc = {};
	rDesc.FillMode = D3D12_FILL_MODE_SOLID;
	rDesc.CullMode = D3D12_CULL_MODE_NONE;

	D3D12_BLEND_DESC bDesc = {};
	bDesc.RenderTarget[0].BlendEnable = false;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	D3D12_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = false;
	dsDesc.StencilEnable = false;

	D3D12_SHADER_BYTECODE vs = { mShader->mVS->GetBufferPointer(), mShader->mVS->GetBufferSize() };
	D3D12_SHADER_BYTECODE ps = { mShader->mPS->GetBufferPointer(), mShader->mPS->GetBufferSize() };
	D3D12_SHADER_BYTECODE gs = { mShader->mGS->GetBufferPointer(), mShader->mGS->GetBufferSize() };


	D3D12_GRAPHICS_PIPELINE_STATE_DESC psDesc{};
	psDesc.pRootSignature = mShader->mRootSignature;
	psDesc.VS = vs;
	psDesc.PS = ps;
	psDesc.GS = gs;
	psDesc.BlendState = bDesc;
	psDesc.SampleMask = UINT_MAX;
	psDesc.RasterizerState = rDesc;
	psDesc.InputLayout = *mInputLayout;
	psDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psDesc.NumRenderTargets = 1;
	psDesc.RTVFormats[0] = mDevice->GetMode().Format;
	psDesc.SampleDesc = { 1, 0 };

	ID3D12PipelineState* pPSO = nullptr;
	HRESULT hr = mDevice->GetDevice()->CreateGraphicsPipelineState(&psDesc, IID_PPV_ARGS(&pPSO));
	CHECK(hr);

	mPipelineState = pPSO;

	return true;
}

void App::ReleasePipelineState()
{
	SAFE_RELEASE(mPipelineState);
}

bool App::CreateInputLayout(D3D12_INPUT_ELEMENT_DESC* ed, DWORD num, D3D12_INPUT_LAYOUT_DESC** ppLayout)
{
	D3D12_INPUT_LAYOUT_DESC* pLayout = new D3D12_INPUT_LAYOUT_DESC;
	pLayout->pInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[num];

	CopyMemory((void*)pLayout->pInputElementDescs, ed, num * sizeof(D3D12_INPUT_ELEMENT_DESC));
	pLayout->NumElements = num;

	*ppLayout = pLayout;

	return true;
}

void App::ReleaseInputLayout(D3D12_INPUT_LAYOUT_DESC*& rpLayout)
{
	SAFE_DELARRY(rpLayout->pInputElementDescs);
	SAFE_DELETE(rpLayout);
}

void App::DrawText(int x, int y, const TCHAR* msg, ...)
{
	TCHAR buff[128] = _T("");
	va_list vl;
	va_start(vl, msg);
	_vstprintf_s(buff, msg, vl);
	va_end(vl);

	HDC hdc = GetDC(g_hWnd);
	TextOut(hdc, x, y, buff, (int)_tcslen(buff));
	ReleaseDC(g_hWnd, hdc);
}

void App::PutFPS(int x, int y)
{
	static UINT  frm = 0;
	static float fps = 0.0f;
	++frm;
	static ULONGLONG oldtime = GetTickCount64();
	ULONGLONG nowtime = GetTickCount64();

	UINT time = (UINT)(nowtime - oldtime);
	if (time >= 1000)
	{
		fps = (float)(frm * 1000) / (float)time;
		frm = 0;
		oldtime = nowtime;
	}

	DrawText(x, y, _T("FPS=%.1f/%d      "), fps, time);
}
