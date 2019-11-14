#include	"../../All.h"
#include	"../../epion.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../ImguiFunction.h"

#include	"dx11_imgui_main_window.h"
#include	"PreviewWindow.h"
#include	"../dx11_dxgi.h"

#include	"EpionNodeEditor.h"
#include	"epion_imgui_node_context.h"

#include	"../../Node/NodeData.h"

#include	"../../ShaderGenerate/ShaderGenerate.h"
#include	"../texture.h"

#pragma warning(disable:4996)

namespace
{
	//float a[4] = {};
	bool is_tex;
	std::string path = "GenerateNodeJson\\test.json";

}


namespace	epion
{
	//PImpl
	class	ImguiMain::Impl
	{
	public:
		ImGuiWindowFlags window_flags;

		std::array<float, 4>	m_back_color;

		bool	is_update;
		bool	is_update_node;
		bool	is_show_node_window;
		bool	is_hlsl_export;

		bool	is_unlit_setting;

		bool	is_link_reset;

		bool	is_shader_reset;

		std::string	json_name;

		int	node_size;

		char node_title_name[CHAR_MAX] = "";
		char node_shader_name[CHAR_MAX] = "";

		//(L"Assets//sa.jpg");

		std::unique_ptr<Texture>	preview_resouce;
		//private:

		//�e�N�X�`���̐����擾
		int	tex_num;
		std::vector<bool>	is_tex;
		std::vector<std::string>	tex_name;
		std::vector<std::unique_ptr<Texture>>	tex_resouce;

	};

	ImguiMain::ImguiMain() :m_impl(std::make_unique<ImguiMain::Impl>())
	{
		m_impl = std::make_unique<ImguiMain::Impl>();
		m_impl->is_update = true;
		m_impl->is_update_node = true;
		m_impl->is_show_node_window = true;


		m_impl->is_hlsl_export = false;
		is_reset = false;
		m_impl->is_shader_reset = false;

		m_impl->json_name = "";

		m_impl->node_size = 0;
		//m_impl->preview = std::make_unique<Square>();

	}

	ImguiMain::~ImguiMain()
	{

	}

	//https://qiita.com/izumin5210/items/26eaed69eea2c4318fcd
	void	ImguiMain::Init()
	{
		m_impl = std::make_unique<ImguiMain::Impl>();
		m_impl->is_update = true;
		m_impl->is_update_node = true;
		m_impl->is_show_node_window = true;
		m_impl->is_hlsl_export = false;
		is_reset = false;
		m_impl->is_link_reset = false;

		m_impl->is_shader_reset = false;

		m_impl->is_unlit_setting = false;

		m_impl->json_name = "";

		m_impl->node_size = 0;

		//m_impl->preview = std::make_unique<Square>();
		m_impl->preview_resouce = std::make_unique<Texture>();
		m_impl->preview_resouce->Create(400, 400, DXGI_FORMAT_R16G16B16A16_FLOAT);

		//m_preview_resouce = std::make_unique<Texture>();
		//m_preview_resouce->Create(400, 400, DXGI_FORMAT_R16G16B16A16_FLOAT);


		ImGuiFunction::DefaultWindowFlagsSetiing(m_impl->window_flags);



		TextureInit();
		NodeCustom::ContextManager::Init();
		ImGui::StyleColorsDark();
		NodeCustom::NodeEditor::Init();
		ColorPicker::Init();
		m_tex_resouce.Init();
		Preview::Init(L"test.hlsl",m_tex_resouce.GetTexNames(),1);
	}

	void	ImguiMain::impl_update()
	{
	}

	void	ImguiMain::Update()
	{

		if (m_impl->is_show_node_window)
		{
			NodeCustom::NodeEditor::Update(&m_impl->is_update_node, m_impl->node_title_name);
		}


		if (m_impl->is_hlsl_export)
		{
			//Shader::NodeShaderManager::json_import("test.json");
			//Shader::NodeShaderManager::generate(m_impl->node_shader_name);
			Shader::NodeShaderManager::json_import("GenerateNodeJson\\test.json");

			Shader::NodeShaderManager::generate("test.hlsl");
		}


		if (m_impl->is_update)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_::ImGuiCond_Appearing);

			ImGui::Begin("MainWindow", &m_impl->is_update, m_impl->window_flags);

			auto&	io = ImGui::GetIO();
			//ImGui::Image(m_impl->shader_resouce_view.Get(), ImVec2(512,512));

			ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

			ImGui::PushItemWidth(200.0f);

			MenuBar::ShowExampleAppMain();
			ImGui::Checkbox("NodeWindow", &m_impl->is_show_node_window);

			//create_shader
			if (m_impl->is_show_node_window)
			{
				if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("MainMenu"))
					{

						ResetEvent();
						//reset

						//import jsonfile
						if (ImGui::Button("Import"))
						{
							//std::string path = "GenerateNodeJson\\";
							std::string path = "GenerateNodeJson\\test.json";
							//path += import_json_name;
							NodeCustom::NodeEditor::Clear();
							NodeCustom::NodeEditor::Init();
							//		NodeCustom::ContextManager::init();
							NodeCustom::NodeEditor::import_node_data(path);
						}
						ImGui::SameLine();
						ImGui::InputText("JsonName", const_cast<char*>(import_json_name.c_str()), CHAR_MAX);

						ImGui::Text(import_json_name.c_str());

						//Node����Json�ɏ����o��
						if (ImGui::Button("SaveNodeData"))
						{
							m_impl->json_name = NodeCustom::NodeEditor::ExportNodeData(path);
						}


						//export_shader_name
						//ImGui::InputText("ShaderName", m_impl->node_shader_name, CHAR_MAX);

						//create_shader
						(ImGui::Button("CreateShader")) ? m_impl->is_hlsl_export = true : m_impl->is_hlsl_export = false;
						ImGui::SameLine();
						ImGui::InputText("ShaderName", m_impl->node_shader_name, CHAR_MAX);

						//reset_shader
						if(ImGui::Button("Updatehlsl"))	Preview::Init(L"test.hlsl", m_tex_resouce.GetTexNames());
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Texture"))
					{
						TextureUpdate();
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("TexParam"))
					{
						m_tex_resouce.Update();
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Node"))
					{
						ImGui::Text("Node size %d", NodeCustom::NodeEditor::GetNodeSize());
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Link"))
					{
						ImGui::Text("Link size %d", NodeCustom::NodeEditor::GetLinkSize());
						if (ImGui::TreeNode("LinkState"))
						{
							for (auto & li : NodeCustom::NodeEditor::links)
							{
								ImGui::Text(li.StateStr().c_str());
							}
							ImGui::TreePop();
						}
						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			}
			PreviewEvent();
			ImGui::End();
		}
	}

	void	ImguiMain::Render()
	{
		Preview::Render();
		//m_impl->preview->render(m_impl->time, math::FVector2(1450, 650), math::FVector2(400, 400), 0, FixColor::Red);
	}

	void	ImguiMain::TextureInit()
	{
		for (auto& x : std::filesystem::directory_iterator("Assets"))
		{
			m_impl->tex_name.push_back(x.path().string());
			m_impl->tex_num++;
			m_impl->is_tex.push_back(false);
		}
		m_impl->tex_resouce.resize(m_impl->tex_num);

		for (int i = 0; i < m_impl->tex_num; i++)
		{
			m_impl->tex_resouce[i] = std::make_unique<Texture>();
			TextureFileIO::LoadTexture(StringConverter::to_wstring(m_impl->tex_name[i]), m_impl->tex_resouce[i]->m_metadata, m_impl->tex_resouce[i]->m_image, m_impl->tex_resouce[i]->m_shader_resource);
		}
	}
	void	ImguiMain::TextureUpdate()
	{
		if (ImGui::TreeNode("Texture"))
		{
			for (int i = 0; i < m_impl->tex_num; i++)
			{
				if (ImGui::Button(m_impl->tex_name[i].c_str()))
				{
					m_impl->is_tex[i] = true;
				}
				if (m_impl->is_tex[i])
				{
					if (ImGui::Button("Close"))
					{
						m_impl->is_tex[i] = false;
					}
					ImGui::Image(m_impl->tex_resouce[i]->m_shader_resource.Get(), ImVec2(200, 200), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(1, 0, 0, 1));
				}
			}
			ImGui::TreePop();
		}
	}

	void	ImguiMain::PreviewEvent()
	{
		ImGui::Text("Preview");
		//ImGui::Image(m_preview_resouce->ShaderResourceView.Get(), ImVec2(400,400), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 0));
		//TextureFileIO::SaveTexture("test3", ".jpg", m_preview_resouce->Texture2D);
	}
	void	ImguiMain::ResetEvent()
	{
		is_reset = ImGui::Button("Reset");
		if (is_reset)
		{
			NodeCustom::NodeEditor::Clear();
			NodeCustom::NodeEditor::Init();
			NodeCustom::ContextManager::Init();
			//m_impl->preview = std::make_unique<Square>();
			TextureFileIO::SaveTexture("GenerateTexture\\out", ".jpg", Dxgi::back_buffer);

		}
		m_impl->is_link_reset = ImGui::Button("LinkReset");
		if (m_impl->is_link_reset)
		{

		}
	}


}