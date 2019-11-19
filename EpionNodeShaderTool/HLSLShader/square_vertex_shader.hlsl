#include "square.hlsli"
cbuffer Buffers : register(b0)
{
    float4 Time;
};

PSInput VS(VSInput input)// : SV_POSITION
{
    PSInput output;

	output.position =input.position;
	output.uv = input.uv;
    output.normal = float4(0,0,0,0);

	return output;
}