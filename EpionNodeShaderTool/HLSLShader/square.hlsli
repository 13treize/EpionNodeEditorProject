struct VSInput
{
    float4 position : POSITION;
    float2 uv : UV0;
    float4 color : COLOR0;
};
struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 wpos : TEXCOORD1;
    float4 lpos : TEXCOORD2;
};
//cbuffer Buffers : register(b0)
//{
//    float Time;
//    float dummy1;
//    float dummy2;
//    float dummy3;
//};
