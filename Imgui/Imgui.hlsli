cbuffer vertexBuffer : register(b0)
{
    float4x4 ProjectionMatrix;
};

cbuffer vertexBuffer2 : register(b1)
{
    float Time;
    float bummy1;
    float bummy2;
    float bummy3;
};
struct VS_INPUT
{
    float2 pos : POSITION;
    float4 col : COLOR0;
    float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 uv : TEXCOORD0;
};
