#pragma once
#include	"../epion.h"
#include	"../dx11//ShaderManager.h"
#include	"../dx11//square.h"
#include	"../dx11//Cube.h"


namespace	epion
{
	class	SceneDemo2D	final :public	Scene
	{
	public:
		void	Init()		override;
		void	Update()	override;
		void	Render()	override;
		void	Release()	override;

	private:
		std::unique_ptr<VertexShader> m_vertex;
		std::unique_ptr<PixelShader> m_pixel;
		std::unique_ptr<Cube>	m_preview_3d;

	};
}
