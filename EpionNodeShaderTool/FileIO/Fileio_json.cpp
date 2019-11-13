#include	"../All.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/polymorphic.hpp>

#include	"../Node/NodeData.h"

#include	"Fileio_json.h"



namespace
{

}
//template<class Archive>
//void serialize(Archive & archive, std::any &data)
//{
//	archive(CEREAL_NVP(data));
//}


template<class Archive>
void serialize(Archive & archive, ImVec4 &vector)
{
	archive(
		cereal::make_nvp("x", vector.x),
		cereal::make_nvp("y", vector.y),
		cereal::make_nvp("z", vector.z),
		cereal::make_nvp("w", vector.w)
	);
}

template<class Archive>
void serialize(Archive & archive, ImVec2 &vector)
{
	archive(
		cereal::make_nvp("x", vector.x),
		cereal::make_nvp("y", vector.y));
}

namespace	epion::FileIO
{

	void	FileIOJson::Input(
		std::string&	path,
		std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>& node_base,
		std::vector<epion::NodeCustom::NodeLink>&	node_link)
	{
		std::ifstream	ifs(path, std::ios::in);
		std::stringstream	stream;
		stream << ifs.rdbuf();
		cereal::JSONInputArchive	i_archive(stream);

		i_archive(cereal::make_nvp("node_param", node_base));
	
		i_archive(cereal::make_nvp("link_param", node_link));
		ifs.close();

	}

	void	FileIOJson::Output(	const std::string&	path,
								const std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>& node_base,
								const std::vector<epion::NodeCustom::NodeLink>&	node_link)
	{
		FileIOStates	output_node_data;

		std::ofstream		ofs(path);
		std::stringstream	stream;

		{
			cereal::JSONOutputArchive	o_archive(stream);
			//o_archive(cereal::make_nvp("node_param", output_node_data.nodes));

			o_archive(cereal::make_nvp("node_param", node_base));
			o_archive(cereal::make_nvp("link_param", node_link));
		}
		ofs << stream.str();
		ofs.close();
	}

	void	FileIOJson::Input(
		std::string&	path,
		std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>& node_base,
		std::list<epion::NodeCustom::NodeLink>&	node_link)
	{
		std::ifstream	ifs(path, std::ios::in);
		std::stringstream	stream;
		stream << ifs.rdbuf();
		cereal::JSONInputArchive	i_archive(stream);

		i_archive(cereal::make_nvp("node_param", node_base));

		i_archive(cereal::make_nvp("link_param", node_link));
		ifs.close();

	}

	void	FileIOJson::Output(const std::string&	path,
		const std::vector<std::unique_ptr<epion::NodeCustom::NodeBase>>& node_base,
		const std::list<epion::NodeCustom::NodeLink>&	node_link)
	{
		FileIOStates	output_node_data;

		std::ofstream		ofs(path);
		std::stringstream	stream;

		{
			cereal::JSONOutputArchive	o_archive(stream);
			//o_archive(cereal::make_nvp("node_param", output_node_data.nodes));

			o_archive(cereal::make_nvp("node_param", node_base));
			o_archive(cereal::make_nvp("link_param", node_link));
		}
		ofs << stream.str();
		ofs.close();
	}
}