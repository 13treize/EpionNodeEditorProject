#include	"blender.h"
#include	"dx11_device.h"
namespace
{
}


namespace	epion
{
	Blender::Blender()
	{
		all_create();
	}

	Blender::~Blender()
	{
	}

	void	Blender::SetState(BLEND_STATE	state)
	{
		Device::GetContext()->OMSetBlendState(blend_states[state].Get(), nullptr, 0xFFFFFFFF);
	}

	bool	Blender::all_create()
	{
		bool	is_check[9];
		is_check[0] = create(blend_states[BS_NONE],
			false,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);

		is_check[1] = create(blend_states[BS_ALPHA],
			true,
			D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);


		is_check[2] = create(blend_states[BS_ADD],
			true,
			D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);

		is_check[3] = create(blend_states[BS_SUBTRACT],
			true,
			D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_SUBTRACT,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);

		is_check[4] = create(blend_states[BS_REPLACE],
			true,
			D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);

		is_check[5] = create(blend_states[BS_MULTIPLY],
			true,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND::D3D11_BLEND_SRC_COLOR,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_DEST_ALPHA,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);

		is_check[6] = create(blend_states[BS_LIGHTEN],
			true,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_MAX,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_MAX);


		is_check[7] = create(blend_states[BS_DARKEN],
			true,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_MIN,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND_OP::D3D11_BLEND_OP_MIN);

		is_check[8] = create(blend_states[BS_SCREEN],
			true,
			D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND::D3D11_BLEND_SRC_COLOR,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD);
		return		(is_check[0] &&
			is_check[1] &&
			is_check[2] &&
			is_check[3] &&
			is_check[4] &&
			is_check[5] &&
			is_check[6] &&
			is_check[7] &&
			is_check[8]) ? true : false;
	}


	bool	Blender::create(com_ptr<ID3D11BlendState>	&blend_state_,
		bool						blend_enable_,
		const	D3D11_BLEND			src_blend_,
		const	D3D11_BLEND			dest_blend_,
		const	D3D11_BLEND_OP		blend_op_,
		const	D3D11_BLEND			src_blend_alpha_,
		const	D3D11_BLEND			dest_blend_alpha_,
		const	D3D11_BLEND_OP		blend_op_alpha_)
	{
		HRESULT	hr = {};
		D3D11_BLEND_DESC	blend_desc = {};
		blend_desc.AlphaToCoverageEnable = false;
		blend_desc.IndependentBlendEnable = false;
		blend_desc.RenderTarget[0].BlendEnable = blend_enable_;
		blend_desc.RenderTarget[0].SrcBlend = src_blend_;
		blend_desc.RenderTarget[0].DestBlend = dest_blend_;
		blend_desc.RenderTarget[0].BlendOp = blend_op_;
		blend_desc.RenderTarget[0].SrcBlendAlpha = src_blend_alpha_ ? src_blend_alpha_ : src_blend_;
		blend_desc.RenderTarget[0].DestBlendAlpha = dest_blend_alpha_ ? dest_blend_alpha_ : dest_blend_;
		blend_desc.RenderTarget[0].BlendOpAlpha = blend_op_alpha_ ? blend_op_alpha_ : blend_op_;
		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		hr = Device::GetDevice()->CreateBlendState(&blend_desc, blend_state_.ReleaseAndGetAddressOf());

		return	SUCCEEDED(hr) ? true : false;
	}
}