#include	<string>
#include	<utility>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeData.h"
#include	"MathInterpolation.h"
#include	"../epion_string.h"
namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::LerpNode)

namespace epion::NodeCustom
{
	LerpNode::LerpNode()
	{
		Init();
	}
	LerpNode::LerpNode(int id, const math::FVector2& pos)
		:NodeBase("Lerp_float", id, pos, size, 3, 1)
	{
		Init();
	}
	LerpNode::~LerpNode()
	{
	}

	void	LerpNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[2] = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");
		m_input_name.push_back("T");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	LerpNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);
		m_input_name[2] = "T" + NodeFunction::GetSlotTypeName(m_input_slot_type[2]);

		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		for (int i = 0; i < m_inputs_count; i++)
		{
			if (!m_is_input[i])
			{
				switch (m_input_slot_type[i])
				{
				case SLOT_TYPE::VECTOR4:	NodeFunction::SetInputSlotFloat(m_input_pos[i], (static_cast<float>(m_input_slot_type[i]) - 3)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[i]) + i * 4), Num[i].w);
				case SLOT_TYPE::VECTOR3:	NodeFunction::SetInputSlotFloat(m_input_pos[i], (static_cast<float>(m_input_slot_type[i]) - 2)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[i]) - 1 + i * 4), Num[i].z);
				case SLOT_TYPE::VECTOR2:	NodeFunction::SetInputSlotFloat(m_input_pos[i], (static_cast<float>(m_input_slot_type[i]) - 1)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[i]) - 2 + i * 4), Num[i].y);
				case SLOT_TYPE::VECTOR1:	NodeFunction::SetInputSlotFloat(m_input_pos[i], (static_cast<float>(m_input_slot_type[i]))		*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[i]) - 3 + i * 4), Num[i].x);
					break;
				}
			}
		}
	}

	void	LerpNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	LerpNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Lerp_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Lerp_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);
		NodeFunction::SetSlotData(Num[2], m_input_str[2], m_input_slot_type[2]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}

	std::string	LerpNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " A," + NodeFunction::GetType(m_input_slot_type[0]) + " B," + NodeFunction::GetType(m_input_slot_type[0]) + " T, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"    Out = lerp(A, B, T);\n"
			"}\n";
	};
}