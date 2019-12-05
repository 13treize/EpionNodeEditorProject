#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../../imgui\\imfilebrowser.h"

#include	"../../ImguiFunction.h"
#include	"ExplorerWindow.h"


namespace
{
	ImGui::FileBrowser fileDialog;
}
namespace	epion::GUI
{
	void ExplorerWindow::Init()
	{
		fileDialog.SetTitle("title");
		fileDialog.SetTypeFilters({ ".json", ".hlsl" });
	}


	void ExplorerWindow::Update()
	{
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowSize(ImVec2(900, 600), ImGuiCond_::ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("test", nullptr, window_flags))
		{
			ImGui::End();
			return;
		}
		LocationSet();
		ImGui::SameLine();
		NameSet();
		if (ImGui::Button("open file dialog"))
		{
			fileDialog.Open();
		}


		ImGui::Text("Name");
		ImGui::End();
		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
			fileDialog.ClearSelected();
		}
	}

	void ExplorerWindow::LocationSet()
	{
		ImGui::BeginChild("node_list", ImVec2(100, 0));
		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::TreeNode("Locations"))
			{
				ImGui::Text("NameA");
				ImGui::Text("NameB");
				ImGui::Text("NameC");
				ImGui::TreePop();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();
	}
	void ExplorerWindow::NameSet()
	{
		ImGui::BeginChild("node_list2", ImVec2(600, 0));
		if (ImGui::BeginTabBar("##tabs2", ImGuiTabBarFlags_None))
		{
			if (ImGui::TreeNode("Name"))
			{
				ImGui::Text("NameA2");
				ImGui::Text("NameB2");
				ImGui::Text("NameC2");
				ImGui::TreePop();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();
	}
}