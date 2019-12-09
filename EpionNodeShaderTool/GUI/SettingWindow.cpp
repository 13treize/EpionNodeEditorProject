#include	"../All.h"
#include	"../epion.h"

#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"

#include	"SettingWindow.h"


namespace epion::GUI
{
	bool SettingWindow::Init()
	{
		return true;
	}

	void SettingWindow::Update()
	{
		ImGui::SetNextWindowPos(ImVec2(1450, 10));
		ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColors::U32::GRAYBLACK);	//îwåi
		ImGui::BeginChild("test4", ImVec2(400, 500));
		ImGui::Text("Settings");
		auto&	io = ImGui::GetIO();
		ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
		if (ImGui::BeginTabBar("##sets", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Node Param"))
			{
				ImGui::Text("Node Param");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Option"))
			{
				ImGui::Text("Option");
				auto&	io = ImGui::GetIO();
				ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
				ImGui::EndTabItem();
			}


		}

		ImGui::EndTabBar();

		ImGui::EndChild();
	}
}
