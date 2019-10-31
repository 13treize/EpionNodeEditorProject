#include	"../All.h"
#include	<wincodec.h>
#include	"../epion.h"
#include	"Texture.h"
#include	"dx11_device.h"
#include	"../epion_string.h"

namespace
{

}

namespace	epion
{

	Texture::Texture()
	{}
	Texture::Texture(std::wstring	load_texture) :texture_name(load_texture)
	{}
	Texture::~Texture()
	{}
	void	Texture::load_file(com_ptr<ID3D11ShaderResourceView>	&shader_resource_view)
	{
		HRESULT	hr = S_OK;
		hr = LoadFromWICFile(texture_name.c_str(), 0, &metadata, image);
		if (FAILED(hr))
		{
			//throw	std::runtime_error("画像の読み込みに失敗しました");
		};

		//	画像からシェーダリソースを生成
		hr = CreateShaderResourceView(Device::GetDevice().Get(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			shader_resource_view.ReleaseAndGetAddressOf());
	}

	void	Texture::load_file(com_ptr<ID3D11ShaderResourceView>	&shader_resource_view,
		com_ptr<ID3D11UnorderedAccessView>	&unordered_access_view)
	{
		HRESULT	hr = S_OK;
		hr = LoadFromWICFile(texture_name.c_str(), 0, &metadata, image);
		if (FAILED(hr))
		{
			//throw	std::runtime_error("画像の読み込みに失敗しました");
		};

		//	画像からシェーダリソースを生成
		hr = CreateShaderResourceView(Device::GetDevice().Get(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			shader_resource_view.ReleaseAndGetAddressOf());
		//if(FAILED(hr))
		//{
		//	throw	"シェーダーリソース生成に失敗しました";
		//};
	}
	bool Texture::Create(u_int width, u_int height, DXGI_FORMAT format)
	{
		HRESULT hr = S_OK;
		//	テクスチャ作成
		texture_desc = {};
		texture_desc.Width = width;
		texture_desc.Height = height;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.Format = format;
		texture_desc.SampleDesc.Count = 1;
		texture_desc.Usage = D3D11_USAGE_DEFAULT;
		texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

		hr = Device::GetDevice()->CreateTexture2D(&texture_desc, nullptr, Texture2D.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}

		//	レンダーターゲットビュー作成
		D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
		rtvd.Format = format;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = 0;
		hr = Device::GetDevice()->CreateRenderTargetView(Texture2D.Get(), &rtvd, RenderTargetView.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}


		//	シェーダーリソースビュー作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
		srvd.Format = format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;
		hr = Device::GetDevice()->CreateShaderResourceView(Texture2D.Get(), &srvd, ShaderResourceView.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}


		//	サンプラステート作成
		D3D11_SAMPLER_DESC sd = {};
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
		//ボーダーカラー
		sd.BorderColor[0] = 1.0f;
		sd.BorderColor[1] = 1.0f;
		sd.BorderColor[2] = 1.0f;
		sd.BorderColor[3] = 1.0f;

		sd.MinLOD = 0;
		sd.MaxLOD = D3D11_FLOAT32_MAX;

		hr = Device::GetDevice()->CreateSamplerState(&sd, sampler.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}

	bool TextureFile::LoadTexture(std::wstring	load_texture, DirectX::TexMetadata&	metadata, DirectX::ScratchImage&	image, com_ptr<ID3D11ShaderResourceView>& srv)
	{
		HRESULT	hr = S_OK;
		hr = LoadFromWICFile(load_texture.c_str(), 0, &metadata, image);
		if (FAILED(hr))
		{
			return false;
		};
		hr = CreateShaderResourceView(Device::GetDevice().Get(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			srv.GetAddressOf());
		//if (FAILED(hr))
		//{
		//	return false;
		//};

		return true;
	}

	bool TextureFile::SaveTexture(std::string name,	std::string ext, com_ptr<ID3D11Texture2D>& texture)
	{
		HRESULT hr = {};
		DirectX::ScratchImage output_image = {};//出力画像
		GUID guid;//ファイル拡張子に対応したやつ、よくわからん
		Extension extension = ExtensionGet(ext);

		switch (extension)
		{
		case Extension::PNG:	guid = GUID_ContainerFormatPng;		break;
		case Extension::JPG:	guid = GUID_ContainerFormatJpeg;	break;
		}
		std::string tex = name + ext;
		hr = DirectX::CaptureTexture(Device::GetDevice().Get(), Device::GetContext().Get(), texture.Get(), output_image);
		hr = DirectX::SaveToWICFile(*output_image.GetImages(), 0, guid, StringConverter::to_wstring(tex).c_str());
		return true;
	}
	Extension TextureFile::ExtensionGet(std::string extension)
	{
		if (extension == ".png")return Extension::PNG;
		else if (extension == ".jpg")return Extension::JPG;

		return Extension::NONE;

	}

	math::Vector2<float>	Texture::get_mata_data()
	{
		math::Vector2<float>	tex_size =
		{
			static_cast<float>(metadata.width),
			static_cast<float>(metadata.height),
		};
		return	tex_size;
	}
}