cbuffer WorldCBuffer : register(b3)
{
    row_major float4x4 WorldViewProjection;
    row_major float4x4 World;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
};
