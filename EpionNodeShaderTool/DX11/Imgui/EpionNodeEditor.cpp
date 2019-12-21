#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/list.hpp>

#include	"EpionNodeEditor.h"
#include	"ImguiNodeContext.h"

#include	"Grid.h"
#include	"../../ImguiFunction.h"
#include	"../../Node/NodeParam.h"
#include	"../../Node/NodeData.h"

#include	"../../FileIO/Fileio_json.h"


//#pragma warning(disable:4996)

#define	DEBUG 1


namespace	epion::Node
{
	std::vector<std::unique_ptr<NodeBase>>	NodeEditor::nodes;
	std::vector<NodeLink>	NodeEditor::links;

	ImGuiWindowFlags NodeEditor::m_window_flags;


	bool	NodeEditor::m_is_node_import;
	bool	NodeEditor::m_is_node_moving;
	bool	NodeEditor::m_is_line;
	bool	NodeEditor::m_is_line_delete_menu;
	bool	NodeEditor::m_is_node_push;

	int	NodeEditor::m_node_select_num;
	int	NodeEditor::m_node_hovered_list;
	int	NodeEditor::m_node_hovered_in_scene;
	ClickState	NodeEditor::m_click_state;

	float	NodeEditor::m_scale;
	float	NodeEditor::m_delta;
	float	NodeEditor::m_line_size;

	ImVec2	NodeEditor::m_offset;
	ImVec2	NodeEditor::m_drag_offset;
	ImVec2	NodeEditor::m_screen_pos;

	int		NodeEditor::m_node_erase_num;
	bool	NodeEditor::m_is_node_erase_menu;

	bool	NodeEditor::m_is_node_widgets_active;
	bool	NodeEditor::m_is_now_any_active;
	bool	NodeEditor::m_is_old_any_active;

	ImVec2	NodeEditor::m_context_pos;
	ImVec2	NodeEditor::m_enclose_pos;
	ImVec2	NodeEditor::m_scrolling_pos;

}

namespace
{
	ImGuiCond_	state_bar = ImGuiCond_::ImGuiCond_Once;
	constexpr	float	NODE_SLOT_RADIUS = 5.0f;

}


namespace	epion::Node
{
	void	NodeEditor::Init()
	{
		m_is_node_import = false;
		m_is_line = false;
		m_is_line_delete_menu = false;
		m_node_select_num = INIT_NUM;
		m_node_hovered_list = INIT_NUM;
		m_click_state = { INIT_NUM,INIT_NUM,ImVec2(0, 0),	false,	false,	false };

		m_scale = zoom_levels[7];

		m_scrolling_pos = ImVec2(0, 0);
		m_delta = 1.0f;
		m_line_size = 3.0f;

		m_offset = ImVec2(0, 0);

		m_drag_offset = ImVec2(0, 0);

		m_node_erase_num = INIT_NUM;;
		m_is_node_erase_menu = false;

		m_screen_pos = ImVec2(1350, 1000);
		m_context_pos = { 0,0 };
		m_window_flags |= ImGuiWindowFlags_NoTitleBar;
		m_window_flags |= ImGuiWindowFlags_MenuBar;
		m_window_flags |= ImGuiWindowFlags_NoMove;
		m_window_flags |= ImGuiWindowFlags_NoResize;

	}

	void	NodeEditor::Update(bool* opened, std::string	node_bar_name)
	{
		m_offset = m_scrolling_pos;

		Node::ContextManager::Update(m_offset);

		ImGui::SetNextWindowSize(m_screen_pos, 1);
		std::string	node_name = node_bar_name;

		if (node_name.empty())	node_name = "Node CustomGraph";

		if (!ImGui::Begin(node_name.c_str(), nullptr, m_window_flags))
		{
			ImGui::End();
			return;
		}
		NodeTabBar();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColors::U32::BLACK);	//背景
		ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, 12);

		ImDrawList*	draw_list = ImGui::GetWindowDrawList();

		draw_list->ChannelsSplit(5);

		// Display grid
		epion::Node::Grids	grid(64.0f, IM_COL32(0, 200, 120, 120));

		grid.ShowGrid(draw_list, ImGui::GetCursorScreenPos(), ImGui::GetWindowSize(), m_scrolling_pos);

		// Display links
		DrawLinkLine(draw_list);

		NodeUpdate(draw_list);

		MouseUpdate(draw_list);

		if (m_node_hovered_list != INIT_NUM)
		{
			m_node_select_num = m_node_hovered_list;
		}
		if (m_node_hovered_in_scene != INIT_NUM)
		{
			m_node_select_num = m_node_hovered_in_scene;
		}
		if (!m_is_line)
		{
			ContextManager::CreateNodeMenu(m_offset);
		}
		ContextManager::LineEvent();

		ImGui::EndChild();
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
		ImGui::EndGroup();
		ImGui::End();
		//	ImGui::EndTabBar();
	}

	void	NodeEditor::Clear()
	{
		nodes.clear();
		links.clear();
	}

	void	NodeEditor::Release()
	{
	}

	void	NodeEditor::ImportNodeData(const std::string& nodejson)
	{
		nodes.clear();
		links.clear();

		epion::FileIO::FileIOJson	json_file;

		json_file.Input(nodejson, nodes, links);

		ContextManager::SetCreateCount(static_cast<int>(nodes.size()));
	}

	std::string	NodeEditor::ExportNodeData(const std::string& json_name)
	{
		std::string	name;

		epion::FileIO::FileIOJson	json_file;
		json_file.Output(json_name, nodes, links);
		return name;
	}

	//ノードを繋ぐ線の描画
	void	NodeEditor::DrawLinkLine(ImDrawList*	draw_list)
	{
		draw_list->ChannelsSetCurrent(2); // Line
#ifdef  DEBUG
		draw_list->AddCircle(ImGui::GetMousePos(), 10.0f, IM_COL32(255, 255, 255, 255));
#endif //  DEBUG

		for (auto& l : links)
		{
			ImVec2 right_pos = m_offset + nodes[l.GetInputID()]->GetInputSlotPos(l.GetInputSlot());
			ImVec2 left_pos = m_offset + nodes[l.GetOutputID()]->GetOutputSlotPos(l.GetOutputSlot());
			left_pos.y += 10.0f;
			right_pos.y += 10.0f;
			ImBezierClosestPoint(left_pos, left_pos + ImVec2(+50, 0), right_pos + ImVec2(-50, 0), right_pos, ImGui::GetIO().MousePos, m_line_size);
			if (physics::Collider2D::LineCircle(ImGuiFunction::GetFVector2(left_pos), ImGuiFunction::GetFVector2(right_pos), ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), 8.0f))
			{
				m_line_size = 10.0f;
				l.m_is_hit = true;
			}
			else
			{
				m_line_size = 3.0f;
				l.m_is_hit = false;
			}

			draw_list->AddBezierCurve(left_pos, left_pos + ImVec2(-50, 0), right_pos + ImVec2(50, 0), right_pos, NODE_LINE_COLOR, m_line_size);
		}

		if (m_is_line &&ImGui::IsMouseClicked(1))
		{
			m_is_line_delete_menu = true;
		}


		for (int i = 0; i < links.size(); i++)
		{
			if (m_is_line_delete_menu)
			{
				ImGui::OpenPopup("delete_menu");
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
				if (ImGui::BeginPopup("delete_menu"))
				{
					if (ImGui::MenuItem("Close"))
					{
						m_is_line_delete_menu = false;
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Delete"))
					{
						links.erase(links.begin() + i);
						m_is_line_delete_menu = false;
					}
					if (ImGui::IsMouseClicked(1))
					{
						m_is_line_delete_menu = false;
					}
					ImGui::EndPopup();
				}
				ImGui::PopStyleVar();
			}
		}

		for (auto& l : links)
		{
			if (l.m_is_hit)
			{
				m_is_line = true;
				break;
			}
			m_is_line = false;
		}
	}


#pragma region	Node
	void	NodeEditor::NodeUpdate(ImDrawList*	draw_list)
	{
		//マウス関連
		m_is_old_any_active = ImGui::IsAnyItemActive();

		m_is_node_widgets_active = (!m_is_old_any_active && ImGui::IsAnyItemActive());

		draw_list->ChannelsSetCurrent(1); // Background

		for (int node_size = 0; node_size < static_cast<int>(nodes.size()); node_size++)
		{
			ImGui::PushID(nodes[node_size]->m_ID);
			ImVec2 node_rect_min = m_offset + ImGuiFunction::GetImVec2(nodes[node_size]->m_Pos);
			//ImVec2 node_rect_max = node_rect_min + nodes[node_size]->m_Size;

			ImGui::SetCursorScreenPos(node_rect_min);
			NodeDrag(draw_list, node_size);
			NodeDraw(draw_list, node_size);
			NodeErase(draw_list, node_size);
			NodeInputUpdate(draw_list, node_size);
			NodeOutputUpdate(draw_list, node_size);

			ImGui::PopID();
		}
		draw_list->ChannelsMerge();
	}

	void NodeEditor::NodeDrag(ImDrawList* draw_list, int size)
	{
		ImGui::InvisibleButton("node", nodes[size]->m_Size);
		if (ImGui::IsItemHovered())
		{
			m_node_hovered_in_scene = nodes[size]->m_ID;
		}
		else
		{
			m_node_hovered_in_scene = INIT_NUM;
		}

		m_is_now_any_active = ImGui::IsItemActive();

		if (m_is_node_widgets_active || m_is_now_any_active)
		{
			m_node_select_num = nodes[size]->m_ID;
		}
		else
		{
			m_node_select_num = INIT_NUM;
		}

		if (m_is_now_any_active	&&
			ImGui::IsMouseDragging(0) &&
			!m_click_state.is_click_input_slot &&
			!m_click_state.is_click_output_slot)
		{
			nodes[size]->m_Pos = nodes[size]->m_Pos + ImGuiFunction::GetFVector2(ImGui::GetIO().MouseDelta);
		}
	}

	void NodeEditor::NodeDraw(ImDrawList* draw_list, int size)
	{
		//Nodeに当たったか
		if (m_node_hovered_list == nodes[size]->m_ID ||
			m_node_hovered_in_scene == nodes[size]->m_ID ||
			(m_node_hovered_list == INIT_NUM && m_node_select_num == nodes[m_is_node_push]->m_ID))
		{
			nodes[size]->m_is_push = true;

			if (!ImGui::IsMouseDoubleClicked(0))
			{
				nodes[size]->m_is_double_clicked = true;
				nodes[size]->m_is_push = false;
			}
		}
		else
		{
			nodes[size]->m_is_push = false;
		}

		draw_list->ChannelsSetCurrent(1);

		ImGui::SetWindowFontScale(1.0f);
		nodes[size]->TitleDraw(m_offset, draw_list, 1.0f);

		ImGui::SetWindowFontScale(0.9f);
		nodes[size]->Update(m_offset, draw_list);
		nodes[size]->ShaderUpdate(nodes, links);
	}

	void NodeEditor::NodeInputUpdate(ImDrawList* draw_list, int size)
	{
		for (int slot_input = 0; slot_input < nodes[size]->m_inputs_count; slot_input++)
		{
			ImVec2	input_slot_pos = m_offset + nodes[size]->GetInputSlotPos(slot_input);
			input_slot_pos.y += 10.0f;
			ImVec2	input_slot_pos2 = nodes[size]->GetInputSlotPos(slot_input);
			input_slot_pos2.y += 10.0f;

			//input slotをクリックしたとき
			if (!m_click_state.is_click_output_slot&&
				ImGui::IsMouseDown(0) &&
				physics::Collider2D::SphereAndSphere<float>(ImGuiFunction::GetFVector2(input_slot_pos), ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
			{
				m_click_state = { nodes[size]->m_ID,	slot_input,input_slot_pos2,	false,	true,	false };
				break;
			}

			//output slotをクリックしてる
			if (m_click_state.is_click_output_slot	&&ImGui::IsMouseReleased(0))
			{
				bool	is_hit = false;
				bool	is_input = false;
				if (physics::Collider2D::SphereAndSphere(ImGuiFunction::GetFVector2(input_slot_pos), ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
				{
					if (m_click_state.id != nodes[size]->m_ID)
					{
						for (auto& check_link : links)
						{
							//既にノードがあるか確認
							if (check_link == NodeLink(m_click_state.id, m_click_state.slot, nodes[size]->m_ID, slot_input))
							{
								is_hit = true;
								break;
							}
							if (check_link.GetInputID() == nodes[size]->m_ID&&
								check_link.GetInputSlot() == slot_input)
							{
								is_input = true;
								break;
							}
						}
						if (is_input)	links.erase(links.begin() + slot_input - 1);
						if (!is_hit)
						{
							links.push_back(NodeLink(m_click_state.id, m_click_state.slot, nodes[m_click_state.id]->m_output_slot_type[m_click_state.slot],
								nodes[size]->m_ID, slot_input, nodes[size]->m_input_slot_type[slot_input]));
						}
					}
					m_click_state = { INIT_NUM,	INIT_NUM,	ImVec2(0, 0),	false,	false,	false };
					break;
				}
			}
		}
	}
	void NodeEditor::NodeOutputUpdate(ImDrawList* draw_list, int size)
	{
		for (int slot_output = 0; slot_output < nodes[size]->m_outputs_count; slot_output++)
		{
			ImVec2	output_slot_pos = m_offset + nodes[size]->GetOutputSlotPos(slot_output);
			output_slot_pos.y += 10.0f;
			ImVec2	output_slot_pos2 = nodes[size]->GetOutputSlotPos(slot_output);
			output_slot_pos2.y += 10.0f;

			//output slotをクリックしたとき
			if (!m_click_state.is_click_input_slot&&
				ImGui::IsMouseDown(0) &&
				physics::Collider2D::SphereAndSphere(math::FVector2(output_slot_pos.x, output_slot_pos.y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				m_click_state = { nodes[size]->m_ID,	slot_output,	output_slot_pos2,false,false,true };
				break;
			}

			//input →outputにノードを挿入するとき
			if (m_click_state.is_click_input_slot	&&ImGui::IsMouseReleased(0))
			{
				bool	is_hit = false;
				if (physics::Collider2D::SphereAndSphere(math::FVector2(output_slot_pos.x, output_slot_pos.y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
				{
					if (m_click_state.id != nodes[size]->m_ID)
					{
						for (auto& check_link : links)
						{
							//既にノードがあるか確認
							if (check_link == NodeLink(nodes[size]->m_ID, slot_output, m_click_state.id, m_click_state.slot))
							{
								is_hit = true;
								break;
							}
						}
						if (!is_hit)
						{
							links.push_back(NodeLink(nodes[size]->m_ID, slot_output, nodes[size]->m_output_slot_type[slot_output],
								m_click_state.id, m_click_state.slot, nodes[m_click_state.id]->m_input_slot_type[m_click_state.slot]));
						}
					}
					m_click_state = { INIT_NUM,INIT_NUM,ImVec2(0, 0),	false,	false,	false };
					break;
				}
			}
		}
	}

	void NodeEditor::NodeTabBar()
	{
		ImGui::BeginChild("node_list", ImVec2(100, 0));
		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Node"))
			{
				if (ImGui::TreeNode("Nodes"))
				{
					ImGui::Separator();
					for (int node_idx = 0; node_idx < nodes.size(); node_idx++)
					{
						ImGui::PushID(nodes[node_idx]->m_ID);
						if (ImGui::Selectable(nodes[node_idx]->m_Name.c_str(), nodes[node_idx]->m_ID == m_node_select_num))
						{
							m_node_select_num = nodes[node_idx]->m_ID;
						}
						if (ImGui::IsItemHovered())
						{
							m_node_hovered_list = nodes[node_idx]->m_ID;
						}
						ImGui::PopID();
					}
					ImGui::TreePop();
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();
	}

	void NodeEditor::NodeErase(ImDrawList* draw_list, int size)
	{
		if (nodes[size]->m_is_push&& ImGui::IsMouseClicked(1))
		{
			ImGui::OpenPopup("d_m_n");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
			ImGui::SetNextWindowPos(ImGui::GetMousePos());
			if (ImGui::BeginPopup("d_m_n"))
			{
				if (ImGui::MenuItem("Delete"))
				{
					nodes.erase(nodes.begin() + size);
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}
	}

#pragma endregion

#pragma region	Mouse
	void	NodeEditor::MouseUpdate(ImDrawList* draw_list)
	{

		//右クリック
		//if (ImGui::IsAnyItemHovered&&ImGui::IsMouseClicked(1))
		//{
		//	if (ContextManager::get_is_line_menu())
		//	{
		//		ContextManager::SetLineMenu(false);
		//	}
		//	else
		//	{
		//		ContextManager::SetLineMenu(true);
		//	}

		//}
		CallContext();
		Drag(draw_list);
		Enclose(draw_list);
		Scroll();
	}

	void NodeEditor::CallContext()
	{
		if (!ImGui::IsAnyItemHovered() &&
		//	ImGui::IsMouseHoveringWindow()&&
			ImGui::IsMouseClicked(1) &&
			!ImGui::IsMouseClicked(0) &&
			!ContextManager::GetContext())
		{
			m_node_select_num = m_node_hovered_list = m_node_hovered_in_scene = INIT_NUM;
			m_context_pos = ImGui::GetIO().MousePos;
			ContextManager::OpenNodeCreateContext(true, ImGui::GetIO().MousePos);
		}
	}

	void NodeEditor::Drag(ImDrawList*	draw_list)
	{
		if (m_click_state.is_click_input_slot || m_click_state.is_click_output_slot)
		{
			draw_list->AddBezierCurve(m_click_state.pos + m_offset, m_click_state.pos + ImVec2(50, 0) + m_offset, ImGui::GetIO().MousePos, ImGui::GetIO().MousePos, NODE_LINE_COLOR, 4.0f);
			if (ImGui::IsMouseClicked(0))
			{
				m_click_state.is_click_input_slot = false;
				m_click_state.is_click_output_slot = false;
			}
		}
	}

	void NodeEditor::Enclose(ImDrawList* draw_list)
	{
		if (ImGui::IsMouseClicked(0))
		{
			if (!m_click_state.is_click_input_slot && !m_click_state.is_click_output_slot)
			{
				m_click_state.is_click_display = true;
				m_enclose_pos = ImGui::GetIO().MousePos;
			}
		}
		if (m_click_state.is_click_display	&&ImGui::IsMouseDragging(0))
		{
			draw_list->AddRect(m_enclose_pos, ImGui::GetIO().MousePos, IM_COL32(215, 15, 15, 255), 5.0f, 0);
		}
	}

	void NodeEditor::Scroll()
	{
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(2, 0.0f))
		{
			m_scrolling_pos = m_scrolling_pos + ImGui::GetIO().MouseDelta;
			m_scrolling_pos.x = std::clamp(m_scrolling_pos.x, -500.0f, 500.0f);
			m_scrolling_pos.y = std::clamp(m_scrolling_pos.y, -500.0f, 500.0f);
		}

		//if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsAnyMouseDown)
		//{
		//}
	}
#pragma endregion

#pragma region	Get
	ImVec2&	NodeEditor::GetScrolling()
	{
		return	m_scrolling_pos;
	}

	ImVec2&	NodeEditor::GetOffset()
	{
		return	m_offset;
	}

	int NodeEditor::GetNodeSize()
	{
		return	static_cast<int>(nodes.size());
	}

	int NodeEditor::GetLinkSize()
	{
		return	static_cast<int>(links.size());
	}
#pragma endregion

}