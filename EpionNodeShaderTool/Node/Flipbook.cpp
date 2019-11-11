#include	<string>
#include	<utility>
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"FlipbookNode.h"
#include	"../epion_string.h"

CEREAL_REGISTER_TYPE(epion::NodeCustom::FlipbookNode)

namespace
{
	const ImVec2	size(0, 0);

	epion::NodeCustom::InputSlotState	UnlitInitState[] =
	{
		{"UV",			0,	epion::NodeCustom::SLOT_TYPE::VECTOR2 },
		{"AngleOffset",	1,	epion::NodeCustom::SLOT_TYPE::VECTOR1 },
		{"CellDensity",	2,	epion::NodeCustom::SLOT_TYPE::VECTOR1 },
		{"CellDensity",	2,	epion::NodeCustom::SLOT_TYPE::VECTOR1 },
		{"CellDensity",	2,	epion::NodeCustom::SLOT_TYPE::VECTOR1 },

	};
	enum	NUM :unsigned char
	{
		m_uv,
		m_angleoffset,
		m_celldensity,
	};
}

namespace	epion::NodeCustom
{
	FlipbookNode::FlipbookNode()
	{
		Init();
	}

	FlipbookNode::FlipbookNode(int id, const math::FVector2& pos)
		:NodeBase("Flipbook", id, pos, 5, 1)
	{
		Init();

	}

	FlipbookNode::~FlipbookNode()
	{
	}

	void	FlipbookNode::Init()
	{
		//UV = { 0,0 };
		//AngleOffset = 1.0f;
		//CellDensity = 1.0f;
		//for (int i = 0; i < m_inputs_count; i++)
		//{
		//	m_input_slot_type.push_back(UnlitInitState[i].slot_type);
		//}
		//for (int i = 0; i < m_outputs_count; i++)
		//{
		//	m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		//}
		////node	slot name
		//m_input_name.push_back("UV(2)");
		//m_input_name.push_back("AngleOffset(1)");
		//m_input_name.push_back("CellDensity(1)");

		//m_output_name.push_back("Out(1)");
		//m_output_name.push_back("Cells(1)");

	}

	void	FlipbookNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		//draw_list->ChannelsSetCurrent(1);

		//if (!m_is_input[0])
		//{
		//	ImGui::SetCursorScreenPos(m_input_pos[0] + ImVec2(-50, -SLOT_INPUT_FLOAT));
		//	ImGui::TextColored(ImColor::Vec4::WHITE, "%s", "uv");
		//}

		//if (!m_is_input[1])
		//{
		//	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), AngleOffset);
		//}

		//if (!m_is_input[2])
		//{
		//	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), CellDensity);
		//}

	}
	void	FlipbookNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		//m_out_str[0] = "Volonoi_out" + std::to_string(m_ID);
		//m_out_str[1] = "Volonoi_cell" + std::to_string(m_ID);


		//m_input_str[0] = "input.uv";
		//m_input_str[1] = std::to_string(AngleOffset);
		//m_input_str[2] = std::to_string(CellDensity);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    float " + m_out_str[1] + ";\n";
		m_function_call_str += "    Voronoi_float(";
		str_set(nodes_ptr, links);
	}
	std::string	FlipbookNode::GetFunctionDefStr()
	{
		return"";

	}
}