#include	"../All.h"
#include	"../epion.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"MasterNode.h"
#include "../ImguiFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::UnlitMasterNode)

namespace	epion::NodeCustom
{
	UnlitMasterNode::UnlitMasterNode()
		:NodeBase( 4, 0)
	{
		Init();
	}

	//Position‚ÍŒã‚Å’Ç‰Á
	UnlitMasterNode::UnlitMasterNode(int id, const epion::math::FVector2& pos)
		:NodeBase("Unlit Master", id, pos, 4, 0)
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
			"Pos","Color","Alpha","AlphaChipThreshold"
		};
		m_function_call_str = "";

		m_output_slot_type.clear();
		m_open_popup[0] = false;
		m_color_picker[0].Init("1", "Color");

		m_node_type = NODE_TYPE::MASTER;
	}

	void	UnlitMasterNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[1])	m_color_picker[0].SetInputSlotColor2(m_input_pos[1], m_open_popup[0], color,1);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2],StringConverter::get_space(2), Alpha);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3],StringConverter::get_space(3), AlphaChipThreshold);
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