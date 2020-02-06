#include    "ObjShader.hlsli"


PSInput VS(VSInput input)
{
    PSInput vout = (PSInput) 0;
    vout.position = mul(input.position, WorldViewProjection);
    float4 W = mul(World, input.position);


    float4 N = float4(normalize(mul((float3) input.normal, (float3x3) World)), 0.0f);
    vout.normal = N;
    vout.uv = input.uv;
    vout.wpos = W;
    vout.lpos = mul(World, float4(0, 0, 0, 1));

    return vout;
}
