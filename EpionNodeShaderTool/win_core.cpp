#include	"epion.h"
#include	"win_core.h"
namespace
{
}

namespace	epion
{

	WNDCLASSEX	MainSystem::create_window(HINSTANCE	h_instance_)
	{
		wcex.cbSize = sizeof(WNDCLASSEX);											//構造体のサイズ
		wcex.style = CS_HREDRAW | CS_VREDRAW;										//ウィンドウスタイル
		wcex.cbClsExtra = 0;																//ウィンドウクラス構造体の補足バイト数
		wcex.cbWndExtra = 0;																//ウィンドウインスタンスの補足バイト数
		wcex.hInstance = h_instance_;													//このクラスで使用するウィンドウプロシージャのあるインスタンスハンドル
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);								//マウスカーソルのハンドル
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);									//ウィンドウの背景色
		wcex.lpszMenuName = nullptr;														//デフォルトメニュー名
		wcex.lpszClassName = "DX11	Epion";													//ウィンドウクラスにつける名前
		wcex.hIconSm = LoadIcon(wcex.hInstance, reinterpret_cast<LPCTSTR>(107));	//小さいサイズのアイコンハンドル
		wcex.lpfnWndProc = wndproc;														//ウィンドウプロシージャへのポインタ
		return	wcex;
	}

	void	MainSystem::Init(HINSTANCE&	hInstance, int&	nCmdShow, WindowRect&	screen_data)
	{
		if (hwnd)
		{
			//exception::EpionDx11Exception("Main Systemn no init,hwnd", "2つ以上のウィンドウを生成できません");
		};
		if (!RegisterClassEx(&create_window(hInstance)))
		{
			//exception::EpionDx11Exception("Main Systemn no init,!RegistarClassEx", "レジスタクラスの登録失敗");
		};
		AdjustWindowRect(&screen_data.get_rc(), WS_OVERLAPPEDWINDOW, false);

		::GetClientRect(hwnd, &screen_data.get_rc());

		hwnd = ::CreateWindow("DX11	Epion",
			"Epion	3D",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			screen_data.get_size().x,
			screen_data.get_size().y,
			nullptr,
			nullptr,
			hInstance,
			nullptr);
		if (!hwnd)
		{
			//exception::EpionDx11Exception("Main Systemn no init,!hwnd", "ウィンドウ作成失敗");
		};
		ShowWindow(hwnd, nCmdShow);
	}

	HWND	MainSystem::GetHwnd()
	{
		return	hwnd;
	}

}