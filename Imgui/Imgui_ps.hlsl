#include"Imgui.hlsli"

sampler sampler0;
Texture2D texture0;
float4 main(PS_INPUT input) : SV_TARGET\
{
float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
    return out_col;
};

