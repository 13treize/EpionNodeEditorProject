#include	"../All.h"
#include	"../epion.h"

#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"../Scene/SceneManager.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"
#include	"../Node/NodeData.h"

#include	"SettingWindow.h"

#include	"../FileIO/Fileio_json.h"
#include	"../ShaderGenerate/ShaderGenerate.h"


namespace epion::GUI
{
	bool SettingWindow::Init()
	{
		m_is_preview_reset = false;
		return true;
	}

	void SettingWindow::Update(std::vector<std::unique_ptr<Node::NodeBase>>&	nodes,std::vector<Node::NodeLink>& links)
	{
		ImGui::SetNextWindowPos(ImVec2(1450, 10));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColors::U32::GRAYBLACK);	//îwåi
		ImGui::BeginChild("test4", ImVec2(400, 500));
		ImGui::Text("Settings");
		if (ImGui::BeginTabBar("##sets", ImGuiTabBarFlags_None))
		{
			FileIOUpdate(nodes, links);
			NodeTabUpdate();
			OptionTabUpdate();
		}

		ImGui::EndTabBar();

		ImGui::EndChild();
	}

	void SettingWindow::FileIOUpdate(std::vector<std::unique_ptr<Node::NodeBase>>&	nodes, std::vector<Node::NodeLink>& links)
	{
		if (ImGui::BeginTabItem("File IO"))
		{
			ImGui::Text("File IO");
			if (ImGui::Button("Update"))
			{
				FileIO::FileIOJson o_json;
				o_json.Output("Default/Default2.json",nodes, links);
				Shader::NodeShaderManager::JsonImport("Default/Default2.json");
				Shader::NodeShaderManager::Generate("Default/Default2.hlsl");
				m_is_preview_reset = true;
			}

			ImGui::InputText("Json Name", const_cast<char*>(m_import_json_name.c_str()), CHAR_MAX);
			ImGui::Text(m_import_json_name.c_str());
			if (ImGui::Button("Json Generate"))
			{
				std::string path;
				path = path + "GenerateNodeJson/" + m_import_json_name.c_str() + ".json";

				FileIO::FileIOJson o_json;
				o_json.Output(path, nodes, links);
			}

			ImGui::InputText("HLSL Name", const_cast<char*>(m_import_hlsl_name.c_str()), CHAR_MAX);
			ImGui::Text(m_import_hlsl_name.c_str());
			if (ImGui::Button("HLSL Generate"))
			{
				std::string path;
				path = path + "GenerateShader/" + m_import_hlsl_name.c_str() + ".hlsl";

				FileIO::FileIOJson o_json;
				o_json.Output("Default/Default2.json", nodes, links);
				Shader::NodeShaderManager::JsonImport("Default/Default2.json");
				Shader::NodeShaderManager::Generate(path);
			}

			//if (ImGui::Button("TGA Generate"))
			//{
			//}

			ImGui::EndTabItem();
		}
	}

	void SettingWindow::NodeTabUpdate()
	{
		if (ImGui::BeginTabItem("Node Param"))
		{
			ImGui::Text("Node Param");

			ImGui::Text("node size %d", m_node_size);


			ImGui::EndTabItem();
		}
	}

	void SettingWindow::OptionTabUpdate()
	{
		if (ImGui::BeginTabItem("Option"))
		{
			ImGui::Text("Option");
			auto&	io = ImGui::GetIO();
			ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
			ImGui::EndTabItem();
		}
		//if (ImGui::BeginTabItem("DemoScene"))
		//{
		//	if (ImGui::RadioButton("Demo 2D", &m_select_scene, 0))
		//	{
		//		SceneManager::SetNextScene<SceneDemo2D>();
		//	}
		//	if (ImGui::RadioButton("Demo 3D", &m_select_scene, 1))
		//	{
		//		SceneManager::SetNextScene<SceneDemo3D>();
		//	}
		//	if (ImGui::RadioButton("Demo Ray", &m_select_scene, 2))
		//	{
		//		SceneManager::SetNextScene<SceneDemoRay>();
		//	}
		//	ImGui::EndTabItem();
		//}
		if (ImGui::BeginTabItem("Camera"))
		{
			ImGui::EndTabItem();
		}
	}


	void SettingWindow::SetNodeState(int size, std::vector<int>& id, std::vector<math::FVector2>& pos)
	{
		m_node_size = size;
		m_node_id = id;
		m_node_pos = pos;
	}


}

