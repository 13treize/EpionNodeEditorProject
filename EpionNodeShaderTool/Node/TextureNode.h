#pragma once
namespace	epion::NodeCustom
{
	class	SamplerTexture2DNode final :public	NodeBase
	{
	public:
		SamplerTexture2DNode();
		SamplerTexture2DNode(int id, const math::FVector2& pos);
		~SamplerTexture2DNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;


		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this));
		};

	private:
	};

	class	SamplerStateNode final :public	NodeBase
	{
	public:
		SamplerStateNode();
		SamplerStateNode(int id, const math::FVector2& pos);
		~SamplerStateNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(cereal::base_class<NodeBase>(this),
				CEREAL_NVP(m_slot_no));
		};

	private:
		float m_slot_no;
	};
}
