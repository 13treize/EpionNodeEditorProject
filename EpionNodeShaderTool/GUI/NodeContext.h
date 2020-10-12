#pragma once

namespace epion::Node
{
	class NodeBase;
	class NodeLink;
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

	enum INPUT :unsigned char
	{
		BASIC,
		TEXTURE,
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

		static	void	CreateNodeMenu(ImVec2& pos);
		static	void	DeleteNodeMenu(std::vector<std::unique_ptr<Node::NodeBase>>& nodes, int& hit_index);
		static	void	DeleteLineMenu(std::vector<Node::NodeLink>&	lines, int& hit_index);

		static	void	SetContext(bool is_set);
		static	bool	GetContext();
		static	void	OpenNodeCreateContext(ImVec2& pos);
		static	void	OpenNodeDeleteContext(ImVec2& pos);
		static	void	OpenLineDeleteContext(ImVec2& pos);

		static	void	SetLineMenu(bool is_set);
		static	bool	GetLineMenu();

		static	void	SetCreateCount(int size);

		static	void	NodeMenu();

		static void ResetCreateCount()
		{
			m_create_count = 0;
		}
	private:
		static bool	m_is_open_node_menus[ArraySize];
		static std::string	m_str_menus[ArraySize];

		static	ImVec2	m_offset;

		static	ImVec2	m_menu_pos;


		//ID������U�邽�߂̃J�E���g,���̓_��
		static	int	m_create_count;
		static	bool	m_is_open_node_create_menu;
		static	bool	m_is_open_node_menu;
		static	bool	m_is_open_artistic_adjustment_menu;
		static	bool	m_is_open_input_basic_menu;
		static	bool	m_is_open_input_texture_menu;
		static	bool	m_is_open_math_advanced_menu;
		static	bool	m_is_open_math_basic_menu;
		static	bool	m_is_open_math_range_menu;
		static	bool	m_is_open_math_round_menu;
		static	bool	m_is_open_math_wave_menu;

		static	bool	m_is_open_node_delete_menu;
		static	bool	m_is_open_line_delete_menu;


		//�ǂꂩ��ł��J����Ă�Ȃ� true
		static	bool	m_is_open;

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

		template<class First>
		static inline void SetFalse(First& first)
		{
			first = false;
		}

		template<class First, class... Args>
		static inline void SetFalse(First& first, Args&... args)
		{
			first = false;
			SetFalse(args...);
		}

		template <class T = epion::Node::NodeBase>
		static inline void MenuCreateNode(std::vector<std::unique_ptr<Node::NodeBase>>& nodes, const std::string& name, ImVec2& pos, int& count, bool& is_open)
		{
			static_assert(std::is_base_of<epion::Node::NodeBase, T>::value == true, "BaseClass not NodeBase");
			if (ImGui::MenuItem(name.c_str()))
			{
				nodes.push_back(std::make_unique<T>(count, math::FVector2(pos.x, pos.y)));
				count++;
				is_open = false;
				//	SetFalse(first, args...);
			}
		};

		//template<class... Args>
		//static inline void MenuCreateNodes(std::vector<std::unique_ptr<Node::NodeBase>>& nodes, ImVec2& pos, int& count, bool& is_open)
		//{
		//	std::tuple<Args...> data = {};
		//	std::string a = "A";
		//	//static_assert(std::is_base_of< typeid(std::get<0>(data), Node::NodeBase>::value == true, "BaseClass not NodeBase");
		//	MenuCreateNode<typeid(std::get<0>(data))>(nodes,a , pos, count, is_open);
		//};


		//template<class T>
		//static inline void MenuItems(std::tuple<Node::NodeBase>& menu_node,std::vector<std::unique_ptr<Node::NodeBase>>& nodes, ImVec2& pos, int& count, bool& is_open)
		//{
		//	using create_class = typeid(std::get<0>(menu_node));
		//	static_assertstd::is_base_of<create_class, T>::value == true, "BaseClass not NodeBase");
		//	MenuCreateNode<create_class>(nodes, pos, count, is_open);
		//}


		//template<class... Args>
		//static inline void MenuItems(std::vector<std::unique_ptr<Node::NodeBase>>& nodes, ImVec2& pos, int& count, bool& is_open, Args&... args)
		//{
		//	MenuCreateNodes(nodes, STR(first), pos, count, is_open, args...);
		//}

		static	inline	void	MenuItem(const std::string& str, NodeType type, bool&is_menu);

	};
}

