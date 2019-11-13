#pragma once

namespace	epion
{
	class	SceneDemo2D	final :public	Scene
	{
	public:
		void	Init()		override;
		void	Update()	override;
		void	Render()	override;
		void	Release()	override;

	};
}
