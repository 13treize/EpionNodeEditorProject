#include	"../All.h"
#include	"../epion.h"

#include	"../../imgui\\imgui.h"
#include	"../../imgui\\imgui_internal.h"

#include	"NodeEditor.h"

#include	"NodeContext.h"

#include	"../Node/NodeData.h"
#include	"../Node/ArtisticAdjustment.h"

#include	"../Node/ChannelNode.h"

#include	"../Node/NoiseNode.h"
#include	"../Node/MasterNode.h"
#include	"../Node/PBRNode.h"

#include	"../Node/ProceduralNode.h"

#include	"../Node/UVNode.h"

#include	"../Node/MathAdvancedNode.h"
#include	"../Node/MathBasicNode.h"
#include	"../Node/MathInterpolation.h"
#include	"../Node/MathRangeNode.h"
#include	"../Node/MathRoundNode.h"
#include	"../Node/MathWaveNode.h"

#include	"../Node/InputBasicNode.h"

#include	"../Node/TextureNode.h"

#define STR(var) #var
/*
	Nodeˆê——
	ŽÀ‘•‚µ‚½‚©‚ÌŠm”F
	Artistic
	--Adjustment
		ReplaceColor
	Channel
		CombineNode

	Input

	--Basic
		FloatNode
		Vector2Node
		Vector3Node
		Vector4Node
		ColorNode
		TimeNode

	Math
	--Advanced
		AbsoluteNode
		LengthNode
		ModuloNode
		NegateNode
		NormalizeNode
		PosterizeNode
		ReciprocalSquareRootNode

	--Basic
		AddNode
		SubtractNode
		MultiplyNode
		DivideNode
		PowerNode
		SquareRootNode

	Noise

	Procedural

	raymarching

	UV
*/

namespace
{
}
namespace	epion::GUI
{
	ImVec2	ContextManager::m_offset;
	ImVec2	ContextManager::m_menu_pos;

	bool	ContextManager::m_is_open;

	bool	ContextManager::m_is_open_node_menus[ArraySize];
	std::string	ContextManager::m_str_menus[ArraySize];

	bool	ContextManager::m_is_open_node_create_menu;
	bool	ContextManager::m_is_open_node_menu;
	bool	ContextManager::m_is_open_artistic_adjustment_menu;
	bool	ContextManager::m_is_open_input_basic_menu;
	bool	ContextManager::m_is_open_input_texture_menu;
	bool	ContextManager::m_is_open_math_advanced_menu;
	bool	ContextManager::m_is_open_math_basic_menu;
	bool	ContextManager::m_is_open_math_range_menu;
	bool	ContextManager::m_is_open_math_round_menu;
	bool	ContextManager::m_is_open_math_wave_menu;

	bool	ContextManager::m_is_open_node_delete_menu;
	bool	ContextManager::m_is_open_line_delete_menu;

	int	ContextManager::m_create_count;

	void	ContextManager::Init()
	{
		m_offset = ImVec2(0, 0);
		m_menu_pos = ImVec2(0, 0);
		for (int i = 0; i < ArraySize; i++)
		{
			m_is_open_node_menus[i] = false;
		}
		m_str_menus[Artistic] = STR(Artistic);
		m_str_menus[Channel] = STR(Channel);
		m_str_menus[Input] = STR(Input);
		m_str_menus[Master] = STR(Master);
		m_str_menus[Math] = STR(Math);
		m_str_menus[Procedural] = STR(Procedural);
		m_str_menus[Utility] = STR(Utility);
		m_str_menus[UV] = STR(UV);
		m_str_menus[Noise] = STR(Noise);

		m_is_open_artistic_adjustment_menu = false;

		m_is_open_input_basic_menu = false;
		m_is_open_math_advanced_menu = false;
		m_is_open_math_basic_menu = false;
		m_is_open_math_range_menu = false;
		m_is_open_math_round_menu = false;
		m_is_open_math_wave_menu = false;

		m_is_open = false;

		m_is_open_line_delete_menu = false;
		m_is_open_node_create_menu = false;
		m_is_open_node_delete_menu =false;

		m_create_count = 0;
	}

	void ContextManager::Update(ImVec2& offset, std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open)
		{
			NodeMenu();
			ArtisticContext(nodes);
			ChannelContext(nodes);
			InputContext(nodes);
			MasterContext(nodes);
			MathContext(nodes);
			ProceduralContext(nodes);
			UtilityContext(nodes);
			UVContext(nodes);
			NoiseContext(nodes);
			if (ImGui::IsMouseClicked(1))
			{
				m_offset = m_menu_pos - offset;
			}
		}
	}
	void	ContextManager::DragAndDropEvent()
	{

	}



#pragma region Node Event
	void	ContextManager::OpenNodeCreateContext(ImVec2& pos)
	{
		m_is_open = true;
		m_is_open_node_create_menu = true;
		m_menu_pos = pos;
	}
	void	ContextManager::OpenNodeDeleteContext(ImVec2& pos)
	{
		m_is_open = true;
		m_is_open_node_delete_menu = true;
		m_menu_pos = pos;
	}

	void	ContextManager::CreateNodeMenu(ImVec2& pos)
	{
		if (m_is_open_node_create_menu)
		{
			ImGui::OpenPopup("create_menu");

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, ImColors::U32::GRAY);
			if (ImGui::BeginPopup("create_menu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Menu");
				ImGui::Separator();
				CloseContext(m_is_open_node_create_menu);
				if (ImGui::MenuItem("Create Node", nullptr, &m_is_open_node_menu))
				{
					m_offset = m_menu_pos - pos;
					m_is_open_node_create_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar();
		}
	}
	void	ContextManager::DeleteNodeMenu(std::vector<std::unique_ptr<Node::NodeBase>>& nodes,int& hit_index)
	{
		if (m_is_open_node_delete_menu)
		{
			ImGui::OpenPopup("delete_node_menu");

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, ImColors::U32::GRAY);
			if (ImGui::BeginPopup("delete_node_menu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Menu");
				ImGui::Separator();
				CloseContext(m_is_open_node_delete_menu);
				if (ImGui::MenuItem("Delete", nullptr))
				{
					nodes.erase(nodes.begin() + hit_index);
					hit_index = Node::INIT_NUM;
					m_is_open_node_delete_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar();
		}
	}

	void	ContextManager::NodeMenu()
	{
		if (m_is_open_node_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("nodemenu");
			if (ImGui::BeginPopup("nodemenu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Create Node");
				ImGui::Separator();
				for (int i = 0; i < NodeType::ArraySize; i++)
				{
					if (ImGui::MenuItem(m_str_menus[i].c_str(), nullptr, &m_is_open_node_menus[i]))
					{
						m_is_open_node_menu = false;
					}
				}
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::ArtisticContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Artistic])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("ArtisticMenu");
			if (ImGui::BeginPopup("ArtisticMenu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Artistic");
				ImGui::Separator();

				BackContext(m_is_open_node_menu, m_is_open_node_menus[Artistic]);
				m_is_open_artistic_adjustment_menu = true;
				m_is_open_node_menus[Artistic] = false;
			}
			PopupEndSettings();
		}
		if (m_is_open_artistic_adjustment_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("ArtisticAdjustmentMenu");
			if (ImGui::BeginPopup("ArtisticAdjustmentMenu"))
			{
				BaseMenuContext("Adjustment", m_is_open_node_menus[Artistic], m_is_open_artistic_adjustment_menu);
				MenuCreateNode<Node::ReplaceColorNode>(nodes, "RePlaceColor", m_offset, m_create_count, m_is_open_artistic_adjustment_menu);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::ChannelContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Channel])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("ChannelMenu");
			if (ImGui::BeginPopup("ChannelMenu"))
			{
				BaseMenuContext("Channel", m_is_open_node_menu, m_is_open_node_menus[Channel]);
				MenuCreateNode<Node::CombineNode>(nodes, "Combine", m_offset, m_create_count, m_is_open_node_menus[Channel]);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::InputContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Input])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("InputMenu");
			if (ImGui::BeginPopup("InputMenu"))
			{
				BaseMenuContext("Input", m_is_open_node_menu, m_is_open_node_menus[Input]);
				MenuItem("Basic", NodeType::Input, m_is_open_input_basic_menu);
				MenuItem("Texture", NodeType::Input, m_is_open_input_texture_menu);
			}
			PopupEndSettings();
		}
		if (m_is_open_input_basic_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("InputBasicMenu");
			if (ImGui::BeginPopup("InputBasicMenu"))
			{
				std::vector<int> a;
				BaseMenuContext("Basic", m_is_open_node_menus[Input], m_is_open_input_basic_menu);

				MenuCreateNode<Node::FloatNode>(nodes, "Float", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Node::Vector2Node>(nodes, "Vector2", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Node::Vector3Node>(nodes, "Vector3", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Node::Vector4Node>(nodes, "Vector4", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Node::ColorNode>(nodes, "Color", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Node::TimeNode>(nodes, "Time", m_offset, m_create_count, m_is_open_input_basic_menu);
			}
			PopupEndSettings();
		}
		if (m_is_open_input_texture_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("InputTextureMenu");
			if (ImGui::BeginPopup("InputTextureMenu"))
			{
				BaseMenuContext("Texture", m_is_open_node_menus[Input], m_is_open_input_texture_menu);
				MenuCreateNode<Node::SamplerStateNode>(nodes, "SamplerState", m_offset, m_create_count, m_is_open_input_texture_menu);
				MenuCreateNode<Node::SamplerTexture2DNode>(nodes, "Sampler Texture2D", m_offset, m_create_count, m_is_open_input_texture_menu);
				MenuCreateNode<Node::Texture2DNode>(nodes, "Texture2D", m_offset, m_create_count, m_is_open_input_texture_menu);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::MasterContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Master])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MasterMenu");
			if (ImGui::BeginPopup("MasterMenu"))
			{
				BaseMenuContext("Master", m_is_open_node_menu, m_is_open_node_menus[Master]);
				MenuCreateNode<Node::UnlitMasterNode>(nodes, "Unlit", m_offset, m_create_count, m_is_open_node_menus[Master]);
				//MenuCreateNode<PBRMasterNode>("PBR", m_offset, m_create_count, m_is_open_menu[Master]);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::MathContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Math])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MathMenu");
			if (ImGui::BeginPopup("MathMenu"))
			{
				BaseMenuContext("Math", m_is_open_node_menu, m_is_open_node_menus[Math]);
				MenuItem("Advanced", NodeType::Math, m_is_open_math_advanced_menu);
				MenuItem("Basic", NodeType::Math, m_is_open_math_basic_menu);
				MenuItem("Range", NodeType::Math, m_is_open_math_range_menu);
				MenuItem("Round", NodeType::Math, m_is_open_math_round_menu);
				MenuItem("Wave", NodeType::Math, m_is_open_math_wave_menu);

				MenuCreateNode<Node::LerpNode>(nodes, "Lerp", m_offset, m_create_count, m_is_open_node_menus[Math]);
			}
			PopupEndSettings();
		}
		if (m_is_open_math_advanced_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MathAdvancedMenu");
			if (ImGui::BeginPopup("MathAdvancedMenu"))
			{
				BaseMenuContext("Advanced", m_is_open_node_menus[Math], m_is_open_math_advanced_menu);
				MenuCreateNode<Node::AbsoluteNode>(nodes, "Absolute", m_offset, m_create_count, m_is_open_math_advanced_menu);
				MenuCreateNode<Node::LengthNode>(nodes, "Length", m_offset, m_create_count, m_is_open_math_advanced_menu);
				MenuCreateNode<Node::ModuloNode>(nodes, "Modulo", m_offset, m_create_count, m_is_open_math_advanced_menu);
			}
			PopupEndSettings();
		}
		if (m_is_open_math_basic_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MathBasicMenu");
			if (ImGui::BeginPopup("MathBasicMenu"))
			{
				BaseMenuContext("Basic", m_is_open_node_menus[Math], m_is_open_math_basic_menu);
				MenuCreateNode<Node::AddNode>(nodes, "Add", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<Node::DivideNode>(nodes, "Divide", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<Node::MultiplyNode>(nodes, "Multiply", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<Node::PowerNode>(nodes, "Power", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<Node::SquareRootNode>(nodes, "SquareRoot", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<Node::SubtractNode>(nodes, "Subtract", m_offset, m_create_count, m_is_open_math_basic_menu);
			}
			PopupEndSettings();
		}
		if (m_is_open_math_range_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MathRangeMenu");
			if (ImGui::BeginPopup("MathRangeMenu"))
			{
				BaseMenuContext("Range", m_is_open_node_menus[Math], m_is_open_math_range_menu);
				MenuCreateNode<Node::ClampNode>(nodes, "Clamp", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<Node::FractionNode>(nodes, "Fraction", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<Node::MaximumNode>(nodes, "Maximum", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<Node::MinimumNode>(nodes, "Minimum", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<Node::OneMinusNode>(nodes, "OneMinus", m_offset, m_create_count, m_is_open_math_range_menu);
			}
			PopupEndSettings();
		}
		if (m_is_open_math_round_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MathRoundMenu");
			if (ImGui::BeginPopup("MathRoundMenu"))
			{
				BaseMenuContext("Round", m_is_open_node_menus[Math], m_is_open_math_round_menu);
				MenuCreateNode<Node::CeilingNode>(nodes, "Ceiling", m_offset, m_create_count, m_is_open_math_round_menu);
				MenuCreateNode<Node::StepNode>(nodes, "Step", m_offset, m_create_count, m_is_open_math_round_menu);
			}
			PopupEndSettings();
		}
		if (m_is_open_math_wave_menu)
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MathWaveMenu");
			if (ImGui::BeginPopup("MathWaveMenu"))
			{
				BaseMenuContext("Wave", m_is_open_node_menus[Math], m_is_open_math_wave_menu);
				MenuCreateNode<Node::NoiseSineWaveNode>(nodes, "NoiseSineWave", m_offset, m_create_count, m_is_open_math_wave_menu);
				MenuCreateNode<Node::SawtoothWaveNode>(nodes, "SawtoothWave", m_offset, m_create_count, m_is_open_math_wave_menu);
			}
			PopupEndSettings();
		}

	}
	void	ContextManager::ProceduralContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Procedural])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("ProceduralMenu");
			if (ImGui::BeginPopup("ProceduralMenu"))
			{
				BaseMenuContext("Procedural", m_is_open_node_menu, m_is_open_node_menus[Procedural]);
				MenuCreateNode<Node::CheckerboardNode>(nodes, "Checkerboard", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<Node::EllipseNode>(nodes, "Ellipse", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<Node::HexagonNode>(nodes, "Hexagon", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<Node::PolygonNode>(nodes, "Polygon", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<Node::RippleNode>(nodes, "Ripple", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<Node::RoundedRectangleNode>(nodes, "RoundedRectangle", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
			}
			PopupEndSettings();
		}

	}
	void	ContextManager::UtilityContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{

	}
	void	ContextManager::UVContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[UV])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("UVMenu");
			if (ImGui::BeginPopup("UVMenu"))
			{
				BaseMenuContext("UV", m_is_open_node_menu, m_is_open_node_menus[UV]);
				MenuCreateNode<Node::PolarCoordinatesNode>(nodes, "PolarCoordinates", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<Node::RadialShearNode>(nodes, "RadialShear", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<Node::SpherizeNode>(nodes, "Spherize", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<Node::TilingAndOffsetNode>(nodes, "TilingAndOffset", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<Node::TwirlNode>(nodes, "Twirl", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<Node::UVNode>(nodes, "UV", m_offset, m_create_count, m_is_open_node_menus[UV]);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::NoiseContext(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		if (m_is_open_node_menus[Noise])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("NoiseMenu");
			if (ImGui::BeginPopup("NoiseMenu"))
			{
				BaseMenuContext("Noise", m_is_open_node_menu, m_is_open_node_menus[Noise]);
				MenuCreateNode<Node::FBMNode>(nodes, "FBM", m_offset, m_create_count, m_is_open_node_menus[Noise]);
				MenuCreateNode<Node::GradientNoiseNode>(nodes, "GradientNoise", m_offset, m_create_count, m_is_open_node_menus[Noise]);
				MenuCreateNode<Node::SimpleNoiseNode>(nodes, "SimpleNoise", m_offset, m_create_count, m_is_open_node_menus[Noise]);
				MenuCreateNode<Node::VoronoiNode>(nodes, "Voronoi", m_offset, m_create_count, m_is_open_node_menus[Noise]);
			}
			PopupEndSettings();
		}
	}
#pragma endregion

#pragma region Line Event
	void	ContextManager::OpenLineDeleteContext(ImVec2& pos)
	{
		m_is_open_line_delete_menu = true;
		m_menu_pos = pos;
	}
	void	ContextManager::DeleteLineMenu(std::vector<Node::NodeLink>&	lines,int& hit_index)
	{
		if (m_is_open_line_delete_menu)
		{
			ImGui::OpenPopup("delete_line_menu");

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, ImColors::U32::GRAY);
			if (ImGui::BeginPopup("delete_line_menu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Menu");
				ImGui::Separator();
				CloseContext(m_is_open_line_delete_menu);
				if (ImGui::MenuItem("Delete", nullptr))
				{
					lines.erase(lines.begin() + hit_index);
					hit_index = Node::INIT_NUM;
					m_is_open_line_delete_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar();
		}
	}
#pragma endregion

	void	ContextManager::BaseMenuContext(const std::string& menu_name, bool& is_back, bool& is_current)
	{
		ImGui::TextColored(ImColors::Vec4::BLACK, menu_name.c_str());
		ImGui::Separator();
		BackContext(is_back, is_current);
		CloseContext(is_current);
		ImGui::Separator();
	}

	void	ContextManager::CloseContext(bool& is_current)
	{
		if (ImGui::MenuItem("Close"))
		{
			is_current = false;
		}
	}

	void	ContextManager::BackContext(bool& is_back, bool& is_current)
	{
		if (ImGui::MenuItem("<-"))
		{
			is_back = true;
			is_current = false;
		}
	}

	void ContextManager::PopupBeginSettings()
	{
		ImGui::SetNextWindowPos(m_menu_pos);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, ImColors::U32::GRAY);
	}
	void ContextManager::PopupEndSettings()
	{
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
		ImGui::EndPopup();
	}

	void	ContextManager::MenuItem(const std::string& str, NodeType type, bool& is_menu)
	{
		if (ImGui::MenuItem(str.c_str()))
		{
			is_menu = true;
			m_is_open_node_menus[type] = false;
		}
	}

	void	ContextManager::SetContext(bool is_set)
	{
		m_is_open_node_create_menu = is_set;
	}

	bool	ContextManager::GetContext()
	{
		return	m_is_open_node_create_menu;
	}

	void ContextManager::SetCreateCount(int size)
	{
		m_create_count = size;
	}

	void	ContextManager::SetLineMenu(bool is_set)
	{
		m_is_open_line_delete_menu = is_set;
	}

	bool	ContextManager::GetLineMenu()
	{
		return	m_is_open_line_delete_menu;
	}

}