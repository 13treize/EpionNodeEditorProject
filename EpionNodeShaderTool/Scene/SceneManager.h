#pragma once
#include	"../DX11/texture.h"
namespace	epion
{
	class	Scene	abstract
	{
	public:
		virtual	~Scene() {};

		virtual	void	Init() = 0;
		virtual	void	Update() = 0;
		virtual	void	Render() = 0;
		virtual	void	RenderTex() = 0;
		virtual	void	Release() = 0;

		std::unique_ptr<Texture> m_tex;
	};

	class SceneManager	final
	{
	public:
		static void Update();
		static void Render();
		static std::unique_ptr<Texture>& GetTexData();

		template<class T, class ...Args>
		static void SetNextScene(Args ...args);

		static void ChangeScene();

	private:
		static std::unique_ptr<Scene> m_scene;
		static std::unique_ptr<Scene> m_next_scene;
	};


	template<class	T, class	...Args>
	inline	void	SceneManager::SetNextScene(Args ...args)
	{
		if (!m_next_scene)
		{
			m_next_scene = std::make_unique<T>(args...);
		}
	}
}