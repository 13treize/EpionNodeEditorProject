#include	<string>
#include	<utility>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"node_data.h"


namespace	epion::NodeCustom
{
	NodeBase::NodeBase()
	{
	}

	NodeBase::NodeBase(std::string name, int id, const ImVec2& pos, int inputs_count, int outputs_count)
	{
		m_Name = name;
		m_ID = id;
		m_Pos = pos;
		m_inputs_count = inputs_count;
		m_outputs_count = outputs_count;

	}

	ImVec2 NodeBase::get_input_slot_pos(int slot_no) const
	{
		return ImVec2(m_Pos.x + 10,
			m_Pos.y + m_Size.y * ((float)slot_no + 1) / ((float)m_inputs_count + 1));
	}
	ImVec2 NodeBase::get_output_slot_pos(int slot_no) const
	{
		return ImVec2(m_Pos.x + m_Size.x - 10,
			m_Pos.y + m_Size.y * ((float)slot_no + 1) / ((float)m_outputs_count + 1));
	}


	PBRMasterNode::PBRMasterNode(std::string name, int id, const ImVec2& pos)
		:NodeBase(name, id, pos, 8, 0)
	{
		inputdata.Position = {1,1,1,1};
		inputdata.Albedo = { 1,1,1,1 };
		inputdata.Normal = { 1,1,1,1 };
		inputdata.Emission = { 1,1,1,1 };
		inputdata.Metallic = 1;
		inputdata.Smoothness = 1;
		inputdata.Occulusion = 1;
		inputdata.Alpha = 1;
		inputdata.AlphaChipThreshold = 1;

		input	=std::make_any<PBRInputData>;

		input = inputdata;

		//inputdata = std::any_cast<PBRInputData>(input);

		//input. = inputdata;
	}

	//ƒm[ƒh‚ğ‚Â‚È‚°‚é
	NodeLink::NodeLink(int input_idx, int input_slot, int output_idx, int output_slot)
		: m_input_id(input_idx), m_input_slot(input_slot), m_output_id(output_idx), m_output_slot(output_slot)
	{

	}

	AddNode::AddNode(std::string name, int id, const ImVec2& pos)
		: NodeBase(name, id, pos, 2, 1)
	{

	}
}