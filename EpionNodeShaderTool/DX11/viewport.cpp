#include	"../epion.h"
#include	"viewport.h"

namespace	epion
{
	void	ViewPort::set(math::FVector2&	size)
	{
		vp.Width = size.x;
		vp.Height = size.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0.0f;
		vp.TopLeftY = 0.0f;
	}

	D3D11_VIEWPORT	ViewPort::get_vp()const	noexcept
	{
		return	vp;
	}

	[[nodiscard]]const	float	ViewPort::get_aspect()	const	noexcept
	{
		return	vp.Width / vp.Height;
	}
}//epion