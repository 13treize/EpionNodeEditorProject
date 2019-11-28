#pragma once

namespace	epion::NodeCustom
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

		static	void	ClickEvent();
		static	void	SetContext(bool is_set);
		static	bool	GetContext();

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

		static	ImVec2	m_offfset;

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

		static	inline	void	ArtisticContext();
		static	inline	void	ChannelContext();
		static	inline	void	InputContext();
		static	inline	void	MasterContext();
		static	inline	void	MathContext();
		static	inline	void	ProceduralContext();
		static	inline	void	UtilityContext();
		static	inline	void	UVContext();
		static	inline	void	NoiseContext();

		static	inline	void	MenuItem(const std::string& str,NodeType type,bool&is_menu);

	};
}

