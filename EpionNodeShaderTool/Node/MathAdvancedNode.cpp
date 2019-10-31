#include	"../All.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeData.h"
#include	"MathAdvancedNode.h"
#include	"../epion_string.h"
namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::AbsoluteNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::LengthNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::ModuloNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::NegateNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::NormalizeNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::PosterizeNode)

namespace	epion::NodeCustom
{
	AbsoluteNode::AbsoluteNode()
	{
		Init();
	}
	AbsoluteNode::AbsoluteNode(int id, const math::FVector2& pos)
		:NodeBase("Absolute_float", id, pos, size, 1, 1)
	{
		Init();
	}
	AbsoluteNode::~AbsoluteNode()
	{
	}
	void	AbsoluteNode::Init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
		m_dynamic_slot_type = SLOT_TYPE::VECTOR1;

	}

	void	AbsoluteNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotDynamic(m_input_pos[0], In, m_input_slot_type[0], 0);
		}
	}

	void	AbsoluteNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	AbsoluteNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Absolute_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name +"_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name +"(";

		str_set(nodes_ptr, links);
	}
	std::string	AbsoluteNode::get_function_def_str()
	{
		return
			"void "+m_Name+"(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = abs(In);\n"
			"}\n";
	}

	LengthNode::LengthNode()
	{
		Init();
	}
	LengthNode::LengthNode(int id, const math::FVector2& pos)
		:NodeBase("Length_float", id, pos, size, 1, 1)
	{
		Init();
	}
	LengthNode::~LengthNode()
	{
	}
	void	LengthNode::Init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	LengthNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

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

	void	LengthNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	LengthNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Length_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] =SLOT_TYPE::VECTOR1;
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}
	std::string	LengthNode::get_function_def_str()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out float Out)\n"
			"{\n"
			"	Out = length(In);\n"
			"}\n";
	}

	ModuloNode::ModuloNode()
	{
		Init();
	}
	ModuloNode::ModuloNode(int id, const math::FVector2& pos)
		:NodeBase("Modulo_float", id, pos, size, 2, 1)
	{
		Init();
	}
	ModuloNode::~ModuloNode()
	{
	}

	void	ModuloNode::Init()
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

	void	ModuloNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
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

	void	ModuloNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	ModuloNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Modulo_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Modulo_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}
	std::string	ModuloNode::get_function_def_str()
	{
		return
			"void "+ m_Name +  "(" + NodeFunction::GetType(m_input_slot_type[0]) + " A," + NodeFunction::GetType(m_input_slot_type[0]) + " B, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = fmod(A, B);\n"
			"}\n";
	};

	NegateNode::NegateNode()
	{
		Init();
	}
	NegateNode::NegateNode(int id, const math::FVector2& pos)
		:NodeBase("Negate_float", id, pos, size, 1, 1)
	{
		Init();
	}
	NegateNode::~NegateNode()
	{
	}
	void	NegateNode::Init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	NegateNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

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

	void	NegateNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	NegateNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Negate_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}
	std::string	NegateNode::get_function_def_str()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = -1* In;\n"
			"}\n";
	}

	NormalizeNode::NormalizeNode()
	{
		Init();
	}
	NormalizeNode::NormalizeNode(int id, const math::FVector2& pos)
		:NodeBase("Normalize_float", id, pos, size, 1, 1)
	{
		Init();
	}
	NormalizeNode::~NormalizeNode()
	{
	}
	void	NormalizeNode::Init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	NormalizeNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

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

	void	NormalizeNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	NormalizeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Negate_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}

	std::string	NormalizeNode::get_function_def_str()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = normalize(In);\n"
			"}\n";
	}

	PosterizeNode::PosterizeNode()
	{
		Init();
	}
	PosterizeNode::PosterizeNode(int id, const math::FVector2& pos)
		:NodeBase("Posterize_float", id, pos, size, 2, 1)
	{
		Init();
	}
	PosterizeNode::~PosterizeNode()
	{
	}

	void	PosterizeNode::Init()
	{
		Num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		Num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("In");
		m_input_name.push_back("Step");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	PosterizeNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
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

	void	PosterizeNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	PosterizeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Posterize_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = "Posterize_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(Num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(Num[1], m_input_str[1], m_input_slot_type[1]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}
	std::string	PosterizeNode::get_function_def_str()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In," + NodeFunction::GetType(m_input_slot_type[0]) + " Steps, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	 Out = floor(In / (1 / Steps)) * (1 / Steps);\n"
			"}\n";
	}

	ReciprocalSquareRootNode::ReciprocalSquareRootNode()
	{
		Init();
	}
	ReciprocalSquareRootNode::ReciprocalSquareRootNode(int id, const math::FVector2& pos)
		:NodeBase("ReciprocalSquareRoot_float", id, pos, size, 1, 1)
	{
		Init();
	}
	ReciprocalSquareRootNode::~ReciprocalSquareRootNode()
	{
	}
	void	ReciprocalSquareRootNode::Init()
	{
		In = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	ReciprocalSquareRootNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

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

	void	ReciprocalSquareRootNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	ReciprocalSquareRootNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "ReciprocalSquareRootNode_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(In, m_input_str[0], m_input_slot_type[0]);

		type_set(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		str_set(nodes_ptr, links);
	}

	std::string	ReciprocalSquareRootNode::get_function_def_str()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"    Out = rsqrt(In);\n"
			"}\n";
	}


}