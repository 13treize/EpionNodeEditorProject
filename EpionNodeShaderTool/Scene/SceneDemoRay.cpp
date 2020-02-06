#include	"../All.h"
#include	"../epion.h"

#include	"SceneManager.h"
#include	"SceneDemoRay.h"

#include	"../Dx11/texture.h"
#include	"../DX11/dx11_dxgi.h"

#include	"../Node/NodeParamDx11.h"
#include	"../CameraManager.h"


namespace epion
{
	void SceneDemoRay::Init()
	{
		CameraManager::Init();
		Node::Dx11::ConstantBufferManager::Create();

		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\square_vertex_shader.hlsl");
		//m_pixel[0] = std::make_unique<PixelShader>(L"HLSLShader\\tex3d_ps.hlsl");
		m_pixel[0] = std::make_unique<PixelShader>(L"HLSLShader\\square_pixel_shader.hlsl");

		square = std::make_unique<Square>(m_vertex->GetBlob());

		m_blender = std::make_unique<Blender>();
		m_blender->SetState(BLEND_STATE::BS_ALPHA);

		m_tex = std::make_unique<Texture>();
		m_tex->Create(1920, 1080, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);
	}
	void SceneDemoRay::Update()
	{
		CameraManager::Update();
	}
	void SceneDemoRay::Render()
	{
		float color[4] = { 0.5, 0.5, 0.5, 1 };

		Device::GetContext()->OMSetRenderTargets(1, m_tex->RenderTargetView.GetAddressOf(), Dxgi::GetDSV().Get());
		Device::GetContext()->ClearRenderTargetView(m_tex->RenderTargetView.Get(), color);
		Device::GetContext()->ClearDepthStencilView(Dxgi::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		static math::FVector4 time;
		time.x += 0.001f;

		math::FVector2 a = { 1920,1080 };
		Node::Dx11::ConstantBufferManager::UpdateCBuffer0(time, a);

		Node::Dx11::ConstantBufferManager::UpdateCBuffer2(
			CameraManager::GetBasicCamera()->GetPos(),
			CameraManager::GetBasicCamera()->GetTarget(),
			CameraManager::GetBasicCamera()->GetUp());


		m_vertex->SetState();

		//m_preview_3d->SetPos(m_pos[0]);
		//m_preview_3d->Update();
		//m_pixel[0]->SetState();
		//m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());

		//m_preview_3d->SetPos(m_pos[1]);
		//m_preview_3d->Update();
		//m_pixel[1]->SetState();
		//m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());

		//m_preview_3d->SetPos(m_pos[2]);
		//m_preview_3d->Update();
		//m_pixel[2]->SetState();
		//m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());

		m_pixel[0]->SetState();
		square->Render(math::FVector2(0, 0), math::FVector2(1920, 1080));


		Device::GetContext()->OMSetRenderTargets(1, Dxgi::GetRTV().GetAddressOf(), Dxgi::GetDSV().Get());
	}
	void SceneDemoRay::RenderTex()
	{

	}

	void SceneDemoRay::Release()
	{
	}
}