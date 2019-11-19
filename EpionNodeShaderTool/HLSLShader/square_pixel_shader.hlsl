struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : UV0;
    float4 color : COLOR0;
};


float4 PS(PSInput vs_out) : SV_TARGET
{
    float4 set_color = float4(1.0,1.0,0.0,1.0);
	return	set_color;
}


