#pragma once

namespace	epion::NodeCustom
{
	class PolarCoordinatesNode	final :public	NodeBase
	{
	public:
		PolarCoordinatesNode();
		PolarCoordinatesNode(int id, const math::FVector2& pos);
		~PolarCoordinatesNode();

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
				CEREAL_NVP(Center),
				CEREAL_NVP(RadialScale),
				CEREAL_NVP(LengthScale));
		};


	private:
		//	input
		math::FVector2	m_uv;
		math::FVector2	Center;
		float RadialScale;
		float LengthScale;
	};
	class RadialShearNode final :public	NodeBase
	{
	public:
		RadialShearNode();
		RadialShearNode(int id, const math::FVector2& pos);
		~RadialShearNode();

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
				CEREAL_NVP(Center),
				CEREAL_NVP(Strength),
				CEREAL_NVP(Offset));
		};
	private:
		math::FVector2	m_uv;
		math::FVector2	Center;
		math::FVector2	Strength;
		math::FVector2	Offset;
	};


	class SpherizeNode	final :public	NodeBase
	{
	public:
		SpherizeNode();
		SpherizeNode(int id, const math::FVector2& pos);
		~SpherizeNode();

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
				CEREAL_NVP(Center),
				CEREAL_NVP(Strength),
				CEREAL_NVP(Offset));
		};

	private:
		math::FVector2	m_uv;
		math::FVector2	Center;
		float	Strength;
		math::FVector2	Offset;
	};


	class TilingAndOffsetNode final :public	NodeBase
	{
	public:
		TilingAndOffsetNode();
		TilingAndOffsetNode(int id, const math::FVector2& pos);
		~TilingAndOffsetNode();

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
				CEREAL_NVP(Tiling),
				CEREAL_NVP(Offset));
		};

	private:
		math::FVector2	m_uv;
		math::FVector2	Tiling;
		math::FVector2	Offset;
	};
	class TwirlNode	final :public	NodeBase
	{
	public:
		TwirlNode();
		TwirlNode(int id, const math::FVector2& pos);
		~TwirlNode();

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
				CEREAL_NVP(Center),
				CEREAL_NVP(Strength),
				CEREAL_NVP(Offset));
		};

	private:
		math::FVector2	m_uv;
		math::FVector2	Center;
		float	Strength;
		math::FVector2	Offset;

	};
	class UVNode	final :public	NodeBase
	{
	public:
		UVNode();
		UVNode(int id, const math::FVector2& pos);
		~UVNode();

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(	cereal::base_class<NodeBase>(this));
		};

	private:
	};
}