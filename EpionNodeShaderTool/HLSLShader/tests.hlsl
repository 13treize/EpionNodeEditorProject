#include "square.hlsli"
SamplerState sample0 : register(s0);
Texture2D tex0 : register(t0);
RWTexture2D tex1 : register(u1);
Texture2D tex2 : register(t1);
// UAV へレンダリング
float4 PSMain(PSInput pin, float4 fscrpos : SV_POSITION) : SV_TARGET
{
    // 書き込むデータのテクスチャ
    float3 data = tex2[pin.uv];

    // フレームバッファの座標
    int2 scrpos = (int2) (fscrpos.xy);

    // フレームバッファの内容を読み出す
    float3 scrdata = tex1[scrpos];

    // 適当にブレンドしてみる
    data.r=1.0f;

    // UAV へ書き込んでいる
    tex1[scrpos.xy + int2(100, 0)] = data;
    tex1[scrpos.xy + int2(0, 0)] = data;

    // RTV へは出力しない
    return float4(0, 0, 0, 0);
}