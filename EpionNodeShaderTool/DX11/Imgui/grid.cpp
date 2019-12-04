#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"


#include	"grid.h"


namespace	epion::NodeCustom
{
	//ƒOƒŠƒbƒh
	Grids::Grids(float	size, ImU32	color)
		:m_is_show_grid(true),
		m_grid_size(size),
		m_grid_color(color)
	{
	}
	Grids::~Grids()
	{
	}

	void	Grids::Init(float	size, ImU32	color)
	{
		m_is_show_grid	=true;
		m_grid_size	=size;
		m_grid_color = color;
	}

	void	Grids::ShowGrid(ImDrawList*	draw_list, ImVec2	win_pos, ImVec2	canvas_size, const	ImVec2&	scroll)
	{
		m_win_pos = win_pos;
		m_canvas_size = canvas_size;

		if (m_is_show_grid)
		{
			for (float x = fmodf(scroll.x, m_grid_size); x < m_canvas_size.x; x += m_grid_size)
			{
				draw_list->AddLine(ImVec2(x, 0.0f) + m_win_pos, ImVec2(x, m_canvas_size.y) + m_win_pos, m_grid_color);
			}

			for (float y = fmodf(scroll.y, m_grid_size); y < m_canvas_size.y; y += m_grid_size)
			{
				draw_list->AddLine(ImVec2(0.0f, y) + m_win_pos, ImVec2(m_canvas_size.x, y) + m_win_pos, m_grid_color);
			}
		}
	}
}