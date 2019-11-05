#pragma once

/**
 * @file NoiseNode.h
 * @brief NoiseÇÃÉmÅ[Éh
 * @author treize
 * @date 2019/10/25
 */

 /**
 * @namespace NodeCustom
 * @brief NodeÇÇ‹Ç∆ÇﬂÇƒÇÈ
 * @details
 */
namespace	epion::NodeCustom
{
	/**
	* @brief FBM(Fractal Brownian Motion)	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Amplitude(float)
	* @details	InputSlot 2 Frequency(float)
	*/

	class	FBMNode :public	NodeBase
	{
	public:
		FBMNode();
		FBMNode(int id, const math::FVector2& pos);
		~FBMNode();
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
				CEREAL_NVP(m_amplitude),
				CEREAL_NVP(m_frequency));
		};

	private:
		math::FVector2	m_uv;
		float m_amplitude;
		float m_frequency;
	};

	/**
	* @brief GradientNoise	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Scale(float)
	*/

	class	GradientNoiseNode :public	NodeBase
	{
	public:
		GradientNoiseNode();
		GradientNoiseNode(int id, const math::FVector2& pos);
		~GradientNoiseNode();
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
				CEREAL_NVP(m_scale));
		};

	private:
		math::FVector2	m_uv;
		float m_scale;
	};

	/**
	* @brief SimpleNoise	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 Scale(float)
	*/
	class	SimpleNoiseNode final :public	NodeBase
	{
	public:
		SimpleNoiseNode();
		SimpleNoiseNode(int id, const math::FVector2& pos);
		~SimpleNoiseNode();

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
				CEREAL_NVP(m_scale));
		};

	private:
		math::FVector2	m_uv;
		float m_scale;
	};
	/**
	* @brief Voronoi	class
	* @details	InputSlot 0 UV(VECTOR2)
	* @details	InputSlot 1 AngleOffset(float)
	* @details	InputSlot 2 CellDensity(float)
	*/

	class	VoronoiNode final :public	NodeBase
	{
	public:
		VoronoiNode();
		VoronoiNode(int id, const math::FVector2& pos);
		~VoronoiNode();

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
				CEREAL_NVP(m_angleoffset),
				CEREAL_NVP(m_celldensity));
		};

	private:
		math::FVector2	m_uv;
		float m_angleoffset;
		float m_celldensity;
	};
}
