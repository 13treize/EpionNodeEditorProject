#include	"../All.h"
#include	"../epion.h"
#include	"../color.h"
#include	"buffer.h"
#include	"dx11_device.h"

namespace
{
}

namespace	epion
{
	void	IndexBuffer::SetState(DXGI_FORMAT	format_)
	{
		Device::GetContext()->IASetIndexBuffer(buffer_ptr.Get(), format_, 0);
	}

	com_ptr<ID3D11Buffer>&	IndexBuffer::get_buffer_ptr()
	{
		return	buffer_ptr;
	}

	void	IndexBuffer::create_desc(const	unsigned	int	buffer_size)
	{
		buffer_desc.ByteWidth = buffer_size;
		buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
		buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;		//cpuアクセスフラグ
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;
	}

	void	IndexBuffer::create_sub_data(const	std::vector<unsigned	int>&	buffer)
	{
		sub_resource_data.pSysMem = buffer.data();
		sub_resource_data.SysMemPitch = 0;
		sub_resource_data.SysMemSlicePitch = 0;
	}

	bool	IndexBuffer::create(const	std::vector<unsigned	int>&	buffer)
	{
		HRESULT	hr = S_OK;
		create_desc(sizeof(unsigned	int)	*static_cast<unsigned	int>(buffer.size()));
		create_sub_data(buffer);
		hr =Device::GetDevice()->CreateBuffer(&buffer_desc,
			&sub_resource_data,
			buffer_ptr.ReleaseAndGetAddressOf());
		return	SUCCEEDED(hr);
	}

	void	ConstantBuffer::SetState(int slot)
	{
		Device::GetContext()->VSSetConstantBuffers(slot, 1, constant_buffer_ptr.GetAddressOf());
		Device::GetContext()->PSSetConstantBuffers(slot, 1, constant_buffer_ptr.GetAddressOf());
	}

	com_ptr<ID3D11Buffer>&	ConstantBuffer::get_buffer_ptr()
	{
		return	constant_buffer_ptr;
	}

	void	ConstantBuffer::create_desc(const	size_t	buffer_size)
	{
		buffer_desc.ByteWidth = static_cast<UINT>(buffer_size);
		buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;		//cpuアクセスフラグ
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;
	}

	com_ptr<ID3D11Buffer>&	VertexBuffer::get_buffer_ptr()
	{
		return vertex_buffer_ptr;
	}

	void	VertexBuffer::create_desc(const	unsigned	int	buffer_size)
	{
		buffer_desc.ByteWidth = buffer_size;
		buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;		//cpuアクセスフラグ
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;
	}

	void	VertexBuffer::SetState(unsigned	int	&stride_, unsigned	int	&off_set_)
	{
		Device::GetContext()->IASetVertexBuffers(0, 1, vertex_buffer_ptr.GetAddressOf(), &stride_, &off_set_);
	}

}