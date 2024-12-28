#include "pch.h"
#include "DemoApp.h"


HWND g_hWnd = NULL;
BOOL g_bLoop = TRUE;

const TCHAR* g_ClassName = _T("MyProject");
extern const TCHAR* g_WindowName;

BOOL InitWindow(int width, int height);
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight);
BOOL MessagePump();
LRESULT  CALLBACK MshProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	if (!InitWindow(960, 600)) return 0;

	DemoApp app;
	app.Init(g_hWnd);

	while (g_bLoop)
	{
		if (!MessagePump())
			break;
		app.Update();

		{
			app.RenderBegin();
			app.Render();
			app.RenderEnd();
		}
		
	}

	app.Release();
	return 0;
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hwnd, WM_DESTROY, 0, 0);
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);

}

BOOL InitWindow(int width, int height)
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0, 0,
		::GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		g_ClassName, NULL
	};
	RegisterClassEx(&wc);

	HWND hWnd = ::CreateWindow(g_ClassName, g_WindowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, width, height, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	if (hWnd == NULL) return FALSE;

	ResizeWindow(hWnd, width, height);

	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);
	::SetCursor(LoadCursor(NULL, IDC_ARROW));

	g_hWnd = hWnd;

	return TRUE;
}

int MessagePump()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return FALSE;

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			return TRUE;
		}
	}
	return FALSE;
}

void ResizeWindow(HWND hWnd, UINT width, UINT height)
{
	RECT oldrc;	
	::GetWindowRect(hWnd, &oldrc);
	DWORD style = (DWORD) ::GetWindowLong(hWnd, GWL_STYLE);
	DWORD exstyle = (DWORD) ::GetWindowLong(hWnd, GWL_EXSTYLE);

	RECT newrc = { 0, 0, (LONG)width, (LONG)height };

	::AdjustWindowRectEx(&newrc, style, NULL, exstyle);

	int newWidth = (newrc.right - newrc.left);
	int newHeight = (newrc.bottom - newrc.top);

	::SetWindowPos(hWnd, HWND_NOTOPMOST, oldrc.left, oldrc.top,
		newWidth, newHeight, SWP_SHOWWINDOW);
}