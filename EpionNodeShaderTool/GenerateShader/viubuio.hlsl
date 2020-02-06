struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 wpos : TEXCOORD1;
    float4 lpos : TEXCOORD2;
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

float fbm_rand(float2 n)
{
    return frac(sin(dot(n, float2(12.9898, 4.1414))) * 43758.5453);
}
float fbm_noise(float2 p)
{
    float2 ip = floor(p);
    float2 u = frac(p);
    u = u * u * (3.0 - 2.0 * u);
    float res = lerp(
        lerp(fbm_rand(ip), fbm_rand(ip + float2(1.0, 0.0)), u.x),
        lerp(fbm_rand(ip + float2(0.0, 1.0)), fbm_rand(ip + float2(1.0, 1.0)), u.x), u.y);
    return res * res;
}
void FBM(float2 uv, float amplitude, float frequency, out float Out)
{
    float2 p = (uv * 2.0 - 1.0);
    float result = 0.;
    float amplitude2 = amplitude;
    float frequency2 = frequency;
    for (int i = 0; i < 8; i++)
    {
        result += fbm_noise(p* frequency2) * amplitude2;
        amplitude2 *= .5;
        frequency2 *= 2.;
    }
    Out = result;
}


void Multiply_float3(float3 A,float3 B, out float3 Out)
{
	Out = A * B;
}

void Add_float3(float3 A,float3 B, out float3 Out)
{
	Out = A + B;
}

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);
    float FBM_out1;
    FBM(input.uv,4.000000,2.000000,FBM_out1);

    float3 Color_out2=float3(0.000000,0.812669,0.953519);

    float3 Multiply_float3_out3;
    Multiply_float3(Color_out2,FBM_out1,Multiply_float3_out3);

    float3 Add_float3_out4;
    Add_float3(float3(0.000000,0.000000,0.000000),Multiply_float3_out3,Add_float3_out4);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),Add_float3_out4,1.000000,0.000000);
    return flag_color;
}
