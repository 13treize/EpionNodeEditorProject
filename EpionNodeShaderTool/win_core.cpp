#include	"epion.h"
#include	"win_core.h"
namespace
{
}

namespace	epion
{

	WNDCLASSEX	MainSystem::create_window(HINSTANCE	h_instance_)
	{
		wcex.cbSize = sizeof(WNDCLASSEX);											//�\���̂̃T�C�Y
		wcex.style = CS_HREDRAW | CS_VREDRAW;										//�E�B���h�E�X�^�C��
		wcex.cbClsExtra = 0;																//�E�B���h�E�N���X�\���̂̕⑫�o�C�g��
		wcex.cbWndExtra = 0;																//�E�B���h�E�C���X�^���X�̕⑫�o�C�g��
		wcex.hInstance = h_instance_;													//���̃N���X�Ŏg�p����E�B���h�E�v���V�[�W���̂���C���X�^���X�n���h��
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);								//�}�E�X�J�[�\���̃n���h��
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);									//�E�B���h�E�̔w�i�F
		wcex.lpszMenuName = nullptr;														//�f�t�H���g���j���[��
		wcex.lpszClassName = "DX11	Epion";													//�E�B���h�E�N���X�ɂ��閼�O
		wcex.hIconSm = LoadIcon(wcex.hInstance, reinterpret_cast<LPCTSTR>(107));	//�������T�C�Y�̃A�C�R���n���h��
		wcex.lpfnWndProc = wndproc;														//�E�B���h�E�v���V�[�W���ւ̃|�C���^
		return	wcex;
	}

	void	MainSystem::Init(HINSTANCE&	hInstance, int&	nCmdShow, WindowRect&	screen_data)
	{
		if (hwnd)
		{
			//exception::EpionDx11Exception("Main Systemn no init,hwnd", "2�ȏ�̃E�B���h�E�𐶐��ł��܂���");
		};
		if (!RegisterClassEx(&create_window(hInstance)))
		{
			//exception::EpionDx11Exception("Main Systemn no init,!RegistarClassEx", "���W�X�^�N���X�̓o�^���s");
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
			//exception::EpionDx11Exception("Main Systemn no init,!hwnd", "�E�B���h�E�쐬���s");
		};
		ShowWindow(hwnd, nCmdShow);
	}

	HWND	MainSystem::GetHwnd()
	{
		return	hwnd;
	}

}