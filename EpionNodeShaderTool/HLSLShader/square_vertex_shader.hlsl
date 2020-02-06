#include "square.hlsli"


PSInput VS(VSInput input)
{
    PSInput output;

	output.position =input.position;
	output.uv = input.uv;
    output.normal = float4(0,0,0,0);

	return output;
}