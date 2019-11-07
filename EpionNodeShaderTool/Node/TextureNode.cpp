#include	"../All.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeData.h"
#include	"TextureNode.h"
#include	"../epion_string.h"

namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::Texture2DNode)

namespace	epion::NodeCustom
{
	Texture2DNode::Texture2DNode()
	{
		Init();
	}
	Texture2DNode::Texture2DNode(int id, const epion::math::FVector2& pos)
		:NodeBase("Texture" + std::to_string(id), id, pos, size, 0, 1)
	{
		Init();
	}

	Texture2DNode::~Texture2DNode()
	{
	}

	void Texture2DNode::Init()
	{
		m_output_slot_type.push_back(SLOT_TYPE::TEXTURE2D);
		m_output_name.push_back("Out");
	}

	void Texture2DNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
	}

	void	Texture2DNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	Texture2DNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = m_Name;
		m_function_call_str = " ";

	}

	std::string	Texture2DNode::GetFunctionDefStr()
	{
		return "Texture2D "+m_Name+": register";
	}

}