#pragma once

namespace	epion
{
	class	WindowRect	final
	{
	public:
		WindowRect(int	x_, int	y_) :rc({ 0,	0,	x_,	y_ }) {};
		~WindowRect() {};
		RECT	get_rc()
		{
			return	rc;
		}

		void	set_size(int	width, int	height)
		{
			rc.right = width;
			rc.bottom = height;
		}

		template<class	T = int>
		math::Vector2<T>	get_size()
		{
			math::Vector2<T>	return_size =
			{
				static_cast<T>(rc.right - rc.left),
				static_cast<T>(rc.bottom - rc.top)
			};
			return	return_size;
		}

	private:
		RECT			rc;		//画面の大きさ
	};

	class	MainSystem	final
	{
	public:
		static	HWND	GetHwnd();

		//ウィンドウ作成
		static	void	Init(HINSTANCE&	hInstance, int&	nCmdShow, WindowRect&	screen_data);

		static	WNDCLASSEX	create_window(HINSTANCE	h_instance);

		static	LRESULT	CALLBACK	wndproc(HWND	hwnd, UINT	message, WPARAM	wparam, LPARAM	lparam);
	private:
		static	HWND		hwnd;			//操作するためのもの
		static	WNDCLASSEX	wcex;
	};
}

