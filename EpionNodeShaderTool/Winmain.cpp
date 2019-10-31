#include	<array>
#include	<memory>

#include	"epion.h"
#include	"../Imgui//imgui.h"
#include	"../Imgui//imgui_impl_win32.h"
#include	"../Imgui//imgui_impl_dx11.h"
#include	"../Imgui//imgui_internal.h"

#include	"Framework.h"
namespace
{
	constexpr	int	SCREEN_WIDTH = 1920;
	constexpr	int	SCREEN_HEIGHT = 1080;
}
HWND		epion::MainSystem::hwnd;
WNDCLASSEX	epion::MainSystem::wcex;
LRESULT		ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT	CALLBACK	epion::MainSystem::wndproc(HWND	hwnd, UINT	message, WPARAM	wparam, LPARAM	lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wparam, lparam))
	{
		return	true;
	}

	PAINTSTRUCT	ps;
	HDC			hdc;
	switch (message)
	{
	case	WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case	WM_DESTROY:
		PostQuitMessage(0);
		break;
	case	WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		};
		break;
	default:
		return	DefWindowProc(hwnd, message, wparam, lparam);
	}
	return	0;
}

int	WINAPI	wWinMain(HINSTANCE	hInstance, HINSTANCE	hPrevInstance, LPWSTR	lpCmdLine, int	nCmdShow)
{
	//warningメッセージを抑止
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	epion::WindowRect	window_rect(SCREEN_WIDTH, SCREEN_HEIGHT);

	//ウィンドウ初期化
	epion::MainSystem::Init(hInstance, nCmdShow, window_rect);


	epion::FrameWork::Init(SCREEN_WIDTH,SCREEN_HEIGHT);

	MSG	msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			epion::FrameWork::Update();
			epion::FrameWork::render();
		}
	}
	epion::FrameWork::release();

	return	static_cast<int>(msg.wParam);
}