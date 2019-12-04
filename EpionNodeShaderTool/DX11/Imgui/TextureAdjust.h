#pragma once
namespace	epion
{
	class Texture;
}
namespace	epion::GUI
{
	/*
		Preview画面で表示するTextureの管理
		フォルダにある画像の確認
		画像出力をFileIOかどうするか

	*/
	class TextureAdjust final
	{
	public:
		TextureAdjust();
		~TextureAdjust();
		void Init();
		void Update();


	private:
		int	m_tex_num;
		std::vector<bool>	m_is_tex;
		std::vector<std::string>	m_tex_name;
		std::vector<std::unique_ptr<Texture>>	m_tex_resouce;

	};
}