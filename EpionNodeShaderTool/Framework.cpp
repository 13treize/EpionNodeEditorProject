#include	"All.h"
#include	"epion.h"
#include	"Dx11//dx11_device.h"
#include	"Dx11//dx11_dxgi.h"
#include	"Dx11//Renderer.h"


#include	"Dx11//Imgui//Dx11ImguiManager.h"

#include	"Node/NodeParamDx11.h"

#include	"GUI/NodeEditor.h"

#include	"CameraManager.h"

#include	"Framework.h"

namespace
{
}

namespace	epion
{
	void	FrameWork::Init(int	width, int	height)
	{
		math::FVector2	src(static_cast<float>(width), static_cast<float>(height));

		Device::set_up();
		Dxgi::Set(src);
		ImguiManager::Init();
		CameraManager::Init();
		Node::Dx11::ConstantBufferManager::Create();
		GUI::NodeEditor::Init();
		Renderer::SetScreenSize(width, height);
	}

	void	FrameWork::Update()
	{
		CameraManager::Update();
		ImguiManager::Begin();
		GUI::NodeEditor::Update();
	}

	void	FrameWork::Render()
	{
		std::array<float, 4>	back_color
		{
			{0.0f,0.0f,0.0f,1.0f}
		};
		Dxgi::Begin(back_color);
		GUI::NodeEditor::Render();
		ImguiManager::End();
		Dxgi::End();

	}

	void	FrameWork::Release()
	{
		ImguiManager::Release();
	}

}