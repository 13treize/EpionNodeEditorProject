#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"ArtisticAdjustment.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{

}

CEREAL_REGISTER_TYPE(epion::NodeCustom::ReplaceColorNode)


namespace epion::NodeCustom
{
#pragma region ReplaceColor
	ReplaceColorNode::ReplaceColorNode()
		:NodeBase(5, 1)
	{
		Init();
	}

	ReplaceColorNode::ReplaceColorNode(int id, const math::FVector2& pos)
		: NodeBase("ReplaceColor", id, pos, 5, 1)
	{
		Init();
	}

	ReplaceColorNode::~ReplaceColorNode()
	{
	}
	void ReplaceColorNode::Init()
	{
		m_in = { 0.0f,0.0f, 0.0f };
		m_from = { 0.0f, 0.0f, 0.0f };
		m_to ={ 0.0f, 0.0f, 0.0f};
		m_range	=0.0f;
		m_fuzziness	=0.0f;

		m_input_slot_type =
		{
			SLOT_TYPE::COLOR, SLOT_TYPE::COLOR, SLOT_TYPE::COLOR, SLOT_TYPE::VECTOR1,SLOT_TYPE::VECTOR1
		};
		m_input_name =
		{
			"In", "From", "To", "Range", "Fuzziness"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR3);
		m_output_name.push_back("Out");

		m_color_picker[0].Init("1", "ColorA");
		m_color_picker[1].Init("2", "ColorB");
		m_color_picker[1].Init("3", "ColorC");
		m_open_popup[0] = false;
		m_open_popup[1] = false;
		m_open_popup[2] = false;

		m_node_type = NODE_TYPE::NORMAL;
	}
	void ReplaceColorNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	m_color_picker[0].SetInputSlotColor2(m_input_pos[0], m_open_popup[0], m_in, 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	m_color_picker[1].SetInputSlotColor2(m_input_pos[1], m_open_popup[1], m_from, 1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	m_color_picker[2].SetInputSlotColor2(m_input_pos[2], m_open_popup[2], m_to, 2);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::GetSpace(3), m_range);
		if (m_is_slot_input[4] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[4], StringConverter::GetSpace(4), m_fuzziness);
	}

	void ReplaceColorNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = NodeFunction::SetInputToString3(m_in);
		m_input_str[1] = NodeFunction::SetInputToString3(m_from);
		m_input_str[2] = NodeFunction::SetInputToString3(m_to);
		m_input_str[3] = std::to_string(m_range);
		m_input_str[4] = std::to_string(m_fuzziness);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr3(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrSet(nodes_ptr, links);
	}

	std::string	ReplaceColorNode::GetFunctionDefStr()
	{
		return
			"void ReplaceColor(float3 In, float3 From, float3 To, float Range, float Fuzziness, out float3 Out)\n"
			"{\n"
			"    float Distance = distance(From, In);\n"
			"    Out = lerp(To, In, saturate((Distance - Range) / max(Fuzziness, e - f)));\n"
			"}\n";
	}
#pragma endregion

}