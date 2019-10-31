struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : UV0;
    float4 color : COLOR0;
};
cbuffer Buffers : register(b0)
{
    float4 Time;
};
//float Sin_Time = sin(Time);

float4 Unlit(float4 Pos, float4 Color, float Alpha, float AlphaChipThreshold)
{
    float4 ret_color = float4(Color.rgb, Alpha);
    return ret_color;
};

float4 PS(PSInput vs_out) : SV_TARGET
{
    //__XB_MemTime();
    float4 Pos = { 0, 0, 0, 0 };
    float4 Color = { 0, 0, 0, 1 };
    float Alpha = 1.0f;
    float AlphaChipThreshold = 0.0f;

    float4 set_color = Unlit(Pos, Color, Alpha, 0);
	return	set_color;
}


