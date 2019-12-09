#pragma once

namespace	epion::Node
{
	class FlipbookNode	final :public	NodeBase
	{
	public:
		FlipbookNode();
		FlipbookNode(int id, const math::FVector2& pos);
		~FlipbookNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_width),
				CEREAL_NVP(m_height),
				CEREAL_NVP(Tile),
				CEREAL_NVP(Invert));
		};

	private:
		math::FVector2	m_uv;
		float	m_width;
		float	m_height;
		float	Tile;
		math::FVector2	Invert;

	};
}