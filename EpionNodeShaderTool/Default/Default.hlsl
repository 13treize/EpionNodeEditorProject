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


void Multiply_float3(float3 A,float3 B, out float3 Out)
{
	Out = A * B;
}

void Multiply_float(float A,float B, out float Out)
{
	Out = A * B;
}

float2 gradientNoise_dir(float2 p)
{
    p = p % 289;
    float x = (34 * p.x + 1) * p.x % 289 + p.y;
    x = (34 * x + 1) * x % 289;
    x = frac(x / 41) * 2 - 1;
    return normalize(float2(x - floor(x + 0.5), abs(x) - 0.5));
}
float gradient_noise(float2 p)
{
    float2 ip = floor(p);
    float2 fp = frac(p);
    float d00 = dot(gradientNoise_dir(ip), fp);
    float d01 = dot(gradientNoise_dir(ip + float2(0, 1)), fp - float2(0, 1));
    float d10 = dot(gradientNoise_dir(ip + float2(1, 0)), fp - float2(1, 0));
    float d11 = dot(gradientNoise_dir(ip + float2(1, 1)), fp - float2(1, 1));
    fp = fp * fp * fp * (fp * (fp * 6 - 15) + 10);
    return lerp(lerp(d00, d01, fp.y), lerp(d10, d11, fp.y), fp.x);
}
void GradientNoise(float2 UV, float Scale, out float Out)
{
    Out = gradient_noise(UV * Scale) + 0.5;
}

void TilingAndOffset(float2 UV, float2 Tiling, float2 Offset, out float2 Out)
{
    Out = UV * Tiling + Offset;
}


void Power_float(float A,float B, out float Out)
{
	Out = pow(A, B);
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


void Add_float(float A,float B, out float Out)
{
	Out = A + B;
}

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);


    float2 TilingAndOffset_out9;
    TilingAndOffset(input.uv,float2(1.000000,1.000000),Time_,TilingAndOffset_out9);


    float Add_float_out12;
    Add_float(Sin_Time_,1.300000,Add_float_out12);

    float VoronoiOut_out8;
    float VoronoiCell_out8;
    float VoronoiLine_out8;
    Voronoi(TilingAndOffset_out9,2.000000,1.000000,VoronoiOut_out8,VoronoiCell_out8,VoronoiLine_out8);

    float2 TilingAndOffset_out5;
    TilingAndOffset(input.uv,float2(1.000000,1.000000),Time_,TilingAndOffset_out5);

    float3 Vector3_out10=float3(Add_float_out12,0.600000,0.000000);

    float Power_float_out7;
    Power_float(VoronoiOut_out8,0.000000,Power_float_out7);

    float GradientNoise_out4;
    GradientNoise(TilingAndOffset_out5,5.000000,GradientNoise_out4);

    float Multiply_float_out3;
    Multiply_float(GradientNoise_out4,Power_float_out7,Multiply_float_out3);

    float3 Color_out1=Vector3_out10;

    float3 Multiply_float3_out2;
    Multiply_float3(Color_out1,Multiply_float_out3,Multiply_float3_out2);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),Multiply_float3_out2,1.000000,0.000000);
    return flag_color;
}
