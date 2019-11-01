#include	"../epion.h"
#include	"Cube.h"


namespace	epion
{
	Cube::Cube()
	{
		file_name=	L"data//cube.obj";
		obj = std::make_unique<ObjMesh>(file_name);
		pos = { 0,0,0 };
		scale = { 10,10,10 };
		angle = { 0,0,0 };


	}
	Cube::~Cube()
	{
	}

	void	Cube::Update()
	{
		DirectX::XMMATRIX	mw = DirectX::XMMatrixIdentity();

		DirectX::XMMATRIX	s, r, t;

		//�}�g���N�X�͂��̂܂܌v�Z�ł���B
		//�@�g��s��쐬
		s = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

		//�@��]�s��쐬
		r = DirectX::XMMatrixRotationRollPitchYaw(angle.x*0.01745f, angle.y*0.01745f, angle.z*0.01745f);

		//�@�ړ��s��쐬
		t = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

		//�@�s�񍇐��ƕϊ�

		//XMFLOAT4X4�֕ϊ���Store�A�t��Load���߂��g���Ă��������B
		mw = s * r	*t;
		XMStoreFloat4x4(&matWorld, mw);
	}


	void	Cube::Render(const	DirectX::XMFLOAT4X4& view,
		const	DirectX::XMFLOAT4X4& projection,
		const	math::FVector4& light)
	{

		Color color = {1,0,0,255};
		DirectX::XMFLOAT4X4 world_view_projection;	//���[�J�����W����v���W�F�N�V�������W�ւ̕ϊ��}�g���N�X
		DirectX::XMFLOAT4X4 world;					//�@�������ׂ̂̃��[���h���W�@���ƁA�ʂ̌v�Z�p

		//�v���W�F�N�V�����ƃ��[���h�ƃr���[���R���X�^���g�o�b�t�@�ɕʁX�ɑ�����GPU�ō�������ƕ��񏈗����A�v�Z�����B
		//�Ȃ�΁A�ŏ�����v�Z���ꂽ���[�J���QD�ϊ��}�g���N�X�ƃ��[���h�}�g���N�X��n�������ǂ������B

		DirectX::XMMATRIX  WP = DirectX::XMLoadFloat4x4(&matWorld) * DirectX::XMLoadFloat4x4(&view) * DirectX::XMLoadFloat4x4(&projection);

		DirectX::XMStoreFloat4x4(&world_view_projection, WP);
		DirectX::XMStoreFloat4x4(&world, DirectX::XMLoadFloat4x4(&matWorld));

		obj->Render(world_view_projection, world, light,color);
	}

	//set�֐�
	void	Cube::set_pos(math::FVector3&	pos_)
	{
		pos = pos_;
	}
	void	Cube::set_scale(math::FVector3&	scale_)
	{
		scale = scale_;
	}
	void	Cube::set_angle(math::FVector3&	angle_)
	{
		angle = angle_;
	}

	//get�֐�
	math::FVector3&Cube::get_pos()
	{
		return	pos;
	}
	math::FVector3&	Cube::get_scale()
	{
		return	scale;
	}
	math::FVector3&	Cube::get_angle()
	{
		return	angle;
	}
	std::wstring&	Cube::get_file_name()
	{
		return	file_name;
	}

}