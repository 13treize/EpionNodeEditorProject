#include	"../All.h"
#include	"../epion.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"ChannelNode.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::CombineNode)


namespace	epion::NodeCustom
{
#pragma region CombineNode
	CombineNode::CombineNode()
		:NodeBase(4, 3)
	{
		Init();
	}

	CombineNode::CombineNode(int id, const math::FVector2& pos)
		:NodeBase("Combine", id, pos, 4, 3)
	{
		Init();
	}

	CombineNode::~CombineNode()
	{
	}

	void CombineNode::Init()
	{
		R = 0;
		G = 0;
		B = 0;
		A = 0;

		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,
		};
		m_input_name =
		{
			"R","G","B","A"
		};

		m_output_slot_type =
		{
			SLOT_TYPE::VECTOR4,	SLOT_TYPE::VECTOR3,	SLOT_TYPE::VECTOR2,
		};

		m_output_name =
		{
			"RGBA","RGB","RG",
		};
		m_node_type = NODE_TYPE::NORMAL;
	}
	void	CombineNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[0], StringConverter::get_space(0), R);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), G);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), B);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3],StringConverter::get_space(3), A);
	}

	void	CombineNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(R);
		m_input_str[1] = std::to_string(G);
		m_input_str[2] = std::to_string(B);
		m_input_str[3] = std::to_string(A);


		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name + "RGBA", m_ID);
		m_out_str[1] = NodeFunction::SetDefineOutName(m_Name + "RGB", m_ID);
		m_out_str[2] = NodeFunction::SetDefineOutName(m_Name + "RG", m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetDefineOutStr1(m_out_str[1]);
		m_function_call_str += NodeFunction::SetDefineOutStr1(m_out_str[2]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		str_set(nodes_ptr, links);
	}

	std::string	CombineNode::GetFunctionDefStr()
	{
		return
			"    void Combine(float R, float G, float B, float A, out float4 RGBA, out float3 RGB, out float2 RG)\n"
			"{\n"
			"    RGBA = float4(R, G, B, A);\n"
			"    RGB = float3(R, G, B);\n"
			"    RG = float2(R, G);\n"
			"}\n";
	}
#pragma endregion

}