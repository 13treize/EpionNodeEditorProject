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

		static	void	click_event();
		static	void	set_context(bool is_set);
		static	bool	GetContext();

		static	void	line_event();
		static	void	set_is_line_menu(bool is_set);
		static	bool	get_is_line_menu();



		static	void	click_add();

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
		static	bool	m_is_open_input_basic_menu;
		static	bool	m_is_open_input_texture_menu;

		static	bool	m_is_open_math_basic_menu;
		static	bool	m_is_open_math_advanced_menu;
		static	bool	m_is_open_math_wave_menu;

		static	bool	m_is_open_context_menu;
		static	bool	m_is_open_line_menu;

		static	bool	m_is_open_node_menu;

		static	inline	void	artistic_context();
		static	inline	void	channel_context();
		static	inline	void	InputContext();
		static	inline	void	master_context();
		static	inline	void	math_context();
		static	inline	void	ProceduralContext();
		static	inline	void	UtilityContext();
		static	inline	void	UVContext();
		static	inline	void	NoiseContext();
	};
}

