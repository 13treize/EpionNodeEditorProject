#pragma	once
#include	"../epion.h"

namespace	epion
{
	enum	BLEND_STATE : unsigned	char
	{
		BS_NONE,
		BS_ALPHA,
		BS_ADD,
		BS_SUBTRACT,
		BS_REPLACE,
		BS_MULTIPLY,
		BS_LIGHTEN,
		BS_DARKEN,
		BS_SCREEN,
		BS_END,
	};
	class	Blender	final
	{
	public:
		Blender();
		~Blender();

		bool	all_create();

		void	SetState(BLEND_STATE	state);

	private:
		bool	create(com_ptr<ID3D11BlendState>	&blend_state_,
			bool						blend_enable_,
			const	D3D11_BLEND			src_blend_,
			const	D3D11_BLEND			dest_blend_,
			const	D3D11_BLEND_OP		blend_op_,
			const	D3D11_BLEND			src_blend_alpha_ = {},
			const	D3D11_BLEND			dest_blend_alpha_ = {},
			const	D3D11_BLEND_OP		blend_op_alpha_ = {});

		com_ptr<ID3D11BlendState>	blend_states[BLEND_STATE::BS_END];
	};
}