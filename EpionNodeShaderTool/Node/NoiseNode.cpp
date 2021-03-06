#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	<cereal/cereal.hpp>
#include	<cereal/types/polymorphic.hpp>

#include	"NodeData.h"
#include	"NoiseNode.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"

namespace
{
}

CEREAL_REGISTER_TYPE(epion::Node::FBMNode)
CEREAL_REGISTER_TYPE(epion::Node::GradientNoiseNode)
CEREAL_REGISTER_TYPE(epion::Node::PhasorNoiseNode)
CEREAL_REGISTER_TYPE(epion::Node::SimpleNoiseNode)
CEREAL_REGISTER_TYPE(epion::Node::VoronoiNode)

namespace	epion::Node
{
#pragma region FBM
	FBMNode::FBMNode()
		:NodeBase(3, 1)
	{
		Init();
	}

	FBMNode::FBMNode(int id, const math::FVector2& pos)
		:NodeBase("FBM", id, pos, 3, 1)
	{
		Init();
	}

	FBMNode::~FBMNode()
	{
	}

	void FBMNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_amplitude = 0.5f;
		m_frequency = 2.0f;

		m_input_slot_type =
		{
			SLOT_TYPE::UV, SLOT_TYPE::VECTOR1, SLOT_TYPE::VECTOR1,
		};
		m_input_name =
		{
			"UV","Amplitude","Frequency",
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::NORMAL;
	}

	void	FBMNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_amplitude);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_frequency);
	}

	void	FBMNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_amplitude);
		m_input_str[2] = std::to_string(m_frequency);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrSet(nodes_ptr, links);
	}
	std::string	FBMNode::GetFunctionDefStr()
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
			"void FBM(float2 uv, float amplitude, float frequency, out float Out)\n"
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
#pragma endregion

#pragma region GradientNoise
	GradientNoiseNode::GradientNoiseNode()
		:NodeBase(2, 1)
	{
		Init();
	}

	GradientNoiseNode::GradientNoiseNode(int id, const math::FVector2& pos)
		:NodeBase("GradientNoise", id, pos, 2, 1)
	{
		Init();
	}

	GradientNoiseNode::~GradientNoiseNode()
	{
	}

	void GradientNoiseNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_scale = 10.0f;
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,
		};
		m_input_name =
		{
			"UV","Scale",
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		m_output_name.push_back("Out");
	}

	void	GradientNoiseNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_scale);
	}

	void	GradientNoiseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_scale);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);

	}
	std::string	GradientNoiseNode::GetFunctionDefStr()
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
			"float gradient_noise(float2 p)\n"
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
			"void GradientNoise(float2 UV, float Scale, out float Out)\n"
			"{\n"
			"    Out = gradient_noise(UV * Scale) + 0.5;\n"
			"}\n";
	}
#pragma endregion


#pragma region PhasorNoise
	PhasorNoiseNode::PhasorNoiseNode()
		:NodeBase(4, 3)
	{
		Init();
	}
	PhasorNoiseNode::PhasorNoiseNode(int id, const math::FVector2& pos)
		: NodeBase("PhasorNoise", id, pos, 4, 3)
	{
		Init();
	}
	PhasorNoiseNode::~PhasorNoiseNode()
	{
	}

	void	PhasorNoiseNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_a = 1.0f;
		m_b = 1.0f;
		m_c = 1.0f;

		m_input_name =
		{
			"UV",	"A",	"B",	"C",
		};
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1
		};
		m_output_name =
		{
			"A",	"B",	"C"
		};

		m_output_slot_type =
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1
		};

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	PhasorNoiseNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_a);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_b);
		if (m_is_slot_input[3] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[3], StringConverter::GetSpace(3), m_c);

	}

	void	PhasorNoiseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_a);
		m_input_str[2] = std::to_string(m_b);
		m_input_str[3] = std::to_string(m_c);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name + "A", m_ID);
		m_out_str[1] = NodeFunction::SetDefineOutName(m_Name + "B", m_ID);
		m_out_str[2] = NodeFunction::SetDefineOutName(m_Name + "C", m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetDefineOutStr1(m_out_str[1]);
		m_function_call_str += NodeFunction::SetDefineOutStr1(m_out_str[2]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}

	std::string	PhasorNoiseNode::GetFunctionDefStr()
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

#pragma endregion

#pragma region SimpleNoise
	SimpleNoiseNode::SimpleNoiseNode()
		:NodeBase(2, 1)
	{
		Init();
	}

	SimpleNoiseNode::SimpleNoiseNode(int id, const math::FVector2& pos)
		:NodeBase("SimpleNoise", id, pos, 2, 1)
	{
		Init();

	}

	SimpleNoiseNode::~SimpleNoiseNode()
	{
	}

	void	SimpleNoiseNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_scale = 500.0f;
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,
		};
		m_output_slot_type.push_back(SLOT_TYPE::VECTOR1);
		//node	slot name
		m_input_name =
		{
			"UV","Scale"
		};
		m_output_name.push_back("Out");
		m_node_type = NODE_TYPE::NORMAL;
	}

	void	SimpleNoiseNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_scale);
	}

	void	SimpleNoiseNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_scale);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name, m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string	SimpleNoiseNode::GetFunctionDefStr()
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
#pragma endregion

//TODO �R�c
#pragma region Voronoi
	VoronoiNode::VoronoiNode()
		:NodeBase( 3, 3)
	{
		Init();
	}

	VoronoiNode::VoronoiNode(int id, const math::FVector2& pos)
		:NodeBase("Voronoi", id, pos, 3, 3)
	{
		Init();
	}

	VoronoiNode::~VoronoiNode()
	{
	}

	void	VoronoiNode::Init()
	{
		m_uv = { 0.0f, 0.0f };
		m_angleoffset = 1.0f;
		m_celldensity = 1.0f;
		m_input_name =
		{
			"UV",	"AngleOffset",	"CellDensity"
		};
		m_input_slot_type =
		{
			SLOT_TYPE::UV,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1
		};
		m_output_name =
		{
			"Out",	"Cells",	"Lines"
		};

		m_output_slot_type =
		{
			SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1,	SLOT_TYPE::VECTOR1
		};

		m_node_type = NODE_TYPE::NORMAL;
	}

	void	VoronoiNode::Update(ImVec2 offset, ImDrawList*	draw_list)
	{
		DrawUpdate(offset, draw_list);
		if (m_is_slot_input[0] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotUV(m_input_pos[0]);
		if (m_is_slot_input[1] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[1], StringConverter::GetSpace(1), m_angleoffset);
		if (m_is_slot_input[2] != INPUT_SLOT_STATE::ONE)	NodeFunction::SetInputSlotFloat(m_input_pos[2], StringConverter::GetSpace(2), m_celldensity);
	}

	void	VoronoiNode::ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		m_input_str[0] = "input.uv";
		m_input_str[1] = std::to_string(m_angleoffset);
		m_input_str[2] = std::to_string(m_celldensity);

		m_out_str[0] = NodeFunction::SetDefineOutName(m_Name + "Out", m_ID);
		m_out_str[1] = NodeFunction::SetDefineOutName(m_Name + "Cell", m_ID);
		m_out_str[2] = NodeFunction::SetDefineOutName(m_Name + "Line", m_ID);
		m_function_call_str = NodeFunction::SetDefineOutStr1(m_out_str[0]);
		m_function_call_str += NodeFunction::SetDefineOutStr1(m_out_str[1]);
		m_function_call_str += NodeFunction::SetDefineOutStr1(m_out_str[2]);
		m_function_call_str += NodeFunction::SetFuncCall(m_Name);
		StrCheck(nodes_ptr, links);
	}
	std::string	VoronoiNode::GetFunctionDefStr()
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
#pragma endregion
}