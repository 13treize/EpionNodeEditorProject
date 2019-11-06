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

		//ファイル名は読み込み済み
		void	load_file(com_ptr<ID3D11ShaderResourceView>	&shader_resource_view);

		void	load_file(com_ptr<ID3D11ShaderResourceView>	&shader_resource_view,
			com_ptr<ID3D11UnorderedAccessView>	&unordered_access_view);

		bool Create(u_int width, u_int height, DXGI_FORMAT format);


		math::Vector2<float>	get_mata_data();
		//private:
		std::wstring	texture_name;
		DirectX::TexMetadata	metadata = {};
		DirectX::ScratchImage	image = {};
		com_ptr<ID3D11RenderTargetView> RenderTargetView;
		com_ptr<ID3D11ShaderResourceView> ShaderResourceView;
		com_ptr<ID3D11SamplerState> sampler;
		com_ptr<ID3D11Texture2D> Texture2D;

		D3D11_TEXTURE2D_DESC texture_desc;
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
	class	TextureFile	final
	{
	public:
		static	bool	LoadTexture(std::wstring load_texture, DirectX::TexMetadata& metadata, DirectX::ScratchImage& image, com_ptr<ID3D11ShaderResourceView>& srv);


		static bool	SaveTexture(std::string name, com_ptr<ID3D11Texture2D>& texture);

		static bool	SaveTexture(std::string name, std::string extension, com_ptr<ID3D11Texture2D>& texture);
	private:
		//enum classにする
		static Extension ExtensionGet(std::string extension);

	};
}