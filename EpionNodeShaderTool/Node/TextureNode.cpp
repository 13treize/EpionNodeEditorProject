#include	"../All.h"
#include	"../epion.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"NodeData.h"
#include	"TextureNode.h"

namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::SamplerStateNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::SamplerTexture2DNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::Texture2DNode)

namespace	epion::NodeCustom
{
#pragma region SamplerState
	SamplerStateNode::SamplerStateNode()
		: NodeBase(1, 1)
	{
		Init();
	}

	SamplerStateNode::SamplerStateNode(int id, const math::FVector2& pos)
		: NodeBase("SamplerState", id, pos, 1, 1)
	{
		Init();
	}

	SamplerStateNode::~SamplerStateNode()
	{
	}
	void SamplerStateNode::Init()
	{
		m_slot_no = 0;
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("Slot");

		m_output_slot_type.push_back(SLOT_TYPE::SAMPLERSTATE);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::VARIABLE;
	}
	void SamplerStateNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
	}

	void SamplerStateNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(static_cast<int>(m_slot_no));
		m_out_str[0] = "SamplerStates" + m_input_str[0];
		//m_function_call_str = m_out_str[0];
		//m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		//str_check(nodes_ptr, links);
	}

	std::string SamplerStateNode::GetFunctionDefStr()
	{
		return "SamplerState " + m_out_str[0] + " : register(s" + m_input_str[0] + ");\n";
	}
#pragma endregion

#pragma region SamplerTexture2D
	SamplerTexture2DNode::SamplerTexture2DNode()
		:NodeBase( 3, 1)
	{
		Init();
	}

	SamplerTexture2DNode::SamplerTexture2DNode(int id, const epion::math::FVector2& pos)
		:NodeBase("SamplerTexture2D", id, pos, 3, 1)
	{
		Init();
	}

	SamplerTexture2DNode::~SamplerTexture2DNode()
	{
	}

	void SamplerTexture2DNode::Init()
	{
		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::TEXTURE2D, SLOT_TYPE::SAMPLERSTATE
		};
		m_input_name =
		{
			"UV", "Texture","SS",
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR4);
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::NORMAL;
	}

	void SamplerTexture2DNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotTexture2D(m_input_pos[1]);
		if (!m_is_input[2])	NodeFunction::SetInputSlotSamplerState(m_input_pos[2]);
	}

	void	SamplerTexture2DNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr4(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		str_check(nodes_ptr, links);
	}

	std::string	SamplerTexture2DNode::GetFunctionDefStr()
	{
		return
		"void SamplerTexture2D(float2 uv, Texture2D t, SamplerState s, out float4 Out)\n"
		"{\n"
		"	Out = t.Sample(s, uv);\n"
		"}";
	//	return "Texture2D "+m_Name+": register";
	}
#pragma endregion

#pragma region Texture2D
	Texture2DNode::Texture2DNode()
		: NodeBase(1, 1)
	{
		Init();
	}

	Texture2DNode::Texture2DNode(int id, const math::FVector2& pos)
		: NodeBase("Texture2D", id, pos, 1, 1)
	{
		Init();
	}

	Texture2DNode::~Texture2DNode()
	{
	}
	void Texture2DNode::Init()
	{
		m_slot_no = 0;
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_name.push_back("Slot");

		m_output_slot_type.push_back(SLOT_TYPE::TEXTURE2D);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::VARIABLE;
	}
	void Texture2DNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
	}

	void Texture2DNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = std::to_string(static_cast<int>(m_slot_no));
		m_out_str[0] = "tex" + m_input_str[0];
	}

	std::string Texture2DNode::GetFunctionDefStr()
	{
		return "Texture2D " + m_out_str[0] + " : register(t" + m_input_str[0] + ");\n";
	}
#pragma endregion

}