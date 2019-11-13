#include	"../All.h"
#include	"../epion.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"UVNode.h"
namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::PolarCoordinatesNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::RadialShearNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::SpherizeNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::TilingAndOffsetNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::TwirlNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::UVNode)


namespace	epion::NodeCustom
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
	}

	void	PolarCoordinatesNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_center, 1);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), m_radialscale);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::get_space(3), m_lengthscale);
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
		str_check(nodes_ptr, links);
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
	}
	void	RadialShearNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_center);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat2(m_input_pos[2], m_strength, 1);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_offset, 2);
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
		str_check(nodes_ptr, links);
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

	}

	void	SpherizeNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat2(m_input_pos[1], m_center, 1);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::get_space(2), m_strength);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat2(m_input_pos[3], m_offset, 3);
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
		str_check(nodes_ptr, links);
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
		Tiling = { 1.0f,1.0f };
		Offset = { 0.0f, 0.0f };
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

	}

	void	TilingAndOffsetNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat2(m_input_pos[1], Tiling, 1);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat2(m_input_pos[2], Offset, 2);
	}

	void	TilingAndOffsetNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(Tiling);
		m_input_str[2] = NodeFunction::SetInputToString2(Offset);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		str_check(nodes_ptr, links);
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
		Center = { 0.5f, 0.5f };
		Strength = 10.0f;
		Offset = { 0.0f, 0.0f };
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

	}

	void	TwirlNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (!m_is_input[0])	NodeFunction::SetInputSlotUV(m_input_pos[1]);
		if (!m_is_input[1])	NodeFunction::SetInputSlotFloat2(m_input_pos[1],Center,1);
		if (!m_is_input[2])	NodeFunction::SetInputSlotFloat(m_input_pos[2],"   ", Strength);
		if (!m_is_input[3])	NodeFunction::SetInputSlotFloat2(m_input_pos[3], Offset, 3);
	}

	void	TwirlNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(Center);
		m_input_str[2] = std::to_string(Strength);
		m_input_str[3] = NodeFunction::SetInputToString2(Offset);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr2(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		str_check(nodes_ptr, links);
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