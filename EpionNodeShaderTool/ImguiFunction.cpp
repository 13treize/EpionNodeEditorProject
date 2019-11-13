#include	"All.h"
#include	"../imgui\\imgui.h"
#include	"../imgui\\imgui_impl_win32.h"
#include	"../imgui\\imgui_impl_dx11.h"
#include	"../imgui\\imgui_internal.h"


#include	"ImguiFunction.h"

namespace epion
{
	ImGuiColorEditFlags ColorPicker::m_edit_flags;
	ImVec4	ColorPicker::m_backup_color;
	ImVec4	ColorPicker::m_color;
	math::FVector3	ColorPicker::m_ret_color;
	
	void ImGuiFunction::DefaultWindowFlagsSetiing(ImGuiWindowFlags& window_flags)
	{
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_MenuBar;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
	}

	void MenuBar::ShowExampleAppMain()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				//ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}


	void	ColorPicker::Init()
	{
		m_edit_flags |= ImGuiColorEditFlags_AlphaBar;
		m_edit_flags |= ImGuiColorEditFlags_NoSidePreview;
		m_edit_flags |= ImGuiColorEditFlags_PickerHueBar;
		m_edit_flags |= ImGuiColorEditFlags_Float;
		m_backup_color =ImVec4(0,0,0,0);
		m_color = ImVec4(0, 0, 0, 0);

	}

	void	ColorPicker::Activate(bool is_popup, math::FVector3& color)
	{
		if (is_popup)
		{
			ImGui::OpenPopup("mypicker");
			m_backup_color.x = color.x;
			m_backup_color.y = color.y;
			m_backup_color.z = color.z;
			m_backup_color.w =1.0;
		}
		if (ImGui::BeginPopup("mypicker"))
		{
			ImGui::Text("ColorPicker");
			ImGui::Separator();
			ImGui::ColorPicker4("##picker", (float*)&m_color, m_edit_flags);
			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Text("Current");
			ImGui::ColorButton("##current", m_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
			ImGui::Text("Previous");
			if (ImGui::ColorButton("##previous", m_backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
				m_color = m_backup_color;
			ImGui::EndGroup();
			ImGui::EndPopup();
		}

		m_ret_color.x =m_color.x;
		m_ret_color.y =m_color.y;
		m_ret_color.z =m_color.z;
	}


	void	ColorPicker::Activate(bool is_popup,math::FVector4& color)
	{
		if (is_popup)
		{
			ImGui::OpenPopup("mypicker");
			m_backup_color.x = color.x;
			m_backup_color.y = color.y;
			m_backup_color.z = color.z;
			m_backup_color.w = color.w;
		}
		if (ImGui::BeginPopup("mypicker"))
		{
			ImGui::Text("ColorPicker");
			ImGui::Separator();
			ImGui::ColorPicker4("##picker", (float*)&m_color, m_edit_flags);
			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Text("Current");
			ImGui::ColorButton("##current", m_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
			ImGui::Text("Previous");
			if (ImGui::ColorButton("##previous", m_backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
				m_color = m_backup_color;
			ImGui::EndGroup();
			ImGui::EndPopup();
		}
		m_ret_color.x = m_color.x;
		m_ret_color.y = m_color.y;
		m_ret_color.z = m_color.z;
	}

	math::FVector3& ColorPicker::GetColor()
	{
		return	m_ret_color;
	}
	ImGuiColorEditFlags&	ColorPicker::GetFrag()
	{
		return m_edit_flags;
	}

	void	ColorPicker2::Init(std::string str,std::string str2)
	{
		m_backup_color = ImVec4(0, 0, 0, 0);
		m_color = ImVec4(0, 0, 0, 0);
		m_popup_name= "mypicker"+str;
		m_picker_name= "##picker" + str;
		m_current_name= "##current" + str;
		m_previous_name= "##previous" + str;
		m_color_button_name= "MyColor"+str;
		m_button_name=str2;

	}

	void	ColorPicker2::Activate(bool is_popup, math::FVector3& color)
	{
		if (is_popup)
		{
			ImGui::OpenPopup(m_popup_name.c_str());
			m_backup_color.x = color.x;
			m_backup_color.y = color.y;
			m_backup_color.z = color.z;
			m_backup_color.w = 1.0;
		}
		if (ImGui::BeginPopup(m_popup_name.c_str()))
		{
			ImGui::Text("ColorPicker");
			ImGui::Separator();
			ImGui::ColorPicker4(m_picker_name.c_str(), (float*)&m_color, m_edit_flags);
			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Text("Current");
			ImGui::ColorButton(m_current_name.c_str(), m_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
			ImGui::Text("Previous");
			if (ImGui::ColorButton(m_previous_name.c_str(), m_backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
				m_color = m_backup_color;
			ImGui::EndGroup();
			ImGui::EndPopup();
		}

		m_ret_color.x = m_color.x;
		m_ret_color.y = m_color.y;
		m_ret_color.z = m_color.z;
	}

	void	ColorPicker2::SetInputSlotColor2(ImVec2& set_cursor, bool popup, math::FVector3& num, int label_num)
	{
		m_edit_flags |= ImGuiColorEditFlags_AlphaBar;
		m_edit_flags |= ImGuiColorEditFlags_NoSidePreview;
		m_edit_flags |= ImGuiColorEditFlags_PickerHueBar;
		m_edit_flags |= ImGuiColorEditFlags_Float;

		ImGui::SetCursorScreenPos(set_cursor + ImVec2(-90,-8));
	//	std::string	m_color_button_name;

		popup = ImGui::ColorButton(m_color_button_name.c_str(), ImVec4(num.x, num.y, num.z, 1.0f), m_edit_flags);
		ImGui::SameLine();
	//	std::string	m_button_name;

		popup |= ImGui::Button(m_button_name.c_str());

		Activate(popup, num);
		num = m_ret_color;
	}

}