#pragma once
namespace	epion::NodeCustom
{

	class	UnlitMasterNode final :public	NodeBase
	{
	public:
		UnlitMasterNode();
		UnlitMasterNode(int id, const epion::math::FVector2& pos);
		~UnlitMasterNode();

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
				CEREAL_NVP(Pos),
				CEREAL_NVP(color),
				CEREAL_NVP(Alpha),
				CEREAL_NVP(AlphaChipThreshold));
		};


	private:
		math::FVector4	Pos;
		math::FVector3	color;
		float	Alpha;
		float	AlphaChipThreshold;
	};
}

