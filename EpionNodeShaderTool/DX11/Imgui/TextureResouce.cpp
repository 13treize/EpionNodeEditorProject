#include	"../../All.h"
#include	"../../epion.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../ImguiFunction.h"

#include	"TextureResouce.h"
#include	"../texture.h"

namespace epion
{
	void	TextureResouce::Init()
	{
		directory_name = "Assets\\";
		for (auto& x : std::filesystem::directory_iterator("Assets"))
		{
			m_combo_file_names.push_back(x.path().string());
			is_combo_selected.push_back(false);
		}
	}

	void	TextureResouce::Update()
	{
		ImGui::InputText("Directory", directory_input_name, CHAR_MAX);
		ImGui::Text(directory_name.c_str());
		ImGui::InputText("ShaderName", tex_input_name, CHAR_MAX);
		if (ImGui::Button("PushBack"))
		{
			m_tex_name.push_back("");

			if (m_tex_name.size() > m_tex_display_str.size())
			{
				m_tex_display_str.push_back("Texture Name" + StringConverter::get_space(static_cast<int>(m_tex_name.size())));
				m_tex_title.push_back("Slot " + std::to_string(m_tex_name.size() - 1));
				m_is_tex.push_back(false);
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("PopBack") && !m_tex_name.empty())
		{
			m_tex_name.pop_back();
		}

		for (int i = 0; i < m_tex_name.size(); i++)
		{
			if (ImGui::TreeNode(m_tex_title[i].c_str()))
			{
				ComboUpdate(i);
				ImGui::TreePop();
			}
			ImGui::Separator();
		}
	}
	void TextureResouce::ComboUpdate(int i)
	{
		if (ImGui::BeginCombo("TextureName", m_tex_name[i].c_str()))
		{
			for (int j = 0; j < m_combo_file_names.size(); j++)
			{
				if (m_tex_name[i] == m_combo_file_names[j])
				{
					is_combo_selected[j] = true;
				}
				else
				{
					is_combo_selected[j] = false;
				}
				if (ImGui::Selectable(m_combo_file_names[j].c_str(), is_combo_selected[j]))
				{
					m_tex_name[i] = m_combo_file_names[j];
				}
				if (is_combo_selected[j])
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
	std::vector<std::string>&	TextureResouce::GetTexNames()
	{
		return m_combo_file_names;
	}
}