#include	"../All.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeParam.h"
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
	AddNode::AddNode()
	{
		Init();
	}

	AddNode::AddNode(int id, const math::FVector2& pos)
		:NodeBase("Add", id, pos, size, 2, 1)
	{
		Init();
	}

	AddNode::~AddNode()
	{
	}

	void	AddNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");


		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	AddNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);


		for (int i = 0; i < m_inputs_count; i++)
		{
			if (!m_is_input[i])
			{
				NodeFunction::SetInputSlotDynamic(m_input_pos[i], Num[i], m_input_slot_type[i],	i);
			}
		}
	}

	void	AddNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);
		if (m_outputs_count != 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	AddNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Add_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Add_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Add_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";

		m_dynamic_slot_type = m_input_slot_type[0];
		str_check(nodes_ptr, links);
	}
	std::string	AddNode::GetFunctionDefStr()
	{
		return
			"void Add_" + NodeFunction::GetType(m_dynamic_slot_type) + "(" + NodeFunction::GetType(m_dynamic_slot_type) + " A," + NodeFunction::GetType(m_dynamic_slot_type) + " B, out " + NodeFunction::GetType(m_dynamic_slot_type) + " Out)\n"
			"{\n"
			"	Out = A + B;\n"
			"}\n";
	};


	SubtractNode::SubtractNode()
	{
		Init();
	}
	SubtractNode::SubtractNode(int id, const math::FVector2& pos)
		:NodeBase("Subtract", id, pos, size, 2, 1)
	{
		Init();
	}
	SubtractNode::~SubtractNode()
	{
	}

	void	SubtractNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	SubtractNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);

		for (int i = 0; i < m_inputs_count; i++)
		{
			if (!m_is_input[i])
			{
				NodeFunction::SetInputSlotDynamic(m_input_pos[i], Num[i], m_input_slot_type[i], i);
			}
		}
	}

	void	SubtractNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);
		if (m_outputs_count != 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	SubtractNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Subtract_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Subtract_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Subtract_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";

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

	MultiplyNode::MultiplyNode()
	{
		Init();
	}
	MultiplyNode::MultiplyNode(int id, const math::FVector2& pos)
		:NodeBase("Multiply", id, pos, size, 2, 1)
	{
		Init();
	}
	MultiplyNode::~MultiplyNode()
	{
	}

	void	MultiplyNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");


		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	MultiplyNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		for (int i = 0; i < m_inputs_count; i++)
		{
			if (!m_is_input[i])
			{
				NodeFunction::SetInputSlotDynamic(m_input_pos[i], Num[i], m_input_slot_type[i], i);
			}
		}
	}

	void	MultiplyNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	MultiplyNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Multiply_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Multiply_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Multiply_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";

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

	DivideNode::DivideNode()
	{
		Init();
	}
	DivideNode::DivideNode(int id, const math::FVector2& pos)
		:NodeBase("Divide_", id, pos, size, 2, 1)
	{
		Init();
	}
	DivideNode::~DivideNode()
	{
	}
	void	DivideNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::DYNAMIC;

	}

	void	DivideNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		for (int i = 0; i < m_inputs_count; i++)
		{
			if (!m_is_input[i])
			{
				NodeFunction::SetInputSlotDynamic(m_input_pos[i], Num[i], m_input_slot_type[i], i);
			}
		}
	}

	void	DivideNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	DivideNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Divide_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Divide_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Divide_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";

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

	PowerNode::PowerNode()
	{
		Init();
	}
	PowerNode::PowerNode(int id, const math::FVector2& pos)
		:NodeBase("Power_float", id, pos, size, 2, 1)
	{
		Init();
	}
	PowerNode::~PowerNode()
	{
	}
	void	PowerNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	PowerNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::GetSlotTypeName(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		for (int i = 0; i < m_inputs_count; i++)
		{
			if (!m_is_input[i])
			{
				NodeFunction::SetInputSlotDynamic(m_input_pos[i], Num[i], m_input_slot_type[i], i);
			}
		}
	}

	void	PowerNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	PowerNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "PowerNode_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "PowerNode_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Power_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";

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


	SquareRootNode::SquareRootNode()
	{
		Init();
	}
	SquareRootNode::SquareRootNode(int id, const math::FVector2& pos)
		:NodeBase("SquareRoot_float", id, pos, size, 1, 1)
	{
		Init();
	}
	SquareRootNode::~SquareRootNode()
	{
	}
	void	SquareRootNode::Init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	SquareRootNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotDynamic(m_input_pos[0], In, m_input_slot_type[0]);
		}
	}

	void	SquareRootNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	SquareRootNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "SquareRoot_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "SquareRoot_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    SquareRoot_" + NodeFunction::GetType(m_input_slot_type[0]) + "(";

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
}