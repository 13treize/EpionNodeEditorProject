#pragma once

namespace	epion::Node
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
		static	void	Update(ImVec2& offset);

		static	void	DragAndDropEvent();

		static	void	CreateNodeMenu(ImVec2& offset);
		static	void	OpenNodeCreateContext(bool is_set, ImVec2& pos);

		static	bool	GetContext();

		static	void	LineEvent();
		static	void	SetLineMenu(bool is_set);
		static	bool	GetLineMenu();

		static	void	SetCreateCount(int size);

		static	void	NodeMenu();

		static void ResetCreateCount()
		{
			m_create_count = 0;
		}
	private:
		static bool		m_is_open_node_menus[ArraySize];
		static std::string	m_str_menus[ArraySize];

		static	ImVec2	m_pos;

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

		static	bool	m_is_open_node_create_menu;
		static	bool	m_is_open_line_delete_menu;

		static	bool	m_is_open_node_menu;

		static	inline	void	ArtisticContext();
		static	inline	void	ChannelContext();
		static	inline	void	InputContext();
		static	inline	void	MasterContext();
		static	inline	void	MathContext();
		static	inline	void	ProceduralContext();
		static	inline	void	UtilityContext();
		static	inline	void	UVContext();
		static	inline	void	NoiseContext();

		static	inline	void	BaseMenuContext(const std::string& menu_name, bool& is_back, bool& is_current);
		static	inline	void	CloseContext(bool& is_current);
		static	inline	void	BackContext(bool& is_back,bool& is_current);

		static	inline	void	PopupBeginSettings();
		static	inline	void	PopupEndSettings();
		static	inline	void	MenuItem(const std::string& str,NodeType type,bool&is_menu);

	};
}

