#pragma once

namespace	epion::NodeCustom::Dx11
{
	/**
	* @brief Nodeで規定している定数バッファ管理
	*/
	struct	BefferBase	abstract
	{
		virtual ~BefferBase() {}
	};
	struct	CBuffer0	final
	{
		math::FVector4	Time;
		math::FVector2	ScreenSize;
		math::FVector2	Dummy0;
	};

	struct	CBuffer1	final
	{
		math::FVector4	LightColor;		//ライトの色
		math::FVector4	LightDir;		//ライトの方向
		math::FVector4	AmbientColor;	//環境光
	};
	/**
	* @brief	このエディタで規定されてる定数バッファの管理
	* @details	TODO ユーザー側に提供するときの考慮
	*/

	class	ConstantBufferManager
	{
	public:
		static bool Create();
		static void	UpdateCBuffer0(math::FVector4&	Time, math::FVector2&	ScreenSize);
		static void	UpdateCBuffer1(math::FVector4&	LightColor, math::FVector4&	LightDir, math::FVector4&	AmbientColor);

	private:
		static void CreateDesc(D3D11_BUFFER_DESC& desc, UINT size);

		static com_ptr<ID3D11Buffer>	m_constant_buffer0;
		static com_ptr<ID3D11Buffer>	m_constant_buffer1;
	};

	/**
	* @brief	このエディタで規定されてるSamplerの管理
	* @details	TODO ユーザー側に提供するときの考慮
	*/

	class	SamplerStateManager	final
	{
	public:
		static bool Create(int index, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address);
		static void SetState(int index);

	private:
		static com_ptr<ID3D11SamplerState>	m_sampler_states[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
	};

}