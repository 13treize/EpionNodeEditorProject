#pragma once

namespace	epion
{
	class	InputLayout
	{
	public:
		InputLayout();
		InputLayout(const	std::vector<D3D11_INPUT_ELEMENT_DESC>&	layout, com_ptr<ID3DBlob>&	v_shader_blob);
		~InputLayout();

		void	Create(const	std::vector<D3D11_INPUT_ELEMENT_DESC>&	layout, com_ptr<ID3DBlob>&	v_shader_blob);
		void	SetState();

	private:
		com_ptr<ID3D11InputLayout>	m_input_layout;
	};
}

