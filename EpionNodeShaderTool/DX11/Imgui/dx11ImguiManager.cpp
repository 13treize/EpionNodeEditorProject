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
		ImGui_ImplWin32_Init(MainSystem::get_hwnd());
		ImGui_ImplDX11_Init(Device::GetDevice().Get(),Device::GetContext().Get());
		ImGui::StyleColorsLight();
	}


	void	ImguiManager::release()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	//	最初に必要
	void	ImguiManager::begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	//	最後に必要
	void	ImguiManager::end()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}