#include	"../All.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeParam.h"
#include	"NodeData.h"
#include	"MasterNode.h"
#include	"../epion_string.h"
#include "../ImguiFunction.h"

namespace
{
	ImVec2	size(0, 0);
	bool open_popup;
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::UnlitMasterNode)

namespace	epion::NodeCustom
{
	UnlitMasterNode::UnlitMasterNode()
	{
		//init();
	}

	//Position‚ÍŒã‚Å’Ç‰Á
	UnlitMasterNode::UnlitMasterNode(int id, const epion::math::FVector2& pos)
		:NodeBase("Unlit Master", id, pos, size, 4, 0)
	{
		Init();
	}

	UnlitMasterNode::~UnlitMasterNode()
	{
	}

	void UnlitMasterNode::Init()
	{
		Pos = 0;
		color = 0;
		Alpha = 1.0f;
		AlphaChipThreshold = 0;
		m_input_slot_type =
		{
			SLOT_TYPE::POS,	SLOT_TYPE::COLOR, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};
		m_input_name =
		{
			"Pos(3)","Color(3)","Alpha(1)","AlphaChipThreshold(1)"
		};
		m_function_call_str = "";
		//
		m_output_slot_type.clear();

		m_node_type = NODE_TYPE::MASTER;
	}

	void	UnlitMasterNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		if (m_inputs_count != 0)
		{
			ImGui::SetCursorScreenPos(m_input_pos[0] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);

			if (!m_is_input[1])	NodeFunction::SetInputSlotColor(m_input_pos[1], open_popup, color,1);
			if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), Alpha);
			if (!m_is_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3], SLOT_INPUT_POS_X, StringConverter::get_space(3), AlphaChipThreshold);
		}
	}

	void	UnlitMasterNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count != 0)
		{
			o_update(offset, draw_list);
		}
	}
	void	UnlitMasterNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		std::string set_up_str = "";

		m_input_str[0] = NodeFunction::SetInputToString4(Pos);
		m_input_str[1] = NodeFunction::SetInputToString3(color);
		m_input_str[2] = std::to_string(Alpha);
		m_input_str[3] = std::to_string(AlphaChipThreshold);

		m_function_call_str = " = Unlit(";
		str_check(nodes_ptr, links);
	}

	std::string	UnlitMasterNode::GetFunctionDefStr()
	{
		return
			"float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)\n"
			"{\n"
			"    float4 ret_color = float4(Color, Alpha);\n"
			"    return ret_color;\n"
			"};\n";
	}

}