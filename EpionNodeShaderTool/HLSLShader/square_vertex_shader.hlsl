#include "square.hlsli"
cbuffer Buffers : register(b0)
{
    float4 Time;
};

PSInput VS(VS_INPUT input)// : SV_POSITION
{
    PSInput output;

	output.position =input.position;
	output.uv = input.uv;
	output.color = input.color;

	return output;
}