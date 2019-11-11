#include	"../All.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeData.h"
#include	"MathBasicNode.h"
#include	"../epion_string.h"
namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::AddNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::SubtractNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::MultiplyNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::DivideNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::PowerNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::SquareRootNode)


namespace	epion::NodeCustom
{
#pragma region Add
	AddNode::AddNode()
		:NodeBase(2, 1)
	{
		Init();
	}

	AddNode::AddNode(int id, const math::FVector2& pos)
		:NodeBase("Add", id, pos, 2, 1)
	{
		Init();
	}

	AddNode::~AddNode()
	{
	}

	void	AddNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
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

	void	AddNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0],	0);
		if (!m_is_input[1])	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
	}

	void	AddNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Add_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);
	}
	std::string	AddNode::GetFunctionDefStr()
	{
		return
			"void " +m_Name + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"	Out = A + B;\n"
			"}\n";
	};
#pragma endregion

#pragma region Subtract
	SubtractNode::SubtractNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	SubtractNode::SubtractNode(int id, const math::FVector2& pos)
		:NodeBase("Subtract", id, pos, 2, 1)
	{
		Init();
	}
	SubtractNode::~SubtractNode()
	{
	}

	void	SubtractNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
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

	void	SubtractNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (!m_is_input[1])	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
	}

	void	SubtractNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Subtract_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);
	}
	std::string	SubtractNode::GetFunctionDefStr()
	{
		return
			"void Subtract_" + NodeFunction::GetType(m_dynamic_slot_type) + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"	Out = A - B;\n"
			"}\n";
	};
#pragma endregion

#pragma region Multiply
	MultiplyNode::MultiplyNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	MultiplyNode::MultiplyNode(int id, const math::FVector2& pos)
		:NodeBase("Multiply", id, pos, 2, 1)
	{
		Init();
	}
	MultiplyNode::~MultiplyNode()
	{
	}

	void	MultiplyNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
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

	void	MultiplyNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (!m_is_input[1])	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
	}

	void	MultiplyNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Multiply_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);
	}
	std::string	MultiplyNode::GetFunctionDefStr()
	{
		return
			"void Multiply_" + NodeFunction::GetType(m_dynamic_slot_type) + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"	Out = A * B;\n"
			"}\n";
	};
#pragma endregion

#pragma region Divide
	DivideNode::DivideNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	DivideNode::DivideNode(int id, const math::FVector2& pos)
		:NodeBase("Divide", id, pos, 2, 1)
	{
		Init();
	}
	DivideNode::~DivideNode()
	{
	}
	void	DivideNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
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

	void	DivideNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (!m_is_input[1])	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
	}

	void	DivideNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Divide_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);
	}
	std::string	DivideNode::GetFunctionDefStr()
	{
		return
			"void Divide_" + NodeFunction::GetType(m_dynamic_slot_type) + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"	Out = A / B;\n"
			"}\n";
	};
#pragma endregion

#pragma region Power

	PowerNode::PowerNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	PowerNode::PowerNode(int id, const math::FVector2& pos)
		:NodeBase("Power", id, pos, 2, 1)
	{
		Init();
	}
	PowerNode::~PowerNode()
	{
	}
	void	PowerNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
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

	void	PowerNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (!m_is_input[1])	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
	}

	void	PowerNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Power_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);
	}

	std::string	PowerNode::GetFunctionDefStr()
	{
		return
			"void Power_" + NodeFunction::GetType(m_input_slot_type[0]) + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " A," + NodeFunction::GetType(m_input_slot_type[0]) + " B, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = pow(A, B);\n"
			"}\n";
	};
#pragma endregion

#pragma region SquareRoot

	SquareRootNode::SquareRootNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	SquareRootNode::SquareRootNode(int id, const math::FVector2& pos)
		:NodeBase("SquareRoot", id, pos, 1, 1)
	{
		Init();
	}
	SquareRootNode::~SquareRootNode()
	{
	}
	void	SquareRootNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	SquareRootNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0]);
	}

	void	SquareRootNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "SquareRoot_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);

	}
	std::string	SquareRootNode::GetFunctionDefStr()
	{
		return
			"void SquareRoot_" + NodeFunction::GetType(m_dynamic_slot_type) + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " In, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"	Out = sqrt(In);\n"
			"}\n";
	};
#pragma endregion

}