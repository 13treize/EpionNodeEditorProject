#include	"../epion.h"
#include	"dx11_state.h"
#include	"dx11_device.h"

namespace	epion
{
	Sampler::Sampler()
	{
		create();
	}
	Sampler::~Sampler()
	{
	}


	bool	Sampler::create()
	{
		HRESULT	hr = {};
		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		sampler_desc.MipLODBias = 1.0f;
		sampler_desc.MaxAnisotropy = 16;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

		sampler_desc.BorderColor[0] = 0.0f;
		sampler_desc.BorderColor[1] = 0.0f;
		sampler_desc.BorderColor[2] = 0.0f;
		sampler_desc.BorderColor[3] = 0.0f;

		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = Device::GetDevice()->CreateSamplerState(&sampler_desc, sampler_ptr.ReleaseAndGetAddressOf());

		return	SUCCEEDED(hr) ? true : false;
	}

	void	Sampler::set_state()
	{
		Device::GetContext()->PSSetSamplers(0, 1, sampler_ptr.GetAddressOf());
	}

	DepthStencil::DepthStencil()
	{
		create();
	}

	DepthStencil::~DepthStencil()
	{
	}

	bool	DepthStencil::create()
	{
		HRESULT	hr = {};
		d_desc.DepthEnable = true;														//�[�x�e�X�g���g�p�\���ǂ���
		d_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		d_desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		d_desc.StencilEnable = false;													//�X�e���V���e�X�g���g�p�\���ǂ���
		d_desc.StencilReadMask = 0xFF;
		d_desc.StencilWriteMask = 0xFF;

		d_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;		//�X�e���V���e�X�g�ŕs���i�ƂȂ����Ƃ��Ɏ��s����X�e���V������
		d_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_INCR;	//�X�e���V���e�X�g�ɍ��i���A�[�x�e�X�g�ŕs���i�ƂȂ����Ƃ��Ɏ��s����X�e���V������
		d_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;		//�X�e���V���e�X�g�Ɛ[�x�e�X�g�̗����ɍ��i�����Ƃ��Ɏ��s����X�e���V������
		d_desc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;	//�X�e���V���f�[�^�������̃X�e���V��	�f�[�^�Ɣ�r����֐�

		d_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
		d_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_DECR;
		d_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
		d_desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		hr =Device::GetDevice()->CreateDepthStencilState(&d_desc, depth_stencil_ptr.ReleaseAndGetAddressOf());
		return	SUCCEEDED(hr) ? true : false;
	}

	void	DepthStencil::set_state()
	{
		Device::GetContext()->OMSetDepthStencilState(depth_stencil_ptr.Get(), 1);
	}
}