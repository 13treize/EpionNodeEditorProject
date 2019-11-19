#include	"../All.h"
#include	"../epion.h"
#include	"dx11_device.h"
#include	"renderer.h"

#include	"NodeResult.h"

namespace epion::NodeCustom
{
	bool	ShaderCompiler2::compile(const	std::wstring	hlsl_name,
		const	std::string		entry_point,
		const	std::string		target,
		com_ptr<ID3DBlob>&	shader_blob)
	{
		HRESULT	hr = S_OK;

		unsigned	int	flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef	_DEBUG
		flags |= D3DCOMPILE_DEBUG;
#endif
		com_ptr<ID3DBlob>	error_blob = {};

		hr = D3DCompileFromFile(hlsl_name.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entry_point.c_str(),
			target.c_str(),
			flags,
			0,
			shader_blob.ReleaseAndGetAddressOf(),
			error_blob.GetAddressOf());

		if (FAILED(hr))
		{
			return	false;
		}
		if (error_blob)
		{
			return	false;
		}
		return	true;
	}
	void	ConstantBufferCreate(com_ptr<ID3D11Device>&	device, com_ptr<ID3D11Buffer>	buffer,UINT size)
	{
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = size;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		HRESULT	hr = device->CreateBuffer(&bd, nullptr, buffer.ReleaseAndGetAddressOf());
		assert(SUCCEEDED(hr));

	}
	void	InputLayoutCreate(com_ptr<ID3D11Device>&	device, com_ptr<ID3D11InputLayout>	layout_ptr,
		const	std::vector<D3D11_INPUT_ELEMENT_DESC>&	layout, com_ptr<ID3DBlob>&	v_shader_blob)
	{
		device->CreateInputLayout(
			layout.data(),
			static_cast<unsigned	int>(layout.size()),
			v_shader_blob->GetBufferPointer(),
			v_shader_blob->GetBufferSize(),
			layout_ptr.ReleaseAndGetAddressOf());
	}

	bool	ShaderManager::ShaderCreate(	com_ptr<ID3D11Device>&	device, std::wstring name,com_ptr<ID3D11VertexShader>&	vertex,	com_ptr<ID3D11PixelShader>&		pixel)
	{
		assert(ShaderCompiler2::compile(L"HLSLShader\\square_vertex_shader.hlsl", "VS", "vs_5_0", vertex_blob));
		device->CreateVertexShader(vertex_blob->GetBufferPointer(),
				vertex_blob->GetBufferSize(),
				nullptr,
				vertex.ReleaseAndGetAddressOf());

		assert(ShaderCompiler2::compile(name, "PS", "ps_5_0", pixel_blob));
		device->CreatePixelShader(pixel_blob->GetBufferPointer(),
			pixel_blob->GetBufferSize(),
			nullptr,
			pixel.ReleaseAndGetAddressOf());
		return true;
	}
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

	void map_update(com_ptr<ID3D11Buffer>	&buffer_, const	void*	data, int	num)
	{
		D3D11_MAPPED_SUBRESOURCE	map_resouce = {};
		Device::GetContext()->Map(buffer_.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &map_resouce);
		memcpy(map_resouce.pData, data, num);
		Device::GetContext()->Unmap(buffer_.Get(), 0);
	}

	NodeResult::NodeResult()
	{

	}
	NodeResult::~NodeResult()
	{
	}

	void	NodeResult::Init(std::wstring name)
	{
		std::vector<SquareVertex>	vertices
		{
			{
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
			}
		};
		v_buffer.create<SquareVertex>(vertices,m_vertex_buffer);
		ConstantBufferCreate(Device::GetDevice(),m_constant_buffer, sizeof(CBuffer));
		m_shader_manager.ShaderCreate(Device::GetDevice(), name, m_vertex_shader, m_pixel_shader);
		m_shader_reflection.set_layout(m_shader_manager.vertex_blob);
		InputLayoutCreate(Device::GetDevice(), m_inputlayout, m_shader_reflection.get_layout(), m_shader_manager.vertex_blob);
	}
	void	NodeResult::Render(float time, math::FVector2  d_xy, math::FVector2  d_wh)
	{
		std::valarray<float>	arr_x =
		{
			d_xy.x,				//left-top
			d_xy.x + d_wh.x,	//right-top
			d_xy.x,				//left-bottom
			d_xy.x + d_wh.x,	//right-bottom
		};

		//std::array	arr_y	=
		std::valarray<float>	arr_y =
		{
			d_xy.y,				//left-top
			d_xy.y,				//right-top
			d_xy.y + d_wh.y,	//left-bottom
			d_xy.y + d_wh.y,	//right-bottom
		};

		arr_x = 2.0f	*arr_x / static_cast<float>(Renderer::GetScreenSize().x) - 1.0f;
		arr_y = 1.0f - 2.0f	*arr_y / static_cast<float>(Renderer::GetScreenSize().y);


		std::array<SquareVertex, 4>	v =
		{
			{
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
			}
		};


		I_FOR(4)
		{
			v[i].pos.x = arr_x[i];
			v[i].pos.y = arr_y[i];
			v[i].pos.z = 0.0f;
			v[i].pos.w = 1.0f;
			v[i].color = {0,0,0,0};

		}

		v[0].uv = { 0,0 };
		v[1].uv = { 1,0 };
		v[2].uv = { 0,1 };
		v[3].uv = { 1,1 };
		auto size = sizeof(epion::NodeCustom::SquareVertex) * 4;


		D3D11_MAPPED_SUBRESOURCE	map_resouce = {};
		Device::GetContext()->Map(m_vertex_buffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &map_resouce);
		memcpy(map_resouce.pData, v.data(), size);
		Device::GetContext()->Unmap(m_vertex_buffer.Get(), 0);

		unsigned	int	stride = sizeof(epion::NodeCustom::SquareVertex);
		unsigned	int	offset = 0;

		Device::GetContext()->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride,&offset);
		Device::GetContext()->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		Device::GetContext()->PSSetShader(m_pixel_shader.Get(), nullptr, 0);

		Device::GetContext()->IASetInputLayout(m_inputlayout.Get());
		CBuffer cb = {};
		cb.Time.x = time;
		cb.Time.y = 1;
		cb.Time.z = 1;
		cb.Time.w = 1;

		Device::GetContext()->UpdateSubresource(m_constant_buffer.Get(), 0, nullptr, &cb, 0, 0);
		Device::GetContext()->VSSetConstantBuffers(0, 1, m_constant_buffer.GetAddressOf());
		Device::GetContext()->PSSetConstantBuffers(0, 1, m_constant_buffer.GetAddressOf());

		Renderer::SetState();

		Renderer::set_2d_draw();

	}

}