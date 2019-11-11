#include	"stdafx.h"

namespace
{

}

namespace	epion::NodeCustom
{
	NodeStates::NodeStates()
	{}
	NodeStates::NodeStates(std::string	name, math::FVector2&	pos, SLOT_TYPE type, ImU32	color)
		:name(name), pos(pos), slot_type(type), color(color)
	{
	}
	NodeStates::~NodeStates()
	{
	}
	void NodeFunction::SetInputSlotFloat(ImVec2& set_cursor, float x, std::string label, float& num)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(x, -SLOT_INPUT_FLOAT));
		ImGui::SetNextItemWidth(30.0f);
		ImGui::InputFloat(label.c_str(), &num, 0.0f, 1.0f, "%.2f");
	}
	void NodeFunction::SetInputSlotFloat2(ImVec2& set_cursor, std::string label, math::FVector2& num)
	{

		//ImGui::SetCursorScreenPos(set_cursor + ImVec2(-60, -SLOT_INPUT_FLOAT));
		//ImGui::SetNextItemWidth(30.0f);
		//ImGui::InputFloat(label.c_str(), &num, 0.0f, 1.0f, "%.2f");
	}
	void NodeFunction::SetInputSlotFloat3(ImVec2& set_cursor, std::string label, math::FVector3& num)
	{

		//ImGui::SetCursorScreenPos(set_cursor + ImVec2(-60, -SLOT_INPUT_FLOAT));
		//ImGui::SetNextItemWidth(30.0f);
		//ImGui::InputFloat(label.c_str(), &num, 0.0f, 1.0f, "%.2f");
	}
	void NodeFunction::SetInputSlotFloat4(ImVec2& set_cursor, std::string label, math::FVector4& num)
	{

		//ImGui::SetCursorScreenPos(set_cursor + ImVec2(-60, -SLOT_INPUT_FLOAT));
		//ImGui::SetNextItemWidth(30.0f);
		//ImGui::InputFloat(label.c_str(), &num, 0.0f, 1.0f, "%.2f");
	}

	std::string	NodeFunction::get_type(SLOT_TYPE type)
	{
		std::string	ret_str = "";
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	ret_str = "float";	break;
		case SLOT_TYPE::VECTOR2:	ret_str = "float2";	break;
		case SLOT_TYPE::VECTOR3:	ret_str = "float3";	break;
		case SLOT_TYPE::VECTOR4:	ret_str = "float4";	break;
		case SLOT_TYPE::COLOR:	break;
		case SLOT_TYPE::TEXTURE2D:	break;
		case SLOT_TYPE::BOOLEAN:	break;
		}
		return ret_str;
	}

	std::string	NodeFunction::get_slot_type_name(SLOT_TYPE type)
	{
		std::string	ret_str = "";
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	ret_str = "(1)";	break;
		case SLOT_TYPE::VECTOR2:	ret_str = "(2)";	break;
		case SLOT_TYPE::VECTOR3:	ret_str = "(3)";	break;
		case SLOT_TYPE::VECTOR4:	ret_str = "(4)";	break;
		case SLOT_TYPE::COLOR:	break;
		case SLOT_TYPE::TEXTURE2D:	break;
		case SLOT_TYPE::BOOLEAN:	break;
		}
		return ret_str;
	}

	void NodeFunction::set_slot_data(math::FVector4& data, std::string& str, SLOT_TYPE type)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	str = std::to_string(data.x);			break;
		case SLOT_TYPE::VECTOR2:	str = NodeFunction::get_type(type) + "(" + StringConverter::to_string2(data.x, data.y) + ")";		break;
		case SLOT_TYPE::VECTOR3:	str = NodeFunction::get_type(type) + "(" + StringConverter::to_string3(data.x, data.y, data.z) + ")";	break;
		case SLOT_TYPE::VECTOR4:	str = NodeFunction::get_type(type) + "(" + StringConverter::to_string4(data) + ")";				break;
		}

	}

	void NodeFunction::NodeCircle(ImDrawList*	draw_list, const ImVec2& centre, float radius, ImU32 color, SLOT_TYPE type)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	color = ImColor::U32::LIGHTBLUE;	break;
		case SLOT_TYPE::VECTOR2:	color = ImColor::U32::LAWNGREEN;	break;
		case SLOT_TYPE::VECTOR3:
		case SLOT_TYPE::COLOR:		color = ImColor::U32::YELLOW;	break;
		case SLOT_TYPE::VECTOR4:	color = ImColor::U32::REDPURPLE;	break;
		case SLOT_TYPE::TEXTURE2D:
			break;
		case SLOT_TYPE::BOOLEAN:
			break;
		}
		draw_list->AddCircle(centre, NODE_SLOT_RADIUS, color);
	}


	NodeBase::NodeBase()
	{
	}

	NodeBase::NodeBase(std::string name, int id, const epion::math::FVector2& pos, const ImVec2& size, int inputs_count, int outputs_count)
		:m_Name(name), m_ID(id), m_Pos(pos), m_Size(size), m_inputs_count(inputs_count), m_outputs_count(outputs_count), m_function_call_str("")
	{
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_is_input.push_back(false);

			m_input_str.push_back("");
			m_input_pos.push_back({});
			m_input_slot_color.push_back(0);
		}

		for (int i = 0; i < m_outputs_count; i++)
		{
			m_out_str.push_back("");
			m_output_pos.push_back({});
			m_output_slot_color.push_back(0);
		}
	}
	void	NodeBase::Update(ImVec2& offset, ImDrawList*	draw_list)
	{
		ImVec2 node_rect_min = { offset.x + m_Pos.x,offset.y + m_Pos.y };
		ImVec2 node_rect_max = node_rect_min + m_Size;
		ImVec2 node_rect_max2 = node_rect_min + ImVec2(m_Size.x*0.5f, m_Size.y);

		draw_list->ChannelsSetCurrent(1);
		draw_list->AddRectFilled(node_rect_min, node_rect_max2, LEFT_RECT_COLOR, 2.0f);
		draw_list->AddRectFilled(node_rect_min, node_rect_max, RIGHT_RECT_COLOR, 2.0f);

	}

	void	NodeBase::i_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		for (int input_slots = 0; input_slots < m_inputs_count; input_slots++)
		{
			m_input_pos[input_slots] = offset + this->get_input_slot_pos(input_slots);

			draw_list->ChannelsSetCurrent(1);
			ImGui::SetCursorScreenPos(m_input_pos[input_slots] + ImVec2(10.0f, -SLOT_INPUT_FLOAT));
			ImGui::TextColored(ImColor::Vec4::WHITE, "%s", m_input_name[input_slots].c_str());
			NodeFunction::NodeCircle(draw_list, m_input_pos[input_slots], NODE_SLOT_RADIUS, m_input_slot_color[input_slots], m_input_slot_type[input_slots]);
			if (!m_is_input[input_slots])
			{
				draw_list->ChannelsSetCurrent(0); // input_slot
				draw_list->AddLine(m_input_pos[input_slots] + ImVec2(-20, 0), m_input_pos[input_slots], ImColor::U32::GREEN, 1.0f);
				draw_list->AddRectFilled(m_input_pos[input_slots] + ImVec2(-70, -SLOT_INPUT_FLOAT), m_input_pos[input_slots] + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
				draw_list->AddRect(m_input_pos[input_slots] + ImVec2(-70, -SLOT_INPUT_FLOAT), m_input_pos[input_slots] + ImVec2(-15, SLOT_INPUT_FLOAT), ImColor::U32::GREEN, 2.0f);
			}


			ImU32	FillRectColor;
			if (physics::Collider2D::SphereAndSphere(math::FVector2(m_input_pos[input_slots].x, m_input_pos[input_slots].y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				FillRectColor = ImColor::U32::GREEN;
			}
			else
			{
				FillRectColor = ImColor::U32::BLACK;
			}
			draw_list->AddCircleFilled(m_input_pos[input_slots], NODE_SLOT_RADIUS - 2, FillRectColor);
		}
	}

	void	NodeBase::o_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		for (int output_slots = 0; output_slots < m_outputs_count; output_slots++)
		{
			m_output_pos[output_slots] = offset + this->get_output_slot_pos(output_slots);

			draw_list->ChannelsSetCurrent(1); // input_slot
			ImGui::SetCursorScreenPos(m_output_pos[output_slots] + ImVec2(-40.0f, -SLOT_INPUT_FLOAT));
			ImGui::TextColored(ImColor::Vec4::WHITE, "%s", m_output_name[output_slots].c_str());
			NodeFunction::NodeCircle(draw_list, m_output_pos[output_slots], NODE_SLOT_RADIUS, m_output_slot_color[output_slots], m_output_slot_type[output_slots]);
			if (physics::Collider2D::sphere_and_sphere(math::FVector2(m_output_pos[output_slots].x, m_output_pos[output_slots].y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				draw_list->AddCircleFilled(m_output_pos[output_slots], NODE_SLOT_RADIUS - 2, ImColor::U32::RED);
			}
		}
	}

	//mainä÷êî
	void	NodeBase::function_call_update(std::string	func_name)
	{
		//m_function_call_str = " ";
		//m_function_call_str	+="    "+func_name+"(";
		//for (auto& args : m_args_str)
		//{
		//	if(args!= m_args_str.end())
		//	m_function_call_str = args+",";

		//}

	}

	ImVec2 NodeBase::get_input_slot_pos(int slot_no) const
	{
		return ImVec2(m_Pos.x + SLOT_POS,
			m_Pos.y + m_Size.y * (static_cast<float>(slot_no) + 1) / (static_cast<float>(m_inputs_count) + 1));
	}
	ImVec2 NodeBase::get_output_slot_pos(int slot_no) const
	{
		return ImVec2(m_Pos.x + m_Size.x - SLOT_POS,
			m_Pos.y + m_Size.y * (static_cast<float>(slot_no) + 1) / (static_cast<float>(m_outputs_count) + 1));
	}
	std::string	NodeBase::get_shader_str()
	{
		return	m_function_call_str;
	}


	std::string	NodeBase::get_function_call_str()
	{
		return	m_function_call_str;
	}

	std::vector<std::string>&	NodeBase::get_out_str()
	{
		return m_out_str;
	}

	std::vector<std::string>&	NodeBase::get_input_str()
	{
		return m_input_str;
	}


	void NodeBase::type_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				//éhÇ≥Ç¡ÇΩèÛë‘
				m_is_input[l.get_input_slot()] = true;
				//output nodeÇ©ÇÁïœêîéÊìæ
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->get_out_str()[l.get_output_slot()];
				//å^ÇçáÇÌÇπÇÈ
				if (m_input_slot_type[l.get_input_slot()] != l.get_output_type())
				{
					switch (m_input_slot_type[l.get_input_slot()])
					{
					case	SLOT_TYPE::VECTOR1:
						m_input_slot_type[l.get_input_slot()] = l.get_output_type();
						break;
					case	SLOT_TYPE::VECTOR2:
						if (m_input_slot_type[l.get_input_slot()] != SLOT_TYPE::VECTOR1)
						{
							m_input_slot_type[l.get_input_slot()] = l.get_output_type();
						}
						break;
					case	SLOT_TYPE::VECTOR3:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:
							break;

						case	SLOT_TYPE::VECTOR2:
							m_input_slot_type[l.get_input_slot()] = l.get_output_type();
							break;
						case	SLOT_TYPE::VECTOR3:
							break;
						case	SLOT_TYPE::VECTOR4:
							m_input_str[l.get_input_slot()] += ".xyz";
							break;

						}
						break;
					case	SLOT_TYPE::VECTOR4:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:
							break;

						case	SLOT_TYPE::VECTOR2:
							m_input_slot_type[l.get_input_slot()] = l.get_output_type();
							break;
						case	SLOT_TYPE::VECTOR3:
							m_input_slot_type[l.get_input_slot()] = l.get_output_type();
							break;
						case	SLOT_TYPE::VECTOR4:
							break;

						}
						break;
					}
				}
			}
		}
		for (int i = 0; i < m_inputs_count; i++)
		{
			for (int j = i + 1; j < m_inputs_count; j++)
			{
				if (m_input_slot_type[i] != m_input_slot_type[j])
				{
					if (m_input_slot_type[i] == SLOT_TYPE::VECTOR1)
					{
						m_input_slot_type[i] = m_input_slot_type[j];
						break;
					}
					if (m_input_slot_type[j] == SLOT_TYPE::VECTOR1)
					{
						m_input_slot_type[j] = m_input_slot_type[i];
						break;
					}


					if (static_cast<int>(m_input_slot_type[i]) < static_cast<int>(m_input_slot_type[j]))
					{
						m_input_slot_type[j] = m_input_slot_type[i];
						m_output_slot_type[0] = m_input_slot_type[i];
						break;
					}
					else
					{
						m_input_slot_type[i] = m_input_slot_type[j];
						m_output_slot_type[0] = m_input_slot_type[j];
						break;
					}
				}
			}
		}
	}

	//à¯êîÇ…ì¸ÇÍç€
	void	NodeBase::str_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				//éhÇ≥Ç¡ÇΩèÛë‘
				m_is_input[l.get_input_slot()] = true;
				//output nodeÇ©ÇÁïœêîéÊìæ
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->get_out_str()[l.get_output_slot()];
				//å^ÇçáÇÌÇπÇÈ
				if (m_input_slot_type[l.get_input_slot()] != l.get_output_type())
				{
					switch (m_input_slot_type[l.get_input_slot()])
					{
					case	SLOT_TYPE::VECTOR1:
						m_input_str[l.get_input_slot()] += ".x";
						break;
					case	SLOT_TYPE::VECTOR2:
						if (m_input_slot_type[l.get_input_slot()] != SLOT_TYPE::VECTOR1)
						{
							m_input_str[l.get_input_slot()] += ".xy";
						}
						break;
					case	SLOT_TYPE::VECTOR3:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:
							break;

						case	SLOT_TYPE::VECTOR2:
							m_input_str[l.get_input_slot()] = "float3(" + nodes_ptr[l.get_output_id()]->get_out_str()[l.get_output_slot()] + ", 0.0)";
							break;
						case	SLOT_TYPE::VECTOR3:
							break;
						case	SLOT_TYPE::VECTOR4:
							m_input_str[l.get_input_slot()] += ".xyz";
							break;

						}
						break;
					case	SLOT_TYPE::VECTOR4:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:
							break;

						case	SLOT_TYPE::VECTOR2:
							m_input_str[l.get_input_slot()] = "float4(" + nodes_ptr[l.get_output_id()]->get_out_str()[l.get_output_slot()] + ",0.0, 0.0)";
							break;
						case	SLOT_TYPE::VECTOR3:
							m_input_str[l.get_input_slot()] = "float4(" + nodes_ptr[l.get_output_id()]->get_out_str()[l.get_output_slot()] + "0.0)";
							break;
						case	SLOT_TYPE::VECTOR4:
							break;

						}
						break;
					}
				}
			}
		}

		for (auto& i : m_input_str)
		{
			m_function_call_str += i + ",";
		}
		for (auto& o : m_out_str)
		{
			m_function_call_str += o + ",";
		}
		m_function_call_str.pop_back();
		m_function_call_str += ");\n";
	}

	//NodeLink

	//ÉmÅ[ÉhÇÇ¬Ç»Ç∞ÇÈ
	NodeLink::NodeLink()
	{
	}
	NodeLink::NodeLink(int output_id, int output_slot, int input_id, int input_slot)
		: m_output_id(output_id), m_output_slot(output_slot), m_output_type(SLOT_TYPE::VECTOR1),
		m_input_id(input_id), m_input_slot(input_slot), m_input_type(SLOT_TYPE::VECTOR1)
	{
	}

	NodeLink::NodeLink(int output_id, int output_slot, SLOT_TYPE output_type, int input_id, int input_slot, SLOT_TYPE input_type)
		: m_output_id(output_id), m_output_slot(output_slot), m_output_type(output_type), m_input_id(input_id), m_input_slot(input_slot), m_input_type(input_type)
	{
	}
	NodeLink::~NodeLink()
	{
	}
	int	NodeLink::get_output_id()
	{
		return	m_output_id;
	}
	int	NodeLink::get_output_slot()
	{
		return	m_output_slot;
	}
	SLOT_TYPE NodeLink::get_output_type()
	{
		return m_output_type;
	}

	//right
	int	NodeLink::get_input_id()
	{
		return	m_input_id;
	}
	int	NodeLink::get_input_slot()
	{
		return	m_input_slot;
	}
	SLOT_TYPE NodeLink::get_input_type()
	{
		return m_input_type;
	}

	//std::string	NodeLink::get_var_name()
	//{
	//	std::string	ret_str=
	//		"var_"+
	//		std::to_string(m_output_id)+"_"+
	//		std::to_string(m_output_slot) + "_"+
	//		std::to_string(m_input_id) + "_"+
	//		std::to_string(m_input_slot);

	//	return	ret_str;
	//}
}