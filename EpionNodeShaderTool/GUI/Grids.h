#pragma once
namespace	epion::GUI
{
	//ƒOƒŠƒbƒh•`‰æ
	class	BackGrids
	{
	public:
		BackGrids() = delete;
		BackGrids(float	size, ImU32	color);

		~BackGrids();
		void	Init(float	size, ImU32	color);
		void	Draw(ImDrawList*	draw_list, ImVec2	win_pos, ImVec2	canvas_size, const	ImVec2&	scroll);

	private:
		bool	m_is_show_grid;
		float	m_grid_size;
		ImVec2	m_win_pos = ImGui::GetCursorScreenPos();
		ImVec2	m_canvas_size = ImGui::GetWindowSize();
		ImU32	m_grid_color;

	};
}
