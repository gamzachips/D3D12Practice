#pragma once
class Shader
{
public:
	void CreateShader(ID3D12Device* device);
	void ReleaseShader();

	void UpdateShader();

private:
	bool LoadShader();
	HRESULT LoadShader(const TCHAR* filename, const CHAR* entry, const CHAR* sm, OUT ID3DBlob** ppfx);
	HRESULT CompileShader(const WCHAR* filename, const char* entry, const char* sm, OUT ID3DBlob** ppCode);
	
	bool	CreateRootSignature(ID3D12Device* device);
	void	ReleaseRootSignature();

public:
	ID3DBlob* mVS = nullptr;
	ID3DBlob* mPS = nullptr;

	ID3D12RootSignature* mRootSignature = nullptr;
};

