#include "pch.h"
#include "Shader.h"
#include "d3dcompiler.h"			
#pragma comment(lib, "d3dcompiler")	

bool Shader::LoadShader()
{
	const TCHAR* filename = _T("../fx/Demo.fx");

	//���̴� �ε�.
	LoadShader(filename, "VS_Main", "vs_5_1", &mVS);
	LoadShader(filename, "PS_Main", "ps_5_1", &mPS);
	LoadShader(filename, "GS_Main", "gs_5_1", &mGS);

	return true;
}

HRESULT Shader::LoadShader(const TCHAR* filename, const CHAR* entry, const CHAR* sm, OUT ID3DBlob** ppfx)
{
	ID3DBlob* pCode = nullptr;
	HRESULT hr = CompileShader(filename, entry, sm, &pCode);
	CHECK(hr);

	*ppfx = pCode;

	return hr;
}

void Shader::ReleaseShader()
{
	SAFE_RELEASE(mVS);
	SAFE_RELEASE(mPS);

	ReleaseRootSignature();
}

HRESULT Shader::CompileShader(const WCHAR* filename, const char* entry, const char* sm, OUT ID3DBlob** ppCode)
{
	ID3DBlob* pError = nullptr;

	UINT flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG;
#endif;

	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, entry, sm,
		flags, 0, ppCode, &pError);
	CHECK(hr);

	SAFE_RELEASE(pError);
	return hr;
}

void Shader::CreateShader(ID3D12Device* device)
{
	CreateRootSignature(device);
	LoadShader();
}

void Shader::UpdateShader()
{
}

bool Shader::CreateRootSignature(ID3D12Device* device)
{
	D3D12_ROOT_PARAMETER param{};
	param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	param.Constants.ShaderRegister = 0;
	param.Constants.RegisterSpace = 0;
	param.Constants.Num32BitValues = 4;
	param.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_DESC rsDesc{};
	rsDesc.NumParameters = 1;
	rsDesc.pParameters = &param;
	rsDesc.NumStaticSamplers = 0;
	rsDesc.pStaticSamplers = nullptr;
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ID3DBlob* pSign = nullptr;
	ID3DBlob* pError = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &pSign, &pError);
	CHECK(hr);

	hr = device->CreateRootSignature(0, pSign->GetBufferPointer(), pSign->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature));
	CHECK(hr);

	SAFE_RELEASE(pSign);
	SAFE_RELEASE(pError);

	return true;
}

void Shader::ReleaseRootSignature()
{
	SAFE_RELEASE(mRootSignature);
}
