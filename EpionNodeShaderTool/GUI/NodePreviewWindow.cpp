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
		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\ObjVertexShader.hlsl");
		m_pixel = std::make_unique<PixelShader>(L"Default\\Default2.hlsl");
		m_preview = std::make_unique<Cube>(L"Assets//obj//plane//plane2.obj", m_vertex->GetBlob());
		//m_preview = std::make_unique<Cube>(L"Assets//obj//sphere//sphere.obj",m_vertex->GetBlob());
		m_pos = { 0.0f,0.0f,4.0f };
		m_preview->SetPos(m_pos);

		math::FVector3 scale = { 1.0f,1.0f,1.0f };
		m_preview->SetScale(scale);
		math::FVector3 angle = { 4.7f,0.0,0.0f };
		m_preview->SetAngle(angle);

		m_tex = std::make_unique<Texture>();
		m_depth = std::make_unique<DepthStencil>();
		m_tex->Create(1920, 1080, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);
		return true;
	}

	void NodePreviewWindow::Update(bool& is_shader_update)
	{
		if (is_shader_update)
		{
			m_pixel = std::make_unique<PixelShader>(L"Default\\Default2.hlsl");
		}
		is_shader_update = false;
		ID3D11RenderTargetView*rtv = m_tex->RenderTargetView.Get();
		ID3D11DepthStencilView*dsv = Dxgi::get_dsv().Get();
		Device::GetContext()->OMSetRenderTargets(1, &rtv, dsv);

		float color[4] = { 1,1,1,1 };
		Device::GetContext()->ClearRenderTargetView(rtv, color);
		Device::GetContext()->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		m_depth->SetState();
		static math::FVector4 time;
		time.x += 0.001f;

		math::FVector2 a = { 1920,1080 };
		Node::Dx11::ConstantBufferManager::UpdateCBuffer0(time, a);

		m_vertex->SetState();

		m_preview->Update();
		m_pixel->SetState();
		m_preview->Render(CameraManager::GetPreviewCamera()->GetView(), CameraManager::GetPreviewCamera()->GetProjection());


		ID3D11RenderTargetView*backbuffer = Dxgi::get_rtv().Get();
		Device::GetContext()->OMSetRenderTargets(1, &backbuffer, dsv);

		ImGui::SetNextWindowPos(ImVec2(1450, 560));
		//ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColors::U32::BLUE);	//”wŒi
		ImGui::BeginChild("test5", ImVec2(403, 403));

		ImGui::Image(m_tex->m_shader_resource.Get(), ImVec2(400, 400), ImVec2(0, 0), ImVec2(1.0, 1.0), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));

		ImGui::EndChild();


	}
	void NodePreviewWindow::Render()
	{
	}

}