#include	"../All.h"
#include	"../epion.h"
#include	"dx11_device.h"
#include	"SamplerState.h"

namespace
{
}

namespace epion
{
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
		int array_index = std::clamp(index, 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT -1);
		Device::GetContext()->PSSetSamplers(array_index, 1, m_sampler_states[array_index].GetAddressOf());
	}

}