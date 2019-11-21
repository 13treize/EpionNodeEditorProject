#include	"../All.h"
#include	"../epion.h"


#include	"ObjMesh.h"

#include	"dx11_device.h"

namespace	epion
{
	ObjMesh::ObjMesh(const std::wstring&	obj_filename_, com_ptr<ID3DBlob>& blob)
	{
		obj_data = std::make_unique<ObjLoader>(obj_filename_);
		obj_mtl_data = std::make_unique<ObjMaterialLoader>(obj_data->mtl_filenames[0], obj_data->materials);
		//for (auto& material : obj_data->materials)
		//{
		//	if (!material.map_Kd.file_name.empty())
		//	{
		//		Texture	map_Kd_texture(material.map_Kd.file_name);
		//		map_Kd_texture.load_file(material.map_Kd.shader_resource_view);
		//	}
		//}

		shader_refrection.set_layout(blob);

		input_layout.Create(shader_refrection.get_layout(), blob);

		depth_stencil.Create();
		assert(vertex_buffer.Create<epion::obj_vertex>(obj_data->vertices));
		assert(index_buffer.Create(obj_data->indices));
		assert(constant_buffer.Create<constant_buffer_3d>());
	}

	void	ObjMesh::Render(const	DirectX::XMFLOAT4X4	&world_view_projection,
		const	DirectX::XMFLOAT4X4	&world)
	{
		unsigned	int	stride = sizeof(obj_vertex);
		unsigned	int	offset = 0;

		vertex_buffer.SetState(stride, offset);
		index_buffer.SetState(DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
		Renderer::set_state_list();
		input_layout.SetState();
		depth_stencil.SetState();
		for (auto& material : obj_data->materials)
		{
			D3D11_MAPPED_SUBRESOURCE	mapped_buffer = {};

			Device::GetContext()->Map(constant_buffer.get_buffer_ptr().Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

			constant_buffer_3d	*data = static_cast<constant_buffer_3d*>(mapped_buffer.pData);
			DirectX::XMStoreFloat4x4(&data->world_view_projection, DirectX::XMLoadFloat4x4(&coordinate_conversion)	*DirectX::XMLoadFloat4x4(&world_view_projection));
			DirectX::XMStoreFloat4x4(&data->world, DirectX::XMLoadFloat4x4(&coordinate_conversion)	*DirectX::XMLoadFloat4x4(&world));

			Device::GetContext()->Unmap(constant_buffer.get_buffer_ptr().Get(), 0);

			constant_buffer.SetState(3);

			for (subset &subset : obj_data->subsets)
			{
				if (material.newmtl == subset.usemtl)
				{
					Renderer::set_drawindexed(subset.index_count, subset.index_start);
				}
			}
		}
	}
}