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
void Checkerboard(float2 UV, float3 ColorA, float3 ColorB, float2 Frequency, out float3 Out)
{
    UV = (UV.xy + 0.5) * Frequency;
    float4 derivatives = float4(ddx(UV), ddy(UV));
    float2 duv_length = sqrt(float2(dot(derivatives.xz, derivatives.xz), dot(derivatives.yw, derivatives.yw)));
    float width = 1.0;
    float2 distance3 = 4.0 * abs(frac(UV + 0.25) - 0.5) - width;
    float2 scale = 0.35 / duv_length.xy;
    float freqLimiter = sqrt(clamp(1.1f - max(duv_length.x, duv_length.y), 0.0, 1.0));
    float2 vector_alpha = clamp(distance3 * scale.xy, -1.0, 1.0);
    float alpha = saturate(0.5f + 0.5f * vector_alpha.x * vector_alpha.y * freqLimiter);
    Out = lerp(ColorA, ColorB, alpha.xxx);
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
    float3 Checkerboard_out0;
   Checkerboard(input.uv,float3(1.000000,0.999990,0.999990),float3(0.000000,0.000000,0.000000),float2(1.000000,1.000000),Checkerboard_out0);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000, 0.0),Checkerboard_out0,1.000000,0.000000);
    return flag_color;
}
