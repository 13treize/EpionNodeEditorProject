#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"MathAdvancedNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::AbsoluteNode)
CEREAL_REGISTER_TYPE(epion::Node::LengthNode)
CEREAL_REGISTER_TYPE(epion::Node::ModuloNode)
CEREAL_REGISTER_TYPE(epion::Node::NegateNode)
CEREAL_REGISTER_TYPE(epion::Node::NormalizeNode)
CEREAL_REGISTER_TYPE(epion::Node::PosterizeNode)
CEREAL_REGISTER_TYPE(epion::Node::ReciprocalSquareRootNode)

namespace	epion::Node
{
#pragma region Absolute
	AbsoluteNode::AbsoluteNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	AbsoluteNode::AbsoluteNode(int id, const math::FVector2& pos)
		:NodeBase("Absolute", id, pos, 1, 1)
	{
		Init();
	}
	AbsoluteNode::~AbsoluteNode()
	{
	}
	void	AbsoluteNode::Init()
	{
		m_in = { 0.0f, 0.0f, 0.0f, 0.0f};

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	AbsoluteNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	AbsoluteNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Absolute_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);

		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	AbsoluteNode::GetFunctionDefStr()
	{
		return
			"void "+m_Name+"(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = abs(In);\n"
			"}\n";
	}
#pragma endregion

#pragma region Length
	LengthNode::LengthNode()
		:NodeBase( 1, 1)
	{
		Init();
	}
	LengthNode::LengthNode(int id, const math::FVector2& pos)
		:NodeBase("Length", id, pos, 1, 1)
	{
		Init();
	}
	LengthNode::~LengthNode()
	{
	}
	void	LengthNode::Init()
	{
		m_in = { 0.0f,0.0f ,0.0f ,0.0f };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	LengthNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	LengthNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Length_" + NodeFunction::GetType(m_input_slot_type[0]);
		m_out_str[0] = m_Name + "_out" + std::to_string(m_ID);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);
		m_output_slot_type[0] = SLOT_TYPE::VECTOR1;
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
		m_output_slot_type[0] = SLOT_TYPE::VECTOR1;

	}
	std::string	LengthNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out float Out)\n"
			"{\n"
			"	Out = length(In);\n"
			"}\n";
	}
#pragma endregion

#pragma region Modulo
	ModuloNode::ModuloNode()
		:NodeBase( 2, 1)
	{
		Init();
	}
	ModuloNode::ModuloNode(int id, const math::FVector2& pos)
		:NodeBase("Modulo", id, pos, 2, 1)
	{
		Init();
	}
	ModuloNode::~ModuloNode()
	{
	}

	void ModuloNode::Init()
	{
		m_num[0] = { 0.0f, 0.0f ,0.0f ,0.0f };
		m_num[1] = { 0.0f, 0.0f ,0.0f ,0.0f };
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

	void ModuloNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[1], m_input_slot_type[1], 1);
	}

	void ModuloNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Modulo_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string ModuloNode::GetFunctionDefStr()
	{
		return
			"void "+ m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " A," + NodeFunction::GetType(m_input_slot_type[0]) + " B, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = fmod(A, B);\n"
			"}\n";
	};
#pragma endregion

#pragma region Negate
	NegateNode::NegateNode()
		:NodeBase( 1, 1)
	{
		Init();
	}
	NegateNode::NegateNode(int id, const math::FVector2& pos)
		:NodeBase("Negate", id, pos, 1, 1)
	{
		Init();
	}
	NegateNode::~NegateNode()
	{
	}
	void	NegateNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	NegateNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	NegateNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Negate_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}
	std::string	NegateNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	Out = -1* In;\n"
			"}\n";
	}
#pragma endregion

#pragma region Normalize
	NormalizeNode::NormalizeNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	NormalizeNode::NormalizeNode(int id, const math::FVector2& pos)
		:NodeBase("Normalize", id, pos, 1, 1)
	{
		Init();
	}
	NormalizeNode::~NormalizeNode()
	{
	}
	void	NormalizeNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	NormalizeNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	NormalizeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Normalize" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}

	std::string	NormalizeNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"    Out = normalize(In);\n"
			"}\n";
	}
#pragma endregion

#pragma region Posterize
	PosterizeNode::PosterizeNode()
		:NodeBase(2, 1)
	{
		Init();
	}
	PosterizeNode::PosterizeNode(int id, const math::FVector2& pos)
		:NodeBase("Posterize", id, pos, 2, 1)
	{
		Init();
	}
	PosterizeNode::~PosterizeNode()
	{
	}

	void	PosterizeNode::Init()
	{
		m_num[0] = { 0.0,0.0 ,0.0 ,0.0 };
		m_num[1] = { 0.0,0.0 ,0.0 ,0.0 };
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name.push_back("In");
		m_input_name.push_back("Step");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	PosterizeNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_num[0], m_input_slot_type[0], 0);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[1], m_num[1], m_input_slot_type[1], 1);
	}

	void	PosterizeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "Posterize_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_num[0], m_input_str[0], m_input_slot_type[0]);
		NodeFunction::SetSlotData(m_num[1], m_input_str[1], m_input_slot_type[1]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}

	std::string	PosterizeNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In," + NodeFunction::GetType(m_input_slot_type[0]) + " Steps, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"	 Out = floor(In / (1 / Steps)) * (1 / Steps);\n"
			"}\n";
	}
#pragma endregion

#pragma region ReciprocalSquareRoot
	ReciprocalSquareRootNode::ReciprocalSquareRootNode()
		:NodeBase(1, 1)
	{
		Init();
	}
	ReciprocalSquareRootNode::ReciprocalSquareRootNode(int id, const math::FVector2& pos)
		:NodeBase("ReciprocalSquareRoot", id, pos, 1, 1)
	{
		Init();
	}
	ReciprocalSquareRootNode::~ReciprocalSquareRootNode()
	{
	}
	void	ReciprocalSquareRootNode::Init()
	{
		m_in = { 0.0,0.0 ,0.0 ,0.0 };

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("In");

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::DYNAMIC;
	}

	void	ReciprocalSquareRootNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotDynamic(m_input_pos[0], m_in, m_input_slot_type[0], 0);
	}

	void	ReciprocalSquareRootNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_Name = "ReciprocalSquareRootNode_" + NodeFunction::GetType(m_input_slot_type[0]);

		NodeFunction::SetSlotData(m_in, m_input_str[0], m_input_slot_type[0]);

		m_output_slot_type[0] = m_input_slot_type[0];
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutDynamic(m_out_str[0], m_output_slot_type[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);

		m_dynamic_slot_type = m_input_slot_type[0];
		StrCheck(nodes_ptr, links);
	}

	std::string	ReciprocalSquareRootNode::GetFunctionDefStr()
	{
		return
			"void " + m_Name + "(" + NodeFunction::GetType(m_input_slot_type[0]) + " In, out " + NodeFunction::GetType(m_input_slot_type[0]) + " Out)\n"
			"{\n"
			"    Out = rsqrt(In);\n"
			"}\n";
	}
#pragma endregion
}