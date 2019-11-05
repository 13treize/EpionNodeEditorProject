#include	"../All.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeParam.h"
#include	"NodeData.h"
#include	"MathWaveNode.h"
#include	"../epion_string.h"

namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::NoiseSineWaveNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::SawtoothWaveNode)

namespace	epion::NodeCustom
{
	NoiseSineWaveNode::NoiseSineWaveNode()
	{
		Init();
	}

	NoiseSineWaveNode::NoiseSineWaveNode(int id, const math::FVector2& pos)
		:NodeBase("NoiseSineWave", id, pos, size, 2, 1)
	{
		Init();
	}

	NoiseSineWaveNode::~NoiseSineWaveNode()
	{
	}

	void	NoiseSineWaveNode::Init()
	{
		In = { 0,0,0,0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_input_name.push_back("MinMax");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	NoiseSineWaveNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "MinMax" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotDynamic(m_input_pos[0], In, m_input_slot_type[0]);
		}
		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[1], MinMax, 2);
		}

	}

	void	NoiseSineWaveNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	NoiseSineWaveNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "NoiseSineWave_" + NodeFunction::GetType(m_input_slot_type[0]);

		m_out_str[0] = "NoiseSineWave_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		//outéwíËÇ…ëŒÇ∑ÇÈíËã`
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    NoiseSineWave_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";
		//å^ÇçáÇÌÇπÇÈ
		m_dynamic_slot_type = m_input_slot_type[0];
		m_input_slot_type[1] = SLOT_TYPE::VECTOR2;

		str_check(nodes_ptr, links);
	}
	std::string	NoiseSineWaveNode::GetFunctionDefStr()
	{
		return
			"void NoiseSineWave_" + NodeFunction::GetType(m_output_slot_type[0]) + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In,  float2 MinMax, out " + NodeFunction::GetType(m_output_slot_type[0]) + " Out)\n"
			"{\n"
			"	float sinIn = sin(In);\n"
			"	float sinInOffset = sin(In + 1.0);\n"
			"	float randomno = frac(sin((sinIn - sinInOffset) * (12.9898 + 78.233))*43758.5453);\n"
			"	float noise = lerp(MinMax.x, MinMax.y, randomno);\n"
			"	Out = sinIn + noise;\n"
			"}\n";
	}


	SawtoothWaveNode::SawtoothWaveNode()
	{
		Init();
	}

	SawtoothWaveNode::SawtoothWaveNode(int id, const math::FVector2& pos)
		:NodeBase("SawtoothWave", id, pos, size, 1, 1)
	{
		Init();
	}

	SawtoothWaveNode::~SawtoothWaveNode()
	{
	}

	void	SawtoothWaveNode::Init()
	{
		In = { 0,0,0,0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");


		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	SawtoothWaveNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotDynamic(m_input_pos[0], In, m_input_slot_type[0]);
		}
	}

	void	SawtoothWaveNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	SawtoothWaveNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "SawtoothWave_" + NodeFunction::GetType(m_input_slot_type[0]);

		m_out_str[0] = "SawtoothWave_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		//outéwíËÇ…ëŒÇ∑ÇÈíËã`
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    SawtoothWave_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";
		//å^ÇçáÇÌÇπÇÈ
		str_check(nodes_ptr, links);
	}
	std::string	SawtoothWaveNode::GetFunctionDefStr()
	{
		return
			"void SawtoothWave_" + NodeFunction::GetType(m_output_slot_type[0]) + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_output_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = 2 * (In - floor(0.5 + In));\n"
			"}\n";
	}

}