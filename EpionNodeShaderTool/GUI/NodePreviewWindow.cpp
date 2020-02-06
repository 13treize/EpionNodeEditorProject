#include	"../All.h"
#include	"../epion.h"

#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"
#include	"../Node/NodeParamDx11.h"

#include	"NodePreviewWindow.h"
#include	"../DX11/dx11_device.h"
#include	"../DX11/dx11_dxgi.h"
#include	"../CameraManager.h"

namespace epion::GUI
{
	bool NodePreviewWindow::Init()
	{
		CameraManager::Init();
		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\ObjVertexShader.hlsl");
		m_pixel = std::make_unique<PixelShader>(L"Default\\Default2.hlsl");
		m_preview[0] = std::make_unique<Cube>(L"Assets//obj//plane//plane2.obj", m_vertex->GetBlob());
		m_preview[1] = std::make_unique<Cube>(L"Assets//obj//sphere//sphere.obj", m_vertex->GetBlob());
		m_preview[2] = std::make_unique<Cube>(L"Assets//obj//box//box.obj", m_vertex->GetBlob());

		math::FVector3 scale = { 1.0f,1.0f,1.0f };
		m_pos[0] = { 0.0f,0.5f,3.0f };
		m_preview[0]->SetPos(m_pos[0]);
		m_preview[0]->SetScale(scale);

		m_rotate = {0.0f,0.0f,0.0f};
		m_depth = std::make_unique<DepthStencil>();

		m_tex = std::make_unique<Texture>();
		m_tex->Create(1920, 1080, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);
		m_preview_state = PreviewState::PLANE;
		m_is_rotates[0] =false;
		m_is_rotates[1] =false;
		m_is_rotates[2] =false;

		m_is_rotate = false;

		return true;
	}

	void NodePreviewWindow::Update(bool& is_shader_update)
	{
		if (is_shader_update)
		{
			m_pixel = std::make_unique<PixelShader>(L"Default\\Default2.hlsl");
		}
		is_shader_update = false;

		static float a = 0.0f;
		a++;
		if (m_is_rotates[0])
		{
			m_rotate.x++;
			m_is_rotate = true;
		}
		if (m_is_rotates[1])
		{
			m_rotate.y++;
			m_is_rotate = true;

		}
		if (m_is_rotates[2])
		{
			m_rotate.z++;
			m_is_rotate = true;
		}


		m_rotate.x = 270.0f;
		



		switch (m_preview_state)
		{
		case PreviewState::PLANE:
			m_preview[0]->SetAngle(m_rotate);
			m_preview[0]->Update();
			break;
		case PreviewState::SPHERE:
			m_preview[1]->SetAngle(m_rotate);
			m_preview[1]->Update();
			break;
		case PreviewState::BOX:
			m_preview[2]->SetAngle(m_rotate);
			m_preview[2]->Update();
			break;
		}


		ImGui::SetNextWindowPos(ImVec2(1450, 560));
		ImGui::BeginChild("test5", ImVec2(403, 403));
		ImGui::Image(m_tex->m_shader_resource.Get(), ImVec2(400, 400), ImVec2(0, 0), ImVec2(1.0, 1.0), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));
		ImGui::EndChild();
		m_is_rotate = false;

	}
	void NodePreviewWindow::Render()
	{
		float color[4] = { 0.5, 0.5, 0.5, 1};

		Device::GetContext()->OMSetRenderTargets(1, m_tex->RenderTargetView.GetAddressOf(), Dxgi::GetDSV().Get());
		Device::GetContext()->ClearRenderTargetView(m_tex->RenderTargetView.Get(), color);
		Device::GetContext()->ClearDepthStencilView(Dxgi::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		//m_depth->SetState();
		static math::FVector4 time;
		time.x += 0.01f;

		math::FVector2 a = { 1920,1080 };
		Node::Dx11::ConstantBufferManager::UpdateCBuffer0(time, a);

		m_vertex->SetState();
		m_pixel->SetState();
		m_preview[0]->Render(CameraManager::GetPreviewCamera()->GetView(), CameraManager::GetPreviewCamera()->GetProjection());

		Device::GetContext()->OMSetRenderTargets(1, Dxgi::GetRTV().GetAddressOf(), Dxgi::GetDSV().Get());
	}
}