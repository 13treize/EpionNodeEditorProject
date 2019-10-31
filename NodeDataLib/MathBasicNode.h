#pragma once
namespace	epion::NodeCustom
{
	class	AddNode final :public NodeBase
	{
	public:
		AddNode();
		AddNode(int id, const math::FVector2& pos);
		~AddNode();

		void	init()override;

		void	input_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	output_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	get_function_def_str()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};

	class	SubtractNode final :public NodeBase
	{
	public:
		SubtractNode();
		SubtractNode(int id, const math::FVector2& pos);
		~SubtractNode();

		void	init()override;

		void	input_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	output_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	get_function_def_str()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};

	class	MultiplyNode final :public NodeBase
	{
	public:
		MultiplyNode();
		MultiplyNode(int id, const math::FVector2& pos);
		~MultiplyNode();

		void	init()override;

		void	input_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	output_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	get_function_def_str()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};

	class	DivideNode final :public NodeBase
	{
	public:
		DivideNode();
		DivideNode(int id, const math::FVector2& pos);
		~DivideNode();

		void	init()override;

		void	input_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	output_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	get_function_def_str()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};

	class	PowerNode	final :public NodeBase
	{
	public:
		PowerNode();
		PowerNode(int id, const math::FVector2& pos);
		~PowerNode();

		void	init()override;

		void	input_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	output_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	get_function_def_str()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};

	class	SquareRootNode	final :public NodeBase
	{
	public:
		SquareRootNode();
		SquareRootNode(int id, const math::FVector2& pos);
		~SquareRootNode();

		void	init()override;

		void	input_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	output_update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	get_function_def_str()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", In));
		};

	private:
		math::FVector4	In;
	};

}