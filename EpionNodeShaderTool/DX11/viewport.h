#pragma	once

namespace	epion
{
	class	ViewPort
	{
	public:
		ViewPort() = default;
		~ViewPort() = default;

		void	set(math::FVector2&	size);

		D3D11_VIEWPORT	get_vp()	const	noexcept;

		/*[[nodiscard]]*/const	float	get_aspect()	const	noexcept;
	private:
		D3D11_VIEWPORT	vp = {};
	};
}//epion
