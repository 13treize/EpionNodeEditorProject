#pragma once

namespace	epion::NodeCustom
{
	class	NoiseSineWaveNode final :public	NodeBase
	{
	public:
		NoiseSineWaveNode();
		NoiseSineWaveNode(int id, const math::FVector2& pos);
		~NoiseSineWaveNode();

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this), CEREAL_NVP(In), CEREAL_NVP(MinMax));
		};

	private:
		math::FVector4	In;

		math::FVector2	MinMax;

	};

	class	SawtoothWaveNode	final :public	NodeBase
	{
	public:
		SawtoothWaveNode();
		SawtoothWaveNode(int id, const math::FVector2& pos);
		~SawtoothWaveNode();

		void	Init()override;

		void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;


		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this), CEREAL_NVP(In));
		};

	private:
		//	input
		math::FVector4	In;
	};


}