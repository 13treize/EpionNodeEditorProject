//���ׂĂ̗U�d�̂ɑ΂��Ĉ��̐������˃t���l���W���B
static const float3 Fdielectric = 0.04;

static const float PI = 3.141592;
static const float Epsilon = 0.00001;
static const uint NumLights = 3;

// GGX / Towbridge-Reitz���K���z�֐��B
//�f�B�Y�j�[�̃A���t�@=�e��^ 2�̍ăp�����[�^�[�����g�p���܂��B
float ndfGGX(float cosLh, float roughness)
{
    float alpha = roughness * roughness;
    float alphaSq = alpha * alpha;

    float denom = (cosLh * cosLh) * (alphaSq - 1.0) + 1.0;
    return alphaSq / (PI * denom * denom);
}


//�ȉ��̕����\��Schlick-GGX�̒P��p��
float gaSchlickG1(float cosTheta, float k)
{
    return cosTheta / (cosTheta * (1.0 - k) + k);
}


//�X�~�X�@���g�p�����􉽊w�I�����֐���Schlick-GGX�ߎ��B
float gaSchlickGGX(float cosLi, float cosLo, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0; // Epic suggests using this roughness remapping for analytic lights.
    return gaSchlickG1(cosLi, k) * gaSchlickG1(cosLo, k);
}


//�t���l���W���̃V�����b�N�ߎ��B
float3 fresnelSchlick(float3 F0, float cosTheta)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}


float4 PBR(float3 )
{
	//�V�F�[�f�B���O���f���̃p�����[�^�[���擾���邽�߂̓��̓e�N�X�`���̃T���v���B
    float3 albedo = Albedo.xyz;
    float metalness = Metalness;
    float roughness = Roughness;
    float3 emission = Emission.xyz;

	//�o�ˌ��̕����i���[���h��Ԃ̃t���O�����g�ʒu����u�ځv�܂ł̃x�N�g���j�B
    //float3 Lo = normalize(eyePosition - pin.position);
    float3 Lo = normalize(EyePos.xyz - input.wPos);

	// ���݂̃t���O�����g�̖@�����擾���A���[���h��Ԃɕϊ����܂��B
    float3 N = normalize(input.wNormal);

    //float3 N = normalize(2.0 * normalTexture.Sample(defaultSampler, pin.texcoord).rgb - 1.0);
    //N = normalize(mul(pin.tangentBasis, N));

    //�\�ʂ̖@���Əo�ˌ��̕����̊Ԃ̊p�x�B
    float cosLo = max(0.0, dot(N, Lo));
		
    //���ʔ��˃x�N�g���B
    float3 Lr = 2.0 * cosLo * N - Lo;


    //�@�����˂ł̃t���l�����˗��i�����ɂ̓A���x�h�F���g�p�j�B
    float3 F0 = lerp(Fdielectric, albedo, metalness);

	// Direct lighting calculation for analytical lights.
    float3 directLighting = 0.0;
    for (uint i = 0; i < NumLights; ++i)
    {
        float3 Li = -LightDir.xyz;
        float3 Lradiance = 1.0f;

		// Half-vector between Li and Lo.
        float3 Lh = normalize(Li + Lo);


        //�\�ʂ̖@���Ƃ��܂��܂ȃ��C�g�x�N�g���̊Ԃ̊p�x���v�Z���܂�
        float cosLi = max(0.0, dot(N, Li));
        float cosLh = max(0.0, dot(N, Lh));

		// Calculate Fresnel term for direct lighting. 
        float3 F = fresnelSchlick(F0, max(0.0, dot(Lh, Lo)));

        //���ʔ��ˌ�BRDF�̐��K���z���v�Z���܂��B
        float D = ndfGGX(cosLh, roughness);
        //���ʔ���BRDF�̊􉽊w�I�������v�Z���܂��B
        float G = gaSchlickGGX(cosLi, cosLo, roughness);


        //�g�U�U���́A�U�d�̂ɂ���Č�����������܂��邽�߂ɔ������܂��B
        //����A�����̓G�l���M�[�𔽎˂܂��͋z�����邽�߁A�g�U��^�͏�Ƀ[���ł��B
        //�G�l���M�[��ߖ񂷂�ɂ́A�t���l���W���Ƌ������Ɋ�Â��Ċg�UBRDF�̊�^���X�P�[�����O����K�v������܂��B
        float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metalness);


        //�����o�[�g�g�UBRDF�B
        //�Ɩ��ƃ}�e���A���̃��j�b�g�����֗��ɂ��邽�߂ɁA1 / PI�ŃX�P�[�����O���܂���B		// See: https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/
        float3 diffuseBRDF = kd * albedo;


        // Cook-Torrance�X�y�L�����[�}�C�N���t�@�Z�b�gBRDF�B
        float3 specularBRDF = (F * D * G) / max(Epsilon, 4.0 * cosLi * cosLo);

		// Total contribution for this light.
        directLighting += (diffuseBRDF + specularBRDF) * Lradiance * cosLi;
    }

	// Ambient lighting (IBL).
    float3 ambientLighting;
	{
        //�@�������̊g�U���ˏƓx���T���v�����O���܂��B
        float3 irradiance =
        {
            1.0, 0.3, 0.2
        };

        //���Ɩ��̃t���l�������v�Z���܂��B
        //���O�Ƀt�B���^�����O���ꂽ�L���[�u�}�b�v���g�p���A���ˏƓx�͑����̕������痈�邽��
        //���C�g�̃n�[�t�x�N�g���i��L��cosLh�j�Ŋp�x�̑����cosLo���g�p���܂��B		// See: https://seblagarde.wordpress.com/2011/08/17/hello-world/
        float3 F = fresnelSchlick(F0, cosLo);


        //�g�U��^�����擾���܂��i���ڏƖ��̏ꍇ�Ɠ��l�j�B
        float3 kd = lerp(1.0 - F, 0.0, metalness);


        //���ˏƓx�}�b�v�ɂ́A�����o�[�gBRDF��z�肵�����ˋP�x���܂܂�Ă���A�����ł�1 / PI�ŃX�P�[�����O����K�v�͂���܂���B
        float3 diffuseIBL = kd * albedo * irradiance;
        
        //�������~�b�v�}�b�v���x���ł̎��O�t�B���^�����O���ꂽ���ʔ��ˊ��̃T���v���B
        //  uint specularTextureLevels = querySpecularTextureLevels();
        float3 specularIrradiance = { 1.0, 1.0, 1.0 };


        // Cook-Torrance�X�y�L����BRDF�̕������v�ߎ��W���B
        //float2 specularBRDF = specularBRDF_LUT.Sample(spBRDF_Sampler, float2(cosLo, roughness)).rg;
        float2 specularBRDF = { 1.0f, 0.0f };

		// Total specular IBL contribution.
        float3 specularIBL = (F0 * specularBRDF.x + specularBRDF.y) * specularIrradiance;

		// Total ambient lighting contribution.
        ambientLighting = diffuseIBL + specularIBL;
    }

	// Final fragment color.
    return float4(directLighting + ambientLighting + emission, 1.0);
}