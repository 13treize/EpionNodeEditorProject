#include	<memory>
#include	<string>
#include	"../epion.h"


#include	"ObjMesh.h"

#include	"dx11_device.h"

namespace	epion
{
	ObjMesh::ObjMesh(std::wstring	obj_filename_)
	{
		obj_data = std::make_unique<ObjLoader>(obj_filename_);
		//obj_mtl_data = std::make_unique<ObjMaterialLoader>(obj_data->mtl_filenames[0], obj_data->materials);
		//for (auto& material : obj_data->materials)
		//{
		//	if (!material.map_Kd.file_name.empty())
		//	{
		//		Texture	map_Kd_texture(material.map_Kd.file_name);
		//		map_Kd_texture.load_file(material.map_Kd.shader_resource_view);
		//	}
		//}

		vertex_shader.Create(L"HLSLShader\\ObjVertexShader.hlsl");
		pixel_shader.Create(L"HLSLShader\\ObjNoTexturePixelShader.hlsl");

		shader_refrection.set_layout(vertex_shader.GetBlob());

		input_layout.create(shader_refrection.get_layout(), vertex_shader.GetBlob());

		depth_stencil.create();
		assert(sampler.create());
		assert(vertex_buffer.create<epion::obj_vertex>(obj_data->vertices));
		assert(index_buffer.create(obj_data->indices));
		assert(constant_buffer.create<constant_buffer_3d>());
	}

	void	ObjMesh::render(const	DirectX::XMFLOAT4X4	&world_view_projection,
		const	DirectX::XMFLOAT4X4	&world,
		const	math::FVector4		&light_direction,
		const	Color				&material_color)
	{
		unsigned	int	stride = sizeof(obj_vertex);
		unsigned	int	offset = 0;

		vertex_buffer.set_state(stride, offset);
		index_buffer.set_state(DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
		Renderer::set_state_list();
		input_layout.set_state();
		vertex_shader.SetState();
		pixel_shader.SetState();
		depth_stencil.set_state();
		for (auto& material : obj_data->materials)
		{
			D3D11_MAPPED_SUBRESOURCE	mapped_buffer = {};

			Device::GetContext()->Map(constant_buffer.get_buffer_ptr().Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

			constant_buffer_3d	*data = static_cast<constant_buffer_3d*>(mapped_buffer.pData);
			data->light_direction = light_direction;
			data->material_color = material_color;
			DirectX::XMStoreFloat4x4(&data->world_view_projection, DirectX::XMLoadFloat4x4(&coordinate_conversion)	*DirectX::XMLoadFloat4x4(&world_view_projection));
			DirectX::XMStoreFloat4x4(&data->world, DirectX::XMLoadFloat4x4(&coordinate_conversion)	*DirectX::XMLoadFloat4x4(&world));

			Device::GetContext()->Unmap(constant_buffer.get_buffer_ptr().Get(), 0);

			constant_buffer.set_state();
			Device::GetContext()->PSSetShaderResources(0, 1, material.map_Kd.shader_resource_view.GetAddressOf());
			sampler.set_state();

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