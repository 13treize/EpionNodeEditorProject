#pragma once

//namespace epion
//{
//	class	VertexShader;
//	class	PixelShader;
//	class	Cube;
//}
//
#include	"../DX11/ShaderManager.h"
#include	"../DX11/Cube.h"
#include	"../Dx11/texture.h"
#include	"../Dx11/dx11_state.h"

namespace epion::GUI
{
	enum class PreviewState :unsigned char
	{
		PLANE,
		BOX,
		SPHERE,
	};
	class NodePreviewWindow final
	{
	public:
		bool Init();
		void Update(bool& is_shader_update);
		void Render();

	private:
		std::unique_ptr<epion::VertexShader> m_vertex;
		std::unique_ptr<epion::PixelShader> m_pixel;
		std::unique_ptr<epion::Cube>	m_preview[3];
		std::unique_ptr<epion::Texture>	m_tex;
		std::unique_ptr<epion::DepthStencil>	m_depth;
		math::FVector3	m_pos[3];
		math::FVector3	m_angle[3];

	};
}