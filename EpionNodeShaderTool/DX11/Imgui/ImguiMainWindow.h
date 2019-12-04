#pragma once
#include	"TextureResouce.h"
#include	"FileIOAdjust.h"
#include	"TextureAdjust.h"


namespace	epion
{

	/*
	–½–¼‹K‘¥
	*/
	//class TextureResouce;
	class	EventBase abstract
	{
	public:
		EventBase() {}
		virtual ~EventBase(){}
		virtual void Init() = 0;
		virtual void Update() = 0;
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


		bool m_is_update_node;

		TextureResouce	m_tex_resouce;
		void	impl_update();

		GUI::FileIOAdjust	m_file_io_adjust;
		GUI::TextureAdjust	m_texture_adjust;

		void ShaderSet();




		void	ResetEvent();

		void	PreviewEvent();

		//std::unique_ptr<Texture> m_preview_resouce;
		bool	is_reset;
		bool	m_is_node_window;

		//Scene
		int		m_select_scene;
		void	SceneUpdate();
	};
}
