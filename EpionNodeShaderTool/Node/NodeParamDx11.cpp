#include	"../All.h"
#include	"../epion.h"
#include	"../DX11/dx11_device.h"
#include	"NodeParamDx11.h"

namespace	epion::Node::Dx11
{
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer0;
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer1;
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer2;
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer3;

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
		if (FAILED(hr))	return false;
		bd = {};
		CreateDesc(bd, sizeof(CBuffer1));
		hr = epion::Device::GetDevice()->CreateBuffer(&bd, nullptr, m_constant_buffer1.ReleaseAndGetAddressOf());
		if (FAILED(hr))	return false;
		bd = {};
		CreateDesc(bd, sizeof(CBuffer2));
		hr = epion::Device::GetDevice()->CreateBuffer(&bd, nullptr, m_constant_buffer2.ReleaseAndGetAddressOf());
		if (FAILED(hr))	return false;
		bd = {};
		CreateDesc(bd, sizeof(CBuffer3));
		hr = epion::Device::GetDevice()->CreateBuffer(&bd, nullptr, m_constant_buffer3.ReleaseAndGetAddressOf());
		if (FAILED(hr))	return false;
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
		Device::GetContext()->VSSetConstantBuffers(1, 1, m_constant_buffer1.GetAddressOf());
		Device::GetContext()->PSSetConstantBuffers(1, 1, m_constant_buffer1.GetAddressOf());
	}

	void ConstantBufferManager::UpdateCBuffer2(math::FVector3&	Pos, math::FVector3&	Target, math::FVector3&	Up)
	{
		CBuffer2 cb = {};
		cb.Pos.SetXYZ(Pos.x, Pos.y, Pos.z);
		cb.Target.SetXYZ(Target.x, Target.y, Target.z);
		cb.Up.SetXYZ(Up.x, Up.y, Up.z);
		cb.Pos.w = 0;
		cb.Target.w = 0;
		cb.Up.w = 0;
		Device::GetContext()->UpdateSubresource(m_constant_buffer2.Get(), 0, nullptr, &cb, 0, 0);
		Device::GetContext()->VSSetConstantBuffers(2, 1, m_constant_buffer2.GetAddressOf());
		Device::GetContext()->PSSetConstantBuffers(2, 1, m_constant_buffer2.GetAddressOf());
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

	com_ptr<ID3D11DepthStencilState>	DepthStencilStateManager::m_depth_stencil_state;

	bool DepthStencilStateManager::Create()
	{
		HRESULT	hr = S_OK;

		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};
		depth_stencil_desc.DepthEnable = true;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
		hr = Device::GetDevice()->CreateDepthStencilState(&depth_stencil_desc,m_depth_stencil_state.GetAddressOf());

		if (FAILED(hr))	return false;
		return true;
	}

	void DepthStencilStateManager::SetState()
	{
		Device::GetContext()->OMSetDepthStencilState(m_depth_stencil_state.Get(), 1);
	}


}