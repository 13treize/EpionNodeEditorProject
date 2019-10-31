struct appdata
{
    float4 vertex : POSITION;
    float3 normal : NORMAL;
};

struct v2f
{
    float4 pos : SV_POSITION;
    float3 normal : TEXCOORD1;
    float4 vpos : TEXCOORD2;
};

Properties {
    _Color ("Diffuse Color", Color) = (1,1,1,1)
    _Roughness ("Roughness", Float) = 0.5
    _FresnelReflectance ("Fresnel Reflectance", Float) = 0.5
}
static const float InversePI = 1.0 / PI;

