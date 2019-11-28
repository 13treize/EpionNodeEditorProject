#include	"../../All.h"
#include	"../../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"EpionNodeEditor.h"

#include	"epion_imgui_node_context.h"

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
	using namespace epion::NodeCustom;
	template<class First>
	void set_false(First& first)
	{
		first = false;
	}

	template<class First, class...  Args>
	void set_false(First& first, Args&... args)
	{
		first = false;
		set_false(args...);
	}

	template <class T =epion::NodeCustom::NodeBase, class First, class... Args>
	void MenuCreateNode(const std::string& name,ImVec2& pos,int& count, First&first, Args&... args)
	{
		static_assert(std::is_base_of<epion::NodeCustom::NodeBase, T>::value == true, "BaseClass not NodeBase");
		if (ImGui::MenuItem(name.c_str()))
		{
			NodeEditor::nodes.push_back(std::make_unique<T>(count, math::FVector2(pos.x, pos.y)));
			count++;
			set_false(first, args...);
		}
	};
}
namespace	epion::NodeCustom
{
	ImVec2	ContextManager::m_offfset;

	bool	ContextManager::m_is_open_artistic_adjustment_menu;

	bool	ContextManager::m_is_open_input_basic_menu;
	bool	ContextManager::m_is_open_input_texture_menu;


	bool	ContextManager::m_is_open_math_advanced_menu;
	bool	ContextManager::m_is_open_math_basic_menu;
	bool	ContextManager::m_is_open_math_range_menu;
	bool	ContextManager::m_is_open_math_round_menu;
	bool	ContextManager::m_is_open_math_wave_menu;

	bool	ContextManager::m_is_open_context_menu;
	bool	ContextManager::m_is_open_line_menu;
	bool	ContextManager::m_is_open_node_menu;

	bool	ContextManager::m_is_open_menu[ArraySize];
	std::string	ContextManager::m_str_menu[ArraySize];

	int	ContextManager::m_create_count;

	void	ContextManager::Init()
	{
		for (int i = 0; i < ArraySize; i++)
		{
			m_is_open_menu[i] = false;
		}
		m_str_menu[Artistic] = STR(Artistic);
		m_str_menu[Channel] = STR(Channel);
		m_str_menu[Input] = STR(Input);
		m_str_menu[Master] = STR(Master);
		m_str_menu[Math] = STR(Math);
		m_str_menu[Procedural] = STR(Procedural);
		m_str_menu[Utility] = STR(Utility);
		m_str_menu[UV] = STR(UV);
		m_str_menu[Noise] = STR(Noise);

		m_is_open_artistic_adjustment_menu = false;

		m_is_open_input_basic_menu = false;
		m_is_open_math_advanced_menu = false;
		m_is_open_math_basic_menu = false;
		m_is_open_math_range_menu = false;
		m_is_open_math_round_menu = false;
		m_is_open_math_wave_menu = false;

		m_is_open_line_menu = false;
		m_is_open_context_menu = false;

		m_create_count = 0;
	}

	void	ContextManager::Update(ImVec2& offset)
	{
		m_offfset=/*offset+*/ ImGui::GetIO().MousePos;

		ClickAdd();
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


	void	ContextManager::ClickEvent()
	{
		if (m_is_open_context_menu)
		{
			//ノードの追加
			ImGui::OpenPopup("context_menu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
			if (ImGui::BeginPopup("context_menu"))
			{
				if (ImGui::MenuItem("Create Node", nullptr, &m_is_open_node_menu))
				{
					m_is_open_context_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}
	}

	void	ContextManager::LineEvent()
	{
		if (m_is_open_line_menu)
		{
			//ノードの追加
			ImGui::OpenPopup("line_menu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 12));
			if (ImGui::BeginPopup("line_menu"))
			{
				if (ImGui::MenuItem("Delete", nullptr, &m_is_open_line_menu))
				{
					m_is_open_line_menu = false;
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}
	}

	//Create Nodeをクリックした後のイベント
	void	ContextManager::ClickAdd()
	{
		if (m_is_open_node_menu)
		{
			ImGui::OpenPopup("nodemenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("nodemenu"))
			{
				for (int i = 0; i < NodeType::ArraySize; i++)
				{
					if (ImGui::MenuItem(m_str_menu[i].c_str(), nullptr, &m_is_open_menu[i]))
					{
						m_is_open_node_menu = false;
					}
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}

	}

	void	ContextManager::ArtisticContext()
	{
		if (m_is_open_menu[Artistic])
		{
			ImGui::OpenPopup("ArtisticMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("ArtisticMenu"))
			{
				m_is_open_artistic_adjustment_menu = true;
				m_is_open_menu[Artistic] = false;
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
		if (m_is_open_artistic_adjustment_menu)
		{
			ImGui::OpenPopup("ArtisticAdjustmentMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("ArtisticAdjustmentMenu"))
			{
				MenuCreateNode<ReplaceColorNode>("RePlaceColor", m_offfset, m_create_count, m_is_open_artistic_adjustment_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
	}
	void	ContextManager::ChannelContext()
	{
		if (m_is_open_menu[Channel])
		{
			ImGui::OpenPopup("ChannelMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("ChannelMenu"))
			{
				MenuCreateNode<CombineNode>("Combine", m_offfset, m_create_count, m_is_open_menu[Channel]);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
	}

	void	ContextManager::InputContext()
	{
		if (m_is_open_menu[Input])
		{
			ImGui::OpenPopup("InputMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("InputMenu"))
			{
				MenuItem("Basic", NodeType::Input, m_is_open_input_basic_menu);
				MenuItem("Texture", NodeType::Input, m_is_open_input_texture_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
		if (m_is_open_input_basic_menu)
		{
			ImGui::OpenPopup("InputBasicMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("InputBasicMenu"))
			{
				MenuCreateNode<FloatNode>("Float", m_offfset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Vector2Node>("Vector2", m_offfset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Vector3Node>("Vector3", m_offfset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<Vector4Node>("Vector4", m_offfset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<ColorNode>("Color", m_offfset, m_create_count, m_is_open_input_basic_menu);
				MenuCreateNode<TimeNode>("Time", m_offfset, m_create_count, m_is_open_input_basic_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
		if (m_is_open_input_texture_menu)
		{
			ImGui::OpenPopup("InputTextureMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("InputTextureMenu"))
			{
				MenuCreateNode<SamplerStateNode>("SamplerState", m_offfset, m_create_count, m_is_open_input_texture_menu);
				MenuCreateNode<SamplerTexture2DNode>("Sampler Texture2D", m_offfset, m_create_count, m_is_open_input_texture_menu);
				MenuCreateNode<Texture2DNode>("Texture2D", m_offfset, m_create_count, m_is_open_input_texture_menu);

			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}


	}

	void	ContextManager::MasterContext()
	{
		if (m_is_open_menu[Master])
		{
			ImGui::OpenPopup("MasterMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MasterMenu"))
			{
				MenuCreateNode<UnlitMasterNode>("Unlit", m_offfset, m_create_count,m_is_open_menu[Master]);
				MenuCreateNode<PBRMasterNode>("PBR", m_offfset, m_create_count, m_is_open_menu[Master]);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
	}

	void	ContextManager::MathContext()
	{
		if (m_is_open_menu[Math])
		{
			ImGui::OpenPopup("MathMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MathMenu"))
			{
				MenuItem("Advanced", NodeType::Math, m_is_open_math_advanced_menu);
				MenuItem("Basic", NodeType::Math, m_is_open_math_basic_menu);
				MenuItem("Range", NodeType::Math, m_is_open_math_range_menu);
				MenuItem("Round", NodeType::Math, m_is_open_math_round_menu);
				MenuItem("Wave", NodeType::Math, m_is_open_math_wave_menu);

				MenuCreateNode<LerpNode>("Lerp", m_offfset, m_create_count, m_is_open_menu[Math]);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
		if (m_is_open_math_advanced_menu)
		{
			ImGui::OpenPopup("MathAdvancedMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MathAdvancedMenu"))
			{
				MenuCreateNode<AbsoluteNode>("Absolute", m_offfset, m_create_count, m_is_open_math_advanced_menu);
				MenuCreateNode<LengthNode>("Length",m_offfset, m_create_count, m_is_open_math_advanced_menu);
				MenuCreateNode<ModuloNode>("Modulo",m_offfset, m_create_count, m_is_open_math_advanced_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}

		if (m_is_open_math_basic_menu)
		{
			ImGui::OpenPopup("MathBasicMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MathBasicMenu"))
			{
				MenuCreateNode<AddNode>("Add", m_offfset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<DivideNode>("Divide", m_offfset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<MultiplyNode>("Multiply", m_offfset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<PowerNode>("Power", m_offfset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<SquareRootNode>("SquareRoot", m_offfset, m_create_count, m_is_open_math_basic_menu);
				MenuCreateNode<SubtractNode>("Subtract", m_offfset, m_create_count, m_is_open_math_basic_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
		if (m_is_open_math_range_menu)
		{
			ImGui::OpenPopup("MathRangeMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MathRangeMenu"))
			{
				MenuCreateNode<ClampNode>("Clamp", m_offfset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<FractionNode>("Fraction", m_offfset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<MaximumNode>("Maximum", m_offfset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<MinimumNode>("Minimum", m_offfset, m_create_count, m_is_open_math_range_menu);
				MenuCreateNode<OneMinusNode>("OneMinus", m_offfset, m_create_count, m_is_open_math_range_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
		if (m_is_open_math_round_menu)
		{
			ImGui::OpenPopup("MathRoundMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MathRoundMenu"))
			{
				MenuCreateNode<CeilingNode>("Ceiling", m_offfset, m_create_count, m_is_open_math_round_menu);
				MenuCreateNode<StepNode>("Step", m_offfset, m_create_count, m_is_open_math_round_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}

		if (m_is_open_math_wave_menu)
		{
			ImGui::OpenPopup("MathWaveMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("MathWaveMenu"))
			{
				MenuCreateNode<NoiseSineWaveNode>("NoiseSineWave", m_offfset, m_create_count, m_is_open_math_wave_menu);
				MenuCreateNode<SawtoothWaveNode>("SawtoothWave", m_offfset, m_create_count, m_is_open_math_wave_menu);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}

	}

	void	ContextManager::ProceduralContext()
	{
		if (m_is_open_menu[Procedural])
		{
			ImGui::OpenPopup("ProceduralMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("ProceduralMenu"))
			{
				MenuCreateNode<CheckerboardNode>("Checkerboard", m_offfset, m_create_count, m_is_open_menu[Procedural]);
				MenuCreateNode<EllipseNode>("Ellipse", m_offfset, m_create_count, m_is_open_menu[Procedural]);
				MenuCreateNode<HexagonNode>("Hexagon", m_offfset, m_create_count, m_is_open_menu[Procedural]);
				MenuCreateNode<PolygonNode>("Polygon", m_offfset, m_create_count, m_is_open_menu[Procedural]);
				MenuCreateNode<RippleNode>("Ripple", m_offfset, m_create_count, m_is_open_menu[Procedural]);
				MenuCreateNode<RoundedRectangleNode>("RoundedRectangle", m_offfset, m_create_count, m_is_open_menu[Procedural]);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}

	}

	void	ContextManager::UtilityContext()
	{

	}

	void	ContextManager::UVContext()
	{
		if (m_is_open_menu[UV])
		{
			ImGui::OpenPopup("UVMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("UVMenu"))
			{
				MenuCreateNode<PolarCoordinatesNode>("PolarCoordinates", m_offfset, m_create_count, m_is_open_menu[UV]);
				MenuCreateNode<RadialShearNode>("RadialShear", m_offfset, m_create_count, m_is_open_menu[UV]);
				MenuCreateNode<SpherizeNode>("Spherize", m_offfset, m_create_count, m_is_open_menu[UV]);
				MenuCreateNode<TilingAndOffsetNode>("TilingAndOffset", m_offfset, m_create_count, m_is_open_menu[UV]);
				MenuCreateNode<TwirlNode>("Twirl", m_offfset, m_create_count, m_is_open_menu[UV]);
				MenuCreateNode<UVNode>("UV", m_offfset, m_create_count, m_is_open_menu[UV]);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
	}

	void	ContextManager::NoiseContext()
	{
		if (m_is_open_menu[Noise])
		{
			ImGui::OpenPopup("NoiseMenu");
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
			if (ImGui::BeginPopup("NoiseMenu"))
			{
				MenuCreateNode<FBMNode>("FBM", m_offfset, m_create_count, m_is_open_menu[Noise]);
				MenuCreateNode<GradientNoiseNode>("GradientNoise", m_offfset, m_create_count, m_is_open_menu[Noise]);
				MenuCreateNode<SimpleNoiseNode>("SimpleNoise", m_offfset, m_create_count, m_is_open_menu[Noise]);
				MenuCreateNode<VoronoiNode>("Voronoi", m_offfset, m_create_count, m_is_open_menu[Noise]);
			}
			ImGui::PopStyleVar();
			ImGui::EndPopup();
		}
	}

	void	ContextManager::MenuItem(const std::string& str, NodeType type, bool& is_menu)
	{
		if (ImGui::MenuItem(str.c_str()))
		{
			is_menu = true;
			m_is_open_menu[type] = false;
		}
	}

	void	ContextManager::SetContext(bool is_set)
	{
		m_is_open_context_menu = is_set;
	}

	bool	ContextManager::GetContext()
	{
		return	m_is_open_context_menu;
	}
	void ContextManager::SetCreateCount(int size)
	{
		m_create_count = size;
	}

	void	ContextManager::SetLineMenu(bool is_set)
	{
		m_is_open_line_menu = is_set;
	}

	bool	ContextManager::GetLineMenu()
	{
		return	m_is_open_line_menu;
	}

}