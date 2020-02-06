#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"UVNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::PolarCoordinatesNode)
CEREAL_REGISTER_TYPE(epion::Node::RadialShearNode)
CEREAL_REGISTER_TYPE(epion::Node::SpherizeNode)
CEREAL_REGISTER_TYPE(epion::Node::TilingAndOffsetNode)
CEREAL_REGISTER_TYPE(epion::Node::TwirlNode)
CEREAL_REGISTER_TYPE(epion::Node::UVNode)


namespace	epion::Node
{
#pragma region PolarCoordinates
	PolarCoordinatesNode::PolarCoordinatesNode()
		:NodeBase( 4, 1)
	{
		Init();
	}

	PolarCoordinatesNode::PolarCoordinatesNode(int id, const math::FVector2& pos)
		:NodeBase("PolarCoordinates", id, pos, 4, 1)
	{
		Init();
	}

	PolarCoordinatesNode::~PolarCoordinatesNode()
	{
	}

	void	PolarCoordinatesNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_center = { 0.5f, 0.5f };
		m_radialscale = 1.0f;
		m_lengthscale = 1.0f;
		m_input_slot_type =
		{
			SLOT_TYPE::UV,SLOT_TYPE::VECTOR2,SLOT_TYPE::VECTOR1,SLOT_TYPE::VECTOR1
		};

		m_input_name =
		{
			"UV", "Center", "RadialScale", "LengthScale"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	PolarCoordinatesNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_center, 1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_radialscale);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::GetSpace(3), m_lengthscale);
	}

	void	PolarCoordinatesNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(m_center);
		m_input_str[2] = std::to_string(m_radialscale);
		m_input_str[3] = std::to_string(m_lengthscale);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}

	std::string	PolarCoordinatesNode::GetFunctionDefStr()
	{
		return
			"void PolarCoordinates(float2 UV, float2 Center, float RadialScale, float LengthScale, out float2 Out)\n"
			"{\n"
			"    float2 delta = UV - Center;\n"
			"    float radius = length(delta) * 2 * RadialScale;\n"
			"    float angle = atan2(delta.x, delta.y) * 1.0 / 6.28 * LengthScale;\n"
			"    Out = float2(radius, angle);\n"
			"}\n";
	}
#pragma endregion

#pragma region RadialShear

	RadialShearNode::RadialShearNode()
		:NodeBase(4, 1)
	{
		Init();
	}
	RadialShearNode::RadialShearNode(int id, const math::FVector2& pos)
		:NodeBase("RadialShear", id, pos, 4, 1)
	{
		Init();
	}
	RadialShearNode::~RadialShearNode()
	{
	}
	void RadialShearNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_center = { 0.5f,0.5f };
		m_strength = { 10.0f, 10.0f };
		m_offset = { 0.0f, 0.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR2, SLOT_TYPE::VECTOR2, SLOT_TYPE::VECTOR2
		};
		m_input_name =
		{
			"UV", "Center", "Strength", "Offset"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}
	void	RadialShearNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_center);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[2], m_strength, 1);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_offset, 2);
	}

	void	RadialShearNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(m_center);
		m_input_str[2] = NodeFunction::SetInputToString2(m_strength);
		m_input_str[3] = NodeFunction::SetInputToString2(m_offset);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);

		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string RadialShearNode::GetFunctionDefStr()
	{
		return
			"void RadialShear(float2 UV, float2 Center, float2 Strength, float2 Offset, out float2 Out)\n"
			"{\n"
			"    float2 delta = UV - Center;\n"
			"    float delta2 = dot(delta.xy, delta.xy);\n"
			"    float2 delta_offset = delta2 * Strength;\n"
			"    Out = UV + float2(delta.y, -delta.x) * delta_offset + Offset;\n"
			"}\n";
	}
#pragma endregion

#pragma region Spherize
	SpherizeNode::SpherizeNode()
		:NodeBase(4, 1)
	{
		Init();
	}

	SpherizeNode::SpherizeNode(int id, const math::FVector2& pos)
		:NodeBase("Spherize", id, pos, 4, 1)
	{
		Init();
	}

	SpherizeNode::~SpherizeNode()
	{
	}

	void	SpherizeNode::Init()
	{
		m_uv = { 0.0f,0.0f };
		m_center = { 0.5f,0.5f };
		m_strength = 10.0f;
		m_offset = { 0.0f,0.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR2,
		};

		m_input_name =
		{
			"UV", "Center", "Strength", "Offset"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	SpherizeNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_center, 1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_strength);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_offset, 3);
	}

	void	SpherizeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(m_center);
		m_input_str[2] = std::to_string(m_strength);
		m_input_str[3] = NodeFunction::SetInputToString2(m_offset);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);

		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string	SpherizeNode::GetFunctionDefStr()
	{
		return
			"void Spherize(float2 UV, float2 Center, float Strength, float2 Offset, out float2 Out)\n"
			"{\n"
			"    float2 delta = UV - Center;\n"
			"    float delta2 = dot(delta.xy, delta.xy);\n"
			"    float delta4 = delta2 * delta2;\n"
			"    float2 delta_offset = delta4 * Strength;\n"
			"    Out = UV + delta * delta_offset + Offset;\n"
			"}\n";
	};
#pragma endregion

#pragma region TilingAndOffset
	TilingAndOffsetNode::TilingAndOffsetNode()
		:NodeBase( 3, 1)
	{
		Init();
	}

	TilingAndOffsetNode::TilingAndOffsetNode(int id, const math::FVector2& pos)
		:NodeBase("TilingAndOffset", id, pos, 3, 1)
	{
		Init();
	}

	TilingAndOffsetNode::~TilingAndOffsetNode()
	{
	}

	void	TilingAndOffsetNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_tiling = { 1.0f,1.0f };
		m_offset = { 0.0f, 0.0f };
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR2,
		};
		m_input_name =
		{
			"UV", "Tiling", "Offset"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	TilingAndOffsetNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_tiling, 1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[2], m_offset, 2);
	}

	void	TilingAndOffsetNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(m_tiling);
		m_input_str[2] = NodeFunction::SetInputToString2(m_offset);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string	TilingAndOffsetNode::GetFunctionDefStr()
	{
		return
			"void TilingAndOffset(float2 UV, float2 Tiling, float2 Offset, out float2 Out)\n"
			"{\n"
			"    Out = UV * Tiling + Offset;\n"
			"}\n";
	};
#pragma endregion

#pragma region Twirl
	TwirlNode::TwirlNode()
		:NodeBase(4, 1)
	{
		Init();
	}

	TwirlNode::TwirlNode(int id, const math::FVector2& pos)
		:NodeBase("Twirl", id, pos, 4, 1)
	{
		Init();
	}

	TwirlNode::~TwirlNode()
	{
	}

	void	TwirlNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_center = { 0.5f, 0.5f };
		m_strength = 10.0f;
		m_offset = { 0.0f, 0.0f };
		m_input_slot_type=
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR2,
		};
		m_input_name =
		{
			"UV","Center","Strength","Offset"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	TwirlNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[1]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[1],m_center,1);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2],"   ", m_strength);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_offset, 3);
	}

	void	TwirlNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(m_center);
		m_input_str[2] = std::to_string(m_strength);
		m_input_str[3] = NodeFunction::SetInputToString2(m_offset);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string	TwirlNode::GetFunctionDefStr()
	{
		return
			"void Twirl(float2 UV, float2 Center, float Strength, float2 Offset, out float2 Out)\n"
			"{\n"
			"    float2 delta = UV - Center;\n"
			"    float angle = Strength * length(delta);\n"
			"    float x = cos(angle) * delta.x - sin(angle) * delta.y;\n"
			"    float y = sin(angle) * delta.x + cos(angle) * delta.y;\n"
			"    Out = float2(x + Center.x + Offset.x, y + Center.y + Offset.y);\n"
			"}\n";
	};
#pragma endregion

#pragma region UV
	UVNode::UVNode()
		:NodeBase(0, 1)
	{
		Init();
	}

	UVNode::UVNode(int id, const math::FVector2& pos)
		:NodeBase("UV", id, pos, 0, 1)
	{
		Init();
	}

	UVNode::~UVNode()
	{
	}

	void	UVNode::Init()
	{
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out");
	}

	void	UVNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
	}

	void	UVNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "input.uv";
	}
	std::string UVNode::GetFunctionDefStr()
	{
		return	"";
	};
#pragma endregion

}

//void Ellipse(vec2 UV, float Width, float Height, out float Out)
//{
//	float d = length((UV * 2.0 - 1.0) / vec2(Width, Height));
//	Out += clamp((1.0 - d) / fwidth(d), 0.0, 1.0);
//}
//
//void Yuppi2D(vec2 UV, vec3 BodyColor, out vec3 Out)
//{
//	//Body
//	float body;
//	Ellipse(UV, 0.7, 0.7, body);
//
//	//Eye
//	vec2 eye_uv = vec2(-0.18, 0.0);
//	float pupil;
//	Ellipse(UV + eye_uv, 0.2, 0.2, pupil);
//	Ellipse(UV + abs(eye_uv), 0.2, 0.2, pupil);
//	float eye;
//	Ellipse(UV + eye_uv, 0.1, 0.1, eye);
//	Ellipse(UV + abs(eye_uv), 0.1, 0.1, eye);
//
//	//Mouth
//	float mouth, mouth2;
//	vec3 mouth_color = vec3(1.0, 1.0, .0);
//	Ellipse(UV + vec2(0.0, 0.2), 0.5, 0.2, mouth);
//	Ellipse(UV, 0.6, 0.6, mouth2);
//
//	//Face
//	vec3 face = body * BodyColor;
//	mouth_color *= mouth * mouth2;
//	face += mouth_color;
//	face += pupil;
//	face *= body * 1.0 - eye;
//
//	Out = face;
//}
//void mainImage(out vec4 fragColor, in vec2 fragCoord)
//{
//	vec2 uv = fragCoord / iResolution.yy;
//	vec3 body_color = vec3(0.0, 1.0, 0.0);
//	vec3 col = vec3(0.0, 0.0, 0.0);
//	Yuppi2D(uv, body_color, col);
//
//	fragColor = vec4(col, 1.0);
//}