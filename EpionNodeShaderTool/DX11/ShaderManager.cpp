#include	<string>
#include	"../epion.h"
#include	"ShaderManager.h"
#include	"dx11_device.h"

namespace
{
}


namespace	epion
{
	bool	ShaderCompiler::Compile(const	std::wstring	hlsl_name, const	std::string		entry_point, const	std::string		target, com_ptr<ID3DBlob>&		shader_blob)
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
	com_ptr<ID3DBlob>&	ShaderBase::GetBlob()	noexcept
	{
		return m_blob;
	}

	VertexShader::VertexShader()
	{

	}
	VertexShader::VertexShader(std::wstring	hlsl_name)
	{
		Create(hlsl_name);
	}

	VertexShader::~VertexShader()
	{
	}

	bool	VertexShader::Create(std::wstring	hlsl_name)
	{
		if (ShaderCompiler::Compile(hlsl_name, "VS", "vs_5_0", m_blob))
		{
			Device::GetDevice()->CreateVertexShader(m_blob->GetBufferPointer(),
				m_blob->GetBufferSize(),
				nullptr,
				m_vs.ReleaseAndGetAddressOf());
		}
		else
		{
			return	false;
		}
		return	true;
	}

	void	VertexShader::SetState()
	{
		Device::GetContext()->VSSetShader(m_vs.Get(), nullptr, 0);
	}

	com_ptr<ID3D11VertexShader>&	VertexShader::GetVS() noexcept
	{
		return m_vs;
	}

	PixelShader::PixelShader()
	{

	}
	PixelShader::PixelShader(std::wstring	hlsl_name)
	{
		Create(hlsl_name);
	}

	PixelShader::~PixelShader()
	{
	}

	bool	PixelShader::Create(std::wstring	hlsl_name)
	{
		if (ShaderCompiler::Compile(hlsl_name, "PS", "ps_5_0", m_blob))
		{
			Device::GetDevice()->CreatePixelShader(
				m_blob->GetBufferPointer(),
				m_blob->GetBufferSize(),
				nullptr,
				m_ps.ReleaseAndGetAddressOf());
		}
		else
		{
			return	false;
		}
		return	true;
	}

	void	PixelShader::SetState()
	{
		Device::GetContext()->PSSetShader(m_ps.Get(), nullptr, 0);
	}

	com_ptr<ID3D11PixelShader>&	PixelShader::GetPS() noexcept
	{
		return m_ps;
	}

}
