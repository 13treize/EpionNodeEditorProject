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


float sphere(float3 p, float a)
{
    float d = length(p) - a;
    return d;
}

float4 PS(PSInput input) : SV_TARGET
{
    float3 col = float3(0., 0.6, 0.6);
    float2 p = (input.uv.xy * 2.0 - 400) / 1000.;
    float3 up = normalize(float3(0., 1., 0.));
    float3 ro = float3(2.);
    float3 ta = float3(0.);
    float3 cdir = normalize(ta - ro);
    float3 side = cross(cdir, up);
    up = cross(side, cdir);
    float fov = 3.;
    float3 rd = normalize(up * p.y + side * p.x + cdir * fov);
    float t = 0.00001;
    float d = 0.;

    for (int i = 0; i < 99; i++)
    {
        float3 pos = ro + rd * t;
        
        d = sphere(pos, 0.5);
        //t+=d;
        if (d < 0.00001)
        {
            col = float3(ro + rd * t);
        }
        t += d;
    }
    return float4(col, 1.0);
}
