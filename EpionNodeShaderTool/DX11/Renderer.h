#pragma	once
namespace	epion
{
	class	Renderer	final
	{
	public:
		static	void	SetState();
		static	void	set_state_list();
		static	void	set_2d_draw();
		static	void	set_drawindexed(unsigned	int	count, unsigned	int	start);
		static	void	SetScreenSize(int	width, int	height);
		static	math::Vector2<int>	GetScreenSize();

	private:
		static	math::Vector2<int>	m_screen_size;
	};
}