#include	"../All.h"
#include	"../epion.h"
#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"NodeEditor.h"
#include	"NodeWindow.h"
#include	"NodeDragWindow.h"
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
	NodeDragWindow	NodeEditor::m_node_drag_window;
	SettingWindow	NodeEditor::m_node_setting_window;
	NodePreviewWindow	NodeEditor::m_node_preview_window;

	void	NodeEditor::Init()
	{
		m_node_window.Init();
		m_node_drag_window.Init();
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
		m_node_window.Update(m_node_drag_window.GetNodeNames());

		//m_node_drag_window.Update();

		m_node_setting_window.Update(m_node_window.GetNodes(),m_node_window.GetLinks());

		m_node_preview_window.Update(m_node_setting_window.m_is_preview_reset);

		ImGui::PopStyleColor();

		ImGui::End();
	}

	void NodeEditor::Render()
	{
		m_node_preview_window.Render();
	}

}