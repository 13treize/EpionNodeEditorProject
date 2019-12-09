#include	"../All.h"
#include	"../epion.h"
#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"NodeEditor.h"
#include	"NodeWindow.h"
#include	"SettingWindow.h"
#include	"NodePreviewWindow.h"


#include	"Grids.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"

namespace
{
	ImGuiWindowFlags m_window_flags;
}

namespace	epion::GUI
{
	NodeWindow	NodeEditor::m_node_window;
	SettingWindow	NodeEditor::m_node_setting_window;
	NodePreviewWindow	NodeEditor::m_node_preview_window;

	void	NodeEditor::Init()
	{
		m_node_window.Init();
		m_node_setting_window.Init();
		m_node_preview_window.Init();
	}
	void	NodeEditor::Update()
	{
		m_window_flags = 0;
		m_window_flags |= ImGuiWindowFlags_NoTitleBar;
		m_window_flags |= ImGuiWindowFlags_NoMove;
		m_window_flags |= ImGuiWindowFlags_NoResize;

		ImGui::SetNextWindowSize(ImVec2(1920,1080), 1);
		if (!ImGui::Begin("Editor", nullptr, m_window_flags))
		{
			ImGui::End();
			return;
		}
		//ImGui::SetNextWindowPos(ImVec2(0, 0));
		//ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColors::U32::RED);	//îwåi
		//ImGui::BeginChild("test1", ImVec2(200, 0));
		//ImGui::EndChild();

		m_node_window.Update();

		m_node_setting_window.Update();

		m_node_preview_window.Update();

		ImGui::SetNextWindowPos(ImVec2(1450, 560));
		ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColors::U32::BLUE);	//îwåi
		ImGui::BeginChild("test5", ImVec2(400, 400));
		ImGui::EndChild();

		ImGui::PopStyleColor(3);

		ImGui::End();
	}
}