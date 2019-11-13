#pragma once
#include	"ObjMesh.h"

namespace	epion
{

	class	Cube	final
	{
	public:
		Cube();
		~Cube();

		void	Update();
		void	Render(
			const	DirectX::XMFLOAT4X4& view,
			const	DirectX::XMFLOAT4X4& projection);

		//setä÷êî
		void	set_pos(math::FVector3&	pos_);
		void	set_scale(math::FVector3&	scale_);
		void	set_angle(math::FVector3&	angle_);

		//getä÷êî
		math::FVector3&	get_pos();
		math::FVector3&	get_scale();
		math::FVector3&	get_angle();
		std::wstring&	get_file_name();

		std::unique_ptr<ObjMesh>	obj;

	private:
		std::wstring	file_name;

		math::FVector3		pos;
		math::FVector3		scale;
		math::FVector3		angle;
		DirectX::XMFLOAT4X4	matWorld;
	};
}