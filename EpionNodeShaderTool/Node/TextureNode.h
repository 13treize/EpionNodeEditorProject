#pragma once
namespace	epion::NodeCustom
{
	class	Texture2DNode final :public	NodeBase
	{
	public:
		Texture2DNode();
		Texture2DNode(int id, const math::FVector2& pos);
		~Texture2DNode();

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this));
		};

	private:
		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;


	};
}
