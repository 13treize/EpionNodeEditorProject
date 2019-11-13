#include	"../All.h"
#include	"SceneManager.h"
#include	"SceneDemo2D.h"

namespace	epion
{
	std::unique_ptr<Scene>	SceneManager::m_scene = {};
	std::unique_ptr<Scene>	SceneManager::m_next_scene = std::make_unique<SceneDemo2D>();

	void	SceneManager::Update()
	{
		m_scene->Update();
	}

	void	SceneManager::Render()
	{
		m_scene->Render();
	}

	void	SceneManager::ChangeScene()
	{
		if (m_next_scene)
		{
			if (m_scene)
			{
				m_scene->Release();
			}
			m_scene = std::move(m_next_scene);
			m_scene->Init();
		}
	}
}