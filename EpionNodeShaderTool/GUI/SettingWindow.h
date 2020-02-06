#pragma once
namespace	epion::GUI
{
	class SettingWindow final
	{
	public:
		bool Init();
		void Update(std::vector<std::unique_ptr<Node::NodeBase>>&	nodes, std::vector<Node::NodeLink>& links);

		void SetNodeState(int size, std::vector<int>& id,std::vector<math::FVector2>& pos);

		bool m_is_preview_reset;
	private:
		int m_node_size;
		int m_select_scene;
		std::vector<int> m_node_id;
		std::vector<math::FVector2> m_node_pos;

		std::string m_import_json_name;
		std::string m_import_hlsl_name;

		void FileIOUpdate(std::vector<std::unique_ptr<Node::NodeBase>>&	nodes, std::vector<Node::NodeLink>& links);
		void NodeTabUpdate();

		void OptionTabUpdate();
	};
}