#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../ImguiFunction.h"

#include	"../../Node/NodeData.h"

#include	"../../ShaderGenerate/ShaderGenerate.h"
#include	"../texture.h"

#include	"TextureAdjust.h"
#include	"EpionNodeEditor.h"

namespace	epion::GUI
{
	TextureAdjust::TextureAdjust()
	{
	}

	TextureAdjust::~TextureAdjust()
	{
	}

	void TextureAdjust::Init()
	{
		for (auto& x : std::filesystem::directory_iterator("Assets"))
		{
			if (x.path().extension() != "")
			{
				m_tex_name.push_back(x.path().string());
				m_tex_num++;
				m_is_tex.push_back(false);
			}
		}
		m_tex_resouce.resize(m_tex_num);

		for (int i = 0; i < m_tex_num; i++)
		{
			m_tex_resouce[i] = std::make_unique<Texture>();
			TextureFileIO::LoadTexture(StringConverter::to_wstring(m_tex_name[i]), m_tex_resouce[i]->m_metadata, m_tex_resouce[i]->m_image, m_tex_resouce[i]->m_shader_resource);
		}
	}

	void TextureAdjust::Update()
	{
		if (ImGui::BeginTabItem("Texture"))
		{
			if (ImGui::TreeNode("Texture"))
			{
				for (int i = 0; i < m_tex_num; i++)
				{
					if (ImGui::Button(m_tex_name[i].c_str()))
					{
						m_is_tex[i] = true;
					}
					if (m_is_tex[i])
					{
						if (ImGui::Button("Close"))
						{
							m_is_tex[i] = false;
						}
						ImGui::Image(m_tex_resouce[i]->m_shader_resource.Get(), ImVec2(200, 200), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(1, 0, 0, 1));
					}
				}
				ImGui::TreePop();
			}
			ImGui::EndTabItem();
		}
	}
}