#include	<string>
#include	<utility>
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"NodeParam.h"
#include	"NodeData.h"
#include	"PBRNode.h"

namespace
{
	const ImVec2	size(0, 0);
	epion::NodeCustom::InputSlotState	InitState[9] =
	{
		{"Pos",					0,epion::NodeCustom::SLOT_TYPE::VECTOR4},
		{"Albedo",				1,epion::NodeCustom::SLOT_TYPE::VECTOR3},
		{"Normal",				2,epion::NodeCustom::SLOT_TYPE::VECTOR3},
		{"Emission",			3,epion::NodeCustom::SLOT_TYPE::VECTOR3},
		{"Metallic",			4,epion::NodeCustom::SLOT_TYPE::VECTOR1},
		{"Smoothness",			5,epion::NodeCustom::SLOT_TYPE::VECTOR1},
		{"Occulusion",			6,epion::NodeCustom::SLOT_TYPE::VECTOR1},
		{"Alpha",				7,epion::NodeCustom::SLOT_TYPE::VECTOR1},
		{"AlphaChipThreshold",	8,epion::NodeCustom::SLOT_TYPE::VECTOR1},
	};
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::PBRMasterNode)


namespace	epion::NodeCustom
{
	PBRMasterNode::PBRMasterNode()
	{
		Init();
	}
	PBRMasterNode::PBRMasterNode(int id, const math::FVector2& pos)
		:NodeBase("PBR Master", id, pos, 9, 0)
	{
		Init();
	}

	PBRMasterNode::~PBRMasterNode()
	{
	}


	void PBRMasterNode::Init()
	{
		Position = { 0 ,0,0,0 };
		Albedo = { 0,0,0 };
		Normal = { 0,0,0 };
		Emission = { 0,0,0 };
		Metallic = 0.0f;
		Smoothness = 0.5f;
		Occulusion = 1.0f;
		Alpha = 1.0f;
		AlphaChipThreshold = 0.0f;
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_input_slot_type.push_back(InitState[i].slot_type);
			m_input_name.push_back(InitState[i].slot_name);
		}

		m_output_slot_type.clear();
	}

	void	PBRMasterNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		if (m_inputs_count != 0)
		{
			ImGui::SetCursorScreenPos(m_input_pos[0] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(90.0f);
			//ImGui::InputFloat3(UnlitInitState[0].slot_name.c_str(), &Pos[2],"%.2f");

			ImGui::SetCursorScreenPos(m_input_pos[1] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(120.0f);

			//if (!m_is_input[2])
			//{
			//	ImGui::SetCursorScreenPos(m_input_pos[2] + SLOT_INPUT_POS);
			//	ImGui::SetNextItemWidth(30.0f);
			//	ImGui::InputFloat("   ", &Alpha, 0.0f, 1.0f, "%.2f");
			//}
			//if (!m_is_input[3])
			//{
			//	ImGui::SetCursorScreenPos(m_input_pos[3] + SLOT_INPUT_POS);
			//	ImGui::SetNextItemWidth(30.0f);
			//	ImGui::InputFloat("    ", &AlphaChipThreshold, 0.0f, 1.0f, "%.2f");
			//}

		}
	}

	void	PBRMasterNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count != 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	PBRMasterNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = NodeFunction::SetInputToString4(Position);
		m_input_str[1] = NodeFunction::SetInputToString3(Albedo);
		m_input_str[2] = NodeFunction::SetInputToString3(Normal);
		m_input_str[3] = NodeFunction::SetInputToString3(Emission);
		m_input_str[4] = NodeFunction::SetInputToString(Metallic);
		m_input_str[5] = NodeFunction::SetInputToString(Smoothness);
		m_input_str[6] = NodeFunction::SetInputToString(Occulusion);
		m_input_str[7] = NodeFunction::SetInputToString(Alpha);
		m_input_str[8] = NodeFunction::SetInputToString(AlphaChipThreshold);

	}
	std::string	PBRMasterNode::GetFunctionDefStr()
	{
		return "";
	}
}