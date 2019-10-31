#pragma once
#include	"../epion.h"
#include	<string>
#include	<vector>
namespace	epion
{
	class	ShaderReflection	final
	{
	public:
		ShaderReflection();
		ShaderReflection(com_ptr<ID3DBlob>&	shader_code);
		~ShaderReflection();

		void	set_layout(com_ptr<ID3DBlob>&	shader_code);

		void	set_layout(ID3DBlob*	shader_code);

		std::vector<D3D11_INPUT_ELEMENT_DESC>&	get_layout();
	private:
		com_ptr<ID3D11ShaderReflection>	reflection_ptr;

		std::vector<D3D11_INPUT_ELEMENT_DESC>	layout = {};

		const DXGI_FORMAT get_dxgi_format(const D3D_REGISTER_COMPONENT_TYPE type,
			const byte mask);

		const unsigned int	get_vertex_buffer_slot(const std::string semantic_name);
	};
}