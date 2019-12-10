#pragma	once

namespace	epion
{
	class	ViewPort
	{
	public:
		ViewPort() = default;
		~ViewPort() = default;

		void	Set(math::FVector2&	size);

		D3D11_VIEWPORT	GetViewPort()	const	noexcept;

		/*[[nodiscard]]*/const	float	GetAspect()	const	noexcept;
	private:
		D3D11_VIEWPORT	vp = {};
	};
}//epion
