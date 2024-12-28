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

void DemoApp::Update()
{
    __super::Update();
    ObjUpdate();
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
    SAFE_RELEASE(mVertexBuffer);					//정점버퍼 제거.★
    SAFE_DELETE(mVertexBufferView);
    ReleaseInputLayout(mInputLayout);		//입력레이아웃 제거.★
}

void DemoApp::ObjUpdate(float dTime)
{
}

void DemoApp::ObjDraw(float dTime)
{
    ID3D12GraphicsCommandList* commandList = mDevice->GetCommandList();

    commandList->SetGraphicsRootSignature(mShader->mRootSignature);

    commandList->SetPipelineState(mPipelineState);

    commandList->IASetVertexBuffers(0, 1, mVertexBufferView);

    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList->DrawInstanced(3, 1, 0, 0);
}
