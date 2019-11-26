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

void Multiply_float(float A,float B, out float Out)
{
	Out = A * B;
}

void Fraction_float(float In, out float Out)
{
    Out = frac(In);
};

void Add_float(float A,float B, out float Out)
{
	Out = A + B;
}

void Step_float(float Edge,float In, out float Out)
{
       Out = step(Edge, In);
}

inline float noise_randomValue(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233)))*43758.5453);
}
inline float noise_interpolate(float a, float b, float t)
{
    return (1.0 - t)*a + (t*b);
}
inline float valueNoise(float2 uv)
{
    float2 i = floor(uv);
    float2 f = frac(uv);
    f = f * f * (3.0 - 2.0 * f);
    uv = abs(frac(uv) - 0.5);
    float2 c0 = i + float2(0.0, 0.0);
    float2 c1 = i + float2(1.0, 0.0);
    float2 c2 = i + float2(0.0, 1.0);
    float2 c3 = i + float2(1.0, 1.0);
    float r0 = noise_randomValue(c0);
    float r1 = noise_randomValue(c1);
    float r2 = noise_randomValue(c2);
    float r3 = noise_randomValue(c3);
    float bottomOfGrid =noise_interpolate(r0, r1, f.x);
    float topOfGrid = noise_interpolate(r2, r3, f.x);
    float t =noise_interpolate(bottomOfGrid, topOfGrid, f.y);
    return t;
}
void SimpleNoise(float2 UV, float Scale, out float Out)
{
    float t = 0.0;
    float freq = pow(2.0, float(0));
    float amp = pow(0.5, float(3 - 0));
    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;
    freq = pow(2.0, float(1));
    amp = pow(0.5, float(3 - 1));
    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;
    freq = pow(2.0, float(2));
    amp = pow(0.5, float(3 - 2));
    t += valueNoise(float2(UV.x*Scale / freq, UV.y*Scale / freq))*amp;
    Out = t;
}


void OneMinus_float(float In, out float Out)
{
    Out = 1 - In;
};

void Multiply_float3(float3 A,float3 B, out float3 Out)
{
	Out = A * B;
}

float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    if (Alpha < AlphaChipThreshold)
    {
        Alpha = 0;
    }
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

float4 PS(PSInput input) : SV_TARGET
{
    float Time_ =Time.x;
    float Sin_Time_ =sin(Time.x);
    float Cos_Time_ =cos(Time.x);

    float Multiply_float_out1;
    Multiply_float(Time_,2.000000,Multiply_float_out1);

    float Fraction_float_out2;
    Fraction_float(Multiply_float_out1,Fraction_float_out2);

    float Add_float_out3;
    Add_float(Fraction_float_out2,0.070000,Add_float_out3);

    float SimpleNoise_out5;
    SimpleNoise(input.uv,50.000000,SimpleNoise_out5);

    float Step_float_out4;
    Step_float(Add_float_out3,SimpleNoise_out5,Step_float_out4);


    float OneMinus_float_out7;
    OneMinus_float(Step_float_out4,OneMinus_float_out7);

    float Multiply_float_out11;
    Multiply_float(Time_,2.000000,Multiply_float_out11);

    float3 Color_out6=float3(0.045937,0.970414,0.000000);

    float Fraction_float_out12;
    Fraction_float(Multiply_float_out11,Fraction_float_out12);

    float SimpleNoise_out10;
    SimpleNoise(input.uv,50.000000,SimpleNoise_out10);

    float3 Multiply_float3_out8;
    Multiply_float3(Color_out6,OneMinus_float_out7,Multiply_float3_out8);

    float4 flag_color = Unlit(float4(0.000000,0.000000,0.000000,0.000000),Multiply_float3_out8,SimpleNoise_out10,Fraction_float_out12);
    return flag_color;
}
