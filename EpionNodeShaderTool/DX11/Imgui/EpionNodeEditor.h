#pragma once
#include	<string>

namespace	epion::NodeCustom
{
	constexpr	int	INIT_NUM = -1;

	const float zoom_levels[] =
	{
		0.1f,	0.15f,	0.20f,	0.25f,	0.33f,	0.5f,
		0.75f,	1.0f,	1.25f,	1.50f,	2.0f,	2.5f,
		3.0f,	4.0f,	5.0f,	6.0f,	7.0f,	8.0f
	};

	class	NodeBase;
	class	NodeLink;
	class	Grids;

	class	ConstantState;

	//マウスをクリックしたときに保持すべき情報
	struct	ClickState
	{
		int	id;
		int	slot;
		ImVec2	pos;
		bool	is_click_display;
		bool	is_click_input_slot;
		bool	is_click_output_slot;
	};

	class	NodeEditor	final
	{
	public:
		static	void	Init();
		static	void	Update(bool* opened, std::string	node_bar_name);

		static	void	Clear();

		static	void	release();

		static	void	import_node_data(std::string nodejson);

		static	void	default_setting_unlit();


		static	void	constant_state_update();

		static	std::string	export_node_data();

		static	void	draw_node_line(ImDrawList*	draw_list);

		static	void	create_node_data(ImDrawList*	draw_list, int scene);

		static	void	create_hlsl();


		static	void	scrolling_event();

		//	get
		static	ImVec2&	get_scrolling();
		static	ImVec2&	get_offset();

		static	int		GetNodeSize();
		static	int		GetLinkSize();

		static	std::vector<std::unique_ptr<NodeBase>>	nodes;

		static	std::vector<NodeLink>	links;

	private:
		static ImGuiWindowFlags m_window_flags;

		static	bool	m_is_node_import;
		static	bool	m_is_node_moving;

		static	bool	m_is_line;
		static	bool	m_is_open_context_menu;

		//クリック時に保持する情報
		static	ClickState	m_click_state;

		static	ConstantState	m_constant_state;
		static	int	m_node_select_num;
		static	int	m_node_hovered_list;
		static	int	m_node_hovered_in_scene;

		static	float	m_scale;

		static	ImVec2	m_scrolling;
		static	float	m_delta;

		static	ImVec2	m_offset;
		static	ImVec2	m_drag_offset;

		static	ImVec2	m_screen_pos;
		static	ImVec2	m_context_pos;

		static	float	m_line_size;

		static	Grids	grid;


		static	void	mouse_update();

		static	void	draw_node_rect();



	};
}