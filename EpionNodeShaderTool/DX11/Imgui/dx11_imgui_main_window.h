#pragma once
#include	"TextureResouce.h"

namespace	epion
{

	/*
	�����K��
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

		TextureResouce	m_tex_resouce;
		void	impl_update();

		void	PathSetting();

		void	JsonSave();

		void	ShaderGenerate();

		std::string	m_json_path;
		std::string	m_json_import_name;
		std::string	m_json_import;

		std::string	m_shader_path;
		std::string	m_shader_generate_name;
		std::string	m_shader_generate;
		void	TextureInit();
		void	TextureUpdate();
		void	TextureRelease();

		void	ResetEvent();

		void	PreviewEvent();

		std::string m_import_json_name;
		//std::unique_ptr<Texture> m_preview_resouce;
		bool	is_reset;
		bool	m_is_node_window;

		//Scene
		int		m_select_scene;
		void	SceneUpdate();
	};
}
