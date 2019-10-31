#pragma once
#pragma once
namespace	epion
{
	class	ObjMaterialLoader	final
	{
	public:
		ObjMaterialLoader(std::wstring	mtl_name_, std::vector<material>&	material_);
		~ObjMaterialLoader() {};
	};
}