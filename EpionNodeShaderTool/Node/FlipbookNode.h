#pragma once

namespace	epion::NodeCustom
{
	class FlipbookNode	final :public	NodeBase
	{
	public:
		FlipbookNode();
		FlipbookNode(int id, const math::FVector2& pos);
		~FlipbookNode();

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
				CEREAL_NVP(UV),
				CEREAL_NVP(Width),
				CEREAL_NVP(Height),
				CEREAL_NVP(Tile),
				CEREAL_NVP(Invert));
		};

	private:
		math::FVector2	UV;
		float	Width;
		float	Height;
		float	Tile;
		math::FVector2	Invert;

	};
}