//すべての誘電体に対して一定の垂直入射フレネル係数。
static const float3 Fdielectric = 0.04;

static const float PI = 3.141592;
static const float Epsilon = 0.00001;
static const uint NumLights = 3;

// GGX / Towbridge-Reitz正規分布関数。
//ディズニーのアルファ=粗さ^ 2の再パラメーター化を使用します。
float ndfGGX(float cosLh, float roughness)
{
    float alpha = roughness * roughness;
    float alphaSq = alpha * alpha;

    float denom = (cosLh * cosLh) * (alphaSq - 1.0) + 1.0;
    return alphaSq / (PI * denom * denom);
}


//以下の分離可能なSchlick-GGXの単一用語
float gaSchlickG1(float cosTheta, float k)
{
    return cosTheta / (cosTheta * (1.0 - k) + k);
}


//スミス法を使用した幾何学的減衰関数のSchlick-GGX近似。
float gaSchlickGGX(float cosLi, float cosLo, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0; // Epic suggests using this roughness remapping for analytic lights.
    return gaSchlickG1(cosLi, k) * gaSchlickG1(cosLo, k);
}


//フレネル係数のシュリック近似。
float3 fresnelSchlick(float3 F0, float cosTheta)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}


float4 PBR(float3 )
{
	//シェーディングモデルのパラメーターを取得するための入力テクスチャのサンプル。
    float3 albedo = Albedo.xyz;
    float metalness = Metalness;
    float roughness = Roughness;
    float3 emission = Emission.xyz;

	//出射光の方向（ワールド空間のフラグメント位置から「目」までのベクトル）。
    //float3 Lo = normalize(eyePosition - pin.position);
    float3 Lo = normalize(EyePos.xyz - input.wPos);

	// 現在のフラグメントの法線を取得し、ワールド空間に変換します。
    float3 N = normalize(input.wNormal);

    //float3 N = normalize(2.0 * normalTexture.Sample(defaultSampler, pin.texcoord).rgb - 1.0);
    //N = normalize(mul(pin.tangentBasis, N));

    //表面の法線と出射光の方向の間の角度。
    float cosLo = max(0.0, dot(N, Lo));
		
    //鏡面反射ベクトル。
    float3 Lr = 2.0 * cosLo * N - Lo;


    //法線入射でのフレネル反射率（金属にはアルベド色を使用）。
    float3 F0 = lerp(Fdielectric, albedo, metalness);

	// Direct lighting calculation for analytical lights.
    float3 directLighting = 0.0;
    for (uint i = 0; i < NumLights; ++i)
    {
        float3 Li = -LightDir.xyz;
        float3 Lradiance = 1.0f;

		// Half-vector between Li and Lo.
        float3 Lh = normalize(Li + Lo);


        //表面の法線とさまざまなライトベクトルの間の角度を計算します
        float cosLi = max(0.0, dot(N, Li));
        float cosLh = max(0.0, dot(N, Lh));

		// Calculate Fresnel term for direct lighting. 
        float3 F = fresnelSchlick(F0, max(0.0, dot(Lh, Lo)));

        //鏡面反射光BRDFの正規分布を計算します。
        float D = ndfGGX(cosLh, roughness);
        //鏡面反射BRDFの幾何学的減衰を計算します。
        float G = gaSchlickGGX(cosLi, cosLo, roughness);


        //拡散散乱は、誘電体によって光が複数回屈折するために発生します。
        //一方、金属はエネルギーを反射または吸収するため、拡散寄与は常にゼロです。
        //エネルギーを節約するには、フレネル係数と金属性に基づいて拡散BRDFの寄与をスケーリングする必要があります。
        float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metalness);


        //ランバート拡散BRDF。
        //照明とマテリアルのユニットをより便利にするために、1 / PIでスケーリングしません。		// See: https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/
        float3 diffuseBRDF = kd * albedo;


        // Cook-TorranceスペキュラーマイクロファセットBRDF。
        float3 specularBRDF = (F * D * G) / max(Epsilon, 4.0 * cosLi * cosLo);

		// Total contribution for this light.
        directLighting += (diffuseBRDF + specularBRDF) * Lradiance * cosLi;
    }

	// Ambient lighting (IBL).
    float3 ambientLighting;
	{
        //法線方向の拡散放射照度をサンプリングします。
        float3 irradiance =
        {
            1.0, 0.3, 0.2
        };

        //環境照明のフレネル項を計算します。
        //事前にフィルタリングされたキューブマップを使用し、放射照度は多くの方向から来るため
        //ライトのハーフベクトル（上記のcosLh）で角度の代わりにcosLoを使用します。		// See: https://seblagarde.wordpress.com/2011/08/17/hello-world/
        float3 F = fresnelSchlick(F0, cosLo);


        //拡散寄与率を取得します（直接照明の場合と同様）。
        float3 kd = lerp(1.0 - F, 0.0, metalness);


        //放射照度マップには、ランバートBRDFを想定した放射輝度が含まれており、ここでも1 / PIでスケーリングする必要はありません。
        float3 diffuseIBL = kd * albedo * irradiance;
        
        //正しいミップマップレベルでの事前フィルタリングされた鏡面反射環境のサンプル。
        //  uint specularTextureLevels = querySpecularTextureLevels();
        float3 specularIrradiance = { 1.0, 1.0, 1.0 };


        // Cook-TorranceスペキュラBRDFの分割合計近似係数。
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