#include	"../All.h"
#include	"../epion.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"ProceduralNode.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::CheckerboardNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::EllipseNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::HexagonNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::PolygonNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::RippleNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::RoundedRectangleNode)

namespace	epion::NodeCustom
{
#pragma region Checkerboard
	CheckerboardNode::CheckerboardNode()
		:NodeBase(4, 1)
	{
		Init();
	}

	CheckerboardNode::CheckerboardNode(int id, const math::FVector2& pos)
		:NodeBase("Checkerboard", id, pos, 4, 1)
	{
		Init();
	}

	CheckerboardNode::~CheckerboardNode()
	{
	}
	void CheckerboardNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_colora = { 0.0f, 0.0f, 0.0f };
		m_colorb = { 1.0f, 1.0f,1.0f };
		m_frequency = { 1.0f, 1.0f };

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
		m_open_popup[0] = false;
		m_open_popup[1] = false;

		m_node_type = NODE_TYPE::NORMAL;
	}
	void	CheckerboardNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_slot_input[1])	m_color_picker[0].SetInputSlotColor2(m_input_pos[1], m_open_popup[0], m_colora, 1);
		if (!m_is_slot_input[2])	m_color_picker[1].SetInputSlotColor2(m_input_pos[2], m_open_popup[1], m_colorb, 2);
		if (!m_is_slot_input[3])	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_frequency, 3);
	}

	void	CheckerboardNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString3(m_colora);
		m_input_str[2] = NodeFunction::SetInputToString3(m_colorb);
		m_input_str[3] = NodeFunction::SetInputToString2(m_frequency);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr3(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrSet(nodes_ptr, links);
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
#pragma endregion

#pragma region Ellipse
	EllipseNode::EllipseNode()
		:NodeBase(3, 1)
	{
		Init();
	}

	EllipseNode::EllipseNode(int id, const math::FVector2& pos)
		:NodeBase("Ellipse", id, pos, 3, 1)
	{
		Init();
	}

	EllipseNode::~EllipseNode()
	{
	}

	void	EllipseNode::Init()
	{
		m_uv = { 0.0f,0.0f };
		m_width = 1.0f;
		m_height = 1.0f;

		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);

		//node	slot name
		m_input_name =
		{
			"UV", "Width", "Height"
		};
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	EllipseNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_slot_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), m_width);
		if (!m_is_slot_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), m_height);
	}

	void	EllipseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_width);
		m_input_str[2] = std::to_string(m_height);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
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
#pragma endregion

	//TODO Ç±Ç¢Ç¬êRãc
#pragma region Hexagon
	HexagonNode::HexagonNode()
		:NodeBase(2, 4)
	{
		Init();
	}
	HexagonNode::HexagonNode(int id, const math::FVector2& pos)
		:NodeBase("Hexagon", id, pos, 2, 4)
	{
		Init();
	}

	HexagonNode::~HexagonNode()
	{
	}

	void	HexagonNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_scale = 1.0f;
		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR1
		};
		m_output_slot_type =
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR2,
		};

		//node	slot name
		m_input_name =
		{
			"UV", "Scale"
		};
		m_output_name =
		{
			"Out","Pos","UV","Index"
		};

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	HexagonNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_slot_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), m_scale);

	}

	void	HexagonNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_scale);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name + "Out", m_ID);
		m_out_str[1] = NodeFunction::SetDefineOutName(m_Name + "Pos", m_ID);
		m_out_str[2] = NodeFunction::SetDefineOutName(m_Name + "Scale", m_ID);
		m_out_str[3] = NodeFunction::SetDefineOutName(m_Name + "Index", m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetDefineOutStr2(m_out_str[1]);
		m_function_call_str += NodeFunction::SetDefineOutStr2(m_out_str[2]);
		m_function_call_str += NodeFunction::SetDefineOutStr2(m_out_str[3]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrSet(nodes_ptr, links);
	}
	std::string	HexagonNode::GetFunctionDefStr()
	{
		return
			"void Hexagon(float2 UV, float Scale, out float Out, out float2 Pos, out float2 oUV, out float2 Index)\n"
			"{\n"
			"    float2 p = UV * Scale;\n"
			//		"    p.x *= 1.15470053838;\n"
			"    float isTwo = frac(floor(p.x) / 2.0) * 2.0;\n"
			"    float isOne = 1.0 - isTwo;\n"
			"    p.y += isTwo * 0.5;\n"
			"    float2 rectUV = frac(p);\n"
			"    float2 grid = floor(p);\n"
			"    p = frac(p) - 0.5;\n"
			"    float2 s = sign(p);\n"
			"    p = abs(p);\n"
			"    Out = abs(max(p.x * 1.5 + p.y, p.y * 2.0) - 1.0);\n"
			"    float isInHex = step(p.x * 1.5 + p.y, 1.0);\n"
			"    float isOutHex = 1.0 - isInHex;\n"
			"    float2 grid2 = float2(0, 0);\n"
			"    grid2 = lerp(float2(s.x, +step(0.0, s.y)), float2(s.x, -step(s.y, 0.0)), isTwo) *isOutHex;\n"
			"    Index = grid + grid2;\n"
			"    Pos = Index / Scale;\n"
			"    oUV = lerp(rectUV, rectUV - s * float2(1.0, 0.5), isOutHex);\n"
			"}\n";
	}

#pragma endregion

#pragma region Polygon
	PolygonNode::PolygonNode()
		:NodeBase( 4, 1)
	{
		Init();
	}

	PolygonNode::PolygonNode(int id, const math::FVector2& pos)
		:NodeBase("Polygon", id, pos, 4, 1)
	{
		Init();
	}

	PolygonNode::~PolygonNode()
	{
	}

	void	PolygonNode::Init()
	{
		m_uv = { 0.0f, 0.0f};
		m_sides = 4.0f;
		m_width = 1.0f;
		m_height = 1.0f;
		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);

		//node	slot name
		m_input_name =
		{
			"UV", "Sides", "Width", "Height"
		};
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	PolygonNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_slot_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), m_sides);
		if (!m_is_slot_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), m_width);
		if (!m_is_slot_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::get_space(3), m_height);
	}

	void	PolygonNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_sides);
		m_input_str[2] = std::to_string(m_width);
		m_input_str[3] = std::to_string(m_height);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrSet(nodes_ptr, links);
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
#pragma endregion

#pragma region Ripple
	RippleNode::RippleNode()
		:NodeBase(5, 1)
	{
		Init();
	}

	RippleNode::RippleNode(int id, const math::FVector2& pos)
		:NodeBase("Ripple", id, pos, 5, 1)
	{
		Init();
	}

	RippleNode::~RippleNode()
	{
	}

	void	RippleNode::Init()
	{
		m_uv = { 0.0f ,0.0f };
		m_width = 1.0f;
		m_height = 1.0f;
		m_center = { 0.0f, 0.0f };
		m_scale = 1.0f;

		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR2, SLOT_TYPE::VECTOR1
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_input_name =
		{
			"UV", "Width", "Height", "Center", "Scale"
		};

		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	RippleNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_slot_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), m_width);
		if (!m_is_slot_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), m_height);
		if (!m_is_slot_input[3])	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_center, 3);
		if (!m_is_slot_input[4])	NodeFunction::SetInputSlotFloat(m_input_pos[4], StringConverter::get_space(4), m_scale);
	}

	void	RippleNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_width);
		m_input_str[2] = std::to_string(m_height);
		m_input_str[3] = NodeFunction::SetInputToString2(m_center);
		m_input_str[4] = std::to_string(m_scale);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		str_check(nodes_ptr, links);
	}
	std::string	RippleNode::GetFunctionDefStr()
	{
		return
			"void Ripple(float2 UV, float Width, float Height, float2 Center, float Scale, out float Out)\n"
			"{\n"
			"    float2 p = (UV * 2.0 - 1.0) / float2(Width, Height);\n"
			"    Out = sin(Scale * distance(p, Center));\n"
			"}\n";
	}
#pragma endregion

#pragma region RoundedRectangle
	RoundedRectangleNode::RoundedRectangleNode()
		:NodeBase(4, 1)
	{
		Init();
	}

	RoundedRectangleNode::RoundedRectangleNode(int id, const math::FVector2& pos)
		:NodeBase("RoundedRectangle", id, pos, 4, 1)
	{
		Init();
	}

	RoundedRectangleNode::~RoundedRectangleNode()
	{
	}

	void	RoundedRectangleNode::Init()
	{
		m_uv = { 0.0f ,0.0f };
		m_width = 1.0f;
		m_height = 1.0f;
		m_radius = 1.0f;

		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1
		};
		m_input_name =
		{
			"UV", "Width", "Height", "Radius"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	RoundedRectangleNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_slot_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_slot_input[1])	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::get_space(1), m_width);
		if (!m_is_slot_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), m_height);
		if (!m_is_slot_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::get_space(3), m_radius);
	}

	void	RoundedRectangleNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_width);
		m_input_str[2] = std::to_string(m_height);
		m_input_str[3] = std::to_string(m_radius);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
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
#pragma endregion

}