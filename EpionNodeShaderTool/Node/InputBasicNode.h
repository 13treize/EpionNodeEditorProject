#pragma once

/*
	Node Input -Basic
	float
	vector2
	vector3
	vector4
	color
	time
*/

namespace	epion::NodeCustom
{
	class	FloatNode final :public	NodeBase
	{
	public:
		FloatNode();
		FloatNode(int id, const math::FVector2& pos);
		~FloatNode();
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
				CEREAL_NVP(m_num));
		};
	private:
		float	m_num;
	};

	class	Vector2Node final :public	NodeBase
	{
	public:
		Vector2Node();
		Vector2Node(int id, const math::FVector2& pos);
		~Vector2Node();
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
				CEREAL_NVP(m_num));
		};
	private:
		math::FVector2	m_num;
	};

	class	Vector3Node final :public	NodeBase
	{
	public:
		Vector3Node();
		Vector3Node(int id, const math::FVector2& pos);
		~Vector3Node();
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
				CEREAL_NVP(m_num));
		};
	private:
	math::FVector3	m_num;
	};

	class	Vector4Node final :public	NodeBase
	{
	public:
		Vector4Node();
		Vector4Node(int id, const math::FVector2& pos);
		~Vector4Node();
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
				CEREAL_NVP(m_num));
		};
	private:
		math::FVector4	m_num;
	};
	class	ColorNode final :public	NodeBase
	{
	public:
		ColorNode();
		ColorNode(int id, const math::FVector2& pos);
		~ColorNode();
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
				CEREAL_NVP(m_color));
		};
	private:
		math::FVector3	m_color;
	};

	/*
		íËã`Ç…ä÷ÇÌÇÁÇ∏Mainì‡Ç≈ç≈èâÇ…ê∂ê¨Ç≥ÇÍÇÈ
	*/
	class	TimeNode final :public	NodeBase
	{
	public:
		TimeNode();
		TimeNode(int id, const math::FVector2& pos);
		~TimeNode();
		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this));
		};
	private:
	};

}
