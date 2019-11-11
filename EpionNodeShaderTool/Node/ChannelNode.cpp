//#include	"../All.h"
//#include	<cereal/cereal.hpp>
//#include	<cereal/types/polymorphic.hpp>
//#include	"../../../imgui\\imgui.h"
//#include	"../../../imgui\\imgui_internal.h"
//#include	"NodeData.h"
//#include	"ChannelNode.h"
//#include	"../epion_string.h"
//
//namespace
//{
//	const ImVec2	size(0, 0);
//}
//
//CEREAL_REGISTER_TYPE(epion::NodeCustom::CombineNode)
//
//
//namespace	epion::NodeCustom
//{
//	CombineNode::CombineNode()
//	{
//		Init();
//	}
//
//	CombineNode::CombineNode(int id, const math::FVector2& pos)
//		:NodeBase("Combine", id, pos, size, 4, 3)
//	{
//		Init();
//	}
//
//	CombineNode::~CombineNode()
//	{
//	}
//
//	void CombineNode::Init()
//	{
//		R = 0;
//		G = 0;
//		B = 0;
//		A = 0;
//
//		m_input_slot_type =
//		{
//			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,
//		};
//		m_input_name =
//		{
//			"R","G","B","A"
//		};
//
//		m_output_slot_type =
//		{
//			SLOT_TYPE::VECTOR4,	SLOT_TYPE::VECTOR3,	SLOT_TYPE::VECTOR2,
//		};
//
//		m_output_name =
//		{
//			"RGBA","RGB","RG",
//		};
//		m_node_type = NODE_TYPE::NORMAL;
//	}
//	void	CombineNode::Update(ImVec2 offset, ImDrawList*	draw_list)
//	{
//		DrawUpdate(offset, draw_list);
//
//		draw_list->ChannelsSetCurrent(1);
//		if (!m_is_input[0])	NodeFunction::SetInputSlotFloat(m_input_pos[0], SLOT_INPUT_POS_X, StringConverter::get_space(0), R);
//		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), G);
//		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), B);
//		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3], SLOT_INPUT_POS_X, StringConverter::get_space(3), A);
//	}
//
//	void	CombineNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
//	{
//		o_update(offset, draw_list);
//	}
//
//	void	CombineNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
//	{
//		m_input_str[0] = std::to_string(R);
//		m_input_str[1] = std::to_string(G);
//		m_input_str[2] = std::to_string(B);
//		m_input_str[3] = std::to_string(A);
//
//		m_out_str[0] = "Ch_out" + std::to_string(m_ID);
//
//		m_function_call_str = "    float3 " + m_out_str[0] + ";\n";
//		m_function_call_str += "   Checkerboard_float(";
//		str_set(nodes_ptr, links);
//	}
//
//	std::string	CombineNode::GetFunctionDefStr()
//	{
//		return
//			"void Checkerboard_float(float2 UV, float3 ColorA, float3 ColorB, float2 Frequency, out float3 Out)\n"
//			"{\n"
//			"    UV = (UV.xy + 0.5) * Frequency;\n"
//			"    float4 derivatives = float4(ddx(UV), ddy(UV));\n"
//			"    float2 duv_length = sqrt(float2(dot(derivatives.xz, derivatives.xz), dot(derivatives.yw, derivatives.yw)));\n"
//			"    float width = 1.0;\n"
//			"    float2 distance3 = 4.0 * abs(frac(UV + 0.25) - 0.5) - width;\n"
//			"    float2 scale = 0.35 / duv_length.xy;\n"
//			"    float freqLimiter = sqrt(clamp(1.1f - max(duv_length.x, duv_length.y), 0.0, 1.0));\n"
//			"    float2 vector_alpha = clamp(distance3 * scale.xy, -1.0, 1.0);\n"
//			"    float alpha = saturate(0.5f + 0.5f * vector_alpha.x * vector_alpha.y * freqLimiter);\n"
//			"    Out = lerp(ColorA, ColorB, alpha.xxx);\n"
//			"}\n";
//	}
//
//}