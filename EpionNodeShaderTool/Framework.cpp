#include	"All.h"
#include	"epion.h"
#include	"Dx11//dx11_device.h"
#include	"Dx11//dx11_dxgi.h"
#include	"Dx11//Renderer.h"


#include	"Dx11//Imgui//Dx11ImguiManager.h"
#include	"Dx11//Imgui//ImguiMainWindow.h"

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
		Dxgi::Set(src);
		ImguiManager::Init();
		ImguiMain::GetInst().Init();
		Renderer::SetScreenSize(width, height);
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
			{0.6f,0.6f,0.6f,0.6f}
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