#pragma once

namespace epion::Node
{
	class NodeBase;
}
namespace epion::GUI
{
	enum NodeType :unsigned char
	{
		Artistic = 0,
		Channel,
		Input,
		Master,
		Math,
		Procedural,
		Utility,
		UV,
		Noise,
		ArraySize
	};

	//InputBasic,
	//	MathBasic,
	//	MathAdvanced,
	class	ContextManager	final
	{
	public:
		static	void	Init();
		static	void	Update(ImVec2& offset, std::vector<std::unique_ptr<Node::NodeBase>>& nodes);

		static	void	DragAndDropEvent();

		static	void	ClickEvent(ImVec2& offset);
		static	void	SetContext(bool is_set);
		static	bool	GetContext();
		static	void	OpenContext(bool is_set, ImVec2& pos);

		static	void	LineEvent();
		static	void	SetLineMenu(bool is_set);
		static	bool	GetLineMenu();

		static	void	SetCreateCount(int size);

		static	void	ClickAdd();

		static void reset_create_count()
		{
			m_create_count = 0;
		}
	private:
		static bool		m_is_open_menu[ArraySize];
		static std::string	m_str_menu[ArraySize];

		static	ImVec2	m_offset;

		static	ImVec2	m_menu_pos;


		//IDを割り振るためのカウント,被りはダメ
		static	int	m_create_count;

		//input
		static	bool	m_is_open_artistic_adjustment_menu;

		static	bool	m_is_open_input_basic_menu;
		static	bool	m_is_open_input_texture_menu;

		static	bool	m_is_open_math_advanced_menu;
		static	bool	m_is_open_math_basic_menu;
		static	bool	m_is_open_math_range_menu;
		static	bool	m_is_open_math_round_menu;
		static	bool	m_is_open_math_wave_menu;

		static	bool	m_is_open_context_menu;
		static	bool	m_is_open_line_menu;

		static	bool	m_is_open_node_menu;

		static	inline	void	ArtisticContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	ChannelContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	InputContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	MasterContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	MathContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	ProceduralContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	UtilityContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	UVContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);
		static	inline	void	NoiseContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes);

		static	inline	void	BaseMenuContext(const std::string& menu_name, bool& is_back, bool& is_current);
		static	inline	void	CloseContext(bool& is_current);
		static	inline	void	BackContext(bool& is_back, bool& is_current);

		static	inline	void	PopupBeginSettings();
		static	inline	void	PopupEndSettings();
		static	inline	void	MenuItem(const std::string& str, NodeType type, bool&is_menu);

	};
}

