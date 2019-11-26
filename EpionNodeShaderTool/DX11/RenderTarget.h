#pragma once
namespace	epion
{
	class	RenderTarget	final
	{
	public:

		static void	Set(com_ptr<ID3D11RenderTargetView>& rtv,
			com_ptr<ID3D11DepthStencilView>& dsv);
		static void	end(com_ptr<ID3D11RenderTargetView>& rtv,
						com_ptr<ID3D11DepthStencilView>& dsv);
	private:

	};
}