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
		std::vector<int> m_node_id;
		std::vector<math::FVector2> m_node_pos;

		void FileIOUpdate(std::vector<std::unique_ptr<Node::NodeBase>>&	nodes, std::vector<Node::NodeLink>& links);
		void NodeTabUpdate();

		void OptionTabUpdate();
	};
}