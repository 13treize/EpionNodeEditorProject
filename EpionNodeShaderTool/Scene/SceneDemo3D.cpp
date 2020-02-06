#include	"../All.h"
#include	"../epion.h"

#include	"SceneManager.h"
#include	"SceneDemo3D.h"

#include	"../Dx11/texture.h"
#include	"../DX11/dx11_dxgi.h"

#include	"../Node/NodeParamDx11.h"
#include	"../CameraManager.h"


namespace epion
{
	void SceneDemo3D::Init()
	{
		CameraManager::Init();
		Node::Dx11::ConstantBufferManager::Create();
		Node::Dx11::DepthStencilStateManager::Create();
		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\ObjVertexShader.hlsl");
		m_pixel[0] = std::make_unique<PixelShader>(L"GenerateShader\\demo1.hlsl");
		m_pixel[1] = std::make_unique<PixelShader>(L"GenerateShader\\Dissolve.hlsl");
		m_pixel[2] = std::make_unique<PixelShader>(L"GenerateShader\\ray.hlsl");

		m_preview_3d = std::make_unique<Cube>(L"Assets//obj//sphere//sphere.obj", m_vertex->GetBlob());

		m_preview_box = std::make_unique<Cube>(L"Assets//obj//box//box.obj", m_vertex->GetBlob());

		m_pos[0] = { 0.0f,0.0f,-20.0f };
		m_pos[1] = { 2.1f,0.0f,-20.0f };
		m_pos[2] = { 0.0f,0.0f,0.0f };

		math::FVector3 scale = { 1.0f,1.0f,1.0f };
		math::FVector3 angle = { 0.0f,0.0,0.0f };
		m_preview_3d->SetScale(scale);
		m_preview_3d->SetAngle(angle);
		scale = { 0.01f,0.01f,0.01f };
		m_preview_box->SetScale(scale);
		m_preview_box->SetAngle(angle);

		m_blender = std::make_unique<Blender>();
		m_blender->SetState(BLEND_STATE::BS_ALPHA);

		m_tex = std::make_unique<Texture>();
		m_tex->Create(1920, 1080, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);
	}
	void SceneDemo3D::Update()
	{
		math::FVector3 set_pos = math::FVector3(0.0, 0.0, 1.0f);
		CameraManager::GetBasicCamera()->SetPos(set_pos);
		CameraManager::Update();
	}
	void SceneDemo3D::Render()
	{
		float color[4] = { 0.5, 0.5, 0.5, 1 };

		Device::GetContext()->OMSetRenderTargets(1, m_tex->RenderTargetView.GetAddressOf(), Dxgi::GetDSV().Get());
		Device::GetContext()->ClearRenderTargetView(m_tex->RenderTargetView.Get(), color);
		Device::GetContext()->ClearDepthStencilView(Dxgi::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		Node::Dx11::DepthStencilStateManager::SetState();

		static math::FVector4 time;
		time.x += 0.001f;

		math::FVector2 a = { 1920,1080 };
		Node::Dx11::ConstantBufferManager::UpdateCBuffer0(time, a);
		Node::Dx11::ConstantBufferManager::UpdateCBuffer2(CameraManager::GetBasicCamera()->GetPos(), CameraManager::GetBasicCamera()->GetTarget(), CameraManager::GetBasicCamera()->GetUp());

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



		Device::GetContext()->OMSetRenderTargets(1, Dxgi::GetRTV().GetAddressOf(), Dxgi::GetDSV().Get());
	}

	void SceneDemo3D::RenderTex()
	{
	}

	void SceneDemo3D::Release()
	{
	}
}