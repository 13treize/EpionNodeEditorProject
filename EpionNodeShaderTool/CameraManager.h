#pragma once

namespace	epion
{

	class	View	/*abstract*/
	{
	public:
		View();

		View(const math::FVector3& p_, const math::FVector3& t_, const math::FVector3& u_,
			float fov_, float aspect_, float n_, float f_);

		virtual	~View() {};



		void set_view(const	math::FVector3&	p, const	math::FVector3& t, const math::FVector3& u);

		void set_projection(float fov, float aspect, float n, float f);
		//行列更新
		void activate();


		DirectX::XMFLOAT4X4& GetView()
		{
			return matView;
		}

		DirectX::XMFLOAT4X4& GetProjection()
		{
			return matProjection;
		}

		//get関数
		math::FVector3&	GetPos();
		math::FVector3&	GetTarget();
		math::FVector3&	GetUp();

		//set関数
		void	SetPos(math::FVector3&		pos_);
		void	SetTarget(math::FVector3&	target_);
		void	SetUp(math::FVector3&		up_);

	protected:
		DirectX::XMFLOAT4X4	matView;		//視野変換行列
		DirectX::XMFLOAT4X4	matProjection;	//投影変換行列
		math::FVector3	pos;
		math::FVector3	target;
		math::FVector3	up;
		float fov;
		float aspect;
		float nearPlane;
		float farPlane;
	};

	class	BasicCamera	final : public	View
	{
	public:
		BasicCamera();

		BasicCamera(const	math::FVector3& p_,
			const	math::FVector3& t_,
			const	math::FVector3& u_,
			float fov_,
			float aspect_,
			float n_,
			float f_);

		~BasicCamera() {};

	};

	//NodeのPreviewCamera
	class	PreviewCamera	final : public	View
	{
	public:
		PreviewCamera();

		PreviewCamera(const	math::FVector3& p_,
			const	math::FVector3& t_,
			const	math::FVector3& u_,
			float fov_,
			float aspect_,
			float n_,
			float f_);

		~PreviewCamera() {};

	};


	class	CameraManager	final
	{
	public:
		static	void	Init();
		static	void	Update();

		//get関数

		static std::unique_ptr<BasicCamera>&	GetBasicCamera();
		static std::unique_ptr<PreviewCamera>&	GetPreviewCamera();


		static	DirectX::XMFLOAT4X4& GetView();

		static	DirectX::XMFLOAT4X4& GetProjection();

	private:
		static	std::unique_ptr<BasicCamera>	m_basic_camera;
		static	std::unique_ptr<PreviewCamera>	m_preview_camera;

	};
}