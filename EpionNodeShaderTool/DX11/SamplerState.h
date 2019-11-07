#pragma once
namespace	epion
{
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