#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"


#include	"../../ImguiFunction.h"

#include	"ImguiMainWindow.h"
#include	"PreviewWindow.h"
#include	"../dx11_dxgi.h"

#include	"EpionNodeEditor.h"
#include	"ImguiNodeContext.h"

#include	"../../Node/NodeData.h"

#include	"../../ShaderGenerate/ShaderGenerate.h"
#include	"../texture.h"

#include	"../../Scene/SceneManager.h"
#include	"../../Scene/SceneDemo2D.h"
#include	"../../Scene/SceneDemo3D.h"

#pragma warning(disable:4996)

namespace
{
	bool is_tex;
	//std::string path = "GenerateNodeJson/test3.json";
	std::string path = "test3.json";

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
		//bool	is_show_node_window;


		bool	is_link_reset;

		bool	is_shader_reset;

		std::string	json_name;

		int	node_size;

		char node_title_name[CHAR_MAX] = "";
		char node_shader_name[CHAR_MAX] = "";

		std::unique_ptr<Texture>	preview_resouce;

	};

	ImguiMain::ImguiMain() :m_impl(std::make_unique<ImguiMain::Impl>())
	{
		m_impl = std::make_unique<ImguiMain::Impl>();
		m_impl->is_update = true;
		m_is_update_node = true;
		m_is_node_window = true;


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
		m_is_update_node = true;
		is_reset = false;
		m_impl->is_link_reset = false;

		m_impl->is_shader_reset = false;

		m_impl->json_name = "";

		m_impl->node_size = 0;

		//m_impl->preview = std::make_unique<Square>();
		m_impl->preview_resouce = std::make_unique<Texture>();
		m_impl->preview_resouce->Create(400, 400, DXGI_FORMAT_R16G16B16A16_FLOAT);

		//m_preview_resouce = std::make_unique<Texture>();
		//m_preview_resouce->Create(400, 400, DXGI_FORMAT_R16G16B16A16_FLOAT);
		m_select_scene = 0;

		m_is_node_window = true;

		ImGuiFunction::DefaultWindowFlagsSetiing(m_impl->window_flags);


		m_texture_adjust.Init();
		NodeCustom::ContextManager::Init();
		ImGui::StyleColorsDark();
		NodeCustom::NodeEditor::Init();
		ColorPicker::Init();
		m_tex_resouce.Init();
		m_file_io_adjust.Init();
		Preview::Init(L"Default/Init.hlsl",m_tex_resouce.GetTexNames(),1);
	}

	void	ImguiMain::impl_update()
	{
	}

	void	ImguiMain::Update()
	{
		if (m_is_node_window)
		{
			NodeCustom::NodeEditor::Update(&m_is_update_node, m_impl->node_title_name);
		}


		if (m_impl->is_update)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_::ImGuiCond_Appearing);

			ImGui::Begin("MainWindow", &m_impl->is_update, m_impl->window_flags);

			ImGui::PushItemWidth(200.0f);

			//MenuBar::ShowExampleAppMain();
			ImGui::Checkbox("NodeWindow", &m_is_node_window);

			//create_shader
			if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
			{

				m_file_io_adjust.Update();

				m_texture_adjust.Update();
				ShaderSet();
				if (ImGui::BeginTabItem("TexParam"))
				{
					m_tex_resouce.Update();
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Node"))
				{
					ImGui::Text("Node size %d", NodeCustom::NodeEditor::GetNodeSize());
					for (const auto& n : NodeCustom::NodeEditor::nodes)
					{
						ImGui::Text("Node pos x %d, y %d", n->m_Pos.x ,n->m_Pos.y);

					}
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
				SceneUpdate();

				if (ImGui::BeginTabItem("Option"))
				{
					ImGui::Text("Option");
					auto&	io = ImGui::GetIO();
					ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
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

#pragma region File Settings

	void ImguiMain::ShaderSet()
	{
		if (ImGui::Button("Updatehlsl"))
		{
			Preview::Init(L"Default/Default.hlsl", m_tex_resouce.GetTexNames());
		}
	}

#pragma endregion


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

	void	ImguiMain::SceneUpdate()
	{
		if (ImGui::BeginTabItem("DemoScene"))
		{
			if (ImGui::RadioButton("Demo 2D", &m_select_scene, 0))
			{
				SceneManager::SetNextScene<SceneDemo2D>();
			}
			if (ImGui::RadioButton("Demo 3D", &m_select_scene, 1))
			{
				SceneManager::SetNextScene<SceneDemo3D>();
			}
			ImGui::EndTabItem();
		}
	}
}