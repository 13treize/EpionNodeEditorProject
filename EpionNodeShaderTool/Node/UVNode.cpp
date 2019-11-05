#include	"../All.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeParam.h"
#include	"NodeData.h"
#include	"UVNode.h"
#include	"../epion_string.h"
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
	PolarCoordinatesNode::PolarCoordinatesNode()
	{
		Init();
	}

	PolarCoordinatesNode::PolarCoordinatesNode(int id, const math::FVector2& pos)
		:NodeBase("PolarCoordinates", id, pos, size, 4, 1)
	{
		Init();
	}

	PolarCoordinatesNode::~PolarCoordinatesNode()
	{
	}

	void	PolarCoordinatesNode::Init()
	{
		m_uv = { 0,0 };
		Center = { 0.5,0.5 };
		RadialScale = 1.0f;
		LengthScale = 1.0f;
		m_input_slot_type =
		{
			SLOT_TYPE::m_uv,SLOT_TYPE::VECTOR2,SLOT_TYPE::VECTOR1,SLOT_TYPE::VECTOR1
		};

		m_input_name =
		{
			"UV(2)","Center(2)","RadialScale(1)","LengthScale(1)"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out(2)");
	}

	void	PolarCoordinatesNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[1]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[1], Center, 1);
		}

		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), RadialScale);
		}

		if (!m_is_input[3])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[3], SLOT_INPUT_POS_X, StringConverter::get_space(3), LengthScale);
		}

	}

	void	PolarCoordinatesNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	PolarCoordinatesNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "PolarCoordinatesNode" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = "float2(" + StringConverter::to_string2(Center, ",") + ")";
		m_input_str[2] = std::to_string(RadialScale);
		m_input_str[3] = std::to_string(LengthScale);

		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				m_is_input[l.get_input_slot()] = true;
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
			}
		}

		m_function_call_str = "    float2 " + m_out_str[0] + ";\n";
		m_function_call_str += "    PolarCoordinates_float(";
		str_set(nodes_ptr, links);
	}
	std::string	PolarCoordinatesNode::GetFunctionDefStr()
	{
		return
			"void PolarCoordinates_float(float2 UV, float2 Center, float RadialScale, float LengthScale, out float2 Out)\n"
			"{\n"
			"    float2 delta = UV - Center;\n"
			"    float radius = length(delta) * 2 * RadialScale;\n"
			"    float angle = atan2(delta.x, delta.y) * 1.0 / 6.28 * LengthScale;\n"
			"    Out = float2(radius, angle);\n"
			"}\n";
	}
	RadialShearNode::RadialShearNode()
	{
		Init();
	}
	RadialShearNode::RadialShearNode(int id, const math::FVector2& pos)
		:NodeBase("RadialShear", id, pos, size, 4, 1)
	{
		Init();
	}
	RadialShearNode::~RadialShearNode()
	{
	}
	void RadialShearNode::Init()
	{
		m_uv = { 0,0 };
		Center = { 0.5,0.5 };
		Strength = { 10,10 };
		Offset = { 0,0 };
		m_input_slot_type =
		{
			SLOT_TYPE::m_uv,SLOT_TYPE::VECTOR2,SLOT_TYPE::VECTOR2,SLOT_TYPE::VECTOR2
		};
		m_input_name =
		{
			"UV(2)","Center(2)","Strength(2)","Offset(2)"
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out(2)");
	}
	void	RadialShearNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[1], Center);
		}
		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[2], Strength, 1);
		}
		if (!m_is_input[3])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[3], Offset, 2);
		}
	}

	void	RadialShearNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	RadialShearNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "RadialShear_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = "float2(" + StringConverter::to_string2(Center, ",") + ")";
		m_input_str[2] = "float2(" + StringConverter::to_string2(Strength, ",") + ")";
		m_input_str[3] = "float2(" + StringConverter::to_string2(Offset, ",") + ")";

		m_function_call_str = "    float2 " + m_out_str[0] + ";\n";
		m_function_call_str += "    RadialShear(";
		str_set(nodes_ptr, links);
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
	SpherizeNode::SpherizeNode()
	{
		Init();
	}

	SpherizeNode::SpherizeNode(int id, const math::FVector2& pos)
		:NodeBase("Spherize", id, pos, size, 4, 1)
	{
		Init();
	}

	SpherizeNode::~SpherizeNode()
	{
	}

	void	SpherizeNode::Init()
	{
		m_uv = { 0,0 };
		Center = { 0.5,0.5 };
		Strength = 10;
		Offset = { 0,0 };
		m_input_slot_type =
		{
			SLOT_TYPE::m_uv,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR2,
		};

		m_input_name =
		{
			"UV(2)","Center(2)","Strength(1)","Offset(2)"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out(2)");

	}

	void	SpherizeNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[1], Center, 1);
		}
		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), Strength);
		}
		if (!m_is_input[3])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[3], Offset, 3);
		}
	}

	void	SpherizeNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	SpherizeNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Spherize_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(Center);
		m_input_str[2] = std::to_string(Strength);
		m_input_str[3] = NodeFunction::SetInputToString2(Offset);

		m_function_call_str = "    float2 " + m_out_str[0] + ";\n";
		m_function_call_str += "    Spherize(";
		str_set(nodes_ptr, links);
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

	TilingAndOffsetNode::TilingAndOffsetNode()
	{
		Init();
	}

	TilingAndOffsetNode::TilingAndOffsetNode(int id, const math::FVector2& pos)
		:NodeBase("TilingAndOffset", id, pos, size, 3, 1)
	{
		Init();
	}

	TilingAndOffsetNode::~TilingAndOffsetNode()
	{
	}

	void	TilingAndOffsetNode::Init()
	{
		m_uv = { 0,0 };
		Tiling = { 1.0f,1.0f };
		Offset = { 0,0 };
		m_input_slot_type =
		{
			SLOT_TYPE::m_uv,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR2,
		};
		m_input_name =
		{
			"UV(2)",	"Tiling(2)",	"Offset(2)"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out(2)");

	}

	void	TilingAndOffsetNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[1], Tiling, 1);
		}
		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[2], Offset, 2);
		}
	}

	void	TilingAndOffsetNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	TilingAndOffsetNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "TilingAndOffset_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(Tiling);
		m_input_str[2] = NodeFunction::SetInputToString2(Offset);

		m_function_call_str = "    float2 " + m_out_str[0] + ";\n";
		m_function_call_str += "    TilingAndOffset(";
		str_set(nodes_ptr, links);
	}
	std::string	TilingAndOffsetNode::GetFunctionDefStr()
	{
		return
			"void TilingAndOffset(float2 UV, float2 Tiling, float2 Offset, out float2 Out)\n"
			"{\n"
			"    Out = UV * Tiling + Offset;\n"
			"}\n";
	};

	TwirlNode::TwirlNode()
	{
		Init();
	}

	TwirlNode::TwirlNode(int id, const math::FVector2& pos)
		:NodeBase("Twirl", id, pos, size, 4, 1)
	{
		Init();
	}

	TwirlNode::~TwirlNode()
	{
	}

	void	TwirlNode::Init()
	{
		m_uv = { 0,0 };
		Center = { 0.5,0.5 };
		Strength = 10;
		Offset = { 0,0 };
		m_input_slot_type=
		{
			SLOT_TYPE::m_uv,	SLOT_TYPE::VECTOR2,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR2,
		};
		m_input_name =
		{
			"UV(2)","Center(2)","Strength(1)","Offset(2)"
		};

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out(2)");

	}

	void	TwirlNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[1]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[1],Center,1);
		}
		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[2], -60,"   ", Strength);
		}
		if (!m_is_input[3])
		{
			NodeFunction::SetInputSlotFloat2(m_input_pos[3], Offset, 3);
		}
	}

	void	TwirlNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	TwirlNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Twirl_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = NodeFunction::SetInputToString2(Center);
		m_input_str[2] = std::to_string(Strength);
		m_input_str[3] = NodeFunction::SetInputToString2(Offset);

		m_function_call_str = "    float2 " + m_out_str[0] + ";\n";
		m_function_call_str += "    Twirl(";
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

	UVNode::UVNode()
	{
		Init();
	}

	UVNode::UVNode(int id, const math::FVector2& pos)
		:NodeBase("UV", id, pos, size, 0, 1)
	{
		Init();
	}

	UVNode::~UVNode()
	{
	}

	void	UVNode::Init()
	{
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR2);
		m_output_name.push_back("Out(2)");
	}

	void	UVNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
	}

	void	UVNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	UVNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "input.uv";
	}
	std::string UVNode::GetFunctionDefStr()
	{
		return	"";
	};
}