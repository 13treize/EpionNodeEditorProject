#pragma once

#include	"../epion.h"
#include	"../dx11//ShaderManager.h"
#include	"../dx11//square.h"
#include	"../dx11//Cube.h"
#include	"../dX11//blender.h"



namespace	epion
{
	class	SceneDemo3D	final :public	Scene
	{
	public:
		void	Init()		override;
		void	Update()	override;
		void	Render()	override;
		void	Release()	override;

	private:
		std::unique_ptr<VertexShader> m_vertex;
		std::array<std::unique_ptr<PixelShader>, 20>	m_pixel;
		std::unique_ptr<Cube> m_preview_3d;
		std::unique_ptr<Cube> m_preview_sphere;
		std::array<math::FVector3, 20>	m_pos;
		//std::array<math::FVector3, 20>	m_scale;
		std::array<math::FVector3, 20>	m_angle;
		std::unique_ptr<Blender>		m_blender;
	};
}
