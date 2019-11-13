#include	"../epion.h"
#include	"dx11_device.h"
#include	"shader_reflection.h"

namespace
{
}

namespace	epion
{
	ShaderReflection::ShaderReflection()
	{
	}
	ShaderReflection::ShaderReflection(com_ptr<ID3DBlob>&	shader_code)
	{
		set_layout(shader_code);
	}
	ShaderReflection::~ShaderReflection()
	{
	}

	void	ShaderReflection::set_layout(com_ptr<ID3DBlob>&	shader_code)
	{
		HRESULT	hr = S_OK;

		hr = D3DReflect(shader_code->GetBufferPointer(),
			shader_code->GetBufferSize(),
			IID_ID3D11ShaderReflection,
			(void**)reflection_ptr.ReleaseAndGetAddressOf());

		D3D11_SHADER_DESC	shaderdesc = {};
		reflection_ptr->GetDesc(&shaderdesc);

		for (unsigned int i = 0; i < shaderdesc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC signaturePrameterDesc = {};
			reflection_ptr->GetInputParameterDesc(i, &signaturePrameterDesc);

			D3D11_INPUT_ELEMENT_DESC	element_desc = {};
			element_desc.SemanticName = signaturePrameterDesc.SemanticName;
			element_desc.SemanticIndex = signaturePrameterDesc.SemanticIndex;
			element_desc.Format = get_dxgi_format(signaturePrameterDesc.ComponentType, signaturePrameterDesc.Mask);
			element_desc.InputSlot = get_vertex_buffer_slot(signaturePrameterDesc.SemanticName);
			element_desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			element_desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			element_desc.InstanceDataStepRate = 0;

			layout.emplace_back(element_desc);
		}
	}

	void	ShaderReflection::set_layout(ID3DBlob*	shader_code)
	{
		HRESULT	hr = S_OK;

		hr = D3DReflect(shader_code->GetBufferPointer(),
			shader_code->GetBufferSize(),
			IID_ID3D11ShaderReflection,
			(void**)reflection_ptr.ReleaseAndGetAddressOf());

		D3D11_SHADER_DESC	shaderdesc = {};
		reflection_ptr->GetDesc(&shaderdesc);

		for (unsigned int i = 0; i < shaderdesc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC signaturePrameterDesc = {};
			reflection_ptr->GetInputParameterDesc(i, &signaturePrameterDesc);

			D3D11_INPUT_ELEMENT_DESC	element_desc = {};
			element_desc.SemanticName = signaturePrameterDesc.SemanticName;
			element_desc.SemanticIndex = signaturePrameterDesc.SemanticIndex;
			element_desc.Format = get_dxgi_format(signaturePrameterDesc.ComponentType, signaturePrameterDesc.Mask);
			element_desc.InputSlot = get_vertex_buffer_slot(signaturePrameterDesc.SemanticName);
			element_desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			element_desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			element_desc.InstanceDataStepRate = 0;

			layout.emplace_back(element_desc);
		}
	}

	const DXGI_FORMAT	ShaderReflection::get_dxgi_format(const D3D_REGISTER_COMPONENT_TYPE type, const byte mask)
	{
		switch (mask)
		{
		case 0xF:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:
				return DXGI_FORMAT_R32G32B32A32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:
				return DXGI_FORMAT_R32G32B32A32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:
				return DXGI_FORMAT_UNKNOWN;
			}
		case 0x7:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32G32B32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:
				return DXGI_FORMAT_R32G32B32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:
				return DXGI_FORMAT_R32G32B32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:
				return DXGI_FORMAT_UNKNOWN;
			}
		case 0x3:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32G32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:
				return DXGI_FORMAT_R32G32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:
				return DXGI_FORMAT_R32G32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:
				return	DXGI_FORMAT_UNKNOWN;
			}
		case 0x1:
			switch (type)
			{
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32_FLOAT;
			case D3D10_REGISTER_COMPONENT_SINT32:
				return DXGI_FORMAT_R32_SINT;
			case D3D10_REGISTER_COMPONENT_UINT32:
				return DXGI_FORMAT_R32_UINT;
			case D3D10_REGISTER_COMPONENT_UNKNOWN:
				return DXGI_FORMAT_UNKNOWN;
			}
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	const unsigned int	ShaderReflection::get_vertex_buffer_slot(const std::string semantic_name)
	{
		int slot = 0;
		int under_score_num = 0;
		int digit = 0;

		// 先頭がアンダースコアでない場合スロット指定がないものとしてスロット0
		if (semantic_name[0] != '_') return slot;

		int nameSize = static_cast<int>(semantic_name.size());
		for (int i = 0; i < nameSize; i++)
		{
			// 2つ目のアンダースコアを確認する
			if (under_score_num >= 2) break;

			// アンダースコアかどうか
			if (semantic_name[i] == '_')
			{
				under_score_num++;
				continue;
			}

			// 数字かどうか
			if (semantic_name[i] >= '0'&&semantic_name[i] <= '9')
			{
				slot *= 10;
				slot += semantic_name[i] - '0';
			}
		}

		return slot;
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC>&	ShaderReflection::get_layout()
	{
		return	layout;
	}
}