#include	"../All.h"
#include	"../epion.h"

#include	"SceneManager.h"
#include	"SceneDemo2D.h"

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

		m_preview_3d = std::make_unique<Cube>(L"Assets//obj//plane//plane.obj",m_vertex->GetBlob());
		//m_preview_3d = std::make_unique<Cube>(L"Assets//obj//sphere//sphere.obj", m_vertex->GetBlob());

		m_pos[0] = { 8.4f,3.0f,-20.0f };
		m_pos[1] = { 6.3f,3.0f,-20.0f };
		m_pos[2] = { 4.2f,3.0f,-20.0f };

		math::FVector3 scale = { 1.0f,1.0f,1.0f };
		m_preview_3d->SetScale(scale);
		math::FVector3 angle = { 200.0f,0.0,0.0f };
		m_preview_3d->SetAngle(angle);

		m_blender = std::make_unique<Blender>();
		m_blender->SetState(BLEND_STATE::BS_ALPHA);

	}
	void SceneDemo2D::Update()
	{
		CameraManager::Update();
	}
	void SceneDemo2D::Render()
	{
		static math::FVector4 time;
		time.x += 0.001f;

		math::FVector2 a = { 1920,1080 };
		Node::Dx11::ConstantBufferManager::UpdateCBuffer0(time, a);

		m_vertex->SetState();

		m_preview_3d->SetPos(m_pos[0]);
		m_preview_3d->Update();
		m_pixel[0]->SetState();
		m_preview_3d->Render(CameraManager::GetView(), CameraManager::GetProjection());

		m_preview_3d->SetPos(m_pos[1]);
		m_preview_3d->Update();
		m_pixel[1]->SetState();
		m_preview_3d->Render(CameraManager::GetView(), CameraManager::GetProjection());

		m_preview_3d->SetPos(m_pos[2]);
		m_preview_3d->Update();
		m_pixel[2]->SetState();
		m_preview_3d->Render(CameraManager::GetView(), CameraManager::GetProjection());
	}
	void SceneDemo2D::Release()
	{
	}
}