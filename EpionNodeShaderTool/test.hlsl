struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};
cbuffer TimeCBuffer : register(b0)
{
    float4 Time;
    float2 ScreenSize;
    float2 Dummy0;
};
cbuffer LightCBuffer : register(b1)
{
    float4 LightColor;
    float4 LightDir;
    float4 AmbientColor;
};
cbuffer CameraCBuffer : register(b2)
{
    float4 Pos;
    float4 Target;
    float4 Up;
};
cbuffer WorldCBuffer : register(b3)
{
    row_major float4x4 WorldViewProjection;
    row_major float4x4 World;
};
inline float noise_randomValue(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233)))*43758.5453);
}
inline float noise_interpolate(float a, float b, float t)
{
    return (1.0 - t)*a + (t*b);
}
inline float valueNoise(float2 uv)
{
    float2 i = floor(uv);
    float2 f = frac(uv);
    f = f * f * (3.0 - 2.0 * f);
    uv = abs(frac(uv) - 0.5);
    float2 c0 = i + float2(0.0, 0.0);
    float2 c1 = i + float2(1.0, 0.0);
    float2 c2 = i + float2(0.0, 1.0);
    float2 c3 = i + float2(1.0, 1.0);
    float r0 = noise_randomValue(c0);
    float r1 = noise_randomValue(c1);
    float r2 = noise_randomValue(c2);
    float r3 = noise_randomValue(c3);
    float bottomOfGrid =noise_interpolate(r0, r1, f.x);
    float topOfGrid = noise_interpolate(r2, r3, f.x);
    float t =noise_interpolate(bottomOfGrid, topOfGrid, f.y);
    return t;
}
void SimpleNoise(float2 UV, float Scale, out float Out)
{
    float t = 0.0;
    float freq = pow(2.0, float(0));
    float amp = pow(0.5, float(3 - 0));
    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;
    freq = pow(2.0, float(1));
    amp = pow(0.5, float(3 - 1));
    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;
    freq = pow(2.0, float(2));
    amp = pow(0.5, float(3 - 2));
    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;
    Out = t;
}

void Hexagon(float2 UV, float Scale, out float Out, out float2 Pos, out float2 oUV, out float2 Index)
{
    float2 p = UV * Scale;
    float isTwo = frac(floor(p.x) / 2.0) * 2.0;
    float isOne = 1.0 - isTwo;
    p.y += isTwo * 0.5;
    float2 rectUV = frac(p);
    float2 grid = floor(p);
    p = frac(p) - 0.5;
    float2 s = sign(p);
    p = abs(p);
    Out = abs(max(p.x * 1.5 + p.y, p.y * 2.0) - 1.0);
    float isInHex = step(p.x * 1.5 + p.y, 1.0);
    float isOutHex = 1.0 - isInHex;
    float2 grid2 = float2(0, 0);
    grid2 = lerp(float2(s.x, +step(0.0, s.y)), float2(s.x, -step(s.y, 0.0)), isTwo) *isOutHex;
    Index = grid + grid2;
    Pos = Index / Scale;
    oUV = lerp(rectUV, rectUV - s * float2(1.0, 0.5), isOutHex);
}

float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);
    float HexagonOut_out1;
    float2 HexagonPos_out1;
    float2 HexagonScale_out1;
    float2 HexagonIndex_out1;
    Hexagon(input.uv,10.000000,HexagonOut_out1,HexagonPos_out1,HexagonScale_out1,HexagonIndex_out1);

    float SimpleNoise_out0;
    SimpleNoise(HexagonPos_out1,50.000000,SimpleNoise_out0);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),float3(1.000000,0.999990,0.999990),SimpleNoise_out0,0.000000);
    return flag_color;
}
