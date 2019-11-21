#pragma once
namespace	epion::NodeCustom
{
	struct	SquareVertex	final
	{
		math::Vector4<float>	pos;
		math::Vector2<float>	uv;
		math::Vector4<float>	color;
	};
	struct	CBuffer	final
	{
		math::FVector4 Time;
	};

	class	ShaderCompiler2	final
	{
	public:
		static	bool	compile(const	std::wstring	hlsl_name,
			const	std::string		entry_point,
			const	std::string		target,
			com_ptr<ID3DBlob>&		shader_blob);
	};
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
	class	VertexBuffer	final
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer() = default;

		//vector
		template<class	T>
		bool	Create(std::vector<T>&	buffer, com_ptr<ID3D11Buffer>&	vertex_buffer_ptr);

		void	SetState(unsigned	int	&stride_, unsigned	int	&off_set_);


	private:
		D3D11_BUFFER_DESC		buffer_desc = {};
		D3D11_SUBRESOURCE_DATA	sub_resource_data = {};

	};

	class	ShaderManager final
	{
	public:
		bool ShaderCreate(
			com_ptr<ID3D11Device>&	device,
			std::wstring name,
			com_ptr<ID3D11VertexShader>&	vertex,
			com_ptr<ID3D11PixelShader>&		pixel);

	//private:
		com_ptr<ID3DBlob>	vertex_blob = {};
		com_ptr<ID3DBlob>	pixel_blob = {};

	};
	void	ConstantBufferCreate(com_ptr<ID3D11Device>&	device, com_ptr<ID3D11Buffer>	buffer, UINT size);

	void	InputLayoutCreate(com_ptr<ID3D11Device>&	device, com_ptr<ID3D11InputLayout>	layout_ptr,
		const	std::vector<D3D11_INPUT_ELEMENT_DESC>&	layout, com_ptr<ID3DBlob>&	v_shader_blob);


	void	map_update(com_ptr<ID3D11Buffer>	&buffer_, const	void*	data, int	num);
	class	NodeResult final
	{
	public:
		NodeResult();
		~NodeResult();
		void	Init(std::wstring name);
		void	Render(float time, math::FVector2 d_xy, math::FVector2 d_wh);

	private:
		VertexBuffer v_buffer;
		ShaderManager m_shader_manager;
		ShaderReflection m_shader_reflection;
		com_ptr<ID3D11VertexShader>	m_vertex_shader;
		com_ptr<ID3D11PixelShader>	m_pixel_shader;
		com_ptr<ID3D11InputLayout>	m_inputlayout;

		com_ptr<ID3D11Buffer>	m_vertex_buffer;
		com_ptr<ID3D11Buffer>	m_constant_buffer;
	};

}


template<class	T>
bool	epion::NodeCustom::VertexBuffer::Create(std::vector<T>&	buffer, com_ptr<ID3D11Buffer>&	vertex_buffer_ptr)
{
	HRESULT	hr = S_OK;
	buffer_desc.ByteWidth = sizeof(T)	*static_cast<unsigned int>(buffer.size());
	buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;		//cpuアクセスフラグ
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	sub_resource_data.pSysMem = buffer.data();
	sub_resource_data.SysMemPitch = 0;
	sub_resource_data.SysMemSlicePitch = 0;
	hr = Device::GetDevice()->CreateBuffer(&buffer_desc,
		&sub_resource_data,
		vertex_buffer_ptr.ReleaseAndGetAddressOf());
	return	SUCCEEDED(hr);
}
