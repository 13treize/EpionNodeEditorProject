#pragma once
#include	<memory>
#include	"buffer.h"
#include	"ShaderManager.h"
#include	"shader_reflection.h"
#include	"InputLayout.h"

namespace	epion
{
	/*__declspec(align(16))*/struct	SquareVertex	final
	{
		math::Vector4<float>	pos;
		math::Vector2<float>	uv;
		Color	color;
	};

	class	Square
	{
	public:
		Square();
		Square(com_ptr<ID3DBlob>&	m_blob);

		~Square();

		void	render(math::FVector2 d_xy, math::FVector2 d_wh, float angle, Color data);

		com_ptr<ID3D11ShaderResourceView>&get_shader_resouce();
	private:

		com_ptr<ID3D11ShaderResourceView>	shader_resouce_view;

		std::unique_ptr<VertexBuffer>	vertex_buffer;
		std::unique_ptr<ShaderReflection>	shader_refrection;
		std::unique_ptr<InputLayout>		input_layout;
	};
}
