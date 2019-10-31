#pragma once
/**
 * @file MathBasicNode.h
 * @brief Šî–{“I‚ÈŒvŽZ
 * @author treize
 * @date 2019/10/25
 */

namespace	epion::NodeCustom
{
	/**
	* @brief Add	class
	* @details ‘«‚µŽZ
	*/

	class	AddNode final :public NodeBase
	{
	public:
		AddNode();
		AddNode(int id, const math::FVector2& pos);
		~AddNode();

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

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

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

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

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

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

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

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

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

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

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

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