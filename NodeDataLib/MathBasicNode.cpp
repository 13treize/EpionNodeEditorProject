#include	"stdafx.h"
#include	"MathBasicNode.h"
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
		init();
	}

	AddNode::AddNode(int id, const math::FVector2& pos)
		:NodeBase("AddNode_float", id, pos, size, 2, 1)
	{
		init();
	}

	AddNode::~AddNode()
	{
	}

	void	AddNode::init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");


		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

	}

	void	AddNode::input_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::get_slot_type_name(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::get_slot_type_name(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::get_slot_type_name(m_output_slot_type[0]);


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

	void	AddNode::output_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	AddNode::shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "AddNode_" + NodeFunction::get_type(m_input_slot_type[0]);
		m_out_str[0] = "AddNode_out" + std::to_string(m_ID);

		NodeFunction::set_slot_data(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::set_slot_data(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::get_type(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Add_" + NodeFunction::get_type(m_input_slot_type[0]) + "(";

		str_set(nodes_ptr, links);
	}
	std::string	AddNode::get_function_def_str()
	{
		return
			"void Add_" + NodeFunction::get_type(m_input_slot_type[0]) + "(" + NodeFunction::get_type(m_input_slot_type[0]) + " A," + NodeFunction::get_type(m_input_slot_type[0]) + " B, out " + NodeFunction::get_type(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = A + B;\n"
			"}\n";
	};


	SubtractNode::SubtractNode()
	{
		init();
	}
	SubtractNode::SubtractNode(int id, const math::FVector2& pos)
		:NodeBase("SubtractNode_float", id, pos, size, 2, 1)
	{
		init();
	}
	SubtractNode::~SubtractNode()
	{
	}

	void	SubtractNode::init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");


		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

	}

	void	SubtractNode::input_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::get_slot_type_name(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::get_slot_type_name(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::get_slot_type_name(m_output_slot_type[0]);

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

	void	SubtractNode::output_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	SubtractNode::shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "SubtractNode_" + NodeFunction::get_type(m_input_slot_type[0]);
		m_out_str[0] = "SubtractNode_out" + std::to_string(m_ID);

		NodeFunction::set_slot_data(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::set_slot_data(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::get_type(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Subtract_" + NodeFunction::get_type(m_input_slot_type[0]) + "(";

		str_set(nodes_ptr, links);
	}
	std::string	SubtractNode::get_function_def_str()
	{
		return
			"void Subtract_" + NodeFunction::get_type(m_input_slot_type[0]) + "(" + NodeFunction::get_type(m_input_slot_type[0]) + " A," + NodeFunction::get_type(m_input_slot_type[0]) + " B, out " + NodeFunction::get_type(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = A - B;\n"
			"}\n";
	};

	MultiplyNode::MultiplyNode()
	{
		init();
	}
	MultiplyNode::MultiplyNode(int id, const math::FVector2& pos)
		:NodeBase("Multiply_float", id, pos, size, 2, 1)
	{
		init();
	}
	MultiplyNode::~MultiplyNode()
	{
	}

	void	MultiplyNode::init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");


		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

	}

	void	MultiplyNode::input_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::get_slot_type_name(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::get_slot_type_name(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::get_slot_type_name(m_output_slot_type[0]);

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

	void	MultiplyNode::output_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	MultiplyNode::shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "MultiplyNode_" + NodeFunction::get_type(m_input_slot_type[0]);
		m_out_str[0] = "MultiplyNode_out" + std::to_string(m_ID);

		NodeFunction::set_slot_data(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::set_slot_data(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::get_type(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Multiply_" + NodeFunction::get_type(m_input_slot_type[0]) + "(";

		str_set(nodes_ptr, links);
	}
	std::string	MultiplyNode::get_function_def_str()
	{
		return
			"void Multiply_" + NodeFunction::get_type(m_input_slot_type[0]) + "(" + NodeFunction::get_type(m_input_slot_type[0]) + " A," + NodeFunction::get_type(m_input_slot_type[0]) + " B, out " + NodeFunction::get_type(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = A * B;\n"
			"}\n";
	};

	DivideNode::DivideNode()
	{
		init();
	}
	DivideNode::DivideNode(int id, const math::FVector2& pos)
		:NodeBase("Divide_float", id, pos, size, 2, 1)
	{
		init();
	}
	DivideNode::~DivideNode()
	{
	}
	void	DivideNode::init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	DivideNode::input_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::get_slot_type_name(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::get_slot_type_name(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::get_slot_type_name(m_output_slot_type[0]);

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

	void	DivideNode::output_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	DivideNode::shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "DivideNode_" + NodeFunction::get_type(m_input_slot_type[0]);
		m_out_str[0] = "DivideNode_out" + std::to_string(m_ID);

		NodeFunction::set_slot_data(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::set_slot_data(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::get_type(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Divide_" + NodeFunction::get_type(m_input_slot_type[0]) + "(";

		str_set(nodes_ptr, links);
	}
	std::string	DivideNode::get_function_def_str()
	{
		return
			"void Divide_" + NodeFunction::get_type(m_input_slot_type[0]) + "(" + NodeFunction::get_type(m_input_slot_type[0]) + " A," + NodeFunction::get_type(m_input_slot_type[0]) + " B, out " + NodeFunction::get_type(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = A / B;\n"
			"}\n";
	};

	PowerNode::PowerNode()
	{
		init();
	}
	PowerNode::PowerNode(int id, const math::FVector2& pos)
		:NodeBase("Power_float", id, pos, size, 2, 1)
	{
		init();
	}
	PowerNode::~PowerNode()
	{
	}
	void	PowerNode::init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("A");
		m_input_name.push_back("B");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	PowerNode::input_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "A" + NodeFunction::get_slot_type_name(m_input_slot_type[0]);
		m_input_name[1] = "B" + NodeFunction::get_slot_type_name(m_input_slot_type[1]);
		m_output_name[0] = "Out" + NodeFunction::get_slot_type_name(m_output_slot_type[0]);

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

	void	PowerNode::output_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	PowerNode::shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "PowerNode_" + NodeFunction::get_type(m_input_slot_type[0]);
		m_out_str[0] = "PowerNode_out" + std::to_string(m_ID);

		NodeFunction::set_slot_data(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::set_slot_data(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::get_type(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    Power_" + NodeFunction::get_type(m_input_slot_type[0]) + "(";

		str_set(nodes_ptr, links);
	}
	std::string	PowerNode::get_function_def_str()
	{
		return
			"void Power_" + NodeFunction::get_type(m_input_slot_type[0]) + "(" + NodeFunction::get_type(m_input_slot_type[0]) + " A," + NodeFunction::get_type(m_input_slot_type[0]) + " B, out " + NodeFunction::get_type(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = pow(A, B);\n"
			"}\n";
	};


	SquareRootNode::SquareRootNode()
	{
		init();
	}
	SquareRootNode::SquareRootNode(int id, const math::FVector2& pos)
		:NodeBase("SquareRoot_float", id, pos, size, 1, 1)
	{
		init();
	}
	SquareRootNode::~SquareRootNode()
	{
	}
	void	SquareRootNode::init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	SquareRootNode::input_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::get_slot_type_name(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::get_slot_type_name(m_output_slot_type[0]);

		if (!m_is_input[0])
		{
			switch (m_input_slot_type[0])
			{
			case SLOT_TYPE::VECTOR4:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 3)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[0])), In.w);
			case SLOT_TYPE::VECTOR3:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 2)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[0]) - 1), In.z);
			case SLOT_TYPE::VECTOR2:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 1)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[0]) - 2), In.y);
			case SLOT_TYPE::VECTOR1:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]))		*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(m_input_slot_type[0]) - 3), In.x);
				break;
			}
		}
	}

	void	SquareRootNode::output_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	SquareRootNode::shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "SquareRoot_" + NodeFunction::get_type(m_input_slot_type[0]);
		m_out_str[0] = "SquareRoot_out" + std::to_string(m_ID);

		NodeFunction::set_slot_data(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::get_type(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    SquareRoot_" + NodeFunction::get_type(m_input_slot_type[0]) + "(";

		str_set(nodes_ptr, links);
	}
	std::string	SquareRootNode::get_function_def_str()
	{
		return
			"void SquareRoot_" + NodeFunction::get_type(m_input_slot_type[0]) + "(" + NodeFunction::get_type(m_input_slot_type[0]) + " In, out " + NodeFunction::get_type(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = sqrt(In);\n"
			"}\n";
	};
}