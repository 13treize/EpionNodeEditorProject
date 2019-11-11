#pragma once

namespace	epion
{
	class	Texture
	{
	public:

		//ファイル名の指定が無ければ
		//Texture()	:file_name(L"data\\FukuiFrog.png"){};

		Texture();
		Texture(std::wstring	load_texture);
		~Texture();

		bool Create(u_int width, u_int height, DXGI_FORMAT format);


		math::Vector2<float>	get_mata_data();
		//private:
		std::wstring	texture_name;
		DirectX::TexMetadata	m_metadata = {};
		DirectX::ScratchImage	m_image = {};
		com_ptr<ID3D11RenderTargetView> RenderTargetView;
		com_ptr<ID3D11ShaderResourceView> m_shader_resource;
		com_ptr<ID3D11Texture2D> Texture2D;

		D3D11_TEXTURE2D_DESC texture_desc;
	};

	class	Texture2D	final
	{
	public:
		Texture2D();
		~Texture2D();
		bool Init(u_int width, u_int height, DXGI_FORMAT format);
		DirectX::TexMetadata& GetMata();
		DirectX::ScratchImage& GetImage();
		com_ptr<ID3D11ShaderResourceView>& GetShaderResouce();

	private:
		DirectX::TexMetadata m_metadata;
		DirectX::ScratchImage m_image;
		com_ptr<ID3D11ShaderResourceView> m_shader_resource;

		com_ptr<ID3D11Texture2D> m_texture2d;
		D3D11_TEXTURE2D_DESC m_texture_desc;
	};

	enum class Extension :unsigned char
	{
		PNG,
		JPG,
		NONE,

		//TGA,
		//BMP,
	};

	//TextureExport
	class	TextureFileIO	final
	{
	public:
		static bool LoadTexture(std::wstring load_texture, DirectX::TexMetadata& m_metadata, DirectX::ScratchImage& m_image, com_ptr<ID3D11ShaderResourceView>& srv);

		static bool SaveTexture(std::string name, com_ptr<ID3D11Texture2D>& texture);
		static bool SaveTexture(std::string name, std::string extension, com_ptr<ID3D11Texture2D>& texture);
	private:
		//enum classにする
		static Extension ExtensionGet(std::string extension);

	};
}