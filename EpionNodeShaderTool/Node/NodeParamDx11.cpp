#include	"../All.h"
#include	"../epion.h"
#include	"../DX11/dx11_device.h"
#include	"NodeParamDx11.h"

namespace	epion::NodeCustom::Dx11
{
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer0;
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer1;

	void ConstantBufferManager::CreateDesc(D3D11_BUFFER_DESC& desc, UINT size)
	{
		desc.ByteWidth = size;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
	}

	bool ConstantBufferManager::Create()
	{
		HRESULT	hr = S_OK;

		D3D11_BUFFER_DESC bd = {};
		CreateDesc(bd, sizeof(CBuffer0));

		hr = epion::Device::GetDevice()->CreateBuffer(&bd, nullptr, m_constant_buffer0.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}

	void ConstantBufferManager::UpdateCBuffer0(math::FVector4&	Time, math::FVector2&	ScreenSize)
	{
		CBuffer0 cb = {};
		cb.Time.x = Time.x;
		cb.Time.y = 1;
		cb.Time.z = 1;
		cb.Time.w = 1;
		cb.ScreenSize = ScreenSize;
		cb.Dummy0 = math::FVector2(0, 0);

		Device::GetContext()->UpdateSubresource(m_constant_buffer0.Get(), 0, nullptr, &cb, 0, 0);
		Device::GetContext()->VSSetConstantBuffers(0, 1, m_constant_buffer0.GetAddressOf());
		Device::GetContext()->PSSetConstantBuffers(0, 1, m_constant_buffer0.GetAddressOf());
	}

	void ConstantBufferManager::UpdateCBuffer1(math::FVector4&	LightColor, math::FVector4&	LightDir, math::FVector4&	AmbientColor)
	{
		CBuffer1 cb = {};
		cb.AmbientColor = AmbientColor;
		cb.LightColor = LightColor;
		cb.LightDir = LightDir;

		Device::GetContext()->UpdateSubresource(m_constant_buffer1.Get(), 0, nullptr, &cb, 0, 0);
		Device::GetContext()->VSSetConstantBuffers(2, 1, m_constant_buffer1.GetAddressOf());
		Device::GetContext()->PSSetConstantBuffers(2, 1, m_constant_buffer1.GetAddressOf());
	}

	com_ptr<ID3D11SamplerState> SamplerStateManager::m_sampler_states[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];

	bool SamplerStateManager::Create(int index, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
	{
		HRESULT	hr = {};
		D3D11_SAMPLER_DESC	sampler_desc;
		int array_index = std::clamp(index, 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1);
		sampler_desc.Filter = filter;
		sampler_desc.AddressU = address;
		sampler_desc.AddressV = address;
		sampler_desc.AddressW = address;

		sampler_desc.MipLODBias = 1.0f;
		sampler_desc.MaxAnisotropy = 16;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

		sampler_desc.BorderColor[0] = 0.0f;
		sampler_desc.BorderColor[1] = 0.0f;
		sampler_desc.BorderColor[2] = 0.0f;
		sampler_desc.BorderColor[3] = 0.0f;

		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
		hr = Device::GetDevice()->CreateSamplerState(&sampler_desc, m_sampler_states[index].ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			return false;
		}
		return true;

	}
	void SamplerStateManager::SetState(int index)
	{
		int array_index = std::clamp(index, 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1);
		Device::GetContext()->PSSetSamplers(array_index, 1, m_sampler_states[array_index].GetAddressOf());
	}

}