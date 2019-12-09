#include	"../All.h"
#include	"../epion.h"

#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"

#include	"NodePreviewWindow.h"

namespace epion::GUI
{
	bool NodePreviewWindow::Init()
	{
		return true;
	}

	void NodePreviewWindow::Update()
	{
		ImGui::SetNextWindowPos(ImVec2(150, 710));
		ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColors::U32::GRAY);	//îwåi
		ImGui::BeginChild("test3", ImVec2(1200, 300));

		ImGui::EndChild();

	}
}