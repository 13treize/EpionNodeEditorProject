#pragma once
#include	"../Color.h"
#include	"dx11_device.h"
namespace	epion
{
	class	IndexBuffer	final
	{
	public:
		IndexBuffer() {};
		~IndexBuffer() {};

		bool	create(const	std::vector<unsigned int>&	buffer);

		void	SetState(DXGI_FORMAT	format_ = DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
		com_ptr<ID3D11Buffer>&	get_buffer_ptr();


	private:
		void	create_desc(const	unsigned	int	buffer_size);

		D3D11_BUFFER_DESC		buffer_desc;
		D3D11_SUBRESOURCE_DATA	sub_resource_data;
		com_ptr<ID3D11Buffer>	buffer_ptr;

		//vector
		void	create_sub_data(const	std::vector<unsigned int>&	buffer);

	};

	class	ConstantBuffer	final
	{
	public:
		ConstantBuffer() = default;
		~ConstantBuffer() = default;

		//vector
		template<class	T>
		bool	create();

		void	SetState(int slot);

		com_ptr<ID3D11Buffer>&	get_buffer_ptr();

	private:
		void	create_desc(const	size_t	buffer_size);

		D3D11_BUFFER_DESC		buffer_desc = {};
		com_ptr<ID3D11Buffer>	constant_buffer_ptr;

	};

	template<class	T>
	bool	ConstantBuffer::create()
	{
		HRESULT	hr = S_OK;
		create_desc(sizeof(T));
		hr =Device::GetDevice()->CreateBuffer(&buffer_desc,
			nullptr,
			constant_buffer_ptr.ReleaseAndGetAddressOf());
		return	SUCCEEDED(hr);
	}

	struct	constant_buffer_3d
	{
		DirectX::XMFLOAT4X4	world_view_projection;
		DirectX::XMFLOAT4X4	world;
	};

	class	VertexBuffer	final
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer() = default;

		//vector
		template<class	T>
		bool	create(std::vector<T>&	buffer);

		void	SetState(unsigned	int	&stride_, unsigned	int	&off_set_);

		com_ptr<ID3D11Buffer>&	get_buffer_ptr();

	private:
		void	create_desc(const	unsigned	int	buffer_size);

		D3D11_BUFFER_DESC		buffer_desc = {};
		D3D11_SUBRESOURCE_DATA	sub_resource_data = {};
		com_ptr<ID3D11Buffer>	vertex_buffer_ptr;

		//vector
		template<class	T>
		void	create_sub_data(const	std::vector<T>&	buffer);

	};

}
template<class	T>
void	epion::VertexBuffer::create_sub_data(const	std::vector<T>&	buffer)
{
	sub_resource_data.pSysMem = buffer.data();
	sub_resource_data.SysMemPitch = 0;
	sub_resource_data.SysMemSlicePitch = 0;
}

template<class	T>
bool	epion::VertexBuffer::create(std::vector<T>&	buffer)
{
	HRESULT	hr = S_OK;
	create_desc(sizeof(T)	*static_cast<unsigned int>(buffer.size()));
	create_sub_data<T>(buffer);
	hr	=Device::GetDevice()->CreateBuffer(&buffer_desc,
		&sub_resource_data,
		vertex_buffer_ptr.ReleaseAndGetAddressOf());
	return	SUCCEEDED(hr);
}
