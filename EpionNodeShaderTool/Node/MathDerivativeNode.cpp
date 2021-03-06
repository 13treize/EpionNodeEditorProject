#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"MathDerivativeNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::DDXNode)
CEREAL_REGISTER_TYPE(epion::Node::DDYNode)
CEREAL_REGISTER_TYPE(epion::Node::DDXYNode)

namespace	epion::Node
{
	DDXNode::DDXNode()
		:NodeBase( 1, 1)
	{
		Init();
	}
	DDXNode::DDXNode(int id, const math::FVector2& pos)
		:NodeBase("DDX_float", id, pos, 1, 1)
	{
		Init();
	}
	DDXNode::~DDXNode()
	{
	}
	void	DDXNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	DDXNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)
		{
			switch (m_input_slot_type[0])
			{
			case SLOT_TYPE::VECTOR4:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 3)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0])), m_in.w);
			case SLOT_TYPE::VECTOR3:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 2)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 1), m_in.z);
			case SLOT_TYPE::VECTOR2:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 1)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 2), m_in.y);
			case SLOT_TYPE::VECTOR1:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]))		*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 3), m_in.x);
				break;
			}
		}
	}

	void	DDXNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "DDX_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		TypeSet(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		StrSet(nodes_ptr, links);
	}
	std::string	DDXNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = ddx(In);\n"
			"}\n";
	}

	DDYNode::DDYNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	DDYNode::DDYNode(int id, const math::FVector2& pos)
		:NodeBase("DDY_float", id, pos, 1, 1)
	{
		Init();
	}
	DDYNode::~DDYNode()
	{
	}
	void	DDYNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	DDYNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)
		{
			switch (m_input_slot_type[0])
			{
			case SLOT_TYPE::VECTOR4:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 3)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0])), m_in.w);
			case SLOT_TYPE::VECTOR3:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 2)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 1), m_in.z);
			case SLOT_TYPE::VECTOR2:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 1)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 2), m_in.y);
			case SLOT_TYPE::VECTOR1:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]))		*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 3), m_in.x);
				break;
			}
		}
	}

	void	DDYNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "DDY_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		TypeSet(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		StrSet(nodes_ptr, links);
	}
	std::string	DDYNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = ddy(In);\n"
			"}\n";
	}

	DDXYNode::DDXYNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	DDXYNode::DDXYNode(int id, const math::FVector2& pos)
		:NodeBase("DDXY_float", id, pos, 1, 1)
	{
		Init();
	}
	DDXYNode::~DDXYNode()
	{
	}
	void	DDXYNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	DDXYNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		m_input_name[0] = "In" + NodeFunction::GetSlotTypeName(m_input_slot_type[0]);
		m_output_name[0] = "Out" + NodeFunction::GetSlotTypeName(m_output_slot_type[0]);

		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)
		{
			switch (m_input_slot_type[0])
			{
			case SLOT_TYPE::VECTOR4:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 3)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0])), m_in.w);
			case SLOT_TYPE::VECTOR3:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 2)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 1), m_in.z);
			case SLOT_TYPE::VECTOR2:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]) - 1)	*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 2), m_in.y);
			case SLOT_TYPE::VECTOR1:	NodeFunction::SetInputSlotFloat(m_input_pos[0], (static_cast<float>(m_input_slot_type[0]))		*SLOT_INPUT_POS_X, StringConverter::GetSpace(static_cast<int>(m_input_slot_type[0]) - 3), m_in.x);
				break;
			}
		}
	}

	void	DDXYNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "DDXY_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		TypeSet(nodes_ptr, links);
		m_output_slot_type[0] = m_input_slot_type[0];
		m_function_call_str = "    " + NodeFunction::GetType(m_output_slot_type[0]) + " " + m_out_str[0] + ";\n";
		m_function_call_str += "    " + m_Name + "(";

		StrSet(nodes_ptr, links);
	}
	std::string	DDXYNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = ddxy(In);\n"
			"}\n";
	}

}
