#pragma once
namespace	epion::Node
{
	class	Yuppi2DNode :public	NodeBase
	{
	public:
		Yuppi2DNode();
		Yuppi2DNode(int id, const math::FVector2& pos);
		~Yuppi2DNode();

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
				CEREAL_NVP(m_color));
		};

	private:
		math::FVector2	m_uv;
		math::FVector3	m_color;

	};
}