#pragma once
namespace	epion
{
	class	Texture;
	class	Square;
	class	VertexShader;
	class	PixelShader;

	/*
	–½–¼‹K‘¥
	*/
	class	EventBase abstract
	{
	public:
		EventBase() {}
		virtual ~EventBase(){}
		virtual void Init() = 0;
		virtual void Update() = 0;
	};
	class	TextureResouce :public EventBase
	{
	public:
		void Init() override;
		void Update() override;

	private:
		char	tex_input_name[CHAR_MAX] = "";
		char	directory_input_name[CHAR_MAX] = "";
		std::string directory_name;
		std::string tex_name;

		std::vector<std::string>	m_tex_names;//texture‚Ìƒtƒ@ƒCƒ‹–¼
		std::vector<std::string>	m_tex_title;
		std::vector<std::string>	m_tex_display_str;
		std::vector<std::string>	m_current_file_name;
		//
		std::vector<std::string>	m_file_names;
	};
	class	ImguiMain	final :public	Singleton<ImguiMain>
	{
	public:
		ImguiMain();
		~ImguiMain();

		void	Init();
		void	Release();

		void	Update();
		void	Render();

	private:
		class	Impl;
		std::unique_ptr<Impl>	m_impl;

		TextureResouce	m_tex_resouce;
		void	impl_update();

		void	TextureInit();
		void	TextureUpdate();
		void	TextureRelease();

		void	ResetEvent();


		void	PreviewEvent();


		std::unique_ptr<Texture>	m_preview_resouce;
		bool	is_reset;

	};

	class	Preview	final
	{
	public:
		static bool Init(std::wstring	ps_name);
		static void Render();

	private:
		static math::FVector4 time;
		static std::unique_ptr<Square> m_preview;
		static std::unique_ptr<VertexShader> m_vertex;
		static std::unique_ptr<PixelShader> m_pixel;
		static std::unique_ptr<Texture> m_preview_tex[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];

	};
}
