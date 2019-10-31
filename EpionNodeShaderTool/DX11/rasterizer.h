#pragma once
#include	"../epion.h"

namespace	epion
{
	enum	RASTER_STATE :unsigned	char
	{
		SOLID,
		WIRE_FRAME,
		RS_END,
	};

	//êFÅXí«â¡
	class	Rasterizer	final
	{
	public:
		Rasterizer();
		~Rasterizer();

		bool	create();
		void	set_state(RASTER_STATE	state_ = SOLID);

	private:
		D3D11_RASTERIZER_DESC				r_desc[RASTER_STATE::RS_END] = {};	//	https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
		com_ptr<ID3D11RasterizerState>		rasterizer_ptr[RASTER_STATE::RS_END];

		//true	wireframe,	false	solid
		void	create_desc();
	};
}