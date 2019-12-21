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



		void SetView(const	math::FVector3&	p, const	math::FVector3& t, const math::FVector3& u);

		void SetProjection(float fov, float aspect, float n, float f);
		//�s��X�V
		void Activate();


		DirectX::XMFLOAT4X4& GetView()
		{
			return matView;
		}

		DirectX::XMFLOAT4X4& GetProjection()
		{
			return matProjection;
		}

		//get�֐�
		math::FVector3&	GetPos();
		math::FVector3&	GetTarget();
		math::FVector3&	GetUp();

		//set�֐�
		void	SetPos(math::FVector3&		pos_);
		void	SetTarget(math::FVector3&	target_);
		void	SetUp(math::FVector3&		up_);

	protected:
		DirectX::XMFLOAT4X4	matView;		//����ϊ��s��
		DirectX::XMFLOAT4X4	matProjection;	//���e�ϊ��s��
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

	//Node��PreviewCamera
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

	class	Scene3DCamera	final : public	View
	{
	public:
		Scene3DCamera();

		Scene3DCamera(
			const	math::FVector3& p_,
			const	math::FVector3& t_,
			const	math::FVector3& u_,
			float fov_,
			float aspect_,
			float n_,
			float f_);

		~Scene3DCamera() {};
	};


	class	CameraManager	final
	{
	public:
		static	void	Init();
		static	void	Update();

		//get�֐�

		static std::unique_ptr<BasicCamera>&	GetBasicCamera();
		static std::unique_ptr<PreviewCamera>&	GetPreviewCamera();
		static std::unique_ptr<Scene3DCamera>&	GetScene3DCamera();

	private:
		static	std::unique_ptr<BasicCamera>	m_basic_camera;
		static	std::unique_ptr<PreviewCamera>	m_preview_camera;
		static	std::unique_ptr<Scene3DCamera>	m_scene3d_camera;

	};
}