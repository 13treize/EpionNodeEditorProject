
#include    "ObjShader.hlsli"

struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
};


float4 PS(VS_OUT pin) : SV_TARGET
{
    float4 color_ ={ 1, 0, 0, 1};

    return color_;
}