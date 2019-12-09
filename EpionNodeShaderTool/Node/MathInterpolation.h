#pragma once
namespace	epion::Node
{
	class	LerpNode	final :public NodeBase
	{
	public:
		LerpNode();
		LerpNode(int id, const math::FVector2& pos);
		~LerpNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", m_num[0]),
				cereal::make_nvp("B", m_num[1]),
				cereal::make_nvp("T", m_num[2]));
		};

	private:
		math::FVector4	m_num[3];
	};

}