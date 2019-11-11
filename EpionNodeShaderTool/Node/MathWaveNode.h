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
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this), CEREAL_NVP(m_in), CEREAL_NVP(m_minmax));
		};

	private:
		math::FVector4	m_in;
		math::FVector2	m_minmax;

	};

	class	SawtoothWaveNode	final :public	NodeBase
	{
	public:
		SawtoothWaveNode();
		SawtoothWaveNode(int id, const math::FVector2& pos);
		~SawtoothWaveNode();

		void	Init()override;
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this), CEREAL_NVP(m_in));
		};

	private:
		//	input
		math::FVector4	m_in;
	};


}