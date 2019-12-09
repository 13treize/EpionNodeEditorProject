#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"MathInterpolation.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::LerpNode)

namespace epion::Node
{
#pragma region Lerp
	LerpNode::LerpNode()
		:NodeBase(3, 1)
	{
		Init();
	}
	LerpNode::LerpNode(int id, const math::FVector2& pos)
		:NodeBase("Lerp", id, pos, 3, 1)
	{
		Init();
	}
	LerpNode::~LerpNode()
	{
	}

	void	LerpNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[2] = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1,SLOT_TYPE::VECTOR1,SLOT_TYPE::VECTOR1
		};

		m_input_name=
		{
			"A", "B", "T"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	LerpNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[2], m_num[2], m_input_slot_type[2], 2);
	}

	void	LerpNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Lerp_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);
		NodeFunction::SetSlotData(m_num[2], m_input_str[2], m_input_slot_type[2]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}

	std::string	LerpNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " A," + NodeFunction::GetType(m_input_slot_type[0]) + " B," + NodeFunction::GetType(m_input_slot_type[0]) + " T, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"    Out = lerp(A, B, T);\n"
			"}\n";
	};
#pragma endregion

}