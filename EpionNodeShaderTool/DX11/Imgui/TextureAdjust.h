#pragma once
namespace	epion
{
	class Texture;
}
namespace	epion::GUI
{
	/*
		Preview��ʂŕ\������Texture�̊Ǘ�
		�t�H���_�ɂ���摜�̊m�F
		�摜�o�͂�FileIO���ǂ����邩

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