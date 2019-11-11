#pragma once


namespace epion
{
	class	Texture2D;
	class	Square;
	class	VertexShader;
	class	PixelShader;

	class	TextureResouce final
	{
	public:
		void Init();
		void Update();

		std::vector<std::string>&	GetTexNames();
	private:
		char	tex_input_name[CHAR_MAX] = "";
		char	directory_input_name[CHAR_MAX] = "";
		std::string directory_name;
		std::string tex_name;


		std::vector<bool>	m_is_tex;
		std::vector<std::string>	m_tex_title;
		std::vector<std::string>	m_tex_display_str;
		std::vector<std::string>	m_tex_name;//texture‚Ìƒtƒ@ƒCƒ‹–¼
		std::vector<Texture2D> m_preview_tex;

		//
		std::vector<std::string> m_combo_file_names;
		std::vector<bool> is_combo_selected;

		void ComboUpdate(int i);

	};

}