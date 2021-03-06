#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"InputBasicNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::FloatNode)
CEREAL_REGISTER_TYPE(epion::Node::Vector2Node)
CEREAL_REGISTER_TYPE(epion::Node::Vector3Node)
CEREAL_REGISTER_TYPE(epion::Node::Vector4Node)
CEREAL_REGISTER_TYPE(epion::Node::ColorNode)
CEREAL_REGISTER_TYPE(epion::Node::TimeNode)

namespace	epion::Node
{
#pragma region Float
	FloatNode::FloatNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	FloatNode::FloatNode(int id, const math::FVector2& pos)
		:NodeBase("Float", id, pos, 1, 1)
	{
		Init();
	}
	FloatNode::~FloatNode()
	{
	}
	void FloatNode::Init()
	{
		m_num = 1.0f;

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("x");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::VARIABLE;
	}
	void	FloatNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[0], StringConverter::GetSpace(0), m_num);
	}

	void	FloatNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(m_num);
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		StrCheck(nodes_ptr, links);
		m_function_call_str = NodeFunction::SetVarFloat(m_input_str[0], m_out_str[0]);
	}

	std::string	FloatNode::GetFunctionDefStr()
	{
		return"";
	}
#pragma endregion

#pragma region Vector2
	Vector2Node::Vector2Node()
		:NodeBase( 2, 1)
	{
		Init();
	}
	Vector2Node::Vector2Node(int id, const math::FVector2& pos)
		:NodeBase("Vector2", id, pos, 2, 1)
	{
		Init();
	}
	Vector2Node::~Vector2Node()
	{
	}
	void Vector2Node::Init()
	{
		m_num = { 1.0f, 1.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};
		m_input_name =
		{
			"x","y"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::VARIABLE;
	}

	void	Vector2Node::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[0], StringConverter::GetSpace(0), m_num.x);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_num.y);
	}

	void	Vector2Node::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(m_num.x);
		m_input_str[1] = std::to_string(m_num.y);
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		StrCheck(nodes_ptr, links);
		m_function_call_str = NodeFunction::SetVarFloat2(m_input_str[0], m_input_str[1], m_out_str[0]);
	}

	std::string	Vector2Node::GetFunctionDefStr()
	{
		return"";
	}
#pragma endregion

	Vector3Node::Vector3Node()
		:NodeBase(3, 1)
	{
		Init();
	}
	Vector3Node::Vector3Node(int id, const math::FVector2& pos)
		:NodeBase("Vector3", id, pos, 3, 1)
	{
		Init();
	}
	Vector3Node::~Vector3Node()
	{
	}
	void	Vector3Node::Init()
	{
		m_num = { 1.0f, 1.0f, 1.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,
		};

		m_input_name =
		{
			"x", "y", "z"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR3);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::VARIABLE;
	}
	void	Vector3Node::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[0], StringConverter::GetSpace(0), m_num.x);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_num.y);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_num.z);
	}

	void	Vector3Node::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(m_num.x);
		m_input_str[1] = std::to_string(m_num.y);
		m_input_str[2] = std::to_string(m_num.z);
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		StrCheck(nodes_ptr, links);
		m_function_call_str = "    float3 " + m_out_str[0] + "=" + "float3(" + m_input_str[0] + "," + m_input_str[1] + "," + m_input_str[2]+");\n";
	}

	std::string	Vector3Node::GetFunctionDefStr()
	{
		return"";
	}


	Vector4Node::Vector4Node()
		:NodeBase( 4, 1)
	{
		Init();
	}
	Vector4Node::Vector4Node(int id, const math::FVector2& pos)
		:NodeBase("Vector4", id, pos, 4, 1)
	{
		Init();
	}
	Vector4Node::~Vector4Node()
	{
	}

	void	Vector4Node::Init()
	{
		m_num = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,
		};

		m_input_name =
		{
			"x", "y", "z", "w"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR4);
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::VARIABLE;
	}
	void	Vector4Node::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[0], StringConverter::GetSpace(0), m_num.x);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_num.y);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_num.z);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::GetSpace(3), m_num.w);
	}

	void	Vector4Node::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(m_num.x);
		m_input_str[1] = std::to_string(m_num.y);
		m_input_str[2] = std::to_string(m_num.z);
		m_input_str[3] = std::to_string(m_num.w);
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		StrCheck(nodes_ptr, links);
		m_function_call_str = "    float4 " + m_out_str[0] + "=" + "float4(" + m_input_str[0] +","+ m_input_str[1] + "," + m_input_str[2] + "," + m_input_str[3] + ");\n";
	}

	std::string	Vector4Node::GetFunctionDefStr()
	{
		return"";
	}

	ColorNode::ColorNode()
		:NodeBase( 1, 1)
	{
		Init();
	}
	ColorNode::ColorNode(int id, const math::FVector2& pos)
		:NodeBase("Color", id, pos, 1, 1)
	{
		Init();
	}
	ColorNode::~ColorNode()
	{
	}
	void ColorNode::Init()
	{
		m_color = { 1.0f, 1.0f, 1.0f};
		m_input_slot_type.push_back(SLOT_TYPE::COLOR);
		m_input_name.push_back("In");
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR3);
		m_output_name.push_back("Out");

		m_color_picker[0].Init("1", "Color");
		m_open_popup[0] = false;
		m_node_type = NODE_TYPE::VARIABLE;
	}
	void	ColorNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	m_color_picker[0].SetInputSlotColor2(m_input_pos[0], m_open_popup[0], m_color,0);
	}

	void	ColorNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = NodeFunction::SetInputToString3(m_color);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);

		StrCheck(nodes_ptr, links);
		m_function_call_str = "    float3 " + m_out_str[0] + "="+ m_input_str[0] +";\n";
	}

	std::string	ColorNode::GetFunctionDefStr()
	{
		return"";
	}

	TimeNode::TimeNode()
		:NodeBase( 0, 3)
	{
		Init();
	}
	TimeNode::TimeNode(int id, const math::FVector2& pos)
		:NodeBase("TimeNode", id, pos, 0, 3)
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
		m_output_name.push_back("Time");
		m_output_name.push_back("Sin Time");
		m_output_name.push_back("Cos Time");
		//m_output_name.push_back("Sin Time(1)");
		//m_output_name.push_back("Sin Time(1)");

		m_node_type = NODE_TYPE::NORMAL;

	}
	void	TimeNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
	}

	void	TimeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Time_";
		m_out_str[1] = "Sin_Time_";
		m_out_str[2] = "Cos_Time_";
	}

	std::string	TimeNode::GetFunctionDefStr()
	{
		return"";
	}

}
