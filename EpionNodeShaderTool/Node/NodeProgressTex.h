#pragma once
/*
	ノードの途中経過を出すTexture
*/
namespace epion
{
	class	VertexBuffer;
	class	VertexShader;
	class	PixelShader;
	class	ShaderReflection;
	class	InputLayout;

	/*__declspec(align(16))*/struct	TexVertex	final
	{
		math::Vector4<float>	pos;
		math::Vector2<float>	uv;
		math::Vector4<float>	color;
	};

	struct LoadNodeResouce final
	{
		LoadNodeResouce();
		~LoadNodeResouce();

		void Create(epion::com_ptr<ID3D11Device>& device);
		void draw(epion::com_ptr<ID3D11DeviceContext>& device,
			com_ptr<ID3D11ShaderResourceView>&view,
			com_ptr<ID3D11SamplerState> &state
		);


		D3D11_TEXTURE2D_DESC texture2d_desc;

		std::unique_ptr<VertexBuffer>	vertex_buffer;
		std::unique_ptr<VertexShader>	vertex_shader;
		std::unique_ptr<PixelShader>	pixel_shader;
		std::unique_ptr<ShaderReflection>	shader_refrection;
		std::unique_ptr<InputLayout>		input_layout;

		epion::com_ptr<ID3D11Texture2D>				Texture;
		epion::com_ptr<ID3D11ShaderResourceView>	shader_resouce_view;
		epion::com_ptr<ID3D11UnorderedAccessView>	unordered_access_view;
		epion::com_ptr<ID3D11RenderTargetView>		render_target_view;
	};

}