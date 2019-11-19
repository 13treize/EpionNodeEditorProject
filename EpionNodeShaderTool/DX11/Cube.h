#pragma once
#include	"ObjMesh.h"

namespace	epion
{

	class	Cube	final
	{
	public:
		Cube(com_ptr<ID3DBlob>& blob);
		~Cube();

		void	Update();
		void	Render(
			const	DirectX::XMFLOAT4X4& view,
			const	DirectX::XMFLOAT4X4& projection);

		//setä÷êî
		void	SetPos(math::FVector3&	pos_);
		void	SetScale(math::FVector3&	scale_);
		void	SetAngle(math::FVector3&	angle_);

		//getä÷êî
		math::FVector3&	GetPos();
		math::FVector3&	GetScale();
		math::FVector3&	GetAngle();
		std::wstring&	GetFileName();

		std::unique_ptr<ObjMesh>	m_obj;

	private:
		std::wstring	m_file_name;

		math::FVector3		m_pos;
		math::FVector3		m_scale;
		math::FVector3		m_angle;
		DirectX::XMFLOAT4X4	m_world_matrix;
	};
}