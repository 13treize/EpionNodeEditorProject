#include "square.hlsli"
SamplerState sample0 : register(s0);
Texture2D tex0 : register(t0);
RWTexture2D tex1 : register(u1);
Texture2D tex2 : register(t1);
// UAV �փ����_�����O
float4 PSMain(PSInput pin, float4 fscrpos : SV_POSITION) : SV_TARGET
{
    // �������ރf�[�^�̃e�N�X�`��
    float3 data = tex2[pin.uv];

    // �t���[���o�b�t�@�̍��W
    int2 scrpos = (int2) (fscrpos.xy);

    // �t���[���o�b�t�@�̓��e��ǂݏo��
    float3 scrdata = tex1[scrpos];

    // �K���Ƀu�����h���Ă݂�
    data.r=1.0f;

    // UAV �֏�������ł���
    tex1[scrpos.xy + int2(100, 0)] = data;
    tex1[scrpos.xy + int2(0, 0)] = data;

    // RTV �ւ͏o�͂��Ȃ�
    return float4(0, 0, 0, 0);
}