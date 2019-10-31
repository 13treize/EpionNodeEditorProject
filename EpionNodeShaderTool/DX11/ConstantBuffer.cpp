#include	"../All.h"
#include	"../epion.h"
#include	"dx11_device.h"
#include	"ConstantBuffer.h"


namespace
{
}


namespace	epion
{
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer0;
	com_ptr<ID3D11Buffer>	ConstantBufferManager::m_constant_buffer1;

	void ConstantBufferManager::CreateDesc(D3D11_BUFFER_DESC& desc,UINT size)
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
		cb.Time.x =	Time.x;
		cb.Time.y = 1;
		cb.Time.z = 1;
		cb.Time.w = 1;
		cb.ScreenSize= ScreenSize;
		cb.Dummy0		=math::FVector2(0,0);

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

}