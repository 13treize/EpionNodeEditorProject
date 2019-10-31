#include	"../../All.h"
#include	"../../epion.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../ImguiFunction.h"

#include	"dx11_imgui_main_window.h"
#include	"../dx11_dxgi.h"

#include	"../ConstantBuffer.h"

#include	"EpionNodeEditor.h"
#include	"epion_imgui_node_context.h"

#include	"../../Node/NodeData.h"
#include	"../../ImguiFunction.h"

#include	"../../ShaderGenerate/ShaderGenerate.h"
#include	"../square.h"
#include	"../texture.h"

#include	"../../epion_string.h"

#pragma warning(disable:4996)

namespace
{
	ImGuiCond_	state_bar = ImGuiCond_::ImGuiCond_Appearing;
	constexpr	int CHAR_SIZE = 256;
	float a[4] = {};
	bool is_tex;
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


		bool	is_reset;
		bool	is_link_reset;

		bool	is_shader_reset;

		std::string	json_name;

		int	node_size;

		char node_title_name[CHAR_MAX] = "";
		char node_shader_name[CHAR_MAX] = "";
		char import_json_name[CHAR_MAX] = "";

		//(L"Assets//sa.jpg");

		std::unique_ptr<Texture>	preview_resouce;
		//private:

		//テクスチャの数を取得
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
		m_impl->is_reset = false;
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
		m_impl->is_reset = false;
		m_impl->is_link_reset = false;

		m_impl->is_shader_reset = false;

		m_impl->is_unlit_setting = false;

		m_impl->json_name = "";

		m_impl->node_size = 0;

		//m_impl->preview = std::make_unique<Square>();
		m_impl->preview_resouce = std::make_unique<Texture>();
		m_impl->preview_resouce->Create(400, 400, DXGI_FORMAT_R16G16B16A16_FLOAT);

		m_preview_resouce = std::make_unique<Texture>();
		m_preview_resouce->Create(400, 400, DXGI_FORMAT_R16G16B16A16_FLOAT);

		m_impl->window_flags |= ImGuiWindowFlags_NoTitleBar;
		m_impl->window_flags |= ImGuiWindowFlags_MenuBar;
		m_impl->window_flags |= ImGuiWindowFlags_NoMove;
		m_impl->window_flags |= ImGuiWindowFlags_NoResize;


		//TextureInit();
		NodeCustom::ContextManager::Init();
		ImGui::StyleColorsDark();
		NodeCustom::NodeEditor::Init();
		ColorPicker::Init();
		Preview::Init(L"test.hlsl");
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
			Shader::NodeShaderManager::json_import("test.json");

			Shader::NodeShaderManager::generate("test.hlsl");

		}


		if (m_impl->is_update)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 600), state_bar);

			ImGui::Begin("MainWindow", &m_impl->is_update, m_impl->window_flags);

			auto&	io = ImGui::GetIO();
			float my_tex_w = (float)io.Fonts->TexWidth;
			float my_tex_h = (float)io.Fonts->TexHeight;
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
							//std::string path = "GenarateNodeJson\\";
							NodeCustom::NodeEditor::Clear();
							NodeCustom::NodeEditor::Init();
							//		NodeCustom::ContextManager::init();
							std::string path = "test.json";
							NodeCustom::NodeEditor::import_node_data(path);
						}
						ImGui::SameLine();
						ImGui::InputText("JsonName", m_impl->import_json_name, CHAR_MAX);

						//nodeセーブ
						if (ImGui::Button("SaveNodeData"))
						{
							m_impl->json_name = NodeCustom::NodeEditor::export_node_data();
							//m_impl->is_node_export = true;
						}


						//export_shader_name
						//ImGui::InputText("ShaderName", m_impl->node_shader_name, CHAR_MAX);

						//create_shader
						(ImGui::Button("CreateShader")) ? m_impl->is_hlsl_export = true : m_impl->is_hlsl_export = false;
						ImGui::SameLine();
						ImGui::InputText("ShaderName", m_impl->node_shader_name, CHAR_MAX);

						//reset_shader
						if(ImGui::Button("Updatehlsl"))	Preview::Init(L"test.hlsl");
						ImGui::EndTabItem();
					}
					//if (ImGui::BeginTabItem("Texture"))
					//{
					//	TextureUpdate();
					//	ImGui::EndTabItem();
					//}
					if (ImGui::BeginTabItem("Node"))
					{
						ImGui::Text("Node size %d", NodeCustom::NodeEditor::get_node_size());
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Link"))
					{
						ImGui::Text("Link size %d", NodeCustom::NodeEditor::get_link_size());
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
			m_impl->tex_resouce[i]->Create(200, 200, DXGI_FORMAT_R16G16B16A16_FLOAT);

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
					TextureFile::LoadTexture(StringConverter::to_wstring(m_impl->tex_name[i]), m_impl->tex_resouce[i]->metadata, m_impl->tex_resouce[i]->image, m_impl->tex_resouce[i]->ShaderResourceView);
					m_impl->is_tex[i] = true;
				}
				if (m_impl->is_tex[i])
				{
					if (ImGui::Button("Close"))
					{
						m_impl->is_tex[i] = false;
					}
					ImGui::Image(m_impl->tex_resouce[i]->ShaderResourceView.Get(), ImVec2(200, 200), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(1, 0, 0, 1));
				}

			}
			ImGui::TreePop();
		}
	}

	void	ImguiMain::PreviewEvent()
	{
		ImGui::Text("Preview");
		//ImGui::Image(m_preview_resouce->ShaderResourceView.Get(), ImVec2(400,400), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 0));
		//TextureFile::SaveTexture("test3", ".jpg", m_preview_resouce->Texture2D);
	}
	void	ImguiMain::ResetEvent()
	{
		m_impl->is_reset = ImGui::Button("Reset");
		if (m_impl->is_reset)
		{
			NodeCustom::NodeEditor::Clear();
			NodeCustom::NodeEditor::Init();
			NodeCustom::ContextManager::Init();
			//m_impl->preview = std::make_unique<Square>();
			TextureFile::SaveTexture("test2", ".jpg", Dxgi::back_buffer);

		}
		m_impl->is_link_reset = ImGui::Button("LinkReset");
		if (m_impl->is_link_reset)
		{

		}
	}

	std::unique_ptr<Square>			Preview::m_preview;
	std::unique_ptr<VertexShader>	Preview::m_vertex;
	std::unique_ptr<PixelShader>	Preview::m_pixel;
	math::FVector4					Preview::time;

	bool	Preview::Init(std::wstring	ps_name)
	{
		ConstantBufferManager::Create();
		m_vertex=std::make_unique<VertexShader>(L"HLSLShader\\square_vertex_shader.hlsl");
		m_pixel = std::make_unique<PixelShader>(ps_name);
		m_preview = std::make_unique<Square>(m_vertex->GetBlob());
		time.x = 0.0f;
		return true;
	}
	void	Preview::Render()
	{
		time.x += 0.01f;
		math::FVector2 a = {1920,1080};
		ConstantBufferManager::UpdateCBuffer0(time,a);
		m_vertex->SetState();
		m_pixel->SetState();
		m_preview->render(math::FVector2(1450, 650), math::FVector2(400, 400), 0, FixColor::Red);
	}

}