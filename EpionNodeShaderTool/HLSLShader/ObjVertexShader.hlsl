#include    "ObjShader.hlsli"


PSInput VS(PSInput input)
{
    PSInput vout;
    vout.position = mul(input.position, WorldViewProjection);

    float4 N = float4(normalize(mul((float3) input.normal, (float3x3) World)), 0.0f);
    vout.normal = N;
    vout.uv = input.uv;

    return vout;
}
