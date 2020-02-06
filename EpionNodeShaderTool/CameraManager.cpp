#include	"epion.h"
#include	"DX11/dx11_dxgi.h"
#include	"CameraManager.h"

namespace
{
	epion::math::FVector3	pos = {0.0f,	0.0f, 10.0f };
	epion::math::FVector3	target = { 0.0f,	0.0f,	0.0f };
	epion::math::FVector3	up = { 0.0f,	1.0f,	0.0f };

}

namespace	epion
{
	View::View()
	{
	}

	View::View(const math::FVector3& p, const math::FVector3& t, const math::FVector3& u, float fov_, float aspect_, float n_, float f_)
		:pos(p), target(t), up(u),
		fov(fov_), aspect(aspect_), nearPlane(n_), farPlane(f_)
	{
	}

	void	View::SetView(const	math::FVector3&	p, const	math::FVector3&	t, const	math::FVector3&	u)
	{
		pos = p;
		target = t;
		up = u;
	}

	void	View::SetProjection(float	fov_, float	aspect_, float	n, float	f)
	{
		fov = fov_;
		aspect = aspect_;
		nearPlane = n;
		farPlane = f;
	}

	void	View::Activate()
	{
		DirectX::XMMATRIX	mv, mp;

		DirectX::XMVECTOR	eye = {},	focus = {},	up_ = {};
		eye = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
		focus = DirectX::XMVectorSet(target.x, target.y, target.z, 1.0f);
		up_ = DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);

		mv = DirectX::XMMatrixLookAtLH(eye, focus, up_);
		DirectX::XMStoreFloat4x4(&matView, mv);

		mp = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearPlane, farPlane);
		DirectX::XMStoreFloat4x4(&matProjection, mp);
	}

	//	get�֐�
	math::FVector3&	View::GetPos()
	{
		return	pos;
	}

	math::FVector3&	View::GetTarget()
	{
		return	target;
	}

	math::FVector3&	View::GetUp()
	{
		return	up;
	}


	//	set�֐�
	void	View::SetPos(math::FVector3&	pos_)
	{
		pos = pos_;
	}

	void	View::SetTarget(math::FVector3&	target_)
	{
		target = target_;
	}

	void	View::SetUp(math::FVector3&	up_)
	{
		up = up_;
	}

	BasicCamera::BasicCamera()
	{
	}
	BasicCamera::BasicCamera(const math::FVector3& p_, const math::FVector3& t_, const math::FVector3& u_,
		float fov_, float aspect_, float n_, float f_) :View(p_, t_, u_, fov_, aspect_, n_, f_)
	{
	}

	PreviewCamera::PreviewCamera()
	{
	}

	PreviewCamera::PreviewCamera(const math::FVector3& p_, const math::FVector3& t_, const math::FVector3& u_,
		float fov_, float aspect_, float n_, float f_) :View(p_, t_, u_, fov_, aspect_, n_, f_)
	{
	}

	Scene3DCamera::Scene3DCamera()
	{
	}

	Scene3DCamera::Scene3DCamera(const math::FVector3& p_, const math::FVector3& t_, const math::FVector3& u_,
		float fov_, float aspect_, float n_, float f_) :View(p_, t_, u_, fov_, aspect_, n_, f_)
	{
	}

	std::unique_ptr<BasicCamera>	CameraManager::m_basic_camera;
	std::unique_ptr<PreviewCamera>	CameraManager::m_preview_camera;
	std::unique_ptr<Scene3DCamera>	CameraManager::m_scene3d_camera;

	void	CameraManager::Init()
	{
		//�J����������

		epion::math::FVector3	pos = { 0.0f,	0.0f, 10.0f };

		m_basic_camera	=std::make_unique<BasicCamera>(
			math::FVector3(0.0f, 0.0f, 10.0f),
			target,
			up,
			math::pi<float> / 8.0f,
			Dxgi::GetViewPort().GetAspect(),
			0.1f,
			1000.0f);

		m_preview_camera = std::make_unique<PreviewCamera>(
			math::FVector3(0.0f, 0.0f, 10.0f),
			math::FVector3(0.0f, 1.0f, 0.0f),
			up,
			math::pi<float> / 8.0f,
			400.0f/400.0f,
			0.1f,
			1000.0f);

		m_scene3d_camera= std::make_unique<Scene3DCamera>(
			math::FVector3(0.0f, 0.0f, -10.0f),
			math::FVector3(0.0f, 0.0f, 0.0f),
			up,
			math::pi<float> / 8.0f,
			Dxgi::GetViewPort().GetAspect(),
			0.1f,
			1000.0f);


	}

	void	CameraManager::Update()
	{
		m_basic_camera->Activate();
		m_preview_camera->Activate();
		m_scene3d_camera->Activate();
	}

	std::unique_ptr<BasicCamera>&	CameraManager::GetBasicCamera()
	{
		return m_basic_camera;
	}
	std::unique_ptr<PreviewCamera>&	CameraManager::GetPreviewCamera()
	{
		return m_preview_camera;
	}
	std::unique_ptr<Scene3DCamera>&	CameraManager::GetScene3DCamera()
	{
		return m_scene3d_camera;
	}
}