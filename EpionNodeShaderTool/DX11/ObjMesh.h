#pragma once

#include	"ObjLoader.h"
#include	"ObjMtlLoader.h"
#include	"Renderer.h"
#include	"texture.h"
#include	"shader_reflection.h"
#include	"ShaderManager.h"
#include	"buffer.h"

#include	"dx11_state.h"
#include	"InputLayout.h"

namespace	epion
{
	class	ObjMesh	final
	{
	public:
		ObjMesh(std::wstring	obj_filename_);

		~ObjMesh() {};
		void render(const DirectX::XMFLOAT4X4 &world_view_projection,
			const DirectX::XMFLOAT4X4 &world,
			const	math::FVector4 &light_direction,
			const	Color&	material_color);
	private:
		std::unique_ptr<ObjLoader>			obj_data;
		std::unique_ptr<ObjMaterialLoader>	obj_mtl_data;

		VertexShader		vertex_shader;
		PixelShader			pixel_shader;
		ShaderReflection	shader_refrection;
		InputLayout			input_layout;

		VertexBuffer	vertex_buffer;
		IndexBuffer		index_buffer;
		ConstantBuffer	constant_buffer;

		DepthStencil	depth_stencil;
		Sampler			sampler;

		//Texture			texture;
		DirectX::XMFLOAT4X4	coordinate_conversion = { 1, 0, 0, 0,
														0, 1, 0, 0,
														0, 0,-1, 0,
														0, 0, 0, 1 };
	};
}
