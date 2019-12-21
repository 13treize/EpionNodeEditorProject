#include	"../All.h"
#include	"../epion.h"

#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"
#include	"../Node/NodeData.h"

#include	"NodeDragWindow.h"
#include	"../Dx11/texture.h"

namespace
{
}

namespace	epion::GUI
{
	bool NodeDragWindow::Init()
	{
		m_node_names.push_back("Add");
		m_node_names.push_back("Noise");
		m_node_names.push_back("Noiseq");
		m_node_names.push_back("Noisew");
		m_node_names.push_back("Noised");

		m_icon_tex = std::make_unique<Texture>();
		TextureFileIO::LoadTexture(L"Assets\\node_icon.png", m_icon_tex->m_metadata, m_icon_tex->m_image, m_icon_tex->m_shader_resource);
		return true;
	}

	void NodeDragWindow::Update()
	{
		ImGui::SetNextWindowPos(ImVec2(150, 710));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColors::U32::GRAY);	//”wŒi
		ImGui::BeginChild("test3", ImVec2(1200, 300));

		//ImGui::ImageButton(m_icon_tex->m_shader_resource.Get(), ImVec2(51, 64));
		//ImGui::Text("Voronoi");
		//ImGui::ImageButton(m_icon_tex->m_shader_resource.Get(), ImVec2(51, 64));
		//ImGui::Text("Add");
		//ImGui::Button("Noise", ImVec2(60, 60));

		//ImGui::ImageButton(m_icon_tex->m_shader_resource.Get(), ImVec2(51, 64));
		ImGui::Text(m_node_name.c_str());

		for (int i = 0; i < m_node_names.size();i++)
		{
			if ((i % 12) != 0)
			{
				ImGui::SameLine();
			}
			ImGui::Button(m_node_names[i].c_str(), ImVec2(60, 60));

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &i, sizeof(int));        // Set payload to carry the index of our item (could be anything)
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int payload_n = *(const int*)payload->Data;
					m_node_name = m_node_names[payload_n];
				}
				ImGui::EndDragDropTarget();
			}
		}

		ImGui::EndChild();
	}

	std::vector<std::string>& NodeDragWindow::GetNodeNames()
	{
		return m_node_names;
	}

}