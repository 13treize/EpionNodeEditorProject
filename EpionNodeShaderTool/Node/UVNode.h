#pragma once

namespace	epion::Node
{
	class PolarCoordinatesNode	final :public	NodeBase
	{
	public:
		PolarCoordinatesNode();
		PolarCoordinatesNode(int id, const math::FVector2& pos);
		~PolarCoordinatesNode();

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
				CEREAL_NVP(m_center),
				CEREAL_NVP(m_radialscale),
				CEREAL_NVP(m_lengthscale));
		};


	private:
		//	input
		math::FVector2	m_uv;
		math::FVector2	m_center;
		float m_radialscale;
		float m_lengthscale;
	};
	class RadialShearNode final :public	NodeBase
	{
	public:
		RadialShearNode();
		RadialShearNode(int id, const math::FVector2& pos);
		~RadialShearNode();

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
				CEREAL_NVP(m_center),
				CEREAL_NVP(m_strength),
				CEREAL_NVP(m_offset));
		};
	private:
		math::FVector2	m_uv;
		math::FVector2	m_center;
		math::FVector2	m_strength;
		math::FVector2	m_offset;
	};


	class SpherizeNode	final :public	NodeBase
	{
	public:
		SpherizeNode();
		SpherizeNode(int id, const math::FVector2& pos);
		~SpherizeNode();

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
				CEREAL_NVP(m_center),
				CEREAL_NVP(m_strength),
				CEREAL_NVP(m_offset));
		};

	private:
		math::FVector2	m_uv;
		math::FVector2	m_center;
		float	m_strength;
		math::FVector2	m_offset;
	};


	class TilingAndOffsetNode final :public	NodeBase
	{
	public:
		TilingAndOffsetNode();
		TilingAndOffsetNode(int id, const math::FVector2& pos);
		~TilingAndOffsetNode();

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
				CEREAL_NVP(m_tiling),
				CEREAL_NVP(m_offset));
		};

	private:
		math::FVector2	m_uv;
		math::FVector2	m_tiling;
		math::FVector2	m_offset;
	};
	class TwirlNode	final :public	NodeBase
	{
	public:
		TwirlNode();
		TwirlNode(int id, const math::FVector2& pos);
		~TwirlNode();

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
				CEREAL_NVP(m_center),
				CEREAL_NVP(m_strength),
				CEREAL_NVP(m_offset));
		};

	private:
		math::FVector2	m_uv;
		math::FVector2	m_center;
		float	m_strength;
		math::FVector2	m_offset;

	};
	class UVNode	final :public	NodeBase
	{
	public:
		UVNode();
		UVNode(int id, const math::FVector2& pos);
		~UVNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(	cereal::base_class<NodeBase>(this));
		};

	private:
	};
}