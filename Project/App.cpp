#include "pch.h"
#include "App.h"
#include "Device.h"

COLOR g_ClearColor(0, 0.125f, 0.3f, 1);

const TCHAR* g_WindowName = _T("Jiwon's first D3D Project");
extern HWND g_hWnd;

App::App()
{
	mDevice = new Device;
}

App::~App()
{
	SAFE_DELETE(mDevice);
}

void App::Init(HWND hWnd)
{
	mDevice->DXSetup(hWnd);
	
	DataLoading();
}

void App::Update()
{
}

void App::Render()
{
	mDevice->ClearBackBuffer(g_ClearColor);
	SceneRender();

	mDevice->Flip();
}

void App::Release()
{
	mDevice->DXRelease();
	DataRelease();
}

int App::DataLoading()
{
	return 0;
}

void App::DataRelease()
{
}

void App::SceneRender()
{
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
