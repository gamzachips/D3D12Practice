#pragma once

class Device;

class App
{
public:
	App();
	~App();
	void Init(HWND hWnd);
	void Update();
	void Render();
	void Release();

private:
	int		DataLoading();
	void	DataRelease();
	void	SceneRender();

	void	DrawText(int x, int y, const TCHAR* msg, ...);
	void	PutFPS(int x, int y);

private:
	Device* mDevice;
};

