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
		RECT			rc;		//��ʂ̑傫��
	};

	class	MainSystem	final
	{
	public:
		static	HWND	GetHwnd();

		//�E�B���h�E�쐬
		static	void	Init(HINSTANCE&	hInstance, int&	nCmdShow, WindowRect&	screen_data);

		static	WNDCLASSEX	create_window(HINSTANCE	h_instance);

		static	LRESULT	CALLBACK	wndproc(HWND	hwnd, UINT	message, WPARAM	wparam, LPARAM	lparam);
	private:
		static	HWND		hwnd;			//���삷�邽�߂̂���
		static	WNDCLASSEX	wcex;
	};
}

