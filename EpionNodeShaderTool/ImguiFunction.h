#pragma once
#include"epion.h"

/**
 * @file ImguiFunction.h
 * @brief Imgui�̃��b�p�[�֐��Q
 * @author treize
 * @date 2019/10/24
 */


namespace	epion
{
	class ImGuiFunction
	{
	public:

	};

	/**
	* @brief Imgui��p����ColorPicker�N���X
	*/

	class ColorPicker final
	{
	public:
		/**
		* @brief private�����o�[�ϐ��̏������AActivate���Ăяo���O�Ɏg��
		*/
		static void Init();
		/**
		* @brief ColorPicker���J����
		* @param[in] (is_popup) ColorPicker���J���邩�ǂ���,true��	open
		* @param[in] (color) base��color��n��
		*/
		static void Activate(bool is_popup, math::FVector3& color);
		static void Activate(bool is_popup, math::FVector4& color);

		static math::FVector3&	GetColor();
		static ImGuiColorEditFlags&	GetFrag();

	private:
		static ImGuiColorEditFlags m_edit_flags;
		static ImVec4 m_backup_color;
		static ImVec4 m_color;
		static math::FVector3 m_ret_color;
	};

	/**
	* @brief Imgui��p����ColorPicker�N���X
	*/

	class ColorPicker2 final
	{
	public:
		ColorPicker2() {}
		~ColorPicker2() {}
		/**
		* @brief private�����o�[�ϐ��̏������AActivate���Ăяo���O�Ɏg��
		*/
		void Init(std::string str, std::string str2);
		/**
		* @brief ColorPicker���J����
		* @param[in] (is_popup) ColorPicker���J���邩�ǂ���,true��	open
		* @param[in] (color) base��color��n��
		*/
		void Activate(bool is_popup, math::FVector3& color);

		void SetInputSlotColor2(ImVec2& set_cursor, bool popup, math::FVector3& num, int label_num = 0);

	private:
		ImGuiColorEditFlags m_edit_flags;
		ImVec4 m_backup_color;
		ImVec4 m_color;
		math::FVector3 m_ret_color;
		std::string	m_popup_name;
		std::string	m_picker_name;
		std::string	m_current_name;
		std::string	m_previous_name;
		std::string	m_color_button_name;
		std::string	m_button_name;

	};

	class MenuBar final
	{
	public:
		static void ShowExampleAppMain();
	};
}