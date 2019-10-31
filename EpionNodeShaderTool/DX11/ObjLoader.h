#pragma once
#include	"../epion_math/epion_math.h"
namespace	epion
{
	struct	mtl_texture
	{
		com_ptr<ID3D11ShaderResourceView>	shader_resource_view;
		std::wstring	file_name;
	};

	struct	obj_vertex
	{
		math::Vector4<float>	position;
		math::Vector4<float>	normal;
		math::Vector2<float>	uv;
	};

	struct	subset
	{
		std::wstring	usemtl;
		unsigned	int	index_start;
		unsigned	int	index_count;
	};

	struct	material
	{
		std::wstring			newmtl;
		math::Vector3<float>	Ka;
		math::Vector3<float>	Kd;
		math::Vector3<float>	Ks;

		unsigned	int	illum;
		mtl_texture	map_Kd;
		mtl_texture	map_bump;
	};

	class	ObjLoader	final
	{
	public:
		ObjLoader() {};
		ObjLoader(std::wstring	file_name_);
		~ObjLoader() {};

		void	Init(std::wstring	file_name_, bool	flipping_v_coordinates = true);

		std::vector<material>			materials;
		std::vector<subset>				subsets;
		std::vector<obj_vertex>			vertices;
		std::vector<unsigned	int>	indices;
		std::vector<std::wstring>		mtl_filenames;

	private:
		//std::vector<material>			materials;
		//std::vector<subset>				subsets;
		//std::vector<obj_vertex>			vertices;
		//std::vector<unsigned	int>	indices;
	};
}