#pragma once

namespace	epion
{
	class	ColorPicker2;
}

/**
 * @file ProceduralNode.h
 * @brief ê}å`
 * @author treize
 * @date 2019/11/1
 */

namespace	epion::Node
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
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
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
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_width),
				CEREAL_NVP(m_height));
		};
	private:
		math::FVector2	m_uv;
		float	m_width;
		float	m_height;
	};

	/**
	* @brief Hexagon	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Scale(float)
	*/

	class	HexagonNode	final :public NodeBase
	{
	public:
		HexagonNode();
		HexagonNode(int id, const math::FVector2& pos);
		~HexagonNode();

		void	Init()override;
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_scale));
		};

	private:
		math::FVector2	m_uv;
		float	m_scale;
	};

	/**
	* @brief Polygon	class ëΩäpå`
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Sides(float)
	* @details	InputSlot 2 Width(float)
	* @details	InputSlot 3 Height(float)
	*/

	class	PolygonNode	final :public NodeBase
	{
	public:
		PolygonNode();
		PolygonNode(int id, const math::FVector2& pos);
		~PolygonNode();

		void	Init()override;
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_sides),
				CEREAL_NVP(m_width),
				CEREAL_NVP(m_height));
		};

	private:
		math::FVector2	m_uv;
		float	m_sides;
		float	m_width;
		float	m_height;
	};

	/**
	* @brief Ripple	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Width(float)
	* @details	InputSlot 2 Height(float)
	* @details	InputSlot 3 Center(VECTOR2)
	* @details	InputSlot 4 Scale(float)
	*/

	class	RippleNode	final :public NodeBase
	{
	public:
		RippleNode();
		RippleNode(int id, const math::FVector2& pos);
		~RippleNode();

		void	Init()override;
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_width),
				CEREAL_NVP(m_height),
				CEREAL_NVP(m_center),
				CEREAL_NVP(m_scale));
		};

	private:
		math::FVector2	m_uv;
		float	m_width;
		float	m_height;
		math::FVector2	m_center;
		float m_scale;
	};

	/**
	* @brief RoundedRectangle	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Width(float)
	* @details	InputSlot 2 Height(float)
	* @details	InputSlot 3 Radius(float)
	*/

	class	RoundedRectangleNode	final :public NodeBase
	{
	public:
		RoundedRectangleNode();
		RoundedRectangleNode(int id, const math::FVector2& pos);
		~RoundedRectangleNode();

		void	Init()override;
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_uv),
				CEREAL_NVP(m_width),
				CEREAL_NVP(m_height),
				CEREAL_NVP(m_radius));
		};

	private:
		math::FVector2	m_uv;
		float	m_width;
		float	m_height;
		float	m_radius;
	};
}