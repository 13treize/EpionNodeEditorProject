#include	<array>
#include	"epion.h"
#include	"Dx11//dx11_device.h"
#include	"Dx11//dx11_dxgi.h"


#include	"Dx11//Imgui//dx11_imgui_manager.h"
#include	"Dx11//Imgui//dx11_imgui_main_window.h"

#include	"Framework.h"

#include	"DX11/blender.h"
#include	"DX11/rasterizer.h"
#include	"CameraManager.h"
#include	"DX11/Cube.h"
#include	"DX11/square.h"

namespace
{
	epion::math::FVector4	light(-1, 1, 1, 1);

	std::unique_ptr<epion::Blender>		blender;
	std::unique_ptr<epion::Rasterizer>	rasterizer;

}

namespace	epion
{
	void	FrameWork::Init(int	width, int	height)
	{
		math::FVector2	src(static_cast<float>(width), static_cast<float>(height));

		Device::set_up();
		Dxgi::set(src);
		ImguiManager::Init();
		ImguiMain::get_inst().Init();
		Renderer::set_screen_size(width, height);
		CameraManager::Init();
		blender		=std::make_unique<Blender>();
		rasterizer	=std::make_unique<Rasterizer>();


	}

	void	FrameWork::Update()
	{

		ImguiManager::begin();
		ImguiMain::get_inst().Update();
		CameraManager::Update();

		blender->set_state(BS_ALPHA);
		rasterizer->set_state(RASTER_STATE::SOLID);
	}

	void	FrameWork::Render()
	{
		std::array<float, 4>	back_color
		{
			{0.0f,0.0f,0.0f,0.0f}
		};
		Dxgi::begin(back_color);

		ImguiMain::get_inst().Render();

		ImguiManager::end();
		Dxgi::end();

	}

	void	FrameWork::release()
	{
		ImguiManager::release();
	}

}