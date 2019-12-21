#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"EpionNodeEditor.h"

#include	"ImguiNodeContext.h"

#include	"../../Node/NodeData.h"
#include	"../../Node/ArtisticAdjustment.h"

#include	"../../Node/ChannelNode.h"

#include	"../../Node/NoiseNode.h"
#include	"../../Node/MasterNode.h"
#include	"../../Node/PBRNode.h"


#include	"../../Node/ProceduralNode.h"

#include	"../../Node/UVNode.h"

#include	"../../Node/MathAdvancedNode.h"
#include	"../../Node/MathBasicNode.h"
#include	"../../Node/MathInterpolation.h"
#include	"../../Node/MathRangeNode.h"
#include	"../../Node/MathRoundNode.h"
#include	"../../Node/MathWaveNode.h"

#include	"../../Node/InputBasicNode.h"

#include	"../../Node/TextureNode.h"

#define STR(var) #var
/*
	Node一覧
	実装したかの確認
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
	using namespace epion;
	using namespace epion::Node;
	template<class First>
	void SetFalse(First& first)
	{
		first = false;
	}

	template<class First, class...  Args>
	void SetFalse(First& first, Args&... args)
	{
		first = false;
		SetFalse(args...);
	}

	template <class T = epion::Node::NodeBase, class First, class... Args>
	void MenuCreateNode(const std::string& name, ImVec2& pos, int& count, First&first, Args&... args)
	{
		static_assert(std::is_base_of<epion::Node::NodeBase, T>::value == true, "BaseClass not NodeBase");
		if (ImGui::MenuItem(name.c_str()))
		{
			NodeEditor::nodes.push_back(std::make_unique<T>(count, math::FVector2(pos.x, pos.y)));
			count++;
			SetFalse(first, args...);
		}
	};
}
namespace	epion::Node
{
	ImVec2	ContextManager::m_pos;
	ImVec2	ContextManager::m_offset;
	ImVec2	ContextManager::m_menu_pos;

	bool	ContextManager::m_is_open_artistic_adjustment_menu;

	bool	ContextManager::m_is_open_input_basic_menu;
	bool	ContextManager::m_is_open_input_texture_menu;


	bool	ContextManager::m_is_open_math_advanced_menu;
	bool	ContextManager::m_is_open_math_basic_menu;
	bool	ContextManager::m_is_open_math_range_menu;
	bool	ContextManager::m_is_open_math_round_menu;
	bool	ContextManager::m_is_open_math_wave_menu;

	bool	ContextManager::m_is_open_node_create_menu;
	bool	ContextManager::m_is_open_line_delete_menu;
	bool	ContextManager::m_is_open_node_menu;

	bool	ContextManager::m_is_open_node_menus[ArraySize];
	std::string	ContextManager::m_str_menus[ArraySize];

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

		m_is_open_line_delete_menu = false;
		m_is_open_node_create_menu = false;

		m_create_count = 0;
	}

	void	ContextManager::Update(ImVec2& offset)
	{
		NodeMenu();
		ArtisticContext();
		ChannelContext();
		InputContext();
		MasterContext();
		MathContext();
		ProceduralContext();
		UtilityContext();
		UVContext();
		NoiseContext();
	}
	void	ContextManager::DragAndDropEvent()
	{
	}


	void	ContextManager::CreateNodeMenu(ImVec2& offset)
	{
		if (m_is_open_node_create_menu)
		{
			//ノードの追加
			ImGui::OpenPopup("create_menu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, ImColors::U32::GRAY);
			if (ImGui::BeginPopup("create_menu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Menu");
				ImGui::Separator();
				if (ImGui::MenuItem("Create Node", nullptr, &m_is_open_node_menu))
				{
					m_offset = m_pos -offset;
					m_is_open_node_create_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar();
		}
	}

	void	ContextManager::LineEvent()
	{
		if (m_is_open_line_delete_menu)
		{
			//ノードの追加
			ImGui::OpenPopup("line_menu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
			if (ImGui::BeginPopup("line_menu"))
			{
				if (ImGui::MenuItem("Delete", nullptr, &m_is_open_line_delete_menu))
				{
					m_is_open_line_delete_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}
	}

	//Create Nodeをクリックした後のイベント
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

	void	ContextManager::ArtisticContext()
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
				MenuCreateNode<ReplaceColorNode>("RePlaceColor", m_offset, m_create_count, m_is_open_artistic_adjustment_menu);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::ChannelContext()
	{
		if (m_is_open_node_menus[Channel])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("ChannelMenu");
			if (ImGui::BeginPopup("ChannelMenu"))
			{
				BaseMenuContext("Channel", m_is_open_node_menu, m_is_open_node_menus[Channel]);
				MenuCreateNode<CombineNode>("Combine", m_offset, m_create_count, m_is_open_node_menus[Channel]);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::InputContext()
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
				BaseMenuContext("Basic", m_is_open_node_menus[Input], m_is_open_input_basic_menu);
				MenuCreateNode<FloatNode>("Float", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Vector2Node>("Vector2", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Vector3Node>("Vector3", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Vector4Node>("Vector4", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<ColorNode>("Color", m_offset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<TimeNode>("Time", m_offset, m_create_count, m_is_open_input_basic_menu);
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
				MenuCreateNode<SamplerStateNode>("SamplerState", m_offset, m_create_count, m_is_open_input_texture_menu);
				MenuCreateNode<SamplerTexture2DNode>("Sampler Texture2D", m_offset, m_create_count, m_is_open_input_texture_menu);
				MenuCreateNode<Texture2DNode>("Texture2D", m_offset, m_create_count, m_is_open_input_texture_menu);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::MasterContext()
	{
		if (m_is_open_node_menus[Master])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("MasterMenu");
			if (ImGui::BeginPopup("MasterMenu"))
			{
				BaseMenuContext("Master", m_is_open_node_menu, m_is_open_node_menus[Master]);
				MenuCreateNode<UnlitMasterNode>("Unlit", m_offset, m_create_count, m_is_open_node_menus[Master]);
				//MenuCreateNode<PBRMasterNode>("PBR", m_offset, m_create_count, m_is_open_menu[Master]);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::MathContext()
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

				MenuCreateNode<LerpNode>("Lerp", m_offset, m_create_count, m_is_open_node_menus[Math]);
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
				MenuCreateNode<AbsoluteNode>("Absolute", m_offset, m_create_count, m_is_open_math_advanced_menu);
				MenuCreateNode<LengthNode>("Length", m_offset, m_create_count, m_is_open_math_advanced_menu);
				MenuCreateNode<ModuloNode>("Modulo", m_offset, m_create_count, m_is_open_math_advanced_menu);
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
				MenuCreateNode<AddNode>("Add", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<DivideNode>("Divide", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<MultiplyNode>("Multiply", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<PowerNode>("Power", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<SquareRootNode>("SquareRoot", m_offset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<SubtractNode>("Subtract", m_offset, m_create_count, m_is_open_math_basic_menu);
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
				MenuCreateNode<ClampNode>("Clamp", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<FractionNode>("Fraction", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<MaximumNode>("Maximum", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<MinimumNode>("Minimum", m_offset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<OneMinusNode>("OneMinus", m_offset, m_create_count, m_is_open_math_range_menu);
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
				MenuCreateNode<CeilingNode>("Ceiling", m_offset, m_create_count, m_is_open_math_round_menu);
				MenuCreateNode<StepNode>("Step", m_offset, m_create_count, m_is_open_math_round_menu);
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
				MenuCreateNode<NoiseSineWaveNode>("NoiseSineWave", m_offset, m_create_count, m_is_open_math_wave_menu);
				MenuCreateNode<SawtoothWaveNode>("SawtoothWave", m_offset, m_create_count, m_is_open_math_wave_menu);
			}
			PopupEndSettings();
		}

	}
	void	ContextManager::ProceduralContext()
	{
		if (m_is_open_node_menus[Procedural])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("ProceduralMenu");
			if (ImGui::BeginPopup("ProceduralMenu"))
			{
				BaseMenuContext("Procedural", m_is_open_node_menu, m_is_open_node_menus[Procedural]);
				MenuCreateNode<CheckerboardNode>("Checkerboard", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<EllipseNode>("Ellipse", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<HexagonNode>("Hexagon", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<PolygonNode>("Polygon", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<RippleNode>("Ripple", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
				MenuCreateNode<RoundedRectangleNode>("RoundedRectangle", m_offset, m_create_count, m_is_open_node_menus[Procedural]);
			}
			PopupEndSettings();
		}

	}
	void	ContextManager::UtilityContext()
	{

	}
	void	ContextManager::UVContext()
	{
		if (m_is_open_node_menus[UV])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("UVMenu");
			if (ImGui::BeginPopup("UVMenu"))
			{
				BaseMenuContext("UV", m_is_open_node_menu, m_is_open_node_menus[UV]);
				MenuCreateNode<PolarCoordinatesNode>("PolarCoordinates", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<RadialShearNode>("RadialShear", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<SpherizeNode>("Spherize", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<TilingAndOffsetNode>("TilingAndOffset", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<TwirlNode>("Twirl", m_offset, m_create_count, m_is_open_node_menus[UV]);
				MenuCreateNode<UVNode>("UV", m_offset, m_create_count, m_is_open_node_menus[UV]);
			}
			PopupEndSettings();
		}
	}
	void	ContextManager::NoiseContext()
	{
		if (m_is_open_node_menus[Noise])
		{
			PopupBeginSettings();
			ImGui::OpenPopup("NoiseMenu");
			if (ImGui::BeginPopup("NoiseMenu"))
			{
				BaseMenuContext("Noise", m_is_open_node_menu, m_is_open_node_menus[Noise]);
				MenuCreateNode<FBMNode>("FBM", m_offset, m_create_count, m_is_open_node_menus[Noise]);
				MenuCreateNode<GradientNoiseNode>("GradientNoise", m_offset, m_create_count, m_is_open_node_menus[Noise]);
				MenuCreateNode<SimpleNoiseNode>("SimpleNoise", m_offset, m_create_count, m_is_open_node_menus[Noise]);
				MenuCreateNode<VoronoiNode>("Voronoi", m_offset, m_create_count, m_is_open_node_menus[Noise]);
			}
			PopupEndSettings();
		}
	}

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
		ImGui::SetNextWindowPos(m_pos);
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


	void	ContextManager::OpenNodeCreateContext(bool is_set, ImVec2& pos)
	{
		m_is_open_node_create_menu = is_set;
		m_pos = pos;
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