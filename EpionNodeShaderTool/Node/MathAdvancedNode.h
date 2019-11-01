#pragma once
namespace	epion::NodeCustom
{
	class	AbsoluteNode	final :public NodeBase
	{
	public:
		AbsoluteNode();
		AbsoluteNode(int id, const math::FVector2& pos);
		~AbsoluteNode();

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
				cereal::make_nvp("In", In));
		};
	private:
		math::FVector4	In;
	};

	class	LengthNode	final :public NodeBase
	{
	public:
		LengthNode();
		LengthNode(int id, const math::FVector2& pos);
		~LengthNode();

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
				cereal::make_nvp("In", In));
		};
	private:
		math::FVector4	In;
	};

	class	ModuloNode	final :public NodeBase
	{
	public:
		ModuloNode();
		ModuloNode(int id, const math::FVector2& pos);
		~ModuloNode();

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
				cereal::make_nvp("A", Num[0]),
				cereal::make_nvp("B", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};

	class	NegateNode	final :public NodeBase
	{
	public:
		NegateNode();
		NegateNode(int id, const math::FVector2& pos);
		~NegateNode();

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
				cereal::make_nvp("In", In));
		};
	private:
		math::FVector4	In;
	};

	class	NormalizeNode	final :public NodeBase
	{
	public:
		NormalizeNode();
		NormalizeNode(int id, const math::FVector2& pos);
		~NormalizeNode();

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
				cereal::make_nvp("In", In));
		};
	private:
		math::FVector4	In;
	};

	class	PosterizeNode	final :public NodeBase
	{
	public:
		PosterizeNode();
		PosterizeNode(int id, const math::FVector2& pos);
		~PosterizeNode();

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
				cereal::make_nvp("In", Num[0]),
				cereal::make_nvp("Step", Num[1]));
		};

	private:
		math::FVector4	Num[2];
	};


	class	ReciprocalSquareRootNode	final :public NodeBase
	{
	public:
		ReciprocalSquareRootNode();
		ReciprocalSquareRootNode(int id, const math::FVector2& pos);
		~ReciprocalSquareRootNode();

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
				cereal::make_nvp("In", In));
		};
	private:
		math::FVector4	In;
	};


}