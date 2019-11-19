#include	"epion.h"
#include	"DX11/dx11_dxgi.h"
#include	"CameraManager.h"

namespace
{
	epion::math::FVector3	pos = { 0.0f,	10.0f,	10.0f };
	epion::math::FVector3	target = { 0.0f,	1.0f,	0.0f };
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

	void	View::set_view(const	math::FVector3&	p, const	math::FVector3&	t, const	math::FVector3&	u)
	{
		pos = p;
		target = t;
		up = u;
	}

	void	View::set_projection(float	fov_, float	aspect_, float	n, float	f)
	{
		fov = fov_;
		aspect = aspect_;
		nearPlane = n;
		farPlane = f;
	}

	void	View::activate()
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

	//	getä÷êî
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


	//	setä÷êî
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

	std::unique_ptr<BasicCamera>	CameraManager::basic_camera;

	void	CameraManager::Init()
	{
		//ÉJÉÅÉâèâä˙âª
		basic_camera	=std::make_unique<BasicCamera>(	pos,
														target,
														up,
		//basic_camera = std::make_unique<BasicCamera>(basic_camera_hotreload->get_data().pos,
		//	basic_camera_hotreload->get_data().target,
		//	basic_camera_hotreload->get_data().up,
			math::pi<float> / 8.0f,
			Dxgi::get_view_port().get_aspect(),
			0.1f,
			1000.0f);
	}

	void	CameraManager::Update()
	{
		basic_camera->activate();
	}

	DirectX::XMFLOAT4X4&	CameraManager::GetView()
	{
		return	basic_camera->GetView();
	}

	DirectX::XMFLOAT4X4&	CameraManager::GetProjection()
	{
		return	basic_camera->GetProjection();
	}

}