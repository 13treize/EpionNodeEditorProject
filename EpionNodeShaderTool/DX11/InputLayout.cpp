#include	"../epion.h"
#include	"InputLayout.h"
#include	"dx11_device.h"



namespace	epion
{
	InputLayout::InputLayout()
	{
	}

	InputLayout::InputLayout(const	std::vector<D3D11_INPUT_ELEMENT_DESC>&	layout, com_ptr<ID3DBlob>&	v_shader_blob)
	{
		Create(layout, v_shader_blob);
	}

	InputLayout::~InputLayout()
	{
	}

	void	InputLayout::Create(const	std::vector<D3D11_INPUT_ELEMENT_DESC>&	layout, com_ptr<ID3DBlob>&	v_shader_blob)
	{
		unsigned	int	layout_size = static_cast<unsigned	int>(layout.size());
		Device::GetDevice()->CreateInputLayout(layout.data(),
			layout_size,
			v_shader_blob->GetBufferPointer(),
			v_shader_blob->GetBufferSize(),
			m_input_layout.ReleaseAndGetAddressOf());
	}

	void	InputLayout::SetState()
	{
		Device::GetContext()->IASetInputLayout(m_input_layout.Get());
	}
}