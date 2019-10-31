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

void Ellipse(float2 UV, float Width, float Height, out float Out)
{
    float d = length((UV * 2 - 1) / float2(Width, Height));
    Out = saturate((1 - d) / fwidth(d));
}

float4 PS(PSInput input) : SV_TARGET
{
float Time_ =Time.x;
float Sin_Time_ =sin(Time.x);
float Cos_Time_ =cos(Time.x);
    float Ellipse_out1;
    Ellipse(input.uv,1.000000,1.000000,Ellipse_out1);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000, 0.0),Ellipse_out1,1.000000,0.000000);
    return flag_color;
}
