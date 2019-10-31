#include    "ObjShader.hlsli"

struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : UV;
};

VS_OUT VS(float4 position : POSITION, float4 normal : NORMAL, float2 uv : UV)
{
    VS_OUT vout;
    vout.position = mul(position, world_view_projection);

    float4 N = float4(normalize(mul((float3) normal, (float3x3) world)), 0.0f);
    vout.normal = N;
    vout.uv = uv;

    return vout;
}
