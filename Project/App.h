#pragma once

class Device;
class Shader;


class App
{
public:
	App();
	~App();
	virtual void Init(HWND hWnd);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void RenderBegin();
	void RenderEnd();

protected:

	bool	CreatePipelineState();
	void	ReleasePipelineState();
	bool	CreateInputLayout(D3D12_INPUT_ELEMENT_DESC* ed, DWORD num, D3D12_INPUT_LAYOUT_DESC** ppLayout);
	void	ReleaseInputLayout(D3D12_INPUT_LAYOUT_DESC*& rpLayout);

	virtual void	DataLoading() abstract;
	virtual void	DataRelease() abstract;

	void	DrawText(int x, int y, const TCHAR* msg, ...);
	void	PutFPS(int x, int y);

protected:
	Device* mDevice;
	Shader* mShader;

	D3D12_INPUT_LAYOUT_DESC* mInputLayout = nullptr;
	
	ID3D12PipelineState* mPipelineState = nullptr;
};

