#pragma once
namespace	epion
{
	class Texture;
}

namespace	epion::GUI
{
	class NodeDragWindow final
	{
	public:
		bool Init();

		void Update();

		std::vector<std::string>& GetNodeNames();
	private:
	std::unique_ptr<Texture>	m_icon_tex;
	std::vector<std::string>	m_node_names;
	std::string	m_node_name;

	};
}