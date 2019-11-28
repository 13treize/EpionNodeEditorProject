#pragma once

namespace	epion::NodeCustom
{
	constexpr	int	INIT_NUM = -1;

	const float zoom_levels[] =
	{
		0.1f,	0.15f,	0.20f,	0.25f,	0.33f,	0.5f,
		0.75f,	1.0f,	1.25f,	1.50f,	2.0f,	2.5f,
		3.0f,	4.0f,	5.0f,	6.0f,	7.0f,	8.0f
	};

	//struct	SettingsParam
	//{
	//	int	m_create_count;	//ノードのサイズ
	//};

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

		static	void	Release();

		static	void	ImportNodeData(std::string nodejson);


		static	std::string	ExportNodeData(const std::string& json_name);

		static	void	DrawLinkLine(ImDrawList*	draw_list);


		//	get
		static	ImVec2&	GetScrolling();
		static	ImVec2&	GetOffset();

		static	int		GetNodeSize();
		static	int		GetLinkSize();

		static	std::vector<std::unique_ptr<NodeBase>>	nodes;


		// list推奨
		static	std::vector<NodeLink>	links;

	private:
		static ImGuiWindowFlags m_window_flags;

		static	bool	m_is_node_import;
		static	bool	m_is_node_moving;

		static	bool	m_is_line;
		static	bool	m_is_line_delete_menu;
		static	bool	m_is_open_context_menu;

		static	bool	m_is_node_push;


		//クリック時に保持する情報
		static	ClickState	m_click_state;

		static	ConstantState	m_constant_state;
		static	int	m_node_select_num;
		static	int	m_node_hovered_list;
		static	int	m_node_hovered_in_scene;

		static	float	m_scale;

		static	float	m_delta;

		static	ImVec2	m_offset;
		static	ImVec2	m_drag_offset;

		static	ImVec2	m_screen_pos;

		static	float	m_line_size;

		//Node
		static	void	NodeUpdate(ImDrawList* draw_list);
		static	void	NodeDrag(ImDrawList* draw_list, int size);
		static	void	NodeDraw(ImDrawList* draw_list, int size);
		static	void	NodeInputUpdate(ImDrawList* draw_list, int size);
		static	void	NodeOutputUpdate(ImDrawList* draw_list, int size);
		static	void	NodeTabBar();

		static	bool	m_is_node_widgets_active;
		static	bool	m_is_now_any_active;
		static	bool	m_is_old_any_active;

		//Mouse
		static	void	MouseUpdate(ImDrawList* draw_list);
		static	void	CallContext();
		static	void	Drag(ImDrawList* draw_list);
		static	void	Enclose(ImDrawList* draw_list);
		static	void	Scroll();
		static ImVec2	m_context_pos;
		static ImVec2	m_enclose_pos;
		static ImVec2	m_scrolling_pos;

	};
}