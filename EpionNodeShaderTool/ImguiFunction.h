#pragma once
#include"epion.h"

/**
 * @file ImguiFunction.h
 * @brief Imguiのラッパー関数群
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
	* @brief Imguiを用いたColorPickerクラス
	*/

	class ColorPicker final
	{
	public:
		/**
		* @brief privateメンバー変数の初期化、Activateを呼び出す前に使う
		*/
		static void Init();
		/**
		* @brief ColorPickerを開ける
		* @param[in] (is_popup) ColorPickerを開けるかどうか,trueで	open
		* @param[in] (color) baseのcolorを渡す
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
	* @brief Imguiを用いたColorPickerクラス
	*/

	class ColorPicker2 final
	{
	public:
		ColorPicker2() {}
		~ColorPicker2() {}
		/**
		* @brief privateメンバー変数の初期化、Activateを呼び出す前に使う
		*/
		void Init(std::string str, std::string str2);
		/**
		* @brief ColorPickerを開ける
		* @param[in] (is_popup) ColorPickerを開けるかどうか,trueで	open
		* @param[in] (color) baseのcolorを渡す
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