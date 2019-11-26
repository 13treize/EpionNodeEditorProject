#include	"../All.h"
#include	"../epion.h"
#include	"dx11_device.h"
#include	"RenderTarget.h"


namespace
{
}

namespace	epion
{
	void	RenderTarget::Set(	com_ptr<ID3D11RenderTargetView>& rtv,
									com_ptr<ID3D11DepthStencilView>& dsv)
	{
		Device::GetContext()->OMSetRenderTargets(1,rtv.GetAddressOf(),dsv.Get());
		float color[4] = { 0,1,1,1 };
		Device::GetContext()->ClearRenderTargetView(rtv.Get(), color);
		Device::GetContext()->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void	RenderTarget::end(	com_ptr<ID3D11RenderTargetView>& rtv,
								com_ptr<ID3D11DepthStencilView>& dsv)
	{
		Device::GetContext()->OMSetRenderTargets(1, rtv.GetAddressOf(), dsv.Get());
	}


}