struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : UV0;
    float4 color : COLOR0;
};
cbuffer TimeCBuffer : register(b0)
{
    float4 Time;
    float2 ScreenSize;
    float2 Dummy0;
};
float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

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

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);
    float1 HexagonOut_out1;
    float2 HexagonPos_out1;
    float2 HexagonScale_out1;
    float2 HexagonIndex_out1;
    Hexagon(input.uv,2.000000,HexagonOut_out1,HexagonPos_out1,HexagonScale_out1,HexagonIndex_out1);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),HexagonOut_out1,1.000000,0.000000);
    return flag_color;
}
