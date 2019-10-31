#include	"../All.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"NodeData.h"
#include	"InputBasicNode.h"
#include	"../epion_string.h"

namespace
{
	const ImVec2	size(-20, -20);

	epion::NodeCustom::InputSlotState	UnlitInitState[] =
	{
		{"NUM",	0,	epion::NodeCustom::SLOT_TYPE::VECTOR1},
	};
	std::string vec_str[4]=
	{
		"x","y","z","w"
	};
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::FloatNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::Vector2Node)
CEREAL_REGISTER_TYPE(epion::NodeCustom::Vector3Node)
CEREAL_REGISTER_TYPE(epion::NodeCustom::Vector4Node)
CEREAL_REGISTER_TYPE(epion::NodeCustom::TimeNode)

namespace	epion::NodeCustom
{
	FloatNode::FloatNode()
	{
		Init();
	}
	FloatNode::FloatNode(int id, const math::FVector2& pos)
		:NodeBase("Float", id, pos, size, 1, 1)
	{
		Init();
	}
	FloatNode::~FloatNode()
	{
		Init();
	}
	void FloatNode::Init()
	{
		input_num = 1.0f;

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back(vec_str[0]);

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}
	void	FloatNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[0], SLOT_INPUT_POS_X, StringConverter::get_space(0), input_num);
		}
	}

	void	FloatNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	FloatNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Float_num" + std::to_string(m_ID);

		m_input_str[0] = std::to_string(input_num);

		str_set(nodes_ptr, links);

		m_function_call_str = "    float " + m_out_str[0]+"="+ m_input_str[0] + ";\n";
	}

	std::string	FloatNode::get_function_def_str()
	{
		return"";
	}


	Vector2Node::Vector2Node()
	{
		Init();
	}
	Vector2Node::Vector2Node(int id, const math::FVector2& pos)
		:NodeBase("Vector2", id, pos, size, 2, 1)
	{
		Init();
	}
	Vector2Node::~Vector2Node()
	{
	}
	void Vector2Node::Init()
	{
		input_num = { 1.0f, 1.0f };
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
			m_input_name.push_back(vec_str[i]);
		}
		m_output_name.push_back("Out");
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
	}

	void	Vector2Node::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		if (!m_is_input[0])
		{
			ImGui::SetCursorScreenPos(m_input_pos[0] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat(" ", &input_num.x, 0.0f, 1.0f, "%.2f");
		}
		if (!m_is_input[1])
		{
			ImGui::SetCursorScreenPos(m_input_pos[1] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat("  ", &input_num.y, 0.0f, 1.0f, "%.2f");
		}
	}

	void	Vector2Node::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	Vector2Node::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Vector2_num" + std::to_string(m_ID);
		m_input_str[0] = std::to_string(input_num.x);
		m_input_str[1] = std::to_string(input_num.y);
		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				m_is_input[l.get_input_slot()] = true;
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
			}
		}
		m_function_call_str = "    float2 " + m_out_str[0] + "=" + "float2("+m_input_str[0] + "," + m_input_str[1]+");\n";
	}

	std::string	Vector2Node::get_function_def_str()
	{
		return"";
	}

	Vector3Node::Vector3Node()
	{
		Init();
	}
	Vector3Node::Vector3Node(int id, const math::FVector2& pos)
		:NodeBase("Vector3Node", id, pos, size, 3, 1)
	{
		Init();
	}
	Vector3Node::~Vector3Node()
	{
	}
	void	Vector3Node::Init()
	{
		input_num = { 1.0f, 1.0f, 1.0f };
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
			m_input_name.push_back(vec_str[i]);
		}
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR3);
		m_output_name.push_back("Out");


	}
	void	Vector3Node::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		if (!m_is_input[0])
		{
			ImGui::SetCursorScreenPos(m_input_pos[0] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat(" ", &input_num.x, 0.0f, 1.0f, "%.2f");
		}
		if (!m_is_input[1])
		{
			ImGui::SetCursorScreenPos(m_input_pos[1] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat("  ", &input_num.y, 0.0f, 1.0f, "%.2f");
		}
		if (!m_is_input[2])
		{
			ImGui::SetCursorScreenPos(m_input_pos[2] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat("   ", &input_num.z, 0.0f, 1.0f, "%.2f");
		}

	}

	void	Vector3Node::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	Vector3Node::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Vector3_num" + std::to_string(m_ID);
		m_input_str[0] = std::to_string(input_num.x);
		m_input_str[1] = std::to_string(input_num.y);
		m_input_str[2] = std::to_string(input_num.z);

		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				m_is_input[l.get_input_slot()] = true;
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
			}
		}
		m_function_call_str = "    float3 " + m_out_str[0] + "=" + "float3(" + m_input_str[0] + "," + m_input_str[1] + "," + m_input_str[2]+");\n";
	}

	std::string	Vector3Node::get_function_def_str()
	{
		return"";
	}


	Vector4Node::Vector4Node()
	{
		Init();
	}
	Vector4Node::Vector4Node(int id, const math::FVector2& pos)
		:NodeBase("Vector4Node", id, pos, size, 4, 1)
	{
		Init();
	}
	Vector4Node::~Vector4Node()
	{
	}

	void	Vector4Node::Init()
	{
		input_num = { 1.0f, 1.0f, 1.0f, 1.0f };
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
			m_input_name.push_back(vec_str[i]);
		}
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR4);
		m_output_name.push_back("Out");
	}
	void	Vector4Node::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		if (!m_is_input[0])
		{
			ImGui::SetCursorScreenPos(m_input_pos[0] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat(" ", &input_num.x, 0.0f, 1.0f, "%.2f");
		}
		if (!m_is_input[1])
		{
			ImGui::SetCursorScreenPos(m_input_pos[1] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat("  ", &input_num.y, 0.0f, 1.0f, "%.2f");
		}
		if (!m_is_input[2])
		{
			ImGui::SetCursorScreenPos(m_input_pos[2] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat("   ", &input_num.z, 0.0f, 1.0f, "%.2f");
		}
		if (!m_is_input[3])
		{
			ImGui::SetCursorScreenPos(m_input_pos[3] + SLOT_INPUT_POS);
			ImGui::SetNextItemWidth(30.0f);
			ImGui::InputFloat("    ", &input_num.w, 0.0f, 1.0f, "%.2f");
		}

	}

	void	Vector4Node::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	Vector4Node::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Vector4_num" + std::to_string(m_ID);
		m_input_str[0] = std::to_string(input_num.x);
		m_input_str[1] = std::to_string(input_num.y);
		m_input_str[2] = std::to_string(input_num.z);
		m_input_str[3] = std::to_string(input_num.w);

		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				m_is_input[l.get_input_slot()] = true;
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
			}
		}
		m_function_call_str = "    float4 " + m_out_str[0] + "=" + "float4(" + m_input_str[0] +","+ m_input_str[1] + "," + m_input_str[2] + "," + m_input_str[3] + ");\n";
	}

	std::string	Vector4Node::get_function_def_str()
	{
		return"";
	}

	ColorNode::ColorNode()
	{
		Init();
	}
	ColorNode::ColorNode(int id, const math::FVector2& pos)
		:NodeBase("ColorNode", id, pos, size, 1, 1)
	{
		Init();
	}
	ColorNode::~ColorNode()
	{
	}
	void ColorNode::Init()
	{
		color = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_input_slot_type.push_back(SLOT_TYPE::COLOR);
		m_input_name.push_back("In");
		m_output_slot_type.push_back(SLOT_TYPE::COLOR);
		m_output_name.push_back("Out");

	}
	void	ColorNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_inputs_count != 0)
		{
			i_update(offset, draw_list);
		}
	}

	void	ColorNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	ColorNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "color_num" + std::to_string(m_ID);
		m_input_str[0] = std::to_string(color.x)+ "," + std::to_string(color.y)+ "," + std::to_string(color.z)+ "," + std::to_string(color.w);

		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				m_is_input[l.get_input_slot()] = true;
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
			}
		}
		m_function_call_str = "    float4 " + m_out_str[0] + "=" + "float4(" + m_input_str[0] +");\n";
	}

	std::string	ColorNode::get_function_def_str()
	{
		return"";
	}

	TimeNode::TimeNode()
	{
		Init();
	}
	TimeNode::TimeNode(int id, const math::FVector2& pos)
		:NodeBase("TimeNode", id, pos, size, 0, 3)
	{
		Init();
	}
	TimeNode::~TimeNode()
	{
		Init();
	}
	void TimeNode::Init()
	{
		for (int i = 0; i < m_outputs_count; i++)
		{
			m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		}
		m_output_name.push_back("Time(1)");

		m_output_name.push_back("Sin Time(1)");
		m_output_name.push_back("Cos Time(1)");
		//m_output_name.push_back("Sin Time(1)");
		//m_output_name.push_back("Sin Time(1)");

		m_node_type = NODE_TYPE::NORMAL;

	}
	void	TimeNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
	}
	void	TimeNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	TimeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Time_";
		m_out_str[1] = "Sin_Time_";
		m_out_str[2] = "Cos_Time_";
	}

	std::string	TimeNode::get_function_def_str()
	{
		return"";
	}

}
