#pragma once

#include	<map>

namespace	epion::Shader
{
	class	NodeShaderManager	final
	{
	public:
		NodeShaderManager();
		~NodeShaderManager();

		static	void	Init();

		static	void	progress_generate();

		static	std::string	create();

		static	std::string	CBuffer0SetUp();

		//定数バッファ生成
		static	std::string	CBuffer0Create();

		static	void	node_create();

		static	void	preview_create();

		static	std::string	func_setup();

		static	void	json_import(std::string	path);

		static	void	generate(std::string	file_path);
	private:
		static	std::vector<int>	current_id;
		static	std::vector<int>	get_id;

		static	int		space_count;
		static	int		texture2d_count;
		static	int		sampler_count;

		static	std::string	function_str;

		//use create,1array 1line
		static	std::list<std::string>	create_str;

		static	std::list<std::string>	node_create_str;

		static	std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>	nodes;
		static	std::vector<epion::NodeCustom::NodeLink>	links;

		static	std::vector	<std::string>	variable;

		static	std::map<std::string, int>	shader_function;

		static	std::string	space;

		static	std::string	call_uv();

		static	std::string	event_begin();
		static	std::string	event_end();
		static	std::string	event_end2();
		static	std::string	PSInputGenerate();
		static	std::string	MainFunctionBegin();
		static	std::string	floatGenerate(std::string	var_str, std::string	init_str);

		static	std::string	float4Generate(std::string	var_str, std::string	init_str);
		static	std::string	float4Generate2(std::string	var_str, std::string	init_str);

		static	std::string	ReturnEvent(std::string retuern_color_str);
	};
}