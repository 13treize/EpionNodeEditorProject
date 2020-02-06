struct PSInput
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 wpos : TEXCOORD1;
    float4 lpos : TEXCOORD2;
};



float4 PS(PSInput vs_out) : SV_TARGET
{
    float4 set_color = float4(vs_out.uv.x, vs_out.uv.y, 0.0, 1.0);
	return	set_color;
}


