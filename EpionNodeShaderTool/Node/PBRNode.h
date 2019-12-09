#pragma once

namespace	epion::Node
{
	class	PBRMasterNode :public	NodeBase
	{
	public:
		PBRMasterNode();
		PBRMasterNode(int id, const epion::math::FVector2& pos);
		~PBRMasterNode();
		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(	CEREAL_NVP(Position),
						CEREAL_NVP(Albedo),
						CEREAL_NVP(Normal),
						CEREAL_NVP(Emission),
						CEREAL_NVP(Metallic),
						CEREAL_NVP(Smoothness),
						CEREAL_NVP(Occulusion),
						CEREAL_NVP(Alpha),
						CEREAL_NVP(AlphaChipThreshold));
		};
	private:
		math::FVector4	Position;
		math::FVector3	Albedo;
		math::FVector3	Normal;
		math::FVector3	Emission;
		float	Metallic;
		float	Smoothness;
		float	Occulusion;
		float	Alpha;
		float	AlphaChipThreshold;

	};
}