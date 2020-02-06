#include	"../All.h"
#include	"../epion.h"
#include	"../../imgui/imgui.h"
#include	"../../imgui/imgui_impl_win32.h"
#include	"../../imgui/imgui_impl_dx11.h"
#include	"../../imgui/imgui_internal.h"

#include	"NodeContext.h"
#include	"../Scene/SceneManager.h"
#include	"../Scene/SceneDemo2D.h"
#include	"../Scene/SceneDemo3D.h"

#include	"../ImguiFunction.h"
#include	"../Node/NodeParam.h"

#include	"NodeWindow.h"



namespace
{
	constexpr	float	NODE_SLOT_RADIUS = 5.0f;
}

//for (int i = 0; i < node_names.size(); i++)
//{
//	if (ImGui::BeginDragDropTarget())
//	{
//		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
//		{
//			IM_ASSERT(payload->DataSize == sizeof(int));
//			int payload_n = *(const int*)payload->Data;
//			node_names[0] = node_names[payload_n];
//		}
//		ImGui::EndDragDropTarget();
//	}
//}

namespace epion::GUI
{

	bool NodeWindow::Init()
	{
		m_bar_flags = 0;
		m_bar_flags |= ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTooltip;
		m_bar_flags |= ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTabListScrollingButtons;
		m_bar_flags |= ImGuiTabBarFlags_::ImGuiTabBarFlags_TabListPopupButton;

		m_nodes.clear();
		m_links.clear();
		m_hit_line_num = 0;
		m_line_size = 0.0f;
		m_is_line_hit = false;
		m_is_slot_hit = false;
		m_scroll_scale = 1.0f;
		m_offset = ImVec2(0, 0);
		ContextManager::Init();

		return true;
	}
	void NodeWindow::Update(std::vector<std::string>&	node_names)
	{
		ContextManager::Update(m_offset, m_nodes);

		ChildSettings();
		ImGui::BeginChild("NodeWindow", ImVec2(1400, 670));
		ImDrawList*	draw_list = ImGui::GetWindowDrawList();
		draw_list->ChannelsSplit(5);

		BackGrids grid(64.0f, IM_COL32(0, 200, 120, 120));

		if (ImGui::BeginTabBar("##tabs", m_bar_flags))
		{
			if (ImGui::BeginTabItem("Node"))
			{
				grid.Draw(draw_list, ImGui::GetCursorScreenPos(), ImGui::GetWindowSize(), m_offset);

				DrawLinkLine(draw_list);

				NodeUpdate(draw_list);

				MouseUpdate(draw_list);

				if (m_node_hovered_list != Node::INIT_NUM)
				{
					m_node_select_num = m_node_hovered_list;
				}
				if (m_node_hovered_in_scene != Node::INIT_NUM)
				{
					m_node_select_num = m_node_hovered_in_scene;
				}
				//	ContextManager::ClickEvent(m_offset);

					//ContextManager::LineEvent();

				ImGui::EndTabItem();
			}
			//if (ImGui::BeginTabItem("Demo"))
			//{
			//	//ImGui::Image(SceneManager::GetTexData()->m_shader_resource.Get(), ImVec2(1400, 670), ImVec2(0, 0), ImVec2(1.0, 1.0), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));
			//	ImGui::EndTabItem();
			//}

			ImGui::EndTabBar();
		}
		ImGui::EndChild();

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
	}

	void NodeWindow::ChildSettings()
	{
		ImGui::SetNextWindowPos(ImVec2(30, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, ImColors::U32::GRAYBLACK);
	}

	void NodeWindow::DrawLinkLine(ImDrawList* draw_list)
	{
		draw_list->ChannelsSetCurrent(2); // Line
#ifdef DEBUG
		draw_list->AddCircle(ImGui::GetMousePos(), 10.0f, IM_COL32(255, 255, 255, 255));
#endif //  DEBUG

		for (auto& l : m_links)
		{
			ImVec2 right_pos = m_offset + m_nodes[l.GetInputID()]->GetInputSlotPos(l.GetInputSlot());
			ImVec2 left_pos = m_offset + m_nodes[l.GetOutputID()]->GetOutputSlotPos(l.GetOutputSlot());
			left_pos.y += 10.0f;
			right_pos.y += 10.0f;
			ImVec2 get_pos = ImBezierClosestPoint(left_pos, left_pos + Node::BEZIERCURVE_LEFT_POS, right_pos + Node::BEZIERCURVE_RIGHT_POS, right_pos, ImGui::GetIO().MousePos, 12.0f);

			if (physics::Collider2D::SphereAndSphere(ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), ImGuiFunction::GetFVector2(get_pos), 8.0f))
			{
				draw_list->AddBezierCurve(left_pos, left_pos + Node::BEZIERCURVE_LEFT_POS, right_pos + Node::BEZIERCURVE_RIGHT_POS, right_pos, Node::NODE_LINE_HIT_COLOR, 7.0f, 12.0f);
				l.m_is_hit = true;
			}
			else
			{
				m_line_size = 3.0f;
				l.m_is_hit = false;
			}
			draw_list->AddBezierCurve(left_pos, left_pos + Node::BEZIERCURVE_LEFT_POS, right_pos + Node::BEZIERCURVE_RIGHT_POS, right_pos, Node::NODE_LINE_COLOR, m_line_size, 12.0f);
		}

		for (int i=0;i< m_links.size();i++)
		{
			if (m_links[i].m_is_hit)
			{
				m_hit_line_num = i;
				m_is_line_hit = true;
				break;
			}
			m_is_line_hit = false;
		}
	}

#pragma region Node
	void	NodeWindow::NodeUpdate(ImDrawList*	draw_list)
	{
		//	draw_list->ChannelsSetCurrent(1); // Background

		for (int node_size = 0; node_size < static_cast<int>(m_nodes.size()); node_size++)
		{
			ImGui::PushID(m_nodes[node_size]->m_ID);
			ImVec2 node_rect_min = m_offset + ImGuiFunction::GetImVec2(m_nodes[node_size]->m_Pos);

			ImGui::SetCursorScreenPos(node_rect_min);
			NodeMouseUpdate(draw_list, node_size);
			NodeDraw(draw_list, node_size);
			//NodeErase(draw_list, node_size);
			NodeInputUpdate(draw_list, node_size);
			NodeOutputUpdate(draw_list, node_size);

			ImGui::PopID();
		}
		draw_list->ChannelsMerge();
	}
	void NodeWindow::NodeMouseUpdate(ImDrawList* draw_list, int size)
	{
		//マウス関連
		m_is_old_any_active = ImGui::IsAnyItemActive();

		m_is_node_widgets_active = (!m_is_old_any_active && ImGui::IsAnyItemActive());

		ImGui::InvisibleButton("Nodes", m_nodes[size]->m_Size);
		if (ImGui::IsItemHovered())
		{
			m_node_hovered_in_scene = m_nodes[size]->m_ID;
		}
		else
		{
			m_node_hovered_in_scene = Node::INIT_NUM;
		}

		m_is_now_any_active = ImGui::IsItemActive();
		if (m_is_node_widgets_active ||
			m_is_now_any_active)
		{
			m_node_select_num = m_nodes[size]->m_ID;
		}
		else
		{
			m_node_select_num = Node::INIT_NUM;
		}

		//Nodeに当たったか
		if (
			//m_node_hovered_list == m_nodes[size]->m_ID ||
			m_node_hovered_in_scene == m_nodes[size]->m_ID ||
			m_node_select_num == m_nodes[m_is_node_push]->m_ID)
		{
			m_nodes[size]->m_is_push = true;
		}
		else
		{
			m_nodes[size]->m_is_push = false;
		}

		if (m_nodes[size]->m_is_push &&
			ImGui::IsMouseDoubleClicked(0))
		{
			m_nodes[size]->m_is_double_clicked = true;
			m_nodes[size]->m_is_push = false;
		}

		if (m_is_now_any_active	&&
			ImGui::IsMouseDragging(0) &&
			!m_click_state.is_click_input_slot &&
			!m_click_state.is_click_output_slot)
		{
			m_nodes[size]->m_Pos = m_nodes[size]->m_Pos + ImGuiFunction::GetFVector2(ImGui::GetIO().MouseDelta);
		}
	}

	void NodeWindow::NodeDraw(ImDrawList* draw_list, int size)
	{
		m_nodes[size]->SetDrawPos(m_offset);
		draw_list->ChannelsSetCurrent(1);

		ImGui::SetWindowFontScale(1.0f);

		m_nodes[size]->TitleDraw(m_offset, draw_list, m_scroll_scale);

		ImGui::SetWindowFontScale(0.9f *m_scroll_scale);
		m_nodes[size]->Update(m_offset, draw_list);
		m_nodes[size]->ShaderUpdate(m_nodes, m_links);
	}

	void NodeWindow::NodeInputUpdate(ImDrawList* draw_list, int size)
	{
		for (int slot_input = 0; slot_input < m_nodes[size]->m_inputs_count; slot_input++)
		{
			ImVec2	input_slot_pos = m_offset + m_nodes[size]->GetInputSlotPos(slot_input);
			input_slot_pos.y += 10.0f;
			ImVec2	input_slot_pos2 = m_nodes[size]->GetInputSlotPos(slot_input);
			input_slot_pos2.y += 10.0f;

			//input slotをクリックしたとき
			if (!m_click_state.is_click_output_slot&&
				ImGui::IsMouseDown(0) &&
				physics::Collider2D::SphereAndSphere<float>(ImGuiFunction::GetFVector2(input_slot_pos), ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
			{
				m_click_state = { m_nodes[size]->m_ID,	slot_input,input_slot_pos2,	false,	true,	false };
				break;
			}

			//output slotをクリックしてる
			if (m_click_state.is_click_output_slot	&&ImGui::IsMouseReleased(0))
			{
				m_is_slot_hit = false;
				bool	is_input = false;
				if (physics::Collider2D::SphereAndSphere(ImGuiFunction::GetFVector2(input_slot_pos), ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
				{
					if (m_click_state.id != m_nodes[size]->m_ID)
					{
						for (auto& check_link : m_links)
						{
							//既にノードがあるか確認
							if (check_link == Node::NodeLink(m_click_state.id, m_click_state.slot, m_nodes[size]->m_ID, slot_input))
							{
								m_is_slot_hit = true;
								break;
							}
							if (check_link.GetInputID() == m_nodes[size]->m_ID&&
								check_link.GetInputSlot() == slot_input)
							{
								is_input = true;
								break;
							}
						}
						if (is_input)	m_links.erase(m_links.begin() + slot_input - 1);
						if (!m_is_slot_hit)
						{
							m_links.push_back(Node::NodeLink(m_click_state.id, m_click_state.slot, m_nodes[m_click_state.id]->m_output_slot_type[m_click_state.slot],
								m_nodes[size]->m_ID, slot_input, m_nodes[size]->m_input_slot_type[slot_input]));
						}
					}
					m_click_state = { Node::INIT_NUM,	Node::INIT_NUM,	ImVec2(0, 0),	false,	false,	false };
					break;
				}
			}
		}
	}
	void NodeWindow::NodeOutputUpdate(ImDrawList* draw_list, int size)
	{
		for (int slot_output = 0; slot_output < m_nodes[size]->m_outputs_count; slot_output++)
		{
			ImVec2	output_slot_pos = m_offset + m_nodes[size]->GetOutputSlotPos(slot_output);
			output_slot_pos.y += 10.0f;
			ImVec2	output_slot_pos2 = m_nodes[size]->GetOutputSlotPos(slot_output);
			output_slot_pos2.y += 10.0f;

			//output slotをクリックしたとき
			if (!m_click_state.is_click_input_slot&&
				ImGui::IsMouseDown(0) &&
				physics::Collider2D::SphereAndSphere(math::FVector2(output_slot_pos.x, output_slot_pos.y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				m_click_state = { m_nodes[size]->m_ID,	slot_output,	output_slot_pos2,false,false,true };
				break;
			}

			//input →outputにノードを挿入するとき
			if (m_click_state.is_click_input_slot	&&ImGui::IsMouseReleased(0))
			{
				m_is_slot_hit = false;
				if (physics::Collider2D::SphereAndSphere(math::FVector2(output_slot_pos.x, output_slot_pos.y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
				{
					if (m_click_state.id != m_nodes[size]->m_ID)
					{
						for (auto& check_link : m_links)
						{
							//既にノードがあるか確認
							if (check_link == Node::NodeLink(m_nodes[size]->m_ID, slot_output, m_click_state.id, m_click_state.slot))
							{
								m_is_slot_hit = true;
								break;
							}
						}
						if (!m_is_slot_hit)
						{
							m_links.push_back(Node::NodeLink(m_nodes[size]->m_ID, slot_output, m_nodes[size]->m_output_slot_type[slot_output],
								m_click_state.id, m_click_state.slot, m_nodes[m_click_state.id]->m_input_slot_type[m_click_state.slot]));
						}
					}
					m_click_state = { Node::INIT_NUM,Node::INIT_NUM,ImVec2(0, 0),	false,	false,	false };
					break;
				}
			}
		}
	}

	void NodeWindow::NodeTabBar()
	{
		//ImGui::BeginChild("node_list", ImVec2(100, 0));
		//if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		//{
		//	if (ImGui::BeginTabItem("Node"))
		//	{
		//		if (ImGui::TreeNode("Nodes"))
		//		{
		//			ImGui::Separator();
		//			for (int i = 0; i < m_nodes.size(); i++)
		//			{
		//				ImGui::PushID(m_nodes[i]->m_ID);
		//				if (ImGui::Selectable(m_nodes[i]->m_Name.c_str(), m_nodes[i]->m_ID == m_node_select_num))
		//				{
		//					m_node_select_num = m_nodes[i]->m_ID;
		//				}
		//				if (ImGui::IsItemHovered())
		//				{
		//					m_node_hovered_list = m_nodes[i]->m_ID;
		//				}
		//				ImGui::PopID();
		//			}
		//			ImGui::TreePop();
		//		}
		//		ImGui::EndTabItem();
		//	}
		//	ImGui::EndTabBar();
		//}
		//ImGui::EndChild();
	}

	void NodeWindow::NodeErase(ImDrawList* draw_list, int size)
	{
		if (m_nodes[size]->m_is_push&& ImGui::IsMouseClicked(1))
		{
			ImGui::OpenPopup("d_m_n");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
			ImGui::SetNextWindowPos(ImGui::GetMousePos());
			if (ImGui::BeginPopup("d_m_n"))
			{
				if (ImGui::MenuItem("Delete"))
				{
					m_nodes.erase(m_nodes.begin() + size);
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}
	}

#pragma endregion

#pragma region	Mouse
	void NodeWindow::MouseUpdate(ImDrawList* draw_list)
	{
		CallContext();
		Drag(draw_list);
		Enclose(draw_list);
		Scroll();
	}


	void NodeWindow::CallContext()
	{
		if (m_is_line_hit)
		{
			if (!ImGui::IsAnyItemHovered() &&
				ImGui::IsMouseClicked(1) &&	//右クリック
				!ImGui::IsMouseClicked(0))	//!左クリック
			{
				ContextManager::OpenLineDeleteContext(ImGui::GetIO().MousePos);
			}
		}
		else
		{
			if(	ImGui::IsMouseClicked(1) &&	//右クリック
				!ImGui::IsMouseClicked(0))	//!左クリック
			{
				if (!ImGui::IsAnyItemHovered())
				{
					m_node_select_num = m_node_hovered_list = m_node_hovered_in_scene = Node::INIT_NUM;
					ContextManager::OpenNodeCreateContext(ImGui::GetIO().MousePos);
				}
				else
				{
					m_node_select_num = m_node_hovered_list = m_node_hovered_in_scene = Node::INIT_NUM;
					ContextManager::OpenNodeDeleteContext(ImGui::GetIO().MousePos);
				}
			}
		}
		ContextManager::CreateNodeMenu(m_offset);
		//ContextManager::DeleteNodeMenu(m_nodes,m_hit_line_num);
		ContextManager::DeleteLineMenu(m_links,m_hit_line_num);
	}

	void NodeWindow::Drag(ImDrawList*	draw_list)
	{
		if (m_click_state.is_click_input_slot ||
			m_click_state.is_click_output_slot)
		{
			draw_list->AddBezierCurve(m_click_state.pos + m_offset, m_click_state.pos + ImVec2(50, 0) + m_offset, ImGui::GetIO().MousePos, ImGui::GetIO().MousePos, Node::NODE_LINE_COLOR, 4.0f);
			//ドラッグをやめる
			if (ImGui::IsMouseClicked(0))
			{
				m_click_state.is_click_input_slot = false;
				m_click_state.is_click_output_slot = false;
			}
		}
	}

	void NodeWindow::Enclose(ImDrawList* draw_list)
	{
		if (ImGui::IsMouseClicked(0) &&
			!m_click_state.is_click_input_slot &&
			!m_click_state.is_click_output_slot)
		{
			m_click_state.is_click_display = true;
			m_enclose_pos = ImGui::GetIO().MousePos;
		}
		if ((!m_click_state.is_click_input_slot ||
			!m_click_state.is_click_output_slot) &&
			m_click_state.is_click_display	&&
			ImGui::IsMouseDragging(0))
		{
			draw_list->AddRect(m_enclose_pos, ImGui::GetIO().MousePos, IM_COL32(215, 15, 15, 255), 5.0f, 0);
		}
	}

	void NodeWindow::Scroll()
	{
		if (ImGui::IsWindowHovered() &&
			!ImGui::IsAnyItemActive() &&
			ImGui::IsMouseDragging(2, 0.0f))
		{
			m_offset = m_offset + ImGui::GetIO().MouseDelta;
			m_offset.x = std::clamp(m_offset.x, -1000.0f, 1000.0f);
			m_offset.y = std::clamp(m_offset.y, -1000.0f, 1000.0f);
		}
	}
#pragma endregion

	std::vector<std::unique_ptr<Node::NodeBase>>&	NodeWindow::GetNodes()
	{
		return m_nodes;
	}

	std::vector<Node::NodeLink>&	NodeWindow::GetLinks()
	{
		return m_links;
	}

}