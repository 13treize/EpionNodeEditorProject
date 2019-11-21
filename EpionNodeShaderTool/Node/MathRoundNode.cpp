#include	"../All.h"
#include	"../epion.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeData.h"

#include	"MathRoundNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

CEREAL_REGISTER_TYPE(epion::NodeCustom::CeilingNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::StepNode)


namespace	epion::NodeCustom
{
#pragma region Ceiling
	CeilingNode::CeilingNode()
		:NodeBase(1,1)
	{
		Init();
	}
	CeilingNode::CeilingNode(int id, const math::FVector2& pos)
		:NodeBase("Ceiling", id, pos, 1, 1)
	{
		Init();
	}
	CeilingNode::~CeilingNode()
	{
	}
	void CeilingNode::Init()
	{
		m_in = { 0.5f,0.5f ,0.5f ,0.5f };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::DYNAMIC;
		m_dynamic_slot_type = SLOT_TYPE::VECTOR1;
	}

	void CeilingNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}
	void CeilingNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Ceiling_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	CeilingNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " In, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"    Out = ceil(In);\n"
			"}\n";
	};
#pragma endregion

#pragma region Step
	StepNode::StepNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	StepNode::StepNode(int id, const math::FVector2& pos)
		: NodeBase("Step", id, pos, 2, 1)
	{
		Init();
	}
	StepNode::~StepNode()
	{
	}
	void StepNode::Init()
	{
		m_edge = { 0.5f,0.5f ,0.5f ,0.5f };
		m_in = { 0.5f,0.5f ,0.5f ,0.5f };
		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};

		m_input_name =
		{
			"Edge","In"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::DYNAMIC;
		m_dynamic_slot_type = SLOT_TYPE::VECTOR1;
	}
	void StepNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_edge, m_input_slot_type[0], 0);
		if (!m_is_slot_input[1])	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_in, m_input_slot_type[1], 1);
	}
	void StepNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Step_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_edge, m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_in, m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	StepNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " Edge," +NodeFunction::GetType(m_dynamic_slot_type) + " In, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"       Out = step(Edge, In);\n"
			"}\n";
	};
#pragma endregion

#pragma region Ceiling
#pragma endregion

#pragma region Ceiling
#pragma endregion

#pragma region Ceiling
#pragma endregion

#pragma region Ceiling
#pragma endregion
}