#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../ImguiFunction.h"


#include	"../../Node/NodeData.h"

#include	"../../ShaderGenerate/ShaderGenerate.h"
#include	"FileIOAdjust.h"
#include	"EpionNodeEditor.h"
#include	"PreviewWindow.h"

namespace
{
	char json_name[CHAR_MAX] = "";
}
namespace	epion::GUI
{
	FileIOAdjust::FileIOAdjust()
	{
	}

	FileIOAdjust::~FileIOAdjust()
	{
	}

	void FileIOAdjust::Init()
	{
		//Default
		m_json_path = "GenerateNodeJson";
		m_shader_path = "GenerateShader";
		m_import_json_path_name="";
		m_export_json_path_name = "";
	}

	void FileIOAdjust::Update()
	{
		if (ImGui::BeginTabItem("IOSetting"))
		{
			//ResetEvent();
			PathSetting();
			JsonImport();
			JsonSave();
			ShaderGenerate();

			ImGui::EndTabItem();
		}
	}

	void FileIOAdjust::PathSetting()
	{
		if (ImGui::CollapsingHeader("Path Setting"))
		{
			ImGui::InputText("Json Path", const_cast<char*>(m_json_path.c_str()), CHAR_MAX);
			ImGui::InputText("Shader Path", const_cast<char*>(m_shader_path.c_str()), CHAR_MAX);
		}
	}

	void FileIOAdjust::JsonImport()
	{
		if (ImGui::CollapsingHeader("Json Import"))
		{
			ImGui::InputText("Import Name", json_name, CHAR_MAX);
			ImGui::Text(json_name);
			m_import_json_name = json_name;
			if (ImGui::Button("Import"))
			{
				m_import_json_path_name = "";
				m_import_json_path_name.append(m_json_path+ "/"+ m_import_json_name);
				Node::NodeEditor::Clear();
				Node::NodeEditor::Init();
				Node::NodeEditor::ImportNodeData(m_import_json_path_name);
			}
		}
	}

	void FileIOAdjust::JsonSave()
	{
		if (ImGui::CollapsingHeader("JsonSave"))
		{
			if (ImGui::Button("Save"))
			{
				Node::NodeEditor::ExportNodeData("Default/Default.json");
			}

			//if (ImGui::Button("Export"))
			//{
			//	ImGui::InputText("Import Name", json_name, CHAR_MAX);
			//	ImGui::Text(json_name);

			//	m_export_json_path_name = "";
			//	m_export_json_path_name.append(m_json_path + "/" + m_export_json_name);
			//	Node::NodeEditor::ExportNodeData("Default/Default.json");
			//}

		}
	}

	void FileIOAdjust::ShaderGenerate()
	{
		if (ImGui::CollapsingHeader("ShaderGenerate"))
		{
			ImGui::Text(const_cast<char*>(m_json_path.c_str()));
			ImGui::Text(const_cast<char*>(m_shader_path.c_str()));

			ImGui::InputText("Json Name", const_cast<char*>(m_json_import_name.c_str()), CHAR_MAX);
			ImGui::Text(const_cast<char*>(m_json_import_name.c_str()));
			ImGui::InputText("Shader Name", const_cast<char*>(m_shader_generate_name.c_str()), CHAR_MAX);
			ImGui::Text(const_cast<char*>(m_shader_generate_name.c_str()));

			if (ImGui::Button("Generate"))
			{
				if (m_json_path.empty())
				{
					m_json_import = m_json_import_name;
				}
				else
				{
					m_json_import = m_json_path + "/"/* += m_json_import_name*/;
					m_json_import += m_json_import_name;

				}

				if (m_shader_path.empty())
				{
					m_shader_generate = m_shader_generate_name;
				}
				else
				{
					m_shader_generate = m_shader_path + "/" /*+=m_shader_generate_name*/;
					m_shader_generate += m_shader_generate_name;
				}

				Shader::NodeShaderManager::JsonImport("Default/Default.json");
				Shader::NodeShaderManager::Generate("Default/Default.hlsl");
			}
		}
	}
}