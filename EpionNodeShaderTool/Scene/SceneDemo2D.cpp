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
		//m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\square_vertex_shader.hlsl");
		//m_pixel = std::make_unique<PixelShader>(L"test.hlsl");
		CameraManager::Init();
		//NodeCustom::Dx11::ConstantBufferManager::Create();

		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\ObjVertexShader.hlsl");
		//m_pixel = std::make_unique<PixelShader>(L"HLSLShader\\ObjNoTexturePixelShader.hlsl");
		m_pixel = std::make_unique<PixelShader>(L"GenerateShader\\demo1.hlsl");
		//m_pixel = std::make_unique<PixelShader>(L"test.hlsl");

		//m_preview = std::make_unique<Square>(m_vertex->GetBlob());
		m_preview_3d = std::make_unique<Cube>(m_vertex->GetBlob());

	}
	void SceneDemo2D::Update()
	{
		CameraManager::Update();
		m_preview_3d->Update();

	}
	void SceneDemo2D::Render()
	{
		//static math::FVector4 time;
		//time.x += 0.01f;

		//math::FVector2 a = { 1920,1080 };
		//NodeCustom::Dx11::ConstantBufferManager::UpdateCBuffer0(time, a);


		m_vertex->SetState();
		m_pixel->SetState();
		m_preview_3d->Render(CameraManager::GetView(), CameraManager::GetProjection());
	}
	void SceneDemo2D::Release()
	{
	}
}