#include	"../All.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"ProceduralNode.h"
#include	"../epion_string.h"

namespace
{
	const ImVec2	size(0, 0);
	bool open_popup[2];
}

//TODO repplenode
//float2 p = (input.uv * 2.0 - 1.0);
//float3 col = float3(1.0,1.0,1.0);
//float2 centre = float2(0.0, 0.0);
//float s = sin(10.0 * distance(p, centre));
//float3 c =s;
//col = c;
CEREAL_REGISTER_TYPE(epion::NodeCustom::CheckerboardNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::EllipseNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::PolygonNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::RoundedRectangleNode)

namespace	epion::NodeCustom
{
	CheckerboardNode::CheckerboardNode()
	{
		Init();
	}

	CheckerboardNode::CheckerboardNode(int id, const math::FVector2& pos)
		:NodeBase("Checkerboard", id, pos, size, 4, 1)
	{
		Init();
	}

	CheckerboardNode::~CheckerboardNode()
	{
	}
	void CheckerboardNode::Init()
	{
		UV = { 0,0 };
		ColorA = { 0,0,0 };
		ColorB = { 1,1,1 };
		Frequency = { 1,	1 };

		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::COLOR, SLOT_TYPE::COLOR, SLOT_TYPE::VECTOR2,
		};
		m_input_name =
		{
			"UV",	"ColorA",	"ColorB",	"Frequency"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR3);
		m_output_name.push_back("Out");

		m_color_picker[0].Init("1", "ColorA");
		m_color_picker[1].Init("2", "ColorB");

		m_node_type = NODE_TYPE::NORMAL;
	}
	void	CheckerboardNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		ImVec2	rect_pos[sizeof(m_inputs_count)];
		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	m_color_picker[0].SetInputSlotColor2(m_input_pos[1], open_popup[0], ColorA, 1);
		if (!m_is_input[2])	m_color_picker[1].SetInputSlotColor2(m_input_pos[2], open_popup[1], ColorB, 2);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat2(m_input_pos[3], Frequency, 3);
	}

	void	CheckerboardNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	CheckerboardNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString3(ColorA);
		m_input_str[2] = NodeFunction::SetInputToString3(ColorB);
		m_input_str[3] = NodeFunction::SetInputToString2(Frequency);


		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr3(m_out_str[0]);
		m_function_call_str += "    Checkerboard(";
		str_set(nodes_ptr, links);
	}

	std::string	CheckerboardNode::GetFunctionDefStr()
	{
		return
			"void Checkerboard(float2 UV, float3 ColorA, float3 ColorB, float2 Frequency, out float3 Out)\n"
			"{\n"
			"    UV = (UV.xy + 0.5) * Frequency;\n"
			"    float4 derivatives = float4(ddx(UV), ddy(UV));\n"
			"    float2 duv_length = sqrt(float2(dot(derivatives.xz, derivatives.xz), dot(derivatives.yw, derivatives.yw)));\n"
			"    float width = 1.0;\n"
			"    float2 distance3 = 4.0 * abs(frac(UV + 0.25) - 0.5) - width;\n"
			"    float2 scale = 0.35 / duv_length.xy;\n"
			"    float freqLimiter = sqrt(clamp(1.1f - max(duv_length.x, duv_length.y), 0.0, 1.0));\n"
			"    float2 vector_alpha = clamp(distance3 * scale.xy, -1.0, 1.0);\n"
			"    float alpha = saturate(0.5f + 0.5f * vector_alpha.x * vector_alpha.y * freqLimiter);\n"
			"    Out = lerp(ColorA, ColorB, alpha.xxx);\n"
			"}\n";
	}

	EllipseNode::EllipseNode()
	{
		Init();
	}

	EllipseNode::EllipseNode(int id, const math::FVector2& pos)
		:NodeBase("Ellipse", id, pos, size, 3, 1)
	{
		Init();
	}

	EllipseNode::~EllipseNode()
	{
	}

	void	EllipseNode::Init()
	{
		UV = { 0,0 };
		Width = 1.0f;
		Height = 1.0f;

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);

		//node	slot name
		m_input_name.push_back("UV(2)");
		m_input_name.push_back("Width(1)");
		m_input_name.push_back("Height(1)");

		m_output_name.push_back("Out(1)");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	EllipseNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), Width);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), Height);
	}

	void	EllipseNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	EllipseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(Width);
		m_input_str[2] = std::to_string(Height);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    Ellipse(";
		str_check(nodes_ptr, links);
	}
	//void Ellipse(float2 UV, float2 pos, float Width, float Height, out float Out)
	//{
	//	float d = length((UV * 2 + pos - 1.5) / float2(Width, Height));
	//	Out = saturate((1 - d) / fwidth(d));
	//}
	std::string	EllipseNode::GetFunctionDefStr()
	{
		return
			"void Ellipse(float2 UV, float Width, float Height, out float Out)\n"
			"{\n"
			"    float d = length((UV * 2 - 1) / float2(Width, Height));\n"
			"    Out = saturate((1 - d) / fwidth(d));\n"
			"}\n";
	}

	PolygonNode::PolygonNode()
	{
		Init();
	}

	PolygonNode::PolygonNode(int id, const math::FVector2& pos)
		:NodeBase("Polygon", id, pos, size, 4, 1)
	{
		Init();
	}

	PolygonNode::~PolygonNode()
	{
	}

	void	PolygonNode::Init()
	{
		UV = { 0,0 };
		Sides = 4.0f;
		Width = 1.0f;
		Height = 1.0f;

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);

		//node	slot name
		m_input_name.push_back("UV(2)");
		m_input_name.push_back("Sides(1)");
		m_input_name.push_back("Width(1)");
		m_input_name.push_back("Height(1)");

		m_output_name.push_back("Out(1)");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	PolygonNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (m_inputs_count != 0)
		{
			if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
			if (!m_is_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), Sides);
			if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), Width);
			if (!m_is_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3], SLOT_INPUT_POS_X, StringConverter::get_space(3), Height);
		}
	}

	void	PolygonNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	PolygonNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(Sides);
		m_input_str[2] = std::to_string(Width);
		m_input_str[3] = std::to_string(Height);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    Polygon(";
		str_set(nodes_ptr, links);
	}
	std::string	PolygonNode::GetFunctionDefStr()
	{
		return
			"void Polygon(float2 UV, float Sides, float Width, float Height, out float Out)\n"
			"{\n"
			"    float pi = 3.14159265359;\n"
			"    float aWidth = Width * cos(pi / Sides);\n"
			"    float aHeight = Height * cos(pi / Sides);\n"
			"    float2 uv = (UV * 2 - 1) / float2(aWidth, aHeight);\n"
			"    uv.y *= -1;\n"
			"    float pCoord = atan2(uv.x, uv.y);\n"
			"    float r = 2 * pi / Sides;\n"
			"    float distance = cos(floor(0.5 + pCoord / r) * r - pCoord) * length(uv);\n"
			"    Out = saturate((1 - distance) / fwidth(distance));\n"
			"}\n";
	}

	RoundedRectangleNode::RoundedRectangleNode()
	{
		Init();
	}

	RoundedRectangleNode::RoundedRectangleNode(int id, const math::FVector2& pos)
		:NodeBase("RoundedRectangle", id, pos, size, 4, 1)
	{
		Init();
	}

	RoundedRectangleNode::~RoundedRectangleNode()
	{
	}

	void	RoundedRectangleNode::Init()
	{
		UV = { 0,0 };
		Width = 1.0f;
		Height = 1.0f;
		Radius = 1.0f;

		m_input_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);

		//node	slot name
		m_input_name.push_back("UV(2)");
		m_input_name.push_back("Width(1)");
		m_input_name.push_back("Height(1)");
		m_input_name.push_back("Radius(1)");

		m_output_name.push_back("Out(1)");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	RoundedRectangleNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), Width);
		}

		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), Height);
		}

		if (!m_is_input[3])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[3], SLOT_INPUT_POS_X, StringConverter::get_space(3), Radius);
		}


	}

	void	RoundedRectangleNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	RoundedRectangleNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "RoundedRectangle_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(Width);
		m_input_str[2] = std::to_string(Height);
		m_input_str[3] = std::to_string(Radius);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    RoundedRectangle(";
		str_check(nodes_ptr, links);
	}
	std::string	RoundedRectangleNode::GetFunctionDefStr()
	{
		return
			"void RoundedRectangle(float2 UV, float Width, float Height, float Radius, out float Out)\n"
			"{\n"
			"    Radius = max(min(min(abs(Radius * 2), abs(Width)), abs(Height)), 1e-5);\n"
			"    float2 uv = abs(UV * 2 - 1) - float2(Width, Height) + Radius;\n"
			"    float d = length(max(0, uv)) / Radius;\n"
			"    Out = saturate((1 - d) / fwidth(d));\n"
			"}\n";
	}

}