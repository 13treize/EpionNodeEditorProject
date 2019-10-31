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
		//�s��X�V
		void activate();


		DirectX::XMFLOAT4X4& get_view()
		{
			return matView;
		}

		DirectX::XMFLOAT4X4& get_projection()
		{
			return matProjection;
		}

		//get�֐�
		math::FVector3&	get_pos();
		math::FVector3&	get_target();
		math::FVector3&	get_up();

		//set�֐�
		void	set_pos(math::FVector3&		pos_);
		void	set_target(math::FVector3&	target_);
		void	set_up(math::FVector3&		up_);

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

	class	CameraManager	final
	{
	public:
		static	void	Init();
		static	void	Update();

		//get�֐�
		static	DirectX::XMFLOAT4X4& get_view();

		static	DirectX::XMFLOAT4X4& get_projection();

	private:
		static	std::unique_ptr<BasicCamera>	basic_camera;
	};
}