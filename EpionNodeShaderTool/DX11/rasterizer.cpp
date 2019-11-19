#include	"rasterizer.h"
#include	"dx11_device.h"
namespace
{
}


namespace	epion
{

	Rasterizer::Rasterizer()
	{
		create();
	}

	Rasterizer::~Rasterizer()
	{

	};


	void	Rasterizer::create_desc()
	{
		r_desc[SOLID].FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		r_desc[SOLID].CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		r_desc[SOLID].FrontCounterClockwise = false;	//三角形が前向きか後ろ向きかを決定します
		r_desc[SOLID].DepthBias = 0;		//https://msdn.microsoft.com/en-us/library/windows/desktop/cc308048(v=vs.85).aspx
		r_desc[SOLID].DepthBiasClamp = 0;
		r_desc[SOLID].SlopeScaledDepthBias = 0;
		r_desc[SOLID].DepthClipEnable = true;
		r_desc[SOLID].ScissorEnable = false;
		r_desc[SOLID].MultisampleEnable = false;
		r_desc[SOLID].AntialiasedLineEnable = false;

		r_desc[WIRE_FRAME].FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		r_desc[WIRE_FRAME].CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		r_desc[WIRE_FRAME].FrontCounterClockwise = false;	//三角形が前向きか後ろ向きかを決定します
		r_desc[WIRE_FRAME].DepthBias = 0;		//https://msdn.microsoft.com/en-us/library/windows/desktop/cc308048(v=vs.85).aspx
		r_desc[WIRE_FRAME].DepthBiasClamp = 0;
		r_desc[WIRE_FRAME].SlopeScaledDepthBias = 0;
		r_desc[WIRE_FRAME].DepthClipEnable = true;
		r_desc[WIRE_FRAME].ScissorEnable = false;
		r_desc[WIRE_FRAME].MultisampleEnable = false;
		r_desc[WIRE_FRAME].AntialiasedLineEnable = false;
	}

	bool	Rasterizer::create()
	{
		HRESULT	hr[2] = {};
		create_desc();
		hr[0] = Device::GetDevice()->CreateRasterizerState(&r_desc[SOLID],
			rasterizer_ptr[SOLID].ReleaseAndGetAddressOf());
		hr[1] = Device::GetDevice()->CreateRasterizerState(&r_desc[WIRE_FRAME],
			rasterizer_ptr[WIRE_FRAME].ReleaseAndGetAddressOf());

		return	SUCCEEDED(hr[0]) && SUCCEEDED(hr[1]) ? true : false;

	}

	void	Rasterizer::SetState(RASTER_STATE	state_)
	{
		Device::GetContext()->RSSetState(rasterizer_ptr[state_].Get());
	}
}	//namespace	epion