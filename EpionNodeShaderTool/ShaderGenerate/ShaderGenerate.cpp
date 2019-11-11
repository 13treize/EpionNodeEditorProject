#include "../All.h"
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include	"../Node/NodeData.h"
#include	"../Node/MasterNode.h"
#include	"../Node/PBRNode.h"
#include	"../Node/TextureNode.h"

#include	"ShaderGenerate.h"

#include	"../FileIO/Fileio_json.h"

namespace
{
	bool cnt;
	int counts=0;
}

namespace	epion::Shader
{
	std::vector<int>	NodeShaderManager::current_id;
	std::vector<int>	NodeShaderManager::get_id;

	int	NodeShaderManager::space_count;
	int	NodeShaderManager::texture2d_count;

	std::string	NodeShaderManager::function_str;

	std::list<std::string>	NodeShaderManager::create_str;
	std::list<std::string>	NodeShaderManager::node_create_str;

	std::vector<std::unique_ptr<NodeCustom::NodeBase>>	NodeShaderManager::nodes;
	std::vector<NodeCustom::NodeLink>	NodeShaderManager::links;
	std::vector	<std::string>	NodeShaderManager::variable;
	std::map	<std::string, int>	NodeShaderManager::shader_function;

	std::string	NodeShaderManager::space;

	NodeShaderManager::NodeShaderManager()
	{
	}

	NodeShaderManager::~NodeShaderManager()
	{
	}

	void	NodeShaderManager::generate(std::string	file_path)
	{
		shader_function.clear();
		create_str.clear();
		node_create_str.clear();

		shader_function.emplace("FIRST", 0);
		variable.clear();
		std::ofstream	ofs(file_path);
		Init();
		ofs << PSInputGenerate();
		ofs << CBuffer0SetUp();
		ofs << func_setup();
		ofs << MainFunctionBegin();
		ofs << event_begin();
		ofs << CBuffer0Create();
		ofs << create();

		ofs << event_end();
		ofs.close();


	}

	void	NodeShaderManager::Init()
	{
		current_id = {};
		get_id = {};
		cnt = false;

		//node_id.resize(nodes.size());
		space = "";
		space_count = 0;
		texture2d_count = 0;
		create_str.clear();
	}

	std::string	NodeShaderManager::CBuffer0SetUp()
	{
		return
			"cbuffer TimeCBuffer : register(b0)\n"
			"{\n"
			"    float4 Time;\n"
			"    float2 ScreenSize;\n"
			"    float2 Dummy0;\n"
			"};\n";

	}

	std::string	NodeShaderManager::CBuffer0Create()
	{
		return
			"    float Time_ =Time.x;\n"
			"    float Sin_Time_ =sin(Time.x);\n"
			"    float Cos_Time_ =cos(Time.x);\n";
	}

	void	NodeShaderManager::node_create()
	{
		counts++;
		get_id.clear();
		//linkdara‚ð‘–¸
		for (auto& li : links)
		{
			for (auto& c_id : current_id)
			{
				//Ž©•ª‚Ìid‚ðŒ©‚Â‚¯‚½‚È‚ç
				if (li.get_input_id() == c_id)
				{
					//”h¶æ‚Ìid‚ðŠi”[
					get_id.push_back(li.get_output_id());
				}
			}
		}
		//”h¶æ‚ð¶¬
		for (auto& ids : get_id)
		{
			create_str.push_front(nodes[ids]->get_function_call_str() + "\n");
		}
		current_id.clear();
		//”h¶‚ðŽæ“¾
		current_id = get_id;

		if (!current_id.empty())
		{
			node_create();
		}
		return;
	}

	std::string	NodeShaderManager::create()
	{
		std::string	ret_str;
		//MasterNode‚ðŒ©‚Â‚¯‚Ä‚»‚Á‚©‚ç’H‚Á‚Ä¶¬

		for (auto&n : nodes)
		{
			if (typeid(*n) == typeid(NodeCustom::UnlitMasterNode) ||
				typeid(*n) == typeid(NodeCustom::PBRMasterNode))
			{
				create_str.push_back(float4Generate2("flag_color", n->get_function_call_str()));
				current_id.push_back(n->m_ID);
				break;
			}
		}

		node_create();

		for (const auto&c : create_str)
		{
			ret_str += c;
		}
		//return

		ret_str += ReturnEvent("flag_color");
		return	ret_str;
	}

	std::string	NodeShaderManager::func_setup()
	{
		function_str = "";
		//texture
		//for (auto&n : nodes)
		//{
		//	if (typeid(*n) == typeid(NodeCustom::SamplerTexture2DNode))
		//	{
		//		function_str += n->GetFunctionDefStr() + "(t" + std::to_string(texture2d_count) + ");\n";
		//		texture2d_count++;
		//	}
		//}

		//Sampler State
		for (auto&n : nodes)
		{
			if (typeid(*n) == typeid(NodeCustom::SamplerStateNode))
			{
				n->ShaderUpdate(nodes,links);
				function_str += n->GetFunctionDefStr() + "\n";
			}
		}

		//function
		for (auto& n : nodes)
		{
			auto it = shader_function.find(n->m_Name);
			if (it != shader_function.end())
			{
				continue;
			}
			else
			{
				//if (typeid(*n) != typeid(NodeCustom::SamplerTexture2DNode))
				if (typeid(*n) != typeid(NodeCustom::SamplerStateNode))
				{
					function_str += n->GetFunctionDefStr() + "\n";
					shader_function.emplace(n->m_Name, 0);
				}
			}
		}
		return	function_str;
	}

	void	NodeShaderManager::json_import(std::string	path)
	{
		epion::FileIO::FileIOJson	json_file;
		json_file.input(path, nodes, links);
	}


	std::string	NodeShaderManager::call_uv()
	{

		return	"input.uv";
	}

	std::string	NodeShaderManager::event_begin()
	{
		std::string	ret_str = space + "{\n";
		space += "    ";
		space_count++;
		return	ret_str;
	}

	std::string	NodeShaderManager::event_end()
	{
		space = "";
		space_count--;
		for (int i = 0; space_count < i; i++)
		{
			space += "    ";
		}
		std::string	ret_str = space + "}\n";
		return	ret_str;
	}

	std::string	NodeShaderManager::event_end2()
	{
		space = "";
		space_count--;
		for (int i = 0; space_count < i; i++)
		{
			space += "    ";
		}
		std::string	ret_str = "};\n";
		return	ret_str;
	}

	std::string	NodeShaderManager::PSInputGenerate()
	{
		std::string	ret_str;
		ret_str = "struct PSInput\n";
		ret_str += event_begin();
		ret_str += space + "float4 position : SV_POSITION;\n";
		ret_str += space + "float2 uv : UV0;\n";
		ret_str += space + "float4 color : COLOR0;\n";
		ret_str += event_end2();
		return	ret_str;
	}

	std::string		NodeShaderManager::MainFunctionBegin()
	{
		std::string	function_name = "float4 PS(PSInput input) : SV_TARGET\n";

		return	function_name;
	}

	std::string	NodeShaderManager::floatGenerate(std::string	var_str, std::string	init_str)
	{
		std::string	ret_str = space + "float " + var_str + init_str + ";\n";
		return	ret_str;
	}

	std::string	NodeShaderManager::float4Generate(std::string	var_str, std::string	init_str)
	{
		std::string	ret_str = space + "float4 " + var_str + init_str + ";\n";
		return	ret_str;
	}
	std::string	NodeShaderManager::float4Generate2(std::string	var_str, std::string	init_str)
	{
		std::string	ret_str = space + "float4 " + var_str + init_str;
		return	ret_str;
	}

	std::string	NodeShaderManager::ReturnEvent(std::string retuern_color_str)
	{
		std::string	ret_str = space + "return " + retuern_color_str + ";\n";
		return	ret_str;
	}

}