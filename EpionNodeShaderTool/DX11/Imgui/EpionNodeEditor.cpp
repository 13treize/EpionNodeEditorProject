#include	"../../All.h"
#include	"../../epion.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/list.hpp>

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"EpionNodeEditor.h"
#include	"epion_imgui_node_context.h"

#include	"grid.h"
#include	"../../ImguiFunction.h"
#include	"../../Node/NodeParam.h"
#include	"../../Node/NodeData.h"
//#include	"../../Node/MasterNode.h"
//#include	"../../Node/PBRNode.h"

#include	"../../FileIO/Fileio_json.h"


#pragma warning(disable:4996)

#define	DEBUG 1


namespace	epion::NodeCustom
{
	std::vector<std::unique_ptr<NodeBase>>	NodeEditor::nodes;
	std::vector<NodeLink>	NodeEditor::links;

	ImGuiWindowFlags NodeEditor::m_window_flags;


	bool	NodeEditor::m_is_node_import;
	bool	NodeEditor::m_is_node_moving;
	bool	NodeEditor::m_is_line;
	bool	NodeEditor::m_is_line_delete_menu;

	int	NodeEditor::m_node_select_num;
	int	NodeEditor::m_node_hovered_list;
	int	NodeEditor::m_node_hovered_in_scene;
	ClickState	NodeEditor::m_click_state;


	float	NodeEditor::m_scale;
	ImVec2	NodeEditor::m_scrolling;
	float	NodeEditor::m_delta;
	float	NodeEditor::m_line_size;

	ImVec2	NodeEditor::m_offset;
	ImVec2	NodeEditor::m_drag_offset;
	ImVec2	NodeEditor::m_screen_pos;
	ImVec2	NodeEditor::m_context_pos;
}

namespace
{
	ImGuiCond_	state_bar	=ImGuiCond_::ImGuiCond_Once;
	constexpr	float	NODE_SLOT_RADIUS	=5.0f;
	const	ImVec2	NODE_WINDOW_PADDING(165.0f, 165.0f);
	const	ImVec2	NODE_FONT_POS(64.0f, 10.0f);

	ImU32	NODE_LINE_COLOR	= IM_COL32(0, 150, 250, 250);



	std::string	name = "GenerateNodeJson\\test.json";

	epion::math::FVector2 getFVec2(ImVec2& vec2)
	{
		return epion::math::FVector2(vec2.x, vec2.y);
	}
	ImVec2 getImVec2(epion::math::FVector2& vec2)
	{
		return ImVec2(vec2.x, vec2.y);
	}
}


namespace	epion::NodeCustom
{
	void	NodeEditor::Init()
	{
		m_is_node_import = false;
		m_is_line = false;
		m_is_line_delete_menu = false;
		m_node_select_num = INIT_NUM;
		m_node_hovered_list = INIT_NUM;
		m_click_state = { INIT_NUM,INIT_NUM,ImVec2(0, 0),	false,	false,	false };

		m_scale=zoom_levels[7];

		m_scrolling = ImVec2(0, 0);
		m_delta =1.0f;
		m_line_size = 3.0f;

		m_offset = ImVec2(0, 0);
		m_drag_offset = ImVec2(0, 0);

		m_screen_pos = ImVec2(1350, 1000);
		m_context_pos = {0,0};
		m_window_flags |= ImGuiWindowFlags_NoTitleBar;
		m_window_flags |= ImGuiWindowFlags_MenuBar;
		m_window_flags |= ImGuiWindowFlags_NoMove;
		m_window_flags |= ImGuiWindowFlags_NoResize;

	}

	void	NodeEditor::Update(bool* opened,std::string	node_bar_name)
	{
		NodeCustom::ContextManager::Update(m_offset);

		ImGui::SetNextWindowSize(m_screen_pos,1);
		std::string	node_name = node_bar_name;


		if(node_name.empty())	node_name = "Node CustomGraph";

		if (!ImGui::Begin(node_name.c_str(),nullptr, m_window_flags))
		{
			ImGui::End();
			return;
		}

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
		ImGui::SameLine();

		ImGui::BeginGroup();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleColor(ImGuiCol_Border,	ImColor::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColor::U32::BLACK);	//背景
		ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, 12);

		m_offset = ImGui::GetCursorScreenPos() + m_scrolling;
		ImDrawList*	draw_list = ImGui::GetWindowDrawList();

		draw_list->ChannelsSplit(5);

		// Display grid
		epion::NodeCustom::Grids	grid;
		grid.Init(64.0f, IM_COL32(0, 200, 120, 120));

		grid.ShowGrid(draw_list, ImGui::GetCursorScreenPos(),ImGui::GetWindowSize(), m_scrolling);

		// Display links
		draw_node_line(draw_list);

		mouse_update();

		create_node_data(draw_list, m_node_hovered_in_scene);

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
			ContextManager::ClickEvent();
		}
		ContextManager::LineEvent();
		ScrollingEvent();

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

	void	NodeEditor::release()
	{

	}
	void	NodeEditor::mouse_update()
	{
		if (ImGui::IsMouseDown(0))
		{
			if (!m_click_state.is_click_input_slot && !m_click_state.is_click_output_slot)
			{
				m_click_state.is_click_display = true;
				m_click_state.pos = ImGui::GetIO().MousePos;
			}
		}
		//右クリック
		//if (ImGui::IsAnyItemHovered&&ImGui::IsMouseClicked(1))
		//{
		//	if (ContextManager::get_is_line_menu())
		//	{
		//		ContextManager::set_is_line_menu(false);
		//	}
		//	else
		//	{
		//		ContextManager::set_is_line_menu(true);
		//	}

		//}
		if (!ImGui::IsAnyItemHovered() && ImGui::IsMouseHoveringWindow() && ImGui::IsMouseClicked(1) && !ImGui::IsMouseClicked(0))
		{
			if (ContextManager::GetContext())
			{
				ContextManager::SetContext(false);
			}
			else
			{
				m_node_select_num = m_node_hovered_list = m_node_hovered_in_scene = INIT_NUM;
				m_context_pos = ImGui::GetIO().MousePos;
				ContextManager::SetContext(true);
			}
		}
	}


	void	NodeEditor::constant_state_update()
	{

	}

	void	NodeEditor::import_node_data(std::string nodejson)
	{
			nodes.clear();
			links.clear();

			epion::FileIO::FileIOJson	json_file;

			json_file.Input(nodejson, nodes, links);
	}

	void	NodeEditor::default_setting_unlit()
	{
		nodes.clear();
		links.clear();
		//nodes.push_back(std::make_unique<UnlitMasterNode>(nodes.size(), math::FVector2(500, 50)));
	}
	std::string	NodeEditor::ExportNodeData(const std::string& json_name)
	{
		epion::FileIO::FileIOJson	json_file;
		json_file.Output(json_name,	nodes,	links);
		return name;
	}

	//ノードを繋ぐ線の描画
	void	NodeEditor::draw_node_line(ImDrawList*	draw_list)
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

			if (physics::Collider2D::LineCircle(::getFVec2(left_pos), ::getFVec2(right_pos), ::getFVec2(ImGui::GetIO().MousePos), 8.0f))
			{
				m_line_size = 10.0f;
				if (ImGui::IsMouseClicked(1))
				{
					m_is_line_delete_menu =true;

				}
				l.m_is_hit = true;
			}
			else
			{
				m_line_size = 3.0f;
				l.m_is_hit = false;
			}

			draw_list->AddBezierCurve(left_pos, left_pos /*+ ImVec2(+50, 0)*/, right_pos /*+ ImVec2(-50, 0)*/, right_pos, NODE_LINE_COLOR, m_line_size);
		}


		for (int i = 0; i < links.size(); i++)
		{
			if(m_is_line_delete_menu)
			{
				ImGui::OpenPopup("context_menu");
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
				if (ImGui::BeginPopup("context_menu"))
				{
					if (ImGui::MenuItem("Delete", nullptr))
					{
						links.erase(links.begin() + i);
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

	void	NodeEditor::create_node_data(ImDrawList*	draw_list,int scene)
	{
		static	bool is_init_size = false;

		for (int node_size = 0; node_size < static_cast<int>(nodes.size()); node_size++)
		{
			ImGui::PushID(nodes[node_size]->m_ID);
			ImVec2 node_rect_min = m_offset + ::getImVec2(nodes[node_size]->m_Pos);
			ImVec2 node_rect_max = node_rect_min + nodes[node_size]->m_Size;

			// Display node contents first
			draw_list->ChannelsSetCurrent(2); // Foreground

			//マウス関連
			bool old_any_active = ImGui::IsAnyItemActive();

			bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());

			if (!is_init_size)
			{
				if (nodes[node_size]->m_inputs_count < nodes[node_size]->m_outputs_count)
				{
					nodes[node_size]->m_Size = { NODE_MIN_SIZE.x + NODE_SIZE * nodes[node_size]->m_outputs_count ,
													NODE_MIN_SIZE.y + NODE_SIZE * nodes[node_size]->m_outputs_count };
				}
				else
				{
					nodes[node_size]->m_Size = { NODE_MIN_SIZE.x + NODE_SIZE * nodes[node_size]->m_inputs_count ,
													NODE_MIN_SIZE.y + NODE_SIZE * nodes[node_size]->m_inputs_count };
				}
			}

			// Display node box
			draw_list->ChannelsSetCurrent(1); // Background
			ImGui::SetCursorScreenPos(node_rect_min);
			ImGui::InvisibleButton("node", nodes[node_size]->m_Size);
			if (ImGui::IsItemHovered())
			{
				scene = nodes[node_size]->m_ID;
			}

			bool node_moving_active = ImGui::IsItemActive();
			if (node_widgets_active || node_moving_active)
			{
				m_node_select_num = nodes[node_size]->m_ID;
			}
			else
			{
				m_node_select_num = INIT_NUM;
			}

			//ノードのブロックを動かす
			if (node_moving_active	&&ImGui::IsMouseDragging(0) && !m_click_state.is_click_input_slot && !m_click_state.is_click_output_slot)
			{
				nodes[node_size]->m_Pos = nodes[node_size]->m_Pos + getFVec2(ImGui::GetIO().MouseDelta);
			}


			for (int slot_input = 0; slot_input < nodes[node_size]->m_inputs_count; slot_input++)
			{
				ImVec2	input_slot_pos = m_offset + nodes[node_size]->GetInputSlotPos(slot_input);
				input_slot_pos.y += 10.0f;
				ImVec2	input_slot_pos2 = nodes[node_size]->GetInputSlotPos(slot_input);
				input_slot_pos2.y += 10.0f;

				//input slotをクリックしたとき
				if (!m_click_state.is_click_output_slot&&
					ImGui::IsMouseDown(0) &&
					physics::Collider2D::SphereAndSphere<float>(getFVec2(input_slot_pos), getFVec2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
				{
					m_click_state = { nodes[node_size]->m_ID,	slot_input,input_slot_pos2,	false,	true,	false };
					break;
				}

				//output slotをクリックしてる
				if (m_click_state.is_click_output_slot	&&ImGui::IsMouseReleased(0))
				{
					bool	is_hit = false;
					bool	is_input = false;
					if (physics::Collider2D::SphereAndSphere(::getFVec2(input_slot_pos), ::getFVec2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
					{
						if (m_click_state.id != nodes[node_size]->m_ID)
						{
							for (auto& check_link : links)
							{
								//既にノードがあるか確認
								if (check_link == NodeLink(m_click_state.id, m_click_state.slot, nodes[node_size]->m_ID, slot_input))
								{
									is_hit = true;
									break;
								}
								if (check_link.GetInputID() == nodes[node_size]->m_ID&&
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
									nodes[node_size]->m_ID, slot_input, nodes[node_size]->m_input_slot_type[slot_input]));
							}
						}
						m_click_state = { INIT_NUM,	INIT_NUM,	ImVec2(0, 0),	false,	false,	false };
						break;
					}
				}
			}


			for (int slot_output = 0; slot_output < nodes[node_size]->m_outputs_count; slot_output++)
			{
				ImVec2	output_slot_pos = m_offset + nodes[node_size]->GetOutputSlotPos(slot_output);
				output_slot_pos.y += 10.0f;
				ImVec2	output_slot_pos2 = nodes[node_size]->GetOutputSlotPos(slot_output);
				output_slot_pos2.y += 10.0f;

				//output slotをクリックしたとき
				if (!m_click_state.is_click_input_slot&&
					ImGui::IsMouseDown(0) &&
					physics::Collider2D::SphereAndSphere(math::FVector2(output_slot_pos.x, output_slot_pos.y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
				{
					m_click_state = { nodes[node_size]->m_ID,	slot_output,	output_slot_pos2,false,false,true };
					break;
				}

				//input →outputにノードを挿入するとき
				if (m_click_state.is_click_input_slot	&&ImGui::IsMouseReleased(0))
				{
					bool	is_hit = false;
					if (physics::Collider2D::SphereAndSphere(math::FVector2(output_slot_pos.x, output_slot_pos.y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
					{
						if (m_click_state.id != nodes[node_size]->m_ID)
						{
							for (auto& check_link : links)
							{
								//既にノードがあるか確認
								if (check_link == NodeLink(nodes[node_size]->m_ID, slot_output, m_click_state.id, m_click_state.slot))
								{
									is_hit = true;
									break;
								}

							}
							if (!is_hit)
							{
								links.push_back(NodeLink(nodes[node_size]->m_ID, slot_output, nodes[node_size]->m_output_slot_type[slot_output],
									m_click_state.id, m_click_state.slot, nodes[m_click_state.id]->m_input_slot_type[m_click_state.slot]));
							}
						}
						m_click_state = { INIT_NUM,INIT_NUM,ImVec2(0, 0),	false,	false,	false };
						break;
					}
				}
			}


			//ノードからマウスまでの描画
			if (m_click_state.is_click_input_slot || m_click_state.is_click_output_slot)
			{
				draw_list->AddBezierCurve(m_click_state.pos + m_offset, m_click_state.pos + ImVec2(50, 0) + m_offset, ImGui::GetIO().MousePos, ImGui::GetIO().MousePos, NODE_LINE_COLOR, 4.0f);
			}

			if (m_click_state.is_click_display	&&ImGui::IsMouseDragging(0))
			{
				draw_list->AddRect(m_click_state.pos, ImGui::GetIO().MousePos, IM_COL32(215, 15, 15, 255), 5.0f, 0);
			}

			//nodeに当たったか
			bool is_push;
			if (m_node_hovered_list == nodes[node_size]->m_ID ||
				scene == nodes[node_size]->m_ID ||
				(m_node_hovered_list == INIT_NUM && m_node_select_num == nodes[node_size]->m_ID))
			{
				is_push = true;
			}
			else
			{
				is_push = false;
			}

			draw_list->ChannelsSetCurrent(1);//NodeDraw

			//Node本体、文字描画
			ImGui::SetWindowFontScale(1.0f);
			nodes[node_size]->TitleDraw(m_offset, draw_list, is_push);


			ImGui::SetWindowFontScale(0.9f);
			//input slot circledraw
			nodes[node_size]->Update(m_offset, draw_list);

			nodes[node_size]->ShaderUpdate(nodes, links);

			ImGui::PopID();
		}
	draw_list->ChannelsMerge();
	}

	void	NodeEditor::draw_node_rect()
	{
	}

	void	NodeEditor::ScrollingEvent()
	{
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(2, 0.0f))
		{
			m_scrolling = m_scrolling + ImGui::GetIO().MouseDelta;
			m_scrolling.x = std::clamp(m_scrolling.x, -500.0f, 500.0f);
			m_scrolling.y = std::clamp(m_scrolling.y, -500.0f, 500.0f);
		}
	}

	void	NodeEditor::create_hlsl()
	{
	}

	//get
	ImVec2&	NodeEditor::GetScrolling()
	{
		return	m_scrolling;
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
}