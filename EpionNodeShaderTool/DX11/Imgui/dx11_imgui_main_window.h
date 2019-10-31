#pragma once
namespace	epion
{
	class	Texture;
	class	Square;
	class	VertexShader;
	class	PixelShader;

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
		void	impl_update();

		void	TextureInit();
		void	TextureUpdate();
		void	TextureRelease();


		void	ResetEvent();


		void	PreviewEvent();


		std::unique_ptr<Texture>	m_preview_resouce;
	};

	class	Preview	final
	{
	public:
		static bool Init(std::wstring	ps_name);
		static void Render();

	private:
		static math::FVector4	time;
		static std::unique_ptr<Square>			m_preview;
		static std::unique_ptr<VertexShader>	m_vertex;
		static std::unique_ptr<PixelShader>		m_pixel;
	};
}
