#include	"../All.h"
#include	"../epion.h"

#include	"SceneManager.h"
#include	"SceneDemo2D.h"

#include	"../Dx11/texture.h"
#include	"../DX11/dx11_dxgi.h"

#include	"../Node/NodeParamDx11.h"
#include	"../CameraManager.h"


namespace epion
{
	void SceneDemo2D::Init()
	{
		CameraManager::Init();
		Node::Dx11::ConstantBufferManager::Create();

		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\ObjVertexShader.hlsl");
		m_pixel[0] = std::make_unique<PixelShader>(L"GenerateShader\\Demo1.hlsl");
		m_pixel[1] = std::make_unique<PixelShader>(L"GenerateShader\\Demo2.hlsl");
		m_pixel[2] = std::make_unique<PixelShader>(L"GenerateShader\\Dissolve.hlsl");
		m_pixel[3] = std::make_unique<PixelShader>(L"GenerateShader\\ray.hlsl");

		m_preview_3d = std::make_unique<Cube>(L"Assets//obj//plane//plane2.obj",m_vertex->GetBlob());

		m_pos[0] = { 4.2f,3.0f,-18.0f };
		m_pos[1] = { 2.1f,3.0f,-18.0f };
		m_pos[2] = { 0.0f,3.0f,-18.0f };
		m_pos[3] = { 4.2f,0.9f,-18.0f };

		math::FVector3 angle = { 30.0f/0.01745f,0.0,0.0f };
		m_preview_3d->SetAngle(angle);

		math::FVector3 scale = { 1.0f,1.0f,1.0f };
		m_preview_3d->SetScale(scale);

		m_blender = std::make_unique<Blender>();
		m_blender->SetState(BLEND_STATE::BS_ALPHA);

		m_tex = std::make_unique<Texture>();
		m_tex->Create(1920, 1080, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);
	}
	void SceneDemo2D::Update()
	{
		CameraManager::Update();
	}
	void SceneDemo2D::Render()
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

		m_preview_3d->SetPos(m_pos[0]);
		m_preview_3d->Update();
		m_pixel[0]->SetState();
		m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());

		m_preview_3d->SetPos(m_pos[1]);
		m_preview_3d->Update();
		m_pixel[1]->SetState();
		m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());

		m_preview_3d->SetPos(m_pos[2]);
		m_preview_3d->Update();
		m_pixel[2]->SetState();
		m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());

		m_preview_3d->SetPos(m_pos[3]);
		m_preview_3d->Update();
		m_pixel[3]->SetState();
		m_preview_3d->Render(CameraManager::GetBasicCamera()->GetView(), CameraManager::GetBasicCamera()->GetProjection());


		Device::GetContext()->OMSetRenderTargets(1, Dxgi::GetRTV().GetAddressOf(), Dxgi::GetDSV().Get());
	}
	void SceneDemo2D::RenderTex()
	{

	}

	void SceneDemo2D::Release()
	{
	}
}