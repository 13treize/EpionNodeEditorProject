#pragma once

namespace	epion::FileIO
{
	class	epion::NodeCustom::NodeBase;
	class	epion::NodeCustom::NodeLink;

	struct	FileIOStates
	{
		FileIOStates() {}
		std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>	nodes;
		std::vector<epion::NodeCustom::NodeLink>	links;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(nodes), CEREAL_NVP(links));
		};
	};


	class	FileIOJson
	{
	public:
		FileIOJson()
		{}

		~FileIOJson()
		{}

		void	Input(	const std::string& path,
						std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>& node_base,
						std::vector<epion::NodeCustom::NodeLink>& node_link);

		void	Output(	const std::string&	path,
						const std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>	&node_base,
						const std::vector<epion::NodeCustom::NodeLink>&	node_link);

		void	Input(const std::string& path,
			std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>& node_base,
			std::list<epion::NodeCustom::NodeLink>&	node_link);

		void	Output(const std::string&	path,
			const std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>	&node_base,
			const std::list<epion::NodeCustom::NodeLink>&	node_link);


	private:
	};
}