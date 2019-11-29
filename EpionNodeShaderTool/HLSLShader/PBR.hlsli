//float4 PBR(float3 Albedo, float3 Normal, float3 Emission, float Metallic, float Roughness, float Alpha, float AlphaChipThreshold)
//{
//    float3 Lo = normalize(EyePos.xyz - input.wPos);
//    float3 N = normalize(Normal);
//    float cosLo = max(0.0, dot(N, Lo));
//    float3 Lr = 2.0 * cosLo * N - Lo;
//    float3 F0 = lerp(Fdielectric, Albedo, Metallic);
//    float3 directLighting = 0.0;
//    for (uint i = 0; i < NumLights; ++i)
//    {
//        float3 Li = -LightDir.xyz;
//        float3 Lradiance = 1.0f;
//        float3 Lh = normalize(Li + Lo);
//        float cosLi = max(0.0, dot(N, Li));
//        float cosLh = max(0.0, dot(N, Lh));
//        float3 F = fresnelSchlick(F0, max(0.0, dot(Lh, Lo)));
//        float D = ndfGGX(cosLh, Roughness);
//        float G = gaSchlickGGX(cosLi, cosLo, Roughness);


//        //�g�U�U���́A�U�d�̂ɂ���Č�����������܂��邽�߂ɔ������܂��B
//        //����A�����̓G�l���M�[�𔽎˂܂��͋z�����邽�߁A�g�U��^�͏�Ƀ[���ł��B
//        //�G�l���M�[��ߖ񂷂�ɂ́A�t���l���W���Ƌ������Ɋ�Â��Ċg�UBRDF�̊�^���X�P�[�����O����K�v������܂��B
//        float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metalness);


//        //�����o�[�g�g�UBRDF�B
//        //�Ɩ��ƃ}�e���A���̃��j�b�g�����֗��ɂ��邽�߂ɁA1 / PI�ŃX�P�[�����O���܂���B		// See: https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/
//        float3 diffuseBRDF = kd * albedo;


//        // Cook-Torrance�X�y�L�����[�}�C�N���t�@�Z�b�gBRDF�B
//        float3 specularBRDF = (F * D * G) / max(Epsilon, 4.0 * cosLi * cosLo);

//		// Total contribution for this light.
//        directLighting += (diffuseBRDF + specularBRDF) * Lradiance * cosLi;
//    }
//}




//float Cook_Tarrance_GGX(in float3 pos, in float3 normal, in float3 light, in float roughness, in float fresnel, in float3 eyePos)
//{
//    float3 Normal = normalize(normal);
//    float3 LightVec = normalize(light);
//    float3 EyeVec = normalize(eyePos - pos);
//    float3 HalfVec = normalize(LightVec + EyeVec);
//    float NdotL = dot(Normal, LightVec);
//    float NdotE = dot(Normal, EyeVec);
//    float NdotH = dot(Normal, HalfVec);
//    float EdotH = dot(EyeVec, HalfVec);

//    //  Distribution function of directions facets
//    //  ���ו\�ʔ��˕��z��
//    //  �����ł�Trowbridge-Reitz(GGX)
//    float sqrNdotH = sqrt(NdotH);
//    float D = InversePI * sqrt(roughness / (sqrNdotH * (roughness * roughness - 1.0) + 1.0));
//    //  Fresnel factor
//    //  �t���l����
//    //  �����ł͋ߎ�����p����
//    float F = fresnel + (1.0 - fresnel) * pow(1.0 - NdotE, 5);
//    //  Geometrical attenuation factor
//    //  �􉽌�����
//    float G = min(1.0, min(2 * NdotH * NdotE / EdotH, 2 * NdotH * NdotL / EdotH));

//    return ((D * F * G) / (NdotL * NdotE + 0.000001f)) * InversePI;
//}
//// D -�}�C�N���t�@�Z�b�g�̍�
////  �����ł�Trowbridge-Reitz(GGX)
////https://hanecci.hatenadiary.org/entry/20130511/p1
//float D_GGX(float Roughness, float3 H, float3 N)
//{
//    float NdotH = saturate(dot(H, N));
//    float roughness = saturate(Roughness);
//    float alpha = roughness * roughness;
//    float alpha2 = alpha * alpha;
//    float t = ((NdotH * NdotH) * (alpha2 - 1.0) + 1.0);
//    float PI = 3.1415926535897;
//    return alpha2 / (PI * t * t);
//}
//// F - �t���l���̍�
//float Flesnel(float Fresnels, float3 V, float3 H)
//{
//    float VdotH = saturate(dot(V, H));
//    float F0 = saturate(Fresnels);
//    float F = pow(1.0 - VdotH, 5.0);
//    F *= (1.0 - F0);
//    F += F0;
//    return F;
//}
//// G - �􉽌����̍��i�N�b�N �g�����X���f���j
//float G_CookTorrance(float3 L, float3 V, float3 H, float3 N)
//{
//    float NdotH = saturate(dot(N, H));
//    float NdotL = saturate(dot(N, L));
//    float NdotV = saturate(dot(N, V));
//    float VdotH = saturate(dot(V, H));

//    float NH2 = 2.0 * NdotH;
//    float g1 = (NH2 * NdotV) / VdotH;
//    float g2 = (NH2 * NdotL) / VdotH;
//    float G = min(1.0, min(g1, g2));
//    return G;
//}

//float4 PBRMaster(float3 Albedo, float Fresnels, float Roughness)
//{

//// �����ƃ}�e���A���̐F�����Z
//    float3 ambientLight = unity_AmbientEquator.xyz * Albedo.rgb;

//    // ���[���h��ԏ�̃��C�g�ʒu�Ɩ@���Ƃ̓��ς��v�Z
//    float3 lightDirectionNormal = normalize(_WorldSpaceLightPos0.xyz);
//    float NdotL = saturate(dot(i.normal, lightDirectionNormal));

//    // ���[���h��ԏ�̎��_�i�J�����j�ʒu�Ɩ@���Ƃ̓��ς��v�Z
//    float3 viewDirectionNormal = normalize((float4(_WorldSpaceCameraPos, 1.0) - i.vpos).xyz);
//    float NdotV = saturate(dot(i.normal, viewDirectionNormal));

//    // ���C�g�Ǝ��_�x�N�g���̃n�[�t�x�N�g�����v�Z
//    float3 halfVector = normalize(lightDirectionNormal + viewDirectionNormal);

//    // D_GGX�̍�
//    float D = D_GGX(Roughness, halfVector, i.normal);

//    // F�̍�
//    float F = Flesnel(Fresnels, viewDirectionNormal, halfVector);

//    // G�̍�
//    float G = G_CookTorrance(lightDirectionNormal, viewDirectionNormal, halfVector, i.normal);

//    // �X�y�L��������уf�B�t���[�Y���v�Z
//    float specularReflection = (D * F * G) / (4.0 * NdotV * NdotL + 0.000001);
//    float3 diffuseReflection = _LightColor0.xyz * Albedo.xyz * NdotL;

//    // �Ō�ɐF�����Z���ďo��
//    return float4(ambientLight + diffuseReflection + specularReflection, 1.0);
//}