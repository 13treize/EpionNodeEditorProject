
#include	"../All.h"
#include	"../epion.h"
#include	"Cube.h"


namespace	epion
{
	Cube::Cube(const std::wstring& model,com_ptr<ID3DBlob>& blob)
	{
		m_file_name= model;
		m_obj = std::make_unique<ObjMesh>(m_file_name,blob);
		m_pos = { 0,0,0 };
		m_scale = { 1,1,1 };
		m_angle = { 0,0,0 };


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
		s = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);

		//�@��]�s��쐬
		r = DirectX::XMMatrixRotationRollPitchYaw(m_angle.x, m_angle.y, m_angle.z);

		//�@�ړ��s��쐬
		t = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

		//�@�s�񍇐��ƕϊ�

		//XMFLOAT4X4�֕ϊ���Store�A�t��Load���߂��g���Ă��������B
		mw = s * r	*t;
		XMStoreFloat4x4(&m_world_matrix, mw);
	}


	void	Cube::Render(const	DirectX::XMFLOAT4X4& view,const	DirectX::XMFLOAT4X4& projection)
	{

		DirectX::XMFLOAT4X4 world_view_projection;	//���[�J�����W����v���W�F�N�V�������W�ւ̕ϊ��}�g���N�X
		DirectX::XMFLOAT4X4 world;					//�@�������ׂ̂̃��[���h���W�@���ƁA�ʂ̌v�Z�p

		//�v���W�F�N�V�����ƃ��[���h�ƃr���[���R���X�^���g�o�b�t�@�ɕʁX�ɑ�����GPU�ō�������ƕ��񏈗����A�v�Z�����B
		//�Ȃ�΁A�ŏ�����v�Z���ꂽ���[�J���QD�ϊ��}�g���N�X�ƃ��[���h�}�g���N�X��n�������ǂ������B

		DirectX::XMMATRIX  WP = DirectX::XMLoadFloat4x4(&m_world_matrix) * DirectX::XMLoadFloat4x4(&view) * DirectX::XMLoadFloat4x4(&projection);

		DirectX::XMStoreFloat4x4(&world_view_projection, WP);
		DirectX::XMStoreFloat4x4(&world, DirectX::XMLoadFloat4x4(&m_world_matrix));

		m_obj->Render(world_view_projection, world);
	}

	//set�֐�
	void	Cube::SetPos(math::FVector3&	pos_)
	{
		m_pos = pos_;
	}
	void	Cube::SetScale(math::FVector3&	scale_)
	{
		m_scale = scale_;
	}
	void	Cube::SetAngle(math::FVector3&	angle_)
	{
		m_angle = angle_;
	}

	//get�֐�
	math::FVector3&Cube::GetPos()
	{
		return	m_pos;
	}
	math::FVector3&	Cube::GetScale()
	{
		return	m_scale;
	}
	math::FVector3&	Cube::GetAngle()
	{
		return	m_angle;
	}
	std::wstring&	Cube::GetFileName()
	{
		return	m_file_name;
	}

}