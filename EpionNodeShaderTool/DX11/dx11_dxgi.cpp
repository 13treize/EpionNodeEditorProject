#include	"../All.h"
#include	"../epion.h"

#include	"dx11_device.h"

#include	"dx11_dxgi.h"

namespace
{
}

namespace	epion
{

	/*
		Dxgi
	*/
	SwapChain	Dxgi::swap_chain;
	DepthView	Dxgi::depth_view;
	Texture_2d	Dxgi::depth_2d;
	ViewPort	Dxgi::view_port;
	com_ptr<IDXGISwapChain>			Dxgi::gi_swapchain;
	com_ptr<ID3D11RenderTargetView>	Dxgi::render_target_view;
	com_ptr<ID3D11DepthStencilView>	Dxgi::depth_stencil_view;
	com_ptr<ID3D11Texture2D>		Dxgi::back_buffer;

	void	Dxgi::Set(math::FVector2&	win_size_)
	{
		HRESULT	hr = S_OK;

		com_ptr<IDXGIDevice>	gi_device;
		hr = Device::GetDevice().Get()->QueryInterface(
			__uuidof(gi_device),
			r_cast<void**>(gi_device.ReleaseAndGetAddressOf()));
		if (FAILED(hr))
		{
			std::terminate();
			throw	"インタフェース取得失敗";
		}

		com_ptr<IDXGIAdapter>		gi_adapter;
		hr = gi_device->GetAdapter(gi_adapter.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			std::terminate();
			throw	"アダプタ取得失敗";
		}

		com_ptr<IDXGIFactory>		gi_factory;
		hr = gi_adapter->GetParent(
			__uuidof(gi_factory),
			r_cast<void**>(gi_factory.ReleaseAndGetAddressOf()));
		if (FAILED(hr))
		{
			std::terminate();
			throw	"ファクトリー取得失敗";
		}

		hr = gi_factory->CreateSwapChain(Device::GetDevice().Get(),
			&swap_chain.Init(win_size_),
			gi_swapchain.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			std::terminate();
			throw	"スワップチェイン生成失敗";
		}

		D3D11_TEXTURE2D_DESC		back_buffer_desc = {};
		hr = gi_swapchain->GetBuffer(0,
			__uuidof(back_buffer),
			r_cast<void**>(back_buffer.ReleaseAndGetAddressOf()));
		if (FAILED(hr))
		{
			std::terminate();
			throw	"バックバッファ生成失敗";
		}

		hr = Device::GetDevice()->CreateRenderTargetView(back_buffer.Get(),
			nullptr,
			render_target_view.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			std::terminate();
			throw	"レンダーターゲットビュー失敗";
		}
		back_buffer->GetDesc(&back_buffer_desc);

		com_ptr<ID3D11Texture2D>	depth_stencil_buffer;

		hr = Device::GetDevice()->CreateTexture2D(&depth_2d.Create(back_buffer_desc,
			D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL),
			nullptr,
			depth_stencil_buffer.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			std::terminate();
			throw	"深度ステンシルバッファ生成失敗";
		}

		hr = Device::GetDevice()->CreateDepthStencilView(depth_stencil_buffer.Get(),
			&depth_view.Create(depth_2d.get_texture_desc()),
			depth_stencil_view.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			std::terminate();
			throw	"深度ステンシルビュー失敗";
		}

		view_port.Set(win_size_);
	}

	void	epion::Dxgi::Begin(std::array<float, 4>&	colordata_)
	{
		Device::GetContext()->RSSetViewports(1, &view_port.GetViewPort());
		Device::GetContext()->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());
		Device::GetContext()->ClearRenderTargetView(render_target_view.Get(), colordata_.data());
		Device::GetContext()->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void	epion::Dxgi::End()
	{
		gi_swapchain->Present(0, 0);
	}


	DXGI_SWAP_CHAIN_DESC&	SwapChain::Init(math::FVector2&	win_size_)
	{
		swap_desc.BufferDesc.Width = st_cast<UINT>(win_size_.x);						//バッファの幅
		swap_desc.BufferDesc.Height = st_cast<UINT>(win_size_.y);						//バッファの高さ
		swap_desc.BufferDesc.RefreshRate.Numerator = 60;												//リフレッシュレート	Hz
		swap_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_desc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;			//バッファのフォーマット
		swap_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
		swap_desc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;

		swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_desc.SampleDesc.Count = 1;
		swap_desc.SampleDesc.Quality = 0;
		swap_desc.BufferCount = 2;											//バックバッファの数
		swap_desc.OutputWindow = MainSystem::GetHwnd();
		swap_desc.Windowed = true;
		swap_desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
		//swap_desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
		swap_desc.Flags = 0;
		return	swap_desc;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC&	DepthView::Create(D3D11_TEXTURE2D_DESC&	t_desc)
	{
		depth_stencil.Format = t_desc.Format;
		depth_stencil.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depth_stencil.Flags = 0;
		depth_stencil.Texture2D.MipSlice = 0;
		return	depth_stencil;
	}

	D3D11_TEXTURE2D_DESC&	Texture_2d::Create(
		D3D11_TEXTURE2D_DESC&	back_buffer_desc,
		D3D11_BIND_FLAG			bind_flag)
	{
		texture_desc = back_buffer_desc;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		texture_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags = bind_flag;
		texture_desc.CPUAccessFlags = 0;
		texture_desc.MiscFlags = 0;
		return	texture_desc;
	}
}