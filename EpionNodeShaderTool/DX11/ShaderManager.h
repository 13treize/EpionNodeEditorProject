#pragma	once
namespace	epion
{
	class	ShaderCompiler	final
	{
	public:
		static	bool	Compile(const	std::wstring	hlsl_name,
			const	std::string		entry_point,
			const	std::string		target,
			com_ptr<ID3DBlob>&		shader_blob);
	};

	class	ShaderBase	abstract
	{
	public:
		virtual	~ShaderBase() {};

		virtual	bool	Create(std::wstring	hlsl_name) = 0;

		com_ptr<ID3DBlob>&	GetBlob()	noexcept;

	protected:
		com_ptr<ID3DBlob>	m_blob;
	};
	class	VertexShader	final : public	ShaderBase
	{
	public:
		VertexShader();
		VertexShader(std::wstring	hlsl_name);
		~VertexShader();

		bool	Create(std::wstring	hlsl_name)	override;
		void	SetState();
		com_ptr<ID3D11VertexShader>&	GetVS()	noexcept;

		void	map_update_begin(com_ptr<ID3D11Buffer>	&buffer_, D3D11_MAPPED_SUBRESOURCE	&resourse_);
		void	map_update_end(com_ptr<ID3D11Buffer>	&buffer_);

	private:
		com_ptr<ID3D11VertexShader>	m_vs;
	};

	class	PixelShader	final : public	ShaderBase
	{
	public:
		PixelShader();
		PixelShader(std::wstring	hlsl_name);
		~PixelShader();

		bool	Create(std::wstring	hlsl_name)	override;
		void	SetState();
		com_ptr<ID3D11PixelShader>&	GetPS()	noexcept;

	private:
		com_ptr<ID3D11PixelShader>	m_ps;
	};
}