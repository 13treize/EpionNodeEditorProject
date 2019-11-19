#include	"All.h"
#include	"epion.h"
#include	"Dx11//dx11_device.h"
#include	"Dx11//dx11_dxgi.h"
#include	"Dx11//Renderer.h"


#include	"Dx11//Imgui//dx11_imgui_manager.h"
#include	"Dx11//Imgui//dx11_imgui_main_window.h"

#include	"Scene/SceneManager.h"
#include	"Framework.h"

//#include	"DX11/blender.h"
//#include	"DX11/rasterizer.h"
//#include	"CameraManager.h"
namespace
{
	epion::math::FVector4	vari;


}

namespace	epion
{
	void	FrameWork::Init(int	width, int	height)
	{
		math::FVector2	src(static_cast<float>(width), static_cast<float>(height));

		Device::set_up();
		Dxgi::set(src);
		ImguiManager::Init();
		ImguiMain::GetInst().Init();
		Renderer::set_screen_size(width, height);
	}

	void	FrameWork::Update()
	{
		SceneManager::ChangeScene();
		ImguiManager::Begin();
		SceneManager::Update();
		ImguiMain::GetInst().Update();

	}

	void	FrameWork::Render()
	{
		std::array<float, 4>	back_color
		{
			{0.0f,0.0f,0.0f,0.0f}
		};
		Dxgi::begin(back_color);

		SceneManager::Render();
		ImguiMain::GetInst().Render();


		ImguiManager::End();
		Dxgi::End();

	}

	void	FrameWork::Release()
	{
		ImguiManager::Release();
	}

}