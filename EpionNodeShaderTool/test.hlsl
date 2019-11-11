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
SamplerState SamplerStates0 : register(s0);

Texture2D tex0 : register(t0);

float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

void Twirl(float2 UV, float2 Center, float Strength, float2 Offset, out float2 Out)
{
    float2 delta = UV - Center;
    float angle = Strength * length(delta);
    float x = cos(angle) * delta.x - sin(angle) * delta.y;
    float y = sin(angle) * delta.x + cos(angle) * delta.y;
    Out = float2(x + Center.x + Offset.x, y + Center.y + Offset.y);
}

void SamplerTexture2D(float2 uv, Texture2D t, SamplerState s, out float4 Out)
{
	Out = t.Sample(s, uv);
}
float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);
    float2 Twirl_out1;
    Twirl(input.uv,float2(0.500000,0.500000),0.000000,float2(0.000000,0.000000),Twirl_out1);



    float4 SamplerTexture2D_out3;
    SamplerTexture2D(Twirl_out1,tex0,SamplerStates0,SamplerTexture2D_out3);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),SamplerTexture2D_out3.xyz,1.000000,0.000000);
    return flag_color;
}
