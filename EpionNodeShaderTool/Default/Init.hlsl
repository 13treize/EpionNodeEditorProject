                                  struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
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
float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    if (Alpha < AlphaChipThreshold)
    {
        Alpha = 0;
    }
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ = Time.x;
    float Sin_Time_ = sin(Time.x);
    float Cos_Time_ = cos(Time.x);
    float4 flag_color = Unlit(float4(0.000000, 0.000000, 0.000000, 0.000000), float3(0.000000, 0.000000, 0.000000), 1.000000, 0.000000);
    return flag_color;
}
