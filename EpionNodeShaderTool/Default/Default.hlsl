struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
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


void Checkerboard(float2 UV, float3 ColorA, float3 ColorB, float2 Frequency, out float3 Out)
{
    UV = (UV.xy + 0.5) * Frequency;
    float4 derivatives = float4(ddx(UV), ddy(UV));
    float2 duv_length = sqrt(float2(dot(derivatives.xz, derivatives.xz), dot(derivatives.yw, derivatives.yw)));
    float width = 1.0;
    float2 distance3 = 4.0 * abs(frac(UV + 0.25) - 0.5) - width;
    float2 scale = 0.35 / duv_length.xy;
    float freqLimiter = sqrt(clamp(1.1f - max(duv_length.x, duv_length.y), 0.0, 1.0));
    float2 vector_alpha = clamp(distance3 * scale.xy, -1.0, 1.0);
    float alpha = saturate(0.5f + 0.5f * vector_alpha.x * vector_alpha.y * freqLimiter);
    Out = lerp(ColorA, ColorB, alpha.xxx);
}

void Twirl(float2 UV, float2 Center, float Strength, float2 Offset, out float2 Out)
{
    float2 delta = UV - Center;
    float angle = Strength * length(delta);
    float x = cos(angle) * delta.x - sin(angle) * delta.y;
    float y = sin(angle) * delta.x + cos(angle) * delta.y;
    Out = float2(x + Center.x + Offset.x, y + Center.y + Offset.y);
}

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
    float VoronoiOut_out4;
    float VoronoiCell_out4;
    float VoronoiLine_out4;
    Voronoi(input.uv,0.900000,1.000000,VoronoiOut_out4,VoronoiCell_out4,VoronoiLine_out4);

    float3 Vector3_out1=float3(VoronoiOut_out4,1.000000,1.000000);

    float2 Twirl_out3;
    Twirl(input.uv,float2(0.500000,0.500000),10.000000,float2(0.000000,0.000000),Twirl_out3);

    float3 Checkerboard_out2;
    Checkerboard(Twirl_out3,float3(1.000000,0.000000,0.000000),Vector3_out1,float2(7.000000,7.000000),Checkerboard_out2);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),Checkerboard_out2,0.200000,0.000000);
    return flag_color;
}
