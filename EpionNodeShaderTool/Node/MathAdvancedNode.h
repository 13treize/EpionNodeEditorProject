#pragma once
namespace	epion::Node
{
	/**
	* @file MathBasicNode.h
	* @brief Šî–{“I‚ÈŒvŽZ
	* @author treize
	* @date 2019/10/25
	*/

	class	AbsoluteNode	final :public NodeBase
	{
	public:
		AbsoluteNode();
		AbsoluteNode(int id, const math::FVector2& pos);
		~AbsoluteNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_in;
	};

	class	LengthNode	final :public NodeBase
	{
	public:
		LengthNode();
		LengthNode(int id, const math::FVector2& pos);
		~LengthNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;
		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_in;
	};

	class	ModuloNode	final :public NodeBase
	{
	public:
		ModuloNode();
		ModuloNode(int id, const math::FVector2& pos);
		~ModuloNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("A", m_num[0]),
				cereal::make_nvp("B", m_num[1]));
		};

	private:
		math::FVector4	m_num[2];
	};

	class	NegateNode	final :public NodeBase
	{
	public:
		NegateNode();
		NegateNode(int id, const math::FVector2& pos);
		~NegateNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_in;
	};

	class	NormalizeNode	final :public NodeBase
	{
	public:
		NormalizeNode();
		NormalizeNode(int id, const math::FVector2& pos);
		~NormalizeNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_in;
	};

	class	PosterizeNode	final :public NodeBase
	{
	public:
		PosterizeNode();
		PosterizeNode(int id, const math::FVector2& pos);
		~PosterizeNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_num[0]),
				cereal::make_nvp("Step", m_num[1]));
		};

	private:
		math::FVector4	m_num[2];
	};


	class	ReciprocalSquareRootNode	final :public NodeBase
	{
	public:
		ReciprocalSquareRootNode();
		ReciprocalSquareRootNode(int id, const math::FVector2& pos);
		~ReciprocalSquareRootNode();

		void Init()override;
		void Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;	
		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In", m_in));
		};
	private:
		math::FVector4	m_in;
	};


}