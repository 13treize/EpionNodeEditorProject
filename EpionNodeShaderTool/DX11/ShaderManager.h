#pragma	once
namespace	epion
{
	class	ShaderCompiler	final
	{
	public:
		static	bool	Compile(const std::wstring&	hlsl_name,
			const std::string&		entry_point,
			const std::string&		target,
			com_ptr<ID3DBlob>&		shader_blob);
	};

	class	ShaderBase	abstract
	{
	public:
		virtual	~ShaderBase() {};

		virtual	bool	Create(const std::wstring&	hlsl_name) = 0;

		com_ptr<ID3DBlob>&	GetBlob()	noexcept;

	protected:
		com_ptr<ID3DBlob>	m_blob;
	};
	class	VertexShader	final : public	ShaderBase
	{
	public:
		VertexShader();
		VertexShader(const std::wstring&	hlsl_name);
		~VertexShader();

		bool	Create(const std::wstring&	hlsl_name)	override;
		void	SetState();
		com_ptr<ID3D11VertexShader>&	GetVS()	noexcept;


	private:
		com_ptr<ID3D11VertexShader>	m_vs;
	};

	class	PixelShader	final : public	ShaderBase
	{
	public:
		PixelShader();
		PixelShader(const std::wstring&	hlsl_name);
		~PixelShader();

		bool	Create(const std::wstring&	hlsl_name)	override;
		void	SetState();
		com_ptr<ID3D11PixelShader>&	GetPS()	noexcept;

	private:
		com_ptr<ID3D11PixelShader>	m_ps;
	};
}