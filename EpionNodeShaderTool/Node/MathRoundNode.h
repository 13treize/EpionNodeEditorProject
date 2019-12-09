#pragma once
namespace	epion::Node
{
	class CeilingNode final :public NodeBase
	{
	public:
		CeilingNode();
		CeilingNode(int id, const math::FVector2& pos);
		~CeilingNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_in;
	};


	class StepNode final :public NodeBase
	{
	public:
		StepNode();
		StepNode(int id, const math::FVector2& pos);
		~StepNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_edge),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_edge;
		math::FVector4	m_in;
	};

}