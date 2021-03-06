#pragma	once

#include	"viewport.h"

namespace	epion
{
	class	SwapChain	final
	{
	public:
		SwapChain() = default;
		~SwapChain() = default;
		DXGI_SWAP_CHAIN_DESC&	Init(math::FVector2&	win_size_);

	private:
		DXGI_SWAP_CHAIN_DESC	swap_desc = {};
	};

	class	DepthView	final
	{
	public:
		DepthView() = default;
		~DepthView() = default;

		D3D11_DEPTH_STENCIL_VIEW_DESC&	Create(D3D11_TEXTURE2D_DESC&	t_desc);

	private:
		D3D11_DEPTH_STENCIL_VIEW_DESC	depth_stencil = {};
	};

	class	Texture_2d	final
	{
	public:
		Texture_2d() = default;
		~Texture_2d() = default;

		D3D11_TEXTURE2D_DESC&	Create(D3D11_TEXTURE2D_DESC&	back_buffer_desc,
			D3D11_BIND_FLAG			bind_flag);

		D3D11_TEXTURE2D_DESC&	get_texture_desc()
		{
			return	texture_desc;
		}
	private:
		D3D11_TEXTURE2D_DESC			texture_desc;
	};

	class	Dxgi	final
	{
	public:
		static	void	Set(math::FVector2&	win_size_);
		static	void	Begin(std::array<float, 4>&	colordata_);
		static	void	End();

		static	ViewPort&	GetViewPort()
		{
			return	view_port;
		};

		static	com_ptr<ID3D11DepthStencilView>&	GetDSV()
		{
			return depth_stencil_view;
		}

		static	com_ptr<ID3D11RenderTargetView>&	GetRTV()
		{
			return render_target_view;
		}

		static	com_ptr<ID3D11Texture2D>	back_buffer;

	private:
		static	SwapChain	swap_chain;
		static	DepthView	depth_view;
		static	Texture_2d	depth_2d;

		//ここにviewportを置くのはどうなのか
		static	ViewPort	view_port;

		static	com_ptr<IDXGISwapChain>			gi_swapchain;
		static	com_ptr<ID3D11RenderTargetView>	render_target_view;
		static	com_ptr<ID3D11DepthStencilView>	depth_stencil_view;
	};
}	//namespace	epion::dx11