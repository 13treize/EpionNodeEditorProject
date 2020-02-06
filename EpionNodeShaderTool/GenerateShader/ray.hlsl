struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 wpos : TEXCOORD1;
    float4 lpos : TEXCOORD2;
};

cbuffer TimeCBuffer : register(b0)
{
    float4 Time;
    float2 ScreenSize;
    float2 Dummy0;
};
cbuffer LightCBuffer : register(b1)
{
    float4 LightColor;
    float4 LightDir;
    float4 AmbientColor;
};
cbuffer CameraCBuffer : register(b2)
{
    float4 Pos;
    float4 Target;
    float4 Up;
};
cbuffer WorldCBuffer : register(b3)
{
    row_major float4x4 WorldViewProjection;
    row_major float4x4 World;
};
float3x3 m = float3x3(0.00, 0.80, 0.60,
              -0.80, 0.36, -0.48,
              -0.60, -0.48, 0.64);


inline float smoothMin(float d1, float d2, float k)
{
    float h = exp(-k * d1) + exp(-k * d2);
    return -log(h) / k;
}

inline float sphere(float3 pos, float radius)
{
    //float a = abs(pos - radius) - radius;
    //return max(a,a);
    return length(pos) - radius;
}


inline bool IsInnerBox(float3 pos, float3 scale)
{
    return all(max(scale * 1.0 - abs(pos), 0.0));
}



inline float _DistanceFunction(float3 pos)
{
    //return cloud(pos);
    return smoothMin(
        sphere(pos - float3(0.2, 0.2, 0.2), 0.3),
        sphere(pos - float3(-0.2, -0.2, -0.2), 0.3),
        8.0);
}

inline float DistanceFunction(float3 pos, float3 scale)
{
    return _DistanceFunction(float3(pos * scale));
}
inline void raymarch(int loop, float3 camera_pos, float3 local_pos, inout float4 world_pos, inout float4 color)
{
    color = float4(0.0, 0.0, 0.0, 1.0);
    float3 to = world_pos.xyz - camera_pos;
    float ray_length = length(to);
    float3 forward = normalize(to);

    float eyeDepth = 10.0f;

    float maxLen = eyeDepth / dot(forward, float3(0.0, 0.0, 0.0));

    float dist = 0.0;
    float3 transformPos = local_pos;

    for (int n = 0; n < loop; ++n)
    {
        dist = DistanceFunction(float3(world_pos.xyz - transformPos), float3(1.0,1.0,1.0));
        ray_length += dist;
        world_pos.xyz += forward * dist;
        if (dist < 0.001 || ray_length > maxLen)
        {
            break;
        }
        if (!IsInnerBox(float3(world_pos.xyz - transformPos), 1.0))
        {
            break;
        }
    }

    if (dist > 0.001 || ray_length > maxLen)
    {
        discard;
    }
}
float4 PS(PSInput input) : SV_TARGET
{
    float4 color;
    //float3 pos = input.wPos.xyz;
    raymarch(100, Pos.xyz, input.lpos.xyz, input.wpos, color);

    color = float4(1.0, 0.0, 0.0, 1.0);
    return color;
}