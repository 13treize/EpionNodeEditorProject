#include	"../../epion.h"
#include	"../dx11_device.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"dx11_imgui_manager.h"
namespace
{
}

namespace	epion
{
	void	ImguiManager::Init()
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(MainSystem::GetHwnd());
		ImGui_ImplDX11_Init(Device::GetDevice().Get(),Device::GetContext().Get());
		ImGui::StyleColorsLight();
	}


	void	ImguiManager::Release()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	//	�ŏ��ɕK�v
	void	ImguiManager::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	//	�Ō�ɕK�v
	void	ImguiManager::End()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}