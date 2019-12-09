#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"MathRangeNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::ClampNode)
CEREAL_REGISTER_TYPE(epion::Node::FractionNode)
CEREAL_REGISTER_TYPE(epion::Node::MaximumNode)
CEREAL_REGISTER_TYPE(epion::Node::MinimumNode)
CEREAL_REGISTER_TYPE(epion::Node::OneMinusNode)

namespace	epion::Node
{
#pragma region Clamp
	ClampNode::ClampNode()
		:NodeBase(3, 1)
	{
		Init();
	}
	ClampNode::ClampNode(int id, const math::FVector2& pos)
		: NodeBase("Clamp", id, pos, 3, 1)
	{
		Init();
	}
	ClampNode::~ClampNode()
	{
	}
	void ClampNode::Init()
	{
		m_in = {0.5f,0.5f ,0.5f ,0.5f };
		m_min = {0.0f,0.0f ,0.0f ,0.0f };
		m_max = {1.0f,1.0f ,1.0f ,1.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};

		m_input_name =
		{
			"In", "Min", "Max"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}
	void ClampNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);

		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_min, m_input_slot_type[1], 1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[2], m_max, m_input_slot_type[2], 2);
	}
	void ClampNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Clamp_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_min, m_input_str[1], m_input_slot_type[1]);
		NodeFunction::SetSlotData(m_max, m_input_str[2], m_input_slot_type[2]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	ClampNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " In," + NodeFunction::GetType(m_dynamic_slot_type) + " Min," + NodeFunction::GetType(m_dynamic_slot_type) + " Max, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"    Out = clamp(In, Min, Max);\n"
			"}\n";
	};
#pragma endregion

#pragma region Fraction
	FractionNode::FractionNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	FractionNode::FractionNode(int id, const math::FVector2& pos)
		: NodeBase("Fraction", id, pos, 1, 1)
	{
		Init();
	}
	FractionNode::~FractionNode()
	{
	}

	void FractionNode::Init()
	{
		m_in = {0.0f, 0.0f, 0.0f, 0.0f};

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	FractionNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	FractionNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Fraction_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	FractionNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " In, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"    Out = frac(In);\n"
			"};\n";
	};
#pragma endregion

#pragma region Maximun
	MaximumNode::MaximumNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	MaximumNode::MaximumNode(int id, const math::FVector2& pos)
		: NodeBase("Maximum", id, pos, 2, 1)
	{
		Init();
	}
	MaximumNode::~MaximumNode()
	{
	}

	void MaximumNode::Init()
	{
		m_in[0] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_in[1] = { 0.0f, 0.0f, 0.0f, 0.0f };

		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};

		m_input_name =
		{
			"A", "B"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	MaximumNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in[0], m_input_slot_type[0], 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_in[1], m_input_slot_type[1], 1);
	}

	void	MaximumNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Maximum_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_in[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	MaximumNode::GetFunctionDefStr()
	{
		return
		"void "+m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
		"{\n"
		"    Out = max(A, B);\n"
		"}; \n";
	};
#pragma endregion

#pragma region Minimum
	MinimumNode::MinimumNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	MinimumNode::MinimumNode(int id, const math::FVector2& pos)
		: NodeBase("Minimum", id, pos, 2, 1)
	{
		Init();
	}
	MinimumNode::~MinimumNode()
	{
	}

	void MinimumNode::Init()
	{
		m_in[0] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_in[1] = { 0.0f, 0.0f, 0.0f, 0.0f };

		m_input_slot_type =
		{
			SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};

		m_input_name =
		{
			"A", "B"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void MinimumNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in[0], m_input_slot_type[0], 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_in[1], m_input_slot_type[1], 1);
	}

	void MinimumNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Minimum_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_in[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	MinimumNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"    Out = min(A, B);\n"
			"}; \n";
	};
#pragma endregion

#pragma region OneMinus
	OneMinusNode::OneMinusNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	OneMinusNode::OneMinusNode(int id, const math::FVector2& pos)
		: NodeBase("OneMinus", id, pos, 1, 1)
	{
		Init();
	}
	OneMinusNode::~OneMinusNode()
	{
	}

	void OneMinusNode::Init()
	{
		m_in = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void OneMinusNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	OneMinusNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "OneMinus_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	OneMinusNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " In, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"    Out = 1 - In;\n"
			"};\n";
	};
#pragma endregion

}