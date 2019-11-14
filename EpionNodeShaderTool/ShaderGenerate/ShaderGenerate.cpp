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
		//何かしらで制御
		ofs << CBuffer0SetUp();
		ofs << CBuffer1SetUp();
		ofs << CBuffer2SetUp();
		ofs << CBuffer3SetUp();

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
	std::string	NodeShaderManager::CBuffer1SetUp()
	{
		return
			"cbuffer LightCBuffer : register(b1)\n"
			"{\n"
			"    float4 LightColor;\n"
			"    float4 LightDir;\n"
			"    float4 AmbientColor;\n"
			"};\n";
	}
	std::string	NodeShaderManager::CBuffer2SetUp()
	{
		return
			"cbuffer CameraCBuffer : register(b2)\n"
			"{\n"
			"    float4 Pos;\n"
			"    float4 Target;\n"
			"    float4 Up;\n"
			"};\n";

	}
	std::string	NodeShaderManager::CBuffer3SetUp()
	{
		return
			"cbuffer WorldCBuffer : register(b3)\n"
			"{\n"
			"    row_major float4x4 WorldViewProjection;\n"
			"    row_major float4x4 World;\n"
			"};\n";
	}


	std::string	NodeShaderManager::CBuffer0Create()
	{
		return
			"    float Time_ =Time.x;\n"
			"    float Sin_Time_ =sin(Time.x);\n"
			"    float Cos_Time_ =cos(Time.x);\n";
	}

	void	NodeShaderManager::NodeCreate()
	{
		counts++;
		get_id.clear();
		//linkdaraを走査
		for (auto& li : links)
		{
			for (auto& c_id : current_id)
			{
				//自分のidを見つけたなら
				if (li.GetInputID() == c_id)
				{
					//派生先のidを格納
					get_id.push_back(li.GetOutputID());
				}
			}
		}
		//派生先を生成
		for (auto& ids : get_id)
		{
			create_str.push_front(nodes[ids]->get_function_call_str() + "\n");
		}
		current_id.clear();
		//派生を取得
		current_id = get_id;

		if (!current_id.empty())
		{
			NodeCreate();
		}
		return;
	}

	std::string	NodeShaderManager::create()
	{
		std::string	ret_str;
		//MasterNodeを見つけてそっから辿って生成

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

		NodeCreate();

		for (const auto&c : create_str)
		{
			ret_str += c;
		}

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
			if (typeid(*n) == typeid(NodeCustom::SamplerStateNode) ||
				typeid(*n) == typeid(NodeCustom::Texture2DNode))
			{
				n->ShaderUpdate(nodes,links);
				function_str += n->GetFunctionDefStr() + "\n";
			}
		}

		//function
		for (auto& n : nodes)
		{
			auto it = shader_function.find(n->m_Name);
			if (it != shader_function.end()||
				typeid(*n) == typeid(NodeCustom::SamplerStateNode) ||
				typeid(*n) == typeid(NodeCustom::Texture2DNode))
			{
				continue;
			}
			else
			{
					function_str += n->GetFunctionDefStr() + "\n";
					shader_function.emplace(n->m_Name, 0);
			}
		}
		return	function_str;
	}

	void	NodeShaderManager::json_import(std::string	path)
	{
		epion::FileIO::FileIOJson	json_file;
		json_file.Input(path, nodes, links);
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
		ret_str += space + "float2 uv : TEXCOORD0;\n";
		ret_str += space + "float4 color : COLOR0;\n";
		ret_str += event_end2();
		return	ret_str;
	}

	std::string		NodeShaderManager::MainFunctionBegin()
	{
		std::string	function_name = "float4 PS(PSInput input) : SV_TARGET\n";

		return	function_name;
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