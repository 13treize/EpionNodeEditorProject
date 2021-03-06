#pragma once
#include	"../Node/NodeData.h"
#include	"Grids.h"

//namespace epion::Node
//{
//	class NodeBase;
//	class NodeLink;
//
//}
namespace epion::GUI
{
	struct	ClickState
	{
		int	id;
		int	slot;
		ImVec2	pos;
		bool	is_click_display;
		bool	is_click_input_slot;
		bool	is_click_output_slot;
	};

	class NodeWindow final
	{
	public:
		bool Init();
		void Update(std::vector<std::string>&	node_names);

		std::vector<std::unique_ptr<Node::NodeBase>>&	GetNodes();
		std::vector<Node::NodeLink>&	GetLinks();

	private:
		std::string m_get_node_name;
		ImVec2	m_offset;
		int	m_node_select_num;
		int	m_node_hovered_list;
		int	m_node_hovered_in_scene;

		//ImGui Settings
		ImGuiTabBarFlags m_bar_flags;
		void ChildSettings();

		ClickState	m_click_state;

		bool	m_is_node_widgets_active;
		bool	m_is_now_any_active;
		bool	m_is_old_any_active;
		std::vector<std::unique_ptr<Node::NodeBase>>	m_nodes;
		std::vector<Node::NodeLink>	m_links;

		//Link
		int m_hit_line_num;
		float m_line_size;
		bool m_is_line_hit;
		bool m_is_slot_hit;

		void DrawLinkLine(ImDrawList* draw_list);

		//Node
		int		m_hit_node_num;
		bool	m_is_node_push;

		void	NodeUpdate(ImDrawList* draw_list);
		void	NodeMouseUpdate(ImDrawList* draw_list, int size);
		void	NodeDraw(ImDrawList* draw_list, int size);
		void	NodeInputUpdate(ImDrawList* draw_list, int size);
		void	NodeOutputUpdate(ImDrawList* draw_list, int size);
		void	NodeTabBar();
		void	NodeErase(ImDrawList* draw_list, int size);

		//Mouse
		void	MouseUpdate(ImDrawList* draw_list);

		void	CallContext();
		void	Drag(ImDrawList* draw_list);
		void	Enclose(ImDrawList* draw_list);
		void	Scroll();
		ImVec2	m_enclose_pos;
		float	m_scroll_scale;

	};
}