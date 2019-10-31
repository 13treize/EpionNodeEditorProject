#pragma once
namespace	epion::NodeCustom
{
	class	DDXNode	final :public NodeBase
	{
	public:
		DDXNode();
		DDXNode(int id, const math::FVector2& pos);
		~DDXNode();

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

	class	DDYNode	final :public NodeBase
	{
	public:
		DDYNode();
		DDYNode(int id, const math::FVector2& pos);
		~DDYNode();

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

	class	DDXYNode	final :public NodeBase
	{
	public:
		DDXYNode();
		DDXYNode(int id, const math::FVector2& pos);
		~DDXYNode();

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