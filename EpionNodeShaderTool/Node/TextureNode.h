#pragma once
namespace	epion::Node
{
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

	class	Texture2DNode final :public	NodeBase
	{
	public:
		Texture2DNode();
		Texture2DNode(int id, const math::FVector2& pos);
		~Texture2DNode();

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
		float m_slot_no;
	};

	class	Texture3DNode final :public	NodeBase
	{
	public:
		Texture3DNode();
		Texture3DNode(int id, const math::FVector2& pos);
		~Texture3DNode();

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
		float m_slot_no;
	};

}

