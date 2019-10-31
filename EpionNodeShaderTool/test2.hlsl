struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : UV0;
    float4 color : COLOR0;
};
float4 Unlit(float4 Pos, float4 Color, float Alpha, float AlphaChipThreshold)
{
    float4 ret_color = float4(Color.rgb, Alpha);
    return ret_color;
};

inline float2 voronoi_noise_randomVector(float2 UV, float offset)
{
    float2x2 m = float2x2(15.27, 47.63, 99.41, 89.98);
    UV = frac(sin(mul(UV, m)) * 46839.32);
    return float2(sin(UV.y * +offset) * 0.5 + 0.5, cos(UV.x * offset) * 0.5 + 0.5);
}
void Voronoi_float(float2 UV, float AngleOffset, float CellDensity, out float Out, out float Cells)
{
    float2 g = floor(UV * CellDensity);
    float2 f = frac(UV * CellDensity);
    float t = 8.0;
    float3 res = float3(8.0, 0.0, 0.0);
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 lattice = float2(x, y);
            float2 offset = voronoi_noise_randomVector(lattice + g, AngleOffset);
            float d = distance(lattice + offset, f);
            if (d < res.x)
            {
                res = float3(d, offset.x, offset.y);
                Out = res.x;
                Cells = res.y;
            }
        }
    }
}

float4 PS(PSInput input) : SV_TARGET
{
    //Œq‚¢‚¾ƒm[ƒh‚Ì¶¬
    float var_1_1_0ssss = 0;

    float var_1_1_0_1_=0;
    float var_1_1_0_1_2 = 0;

    Voronoi_float(input.uv, 2, 5, var_1_1_0_1_, var_1_1_0_1_2);
    float4 color = Unlit(float4(0,0,0,0), var_1_1_0_1_2, 1, 0);

    return color;
}
