#pragma once

namespace	epion
{
	class	ColorPicker2;
}

/**
 * @file ProceduralNode.h
 * @brief �}�`
 * @author treize
 * @date 2019/11/1
 */

namespace	epion::NodeCustom
{
	/**
	* @brief Checkerboard	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 ColorA(COLOR)
	* @details	InputSlot 2 ColorB(COLOR)
	* @details	InputSlot 3 Frequency(VECTOR2)
	*/

	class	CheckerboardNode	final :public	NodeBase
	{
	public:
		CheckerboardNode();
		CheckerboardNode(int id, const  math::FVector2& pos);
		~CheckerboardNode();
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
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_colora),
				CEREAL_NVP(m_colorb),
				CEREAL_NVP(m_frequency));
		};
	private:
		//	input
		math::FVector2	m_uv;
		math::FVector3	m_colora;
		math::FVector3	m_colorb;
		math::FVector2	m_frequency;
	};

	/**
	* @brief Ellipse	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 ColorA(COLOR)
	* @details	InputSlot 2 ColorB(COLOR)
	* @details	InputSlot 3 Frequency(VECTOR2)
	*/

	class	EllipseNode	final:public NodeBase
	{
	public:
		EllipseNode();
		EllipseNode(int id, const math::FVector2& pos);
		~EllipseNode();

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
				CEREAL_NVP(Height));
		};

	private:
		math::FVector2	UV;
		float	Width;
		float	Height;
	};

	class	PolygonNode	final :public NodeBase
	{
	public:
		PolygonNode();
		PolygonNode(int id, const math::FVector2& pos);
		~PolygonNode();

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
				CEREAL_NVP(Sides),
				CEREAL_NVP(Width),
				CEREAL_NVP(Height));
		};

	private:
		math::FVector2	UV;
		float	Sides;
		float	Width;
		float	Height;
	};

	class	RoundedRectangleNode	final :public NodeBase
	{
	public:
		RoundedRectangleNode();
		RoundedRectangleNode(int id, const math::FVector2& pos);
		~RoundedRectangleNode();

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
				CEREAL_NVP(Radius));
		};

	private:
		math::FVector2	UV;
		float	Width;
		float	Height;
		float	Radius;
	};
}