#include	"../All.h"
#include	"../epion.h"

#include	"SceneManager.h"
#include	"SceneDefault.h"
namespace	epion
{
	std::unique_ptr<Scene>	SceneManager::m_scene = {};
	std::unique_ptr<Scene>	SceneManager::m_next_scene = std::make_unique<SceneDefault>();

	void	SceneManager::Update()
	{
		m_scene->Update();
	}

	void	SceneManager::Render()
	{
		m_scene->Render();
	}

	std::unique_ptr<Texture>& SceneManager::GetTexData()
	{
		return m_scene->m_tex;
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