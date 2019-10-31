#include	"../All.h"
#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"NodeData.h"
#include	"NoiseNode.h"
#include	"../epion_string.h"

namespace
{
	const ImVec2	size(0, 0);
}

CEREAL_REGISTER_TYPE(epion::NodeCustom::FBMNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::GradientNoiseNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::SimpleNoiseNode)
CEREAL_REGISTER_TYPE(epion::NodeCustom::VoronoiNode)

namespace	epion::NodeCustom
{
	FBMNode::FBMNode()
	{
		Init();
	}

	FBMNode::FBMNode(int id, const math::FVector2& pos)
		:NodeBase("FBM", id, pos, size, 3, 1)
	{
		Init();
	}

	FBMNode::~FBMNode()
	{
	}

	void FBMNode::Init()
	{
		UV = { 0,0 };
		Amplitude=0.5f;
		Frequency=2.0f;

		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,SLOT_TYPE::VECTOR1,
		};
		m_input_name =
		{
			"UV(2)","Amplitude(1)","Frequency(1)",
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	FBMNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}
		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1),Amplitude);
		}
		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), Frequency);
		}

	}

	void	FBMNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	FBMNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "FBM_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(Amplitude);
		m_input_str[2] = std::to_string(Frequency);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    fbm(";

		str_set(nodes_ptr, links);

	}
	std::string	FBMNode::get_function_def_str()
	{
		return
		"float fbm_rand(float2 n)\n"
		"{\n"
		"    return frac(sin(dot(n, float2(12.9898, 4.1414))) * 43758.5453);\n"
		"}\n"
		"float fbm_noise(float2 p)\n"
		"{\n"
		"    float2 ip = floor(p);\n"
		"    float2 u = frac(p);\n"
		"    u = u * u * (3.0 - 2.0 * u);\n"
		"    float res = lerp(\n"
		"        lerp(fbm_rand(ip), fbm_rand(ip + float2(1.0, 0.0)), u.x),\n"
		"        lerp(fbm_rand(ip + float2(0.0, 1.0)), fbm_rand(ip + float2(1.0, 1.0)), u.x), u.y);\n"
		"    return res * res;\n"
		"}\n"
			"void fbm(float2 uv, float amplitude, float frequency, out float Out)\n"
			"{\n"
			"    float2 p = (uv * 2.0 - 1.0);\n"
			"    float result = 0.;\n"
			"    float amplitude2 = amplitude;\n"
			"    float frequency2 = frequency;\n"
			"    for (int i = 0; i < 8; i++)\n"
			"    {\n"
			"        result += fbm_noise(p* frequency2) * amplitude2;\n"
			"        amplitude2 *= .5;\n"
			"        frequency2 *= 2.;\n"
			"    }\n"
			"    Out = result;\n"
			"}\n";
	}

	GradientNoiseNode::GradientNoiseNode()
	{
		Init();
	}

	GradientNoiseNode::GradientNoiseNode(int id, const math::FVector2& pos)
		:NodeBase("GradientNoise", id, pos, size, 2, 1)
	{
		Init();
	}

	GradientNoiseNode::~GradientNoiseNode()
	{
	}

	void GradientNoiseNode::Init()
	{
		UV = { 0,0 };
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,
		};
		m_input_name =
		{
			"UV(2)","Scale(1)",
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	GradientNoiseNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);

		draw_list->ChannelsSetCurrent(1);
		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}
		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), Scale);
		}
	}

	void	GradientNoiseNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	GradientNoiseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Gradient_out" + std::to_string(m_ID);

		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(Scale);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    GradientNoise_float(";

		str_set(nodes_ptr, links);

	}
	std::string	GradientNoiseNode::get_function_def_str()
	{
		return
			"float2 gradientNoise_dir(float2 p)\n"
			"{\n"
			"    p = p % 289;\n"
			"    float x = (34 * p.x + 1) * p.x % 289 + p.y;\n"
			"    x = (34 * x + 1) * x % 289;\n"
			"    x = frac(x / 41) * 2 - 1;\n"
			"    return normalize(float2(x - floor(x + 0.5), abs(x) - 0.5));\n"
			"}\n"
			"float gradientNoise(float2 p)\n"
			"{\n"
			"    float2 ip = floor(p);\n"
			"    float2 fp = frac(p);\n"
			"    float d00 = dot(gradientNoise_dir(ip), fp);\n"
			"    float d01 = dot(gradientNoise_dir(ip + float2(0, 1)), fp - float2(0, 1));\n"
			"    float d10 = dot(gradientNoise_dir(ip + float2(1, 0)), fp - float2(1, 0));\n"
			"    float d11 = dot(gradientNoise_dir(ip + float2(1, 1)), fp - float2(1, 1));\n"
			"    fp = fp * fp * fp * (fp * (fp * 6 - 15) + 10);\n"
			"    return lerp(lerp(d00, d01, fp.y), lerp(d10, d11, fp.y), fp.x);\n"
			"}\n"
			"void GradientNoise_float(float2 UV, float Scale, out float Out)\n"
			"{\n"
			"    Out = gradientNoise(UV * Scale) + 0.5;\n"
			"}\n";
	}

	SimpleNoiseNode::SimpleNoiseNode()
	{
		Init();
	}

	SimpleNoiseNode::SimpleNoiseNode(int id, const math::FVector2& pos)
		:NodeBase("SimpleNoise", id, pos, size, 2, 1)
	{
		Init();

	}

	SimpleNoiseNode::~SimpleNoiseNode()
	{
	}

	void	SimpleNoiseNode::Init()
	{
		UV = { 0,0 };
		Scale = 500;
		m_input_slot_type.push_back(SLOT_TYPE::UV);
		m_input_slot_type.push_back(SLOT_TYPE::VECTOR1);

		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		//node	slot name
		m_input_name.push_back("UV(2)");
		m_input_name.push_back("Scale(1)");

		m_output_name.push_back("Out(1)");

	}

	void	SimpleNoiseNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), Scale);
		}
	}

	void	SimpleNoiseNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		if (m_outputs_count > 0)
		{
			o_update(offset, draw_list);
		}
	}

	void	SimpleNoiseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "SimpleNoise_out" + std::to_string(m_ID);


		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(Scale);

		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    SimpleNoise(";
		str_set(nodes_ptr, links);
	}
	std::string	SimpleNoiseNode::get_function_def_str()
	{
		return
			"inline float noise_randomValue(float2 uv)\n"
			"{\n"
			"    return frac(sin(dot(uv, float2(12.9898, 78.233)))*43758.5453);\n"
			"}\n"
			"inline float noise_interpolate(float a, float b, float t)\n"
			"{\n"
			"    return (1.0 - t)*a + (t*b);\n"
			"}\n"
			"inline float valueNoise(float2 uv)\n"
			"{\n"
			"    float2 i = floor(uv);\n"
			"    float2 f = frac(uv);\n"
			"    f = f * f * (3.0 - 2.0 * f);\n"
			"    uv = abs(frac(uv) - 0.5);\n"
			"    float2 c0 = i + float2(0.0, 0.0);\n"
			"    float2 c1 = i + float2(1.0, 0.0);\n"
			"    float2 c2 = i + float2(0.0, 1.0);\n"
			"    float2 c3 = i + float2(1.0, 1.0);\n"
			"    float r0 = noise_randomValue(c0);\n"
			"    float r1 = noise_randomValue(c1);\n"
			"    float r2 = noise_randomValue(c2);\n"
			"    float r3 = noise_randomValue(c3);\n"
			"    float bottomOfGrid =noise_interpolate(r0, r1, f.x);\n"
			"    float topOfGrid = noise_interpolate(r2, r3, f.x);\n"
			"    float t =noise_interpolate(bottomOfGrid, topOfGrid, f.y);\n"
			"    return t;\n"
			"}\n"
			"void SimpleNoise(float2 UV, float Scale, out float Out)\n"
			"{\n"
			"    float t = 0.0;\n"
			"    float freq = pow(2.0, float(0));\n"
			"    float amp = pow(0.5, float(3 - 0));\n"
			"    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;\n"
			"    freq = pow(2.0, float(1));\n"
			"    amp = pow(0.5, float(3 - 1));\n"
			"    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;\n"
			"    freq = pow(2.0, float(2));\n"
			"    amp = pow(0.5, float(3 - 2));\n"
			"    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;\n"
			"    Out = t;\n"
			"}\n";
	}

	VoronoiNode::VoronoiNode()
	{
		Init();
	}

	VoronoiNode::VoronoiNode(int id, const math::FVector2& pos)
		:NodeBase("Voronoi", id, pos, size, 3, 3)
	{
		Init();
	}

	VoronoiNode::~VoronoiNode()
	{
	}

	void	VoronoiNode::Init()
	{
		UV = { 0,0 };
		AngleOffset = 1.0f;
		CellDensity = 1.0f;
		m_input_name =
		{
			"UV(2)",	"AngleOffset(1)",	"CellDensity(1)"
		};
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1
		};
		m_output_name =
		{
			"Out(1)",	"Cells(1)",	"Lines(1)"
		};

		m_output_slot_type=
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1
		};

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	VoronoiNode::InputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		i_update(offset, draw_list);
		draw_list->ChannelsSetCurrent(1);

		if (!m_is_input[0])
		{
			NodeFunction::SetInputSlotUV(m_input_pos[0]);
		}

		if (!m_is_input[1])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[1], SLOT_INPUT_POS_X, StringConverter::get_space(1), AngleOffset);
		}

		if (!m_is_input[2])
		{
			NodeFunction::SetInputSlotFloat(m_input_pos[2], SLOT_INPUT_POS_X, StringConverter::get_space(2), CellDensity);
		}
	}

	void	VoronoiNode::OutputUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		o_update(offset, draw_list);
	}

	void	VoronoiNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_out_str[0] = "Volonoi_out" + std::to_string(m_ID);
		m_out_str[1] = "Volonoi_cell" + std::to_string(m_ID);
		m_out_str[2] = "Volonoi_line" + std::to_string(m_ID);


		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(AngleOffset);
		m_input_str[2] = std::to_string(CellDensity);

		//outéwíËÇ…ëŒÇ∑ÇÈíËã`
		m_function_call_str = "    float " + m_out_str[0] + ";\n";
		m_function_call_str += "    float " + m_out_str[1] + ";\n";
		m_function_call_str += "    float " + m_out_str[2] + ";\n";

		//call
		m_function_call_str += "    Voronoi(";
		//å^ÇçáÇÌÇπÇÈ
		str_set(nodes_ptr, links);
	}
	std::string	VoronoiNode::get_function_def_str()
	{
		return
			"inline float2 voronoi_noise_randomVector(float2 UV, float offset)\n"
			"{\n"
			"    float2x2 m = float2x2(15.27, 47.63, 99.41, 89.98);\n"
			"    UV = frac(sin(mul(UV, m)) * 46839.32);\n"
			"    return float2(sin(UV.y * +offset) * 0.5 + 0.5, cos(UV.x * offset) * 0.5 + 0.5);\n"
			"}\n"
			"void Voronoi(float2 UV, float AngleOffset, float CellDensity, out float Out, out float Cells, out float Lines)\n"
			"{\n"
			"    float2 g = floor(UV * CellDensity);\n"
			"    float2 f = frac(UV * CellDensity);\n"
			"    float3 res = float3(8.0, 0.0, 0.0);\n"
			"    float2 res2 = float2(8.0, 8.0);\n"

			"    for (int y = -1; y <= 1; y++)\n"
			"    {\n"
			"        for (int x = -1; x <= 1; x++)\n"
			"        {\n"
			"            float2 lattice = float2(x, y);\n"
			"            float2 offset = voronoi_noise_randomVector(lattice + g, AngleOffset);\n"
			"            float d = distance(lattice + offset, f);\n"

			"            float2 r = lattice +offset -f;\n"
			"            float d2 = dot(r,r);\n"

			"            if (d < res.x)\n"
			"            {\n"
			"                res = float3(d, offset.x, offset.y);\n"
			"                Out = res.x;\n"
			"                Cells = res.y;\n"
			"            }\n"
			"            else if (d < res.y)\n"
			"            {\n"
			"                res.y = d; \n"
			"            }\n"

			"            if (d2 < res2.x)\n"
			"            {\n"
			"                res2.y = res2.x;\n"
			"                res2.x = d2;\n"
			"            }\n"
			"            else if (d2 < res2.y)\n"
			"            {\n"
			"                res2.y = d2; \n"
			"            }\n"
			"        }\n"
			"    }\n"
			"    float2 c = sqrt(res2);\n"
			"    Lines = 1.-smoothstep(0.0, 0.1, c.y-c.x);\n"
			"}\n";
	}
}