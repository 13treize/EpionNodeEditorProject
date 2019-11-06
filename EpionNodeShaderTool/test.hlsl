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

void PolarCoordinates(float2 UV, float2 Center, float RadialScale, float LengthScale, out float2 Out)
{
    float2 delta = UV - Center;
    float radius = length(delta) * 2 * RadialScale;
    float angle = atan2(delta.x, delta.y) * 1.0 / 6.28 * LengthScale;
    Out = float2(radius, angle);
}

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);
    float2 PolarCoordinates_out1;
    PolarCoordinates(input.uv,float2(0.500000,0.500000),1.000000,1.000000,PolarCoordinates_out1);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),float3(PolarCoordinates_out1, 0.0),1.000000,0.000000);
    return flag_color;
}
