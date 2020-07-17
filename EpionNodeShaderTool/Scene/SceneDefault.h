#pragma once
namespace	epion
{
	class	SceneDefault	final :public	Scene
	{
	public:
		void	Init()		override;
		void	Update()	override;
		void	Render()	override;
		void	RenderTex()	override;
		void	Release()	override;
	private:
	};
}
