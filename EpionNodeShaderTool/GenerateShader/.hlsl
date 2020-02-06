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
float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    if (Alpha < AlphaChipThreshold)
    {
        Alpha = 0;
    }
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

inline float2 voronoi_noise_randomVector(float2 UV, float offset)
{
    float2x2 m = float2x2(15.27, 47.63, 99.41, 89.98);
    UV = frac(sin(mul(UV, m)) * 46839.32);
    return float2(sin(UV.y * +offset) * 0.5 + 0.5, cos(UV.x * offset) * 0.5 + 0.5);
}
void Voronoi(float2 UV, float AngleOffset, float CellDensity, out float Out, out float Cells, out float Lines)
{
    float2 g = floor(UV * CellDensity);
    float2 f = frac(UV * CellDensity);
    float3 res = float3(8.0, 0.0, 0.0);
    float2 res2 = float2(8.0, 8.0);
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 lattice = float2(x, y);
            float2 offset = voronoi_noise_randomVector(lattice + g, AngleOffset);
            float d = distance(lattice + offset, f);
            float2 r = lattice +offset -f;
            float d2 = dot(r,r);
            if (d < res.x)
            {
                res = float3(d, offset.x, offset.y);
                Out = res.x;
                Cells = res.y;
            }
            else if (d < res.y)
            {
                res.y = d; 
            }
            if (d2 < res2.x)
            {
                res2.y = res2.x;
                res2.x = d2;
            }
            else if (d2 < res2.y)
            {
                res2.y = d2; 
            }
        }
    }
    float2 c = sqrt(res2);
    Lines = 1.-smoothstep(0.0, 0.1, c.y-c.x);
}

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);
    float VoronoiOut_out1;
    float VoronoiCell_out1;
    float VoronoiLine_out1;
    Voronoi(input.uv,4.000000,7.000000,VoronoiOut_out1,VoronoiCell_out1,VoronoiLine_out1);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),VoronoiCell_out1,1.000000,0.000000);
    return flag_color;
}
