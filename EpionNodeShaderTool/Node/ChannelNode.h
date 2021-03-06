#pragma once

namespace	epion::Node
{
	class	CombineNode	final	:public	NodeBase
	{
	public:
		CombineNode();
		CombineNode(int id, const math::FVector2& pos);
		~CombineNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(R),
				CEREAL_NVP(G),
				CEREAL_NVP(B),
				CEREAL_NVP(A));
		};

	private:
		float	R;
		float	G;
		float	B;
		float	A;
	};
}