#pragma once

namespace	epion::Shader
{
	/*
		生成管理
		中間形式(Json)から、HLSLを生成

		生成手順
		PSInput →cbuffer →Nodeの関数 →main
	*/

	class	NodeShaderManager	final
	{
	public:
		NodeShaderManager();
		~NodeShaderManager();

		static	void	Init();

		static	void	progress_generate();

		static	std::string	Create();

		static	std::string	CBuffer0SetUp();
		static	std::string	CBuffer1SetUp();
		static	std::string	CBuffer2SetUp();
		static	std::string	CBuffer3SetUp();

		//定数バッファ生成
		static	std::string	CBuffer0Create();

		static	void	NodeCreate();

		static	void	preview_create();

		static	std::string	FuncSetup();

		static	void	JsonImport(const std::string&	path);

		static	void	Generate(const std::string& file_path);
	private:
		static	std::vector<int>	current_id;
		static	std::vector<int>	get_id;

		static	int		m_space_count;
		static	int		texture2d_count;
		static	int		sampler_count;

		static	std::string	function_str;

		//use Create,1array 1line
		static	std::list<std::string>	create_str;

		static	std::list<std::string>	node_create_str;

		static	std::vector<std::unique_ptr<epion::Node::NodeBase>>	nodes;
		static	std::vector<epion::Node::NodeLink>	links;

		static	std::vector	<std::string>	variable;

		static	std::map<std::string, int>	shader_function;

		static	std::string	m_space;

		static	std::string	CallUV();

		static	std::string	EventBegin();
		static	std::string	EventEnd();
		static	std::string	event_end2();
		static	std::string	PSInputGenerate();
		static	std::string	MainFunctionBegin();

		static	std::string	float4Generate2(std::string	var_str, std::string	init_str);

		static	std::string	ReturnEvent(std::string retuern_color_str);
	};
}