#pragma once
namespace	epion
{

	class	FrameWork	final
	{
	public:
		static	void	Init(int	width, int	height);
		static	void	Update();
		static	void	render();
		static	void	release();
	};

}