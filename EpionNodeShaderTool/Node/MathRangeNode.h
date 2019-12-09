#pragma once
namespace	epion::Node
{
	class ClampNode final :public NodeBase
	{
	public:
		ClampNode();
		ClampNode(int id, const math::FVector2& pos);
		~ClampNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in),
				cereal::make_nvp("Min", m_min),
				cereal::make_nvp("Max", m_max));
		};

	private:
		math::FVector4	m_in;
		math::FVector4	m_min;
		math::FVector4	m_max;
	};

	class FractionNode final :public NodeBase
	{
	public:
		FractionNode();
		FractionNode(int id, const math::FVector2& pos);
		~FractionNode();

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

	class MaximumNode final :public NodeBase
	{
	public:
		MaximumNode();
		MaximumNode(int id, const math::FVector2& pos);
		~MaximumNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", m_in[0]),
				cereal::make_nvp("B", m_in[1]));
		};

	private:
		math::FVector4	m_in[2];
	};

	class MinimumNode final :public NodeBase
	{
	public:
		MinimumNode();
		MinimumNode(int id, const math::FVector2& pos);
		~MinimumNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", m_in[0]),
				cereal::make_nvp("B", m_in[1]));
		};

	private:
		math::FVector4	m_in[2];
	};

	class OneMinusNode final :public NodeBase
	{
	public:
		OneMinusNode();
		OneMinusNode(int id, const math::FVector2& pos);
		~OneMinusNode();

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

}