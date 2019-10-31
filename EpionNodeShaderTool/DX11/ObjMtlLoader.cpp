#include	<fstream>
#include	<string>
#include	<vector>
#include	"../epion.h"
#include	"../epion_string.h"
#include	"ObjLoader.h"
#include	"ObjMtlLoader.h"

#undef	min
#undef	max


namespace	epion
{
	ObjMaterialLoader::ObjMaterialLoader(std::wstring	mtl_name_, std::vector<material>&	material_)
	{
		std::wifstream	fin_mtl(mtl_name_);
		std::wstring	command_mtl;

		std::wstring	file_path = StringConverter::get_file_path(mtl_name_);
		while (fin_mtl)
		{
			fin_mtl >> command_mtl;
			if (fin_mtl.eof())
			{
				break;
			}
			if (command_mtl == L"#")//コメント
			{
				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else if (command_mtl == L"map_Kd")
			{
				//fin_mtl.ignore();
				std::wstring	m;
				//wchar_t	map_Kd[256] = {};
				fin_mtl >> m;
				std::wstring	map_str = m;
				//objのファイルパスを付与する
				material_[0].map_Kd.file_name = (file_path + map_str);
				//material_.begin()->map_Kd.file_name = set_file_path(map_Kd, read_mtl_file.c_str());
				//material_[0].map_Kd.file_name = L"data\\obj\\yuppi\\yuppisan.png";

				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else	if (command_mtl == L"newmtl")
			{
				fin_mtl.ignore();
				wchar_t newmtl[256];
				material material;
				fin_mtl >> newmtl;
				material.newmtl = newmtl;
				material_.push_back(material);
			}
			else if (command_mtl == L"Ka")
			{
				float r, g, b;
				fin_mtl >> r >> g >> b;
				material_.rbegin()->Ka = math::FVector3(r, g, b);
				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else if (command_mtl == L"Kd")
			{
				float	r, g, b;
				fin_mtl >> r >> g >> b;
				material_.rbegin()->Kd = math::FVector3(r, g, b);
				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else if (command_mtl == L"Ks")
			{
				float r, g, b;
				fin_mtl >> r >> g >> b;
				material_.rbegin()->Ks = math::FVector3(r, g, b);
				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else if (command_mtl == L"illum")
			{
				unsigned	int	illum;
				fin_mtl >> illum;
				material_.rbegin()->illum = illum;
				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
			else
			{
				fin_mtl.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
			}
		}


		//bumpmap,あとで暇なら殴る
		//else	if(0	==wcscmp(command,	L"map_bump"))
		//{
		//	fin.ignore();
		//	wchar_t	file_map_bump[256];
		//	fin	>> file_map_bump;
		//	combine_resource_path(file_map_bump,	obj_filename,	file_map_bump);
		//	materials.rbegin()->map_bump.file_name	=file_map_bump;
		//	fin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');		//読み捨てる
		//}


	}
}