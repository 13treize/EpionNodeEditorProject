#pragma once
namespace	epion::NodeCustom
{
	class	LerpNode	final :public NodeBase
	{
	public:
		LerpNode();
		LerpNode(int id, const math::FVector2& pos);
		~LerpNode();

		void	Init()override;
		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]),
				cereal::make_nvp("T", Num[2]));
		};

	private:
		math::FVector4	Num[3];
	};

}