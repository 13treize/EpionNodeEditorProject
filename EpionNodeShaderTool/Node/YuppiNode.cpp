#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"YuppiNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

namespace	epion::Node
{
	Yuppi2DNode::Yuppi2DNode()
		:NodeBase(2, 1)
	{
		Init();
	}

	Yuppi2DNode::Yuppi2DNode(int id, const math::FVector2& pos)
		: NodeBase("Yuppi2D", id, pos, 2, 1)
	{
		Init();
	}

	Yuppi2DNode::~Yuppi2DNode()
	{
	}

	void Yuppi2DNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::COLOR,
		};
		m_input_name =
		{
			"UV","Body"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR3);
		m_output_name.push_back("Out");

		m_color_picker[0].Init("0", "Color");
		m_open_popup[0] = false;
		m_node_type = NODE_TYPE::NORMAL;
	}

	void	Yuppi2DNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	m_color_picker[0].SetInputSlotColor2(m_input_pos[1], m_open_popup[0], m_color, 1);
	}

	void	Yuppi2DNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString3(m_color);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string	Yuppi2DNode::GetFunctionDefStr()
	{
		return
			"void yuppi_ellipse(float2 UV, float Width, float Height, out float Out)\n"
			"{\n"
			"    float d = length((UV * 2 - 1) / float2(Width, Height));\n"
			"    Out = saturate((1 - d) / fwidth(d));\n"
			"}\n";
			"void Yuppi2D(float2 UV, float3 Body, out float3 Out)\n"
			"{\n"
			"    \n"
			"}\n";
	}
#pragma endregion

}