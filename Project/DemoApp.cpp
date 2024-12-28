#include "pch.h"
#include "DemoApp.h"
#include "Device.h"
#include "Shader.h"

DemoApp::DemoApp()
{
}

DemoApp::~DemoApp()
{
}

void DemoApp::Init(HWND hWnd)
{
    __super::Init(hWnd);
}

void DemoApp::Update(float deltaTime)
{
    __super::Update(deltaTime);
    ObjUpdate(deltaTime);
}

void DemoApp::Render()
{
    __super::Render();
    ObjDraw();
}

void DemoApp::Release()
{
    __super::Release();
}

void DemoApp::DataLoading()
{
    ObjLoad();
    CreatePipelineState();
}

void DemoApp::DataRelease()
{

    ObjRelease();
    ReleasePipelineState();
}

void DemoApp::CreateCBs()
{
   // mDevice->CreateConstantBuffer();
}

bool DemoApp::ObjLoad()
{
    Vertex vertices[] =
    {
        {{180.f, 450.f, 0.f}, {1, 0, 0, 1}},
        {{380, 150.f, 0.f}, {0, 1, 0, 1}},
        {{580.f, 450.f, 0.f}, {0, 0, 1, 1}},
    };

    UINT size = sizeof(vertices);

    HRESULT hr = mDevice->CreateVertexBuffer(vertices, size, sizeof(Vertex), &mVertexBuffer, &mVertexBufferView);
    CHECK(hr);


    D3D12_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };

    UINT numElements = ARRAYSIZE(layout);

    CreateInputLayout(layout, numElements, &mInputLayout);

    return true;

}

void DemoApp::ObjRelease()
{
    SAFE_RELEASE(mVertexBuffer);	
    SAFE_DELETE(mVertexBufferView);
    ReleaseInputLayout(mInputLayout);		
}

void DemoApp::ObjUpdate(float deltaTime)
{
    //오브젝트 갱신, 상수버퍼 갱신 UpdateBuffer(...);
    mColorTime += deltaTime;

    float phase = mColorTime * mColorSpeed;

    if (phase < 1.0f)
    {
        float t = phase;
        mColor = {1.f - t, t, 0.f, 1.f };
    }
    else if (phase < 2.f)
    {
        float t = phase - 1.f;
        mColor = { 0.f, 1.f - t, t, 1.f };
    }
    else
    {
        float t = phase - 2.f;
        mColor = { t, 0, 1.f - t, 1.f };
    }

    if (phase >= 3.0f)
    {
        mColorTime = 0.f;
    }

}

void DemoApp::ObjDraw(float dTime)
{
    ID3D12GraphicsCommandList* commandList = mDevice->GetCommandList();

    commandList->SetGraphicsRootSignature(mShader->mRootSignature);

    commandList->SetGraphicsRoot32BitConstants(0, 4, (void*)&mColor, 0);

    commandList->SetPipelineState(mPipelineState);

    commandList->IASetVertexBuffers(0, 1, mVertexBufferView);

    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList->DrawInstanced(3, 1, 0, 0);
}
