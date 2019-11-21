#pragma once
namespace	epion
{
	class	Sampler	final
	{
	public:
		Sampler();
		~Sampler();
		bool	Create();
		void	SetState();

	private:
		D3D11_SAMPLER_DESC	sampler_desc;
		com_ptr<ID3D11SamplerState>	sampler_ptr;
	};

	class	DepthStencil	final
	{
	public:
		DepthStencil();
		~DepthStencil();

		bool	Create();

		void	SetState();

	private:
		D3D11_DEPTH_STENCIL_DESC	d_desc;
		com_ptr<ID3D11DepthStencilState>	depth_stencil_ptr;
	};

}